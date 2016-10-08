/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "kull_m_kerberos_asn1_helper.h"

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

OssGlobal	world;

BOOL kull_m_kerberos_asn1_helper_init()
{
	BOOL status = FALSE;
	
	if(!ossinit(&world, kull_m_kerberos_asn1) == 0)
		PRINT_ERROR("ossinit\n");
	else status = TRUE;
	return status;
}

BOOL kull_m_kerberos_asn1_helper_term()
{
	ossterm(&world);
	return TRUE;
}

void kull_m_kerberos_asn1_helper_ossFreeBuf(void *data)
{
	ossFreeBuf(&world, data);
}

int kull_m_kerberos_asn1_helper_ossFreePDU(int pdunum, void *data)
{
	return ossFreePDU(&world, pdunum, data);
}

int kull_m_kerberos_asn1_helper_ossPrintPDU(int pdunum, void *data)
{
	return ossPrintPDU(&world, pdunum, data);
}

int kull_m_kerberos_asn1_helper_ossDecode(int pdunum, OssBuf *input, void **output)
{
	return ossDecode(&world, &pdunum, input, output);
}

int kull_m_kerberos_asn1_helper_ossEncode(int pdunum, void * input, OssBuf *output)
{
	return ossEncode(&world, pdunum,  input, output);
}

int kull_m_kerberos_asn1_helper_ossCpyValue(int pdunum, void *source, void **destination)
{
	return ossCpyValue(&world, pdunum, source, destination);
}

char * kull_m_kerberos_asn1_helper_ossGetErrMsg()
{
	return ossGetErrMsg(&world);
}

void kull_m_kerberos_asn1_helper_init_PrincipalName(PrincipalName * name, INT name_type, DWORD count, ...)
{
	DWORD i;
	va_list vaList;
	va_start(vaList, count); 
	name->name_type = name_type;
	if(name->name_string = (struct _seqof1 *) LocalAlloc(LPTR, sizeof(struct _seqof1) * count))
	{
		for(i = 0; i < count; i++)
		{
			name->name_string[i].value = va_arg(vaList, char *);
			name->name_string[i].next = (i + 1 < count) ? &name->name_string[i + 1] : NULL;
		}
	}
	va_end(vaList);
}

const KerberosTime MAX_MS_2037_GT = {2037, 9, 13, 2, 48, 5, 0, 0, TRUE};
void kull_m_kerberos_asn1_helper_init_KerberosTime(KerberosTime *time, PSYSTEMTIME pSystemTime, BOOL isMaxMs2037)
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

void kull_m_kerberos_asn1_helper_init_KerberosTime2(KerberosTime *time, PFILETIME pFileTime, BOOL isMaxMs2037)
{
	SYSTEMTIME systemTime;
	BOOL isPtr = FALSE;
	if(!isMaxMs2037 && pFileTime)
		isPtr = FileTimeToSystemTime(pFileTime, &systemTime);
	kull_m_kerberos_asn1_helper_init_KerberosTime(time, isPtr ? &systemTime : NULL, isMaxMs2037);
}

void kull_m_kerberos_asn1_helper_init_KerberosTime3(KerberosTime *time, time_t uTime)
{
	FILETIME fileTime;
	*(PLONGLONG) &fileTime = Int32x32To64(uTime, 10000000) + 116444736000000000;
	kull_m_kerberos_asn1_helper_init_KerberosTime2(time, &fileTime, FALSE);
}

void kull_m_kerberos_asn1_helper_get_KerberosTime(KerberosTime *time, PSYSTEMTIME pSystemTime)
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

void kull_m_kerberos_asn1_helper_get_KerberosTime2(KerberosTime *time, PFILETIME pFileTime)
{
	SYSTEMTIME systemTime;
	kull_m_kerberos_asn1_helper_get_KerberosTime(time, &systemTime);
	SystemTimeToFileTime(&systemTime, pFileTime);
}

void kull_m_kerberos_asn1_helper_get_KerberosTime3(KerberosTime *time, time_t * uTime)
{
	FILETIME fileTime;
	kull_m_kerberos_asn1_helper_get_KerberosTime2(time, &fileTime);
	*uTime = (*(PLONGLONG) &fileTime - 116444736000000000) / 10000000; 
}

void kull_m_kerberos_asn1_helper_display_KerberosTime(KerberosTime *time)
{
	FILETIME ft;
	kull_m_kerberos_asn1_helper_get_KerberosTime2(time, &ft);
	kull_m_string_displayLocalFileTime(&ft);
}

PA_DATA * kull_m_kerberos_asn1_helper_get_PADATA_from_REP(KDC_REP *Rep, Int32 type)
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

PA_DATA * kull_m_kerberos_asn1_helper_get_PADATA_from_REQ(KDC_REQ *Req, Int32 type)
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

void kull_m_kerberos_asn1_helper_init_PADATAs(_seqof4 *padata, DWORD count, ...)
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

BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_encTimeStamp(PA_DATA *data, EncryptionKey *key)
{
	BOOL status = FALSE;
	PA_ENC_TS_ENC tsEnc;
	PA_ENC_TIMESTAMP timeStampEnc;
	OssBuf encodedTsEnc = {0, NULL}, encodedTimeStamp = {0, NULL};

	data->padata_value.value = NULL;
	tsEnc.bit_mask = 0;
	timeStampEnc.bit_mask = 0;
	timeStampEnc.etype = key->keytype;
	kull_m_kerberos_asn1_helper_init_KerberosTime(&tsEnc.patimestamp, NULL, FALSE);
	if(!ossEncode(&world, PA_ENC_TS_ENC_PDU, &tsEnc, &encodedTsEnc))
	{
		if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt(KRB_KEY_USAGE_AS_REQ_PA_ENC_TIMESTAMP, key, &encodedTsEnc, (OssBuf *) &timeStampEnc.cipher, TRUE)))
		{
			if(status = !ossEncode(&world, PA_ENC_TIMESTAMP_PDU, &timeStampEnc, &encodedTimeStamp))
			{
				data->padata_type = PA_TYPE_ENC_TIMESTAMP;
				data->padata_value.length = encodedTimeStamp.length;
				data->padata_value.value = encodedTimeStamp.value;
			}
			else PRINT_ERROR("%s\n", ossGetErrMsg(&world));
			LocalFree(timeStampEnc.cipher.value);
		}
		else PRINT_ERROR("Encrypt\n");
		ossFreeBuf(&world, encodedTsEnc.value);
	}
	else PRINT_ERROR("%s\n", ossGetErrMsg(&world));
	return status;
}

BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_PacRequest(PA_DATA *data, BOOL request)
{
	BOOL status = FALSE;
	KERB_PA_PAC_REQUEST pacRequest = {request};
	OssBuf encodedReq = {0, NULL};

	data->padata_value.value = NULL;
	if(status = !ossEncode(&world, KERB_PA_PAC_REQUEST_PDU, &pacRequest, &encodedReq))
	{
		data->padata_type = PA_TYPE_PAC_REQUEST;
		data->padata_value.length = encodedReq.length;
		data->padata_value.value = encodedReq.value;
	}
	else PRINT_ERROR("%s\n", ossGetErrMsg(&world));
	return status;
}

BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_TGS_REQ(PA_DATA *data, PCSTR Username, PCSTR Domain, Ticket *ticket, EncryptionKey *key)
{
	BOOL status = FALSE;
	OssBuf encodedReq = {0, NULL};

	data->padata_value.value = NULL;
	if(status = kull_m_kerberos_asn1_helper_build_ApReq(&encodedReq, Username, Domain, ticket, key, KRB_KEY_USAGE_TGS_REQ_PA_AUTHENTICATOR, NULL, NULL))
	{
		data->padata_type = PA_TYPE_TGS_REQ;
		data->padata_value.length = encodedReq.length;
		data->padata_value.value = encodedReq.value;
	}
	return status;
}

BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_PA_PK_AS_REQ_old(PA_DATA *data, PCSTR Domain, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo)
{
	BOOL status = FALSE;
	PA_PK_AS_REQ pkAsReq = {0, {0, NULL}};
	OssBuf encodedPkAsReq = {0, NULL};

	data->padata_value.value = NULL;
	if(kull_m_kerberos_asn1_helper_build_AuthPackOld_signed(&pkAsReq.signedAuthPack, Domain, time, certSignInfo))
	{
		if(status = !ossEncode(&world, PA_PK_AS_REQ_PDU, &pkAsReq, &encodedPkAsReq))
		{
			data->padata_type = PA_TYPE_PK_AS_REP_OLD;
			data->padata_value.length = encodedPkAsReq.length;
			data->padata_value.value = encodedPkAsReq.value;
		}
		if(pkAsReq.signedAuthPack.value)
			LocalFree(pkAsReq.signedAuthPack.value);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_PA_PK_AS_REQ(PA_DATA *data, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, PSHA_DIGEST digest)
{
	BOOL status = FALSE;
	PA_PK_AS_REQ pkAsReq = {0, {0, NULL}};
	OssBuf encodedPkAsReq = {0, NULL};

	data->padata_value.value = NULL;
	if(kull_m_kerberos_asn1_helper_build_AuthPack_signed(&pkAsReq.signedAuthPack, time, certSignInfo, dhKeyInfo, digest))
	{
		if(status = !ossEncode(&world, PA_PK_AS_REQ_PDU, &pkAsReq, &encodedPkAsReq))
		{
			data->padata_type = PA_TYPE_PK_AS_REQ;
			data->padata_value.length = encodedPkAsReq.length;
			data->padata_value.value = encodedPkAsReq.value;
		}
		if(pkAsReq.signedAuthPack.value)
			LocalFree(pkAsReq.signedAuthPack.value);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_AsReq_Generic(PKIWI_AUTH_INFOS authInfo, PCSTR Service, PCSTR Target, KerberosTime *time, BOOL PacRequest, OssBuf *AsReq)
{
	BOOL status = FALSE;
	AS_REQ *AsReqObject = NULL;
	int pdu = AS_REQ_PDU;
	switch(authInfo->type)
	{
	case KIWI_AUTH_INFOS_TYPE_KEY:
		status = kull_m_kerberos_asn1_helper_build_KdcReq_key(authInfo->szUser, authInfo->szDomain, &authInfo->u.userKey, Service, Target, NULL, PacRequest, NULL, NULL, AsReq);
		break;
	case KIWI_AUTH_INFOS_TYPE_RSA:
	case KIWI_AUTH_INFOS_TYPE_OTF_RSA:
		status = kull_m_kerberos_asn1_helper_build_KdcReq_RSA(authInfo->szUser, authInfo->szDomain, &authInfo->u.certInfoDH.certinfo, Service, Target, time, PacRequest, AsReq);
		break;
	case KIWI_AUTH_INFOS_TYPE_RSA_DH:
	case KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH:
		status = kull_m_kerberos_asn1_helper_build_KdcReq_RSA_DH(authInfo->szUser, authInfo->szDomain, &authInfo->u.certInfoDH.certinfo, &authInfo->u.certInfoDH.dhKeyInfo, Service, Target, time, PacRequest, AsReq);
		break;
	case KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH:
			AsReq->length = 0;
			AsReq->value = NULL;
			if(!(status = !ossEncode(&world, pdu, authInfo->u.asReqDH.AsReq, AsReq)))
				PRINT_ERROR("Unable to encode AS_REQ buffer: %s\n", ossGetErrMsg(&world));
			ossFreePDU(&world, pdu, AsReqObject);
		break;
	}
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_AsRep_Generic(PKIWI_AUTH_INFOS authInfo, KDC_REP *AsRep, EncKDCRepPart **encAsRepPart)
{
	BOOL status = FALSE;
	switch(authInfo->type)
	{
	case KIWI_AUTH_INFOS_TYPE_KEY:
		status = kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_key(AsRep, encAsRepPart, &authInfo->u.userKey, EncASRepPart_PDU);
		break;
	case KIWI_AUTH_INFOS_TYPE_RSA:
	case KIWI_AUTH_INFOS_TYPE_OTF_RSA:
		status = kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_RSA(AsRep, &authInfo->u.certInfoDH.certinfo.provider, EncASRepPart_PDU, encAsRepPart);
		break;
	case KIWI_AUTH_INFOS_TYPE_RSA_DH:
	case KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH:
		status = kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_RSA_DH(AsRep, &authInfo->u.certInfoDH.dhKeyInfo, EncASRepPart_PDU, encAsRepPart);
		break;
	case KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH:
		status = kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_RSA_DH(AsRep, &authInfo->u.asReqDH.dhKeyInfo, EncASRepPart_PDU, encAsRepPart);
		break;
	}
	return status;
}

const struct _seqof2	suppEtypeRC4 = {NULL, KERB_ETYPE_RC4_HMAC_NT},
						suppEtypeAES128 = {(struct _seqof2 *) &suppEtypeRC4, KERB_ETYPE_AES128_CTS_HMAC_SHA1_96},
						suppEtypeAES256 = {(struct _seqof2 *) &suppEtypeAES128, KERB_ETYPE_AES256_CTS_HMAC_SHA1_96};
void kull_m_kerberos_asn1_helper_build_KdcReqBody(KDC_REQ_BODY *body, PCSTR cname, PCSTR Domain, DWORD Options, struct _seqof2 *suppEtype, PCSTR Service, PCSTR Target, PCSTR sDomain)
{
	RtlZeroMemory(body, sizeof(KDC_REQ_BODY));
	body->bit_mask = KDC_REQ_BODY_sname_present;
	body->kdc_options.length = sizeof(DWORD) * 8;
	body->kdc_options.value = (unsigned char *) LocalAlloc(LPTR, sizeof(DWORD));
	*(PDWORD) body->kdc_options.value = _byteswap_ulong(Options ? Options : KERB_KDCOPTION_standard);
	if(cname)
	{
		body->bit_mask |= KDC_REQ_BODY_cname_present;
		kull_m_kerberos_asn1_helper_init_PrincipalName(&body->cname, KRB_NT_PRINCIPAL, 1, cname);
	}
	body->realm = (Realm) (sDomain ? sDomain : Domain);
	kull_m_kerberos_asn1_helper_init_PrincipalName(&body->sname, KRB_NT_SRV_INST, 2, Service ? Service : "krbtgt", Target ? Target : Domain);
	kull_m_kerberos_asn1_helper_init_KerberosTime(&body->till, NULL, TRUE);
	body->nonce = MIMIKATZ_NONCE;
	body->etype = suppEtype ? suppEtype : (struct _seqof2 *) ((MIMIKATZ_NT_MAJOR_VERSION < 6) ? &suppEtypeRC4 : &suppEtypeAES256);
}

void kull_m_kerberos_asn1_helper_build_FreeReqBody(KDC_REQ_BODY *body)
{
	if(body->enc_authorization_data.cipher.value)
		LocalFree(body->enc_authorization_data.cipher.value);
	if(body->sname.name_string)
		LocalFree(body->sname.name_string);
	if(body->cname.name_string)
		LocalFree(body->cname.name_string);
	if(body->kdc_options.value)
		LocalFree(body->kdc_options.value);
}

BOOL kull_m_kerberos_asn1_helper_build_KdcReq_key(PCSTR Username, PCSTR Domain, EncryptionKey *key, PCSTR Service, PCSTR Target, PCSTR sDomain, BOOL PacRequest, Ticket *ticket, _octet1 *pac, OssBuf *OutKdcReq)
{
	BOOL status = FALSE;
	KDC_REQ req;
	PA_DATA PaGeneric, PaPacRequest;
	OssBuf AuthData;
	struct _seqof2 suppEtype = {NULL, key->keytype};
	BOOL isTgs = Service && ticket && key;
	DWORD Options = 0;

	OutKdcReq->length = 0;
	OutKdcReq->value = NULL;
	req.pvno = 5;
	req.msg_type = isTgs ? 12 : 10;

	if(Service && (strlen(Service) >= 2) && (Service[0] == '~'))
	{
		Options = KERB_KDCOPTION_standard | KERB_KDCOPTION_renew;
		Service++;
	}
	kull_m_kerberos_asn1_helper_build_KdcReqBody(&req.req_body, isTgs ? NULL : Username, Domain, Options, &suppEtype, Service, Target, sDomain);
	if(kull_m_kerberos_asn1_helper_init_PA_DATA_PacRequest(&PaPacRequest, PacRequest))
	{
		if(isTgs ? kull_m_kerberos_asn1_helper_init_PA_DATA_TGS_REQ(&PaGeneric, Username, Domain, ticket, key) : kull_m_kerberos_asn1_helper_init_PA_DATA_encTimeStamp(&PaGeneric, key))
		{
			kull_m_kerberos_asn1_helper_init_PADATAs(&req.padata, 2, &PaGeneric, &PaPacRequest);
			req.bit_mask = KDC_REQ_padata_present;

			if(isTgs && pac)
			{
				if(kull_m_kerberos_asn1_helper_build_AuthorizationData(&AuthData, pac))
				{
					if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt((ticket->enc_part.bit_mask & kvno_present) ? KRB_KEY_USAGE_AS_REQ_AUTHORIZATION_SESSION : KRB_KEY_USAGE_AS_DATA_ENCRYPTED_NO_SPEC, key, &AuthData, (OssBuf *) &req.req_body.enc_authorization_data.cipher, TRUE)))
					{
						req.req_body.bit_mask |= enc_authorization_data_present;
						req.req_body.enc_authorization_data.bit_mask = 0;
						req.req_body.enc_authorization_data.etype = key->keytype;
					}
					else PRINT_ERROR("Encrypt\n");
					ossFreeBuf(&world, AuthData.value);
				}
			}

			if(!(status = !ossEncode(&world, isTgs ? TGS_REQ_PDU : AS_REQ_PDU, &req, OutKdcReq)))
				PRINT_ERROR("%s\n", ossGetErrMsg(&world));

			if(req.padata)
				LocalFree(req.padata);
			if(PaGeneric.padata_value.value)
				ossFreeBuf(&world, PaGeneric.padata_value.value);
		}
		if(PaPacRequest.padata_value.value)
			ossFreeBuf(&world, PaPacRequest.padata_value.value);
	}
	kull_m_kerberos_asn1_helper_build_FreeReqBody(&req.req_body);
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_KdcReq_RSA(PCSTR Username, PCSTR Domain, PKULL_M_CRYPTO_CERT_INFO certInfo, PCSTR Service, PCSTR Target, KerberosTime *time, BOOL PacRequest, OssBuf *OutKdcReq)
{
	BOOL status = FALSE;
	KDC_REQ req;
	PA_DATA PaAuthPackOld, PaPacRequest;
	
	OutKdcReq->length = 0;
	OutKdcReq->value = NULL;
	req.pvno = 5;
	req.msg_type = 10;

	kull_m_kerberos_asn1_helper_build_KdcReqBody(&req.req_body, Username, Domain, 0, NULL, Service, Target, NULL);	
	if(kull_m_kerberos_asn1_helper_init_PA_DATA_PacRequest(&PaPacRequest, PacRequest))
	{
		if(kull_m_kerberos_asn1_helper_init_PA_DATA_PA_PK_AS_REQ_old(&PaAuthPackOld, Domain, time, certInfo))
		{
			kull_m_kerberos_asn1_helper_init_PADATAs(&req.padata, 2, &PaAuthPackOld, &PaPacRequest);
			req.bit_mask = KDC_REQ_padata_present;
			if(!(status = !ossEncode(&world, AS_REQ_PDU, &req, OutKdcReq)))
				PRINT_ERROR("%s\n", ossGetErrMsg(&world));
			if(req.padata)
				LocalFree(req.padata);
			if(PaAuthPackOld.padata_value.value)
				ossFreeBuf(&world, PaAuthPackOld.padata_value.value);
		}
		if(PaPacRequest.padata_value.value)
			ossFreeBuf(&world, PaPacRequest.padata_value.value);
	}
	kull_m_kerberos_asn1_helper_build_FreeReqBody(&req.req_body);
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_KdcReq_RSA_DH(PCSTR Username, PCSTR Domain, PKULL_M_CRYPTO_CERT_INFO certInfo, PKULL_M_CRYPTO_DH_KEY_INFO keyInfo, PCSTR Service, PCSTR Target, KerberosTime *time, BOOL PacRequest, OssBuf *OutKdcReq)
{
	BOOL status = FALSE;
	KDC_REQ req;
	PA_DATA PaAuthPack, PaPacRequest;

	OutKdcReq->length = 0;
	OutKdcReq->value = NULL;
	req.pvno = 5;
	req.msg_type = 10;
	
	kull_m_kerberos_asn1_helper_build_KdcReqBody(&req.req_body, Username, Domain, 0, NULL, Service, Target, NULL);	
	if(kull_m_kerberos_asn1_helper_init_PA_DATA_PacRequest(&PaPacRequest, PacRequest))
	{
		if(kull_m_kerberos_asn1_helper_init_PA_DATA_PA_PK_AS_REQ(&PaAuthPack, time, certInfo, keyInfo, NULL))
		{
			kull_m_kerberos_asn1_helper_init_PADATAs(&req.padata, 2, &PaAuthPack, &PaPacRequest);
			req.bit_mask = KDC_REQ_padata_present;
			if(!(status = !ossEncode(&world, AS_REQ_PDU, &req, OutKdcReq)))
				PRINT_ERROR("%s\n", ossGetErrMsg(&world));
			if(req.padata)
				LocalFree(req.padata);
			if(PaAuthPack.padata_value.value)
				ossFreeBuf(&world, PaAuthPack.padata_value.value);
		}
		if(PaPacRequest.padata_value.value)
			ossFreeBuf(&world, PaPacRequest.padata_value.value);
	}
	kull_m_kerberos_asn1_helper_build_FreeReqBody(&req.req_body);
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_key(KDC_REP *rep, EncKDCRepPart ** encRepPart, EncryptionKey *key, int pdu)
{
	BOOL status = FALSE;
	OssBuf EncRepPartBuff;
	*encRepPart = NULL;
	if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt(((pdu == EncASRepPart_PDU) && (key->keytype != KERB_ETYPE_RC4_HMAC_NT)) ? KRB_KEY_USAGE_AS_REP_EP_SESSION_KEY : KRB_KEY_USAGE_TGS_REP_EP_SESSION_KEY, key, (OssBuf *) &rep->enc_part.cipher, &EncRepPartBuff, FALSE)))
	{
		if(!(status = !ossDecode(&world, &pdu, &EncRepPartBuff, (LPVOID *) encRepPart)))
			PRINT_ERROR("Unable to decode EncASRepPart from REP: %s\n", ossGetErrMsg(&world));;
		LocalFree(EncRepPartBuff.value);
	}
	else PRINT_ERROR("Decrypt\n");
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_RSA(KDC_REP *rep, PKULL_M_CRYPTO_PROV_INFO provInfo, int pdu, EncKDCRepPart **encRepPart)
{
	BOOL status = FALSE;
	int internDpu = PA_PK_AS_REP_PDU;
	PA_DATA *paAsRepOld;
	OssBuf KeyData;
	PA_PK_AS_REP *pkAsRep = NULL;
	KERB_REPLY_KEY_PACKAGE *KeyPack = NULL;

	*encRepPart = NULL;

	if(paAsRepOld = kull_m_kerberos_asn1_helper_get_PADATA_from_REP(rep, PA_TYPE_PK_AS_REP_OLD))
	{
		if(!ossDecode(&world, &internDpu, (OssBuf *) &paAsRepOld->padata_value, (LPVOID *) &pkAsRep))
		{
			if(pkAsRep->choice == encKeyPack_chosen)
			{
				if(kull_m_crypto_simple_message_dec(provInfo, &pkAsRep->u.encKeyPack, &KeyData))
				{
					internDpu = KERB_REPLY_KEY_PACKAGE_PDU;
					if(!ossDecode(&world, &internDpu, &KeyData, (LPVOID *) &KeyPack))
					{
						status = kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_key(rep, encRepPart, &KeyPack->replyKey, pdu);
						ossFreePDU(&world, KERB_REPLY_KEY_PACKAGE_PDU, KeyPack);
					}
					else PRINT_ERROR("Unable to decode KERB_REPLY_KEY_PACKAGE from encKeyPack: %s\n", ossGetErrMsg(&world));;
					LocalFree(KeyData.value);
				}
			}
			else PRINT_ERROR("PA_PK_AS_REP (old) is not encKeyPack\n");
			ossFreePDU(&world, PA_PK_AS_REP_PDU, pkAsRep);
		}
		else PRINT_ERROR("Unable to decode PA_PK_AS_REP from REP: %s\n", ossGetErrMsg(&world));;
	}
	return status;
}

void reverseit(PVOID data, DWORD dwData)
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

BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_RSA_DH(KDC_REP *rep, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, int pdu, EncKDCRepPart **encRepPart)
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

	if(paAsRep = kull_m_kerberos_asn1_helper_get_PADATA_from_REP(rep, PA_TYPE_PK_AS_REP))
	{
		if(!ossDecode(&world, &internDpu, (OssBuf *) &paAsRep->padata_value, (LPVOID *) &pkAsRep))
		{
			if(pkAsRep->choice == dhInfo_chosen)
			{
				if((!(dhKeyInfo->dhClientNonce.length && dhKeyInfo->dhClientNonce.value) == !(pkAsRep->u.dhInfo.bit_mask & serverDHNonce_present))
					||
					((dhKeyInfo->dhClientNonce.length && dhKeyInfo->dhClientNonce.value) && (pkAsRep->u.dhInfo.bit_mask & serverDHNonce_present)))
				{
					//if(pkAsRep->u.dhInfo.bit_mask & serverDHNonce_present)
					//{
					//	kprintf("(-) Server nonce:\n"); kull_m_string_printf_hex(pkAsRep->u.dhInfo.serverDHNonce.value, pkAsRep->u.dhInfo.serverDHNonce.length, 0 | (32 << 16)); kprintf("\n");
					//}
					if(kull_m_crypto_simple_message_get(&pkAsRep->u.dhInfo.dhSignedData, &buffer))
					{
						internDpu = KDCDHKeyInfo_PDU;
						if(!ossDecode(&world, &internDpu, &buffer, (LPVOID *) &keyInfo))
						{
							if(kull_m_crypto_genericDecode(X509_DH_PUBLICKEY, keyInfo->subjectPublicKey.value, keyInfo->subjectPublicKey.length / 8, (LPVOID *) &pIntegerBlob))
							{
								//kprintf("(W) Server Public key:\n"); kull_m_string_printf_hex(pIntegerBlob->pbData, pIntegerBlob->cbData, 0 | (32 << 16)); kprintf("\n");
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
													//kprintf("(W) SessionKey:\n"); kull_m_string_printf_hex(pSessionKey, dwSessionKey, 0 | (32 << 16)); kprintf("\n");
													reverseit(pSessionKey, dwSessionKey);
													//kprintf("(-) SessionKey:\n"); kull_m_string_printf_hex(pSessionKey, dwSessionKey, 0 | (32 << 16)); kprintf("\n");
													if(octetstring2key(pSessionKey, dwSessionKey, &dhKeyInfo->dhClientNonce, (pkAsRep->u.dhInfo.bit_mask & serverDHNonce_present) ? &pkAsRep->u.dhInfo.serverDHNonce : NULL, &eKey))
													{
														//kprintf("(-) Kerberos key (%s):\n", kull_m_kerberos_asn1_helper_util_etypeToString(eKey.keytype)); kull_m_string_printf_hex(eKey.keyvalue.value, eKey.keyvalue.length, 0 | (32 << 16)); kprintf("\n");
														status = kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_key(rep, encRepPart, &eKey, pdu);
														LocalFree(eKey.keyvalue.value);
													}
												}
												LocalFree(pSessionKey);
											}
										}
										else PRINT_ERROR_AUTO("CryptGetKeyParam");
										CryptDestroyKey(hSessionKey);
									}
									else PRINT_ERROR_AUTO("CryptImportKey");
									LocalFree(PublicKey);
								}
							}
							ossFreePDU(&world, KDCDHKeyInfo_PDU, keyInfo);
						}
						LocalFree(buffer.value);
					}
				}
				else PRINT_ERROR("Illogic nonce between client and server\n");
			}
			else PRINT_ERROR("PA_PK_AS_REP is not dhInfo\n");
			ossFreePDU(&world, PA_PK_AS_REP_PDU, pkAsRep);
		}
		else PRINT_ERROR("Unable to decode PA_PK_AS_REP from REP: %s\n", ossGetErrMsg(&world));;
	}
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_ApReq(OssBuf * ApReqData, PCSTR Username, PCSTR Domain, Ticket *ticket, EncryptionKey *key, ULONG keyUsage, EncryptionKey *authenticatorNewKey, UInt32 *authenticatorNewSeq)
{
	BOOL status = FALSE;
	AP_REQ req;
	Authenticator authenticator;
	DWORD apOptions = 0;
	OssBuf encodedAuthenticator = {0, NULL};

	ApReqData->length = 0;
	ApReqData->value = NULL;

	req.pvno = 5;
	req.msg_type = 14;
	req.ap_options.length = sizeof(apOptions) * 8;
	req.ap_options.value = (unsigned char *) &apOptions;
	req.ticket = *ticket;
	req.authenticator.bit_mask = 0;
	req.authenticator.etype = key->keytype;
	req.authenticator.cipher.length = 0;
	req.authenticator.cipher.value = NULL;

	authenticator.bit_mask = 0;
	authenticator.authenticator_vno = 5;
	authenticator.crealm = (Realm) Domain;
	kull_m_kerberos_asn1_helper_init_PrincipalName(&authenticator.cname, KRB_NT_PRINCIPAL, 1, Username);
	authenticator.cusec = 0;
	kull_m_kerberos_asn1_helper_init_KerberosTime(&authenticator.ctime, NULL, FALSE);

	if(authenticatorNewKey)
	{
		*authenticatorNewKey = *key;
		authenticatorNewKey->keyvalue.value = NULL;
		if(authenticatorNewKey->keyvalue.value = (unsigned char * ) LocalAlloc(LPTR, authenticatorNewKey->keyvalue.length))
		{
			if(NT_SUCCESS(CDGenerateRandomBits(authenticatorNewKey->keyvalue.value, authenticatorNewKey->keyvalue.length)))
			{
				authenticator.subkey = *authenticatorNewKey;
				authenticator.bit_mask |= Authenticator_subkey_present;
			}
			else
			{
				authenticatorNewKey->keyvalue.value = (unsigned char * )LocalFree(authenticatorNewKey->keyvalue.value);
				PRINT_ERROR("GenerateRandom\n");
			}
		}
	}

	if(authenticatorNewSeq)
	{
		authenticator.seq_number = *authenticatorNewSeq = MIMIKATZ_NONCE;
		authenticator.bit_mask |= Authenticator_seq_number_present;
	}

	if(!ossEncode(&world, Authenticator_PDU, &authenticator, &encodedAuthenticator))
	{
		if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt(keyUsage, key, &encodedAuthenticator, (OssBuf *) &req.authenticator.cipher, TRUE)))
		{
			if(!(status = !ossEncode(&world, AP_REQ_PDU, &req, ApReqData)))
				 PRINT_ERROR("Unable to encode AP_REQ: %s\n", ossGetErrMsg(&world));
			LocalFree(req.authenticator.cipher.value);
		}
		else PRINT_ERROR("Encrypt\n");
		ossFreeBuf(&world, encodedAuthenticator.value);
	}
	else PRINT_ERROR("Unable to encode Authenticator: %s\n", ossGetErrMsg(&world));

	if(authenticator.cname.name_string)
		LocalFree(authenticator.cname.name_string);

	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_AuthorizationData(OssBuf * AuthData, _octet1 *pac)
{
	BOOL status = FALSE;
	OssBuf adPacBuff = {0, NULL};
	struct AuthorizationData adIf = {NULL, {AD_TYPE_IF_RELEVANT}}, adPac = {NULL, {AD_TYPE_WIN2K_PAC}}, adRoot = {NULL, {0, {0, NULL}}};

	*AuthData = adPacBuff;// to do !!!

	adPac.value.ad_data = *pac;
	adRoot.next = &adPac;
	if(!ossEncode(&world, AD_IF_RELEVANT_PDU, &adRoot, &adPacBuff))
	{
		adIf.value.ad_data = *(_octet1 *) &adPacBuff;
		adRoot.next = &adIf;
		status = !ossEncode(&world, AD_IF_RELEVANT_PDU, &adRoot, AuthData);
		ossFreeBuf(&world, adPacBuff.value);
	}
	if(!status)
		PRINT_ERROR("Unable to encode AD_IF_RELEVANT: %s\n", ossGetErrMsg(&world));
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_KrbPriv(_octet1 *data, EncryptionKey *key, PCSTR machineName, OssBuf *OutKrbPriv, UInt32 *seq)
{
	BOOL status = FALSE;
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

	if(!ossEncode(&world, EncKrbPrivPart_PDU, &encPart, &bufEncPart))
	{
		if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt(KRB_KEY_USAGE_KRB_PRIV_ENCRYPTED_PART, key, &bufEncPart, (OssBuf *) &kPriv.enc_part.cipher, TRUE)))
		{
			if(!(status = !ossEncode(&world, KRB_PRIV_PDU, &kPriv, OutKrbPriv)))
				PRINT_ERROR("Unable to encode KRB_PRIV: %s\n", ossGetErrMsg(&world));
			LocalFree(kPriv.enc_part.cipher.value);
		}
		else PRINT_ERROR("Encrypt\n");
		ossFreeBuf(&world, bufEncPart.value);
	}
	else PRINT_ERROR("Unable to encode EncKrbPrivPart: %s\n", ossGetErrMsg(&world));
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_KrbCred(Realm *prealm, PrincipalName *pname, EncKDCRepPart *repPart, Ticket *ticket, OssBuf *OutKrbCred)
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
		seqTicket.value = *ticket;
	cred.enc_part.bit_mask = 0;
	cred.enc_part.etype = KERB_ETYPE_NULL;
	cred.enc_part.cipher.length = 0;
	cred.enc_part.cipher.value = NULL;

	encKrbCredPart.bit_mask = 0;
	encKrbCredPart.ticket_info = &krbCredInfo;

	krbCredInfo.next = NULL;
	krbCredInfo.value.bit_mask = pname_present | flags_present | KrbCredInfo_starttime_present | endtime_present | KrbCredInfo_renew_till_present | KrbCredInfo_sname_present;

	krbCredInfo.value.key = repPart->key;
	krbCredInfo.value.prealm = *prealm;
	krbCredInfo.value.pname = *pname;

	krbCredInfo.value.flags = repPart->flags;
	krbCredInfo.value.starttime = repPart->starttime;
	krbCredInfo.value.endtime = repPart->endtime;
	krbCredInfo.value.renew_till = repPart->renew_till;

	krbCredInfo.value.sname = repPart->sname;
	krbCredInfo.value.srealm = repPart->srealm;
	
	if(!ossEncode(&world, EncKrbCredPart_PDU, &encKrbCredPart, (OssBuf *) &cred.enc_part.cipher))
	{
		status = !ossEncode(&world, KRB_CRED_PDU, &cred, OutKrbCred);
		ossFreeBuf(&world, cred.enc_part.cipher.value);
	}
	if(!status)
		PRINT_ERROR("Unable to encode EncKrbCredPart or KRB_CRED: %s\n", ossGetErrMsg(&world));
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_EncKrbPrivPart_from_Priv(KRB_PRIV *priv, EncKrbPrivPart ** encKrbPrivPart, EncryptionKey *authKey)
{
	BOOL status = FALSE;
	OssBuf encKrbPrivPartBuff;
	int pdu = EncKrbPrivPart_PDU;
	*encKrbPrivPart = NULL;

	if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt(KRB_KEY_USAGE_KRB_PRIV_ENCRYPTED_PART, authKey, (OssBuf *) &priv->enc_part.cipher, &encKrbPrivPartBuff, FALSE)))
	{
		if(!(status = !ossDecode(&world, &pdu, &encKrbPrivPartBuff, (LPVOID *) encKrbPrivPart)))
			PRINT_ERROR("Unable to decode EncKrbPrivPart from REP: %s\n", ossGetErrMsg(&world));;
		LocalFree(encKrbPrivPartBuff.value);
	}
	else PRINT_ERROR("Encrypt\n");
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_AuthPackOld(OssBuf *AuthPackOld, PCSTR Domain, KerberosTime *time)
{
	BOOL status = FALSE;
	AuthPack_OLD auth = {0};
	AuthPackOld->length = 0;
	AuthPackOld->value = NULL;
	kull_m_kerberos_asn1_helper_init_PrincipalName(&auth.pkAuthenticator.kdc_name, KRB_NT_SRV_INST, 2, "krbtgt", Domain);
	auth.pkAuthenticator.kdc_realm = (Realm) Domain;
	auth.pkAuthenticator.cusec = 0;
	if(time)
		auth.pkAuthenticator.ctime = *time;
	else
		kull_m_kerberos_asn1_helper_init_KerberosTime(&auth.pkAuthenticator.ctime, NULL, FALSE);
	auth.pkAuthenticator.nonce = MIMIKATZ_NONCE;

	if(!(status = !ossEncode(&world, AuthPack_OLD_PDU, &auth, AuthPackOld)))
		PRINT_ERROR("Unable to encode AuthPack_OLD: %s\n", ossGetErrMsg(&world));
	if(auth.pkAuthenticator.kdc_name.name_string)
		LocalFree(auth.pkAuthenticator.kdc_name.name_string);
	return status;
}

const BYTE sha_req[SHA_DIGEST_LENGTH] = {0}; // Windows does not check? :))
const BYTE oidDhPublicNumber[] = {0x2a, 0x86, 0x48, 0xce, 0x3e, 0x02, 0x01};
BOOL kull_m_kerberos_asn1_helper_build_AuthPack(OssBuf *authPack, KerberosTime *time, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, PSHA_DIGEST digest)
{
	BOOL status = FALSE;
	AuthPack auth;
	DWORD szPublicKey = 0;
	PUBLICKEYSTRUC *PublicKey;
	CRYPT_INTEGER_BLOB integerBlob;
	CERT_X942_DH_PARAMETERS parameters;
	authPack->length = 0;
	authPack->value = NULL;

	if(kull_m_crypto_get_DHKeyInfo_Parameters(dhKeyInfo->hKey, &parameters))
	{
		//kprintf("(W) Client P param:\n"); kull_m_string_printf_hex(parameters.p.pbData, parameters.p.cbData, 0 | (32 << 16)); kprintf("\n");
		//kprintf("(W) Client G param:\n"); kull_m_string_printf_hex(parameters.g.pbData, parameters.g.cbData, 0 | (32 << 16)); kprintf("\n");
		if(kull_m_crypto_genericEncode(X509_DH_PARAMETERS, &parameters, &auth.clientPublicValue.algorithm.parameters.value, (PDWORD) &auth.clientPublicValue.algorithm.parameters.length))
		{
			if(CryptExportKey(dhKeyInfo->hKey, 0, PUBLICKEYBLOB, 0, NULL, &szPublicKey))
			{
				if(PublicKey = (PUBLICKEYSTRUC *) LocalAlloc(LPTR, szPublicKey))
				{
					if(CryptExportKey(dhKeyInfo->hKey, 0, PUBLICKEYBLOB, 0, (PBYTE) PublicKey, &szPublicKey))
					{
						integerBlob.cbData = szPublicKey - (sizeof(PUBLICKEYSTRUC) + sizeof(DHPUBKEY));
						integerBlob.pbData = (PBYTE) PublicKey + (sizeof(PUBLICKEYSTRUC) + sizeof(DHPUBKEY));
						//kprintf("(W) Client Public Key:\n"); kull_m_string_printf_hex(integerBlob.pbData, integerBlob.cbData, 0 | (32 << 16)); kprintf("\n");

						if(kull_m_crypto_genericEncode(X509_DH_PUBLICKEY, &integerBlob, &auth.clientPublicValue.subjectPublicKey.value, (PDWORD) &auth.clientPublicValue.subjectPublicKey.length))
						{
							auth.bit_mask = clientPublicValue_present;
							if(dhKeyInfo->dhClientNonce.length && dhKeyInfo->dhClientNonce.value)
								auth.bit_mask |= clientDHNonce_present;

							auth.pkAuthenticator.bit_mask = paChecksum_present;
							auth.pkAuthenticator.cusec = 0;
							if(time)
								auth.pkAuthenticator.ctime = *time;
							else
								kull_m_kerberos_asn1_helper_init_KerberosTime(&auth.pkAuthenticator.ctime, NULL, FALSE);
							auth.pkAuthenticator.nonce = MIMIKATZ_NONCE;
							auth.pkAuthenticator.paChecksum.length = SHA_DIGEST_LENGTH;
							auth.pkAuthenticator.paChecksum.value = digest ? digest->digest : (PBYTE) sha_req;

							auth.clientPublicValue.algorithm.bit_mask = parameters_present;
							auth.clientPublicValue.algorithm.algorithm.length = sizeof(oidDhPublicNumber);
							auth.clientPublicValue.algorithm.algorithm.value = (PBYTE) oidDhPublicNumber;

							auth.clientPublicValue.subjectPublicKey.length *= 8; // in bits

							if(auth.bit_mask & clientDHNonce_present)
							//{
								auth.clientDHNonce = dhKeyInfo->dhClientNonce;
							//	kprintf("(-) Client Nonce:\n"); kull_m_string_printf_hex(auth.clientDHNonce.value, auth.clientDHNonce.length, 0 | (32 << 16)); kprintf("\n");
							//}
							if(!(status = !ossEncode(&world, AuthPack_PDU, &auth, authPack)))
								kull_m_kerberos_asn1_helper_ossFreeBuf(authPack->value);

							LocalFree(auth.clientPublicValue.subjectPublicKey.value);
						}
					}
					LocalFree(PublicKey);
				}
			}
			LocalFree(auth.clientPublicValue.algorithm.parameters.value);
		}
		kull_m_crypto_free_DHKeyInfo_Parameters(&parameters);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_AuthPackOld_signed(_octet1 * signedInfo, PCSTR Domain, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo)
{
	BOOL status = FALSE;
	OssBuf AuthPackOld = {0, NULL};
	signedInfo->length = 0;
	signedInfo->value = NULL;
	if(kull_m_kerberos_asn1_helper_build_AuthPackOld(&AuthPackOld, Domain, time))
	{
		status = kull_m_crypto_simple_message_sign(certSignInfo, &AuthPackOld, signedInfo);
		ossFreeBuf(&world, AuthPackOld.value);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_AuthPack_signed(_octet1 * signedInfo, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, PSHA_DIGEST digest)
{
	BOOL status = FALSE;
	OssBuf AuthPack = {0, NULL};
	signedInfo->length = 0;
	signedInfo->value = NULL;
	if(kull_m_kerberos_asn1_helper_build_AuthPack(&AuthPack, time, dhKeyInfo, digest))
	{
		status = kull_m_crypto_simple_message_sign(certSignInfo, &AuthPack, signedInfo);
		ossFreeBuf(&world, AuthPack.value);
	}
	return status;
}

NTSTATUS kull_m_kerberos_asn1_helper_util_encrypt(ULONG keyUsage, EncryptionKey *key, OssBuf *in, OssBuf *out, BOOL encrypt)
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

NTSTATUS kull_m_kerberos_asn1_helper_util_stringToKey(PCSTR user, PCSTR domain, PCSTR password, PCSTR key, EncryptionKey *eKey)
{
	NTSTATUS status;
	PKERB_ECRYPT pCSystem;
	STRING aUser, aDomain, aPassword;
	UNICODE_STRING uUser, uDomain, uPassword, uSalt = {0, 0, NULL};

	status = CDLocateCSystem(eKey->keytype, &pCSystem);
	if(NT_SUCCESS(status))
	{
		eKey->keyvalue.length = pCSystem->KeySize;
		if(eKey->keyvalue.value = (unsigned char * ) LocalAlloc(LPTR, eKey->keyvalue.length))
		{
			if(key)
			{
				if(!kull_m_string_stringToHex(key, eKey->keyvalue.value, eKey->keyvalue.length))
				{
					PRINT_ERROR("key size length must be %u (%u bytes) for %s\n", pCSystem->KeySize * 2, pCSystem->KeySize, kull_m_kerberos_asn1_helper_util_etypeToString(eKey->keytype));
					status = STATUS_WRONG_PASSWORD;
				}
			}
			else
			{
				RtlInitString(&aUser, user);
				RtlInitString(&aDomain, domain);
				RtlInitString(&aPassword, password);
				status = RtlAnsiStringToUnicodeString(&uUser, &aUser, TRUE);
				if(NT_SUCCESS(status))
				{
					status = RtlAnsiStringToUnicodeString(&uDomain, &aDomain, TRUE);
					if(NT_SUCCESS(status))
					{
						status = RtlAnsiStringToUnicodeString(&uPassword, &aPassword, TRUE);
						if(NT_SUCCESS(status))
						{
							RtlUpcaseUnicodeString(&uDomain, &uDomain, FALSE);
							uSalt.MaximumLength = uUser.Length + uDomain.Length + sizeof(wchar_t);
							if(uSalt.Buffer = (PWSTR) LocalAlloc(LPTR, uSalt.MaximumLength))
							{
								RtlAppendUnicodeStringToString(&uSalt, &uDomain);
								RtlAppendUnicodeStringToString(&uSalt, &uUser);
								status = (MIMIKATZ_NT_MAJOR_VERSION < 6) ? pCSystem->HashPassword_NT5(&uPassword, eKey->keyvalue.value) : pCSystem->HashPassword_NT6(&uPassword, &uSalt, 4096, eKey->keyvalue.value);
								if(!NT_SUCCESS(status))
									PRINT_ERROR("HashPassword: %08x\n", status);
								LocalFree(uSalt.Buffer);
							}
							RtlFreeUnicodeString(&uPassword);
						}
						RtlFreeUnicodeString(&uDomain);
					}
					RtlFreeUnicodeString(&uUser);
				}
			}
			if(!NT_SUCCESS(status))
				LocalFree(eKey->keyvalue.value);
		}
	}
	else PRINT_ERROR("LocateCSystem: %08x\n", status);
	return status;
}

PCSTR kull_m_kerberos_asn1_helper_util_etypeToString(LONG eType)
{
	PCSTR type;
	switch(eType)
	{
	case KERB_ETYPE_RC4_HMAC_NT:					type = "rc4_hmac_nt"; break;
	case KERB_ETYPE_AES128_CTS_HMAC_SHA1_96:		type = "aes128_hmac"; break;
	case KERB_ETYPE_AES256_CTS_HMAC_SHA1_96:		type = "aes256_hmac"; break;
	default:										type = "unknow     "; break;
	}
	return type;
}

BOOL kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(OssBuf *data, int pdu, LPVOID *out)
{
	BOOL status = FALSE;
	KRB_ERROR *error = NULL;

	if(!(status = !ossDecode(&world, &pdu, data, out)))
	{
		pdu = KRB_ERROR_PDU;
		if(!ossDecode(&world, &pdu, data, (LPVOID *) &error))
		{
			kprintf("%s (%u) - ", kull_m_kerberos_asn1_helper_util_err_to_string(error->error_code), error->error_code);
			kull_m_kerberos_asn1_helper_display_KerberosTime(&error->stime);
			kprintf("\n");
			ossFreePDU(&world, pdu, error);
		}
		else PRINT_ERROR("Unable to decode KRB Packet: %s\n", ossGetErrMsg(&world));
	}
	return status;
}

const KULL_M_KERBEROS_ASN1_HELPER_UTIL_ERR kull_m_kerberos_asn1_helper_util_err[] = {
	{0,		"KDC_ERR_NONE"},
	{1,		"KDC_ERR_NAME_EXP"},
	{2,		"KDC_ERR_SERVICE_EXP"},
	{3,		"KDC_ERR_BAD_PVNO"},
	{4,		"KDC_ERR_C_OLD_MAST_KVNO"},
	{5,		"KDC_ERR_S_OLD_MAST_KVNO"},
	{6,		"KDC_ERR_C_PRINCIPAL_UNKNOWN"},
	{7,		"KDC_ERR_S_PRINCIPAL_UNKNOWN"},
	{8,		"KDC_ERR_PRINCIPAL_NOT_UNIQUE"},
	{9,		"KDC_ERR_NULL_KEY"},
	{10,	"KDC_ERR_CANNOT_POSTDATE"},
	{11,	"KDC_ERR_NEVER_VALID"},
	{12,	"KDC_ERR_POLICY"},
	{13,	"KDC_ERR_BADOPTION"},
	{14,	"KDC_ERR_ETYPE_NOSUPP"},
	{15,	"KDC_ERR_SUMTYPE_NOSUPP"},
	{16,	"KDC_ERR_PADATA_TYPE_NOSUPP"},
	{17,	"KDC_ERR_TRTYPE_NOSUPP"},
	{18,	"KDC_ERR_CLIENT_REVOKED"},
	{19,	"KDC_ERR_SERVICE_REVOKED"},
	{20,	"KDC_ERR_TGT_REVOKED"},
	{21,	"KDC_ERR_CLIENT_NOTYET"},
	{22,	"KDC_ERR_SERVICE_NOTYET"},
	{23,	"KDC_ERR_KEY_EXPIRED"},
	{24,	"KDC_ERR_PREAUTH_FAILED"},
	{25,	"KDC_ERR_PREAUTH_REQUIRED"},
	{26,	"KDC_ERR_SERVER_NOMATCH"},
	{27,	"KDC_ERR_MUST_USE_USER2USER"},
	{28,	"KDC_ERR_PATH_NOT_ACCEPTED"},
	{29,	"KDC_ERR_SVC_UNAVAILABLE"},
	{31,	"KRB_AP_ERR_BAD_INTEGRITY"},
	{32,	"KRB_AP_ERR_TKT_EXPIRED"},
	{33,	"KRB_AP_ERR_TKT_NYV"},
	{34,	"KRB_AP_ERR_REPEAT"},
	{35,	"KRB_AP_ERR_NOT_US"},
	{36,	"KRB_AP_ERR_BADMATCH"},
	{37,	"KRB_AP_ERR_SKEW"},
	{38,	"KRB_AP_ERR_BADADDR"},
	{39,	"KRB_AP_ERR_BADVERSION"},
	{40,	"KRB_AP_ERR_MSG_TYPE"},
	{41,	"KRB_AP_ERR_MODIFIED"},
	{42,	"KRB_AP_ERR_BADORDER"},
	{44,	"KRB_AP_ERR_BADKEYVER"},
	{45,	"KRB_AP_ERR_NOKEY"},
	{46,	"KRB_AP_ERR_MUT_FAIL"},
	{47,	"KRB_AP_ERR_BADDIRECTION"},
	{48,	"KRB_AP_ERR_METHOD"},
	{49,	"KRB_AP_ERR_BADSEQ"},
	{50,	"KRB_AP_ERR_INAPP_CKSUM"},
	{51,	"KRB_AP_PATH_NOT_ACCEPTED"},
	{52,	"KRB_ERR_RESPONSE_TOO_BIG"},
	{60,	"KRB_ERR_GENERIC"},
	{61,	"KRB_ERR_FIELD_TOOLONG"},
	{62,	"KDC_ERROR_CLIENT_NOT_TRUSTED"},
	{63,	"KDC_ERROR_KDC_NOT_TRUSTED"},
	{64,	"KDC_ERROR_INVALID_SIG"},
	{65,	"KDC_ERR_KEY_TOO_WEAK"},
	{66,	"KDC_ERR_CERTIFICATE_MISMATCH"},
	{67,	"KRB_AP_ERR_NO_TGT"},
	{68,	"KDC_ERR_WRONG_REALM"},
	{69,	"KRB_AP_ERR_USER_TO_USER_REQUIRED"},
	{70,	"KDC_ERR_CANT_VERIFY_CERTIFICATE"},
	{71,	"KDC_ERR_INVALID_CERTIFICATE"},
	{72,	"KDC_ERR_REVOKED_CERTIFICATE"},
	{73,	"KDC_ERR_REVOCATION_STATUS_UNKNOWN"},
	{74,	"KDC_ERR_REVOCATION_STATUS_UNAVAILABLE"},
	{75,	"KDC_ERR_CLIENT_NAME_MISMATCH"},
	{76,	"KDC_ERR_KDC_NAME_MISMATCH"},
};

PCSTR kull_m_kerberos_asn1_helper_util_err_to_string(DWORD id)
{
	DWORD i;
	for(i = 0; i < ARRAYSIZE(kull_m_kerberos_asn1_helper_util_err); i++)
		if(kull_m_kerberos_asn1_helper_util_err[i].id == id)
			return kull_m_kerberos_asn1_helper_util_err[i].name;
	return "ERROR ?";
}