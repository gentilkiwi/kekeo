/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kull_m_kerberos_asn1_crypto.h"

NTSTATUS kull_m_kerberos_asn1_crypto_ekey_create_fromHexString(LPCWSTR key, EncryptionKey *ekey)
{
	NTSTATUS status;
	PKERB_ECRYPT pCSystem;
	status = CDLocateCSystem(ekey->keytype, &pCSystem);
	if(NT_SUCCESS(status))
	{
		ekey->keyvalue.length = pCSystem->KeySize;
		if(ekey->keyvalue.value = (unsigned char * ) LocalAlloc(LPTR, ekey->keyvalue.length))
		{
			if(!kull_m_string_stringToHex(key, ekey->keyvalue.value, ekey->keyvalue.length))
			{
				PRINT_ERROR(L"key size length must be %u (%u bytes) for %s\n", pCSystem->KeySize * 2, pCSystem->KeySize, kull_m_kerberos_asn1_crypto_etype(ekey->keytype));
				status = STATUS_WRONG_PASSWORD;
				ekey->keyvalue.value = (unsigned char *) LocalFree(ekey->keyvalue.value);
			}
		}
	}
	else PRINT_ERROR(L"CDLocateCSystem: %08x\n", status);
	return status;
}

NTSTATUS kull_m_kerberos_asn1_crypto_ekey_create_fromPassword(LPCWSTR w_realm, LPCWSTR w_short_cname, LPCWSTR w_password, EncryptionKey *ekey)
{
	NTSTATUS status;
	PKERB_ECRYPT pCSystem;
	UNICODE_STRING uUser, uDomain, uDomainUP, uPassword, uSalt = {0, 0, NULL};

	status = CDLocateCSystem(ekey->keytype, &pCSystem);
	if(NT_SUCCESS(status))
	{
		ekey->keyvalue.length = pCSystem->KeySize;
		if(ekey->keyvalue.value = (unsigned char *) LocalAlloc(LPTR, ekey->keyvalue.length))
		{
			RtlInitUnicodeString(&uUser, w_short_cname);
			RtlInitUnicodeString(&uDomain, w_realm);
			RtlInitUnicodeString(&uPassword, w_password);
			status = RtlUpcaseUnicodeString(&uDomainUP, &uDomain, TRUE);
			if(NT_SUCCESS(status))
			{
				uSalt.MaximumLength = uUser.Length + uDomainUP.Length + sizeof(wchar_t);
				if(uSalt.Buffer = (PWSTR) LocalAlloc(LPTR, uSalt.MaximumLength))
				{
					RtlAppendUnicodeStringToString(&uSalt, &uDomainUP);
					RtlAppendUnicodeStringToString(&uSalt, &uUser);
					status = (MIMIKATZ_NT_MAJOR_VERSION < 6) ? pCSystem->HashPassword_NT5(&uPassword, ekey->keyvalue.value) : pCSystem->HashPassword_NT6(&uPassword, &uSalt, 4096, ekey->keyvalue.value);
					if(!NT_SUCCESS(status))
						PRINT_ERROR(L"HashPassword: %08x\n", status);
					LocalFree(uSalt.Buffer);
				}
				RtlFreeUnicodeString(&uDomainUP);
			}
			if(!NT_SUCCESS(status))
				ekey->keyvalue.value = (unsigned char *) LocalFree(ekey->keyvalue.value);
		}
	}
	else PRINT_ERROR(L"CDLocateCSystem: %08x\n", status);
	return status;
}

void kull_m_kerberos_asn1_crypto_ekey_free(EncryptionKey *ekey)
{
	if(ekey)
		if(ekey->keyvalue.value)
			ekey->keyvalue.value = (unsigned char *) LocalFree(ekey->keyvalue.value);
}

void kull_m_kerberos_asn1_crypto_ekey_descr(EncryptionKey *ekey)
{
	if(ekey)
	{
		kprintf(L"ENCRYPTION KEY %i (%s): ", ekey->keytype, kull_m_kerberos_asn1_crypto_etype(ekey->keytype));
		if(ekey->keyvalue.length && ekey->keyvalue.value)
			kull_m_string_wprintf_hex(ekey->keyvalue.value, ekey->keyvalue.length, 0);
		kprintf(L"\n");
	}
}

NTSTATUS kull_m_kerberos_asn1_crypto_encrypt(DWORD keyUsage, EncryptionKey *key, OssBuf *in, OssBuf *out, BOOL encrypt)
{
	NTSTATUS status;
	PKERB_ECRYPT pCSystem;
	PVOID pContext;
	DWORD modulo;

	status = CDLocateCSystem(key->keytype, &pCSystem);
	if(NT_SUCCESS(status))
	{
		status = pCSystem->Initialize(key->keyvalue.value, key->keyvalue.length, keyUsage, &pContext);
		if(NT_SUCCESS(status))
		{
			out->length = in->length;
			if(encrypt)
			{
				if(modulo = out->length % pCSystem->BlockSize)
					out->length += pCSystem->BlockSize - modulo;
				out->length += pCSystem->Size;
			}
			if(out->value = (unsigned char *) LocalAlloc(LPTR, out->length))
			{
				status = encrypt ? pCSystem->Encrypt(pContext, in->value, in->length, out->value, (DWORD *) &out->length) : pCSystem->Decrypt(pContext, in->value, in->length, out->value, (DWORD *) &out->length);
				if(!NT_SUCCESS(status))
					LocalFree(out->value);
			}
			pCSystem->Finish(&pContext);
		}
	}
	return status;
}

BOOL kull_m_kerberos_asn1_crypto_get_CertInfo(PCWSTR Subject, PKULL_M_CRYPTO_CERT_INFO certInfo)
{
	BOOL status = FALSE, keyToFree;
	RtlZeroMemory(certInfo, sizeof(KULL_M_CRYPTO_CERT_INFO));
	if(certInfo->hCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, (HCRYPTPROV_LEGACY) NULL, CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG, L"My"))
		if(certInfo->pCertContext = CertFindCertificateInStore(certInfo->hCertStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_SUBJECT_STR, Subject, NULL))
			status = CryptAcquireCertificatePrivateKey(certInfo->pCertContext, CRYPT_ACQUIRE_CACHE_FLAG, NULL, &certInfo->provider.hProv, &certInfo->provider.dwKeySpec, &keyToFree);
	
	if(!status)
		kull_m_kerberos_asn1_crypto_free_CertInfo(certInfo);
	return status;
}

void kull_m_kerberos_asn1_crypto_free_CertInfo(PKULL_M_CRYPTO_CERT_INFO certInfo)
{
	if(certInfo->pCertContext)
		CertFreeCertificateContext(certInfo->pCertContext);
	if(certInfo->hCertStore)
		CertCloseStore(certInfo->hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
}

void kull_m_kerberos_asn1_crypto_CertInfo_descr(PKULL_M_CRYPTO_CERT_INFO certInfo)
{
	//certInfo->

}


BOOL kull_m_kerberos_asn1_crypto_simple_message_sign(PKULL_M_CRYPTO_CERT_INFO certInfo, OssBuf *input, _octet1 *output)
{
	BOOL status = FALSE;
	HCRYPTMSG hCryptMsg;
	CERT_BLOB Certificate = {certInfo->pCertContext->cbCertEncoded, certInfo->pCertContext->pbCertEncoded};
	CMSG_SIGNER_ENCODE_INFO Signers = {sizeof(CMSG_SIGNER_ENCODE_INFO), certInfo->pCertContext->pCertInfo, certInfo->provider.hProv, certInfo->provider.dwKeySpec, {szOID_OIWSEC_sha1, 0, NULL}, NULL, 0, NULL, 0, NULL};
	CMSG_SIGNED_ENCODE_INFO MsgEncodeInfo = {sizeof(CMSG_SIGNED_ENCODE_INFO), 1, &Signers, 1, &Certificate, 0, NULL};
	RtlZeroMemory(output, sizeof(_octet1));

	if(hCryptMsg = CryptMsgOpenToEncode(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, CMSG_CMS_ENCAPSULATED_CONTENT_FLAG, CMSG_SIGNED, &MsgEncodeInfo, "1.3.6.1.5.2.3.1", NULL))
	{
		if(CryptMsgUpdate(hCryptMsg, input->value, input->length, TRUE))
		{
			if(CryptMsgGetParam(hCryptMsg, CMSG_CONTENT_PARAM, 0, NULL, (PDWORD) &output->length))
			{
				if(output->value = (PBYTE) LocalAlloc(LPTR, output->length))
					if(!(status = CryptMsgGetParam(hCryptMsg, CMSG_CONTENT_PARAM, 0, output->value, (PDWORD) &output->length)))
					{
						PRINT_ERROR_AUTO(L"CryptMsgGetParam(CMSG_CONTENT_PARAM - data)");
						LocalFree(output->value);
					}
			}
			else PRINT_ERROR_AUTO(L"CryptMsgGetParam(CMSG_CONTENT_PARAM - init)");
		}
		else PRINT_ERROR_AUTO(L"CryptMsgUpdate");
		CryptMsgClose(hCryptMsg);
	}
	else PRINT_ERROR_AUTO(L"CryptMsgOpenToEncode");
	return status;
}

BOOL kull_m_kerberos_asn1_crypto_simple_message_dec(PKULL_M_CRYPTO_PROV_INFO provInfo, _octet1 *input, OssBuf *output)
{
	BOOL status = FALSE;
	HCRYPTMSG hCryptMsg;
	CMSG_CTRL_DECRYPT_PARA DecryptParam = {sizeof(CMSG_CTRL_DECRYPT_PARA), provInfo->hProv, provInfo->dwKeySpec, 0};
	_octet1 buffer = {0, NULL};
	RtlZeroMemory(output, sizeof(OssBuf));

	if(hCryptMsg = CryptMsgOpenToDecode(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, 0, 0, NULL, NULL))
	{
		if(CryptMsgUpdate(hCryptMsg, input->value, input->length, TRUE))
		{
			if(CryptMsgControl(hCryptMsg, 0, CMSG_CTRL_DECRYPT, &DecryptParam))
			{
				if(CryptMsgGetParam(hCryptMsg, CMSG_CONTENT_PARAM, 0, NULL, (PDWORD) &buffer.length))
				{
					if(buffer.value = (PBYTE) LocalAlloc(LPTR, buffer.length))
					{
						if(CryptMsgGetParam(hCryptMsg, CMSG_CONTENT_PARAM, 0, buffer.value, (PDWORD) &buffer.length))
							status = kull_m_kerberos_asn1_crypto_simple_message_get(&buffer, output);
						else PRINT_ERROR_AUTO(L"CryptMsgGetParam(CMSG_CONTENT_PARAM - data)");
						LocalFree(buffer.value);
					}
				}
				else PRINT_ERROR_AUTO(L"CryptMsgGetParam(CMSG_CONTENT_PARAM - init)");
			}
			else PRINT_ERROR_AUTO(L"CryptMsgControl(CMSG_CTRL_DECRYPT)");
		}
		else PRINT_ERROR_AUTO(L"CryptMsgUpdate");
		CryptMsgClose(hCryptMsg);
	}
	else PRINT_ERROR_AUTO(L"CryptMsgOpenToEncode");
	return status;
}

BOOL kull_m_kerberos_asn1_crypto_simple_message_get(_octet1 *input, OssBuf *output)
{
	BOOL status = FALSE;
	HCRYPTMSG hCryptMsg2;
	output->length = 0;
	output->value = NULL;

	if(hCryptMsg2 = CryptMsgOpenToDecode(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, 0, 0, NULL, NULL))
	{
		if(CryptMsgUpdate(hCryptMsg2, input->value, input->length, TRUE))
		{
			if(CryptMsgGetParam(hCryptMsg2, CMSG_CONTENT_PARAM, 0, NULL, (PDWORD) &output->length))
			{
				if(output->value = (PBYTE) LocalAlloc(LPTR, output->length))
					if(!(status = CryptMsgGetParam(hCryptMsg2, CMSG_CONTENT_PARAM, 0, output->value, (PDWORD) &output->length)))
					{
						PRINT_ERROR_AUTO(L"CryptMsgGetParam(CMSG_CONTENT_PARAM - data)");
						LocalFree(output->value);
					}
			}
			else PRINT_ERROR_AUTO(L"CryptMsgGetParam(CMSG_CONTENT_PARAM - init)");
		}
		else PRINT_ERROR_AUTO(L"CryptMsgUpdate");
		CryptMsgClose(hCryptMsg2);
	}
	else PRINT_ERROR_AUTO(L"CryptMsgOpenToEncode");
	return status;
}

BOOL kull_m_kerberos_asn1_crypto_genericEncode(__in LPCSTR lpszStructType, __in const void *pvStructInfo, __inout PBYTE *pvEncoded, __inout DWORD *pcbEncoded)
{
	BOOL status = FALSE;
	*pcbEncoded = 0;
	if(CryptEncodeObjectEx(X509_ASN_ENCODING, lpszStructType, pvStructInfo, 0, NULL, NULL, pcbEncoded))
		if(*pvEncoded = (PBYTE) LocalAlloc(LPTR, *pcbEncoded))
			if(!(status = CryptEncodeObjectEx(X509_ASN_ENCODING, lpszStructType, pvStructInfo, 0, NULL, *pvEncoded, pcbEncoded)))
				LocalFree(*pvEncoded);
	return status;
}

BOOL kull_m_kerberos_asn1_crypto_genericDecode(__in LPCSTR lpszStructType,  __in_bcount(cbEncoded) const BYTE *pbEncoded, __in DWORD cbEncoded, __out void **ppvStructInfo)
{
	BOOL status = FALSE;
	DWORD szNeeded = 0;
	if(CryptDecodeObjectEx(X509_ASN_ENCODING, lpszStructType, pbEncoded, cbEncoded, 0, NULL, NULL, &szNeeded))
		if(*ppvStructInfo = LocalAlloc(LPTR, szNeeded))
			if(!(status = CryptDecodeObjectEx(X509_ASN_ENCODING, lpszStructType, pbEncoded, cbEncoded, 0, NULL, *ppvStructInfo, &szNeeded)))
				LocalFree(*ppvStructInfo);
	return status;
}

const BYTE kull_m_kerberos_asn1_crypto_g_rgbPrime[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x53, 0xe6, 0xec, 0x51, 0x66, 0x28, 0x49,
	0xe6, 0x1f, 0x4b, 0x7c, 0x11, 0x24, 0x9f, 0xae, 0xa5, 0x9f, 0x89, 0x5a, 0xfb, 0x6b, 0x38, 0xee,
	0xed, 0xb7, 0x06, 0xf4, 0xb6, 0x5c, 0xff, 0x0b, 0x6b, 0xed, 0x37, 0xa6, 0xe9, 0x42, 0x4c, 0xf4,
	0xc6, 0x7e, 0x5e, 0x62, 0x76, 0xb5, 0x85, 0xe4, 0x45, 0xc2, 0x51, 0x6d, 0x6d, 0x35, 0xe1, 0x4f,
	0x37, 0x14, 0x5f, 0xf2, 0x6d, 0x0a, 0x2b, 0x30, 0x1b, 0x43, 0x3a, 0xcd, 0xb3, 0x19, 0x95, 0xef,
	0xdd, 0x04, 0x34, 0x8e, 0x79, 0x08, 0x4a, 0x51, 0x22, 0x9b, 0x13, 0x3b, 0xa6, 0xbe, 0x0b, 0x02,
	0x74, 0xcc, 0x67, 0x8a, 0x08, 0x4e, 0x02, 0x29, 0xd1, 0x1c, 0xdc, 0x80, 0x8b, 0x62, 0xc6, 0xc4,
	0x34, 0xc2, 0x68, 0x21, 0xa2, 0xda, 0x0f, 0xc9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

const BYTE kull_m_kerberos_asn1_crypto_g_rgbGenerator[] = {
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const CERT_X942_DH_PARAMETERS kull_m_kerberos_asn1_crypto_dhGlobParameters = {
		{sizeof(kull_m_kerberos_asn1_crypto_g_rgbPrime), (PBYTE) kull_m_kerberos_asn1_crypto_g_rgbPrime},
		{sizeof(kull_m_kerberos_asn1_crypto_g_rgbGenerator), (PBYTE) kull_m_kerberos_asn1_crypto_g_rgbGenerator},
		{0, NULL},
		{0, NULL},
		NULL
};

const BYTE kull_m_kerberos_asn1_crypto_goodDhKey[] = {
	0x07, 0x02, 0x00, 0x00, 0x02, 0xaa, 0x00, 0x00, 0x00, 0x44, 0x48, 0x32, 0x00, 0x04, 0x00, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x53, 0xe6, 0xec, 0x51, 0x66, 0x28, 0x49,
	0xe6, 0x1f, 0x4b, 0x7c, 0x11, 0x24, 0x9f, 0xae, 0xa5, 0x9f, 0x89, 0x5a, 0xfb, 0x6b, 0x38, 0xee,
	0xed, 0xb7, 0x06, 0xf4, 0xb6, 0x5c, 0xff, 0x0b, 0x6b, 0xed, 0x37, 0xa6, 0xe9, 0x42, 0x4c, 0xf4,
	0xc6, 0x7e, 0x5e, 0x62, 0x76, 0xb5, 0x85, 0xe4, 0x45, 0xc2, 0x51, 0x6d, 0x6d, 0x35, 0xe1, 0x4f,
	0x37, 0x14, 0x5f, 0xf2, 0x6d, 0x0a, 0x2b, 0x30, 0x1b, 0x43, 0x3a, 0xcd, 0xb3, 0x19, 0x95, 0xef,
	0xdd, 0x04, 0x34, 0x8e, 0x79, 0x08, 0x4a, 0x51, 0x22, 0x9b, 0x13, 0x3b, 0xa6, 0xbe, 0x0b, 0x02,
	0x74, 0xcc, 0x67, 0x8a, 0x08, 0x4e, 0x02, 0x29, 0xd1, 0x1c, 0xdc, 0x80, 0x8b, 0x62, 0xc6, 0xc4,
	0x34, 0xc2, 0x68, 0x21, 0xa2, 0xda, 0x0f, 0xc9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xef, 0x97, 0x84, 0xda, 0xfe, 0xed, 0xe2, 0xd4, 0xe1, 0x64, 0xe1, 0x64, 0xe6, 0x14, 0xbf, 0x08,
	0x99, 0xb1, 0x4c, 0x40, 0xb8, 0xac, 0xc2, 0xca, 0xc3, 0x37, 0x98, 0x71, 0x08, 0x9c, 0x08, 0xaa,
	0x9b, 0x9c, 0xe4, 0x5b, 0x33, 0xc6, 0xe6, 0x1e, 0x77, 0xfb, 0x82, 0x68, 0x25, 0x00, 0x7a, 0x94,
	0x15, 0xbb, 0x9e, 0xe0, 0xca, 0x50, 0xdc, 0x2c, 0x53, 0xa2, 0x42, 0x94, 0x97, 0x3b, 0x18, 0x8a,
	0x05, 0x29, 0xdd, 0x33, 0x93, 0x03, 0xbe, 0xbc, 0xb6, 0x55, 0xe7, 0x8f, 0x44, 0xf0, 0x5b, 0x20,
	0xa9, 0x16, 0x9e, 0x75, 0xc1, 0x01, 0xe9, 0x7d, 0xa4, 0x6c, 0xc5, 0x7f, 0xee, 0x38, 0xe5, 0xd1,
	0xbb, 0xf5, 0x28, 0xf5, 0xd3, 0x91, 0xf0, 0xaa, 0x04, 0xfc, 0xab, 0x69, 0x79, 0xfd, 0xfa, 0x39,
	0xd1, 0x19, 0x8e, 0x7d, 0x0e, 0xb7, 0x36, 0xb9, 0xbe, 0x81, 0xeb, 0x7f, 0xf0, 0x10, 0x1e, 0x2e,
};

BOOL kull_m_kerberos_asn1_crypto_get_DHKeyInfo(BOOL integrated, BOOL withNonce, PKULL_M_CRYPTO_DH_KEY_INFO keyInfo)
{
	BOOL status = FALSE;

	RtlZeroMemory(keyInfo, sizeof(KULL_M_CRYPTO_DH_KEY_INFO));
	if(CryptAcquireContext(&keyInfo->hProv, NULL, MS_ENH_DSS_DH_PROV, PROV_DSS_DH, CRYPT_VERIFYCONTEXT))
	{
		#ifdef _M_X64
		#define DH_XOR		0xa2491d83d96214a0
		#define DH_OFFSET	6
		#else
		#define DH_XOR		0xa2491d83
		#define DH_OFFSET	5
		# endif
		((PDWORD) (((PULONG_PTR) keyInfo->hProv)[28] ^ DH_XOR))[DH_OFFSET] = TRUE; // :)
		if(integrated)
		{
			if(CryptImportKey(keyInfo->hProv, kull_m_kerberos_asn1_crypto_goodDhKey, sizeof(kull_m_kerberos_asn1_crypto_goodDhKey), 0, CRYPT_EXPORTABLE, &keyInfo->hKey))
				status = CryptSetKeyParam(keyInfo->hKey, KP_Q, (PBYTE) &kull_m_kerberos_asn1_crypto_dhGlobParameters.q, 0);
		}
		else
		{
			if(CryptGenKey(keyInfo->hProv, CALG_DH_EPHEM, RSA1024BIT_KEY | CRYPT_EXPORTABLE, &keyInfo->hKey))
				if(CryptSetKeyParam(keyInfo->hKey, KP_P, (PBYTE) &kull_m_kerberos_asn1_crypto_dhGlobParameters.p, 0))
					if(CryptSetKeyParam(keyInfo->hKey, KP_G, (PBYTE) &kull_m_kerberos_asn1_crypto_dhGlobParameters.g, 0))
						if(CryptSetKeyParam(keyInfo->hKey, KP_Q, (PBYTE) &kull_m_kerberos_asn1_crypto_dhGlobParameters.q, 0))
							status = CryptSetKeyParam(keyInfo->hKey, KP_X, NULL, 0);
		}

		if(status && withNonce)
		{
			status = FALSE;
			keyInfo->dhClientNonce.length = AES_256_KEY_LENGTH;
			if(keyInfo->dhClientNonce.value = (PBYTE) LocalAlloc(LPTR, keyInfo->dhClientNonce.length))
				if(!(status = NT_SUCCESS(CDGenerateRandomBits(keyInfo->dhClientNonce.value, keyInfo->dhClientNonce.length))))
					SetLastError(ERROR_INTERNAL_ERROR);
		}
	}
	if(!status)
		kull_m_kerberos_asn1_crypto_free_DHKeyInfo(keyInfo);
	return status;
}

void kull_m_kerberos_asn1_crypto_free_DHKeyInfo(PKULL_M_CRYPTO_DH_KEY_INFO keyInfo)
{
	if(keyInfo->dhClientNonce.value)
		LocalFree(keyInfo->dhClientNonce.value);
	if(keyInfo->hKey)
		CryptDestroyKey(keyInfo->hKey);
	if(keyInfo->hProv)
		CryptReleaseContext(keyInfo->hProv, 0);
}

BOOL kull_m_kerberos_asn1_crypto_get_DHKeyInfo_Parameters(HCRYPTKEY hKey, PCERT_X942_DH_PARAMETERS parameters)
{
	BOOL status = FALSE;
	RtlZeroMemory(parameters, sizeof(CERT_X942_DH_PARAMETERS));
	if(CryptGetKeyParam(hKey, KP_P, NULL, &parameters->p.cbData, 0))
		if(parameters->p.pbData = (PBYTE) LocalAlloc(LPTR, parameters->p.cbData))
			if(CryptGetKeyParam(hKey, KP_P, parameters->p.pbData, &parameters->p.cbData, 0))
				if(CryptGetKeyParam(hKey, KP_G, NULL, &parameters->g.cbData, 0))
					if(parameters->g.pbData = (PBYTE) LocalAlloc(LPTR, parameters->g.cbData))
						status = CryptGetKeyParam(hKey, KP_G, parameters->g.pbData, &parameters->g.cbData, 0);

	if(!status)
		kull_m_kerberos_asn1_crypto_free_DHKeyInfo_Parameters(parameters);
	return status;
}

void kull_m_kerberos_asn1_crypto_free_DHKeyInfo_Parameters(PCERT_X942_DH_PARAMETERS parameters)
{
	if(parameters->p.pbData)
		LocalFree(parameters->p.pbData);
	if(parameters->g.pbData)
		LocalFree(parameters->g.pbData);
	if(parameters->q.pbData)
		LocalFree(parameters->q.pbData);
	if(parameters->j.pbData)
		LocalFree(parameters->j.pbData);
}

void kull_m_kerberos_asn1_crypto_reverseit(PVOID data, DWORD dwData)
{
	DWORD i;
	PBYTE buffer;
	if(buffer = (PBYTE) LocalAlloc(LPTR, dwData))
	{
		for(i = 0; i < dwData; i++)
			buffer[dwData - 1 - i] = ((PBYTE) data)[i];
		RtlCopyMemory(data, buffer, dwData);
		LocalFree(buffer);
	}
}

void kull_m_kerberos_asn1_crypto_k_truncate(PVOID input, DWORD cbInput, PVOID output, DWORD cbOutput)
{
	BYTE counter;
	DWORD offset;
	SHA_CTX ctx;
	SHA_DIGEST shaDigest;
	for(counter = 0, offset = 0; offset < cbOutput; counter++, offset += SHA_DIGEST_LENGTH)
	{
		 A_SHAInit(&ctx);
		 A_SHAUpdate(&ctx, &counter, 1);
		 A_SHAUpdate(&ctx, input, cbInput);
		 A_SHAFinal(&ctx, &shaDigest);
		 RtlCopyMemory((PBYTE) output + offset, shaDigest.digest, min(cbOutput - offset, SHA_DIGEST_LENGTH));
	}
}

BOOL kull_m_kerberos_asn1_crypto_octetstring2key(PVOID input, DWORD cbInput, DHNonce *client, DHNonce *server, EncryptionKey *ekey)
{
	BOOL status = FALSE;
	PKERB_ECRYPT pCSystem;
	PVOID iBuffer, oBuffer;
	DWORD iCbBuffer, clientLen = client ? client->length : 0, serverLen = server ? server->length : 0;

	if(NT_SUCCESS(CDLocateCSystem(ekey->keytype, &pCSystem)))
	{
		iCbBuffer = cbInput + clientLen + serverLen;
		if(iBuffer = LocalAlloc(LPTR, iCbBuffer))
		{
			RtlCopyMemory(iBuffer, input, cbInput);
			if(clientLen)
				RtlCopyMemory((PBYTE) iBuffer + cbInput, client->value, client->length);
			if(serverLen)
				RtlCopyMemory((PBYTE) iBuffer + cbInput + clientLen, server->value, server->length);
			if(oBuffer = LocalAlloc(LPTR, pCSystem->KeySize))
			{
				kull_m_kerberos_asn1_crypto_k_truncate(iBuffer, iCbBuffer, oBuffer, pCSystem->KeySize);
				ekey->keyvalue.length = pCSystem->KeySize;
				if(ekey->keyvalue.value = (PBYTE) LocalAlloc(LPTR, ekey->keyvalue.length))
					if(!(status = NT_SUCCESS(pCSystem->RandomKey(oBuffer, pCSystem->KeySize, ekey->keyvalue.value))))
						LocalFree(ekey->keyvalue.value);
				LocalFree(oBuffer);
			}
			LocalFree(iBuffer);
		}
	}
	return status;
}

BOOL kull_m_kerberos_asn1_crypto_get_CertFromCA(PCWSTR caname, PCWSTR castore, PCWSTR upn, PKULL_M_CRYPTO_CERT_INFO certInfo, PCRYPT_KEY_PROV_INFO keyInfo)
{
	BOOL status = FALSE;
	HCERTSTORE hCertStoreCA;
	PCCERT_CONTEXT pCertCtxCA;
	HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hKeyCA;
	DWORD dwKeySpecCA;
	BOOL bToFreeCA;
	HCRYPTKEY hKeyCERT;
	BYTE SerialNumber[42];
	CERT_RDN_ATTR rgNameAttr[] = {
		{szOID_COMMON_NAME, CERT_RDN_UNICODE_STRING, {0, NULL}},
		{szOID_ORGANIZATION_NAME, CERT_RDN_UNICODE_STRING, {10, (PBYTE) MIMIKATZ}},
		{szOID_COUNTRY_NAME, CERT_RDN_UNICODE_STRING, {sizeof(L"FR") - sizeof(wchar_t), (PBYTE) L"FR"}},
	};
	CERT_RDN rgRDN = {ARRAYSIZE(rgNameAttr), rgNameAttr};
	CERT_NAME_INFO Name = {1, &rgRDN};
	CERT_EXTENSION Extensions[3] = {0}; // EKU, KU, AltNames
	DWORD cbPublicKeyInfo;
	PCERT_PUBLIC_KEY_INFO pbPublicKeyInfo;
	CERT_INFO CertInfo = {0};
	DWORD szCertificate = 0;
	PBYTE Certificate = NULL;

	RtlZeroMemory(certInfo, sizeof(KULL_M_CRYPTO_CERT_INFO));
	RtlZeroMemory(keyInfo, sizeof(CRYPT_KEY_PROV_INFO));

	if(keyInfo->pwszContainerName = kull_m_string_getRandomGUID())
	{
		keyInfo->pwszProvName = MS_ENHANCED_PROV_W;
		keyInfo->dwProvType = PROV_RSA_FULL;
		keyInfo->dwFlags = CRYPT_SILENT;
		keyInfo->cProvParam = 0;
		keyInfo->rgProvParam = NULL;
		keyInfo->dwKeySpec = AT_KEYEXCHANGE;

		CertInfo.dwVersion = CERT_V3;
		CertInfo.SerialNumber.cbData = sizeof(SerialNumber);
		CertInfo.SerialNumber.pbData = SerialNumber;
		CertInfo.cExtension = ARRAYSIZE(Extensions);
		CertInfo.rgExtension = Extensions;
		CDGenerateRandomBits(CertInfo.SerialNumber.pbData, CertInfo.SerialNumber.cbData);

		rgNameAttr[0].Value.cbData = (DWORD) wcslen(upn) * sizeof(wchar_t);
		rgNameAttr[0].Value.pbData = (PBYTE) upn;
		kprintf(L"CA store           : %s\n", castore);
		if(hCertStoreCA = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, (HCRYPTPROV_LEGACY) NULL, kull_m_kerberos_asn1_crypto_system_store_to_dword(castore) | CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG, L"My"))
		{
			kprintf(L"CA name            : %s\n", caname);
			if(pCertCtxCA = CertFindCertificateInStore(hCertStoreCA, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_SUBJECT_STR, caname, NULL))
			{
				kprintf(L"CA validity        : "); kull_m_string_displayLocalFileTime(&pCertCtxCA->pCertInfo->NotBefore);
				kprintf(L" -> "); kull_m_string_displayLocalFileTime(&pCertCtxCA->pCertInfo->NotAfter); kprintf(L"\n");
				if(CryptAcquireCertificatePrivateKey(pCertCtxCA, CRYPT_ACQUIRE_CACHE_FLAG | CRYPT_ACQUIRE_ALLOW_NCRYPT_KEY_FLAG, NULL, &hKeyCA, &dwKeySpecCA, &bToFreeCA))
				{
					CertInfo.Issuer = pCertCtxCA->pCertInfo->Subject;
					CertInfo.IssuerUniqueId = pCertCtxCA->pCertInfo->SubjectUniqueId;
					CertInfo.NotBefore = pCertCtxCA->pCertInfo->NotBefore;
					CertInfo.NotAfter = pCertCtxCA->pCertInfo->NotAfter;
					CertInfo.SignatureAlgorithm = pCertCtxCA->pCertInfo->SignatureAlgorithm;
					kprintf(L"Certificate UPN    : %s\n", upn);
					if(kull_m_kerberos_asn1_crypto_genericEncode(X509_NAME, &Name, &CertInfo.Subject.pbData, &CertInfo.Subject.cbData))
					{
						if(kull_m_kerberos_asn1_crypto_sc_auth_Ext_EKU(&Extensions[0], 2, szOID_KP_SMARTCARD_LOGON, szOID_PKIX_KP_CLIENT_AUTH))
						{
							if(kull_m_kerberos_asn1_crypto_sc_auth_Ext_KU(&Extensions[1], CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE))
							{
								if(kull_m_kerberos_asn1_crypto_sc_auth_Ext_AltUPN(&Extensions[2], upn))
								{
									kprintf(L"Key container      : %s\n", keyInfo->pwszContainerName);
									kprintf(L"Key provider       : %s\n", keyInfo->pwszProvName);
									certInfo->provider.dwKeySpec = keyInfo->dwKeySpec;
									if(CryptAcquireContextW(&certInfo->provider.hProv, keyInfo->pwszContainerName, keyInfo->pwszProvName, keyInfo->dwProvType, CRYPT_NEWKEYSET | keyInfo->dwFlags))
									{
										if(CryptGenKey(certInfo->provider.hProv, certInfo->provider.dwKeySpec, CRYPT_EXPORTABLE | (RSA1024BIT_KEY * 2), &hKeyCERT))
										{
											if(CryptExportPublicKeyInfo(certInfo->provider.hProv, certInfo->provider.dwKeySpec, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, &cbPublicKeyInfo))
											{
												if(pbPublicKeyInfo = (PCERT_PUBLIC_KEY_INFO) LocalAlloc(LPTR, cbPublicKeyInfo))
												{
													if(CryptExportPublicKeyInfo(certInfo->provider.hProv, certInfo->provider.dwKeySpec, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, pbPublicKeyInfo, &cbPublicKeyInfo))
													{
														CertInfo.SubjectPublicKeyInfo = *pbPublicKeyInfo;
														if(CryptSignAndEncodeCertificate(hKeyCA, dwKeySpecCA, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, X509_CERT_TO_BE_SIGNED, &CertInfo, &CertInfo.SignatureAlgorithm, NULL, NULL, &szCertificate))
														{
															if(Certificate = (PBYTE) LocalAlloc(LPTR, szCertificate))
															{
																if(CryptSignAndEncodeCertificate(hKeyCA, dwKeySpecCA, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, X509_CERT_TO_BE_SIGNED, &CertInfo, &CertInfo.SignatureAlgorithm, NULL, Certificate, &szCertificate))
																{
																	if(certInfo->hCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0, CERT_STORE_CREATE_NEW_FLAG, NULL))
																	{
																		if(CertAddEncodedCertificateToStore(certInfo->hCertStore, X509_ASN_ENCODING, Certificate, szCertificate, CERT_STORE_ADD_NEW, &certInfo->pCertContext))
																		{
																			if(!(status = CertSetCertificateContextProperty(certInfo->pCertContext, CERT_KEY_PROV_INFO_PROP_ID, 0, (LPCVOID) keyInfo)))
																				PRINT_ERROR_AUTO(L"CertSetCertificateContextProperty(CERT_KEY_PROV_INFO_PROP_ID)");
																		}
																	}
																}
																else PRINT_ERROR_AUTO(L"CryptSignAndEncodeCertificate (data)");
																LocalFree(Certificate);
															}
														}
														else PRINT_ERROR_AUTO(L"CryptSignAndEncodeCertificate (init)");
													}
													else PRINT_ERROR_AUTO(L"CryptExportPublicKeyInfo (data)");
													LocalFree(pbPublicKeyInfo);
												}
											}
											else PRINT_ERROR_AUTO(L"CryptExportPublicKeyInfo (init)");
											CryptDestroyKey(hKeyCERT);
										}
										else PRINT_ERROR_AUTO(L"CryptGenKey");
									}
									else PRINT_ERROR_AUTO(L"CryptAcquireContext");
									kull_m_kerberos_asn1_crypto_sc_auth_Ext_Free(&Extensions[2]);
								}
								kull_m_kerberos_asn1_crypto_sc_auth_Ext_Free(&Extensions[1]);
							}
							kull_m_kerberos_asn1_crypto_sc_auth_Ext_Free(&Extensions[0]);
						}
						LocalFree(CertInfo.Subject.pbData);
					}
					CryptReleaseContext(hKeyCA, 0);
				}
				else PRINT_ERROR_AUTO(L"CryptAcquireCertificatePrivateKey");
				CertFreeCertificateContext(pCertCtxCA);
			}
			else PRINT_ERROR_AUTO(L"CertFindCertificateInStore");
			CertCloseStore(hCertStoreCA, CERT_CLOSE_STORE_FORCE_FLAG);
		}
		else PRINT_ERROR_AUTO(L"CertOpenStore");
	}

	return status;
}

void kull_m_kerberos_asn1_crypto_free_CertFromCA(PKULL_M_CRYPTO_CERT_INFO certInfo, PCRYPT_KEY_PROV_INFO keyInfo)
{
	kull_m_kerberos_asn1_crypto_free_CertInfo(certInfo);
	if(certInfo->provider.hProv)
	{
		CryptReleaseContext(certInfo->provider.hProv, 0);
		if(!CryptAcquireContext(&certInfo->provider.hProv, keyInfo->pwszContainerName, keyInfo->pwszProvName, keyInfo->dwProvType, CRYPT_DELETEKEYSET | keyInfo->dwFlags))
			PRINT_ERROR_AUTO(L"Unable to delete temp keyset");
	}
	if(keyInfo->pwszContainerName)
		LocalFree(keyInfo->pwszContainerName);
}

BOOL kull_m_kerberos_asn1_crypto_sc_auth_Ext_AltUPN(PCERT_EXTENSION pCertExtension, LPCWSTR upn)
{
	BOOL status = FALSE;
	CERT_NAME_VALUE otherNameValue = {CERT_RDN_UTF8_STRING, (DWORD) wcslen(upn) * sizeof(wchar_t), (PBYTE) upn};
	CERT_OTHER_NAME otherName = {szOID_NT_PRINCIPAL_NAME, {0, NULL}};
	CERT_ALT_NAME_ENTRY altName = {CERT_ALT_NAME_OTHER_NAME, &otherName};
	CERT_ALT_NAME_INFO AltName = {1, &altName};
	pCertExtension->pszObjId = szOID_SUBJECT_ALT_NAME2;
	pCertExtension->fCritical = FALSE;
	if(kull_m_kerberos_asn1_crypto_genericEncode(X509_UNICODE_ANY_STRING, &otherNameValue, &otherName.Value.pbData, &otherName.Value.cbData))
	{
		status = kull_m_kerberos_asn1_crypto_genericEncode(pCertExtension->pszObjId, &AltName, &pCertExtension->Value.pbData, &pCertExtension->Value.cbData);
		LocalFree(otherName.Value.pbData);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_crypto_sc_auth_Ext_KU(PCERT_EXTENSION pCertExtension, WORD bits)
{
	CRYPT_BIT_BLOB bit = {sizeof(bits), (PBYTE) &bits, 5};
	pCertExtension->pszObjId = szOID_KEY_USAGE;
	pCertExtension->fCritical = TRUE;
	return kull_m_kerberos_asn1_crypto_genericEncode(pCertExtension->pszObjId, &bit, &pCertExtension->Value.pbData, &pCertExtension->Value.cbData);
}

BOOL kull_m_kerberos_asn1_crypto_sc_auth_Ext_EKU(PCERT_EXTENSION pCertExtension, DWORD count, ...)
{
	BOOL status = FALSE;
	DWORD i;
	va_list vaList;
	CERT_ENHKEY_USAGE usage = {count, NULL};
	pCertExtension->pszObjId = szOID_ENHANCED_KEY_USAGE;
	pCertExtension->fCritical = FALSE;
	if(usage.rgpszUsageIdentifier = (LPSTR *) LocalAlloc(LPTR, sizeof(LPSTR) * count))
	{
		va_start(vaList, count); 
		for(i = 0; i < count; i++)
			usage.rgpszUsageIdentifier[i] =  va_arg(vaList, LPSTR);
		va_end(vaList);
		status = kull_m_kerberos_asn1_crypto_genericEncode(pCertExtension->pszObjId, &usage, &pCertExtension->Value.pbData, &pCertExtension->Value.cbData);
		LocalFree(usage.rgpszUsageIdentifier);
	}
	return status;
}

__inline void kull_m_kerberos_asn1_crypto_sc_auth_Ext_Free(PCERT_EXTENSION pCertExtension)
{
	if(pCertExtension->Value.pbData)
		LocalFree(pCertExtension->Value.pbData);
}

const KULL_M_KERBEROS_ASN1_CRYPTO_DUAL_STRING_DWORD kull_m_kerberos_asn1_crypto_system_stores[] = {
	{L"CERT_SYSTEM_STORE_CURRENT_USER",					CERT_SYSTEM_STORE_CURRENT_USER},
	{L"CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY",	CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY},
	{L"CERT_SYSTEM_STORE_LOCAL_MACHINE",				CERT_SYSTEM_STORE_LOCAL_MACHINE},
	{L"CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY",	CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY},
	{L"CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE",		CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE},
	{L"CERT_SYSTEM_STORE_CURRENT_SERVICE",				CERT_SYSTEM_STORE_CURRENT_SERVICE},
	{L"CERT_SYSTEM_STORE_USERS",						CERT_SYSTEM_STORE_USERS},
	{L"CERT_SYSTEM_STORE_SERVICES",						CERT_SYSTEM_STORE_SERVICES},
};

DWORD kull_m_kerberos_asn1_crypto_system_store_to_dword(PCWSTR name)
{
	DWORD i;
	if(name)
		for(i = 0; i < ARRAYSIZE(kull_m_kerberos_asn1_crypto_system_stores); i++)
			if((_wcsicmp(name, kull_m_kerberos_asn1_crypto_system_stores[i].name) == 0) || (_wcsicmp(name, kull_m_kerberos_asn1_crypto_system_stores[i].name + 18) == 0))
				return kull_m_kerberos_asn1_crypto_system_stores[i].id;
	return 0;
}

PCWCHAR kull_m_kerberos_asn1_crypto_etype(LONG eType)
{
	PCWCHAR type;
	switch(eType)
	{
	case KERB_ETYPE_NULL:							type = L"null             "; break;
	case KERB_ETYPE_DES_PLAIN:						type = L"des_plain        "; break;
	case KERB_ETYPE_DES_CBC_CRC:					type = L"des_cbc_crc      "; break;
	case KERB_ETYPE_DES_CBC_MD4:					type = L"des_cbc_md4      "; break;
	case KERB_ETYPE_DES_CBC_MD5:					type = L"des_cbc_md5      "; break;
	case KERB_ETYPE_DES_CBC_MD5_NT:					type = L"des_cbc_md5_nt   "; break;
	case KERB_ETYPE_RC4_PLAIN:						type = L"rc4_plain        "; break;
	case KERB_ETYPE_RC4_PLAIN2:						type = L"rc4_plain2       "; break;
	case KERB_ETYPE_RC4_PLAIN_EXP:					type = L"rc4_plain_exp    "; break;
	case KERB_ETYPE_RC4_LM:							type = L"rc4_lm           "; break;
	case KERB_ETYPE_RC4_MD4:						type = L"rc4_md4          "; break;
	case KERB_ETYPE_RC4_SHA:						type = L"rc4_sha          "; break;
	case KERB_ETYPE_RC4_HMAC_NT:					type = L"rc4_hmac_nt      "; break;
	case KERB_ETYPE_RC4_HMAC_NT_EXP:				type = L"rc4_hmac_nt_exp  "; break;
	case KERB_ETYPE_RC4_PLAIN_OLD:					type = L"rc4_plain_old    "; break;
	case KERB_ETYPE_RC4_PLAIN_OLD_EXP:				type = L"rc4_plain_old_exp"; break;
	case KERB_ETYPE_RC4_HMAC_OLD:					type = L"rc4_hmac_old     "; break;
	case KERB_ETYPE_RC4_HMAC_OLD_EXP:				type = L"rc4_hmac_old_exp "; break;
	case KERB_ETYPE_AES128_CTS_HMAC_SHA1_96_PLAIN:	type = L"aes128_hmac_plain"; break;
	case KERB_ETYPE_AES256_CTS_HMAC_SHA1_96_PLAIN:	type = L"aes256_hmac_plain"; break;
	case KERB_ETYPE_AES128_CTS_HMAC_SHA1_96:		type = L"aes128_hmac      "; break;
	case KERB_ETYPE_AES256_CTS_HMAC_SHA1_96:		type = L"aes256_hmac      "; break;
	default:										type = L"unknow           "; break;
	}
	return type;
}

PCWCHAR kull_m_kerberos_asn1_crypto_ctype(LONG cType)
{
	PCWCHAR type;
	switch(cType)
	{
	case KERB_CHECKSUM_NONE:					type = L"none               "; break;
	case KERB_CHECKSUM_CRC32:					type = L"crc32              "; break;
	case KERB_CHECKSUM_MD4:						type = L"md4                "; break;
	case KERB_CHECKSUM_KRB_DES_MAC:				type = L"krb_des_mac        "; break;
	case KERB_CHECKSUM_KRB_DES_MAC_K:			type = L"krb_des_mac_k      "; break;
	case KERB_CHECKSUM_MD5:						type = L"md5                "; break;
	case KERB_CHECKSUM_MD5_DES:					type = L"md5_des            "; break;
	case KERB_CHECKSUM_SHA1_NEW:				type = L"sha1_new           "; break;
	case KERB_CHECKSUM_HMAC_SHA1_96_AES128:		type = L"hmac_sha1_aes128   "; break;
	case KERB_CHECKSUM_HMAC_SHA1_96_AES256:		type = L"hmac_sha1_aes256   "; break;
	case KERB_CHECKSUM_LM:						type = L"lm                 "; break;
	case KERB_CHECKSUM_SHA1:					type = L"sha1               "; break;
	case KERB_CHECKSUM_REAL_CRC32:				type = L"real_crc32         "; break;
	case KERB_CHECKSUM_DES_MAC:					type = L"dec_mac            "; break;
	case KERB_CHECKSUM_DES_MAC_MD5:				type = L"dec_mac_md5        "; break;
	case KERB_CHECKSUM_MD25:					type = L"md25               "; break;
	case KERB_CHECKSUM_RC4_MD5:					type = L"rc4_md5            "; break;
	case KERB_CHECKSUM_MD5_HMAC:				type = L"md5_hmac           "; break;
	case KERB_CHECKSUM_HMAC_MD5:				type = L"hmac_md5           "; break;
	case KERB_CHECKSUM_HMAC_SHA1_96_AES128_Ki:	type = L"hmac_sha1_aes128_ki"; break;
	case KERB_CHECKSUM_HMAC_SHA1_96_AES256_Ki:	type = L"hmac_sha1_aes256_ki"; break;
	default:									type = L"unknow             "; break;
	}
	return type;
}