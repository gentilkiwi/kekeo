/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kull_m_kerberos_asn1.h"

#if _MSC_VER >= 1900
#pragma comment(lib, "legacy_stdio_definitions.lib")
//#pragma comment(lib, "legacy_stdio_wide_specifiers.lib")
FILE __iob_func_data[3];
_CRTIMP FILE * __cdecl __iob_func(void)
{
	__iob_func_data[0] = *__acrt_iob_func(0);
	__iob_func_data[1] = *__acrt_iob_func(1);
	__iob_func_data[2] = *__acrt_iob_func(2);
	return __iob_func_data;
}
#endif

OssGlobal kull_m_kerberos_asn1_world;
BOOL kull_m_kerberos_asn1_isInit = FALSE;

BOOL kull_m_kerberos_asn1_init()
{
	int OssStatus = ossinit(&kull_m_kerberos_asn1_world, kekeo_asn1);
	if(!(kull_m_kerberos_asn1_isInit = !OssStatus))
		PRINT_ERROR(L"ossinit: %i\n", OssStatus);
	return kull_m_kerberos_asn1_isInit;
}

void kull_m_kerberos_asn1_term()
{
	if(kull_m_kerberos_asn1_isInit)
	{
		ossterm(&kull_m_kerberos_asn1_world);
		kull_m_kerberos_asn1_isInit = FALSE;
	}
}

void kull_m_kerberos_asn1_PrincipalName_create(PrincipalName *principal_name, Int32 name_type, DWORD count, ...)
{
	DWORD i;
	va_list vaList;
	if(principal_name)
	{
		RtlZeroMemory(principal_name, sizeof(PrincipalName));
		va_start(vaList, count); 
		principal_name->name_type = name_type;
		if(principal_name->name_string = (struct _seqof1 *) LocalAlloc(LPTR, sizeof(struct _seqof1) * count))
		{
			for(i = 0; i < count; i++)
			{
				kull_m_string_copyA(&principal_name->name_string[i].value, va_arg(vaList, char *));
				principal_name->name_string[i].next = (i + 1 < count) ? &principal_name->name_string[i + 1] : NULL;
			}
		}
		va_end(vaList);
	}
}

void kull_m_kerberos_asn1_PrincipalName_create_fromName(PrincipalName *principal_name, Realm *pRealm, LPCWSTR name)
{
	DWORD count = 0, i;
	char *dupName, *nextToken, *token;
	LPSTR aName;
	if(principal_name && name)
	{
		if(aName = kull_m_string_unicode_to_ansi(name))
		{
			RtlZeroMemory(principal_name, sizeof(PrincipalName));
			if(strchr(aName, '/'))
			{
				if(pRealm)
				{
					if(nextToken = strrchr(aName, '@'))
					{
						if(*(nextToken + 1))
						{
							*nextToken = '\0';
							*pRealm = _strdup(nextToken + 1);
						}
					}
				}
				if(dupName = _strdup(aName))
				{
					for(nextToken = NULL, token = strtok_s(dupName, "/", &nextToken); token; token = strtok_s(NULL, "/", &nextToken))
						count++;
					free(dupName);

					if(count)
					{
						if(dupName = _strdup(aName))
						{
							principal_name->name_type = KRB_NT_SRV_INST;
							if(principal_name->name_string = (struct _seqof1 *) LocalAlloc(LPTR, sizeof(struct _seqof1) * count))
							{
								for(nextToken = NULL, token = strtok_s(dupName, "/", &nextToken), i = 0; token; token = strtok_s(NULL, "/", &nextToken), i++)
								{
									kull_m_string_copyA(&principal_name->name_string[i].value, token);
									principal_name->name_string[i].next = (i + 1 < count) ? &principal_name->name_string[i + 1] : NULL;
								}
							}
							free(dupName);
						}
					}
				}
			}
			else
			{
				if(strchr(aName, '\\'))
					principal_name->name_type = KRB_NT_MS_PRINCIPAL;
				else if(strchr(aName, '@'))
					principal_name->name_type = KRB_NT_ENTERPRISE_PRINCIPAL;
				else
					principal_name->name_type = KRB_NT_PRINCIPAL;

				if(principal_name->name_string = (struct _seqof1 *) LocalAlloc(LPTR, sizeof(struct _seqof1)))
					kull_m_string_copyA(&principal_name->name_string->value, aName);
			}
			LocalFree(aName);
		}
	}
}

void kull_m_kerberos_asn1_PrincipalName_delete(PrincipalName *principal_name)
{
	struct _seqof1 *names;
	if(principal_name)
	{
		for(names = principal_name->name_string; names; names = names->next)
			if(names->value)
				LocalFree(names->value);
		if(principal_name->name_string)
			LocalFree(principal_name->name_string);
	}
}

void kull_m_kerberos_asn1_PrincipalName_descr(PrincipalName *principal_name, BOOL withType)
{
	PCWCHAR type;
	struct _seqof1 *names;
	DWORD j;
	if(principal_name)
	{
		for(names = principal_name->name_string, j = 0; names; names = names->next, j++)
		{
			kprintf(L"%S", names->value);
			if(names->next)
				kprintf(L"/");
		}
		if(withType)
		{
			switch(principal_name->name_type)
			{
			case KRB_NT_PRINCIPAL:
				type = L"KRB_NT_PRINCIPAL";
				break;
			case KRB_NT_SRV_INST:
				type = L"KRB_NT_SRV_INST";
				break;
			case KRB_NT_ENTERPRISE_PRINCIPAL:
				type = L"KRB_NT_ENTERPRISE_PRINCIPAL";
				break;
			case KRB_NT_MS_PRINCIPAL:
				type = L"KRB_NT_MS_PRINCIPAL";
				break;
			default:
				type = L"?";
			}
			kprintf(L"\t[%s (%i)]", type, principal_name->name_type);
		}
	}
}

const KerberosTime MAX_MS_2037_GT = {2037, 9, 13, 2, 48, 5, 0, 0, TRUE};
void kull_m_kerberos_asn1_KerberosTime_build_systemtime(KerberosTime *time, PSYSTEMTIME pSystemTime, BOOL isMaxMs2037)
{
	SYSTEMTIME systemTime;
	if(isMaxMs2037)
	{
		*time = MAX_MS_2037_GT;
	}
	else
	{
		if(pSystemTime)
			systemTime = *pSystemTime;
		else
			GetSystemTime(&systemTime);

		time->year = systemTime.wYear;
		time->month = systemTime.wMonth;
		time->day = systemTime.wDay;
		time->hour = systemTime.wHour;
		time->minute = systemTime.wMinute;
		time->second = systemTime.wSecond;
		time->millisec = 0;
		time->mindiff = 0;
		time->utc = TRUE;
	}
}

void kull_m_kerberos_asn1_KerberosTime_build_filetime(KerberosTime *time, PFILETIME pFileTime, BOOL isMaxMs2037)
{
	SYSTEMTIME systemTime;
	BOOL isPtr = FALSE;
	if(!isMaxMs2037 && pFileTime)
		isPtr = FileTimeToSystemTime(pFileTime, &systemTime);
	kull_m_kerberos_asn1_KerberosTime_build_systemtime(time, isPtr ? &systemTime : NULL, isMaxMs2037);
}

void kull_m_kerberos_asn1_KerberosTime_build_time_t(KerberosTime *time, time_t uTime)
{
	FILETIME fileTime;
	*(PLONGLONG) &fileTime = Int32x32To64(uTime, 10000000) + 116444736000000000;
	kull_m_kerberos_asn1_KerberosTime_build_filetime(time, &fileTime, FALSE);
}

void kull_m_kerberos_asn1_KerberosTime_to_systemtime(KerberosTime *time, PSYSTEMTIME pSystemTime)
{
	pSystemTime->wYear = time->year;
	pSystemTime->wMonth = time->month;
	pSystemTime->wDay = time->day;
	pSystemTime->wHour = time->hour;
	pSystemTime->wMinute = time->minute;
	pSystemTime->wSecond = time->second;
	pSystemTime->wMilliseconds = time->millisec;
	pSystemTime->wDayOfWeek = 0;
}

void kull_m_kerberos_asn1_KerberosTime_to_filetime(KerberosTime *time, PFILETIME pFileTime)
{
	SYSTEMTIME systemTime;
	kull_m_kerberos_asn1_KerberosTime_to_systemtime(time, &systemTime);
	SystemTimeToFileTime(&systemTime, pFileTime);
}

void kull_m_kerberos_asn1_KerberosTime_to_time_t(KerberosTime *time, time_t * uTime)
{
	FILETIME fileTime;
	kull_m_kerberos_asn1_KerberosTime_to_filetime(time, &fileTime);
	*uTime = (time_t) (*(PLONGLONG) &fileTime - 116444736000000000) / 10000000; 
}

void kull_m_kerberos_asn1_KerberosTime_print(KerberosTime *time)
{
	FILETIME ft;
	kull_m_kerberos_asn1_KerberosTime_to_filetime(time, &ft);
	kull_m_string_displayLocalFileTime(&ft);
}

const struct _seqof2	suppEtypeRC4 = {NULL, KERB_ETYPE_RC4_HMAC_NT},
						suppEtypeAES128 = {(struct _seqof2 *) &suppEtypeRC4, KERB_ETYPE_AES128_CTS_HMAC_SHA1_96},
						suppEtypeAES256 = {(struct _seqof2 *) &suppEtypeAES128, KERB_ETYPE_AES256_CTS_HMAC_SHA1_96};
void kull_m_kerberos_asn1_KdcReqBody_build(KDC_REQ_BODY *body, PrincipalName *cname, Realm realm, PrincipalName *sname, DWORD Options, struct _seqof2 *suppEtype)
{
	RtlZeroMemory(body, sizeof(KDC_REQ_BODY));
	body->kdc_options.length = sizeof(DWORD) * 8;
	body->kdc_options.value = (unsigned char *) LocalAlloc(LPTR, sizeof(DWORD));
	if(!Options)
		Options = KERB_KDCOPTION_standard;
	*(PDWORD) body->kdc_options.value = _byteswap_ulong(Options);

	if(cname)
	{
		body->cname = *cname;
		body->bit_mask |= KDC_REQ_BODY_cname_present;
	}
	body->realm = realm;
	if(sname)
	{
		body->sname = *sname;
		body->bit_mask |= KDC_REQ_BODY_sname_present;
	}
	kull_m_kerberos_asn1_KerberosTime_build_systemtime(&body->till, NULL, TRUE);
	body->nonce = MIMIKATZ_NONCE;
	body->etype = suppEtype ? suppEtype : (struct _seqof2 *) ((MIMIKATZ_NT_MAJOR_VERSION < 6) ? &suppEtypeRC4 : &suppEtypeAES256);
}

void kull_m_kerberos_asn1_KdcReqBody_free(KDC_REQ_BODY *body)
{
	if(body->enc_authorization_data.cipher.value)
		body->enc_authorization_data.cipher.value = (unsigned char *) LocalFree(body->enc_authorization_data.cipher.value);
	if(body->kdc_options.value)
		body->kdc_options.value = (unsigned char *) LocalFree(body->kdc_options.value);
}

BOOL kull_m_kerberos_asn1_AsReqAsRep(PKIWI_AUTH_INFOS authinfos, PKULL_M_SOCK fullsocket, KerberosTime *time, PrincipalName *altService, AS_REP **AsRep, EncKDCRepPart **encAsRepPart, EncryptionKey *replyKey)
{
	BOOL status = FALSE;
	OssBuf AsReq = {0, NULL};
	
	*AsRep = NULL;
	*encAsRepPart = NULL;
	if(kull_m_kerberos_asn1_AsReq_build(authinfos, time, altService, &AsReq))
	{
		if(kull_m_kerberos_asn1_net_callKdcOssBuf(fullsocket, &AsReq, (LPVOID *) AsRep, AS_REP_PDU))
		{
			if(!(status = kull_m_kerberos_asn1_EncKDCRepPart_from_AsRep_build(authinfos, *AsRep, encAsRepPart, replyKey)))
				ossFreePDU(&kull_m_kerberos_asn1_world, AS_REP_PDU, *AsRep);
		}
		ossFreeBuf(&kull_m_kerberos_asn1_world, AsReq.value);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_AsReq_build(PKIWI_AUTH_INFOS authinfos, KerberosTime *time, PrincipalName *altService, OssBuf *OutKdcReq)
{
	BOOL status = FALSE, goodPa = FALSE;
	AS_REQ asreq = {0};
	PrincipalName sname = {0};
	PA_DATA PaGeneric = {0}, PaPacRequest = {0};

	RtlZeroMemory(OutKdcReq, sizeof(OssBuf));
	if(authinfos->type != KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH)
	{
		asreq.pvno = 5;
		asreq.msg_type = 10;
		asreq.bit_mask = KDC_REQ_padata_present;

		kull_m_kerberos_asn1_PrincipalName_create(&sname, KRB_NT_SRV_INST, 2, "krbtgt", authinfos->realm); // maybe to move in kull_m_kerberos_asn1_PA_DATA_PA_PK_AS_REQ_old_build
		kull_m_kerberos_asn1_KdcReqBody_build(&asreq.req_body, &authinfos->cname, authinfos->realm, &authinfos->sname, 0, NULL);
		if(kull_m_kerberos_asn1_PA_DATA_PacRequest_build(&PaPacRequest, authinfos->needPac))
		{
			switch(authinfos->type)
			{
			case KIWI_AUTH_INFOS_TYPE_KEY:
				goodPa = kull_m_kerberos_asn1_PA_DATA_encTimeStamp_build(&PaGeneric, time, &authinfos->u.ekey);
				break;
			case KIWI_AUTH_INFOS_TYPE_RSA:
			case KIWI_AUTH_INFOS_TYPE_OTF_RSA:
				goodPa = kull_m_kerberos_asn1_PA_DATA_PA_PK_AS_REQ_old_build(&PaGeneric, &sname, authinfos->realm, time, &authinfos->u.certinfos);
				break;
			case KIWI_AUTH_INFOS_TYPE_RSA_DH:
			case KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH:
				goodPa = kull_m_kerberos_asn1_PA_DATA_PA_PK_AS_REQ_build(&PaGeneric, NULL /* todo, one day...*/, time, &authinfos->u.certinfos, &authinfos->u.certinfos.dhKeyInfo);
				break;
			default:
				;
			}

			if(goodPa)
			{
				kull_m_kerberos_asn1_PA_DATAs_build(&asreq.padata, 2, &PaGeneric, &PaPacRequest);
				if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, AS_REQ_PDU, &asreq, OutKdcReq)))
					PRINT_ERROR(L"Unable to encode AS_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
				if(asreq.padata)
					LocalFree(asreq.padata);
				ossFreeBuf(&kull_m_kerberos_asn1_world, PaGeneric.padata_value.value);
			}
			ossFreeBuf(&kull_m_kerberos_asn1_world, PaPacRequest.padata_value.value);
		}
		kull_m_kerberos_asn1_KdcReqBody_free(&asreq.req_body);
		kull_m_kerberos_asn1_PrincipalName_delete(&sname);
	}
	else
	{
		if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, AS_REQ_PDU, authinfos->u.certinfos.tmpAsReq, OutKdcReq)))
			PRINT_ERROR(L"Unable to encode AS_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	}
	return status;
}

BOOL kull_m_kerberos_asn1_EncKDCRepPart_from_AsRep_build(PKIWI_AUTH_INFOS authInfo, KDC_REP *AsRep, EncKDCRepPart **encAsRepPart, EncryptionKey *replyKey)
{
	BOOL status = FALSE;
	if(replyKey)
		RtlZeroMemory(replyKey, sizeof(EncryptionKey));
	switch(authInfo->type)
	{
	case KIWI_AUTH_INFOS_TYPE_KEY:
		status = kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_Key_build(AsRep, &authInfo->u.ekey, EncASRepPart_PDU, encAsRepPart);
		break;
	case KIWI_AUTH_INFOS_TYPE_RSA:
	case KIWI_AUTH_INFOS_TYPE_OTF_RSA:
		status = kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_Rsa_build(AsRep, &authInfo->u.certinfos.provider, EncASRepPart_PDU, encAsRepPart, replyKey);
		break;
	case KIWI_AUTH_INFOS_TYPE_RSA_DH:
	case KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH:
	case KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH:
		status = kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_RsaDh_build(AsRep, &authInfo->u.certinfos.dhKeyInfo, EncASRepPart_PDU, encAsRepPart, replyKey);
		break;
	default:
		;
	}
	return status;
}

BOOL kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_Key_build(KDC_REP *rep, EncryptionKey *key, int pdu, EncKDCRepPart **encRepPart)
{
	BOOL status = FALSE;
	OssBuf EncRepPartBuff;
	NTSTATUS ntStatus;
	*encRepPart = NULL;

	ntStatus = kull_m_kerberos_asn1_crypto_encrypt(((pdu == EncASRepPart_PDU) && (key->keytype != KERB_ETYPE_RC4_HMAC_NT)) ? KRB_KEY_USAGE_AS_REP_EP_SESSION_KEY : KRB_KEY_USAGE_TGS_REP_EP_SESSION_KEY, key, (OssBuf *) &rep->enc_part.cipher, &EncRepPartBuff, FALSE);
	if(NT_SUCCESS(ntStatus))
	{
		if(!(status = !ossDecode(&kull_m_kerberos_asn1_world, &pdu, &EncRepPartBuff, (LPVOID *) encRepPart)))
			PRINT_ERROR(L"Unable to decode EncASRepPart from REP: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));;
		LocalFree(EncRepPartBuff.value);
	}
	else PRINT_ERROR(L"Unable to decrypt EncASRepPart: %08x\n", ntStatus);
	return status;
}

BOOL kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_Rsa_build(KDC_REP *rep, PKULL_M_CRYPTO_PROV_INFO provInfo, int pdu, EncKDCRepPart **encRepPart, EncryptionKey *replyKey)
{
	BOOL status = FALSE;
	int internDpu = PA_PK_AS_REP_PDU;
	PA_DATA *paAsRepOld;
	OssBuf KeyData;
	PA_PK_AS_REP *pkAsRep = NULL;
	KERB_REPLY_KEY_PACKAGE *KeyPack = NULL;

	*encRepPart = NULL;
	if(paAsRepOld = kull_m_kerberos_asn1_PADATA_from_REP(rep, PA_TYPE_PK_AS_REP_OLD))
	{
		if(!ossDecode(&kull_m_kerberos_asn1_world, &internDpu, (OssBuf *) &paAsRepOld->padata_value, (LPVOID *) &pkAsRep))
		{
			if(pkAsRep->choice == encKeyPack_chosen)
			{
				if(kull_m_kerberos_asn1_crypto_simple_message_dec(provInfo, &pkAsRep->u.encKeyPack, &KeyData))
				{
					internDpu = KERB_REPLY_KEY_PACKAGE_PDU;
					if(!ossDecode(&kull_m_kerberos_asn1_world, &internDpu, &KeyData, (LPVOID *) &KeyPack))
					{
						status = kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_Key_build(rep, &KeyPack->replyKey, pdu, encRepPart);
						if(status && replyKey)
						{
							*replyKey = KeyPack->replyKey;
							if(replyKey->keyvalue.value = (PBYTE) LocalAlloc(LPTR, replyKey->keyvalue.length))
								RtlCopyMemory(replyKey->keyvalue.value, KeyPack->replyKey.keyvalue.value, replyKey->keyvalue.length);
						}
						ossFreePDU(&kull_m_kerberos_asn1_world, KERB_REPLY_KEY_PACKAGE_PDU, KeyPack);
					}
					else PRINT_ERROR(L"Unable to decode KERB_REPLY_KEY_PACKAGE from encKeyPack: %s\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));;
					LocalFree(KeyData.value);
				}
			}
			else PRINT_ERROR(L"PA_PK_AS_REP (old) is not encKeyPack\n");
			ossFreePDU(&kull_m_kerberos_asn1_world, PA_PK_AS_REP_PDU, pkAsRep);
		}
		else PRINT_ERROR(L"Unable to decode PA_PK_AS_REP from REP: %s\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));;
	}
	return status;
}

BOOL kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_RsaDh_build(KDC_REP *rep, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, int pdu, EncKDCRepPart **encRepPart, EncryptionKey *replyKey)
{
	BOOL status = FALSE;
	int internDpu = PA_PK_AS_REP_PDU;
	PA_DATA *paAsRep;
	PA_PK_AS_REP *pkAsRep = NULL;
	OssBuf buffer = {0, NULL};
	KDCDHKeyInfo *keyInfo = NULL;
	PCRYPT_INTEGER_BLOB pIntegerBlob;
	
	DWORD szPublicKey;
	PUBLICKEYSTRUC *PublicKey;
	HCRYPTKEY hSessionKey;

	DWORD dwSessionKey = 0;
	PBYTE pSessionKey;
	EncryptionKey eKey = {rep->enc_part.etype, {0, NULL}};

	*encRepPart = NULL;

	if(paAsRep = kull_m_kerberos_asn1_PADATA_from_REP(rep, PA_TYPE_PK_AS_REP))
	{
		if(!ossDecode(&kull_m_kerberos_asn1_world, &internDpu, (OssBuf *) &paAsRep->padata_value, (LPVOID *) &pkAsRep))
		{
			if(pkAsRep->choice == dhInfo_chosen)
			{
				if((!(dhKeyInfo->dhClientNonce.length && dhKeyInfo->dhClientNonce.value) == !(pkAsRep->u.dhInfo.bit_mask & serverDHNonce_present))
					||
					((dhKeyInfo->dhClientNonce.length && dhKeyInfo->dhClientNonce.value) && (pkAsRep->u.dhInfo.bit_mask & serverDHNonce_present)))
				{
					//if(pkAsRep->u.dhInfo.bit_mask & serverDHNonce_present)
					//{
					//	kprintf(L"(-) Server nonce:\n"); kull_m_string_wprintf_hex(pkAsRep->u.dhInfo.serverDHNonce.value, pkAsRep->u.dhInfo.serverDHNonce.length, 0 | (32 << 16)); kprintf(L"\n");
					//}
					if(kull_m_kerberos_asn1_crypto_simple_message_get(&pkAsRep->u.dhInfo.dhSignedData, &buffer))
					{
						internDpu = KDCDHKeyInfo_PDU;
						if(!ossDecode(&kull_m_kerberos_asn1_world, &internDpu, &buffer, (LPVOID *) &keyInfo))
						{
							if(kull_m_kerberos_asn1_crypto_genericDecode(X509_DH_PUBLICKEY, keyInfo->subjectPublicKey.value, keyInfo->subjectPublicKey.length / 8, (LPVOID *) &pIntegerBlob))
							{
								//kprintf(L"(W) Server Public key:\n"); kull_m_string_wprintf_hex(pIntegerBlob->pbData, pIntegerBlob->cbData, 0 | (32 << 16)); kprintf(L"\n"); //
								szPublicKey = pIntegerBlob->cbData + sizeof(PUBLICKEYSTRUC) + sizeof(DHPUBKEY);
								if(PublicKey = (PUBLICKEYSTRUC *) LocalAlloc(LPTR, szPublicKey))
								{
									PublicKey->bType = PUBLICKEYBLOB;
									PublicKey->bVersion = CUR_BLOB_VERSION;
									PublicKey->aiKeyAlg = CALG_DH_EPHEM;
									((DHPUBKEY *) ((PBYTE) PublicKey + sizeof(PUBLICKEYSTRUC)))->magic = '1HD\0';
									((DHPUBKEY *) ((PBYTE) PublicKey + sizeof(PUBLICKEYSTRUC)))->bitlen = pIntegerBlob->cbData * 8;
									RtlCopyMemory((PBYTE) PublicKey + sizeof(PUBLICKEYSTRUC) + sizeof(DHPUBKEY), pIntegerBlob->pbData, pIntegerBlob->cbData);

									if(CryptImportKey(dhKeyInfo->hProv, (LPCBYTE) PublicKey, szPublicKey, dhKeyInfo->hKey, 0, &hSessionKey))
									{
										if(CryptGetKeyParam(hSessionKey, KP_KEYVAL, NULL, &dwSessionKey, IPSEC_FLAG_CHECK))
										{
											if(pSessionKey = (PBYTE) LocalAlloc(LPTR, dwSessionKey))
											{
												if(CryptGetKeyParam(hSessionKey, KP_KEYVAL, pSessionKey, &dwSessionKey, IPSEC_FLAG_CHECK))
												{
													//kprintf(L"(W) SessionKey:\n"); kull_m_string_wprintf_hex(pSessionKey, dwSessionKey, 0 | (32 << 16)); kprintf(L"\n"); //
													kull_m_kerberos_asn1_crypto_reverseit(pSessionKey, dwSessionKey);
													//kprintf(L"(-) SessionKey:\n"); kull_m_string_wprintf_hex(pSessionKey, dwSessionKey, 0 | (32 << 16)); kprintf(L"\n"); //
													if(kull_m_kerberos_asn1_crypto_octetstring2key(pSessionKey, dwSessionKey, &dhKeyInfo->dhClientNonce, (pkAsRep->u.dhInfo.bit_mask & serverDHNonce_present) ? &pkAsRep->u.dhInfo.serverDHNonce : NULL, &eKey))
													{
														//kprintf(L"(-) Kerberos key (%s):\n", kull_m_kerberos_asn1_crypto_etype(eKey.keytype)); kull_m_string_wprintf_hex(eKey.keyvalue.value, eKey.keyvalue.length, 0 | (32 << 16)); kprintf(L"\n");
														status = kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_Key_build(rep, &eKey, pdu, encRepPart);
														if(status && replyKey)
														{
															*replyKey = eKey;
															if(replyKey->keyvalue.value = (PBYTE) LocalAlloc(LPTR, replyKey->keyvalue.length))
																RtlCopyMemory(replyKey->keyvalue.value, eKey.keyvalue.value, replyKey->keyvalue.length);
														}
														LocalFree(eKey.keyvalue.value);
													}
												}
												LocalFree(pSessionKey);
											}
										}
										else PRINT_ERROR_AUTO(L"CryptGetKeyParam");
										CryptDestroyKey(hSessionKey);
									}
									else PRINT_ERROR_AUTO(L"CryptImportKey");
									LocalFree(PublicKey);
								}
							}
							ossFreePDU(&kull_m_kerberos_asn1_world, KDCDHKeyInfo_PDU, keyInfo);
						}
						LocalFree(buffer.value);
					}
				}
				else PRINT_ERROR(L"Illogic nonce between client and server\n");
			}
			else PRINT_ERROR(L"PA_PK_AS_REP is not dhInfo\n");
			ossFreePDU(&kull_m_kerberos_asn1_world, PA_PK_AS_REP_PDU, pkAsRep);
		}
		else PRINT_ERROR(L"Unable to decode PA_PK_AS_REP from REP: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));;
	}
	return status;
}

void kull_m_kerberos_asn1_PA_DATAs_build(_seqof4 *padata, DWORD count, ...)
{
	DWORD i;
	va_list vaList;
	va_start(vaList, count);
	if(*padata = (_seqof4) LocalAlloc(LPTR, sizeof(struct _seqof4) * count))
	{
		for(i = 0; i < count; i++)
		{
			(*padata)[i].value = *va_arg(vaList, PA_DATA *);
			(*padata)[i].next = (i + 1 < count) ? &((*padata)[i + 1]) : NULL;
		}
	}
	va_end(vaList);
}

PA_DATA * kull_m_kerberos_asn1_PADATA_from_REP(KDC_REP *Rep, Int32 type)
{
	PA_DATA *result = NULL;
	struct _seqof4  *padata;
	if(Rep->bit_mask & KDC_REP_padata_present)
	{
		for(padata = Rep->padata; padata; padata = padata->next)
			if(padata->value.padata_type == type)
			{
				result = &padata->value;
				break;
			}
	}
	return result;
}

PA_DATA * kull_m_kerberos_asn1_PADATA_from_REQ(KDC_REQ *Req, Int32 type)
{
	PA_DATA *result = NULL;
	struct _seqof4  *padata;
	if(Req->bit_mask & KDC_REQ_padata_present)
	{
		for(padata = Req->padata; padata; padata = padata->next)
			if(padata->value.padata_type == type)
			{
				result = &padata->value;
				break;
			}
	}
	return result;
}

_octet1 * kull_m_kerberos_asn1_AuthorizationData_from_Type(AuthorizationData data, Int32 ad_type)
{
	_octet1 *ad_data = NULL;
	AuthorizationData cur;
	AD_IF_RELEVANT *adIfRelevant = NULL; // *?
	int myPdu = AD_IF_RELEVANT_PDU;

	for(cur = data; cur && !ad_data; cur = cur->next)
	{
		if(cur->value.ad_type == ad_type)
			ad_data = &cur->value.ad_data;
		else if(cur->value.ad_type == AD_TYPE_IF_RELEVANT)
		{
			if(!ossDecode(&kull_m_kerberos_asn1_world, &myPdu, (OssBuf *) &cur->value.ad_data, (LPVOID *) &adIfRelevant))
			{
				ad_data = kull_m_kerberos_asn1_AuthorizationData_from_Type(*adIfRelevant, ad_type);
				ossFreePDU(&kull_m_kerberos_asn1_world, AD_IF_RELEVANT_PDU, *adIfRelevant);
			}
		}
	}
	return ad_data;
}

BOOL kull_m_kerberos_asn1_PA_DATA_encTimeStamp_build(PA_DATA *data, KerberosTime *time, EncryptionKey *key)
{
	BOOL status = FALSE;
	PA_ENC_TS_ENC tsEnc = {0};
	PA_ENC_TIMESTAMP timeStampEnc = {0};
	OssBuf encodedTsEnc = {0, NULL}, encodedTimeStamp = {0, NULL};
	NTSTATUS ntStatus;

	RtlZeroMemory(data, sizeof(PA_DATA));
	timeStampEnc.etype = key->keytype;
	if(time)
		tsEnc.patimestamp = *time;
	else
		kull_m_kerberos_asn1_KerberosTime_build_systemtime(&tsEnc.patimestamp, NULL, FALSE);
	if(!ossEncode(&kull_m_kerberos_asn1_world, PA_ENC_TS_ENC_PDU, &tsEnc, &encodedTsEnc))
	{
		ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_AS_REQ_PA_ENC_TIMESTAMP, key, &encodedTsEnc, (OssBuf *) &timeStampEnc.cipher, TRUE);
		if(NT_SUCCESS(ntStatus))
		{
			if(status = !ossEncode(&kull_m_kerberos_asn1_world, PA_ENC_TIMESTAMP_PDU, &timeStampEnc, &encodedTimeStamp))
			{
				data->padata_type = PA_TYPE_ENC_TIMESTAMP;
				data->padata_value.length = encodedTimeStamp.length;
				data->padata_value.value = encodedTimeStamp.value;
			}
			else PRINT_ERROR(L"Unable to encode PA_ENC_TIMESTAMP: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
			LocalFree(timeStampEnc.cipher.value);
		}
		else PRINT_ERROR(L"Unable to encrypt PA_ENC_TS_ENC: %08x\n", ntStatus);
		ossFreeBuf(&kull_m_kerberos_asn1_world, encodedTsEnc.value);
	}
	else PRINT_ERROR(L"Unable to encode PA_ENC_TS_ENC: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kull_m_kerberos_asn1_PA_DATA_PA_PK_AS_REQ_old_build(PA_DATA *data, PrincipalName *sname, Realm srealm, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo)
{
	BOOL status = FALSE;
	PA_PK_AS_REQ pkAsReq = {0, {0, NULL}};
	OssBuf encodedPkAsReq = {0, NULL};

	RtlZeroMemory(data, sizeof(PA_DATA));
	if(kull_m_kerberos_asn1_AuthPackOld_signed_build(&pkAsReq.signedAuthPack, sname, srealm, time, certSignInfo))
	{
		if(status = !ossEncode(&kull_m_kerberos_asn1_world, PA_PK_AS_REQ_PDU, &pkAsReq, &encodedPkAsReq))
		{
			data->padata_type = PA_TYPE_PK_AS_REP_OLD;
			data->padata_value.length = encodedPkAsReq.length;
			data->padata_value.value = encodedPkAsReq.value;
		}
		else PRINT_ERROR(L"Unable to encode PA_PK_AS_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
		if(pkAsReq.signedAuthPack.value)
			LocalFree(pkAsReq.signedAuthPack.value);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_AuthPackOld_signed_build(_octet1 *signedInfo, PrincipalName *sname, Realm srealm, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo)
{
	BOOL status = FALSE;
	OssBuf AuthPackOld = {0, NULL};

	RtlZeroMemory(signedInfo, sizeof(_octet1));
	if(kull_m_kerberos_asn1_AuthPackOld_build(&AuthPackOld, sname, srealm, time))
	{
		status = kull_m_kerberos_asn1_crypto_simple_message_sign(certSignInfo, &AuthPackOld, signedInfo);
		ossFreeBuf(&kull_m_kerberos_asn1_world, AuthPackOld.value);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_AuthPackOld_build(OssBuf *AuthPackOld, PrincipalName *sname, Realm srealm, KerberosTime *time)
{
	BOOL status = FALSE;
	AuthPack_OLD auth = {0};

	RtlZeroMemory(AuthPackOld, sizeof(OssBuf));
	auth.pkAuthenticator.kdc_name = *sname;
	auth.pkAuthenticator.kdc_realm = srealm;
	auth.pkAuthenticator.cusec = 0;
	auth.pkAuthenticator.nonce = MIMIKATZ_NONCE;
	if(time)
		auth.pkAuthenticator.ctime = *time;
	else
		kull_m_kerberos_asn1_KerberosTime_build_systemtime(&auth.pkAuthenticator.ctime, NULL, FALSE);
	if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, AuthPack_OLD_PDU, &auth, AuthPackOld)))
		PRINT_ERROR(L"Unable to encode AuthPack_OLD: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kull_m_kerberos_asn1_PA_DATA_PA_PK_AS_REQ_build(PA_DATA *data, PSHA_DIGEST digest, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo)
{
	BOOL status = FALSE;
	PA_PK_AS_REQ pkAsReq = {0, {0, NULL}};
	OssBuf encodedPkAsReq = {0, NULL};

	RtlZeroMemory(data, sizeof(PA_DATA));
	if(kull_m_kerberos_asn1_AuthPack_signed_build(&pkAsReq.signedAuthPack, digest, time, certSignInfo, dhKeyInfo))
	{
		if(status = !ossEncode(&kull_m_kerberos_asn1_world, PA_PK_AS_REQ_PDU, &pkAsReq, &encodedPkAsReq))
		{
			data->padata_type = PA_TYPE_PK_AS_REQ;
			data->padata_value.length = encodedPkAsReq.length;
			data->padata_value.value = encodedPkAsReq.value;
		}
		else PRINT_ERROR(L"Unable to encode PA_PK_AS_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
		if(pkAsReq.signedAuthPack.value)
			LocalFree(pkAsReq.signedAuthPack.value);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_AuthPack_signed_build(_octet1 * signedInfo, PSHA_DIGEST digest, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo)
{
	BOOL status = FALSE;
	OssBuf AuthPack = {0, NULL};

	RtlZeroMemory(signedInfo, sizeof(_octet1));
	if(kull_m_kerberos_asn1_AuthPack_build(&AuthPack, digest, time, dhKeyInfo))
	{
		status = kull_m_kerberos_asn1_crypto_simple_message_sign(certSignInfo, &AuthPack, signedInfo);
		ossFreeBuf(&kull_m_kerberos_asn1_world, AuthPack.value);
	}
	return status;
}

const BYTE sha_req[SHA_DIGEST_LENGTH] = {0}; // Windows does not check? :))
BOOL kull_m_kerberos_asn1_AuthPack_build(OssBuf *authPack, PSHA_DIGEST digest, KerberosTime *time, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo)
{
	BOOL status = FALSE;
	AuthPack auth = {0};
	DWORD szPublicKey = 0;
	PUBLICKEYSTRUC *PublicKey = NULL;
	CRYPT_INTEGER_BLOB integerBlob = {0};
	CERT_X942_DH_PARAMETERS parameters = {0};
	OssEncodedOID eoid = {0};

	RtlZeroMemory(authPack, sizeof(OssBuf));
	if(kull_m_kerberos_asn1_crypto_get_DHKeyInfo_Parameters(dhKeyInfo->hKey, &parameters))
	{
		//kprintf("(W) Client P param:\n"); kull_m_string_printf_hex(parameters.p.pbData, parameters.p.cbData, 0 | (32 << 16)); kprintf("\n");
		//kprintf("(W) Client G param:\n"); kull_m_string_printf_hex(parameters.g.pbData, parameters.g.cbData, 0 | (32 << 16)); kprintf("\n");
		if(kull_m_kerberos_asn1_crypto_genericEncode(X509_DH_PARAMETERS, &parameters, &auth.clientPublicValue.algorithm.parameters.value, (PDWORD) &auth.clientPublicValue.algorithm.parameters.length))
		{
			auth.clientPublicValue.algorithm.bit_mask = parameters_present;
			if(CryptExportKey(dhKeyInfo->hKey, 0, PUBLICKEYBLOB, 0, NULL, &szPublicKey))
			{
				if(PublicKey = (PUBLICKEYSTRUC *) LocalAlloc(LPTR, szPublicKey))
				{
					if(CryptExportKey(dhKeyInfo->hKey, 0, PUBLICKEYBLOB, 0, (PBYTE) PublicKey, &szPublicKey))
					{
						integerBlob.cbData = szPublicKey - (sizeof(PUBLICKEYSTRUC) + sizeof(DHPUBKEY));
						integerBlob.pbData = (PBYTE) PublicKey + (sizeof(PUBLICKEYSTRUC) + sizeof(DHPUBKEY));
						//kprintf("(W) Client Public Key:\n"); kull_m_string_printf_hex(integerBlob.pbData, integerBlob.cbData, 0 | (32 << 16)); kprintf("\n");
						if(kull_m_kerberos_asn1_crypto_genericEncode(X509_DH_PUBLICKEY, &integerBlob, &auth.clientPublicValue.subjectPublicKey.value, (PDWORD) &auth.clientPublicValue.subjectPublicKey.length))
						{
							auth.clientPublicValue.subjectPublicKey.length *= 8; // in bits
							auth.bit_mask = clientPublicValue_present;
							if(dhKeyInfo->dhClientNonce.length && dhKeyInfo->dhClientNonce.value)
							{
								auth.bit_mask |= clientDHNonce_present;
								auth.clientDHNonce = dhKeyInfo->dhClientNonce;
								//kprintf("(-) Client Nonce:\n"); kull_m_string_printf_hex(auth.clientDHNonce.value, auth.clientDHNonce.length, 0 | (32 << 16)); kprintf("\n");
							}
							auth.pkAuthenticator.bit_mask = paChecksum_present;
							auth.pkAuthenticator.cusec = 0;
							if(time)
								auth.pkAuthenticator.ctime = *time;
							else
								kull_m_kerberos_asn1_KerberosTime_build_systemtime(&auth.pkAuthenticator.ctime, NULL, FALSE);
							auth.pkAuthenticator.nonce = MIMIKATZ_NONCE;
							auth.pkAuthenticator.paChecksum.length = SHA_DIGEST_LENGTH;
							auth.pkAuthenticator.paChecksum.value = digest ? digest->digest : (PBYTE) sha_req;
							if(!ossDotValToEncodedOid(&kull_m_kerberos_asn1_world, szOID_ANSI_X942_DH, &eoid))
							{
								auth.clientPublicValue.algorithm.algorithm.length = eoid.length;
								auth.clientPublicValue.algorithm.algorithm.value = eoid.value;
								if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, AuthPack_PDU, &auth, authPack)))
									ossFreeBuf(&kull_m_kerberos_asn1_world, authPack->value);
								ossFreeBuf(&kull_m_kerberos_asn1_world, eoid.value);
							}
							LocalFree(auth.clientPublicValue.subjectPublicKey.value);
						}
					}
					LocalFree(PublicKey);
				}
			}
			LocalFree(auth.clientPublicValue.algorithm.parameters.value);
		}
		kull_m_kerberos_asn1_crypto_free_DHKeyInfo_Parameters(&parameters);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_PA_DATA_FOR_USER_build(PA_DATA *data, PrincipalName *user, Realm realm, EncryptionKey *key)
{
	BOOL status = FALSE;
	OssBuf encodedReq = {0, NULL};

	data->padata_value.value = NULL;
	if(status = kull_m_kerberos_asn1_ForUser_build(&encodedReq, user, realm, key))
	{
		data->padata_type = PA_TYPE_FOR_USER;
		data->padata_value.length = encodedReq.length;
		data->padata_value.value = encodedReq.value;
	}
	return status;
}

BOOL kull_m_kerberos_asn1_ForUser_build(OssBuf *ForUserData, PrincipalName *user, Realm realm, EncryptionKey *key)
{
	BOOL status = FALSE;
	PA_FOR_USER_ENC forUser;
	BYTE hmacMd5[MD5_DIGEST_LENGTH] = {0};
	PKERB_CHECKSUM pCheckSum;
	PVOID Context;
	_seqof1 pname;

	ForUserData->length = 0;
	ForUserData->value = NULL;

	forUser.userName = *user;
	forUser.userRealm = realm;
	forUser.cksum.cksumtype = KERB_CHECKSUM_HMAC_MD5;
	forUser.cksum.checksum.length = sizeof(hmacMd5);
	forUser.cksum.checksum.value = hmacMd5;
	forUser.auth_package = MICROSOFT_KERBEROS_NAME_A;;
	if(key)
	{
		if(NT_SUCCESS(CDLocateCheckSum(KERB_CHECKSUM_HMAC_MD5, &pCheckSum)))
		{
			if(NT_SUCCESS(pCheckSum->InitializeEx(key->keyvalue.value, key->keyvalue.length, KERB_NON_KERB_CKSUM_SALT, &Context)))
			{
				pCheckSum->Sum(Context, sizeof(forUser.userName.name_type), &forUser.userName.name_type);
				for(pname = forUser.userName.name_string; pname; pname = pname->next)
					pCheckSum->Sum(Context, lstrlenA(pname->value), pname->value);
				pCheckSum->Sum(Context, lstrlenA(forUser.userRealm), forUser.userRealm);
				pCheckSum->Sum(Context, lstrlenA(forUser.auth_package), forUser.auth_package);
				pCheckSum->Finalize(Context, hmacMd5);
				pCheckSum->Finish(&Context);
			}
		}
	}
	if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, PA_FOR_USER_ENC_PDU, &forUser, ForUserData)))
			PRINT_ERROR(L"Unable to encode PA_FOR_USER_ENC: %s\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kull_m_kerberos_asn1_TgsReq_build(OssBuf *OutKdcReq, PrincipalName *cname, Realm crealm, PrincipalName *sname, Realm srealm, DWORD options, Ticket *ticket, EncryptionKey *key, Ticket *addTicket, _octet1 *pac, PA_DATA *optPa)
{
	BOOL status = FALSE;
	NTSTATUS ntStatus;
	TGS_REQ tgsReq = {0};
	PA_DATA PaGeneric = {0};
	OssBuf AuthData = {0, NULL};
	struct _seqof3 seqofTickets;
	
	OutKdcReq->length = 0;
	OutKdcReq->value = NULL;
	tgsReq.pvno = 5;
	tgsReq.msg_type = 12;
	kull_m_kerberos_asn1_KdcReqBody_build(&tgsReq.req_body, (options & KERB_KDCOPTION_request_anonymous) ? NULL : cname, srealm ? srealm : crealm, sname, options, NULL);
	if(addTicket)
	{
		seqofTickets.next = NULL;
		seqofTickets.value = *addTicket;
		tgsReq.req_body.additional_tickets = &seqofTickets;
		tgsReq.req_body.bit_mask |= additional_tickets_present;
	}
	if(pac)
	{
		if(kull_m_kerberos_asn1_AuthorizationData_from_PAC_build(&AuthData, pac))
		{
			ntStatus = kull_m_kerberos_asn1_crypto_encrypt((ticket->enc_part.bit_mask & kvno_present) ? KRB_KEY_USAGE_AS_REQ_AUTHORIZATION_SESSION : KRB_KEY_USAGE_AS_DATA_ENCRYPTED_NO_SPEC, key, &AuthData, (OssBuf *) &tgsReq.req_body.enc_authorization_data.cipher, TRUE);
			if(NT_SUCCESS(ntStatus))
			{
				tgsReq.req_body.bit_mask |= enc_authorization_data_present;
				tgsReq.req_body.enc_authorization_data.etype = key->keytype;
			}
			else PRINT_ERROR(L"Encrypt: %08x\n", ntStatus);
			ossFreeBuf(&kull_m_kerberos_asn1_world, AuthData.value);
		}
	}
	if(kull_m_kerberos_asn1_PA_DATA_TGS_REQ_build(&PaGeneric, cname, crealm, ticket, key))
	{
		kull_m_kerberos_asn1_PA_DATAs_build(&tgsReq.padata, optPa ? 2 : 1, &PaGeneric, optPa);
		tgsReq.bit_mask = KDC_REQ_padata_present;
		if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, TGS_REQ_PDU, &tgsReq, OutKdcReq)))
			PRINT_ERROR(L"Unable to encode TGS_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
		if(tgsReq.padata)
			LocalFree(tgsReq.padata);
		if(PaGeneric.padata_value.value)
			ossFreeBuf(&kull_m_kerberos_asn1_world, PaGeneric.padata_value.value);
	}
	kull_m_kerberos_asn1_KdcReqBody_free(&tgsReq.req_body);
	return status;
}

BOOL kull_m_kerberos_asn1_PA_DATA_PacRequest_build(PA_DATA *data, BOOL request)
{
	BOOL status = FALSE;
	KERB_PA_PAC_REQUEST pacRequest = {request};
	OssBuf encodedReq = {0, NULL};

	RtlZeroMemory(data, sizeof(PA_DATA));
	if(status = !ossEncode(&kull_m_kerberos_asn1_world, KERB_PA_PAC_REQUEST_PDU, &pacRequest, &encodedReq))
	{
		data->padata_type = PA_TYPE_PAC_REQUEST;
		data->padata_value.length = encodedReq.length;
		data->padata_value.value = encodedReq.value;
	}
	else PRINT_ERROR(L"Unable to encode KERB_PA_PAC_REQUEST: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kull_m_kerberos_asn1_PA_DATA_TGS_REQ_build(PA_DATA *data, PrincipalName *pname, Realm prealm, Ticket *ticket, EncryptionKey *key)
{
	BOOL status = FALSE;
	OssBuf encodedReq = {0, NULL};

	data->padata_value.value = NULL;
	if(status = kull_m_kerberos_asn1_ApReq_build(&encodedReq, pname, prealm, ticket, key, KRB_KEY_USAGE_TGS_REQ_PA_AUTHENTICATOR, NULL, NULL))
	{
		data->padata_type = PA_TYPE_TGS_REQ;
		data->padata_value.length = encodedReq.length;
		data->padata_value.value = encodedReq.value;
	}
	return status;
}

BOOL kull_m_kerberos_asn1_ApReq_build(OssBuf *ApReqData, PrincipalName *pname, Realm prealm, Ticket *ticket, EncryptionKey *key, ULONG keyUsage, EncryptionKey *authenticatorNewKey, UInt32 *authenticatorNewSeq)
{
	BOOL status = FALSE;
	NTSTATUS ntStatus;
	AP_REQ req = {0};
	Authenticator authenticator = {0};
	DWORD apOptions = 0;
	OssBuf encodedAuthenticator = {0, NULL};

	ApReqData->length = 0;
	ApReqData->value = NULL;
	req.pvno = 5;
	req.msg_type = 14;
	req.ap_options.length = sizeof(apOptions) * 8;
	req.ap_options.value = (unsigned char *) &apOptions;
	req.ticket = *ticket;
	req.authenticator.etype = key->keytype;
	authenticator.authenticator_vno = 5;
	authenticator.crealm = prealm;
	authenticator.cname = *pname;
	kull_m_kerberos_asn1_KerberosTime_build_systemtime(&authenticator.ctime, NULL, FALSE);
	if(authenticatorNewKey)
	{
		*authenticatorNewKey = *key;
		authenticatorNewKey->keyvalue.value = NULL;
		if(authenticatorNewKey->keyvalue.value = (unsigned char * ) LocalAlloc(LPTR, authenticatorNewKey->keyvalue.length))
		{
			ntStatus = CDGenerateRandomBits(authenticatorNewKey->keyvalue.value, authenticatorNewKey->keyvalue.length);
			if(NT_SUCCESS(ntStatus))
			{
				authenticator.subkey = *authenticatorNewKey;
				authenticator.bit_mask |= Authenticator_subkey_present;
			}
			else
			{
				authenticatorNewKey->keyvalue.value = (unsigned char * )LocalFree(authenticatorNewKey->keyvalue.value);
				PRINT_ERROR(L"GenerateRandom: %08x\n", ntStatus);
			}
		}
	}
	if(authenticatorNewSeq)
	{
		authenticator.seq_number = *authenticatorNewSeq = MIMIKATZ_NONCE;
		authenticator.bit_mask |= Authenticator_seq_number_present;
	}
	if(!ossEncode(&kull_m_kerberos_asn1_world, Authenticator_PDU, &authenticator, &encodedAuthenticator))
	{
		ntStatus = kull_m_kerberos_asn1_crypto_encrypt(keyUsage, key, &encodedAuthenticator, (OssBuf *) &req.authenticator.cipher, TRUE);
		if(NT_SUCCESS(ntStatus))
		{
			if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, AP_REQ_PDU, &req, ApReqData)))
				 PRINT_ERROR(L"Unable to encode AP_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
			LocalFree(req.authenticator.cipher.value);
		}
		else PRINT_ERROR(L"Encrypt: %08x\n", ntStatus);
		ossFreeBuf(&kull_m_kerberos_asn1_world, encodedAuthenticator.value);
	}
	else PRINT_ERROR(L"Unable to encode Authenticator: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kull_m_kerberos_asn1_AuthorizationData_from_PAC_build(OssBuf *AuthData, _octet1 *pac)
{
	BOOL status = FALSE;
	OssBuf adPacBuff = {0, NULL};
	struct AuthorizationData adIf = {NULL, {AD_TYPE_IF_RELEVANT}}, adPac = {NULL, {AD_TYPE_WIN2K_PAC}}, adRoot = {NULL, {0, {0, NULL}}};

	*AuthData = adPacBuff;// to do !!!

	adPac.value.ad_data = *pac;
	adRoot.next = &adPac;
	if(!ossEncode(&kull_m_kerberos_asn1_world, AD_IF_RELEVANT_PDU, &adRoot, &adPacBuff))
	{
		adIf.value.ad_data = *(_octet1 *) &adPacBuff;
		adRoot.next = &adIf;
		status = !ossEncode(&kull_m_kerberos_asn1_world, AD_IF_RELEVANT_PDU, &adRoot, AuthData);
		ossFreeBuf(&kull_m_kerberos_asn1_world, adPacBuff.value);
	}
	if(!status)
		PRINT_ERROR(L"Unable to encode AD_IF_RELEVANT: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kull_m_kerberos_asn1_PAC_from_EncTicketPart(EncryptionKey *key, EncryptedData *data, _octet1 *pac)
{
	BOOL status = FALSE;
	NTSTATUS ntStatus;
	OssBuf binTicket = {0, NULL};
	int myPdu;
	EncTicketPart *ticket = NULL;
	_octet1 *extractedPac;

	pac->length = 0;
	pac->value = NULL;
	ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_AS_REP_TGS_REP, key, (OssBuf *) &data->cipher, &binTicket, FALSE);
	if(NT_SUCCESS(ntStatus))
	{
		myPdu = EncTicketPart_PDU;
		if(!ossDecode(&kull_m_kerberos_asn1_world, &myPdu, &binTicket, (LPVOID *) &ticket))
		{
			if(ticket->bit_mask & EncTicketPart_authorization_data_present)
			{
				if(extractedPac = kull_m_kerberos_asn1_AuthorizationData_from_Type(ticket->authorization_data, AD_TYPE_WIN2K_PAC))
				{
					if(pac->value = (PBYTE) LocalAlloc(LPTR, extractedPac->length))
					{
						pac->length = extractedPac->length;
						RtlCopyMemory(pac->value, extractedPac->value, pac->length);
						status = TRUE;
					}
				}
				else PRINT_ERROR(L"No AD_TYPE_WIN2K_PAC found\n");
			}
			else PRINT_ERROR(L"No authorization data\n");
			ossFreePDU(&kull_m_kerberos_asn1_world, EncTicketPart_PDU, ticket);
		}
		else PRINT_ERROR(L"Unable to decode EncTicketPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
		LocalFree(binTicket.value);
	}
	else PRINT_ERROR(L"Decrypt: %08x\n", ntStatus);
	return status;
}

BOOL kull_m_kerberos_asn1_KrbPriv_build(_octet1 *data, EncryptionKey *key, PCSTR machineName, OssBuf *OutKrbPriv, UInt32 *seq)
{
	BOOL status = FALSE;
	NTSTATUS ntStatus;
	EncKrbPrivPart encPart;
	KRB_PRIV kPriv;
	unsigned char src[16];
	OssBuf bufEncPart = {0, NULL};
	
	OutKrbPriv->length = 0;
	OutKrbPriv->value = NULL;

	RtlFillMemory(src, ARRAYSIZE(src), ' ');
	if(machineName)
		RtlCopyMemory(src, machineName, min(strlen(machineName), ARRAYSIZE(src)));

	kPriv.pvno = 5;
	kPriv.msg_type = 21;
	kPriv.enc_part.bit_mask = 0;
	kPriv.enc_part.etype = key->keytype;

	encPart.bit_mask = 0;
	encPart.s_address.addr_type = 20;
	encPart.s_address.address.length = ARRAYSIZE(src);
	encPart.s_address.address.value = src;
	encPart.user_data = *data;

	if(seq)
	{
		encPart.seq_number = *seq;
		encPart.bit_mask |= EncKrbPrivPart_seq_number_present;
	}

	if(!ossEncode(&kull_m_kerberos_asn1_world, EncKrbPrivPart_PDU, &encPart, &bufEncPart))
	{
		ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_KRB_PRIV_ENCRYPTED_PART, key, &bufEncPart, (OssBuf *) &kPriv.enc_part.cipher, TRUE);
		if(NT_SUCCESS(ntStatus))
		{
			if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, KRB_PRIV_PDU, &kPriv, OutKrbPriv)))
				PRINT_ERROR(L"Unable to encode KRB_PRIV: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
			LocalFree(kPriv.enc_part.cipher.value);
		}
		else PRINT_ERROR(L"Encrypt: %08x\n", ntStatus);
		ossFreeBuf(&kull_m_kerberos_asn1_world, bufEncPart.value);
	}
	else PRINT_ERROR(L"Unable to encode EncKrbPrivPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kull_m_kerberos_asn1_EncKrbPrivPart_from_Priv_build(KRB_PRIV *priv, EncKrbPrivPart ** encKrbPrivPart, EncryptionKey *authKey)
{
	BOOL status = FALSE;
	NTSTATUS ntStatus;
	OssBuf encKrbPrivPartBuff;
	int pdu = EncKrbPrivPart_PDU;
	*encKrbPrivPart = NULL;

	ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_KRB_PRIV_ENCRYPTED_PART, authKey, (OssBuf *) &priv->enc_part.cipher, &encKrbPrivPartBuff, FALSE);
	if(NT_SUCCESS(ntStatus))
	{
		if(!(status = !ossDecode(&kull_m_kerberos_asn1_world, &pdu, &encKrbPrivPartBuff, (LPVOID *) encKrbPrivPart)))
			PRINT_ERROR(L"Unable to decode EncKrbPrivPart from REP: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));;
		LocalFree(encKrbPrivPartBuff.value);
	}
	else PRINT_ERROR(L"Decrypt: %08x\n", ntStatus);
	return status;
}

BOOL kull_m_kerberos_asn1_KrbCred_build(KDC_REP *rep, EncKDCRepPart *repPart, OssBuf *OutKrbCred)
{
	BOOL status = FALSE;
	KRB_CRED cred;
	struct _seqof3 seqTicket;
	EncKrbCredPart encKrbCredPart;
	struct _seqof5 krbCredInfo;

	OutKrbCred->length = 0;
	OutKrbCred->value = NULL;

	cred.pvno = 5;
	cred.msg_type = 22;
	cred.tickets = &seqTicket;
		seqTicket.next= NULL;
		seqTicket.value = rep->ticket;
	cred.enc_part.bit_mask = 0;
	cred.enc_part.etype = KERB_ETYPE_NULL;
	cred.enc_part.cipher.length = 0;
	cred.enc_part.cipher.value = NULL;

	encKrbCredPart.bit_mask = 0;
	encKrbCredPart.ticket_info = &krbCredInfo;

	krbCredInfo.next = NULL;
	krbCredInfo.value.bit_mask = pname_present | flags_present | endtime_present | KrbCredInfo_sname_present;
	krbCredInfo.value.key = repPart->key;
	krbCredInfo.value.prealm = rep->crealm;
	krbCredInfo.value.pname = rep->cname;
	krbCredInfo.value.flags = repPart->flags;
	krbCredInfo.value.endtime = repPart->endtime;
	krbCredInfo.value.sname = repPart->sname;
	krbCredInfo.value.srealm = repPart->srealm;

	if(repPart->bit_mask & EncKDCRepPart_starttime_present)
	{
		krbCredInfo.value.starttime = repPart->starttime;
		krbCredInfo.value.bit_mask |= KrbCredInfo_starttime_present;
	}
	if(repPart->bit_mask & EncKDCRepPart_renew_till_present)
	{
		krbCredInfo.value.renew_till = repPart->renew_till;
		krbCredInfo.value.bit_mask |= KrbCredInfo_renew_till_present;
	}
	if(repPart->bit_mask & EncKDCRepPart_caddr_present)
	{
		krbCredInfo.value.caddr = repPart->caddr;
		krbCredInfo.value.bit_mask |= KrbCredInfo_caddr_present;
	}
	if(!ossEncode(&kull_m_kerberos_asn1_world, EncKrbCredPart_PDU, &encKrbCredPart, (OssBuf *) &cred.enc_part.cipher))
	{
		if(!(status = !ossEncode(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, &cred, OutKrbCred)))
			PRINT_ERROR(L"Unable to encode KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
		ossFreeBuf(&kull_m_kerberos_asn1_world, cred.enc_part.cipher.value);
	}
	else PRINT_ERROR(L"Unable to encode EncKrbCredPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

LPWSTR kull_m_kerberos_asn1_KdcRep_filename(KDC_REP *rep, EncKDCRepPart *enc, PCWCHAR opt, PCWCHAR ext)
{
	struct _seqof1 *names;
	DWORD len = 4; // TGT_ or TGS_
	LPWSTR buffer = NULL, nbuffer, sep;
	PCWCHAR pExt = ext ? ext : MIMIKATZ_KERBEROS_EXT;

	for(names = rep->cname.name_string; names; names = names->next)
		len += lstrlenA(names->value) + 1; // + ~ or @
	len += lstrlenA(rep->crealm);
	if(enc)
	{
		len += 1; // + _
		for(names = enc->sname.name_string; names; names = names->next)
			len += lstrlenA(names->value) + 1; // + ~ or @
		len += lstrlenA(enc->srealm);
	}
	if(opt)
		len += lstrlenW(opt);
	len += 1 + lstrlen(pExt) + 1; // + . + NULL

	if(buffer = (LPWSTR) LocalAlloc(LPTR, len * sizeof(wchar_t)))
	{
		wcscat_s(buffer, len, (rep->msg_type == 11) ? L"TGT_" : L"TGS_");
		for(names = rep->cname.name_string; names; names = names->next)
		{
			if(nbuffer = kull_m_string_qad_ansi_to_unicode(names->value))
			{
				wcscat_s(buffer, len, nbuffer);
				sep = names->next ? L"~" : L"@";
				wcscat_s(buffer, len, sep);
				LocalFree(nbuffer);
			}
		}
		if(nbuffer = kull_m_string_qad_ansi_to_unicode(rep->crealm))
		{
			wcscat_s(buffer, len, nbuffer);
			LocalFree(nbuffer);
		}
		if(enc)
		{
			wcscat_s(buffer, len, L"_");
			for(names = enc->sname.name_string; names; names = names->next)
			{
				if(nbuffer = kull_m_string_qad_ansi_to_unicode(names->value))
				{
					wcscat_s(buffer, len, nbuffer);
					sep = names->next ? L"~" : L"@";
					wcscat_s(buffer, len, sep);
					LocalFree(nbuffer);
				}
			}
			if(nbuffer = kull_m_string_qad_ansi_to_unicode(enc->srealm))
			{
				wcscat_s(buffer, len, nbuffer);
				LocalFree(nbuffer);
			}
		}
		if(opt)
			wcscat_s(buffer, len, opt);
		wcscat_s(buffer, len, L".");
		wcscat_s(buffer, len, pExt);
		kull_m_file_cleanFilename(buffer);
	}
	return buffer;
}

LPWSTR kull_m_kerberos_asn1_KrbCred_filename(KRB_CRED *cred, PCWCHAR opt, PCWCHAR ext)
{
	struct _seqof1 *names;
	DWORD len = 0;
	LPWSTR buffer = NULL, nbuffer;
	PCWCHAR pExt = ext ? ext : MIMIKATZ_KERBEROS_EXT;
	int pduNum = EncKrbCredPart_PDU;
	EncKrbCredPart *KrbCred = NULL;
	KrbCredInfo *infos;

	if(cred->enc_part.etype == KERB_ETYPE_NULL)
	{
		if(!ossDecode(&kull_m_kerberos_asn1_world, &pduNum, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &KrbCred))
		{
			infos = &KrbCred->ticket_info->value;
			if(infos->bit_mask & pname_present)
			{
				for(names = infos->pname.name_string; names; names = names->next)
					len += lstrlenA(names->value) + 1; // + ~ or @
				if(infos->prealm)
					len += lstrlenA(infos->prealm);
				else len--;
			}
			if(infos->bit_mask & KrbCredInfo_sname_present)
			{
				len += 1; // + _
				for(names = infos->sname.name_string; names; names = names->next)
					len += lstrlenA(names->value) + 1; // + ~ or @
				if(infos->srealm)
					len += lstrlenA(infos->srealm);
				else len--;
			}
			if(opt)
				len += lstrlenW(opt);
			len += 1 + lstrlen(pExt) + 1; // + . + NULL

			if(buffer = (LPWSTR) LocalAlloc(LPTR, len * sizeof(wchar_t)))
			{
				if(infos->bit_mask & pname_present)
				{
					for(names = infos->pname.name_string; names; names = names->next)
					{
						if(nbuffer = kull_m_string_qad_ansi_to_unicode(names->value))
						{
							wcscat_s(buffer, len, nbuffer);
							if(names->next)
								wcscat_s(buffer, len, L"~");
							LocalFree(nbuffer);
						}
					}
					if(infos->prealm)
					{
						wcscat_s(buffer, len, L"@");
						if(nbuffer = kull_m_string_qad_ansi_to_unicode(infos->prealm))
						{
							wcscat_s(buffer, len, nbuffer);
							LocalFree(nbuffer);
						}
					}
				}
				if(infos->bit_mask & KrbCredInfo_sname_present)
				{
					wcscat_s(buffer, len, L"_");
					for(names = infos->sname.name_string; names; names = names->next)
					{
						if(nbuffer = kull_m_string_qad_ansi_to_unicode(names->value))
						{
							wcscat_s(buffer, len, nbuffer);
							if(names->next)
								wcscat_s(buffer, len, L"~");
							LocalFree(nbuffer);
						}
					}
					if(infos->srealm)
					{
						wcscat_s(buffer, len, L"@");
						if(nbuffer = kull_m_string_qad_ansi_to_unicode(infos->srealm))
						{
							wcscat_s(buffer, len, nbuffer);
							LocalFree(nbuffer);
						}
					}
				}
				if(opt)
					wcscat_s(buffer, len, opt);
				wcscat_s(buffer, len, L".");
				wcscat_s(buffer, len, pExt);
				kull_m_file_cleanFilename(buffer);
			}
			ossFreePDU(&kull_m_kerberos_asn1_world, EncKrbCredPart_PDU, KrbCred);
		}
		else PRINT_ERROR(L"Unable to decode EncKrbCredPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	}
	return buffer;
}

BOOL kull_m_kerberos_asn1_KdcRep_save(KDC_REP *rep, EncKDCRepPart *encRepPart, LPCWSTR filename, LPCWSTR opt, PKULL_M_KERBEROS_ASN1_SAVEKDCREP_CALLBACK callback)
{
	BOOL status = FALSE;
	OssBuf KrbCred = {0, NULL};
	LPCWSTR dstFilename = NULL;
	LPWSTR buffer = NULL;

	if(kull_m_kerberos_asn1_KrbCred_build(rep, encRepPart, &KrbCred))
	{
		if(callback)
			status = NT_SUCCESS(callback(KrbCred.value, KrbCred.length, &encRepPart->sname));
		else
		{
			if(filename)
				dstFilename = filename;
			else
			{
				if(buffer = kull_m_kerberos_asn1_KdcRep_filename(rep, encRepPart, opt, NULL))
					dstFilename = buffer;
			}
			if(dstFilename)
			{
				if(status = kull_m_file_writeData(dstFilename, KrbCred.value, KrbCred.length))
					kprintf(L"  > Ticket in file \'%s\'\n", dstFilename);
				else PRINT_ERROR_AUTO(L"kull_m_file_writeData");

			}
			else PRINT_ERROR(L"Unable to get a filename\n");
		}
		ossFreeBuf(&kull_m_kerberos_asn1_world, KrbCred.value);
	}
	if(buffer)
		LocalFree(buffer);
	return status;
}

const PCWCHAR TicketFlagsToStrings[] = {
	L"name_canonicalize", L"?", L"ok_as_delegate", L"?",
	L"hw_authent", L"pre_authent", L"initial", L"renewable",
	L"invalid", L"postdated", L"may_postdate", L"proxy",
	L"proxiable", L"forwarded", L"forwardable", L"reserved",
};
void kull_m_kerberos_asn1_displayFlags(ULONG flags)
{
	DWORD i;
	for(i = 0; i < ARRAYSIZE(TicketFlagsToStrings); i++)
		if((flags >> (i + 16)) & 1)
			kprintf(L"%s ; ", TicketFlagsToStrings[i]);
}
BOOL kull_m_kerberos_asn1_KrbCred_decode(OssBuf *ossBuf, EncryptionKey *key, KRB_CRED **KrbCred, EncKrbCredPart **encKrbCred)
{
	BOOL status = FALSE;
	DWORD flags;
	int myPdu = KRB_CRED_PDU;
	*KrbCred = NULL;
	*encKrbCred = NULL;

	if(!ossDecode(&kull_m_kerberos_asn1_world, &myPdu, ossBuf, (LPVOID *) KrbCred))
	{
		kprintf(L"  [krb-cred]     S: ");
		kull_m_kerberos_asn1_PrincipalName_descr(&(*KrbCred)->tickets->value.sname, FALSE);
		kprintf(L" @ %S\n  [krb-cred]     E: [%08x] %s\n", (*KrbCred)->tickets->value.realm, (*KrbCred)->tickets->value.enc_part.etype, kull_m_kerberos_asn1_crypto_etype((*KrbCred)->tickets->value.enc_part.etype));
				
		// TODO: decryption with key
		myPdu = EncKrbCredPart_PDU;
		if(status = !ossDecode(&kull_m_kerberos_asn1_world, &myPdu, (OssBuf *) &(*KrbCred)->enc_part.cipher, (LPVOID *) encKrbCred))
		{
			if((*encKrbCred)->ticket_info->value.bit_mask & pname_present)
			{
				kprintf(L"  [enc-krb-cred] P: ");
				kull_m_kerberos_asn1_PrincipalName_descr(&(*encKrbCred)->ticket_info->value.pname, FALSE);
				if((*encKrbCred)->ticket_info->value.prealm)
					kprintf(L" @ %S", (*encKrbCred)->ticket_info->value.prealm);
				kprintf(L"\n");
			}
			if((*encKrbCred)->ticket_info->value.bit_mask & KrbCredInfo_sname_present)
			{
				kprintf(L"  [enc-krb-cred] S: ");
				kull_m_kerberos_asn1_PrincipalName_descr(&(*encKrbCred)->ticket_info->value.sname, FALSE);
				if((*encKrbCred)->ticket_info->value.srealm)
					kprintf(L" @ %S", (*encKrbCred)->ticket_info->value.srealm);
				kprintf(L"\n");
			}

			kprintf(L"  [enc-krb-cred] T: ");
			if((*encKrbCred)->ticket_info->value.bit_mask & authtime_present)
			{
				kprintf(L"{A:");
				kull_m_kerberos_asn1_KerberosTime_print(&(*encKrbCred)->ticket_info->value.authtime);
				kprintf(L"} ");
			}
			if((*encKrbCred)->ticket_info->value.bit_mask & KrbCredInfo_starttime_present)
			{
				kprintf(L"[");
				kull_m_kerberos_asn1_KerberosTime_print(&(*encKrbCred)->ticket_info->value.starttime);
				kprintf(L" ; ");
			}
			if((*encKrbCred)->ticket_info->value.bit_mask & endtime_present)
			{
				kull_m_kerberos_asn1_KerberosTime_print(&(*encKrbCred)->ticket_info->value.endtime);
				kprintf(L"]");
			}
			if((*encKrbCred)->ticket_info->value.bit_mask & KrbCredInfo_renew_till_present)
			{
				kprintf(L" {R:");
				kull_m_kerberos_asn1_KerberosTime_print(&(*encKrbCred)->ticket_info->value.renew_till);
				kprintf(L"}");
			}
			kprintf(L"\n");

			if((*encKrbCred)->ticket_info->value.bit_mask & flags_present)
			{
				if((*encKrbCred)->ticket_info->value.flags.length >= (sizeof(DWORD) * 8))
				{
					flags = _byteswap_ulong(*(PDWORD) (*encKrbCred)->ticket_info->value.flags.value);
					kprintf(L"  [enc-krb-cred] F: [%08x] ", flags);
					kull_m_kerberos_asn1_displayFlags(flags);
					kprintf(L"\n");
				}
			}
			kprintf(L"  [enc-krb-cred] K: ");
			kull_m_kerberos_asn1_crypto_ekey_descr(&(*encKrbCred)->ticket_info->value.key);
		}
		else
		{
			PRINT_ERROR(L"Unable to decode EncKrbCredPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
			ossFreePDU(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, *KrbCred);
			*KrbCred = NULL;
		}
	}
	else PRINT_ERROR(L"Unable to decode KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kull_m_kerberos_asn1_KrbCred_load(LPCWSTR filename, EncryptionKey *key, KRB_CRED **KrbCred, EncKrbCredPart **encKrbCred)
{
	BOOL status = FALSE;
	OssBuf ossTgtBuff = {0, NULL};
	*KrbCred = NULL;
	*encKrbCred = NULL;
	if(kull_m_file_readData(filename, &ossTgtBuff.value, (PDWORD) &ossTgtBuff.length))
	{
		status = kull_m_kerberos_asn1_KrbCred_decode(&ossTgtBuff, key, KrbCred, encKrbCred);
		LocalFree(ossTgtBuff.value);
	}
	else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	return status;
}