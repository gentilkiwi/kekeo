/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "kull_m_crypto_pkinit.h"

BOOL kull_m_crypto_get_CertInfo(PCSTR Subject, PKULL_M_CRYPTO_CERT_INFO certInfo)
{
	BOOL status = FALSE, keyToFree;
	RtlZeroMemory(certInfo, sizeof(KULL_M_CRYPTO_CERT_INFO));
	if(certInfo->hCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, (HCRYPTPROV_LEGACY) NULL, CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG, L"My"))
		if(certInfo->pCertContext = CertFindCertificateInStore(certInfo->hCertStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_SUBJECT_STR_A, Subject, NULL))
			status = CryptAcquireCertificatePrivateKey(certInfo->pCertContext, CRYPT_ACQUIRE_CACHE_FLAG, NULL, &certInfo->provider.hProv, &certInfo->provider.dwKeySpec, &keyToFree);
	
	if(!status)
		kull_m_crypto_free_CertInfo(certInfo);
	return status;
}

void kull_m_crypto_free_CertInfo(PKULL_M_CRYPTO_CERT_INFO certInfo)
{
	if(certInfo->pCertContext)
		CertFreeCertificateContext(certInfo->pCertContext);
	if(certInfo->hCertStore)
		CertCloseStore(certInfo->hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
}

BOOL kuhl_m_crypto_c_sc_auth_Ext_AltUPN(PCERT_EXTENSION pCertExtension, LPCWSTR upn)
{
	BOOL status = FALSE;
	CERT_NAME_VALUE otherNameValue = {CERT_RDN_UTF8_STRING, (DWORD) wcslen(upn) * sizeof(wchar_t), (PBYTE) upn};
	CERT_OTHER_NAME otherName = {szOID_NT_PRINCIPAL_NAME, {0, NULL}};
	CERT_ALT_NAME_ENTRY altName = {CERT_ALT_NAME_OTHER_NAME, &otherName};
	CERT_ALT_NAME_INFO AltName = {1, &altName};
	pCertExtension->pszObjId = szOID_SUBJECT_ALT_NAME2;
	pCertExtension->fCritical = FALSE;
	if(kull_m_crypto_genericEncode(X509_UNICODE_ANY_STRING, &otherNameValue, &otherName.Value.pbData, &otherName.Value.cbData))
	{
		status = kull_m_crypto_genericEncode(pCertExtension->pszObjId, &AltName, &pCertExtension->Value.pbData, &pCertExtension->Value.cbData);
		LocalFree(otherName.Value.pbData);
	}
	return status;
}

BOOL kuhl_m_crypto_c_sc_auth_Ext_KU(PCERT_EXTENSION pCertExtension, WORD bits)
{
	CRYPT_BIT_BLOB bit = {sizeof(bits), (PBYTE) &bits, 5};
	pCertExtension->pszObjId = szOID_KEY_USAGE;
	pCertExtension->fCritical = TRUE;
	return kull_m_crypto_genericEncode(pCertExtension->pszObjId, &bit, &pCertExtension->Value.pbData, &pCertExtension->Value.cbData);
}

BOOL kuhl_m_crypto_c_sc_auth_Ext_EKU(PCERT_EXTENSION pCertExtension, DWORD count, ...)
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
		status = kull_m_crypto_genericEncode(pCertExtension->pszObjId, &usage, &pCertExtension->Value.pbData, &pCertExtension->Value.cbData);
		LocalFree(usage.rgpszUsageIdentifier);
	}
	return status;
}

__inline void kuhl_m_crypto_c_sc_auth_Ext_Free(PCERT_EXTENSION pCertExtension)
{
	if(pCertExtension->Value.pbData)
		LocalFree(pCertExtension->Value.pbData);
}

BOOL kull_m_crypto_get_CertFromCA(PCSTR sNameCA, PCSTR sStoreCA, PCSTR sUPN, PKULL_M_CRYPTO_CERT_INFO certInfo, PCRYPT_KEY_PROV_INFO keyInfo)
{
	BOOL status = FALSE;
	PWSTR szNameCA, szStoreCA, szUPN;
	HCERTSTORE hCertStoreCA;
	PCCERT_CONTEXT pCertCtxCA;
	HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hKeyCA;
	DWORD dwKeySpecCA;
	BOOL bToFreeCA;
	HCRYPTKEY hKeyCERT;
	BYTE SerialNumber[LM_NTLM_HASH_LENGTH];
	CERT_RDN_ATTR rgNameAttr[] = {
		{szOID_COMMON_NAME, CERT_RDN_UNICODE_STRING, {0, NULL}},
		{szOID_ORGANIZATION_NAME, CERT_RDN_UNICODE_STRING, {10, (PBYTE) L"kekeo"}},
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
	if(szNameCA = kull_m_string_qad_ansi_to_unicode(sNameCA))
	{
		if(szStoreCA = kull_m_string_qad_ansi_to_unicode(sStoreCA))
		{
			if(szUPN = kull_m_string_qad_ansi_to_unicode(sUPN))
			{
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

					rgNameAttr[0].Value.cbData = (DWORD) wcslen(szUPN) * sizeof(wchar_t);
					rgNameAttr[0].Value.pbData = (PBYTE) szUPN;
					kprintf("CA store           : %s\n", sStoreCA);
					if(hCertStoreCA = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, (HCRYPTPROV_LEGACY) NULL, kull_m_crypto_system_store_to_dword(szStoreCA) | CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG, L"My"))
					{
						kprintf("CA name            : %s\n", sNameCA);
						if(pCertCtxCA = CertFindCertificateInStore(hCertStoreCA, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_SUBJECT_STR, szNameCA, NULL))
						{
							kprintf("CA validity        : "); kull_m_string_displayLocalFileTime(&pCertCtxCA->pCertInfo->NotBefore);
							kprintf(" -> "); kull_m_string_displayLocalFileTime(&pCertCtxCA->pCertInfo->NotAfter); kprintf("\n");
							if(CryptAcquireCertificatePrivateKey(pCertCtxCA, CRYPT_ACQUIRE_CACHE_FLAG | CRYPT_ACQUIRE_ALLOW_NCRYPT_KEY_FLAG, NULL, &hKeyCA, &dwKeySpecCA, &bToFreeCA))
							{
								CertInfo.Issuer = pCertCtxCA->pCertInfo->Subject;
								CertInfo.IssuerUniqueId = pCertCtxCA->pCertInfo->SubjectUniqueId;
								CertInfo.NotBefore = pCertCtxCA->pCertInfo->NotBefore;
								CertInfo.NotAfter = pCertCtxCA->pCertInfo->NotAfter;
								CertInfo.SignatureAlgorithm = pCertCtxCA->pCertInfo->SignatureAlgorithm;
								kprintf("Certificate UPN    : %s\n", sUPN);
								if(kull_m_crypto_genericEncode(X509_NAME, &Name, &CertInfo.Subject.pbData, &CertInfo.Subject.cbData))
								{
									if(kuhl_m_crypto_c_sc_auth_Ext_EKU(&Extensions[0], 2, szOID_KP_SMARTCARD_LOGON, szOID_PKIX_KP_CLIENT_AUTH))
									{
										if(kuhl_m_crypto_c_sc_auth_Ext_KU(&Extensions[1], CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE))
										{
											if(kuhl_m_crypto_c_sc_auth_Ext_AltUPN(&Extensions[2], szUPN))
											{
												kprintf("Key container      : %S\n", keyInfo->pwszContainerName);
												kprintf("Key provider       : %S\n", keyInfo->pwszProvName);
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
																							PRINT_ERROR_AUTO("CertSetCertificateContextProperty(CERT_KEY_PROV_INFO_PROP_ID)");
																					}
																				}
																			}
																			else PRINT_ERROR_AUTO("CryptSignAndEncodeCertificate (data)");
																			LocalFree(Certificate);
																		}
																	}
																	else PRINT_ERROR_AUTO("CryptSignAndEncodeCertificate (init)");
																}
																else PRINT_ERROR_AUTO("CryptExportPublicKeyInfo (data)");
																LocalFree(pbPublicKeyInfo);
															}
														}
														else PRINT_ERROR_AUTO("CryptExportPublicKeyInfo (init)");
														CryptDestroyKey(hKeyCERT);
													}
													else PRINT_ERROR_AUTO("CryptGenKey");
												}
												else PRINT_ERROR_AUTO("CryptAcquireContext");
												kuhl_m_crypto_c_sc_auth_Ext_Free(&Extensions[2]);
											}
											kuhl_m_crypto_c_sc_auth_Ext_Free(&Extensions[1]);
										}
										kuhl_m_crypto_c_sc_auth_Ext_Free(&Extensions[0]);
									}
									LocalFree(CertInfo.Subject.pbData);
								}
								CryptReleaseContext(hKeyCA, 0);
							}
							else PRINT_ERROR_AUTO("CryptAcquireCertificatePrivateKey");
							CertFreeCertificateContext(pCertCtxCA);
						}
						else PRINT_ERROR_AUTO("CertFindCertificateInStore");
						CertCloseStore(hCertStoreCA, CERT_CLOSE_STORE_FORCE_FLAG);
					}
					else PRINT_ERROR_AUTO("CertOpenStore");
				}
				LocalFree(szUPN);
			}
			LocalFree(szStoreCA);
		}
		LocalFree(szNameCA);
	}
	return status;
}

void kull_m_crypto_free_CertFromCA(PKULL_M_CRYPTO_CERT_INFO certInfo, PCRYPT_KEY_PROV_INFO keyInfo)
{
	kull_m_crypto_free_CertInfo(certInfo);
	if(certInfo->provider.hProv)
	{
		CryptReleaseContext(certInfo->provider.hProv, 0);
	if(!CryptAcquireContextW(&certInfo->provider.hProv, keyInfo->pwszContainerName, keyInfo->pwszProvName, keyInfo->dwProvType, CRYPT_DELETEKEYSET | keyInfo->dwFlags))
		PRINT_ERROR_AUTO("Unable to delete temp keyset");
	}
	if(keyInfo->pwszContainerName)
		LocalFree(keyInfo->pwszContainerName);
}

BOOL kull_m_crypto_simple_message_sign(PKULL_M_CRYPTO_CERT_INFO certInfo, OssBuf *input, _octet1 *output)
{
	BOOL status = FALSE;
	HCRYPTMSG hCryptMsg;
	CERT_BLOB Certificate = {certInfo->pCertContext->cbCertEncoded, certInfo->pCertContext->pbCertEncoded};
	CMSG_SIGNER_ENCODE_INFO Signers = {sizeof(CMSG_SIGNER_ENCODE_INFO), certInfo->pCertContext->pCertInfo, certInfo->provider.hProv, certInfo->provider.dwKeySpec, {szOID_OIWSEC_sha1, 0, NULL}, NULL, 0, NULL, 0, NULL};
	CMSG_SIGNED_ENCODE_INFO MsgEncodeInfo = {sizeof(CMSG_SIGNED_ENCODE_INFO), 1, &Signers, 1, &Certificate, 0, NULL};
	output->length = 0;
	output->value = NULL;

	if(hCryptMsg = CryptMsgOpenToEncode(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, CMSG_CMS_ENCAPSULATED_CONTENT_FLAG, CMSG_SIGNED, &MsgEncodeInfo, "1.3.6.1.5.2.3.1", NULL))
	{
		if(CryptMsgUpdate(hCryptMsg, input->value, input->length, TRUE))
		{
			if(CryptMsgGetParam(hCryptMsg, CMSG_CONTENT_PARAM, 0, NULL, (PDWORD) &output->length))
			{
				if(output->value = (PBYTE) LocalAlloc(LPTR, output->length))
					if(!(status = CryptMsgGetParam(hCryptMsg, CMSG_CONTENT_PARAM, 0, output->value, (PDWORD) &output->length)))
					{
						PRINT_ERROR_AUTO("CryptMsgGetParam(CMSG_CONTENT_PARAM - data)");
						LocalFree(output->value);
					}
			}
			else PRINT_ERROR_AUTO("CryptMsgGetParam(CMSG_CONTENT_PARAM - init)");
		}
		else PRINT_ERROR_AUTO("CryptMsgUpdate");
		CryptMsgClose(hCryptMsg);
	}
	else PRINT_ERROR_AUTO("CryptMsgOpenToEncode");
	return status;
}

BOOL kull_m_crypto_simple_message_dec(PKULL_M_CRYPTO_PROV_INFO provInfo, _octet1 *input, OssBuf *output)
{
	BOOL status = FALSE;
	HCRYPTMSG hCryptMsg;
	CMSG_CTRL_DECRYPT_PARA DecryptParam = {sizeof(CMSG_CTRL_DECRYPT_PARA), provInfo->hProv, provInfo->dwKeySpec, 0};
	_octet1 buffer = {0, NULL};
	output->length = 0;
	output->value = NULL;

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
							status = kull_m_crypto_simple_message_get(&buffer, output);
						else PRINT_ERROR_AUTO("CryptMsgGetParam(CMSG_CONTENT_PARAM - data)");
						LocalFree(buffer.value);
					}
				}
				else PRINT_ERROR_AUTO("CryptMsgGetParam(CMSG_CONTENT_PARAM - init)");
			}
			else PRINT_ERROR_AUTO("CryptMsgControl(CMSG_CTRL_DECRYPT)");
		}
		else PRINT_ERROR_AUTO("CryptMsgUpdate");
		CryptMsgClose(hCryptMsg);
	}
	else PRINT_ERROR_AUTO("CryptMsgOpenToEncode");
	return status;
}

BOOL kull_m_crypto_simple_message_get(_octet1 *input, OssBuf *output)
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
						PRINT_ERROR_AUTO("CryptMsgGetParam(CMSG_CONTENT_PARAM - data)");
						LocalFree(output->value);
					}
			}
			else PRINT_ERROR_AUTO("CryptMsgGetParam(CMSG_CONTENT_PARAM - init)");
		}
		else PRINT_ERROR_AUTO("CryptMsgUpdate");
		CryptMsgClose(hCryptMsg2);
	}
	else PRINT_ERROR_AUTO("CryptMsgOpenToEncode");
	return status;
}

const BYTE g_rgbPrime[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x53, 0xe6, 0xec, 0x51, 0x66, 0x28, 0x49,
	0xe6, 0x1f, 0x4b, 0x7c, 0x11, 0x24, 0x9f, 0xae, 0xa5, 0x9f, 0x89, 0x5a, 0xfb, 0x6b, 0x38, 0xee,
	0xed, 0xb7, 0x06, 0xf4, 0xb6, 0x5c, 0xff, 0x0b, 0x6b, 0xed, 0x37, 0xa6, 0xe9, 0x42, 0x4c, 0xf4,
	0xc6, 0x7e, 0x5e, 0x62, 0x76, 0xb5, 0x85, 0xe4, 0x45, 0xc2, 0x51, 0x6d, 0x6d, 0x35, 0xe1, 0x4f,
	0x37, 0x14, 0x5f, 0xf2, 0x6d, 0x0a, 0x2b, 0x30, 0x1b, 0x43, 0x3a, 0xcd, 0xb3, 0x19, 0x95, 0xef,
	0xdd, 0x04, 0x34, 0x8e, 0x79, 0x08, 0x4a, 0x51, 0x22, 0x9b, 0x13, 0x3b, 0xa6, 0xbe, 0x0b, 0x02,
	0x74, 0xcc, 0x67, 0x8a, 0x08, 0x4e, 0x02, 0x29, 0xd1, 0x1c, 0xdc, 0x80, 0x8b, 0x62, 0xc6, 0xc4,
	0x34, 0xc2, 0x68, 0x21, 0xa2, 0xda, 0x0f, 0xc9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

const BYTE g_rgbGenerator[] = {
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const CERT_X942_DH_PARAMETERS dhGlobParameters = {
		{sizeof(g_rgbPrime), (PBYTE) g_rgbPrime},
		{sizeof(g_rgbGenerator), (PBYTE) g_rgbGenerator},
		{0, NULL},
		{0, NULL},
		NULL
};

const BYTE goodDhKey[] = {
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

BOOL kull_m_crypto_get_DHKeyInfo(BOOL integrated, BOOL withNonce, PKULL_M_CRYPTO_DH_KEY_INFO keyInfo)
{
	BOOL status = FALSE;

	RtlZeroMemory(keyInfo, sizeof(KULL_M_CRYPTO_DH_KEY_INFO));
	if(CryptAcquireContext(&keyInfo->hProv, NULL, MS_ENH_DSS_DH_PROV, PROV_DSS_DH, CRYPT_VERIFYCONTEXT))
	{
		((PDWORD) (((PULONG_PTR) keyInfo->hProv)[28] ^ 0xa2491d83))[5] = 1; // :)
		if(integrated)
		{
			if(CryptImportKey(keyInfo->hProv, goodDhKey, sizeof(goodDhKey), 0, CRYPT_EXPORTABLE, &keyInfo->hKey))
				status = CryptSetKeyParam(keyInfo->hKey, KP_Q, (PBYTE) &dhGlobParameters.q, 0);
		}
		else
		{
			if(CryptGenKey(keyInfo->hProv, CALG_DH_EPHEM, RSA1024BIT_KEY | CRYPT_EXPORTABLE, &keyInfo->hKey))
				if(CryptSetKeyParam(keyInfo->hKey, KP_P, (PBYTE) &dhGlobParameters.p, 0))
					if(CryptSetKeyParam(keyInfo->hKey, KP_G, (PBYTE) &dhGlobParameters.g, 0))
						if(CryptSetKeyParam(keyInfo->hKey, KP_Q, (PBYTE) &dhGlobParameters.q, 0))
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
		kull_m_crypto_free_DHKeyInfo(keyInfo);
	return status;
}

void kull_m_crypto_free_DHKeyInfo(PKULL_M_CRYPTO_DH_KEY_INFO keyInfo)
{
	if(keyInfo->dhClientNonce.value)
		LocalFree(keyInfo->dhClientNonce.value);
	if(keyInfo->hKey)
		CryptDestroyKey(keyInfo->hKey);
	if(keyInfo->hProv)
		CryptReleaseContext(keyInfo->hProv, 0);
}

BOOL kull_m_crypto_get_DHKeyInfo_Parameters(HCRYPTKEY hKey, PCERT_X942_DH_PARAMETERS parameters)
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
		kull_m_crypto_free_DHKeyInfo_Parameters(parameters);
	return status;
}

void kull_m_crypto_free_DHKeyInfo_Parameters(PCERT_X942_DH_PARAMETERS parameters)
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

void k_truncate(PVOID input, DWORD cbInput, PVOID output, DWORD cbOutput)
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

BOOL octetstring2key(PVOID input, DWORD cbInput, DHNonce *client, DHNonce *server, EncryptionKey *ekey)
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
				k_truncate(iBuffer, iCbBuffer, oBuffer, pCSystem->KeySize);
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

BOOL kull_m_crypto_genericEncode(__in LPCSTR lpszStructType, __in const void *pvStructInfo, __inout PBYTE *pvEncoded, __inout DWORD *pcbEncoded)
{
	BOOL status = FALSE;
	*pcbEncoded = 0;
	if(CryptEncodeObjectEx(X509_ASN_ENCODING, lpszStructType, pvStructInfo, 0, NULL, NULL, pcbEncoded))
		if(*pvEncoded = (PBYTE) LocalAlloc(LPTR, *pcbEncoded))
			if(!(status = CryptEncodeObjectEx(X509_ASN_ENCODING, lpszStructType, pvStructInfo, 0, NULL, *pvEncoded, pcbEncoded)))
				LocalFree(*pvEncoded);
	return status;
}

BOOL kull_m_crypto_genericDecode(__in LPCSTR lpszStructType,  __in_bcount(cbEncoded) const BYTE *pbEncoded, __in DWORD cbEncoded, __out void **ppvStructInfo)
{
	BOOL status = FALSE;
	DWORD szNeeded = 0;
	if(CryptDecodeObjectEx(X509_ASN_ENCODING, lpszStructType, pbEncoded, cbEncoded, 0, NULL, NULL, &szNeeded))
		if(*ppvStructInfo = LocalAlloc(LPTR, szNeeded))
			if(!(status = CryptDecodeObjectEx(X509_ASN_ENCODING, lpszStructType, pbEncoded, cbEncoded, 0, NULL, *ppvStructInfo, &szNeeded)))
				LocalFree(*ppvStructInfo);
	return status;
}


const KULL_M_CRYPTO_DUAL_STRING_DWORD kull_m_crypto_system_stores[] = {
	{L"CERT_SYSTEM_STORE_CURRENT_USER",					CERT_SYSTEM_STORE_CURRENT_USER},
	{L"CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY",	CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY},
	{L"CERT_SYSTEM_STORE_LOCAL_MACHINE",				CERT_SYSTEM_STORE_LOCAL_MACHINE},
	{L"CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY",	CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY},
	{L"CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE",		CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE},
	{L"CERT_SYSTEM_STORE_CURRENT_SERVICE",				CERT_SYSTEM_STORE_CURRENT_SERVICE},
	{L"CERT_SYSTEM_STORE_USERS",						CERT_SYSTEM_STORE_USERS},
	{L"CERT_SYSTEM_STORE_SERVICES",						CERT_SYSTEM_STORE_SERVICES},
};

DWORD kull_m_crypto_system_store_to_dword(PCWSTR name)
{
	DWORD i;
	if(name)
		for(i = 0; i < ARRAYSIZE(kull_m_crypto_system_stores); i++)
			if((_wcsicmp(name, kull_m_crypto_system_stores[i].name) == 0) || (_wcsicmp(name, kull_m_crypto_system_stores[i].name + 18) == 0))
				return kull_m_crypto_system_stores[i].id;
	return 0;
}