/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "kull_m_kerberos_asn1_helper.h"

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
	pSystemTime->wMilliseconds = 0;
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

int kull_m_kerberos_asn1_helper_init_PA_DATA_encTimeStamp(PA_DATA *data, EncryptionKey *key)
{
	int retCode;
	PA_ENC_TS_ENC tsEnc;
	PA_ENC_TIMESTAMP timeStampEnc;
	OssBuf encodedTsEnc = {0, NULL}, encodedTimeStamp = {0, NULL};

	tsEnc.bit_mask = 0;
	timeStampEnc.bit_mask = 0;
	timeStampEnc.etype = key->keytype;
	
	kull_m_kerberos_asn1_helper_init_KerberosTime(&tsEnc.patimestamp, NULL, FALSE);
	retCode = ossEncode(&world, PA_ENC_TS_ENC_PDU, &tsEnc, &encodedTsEnc);
	if(!retCode)
	{
		if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt(KRB_KEY_USAGE_AS_REQ_PA_ENC_TIMESTAMP, key, &encodedTsEnc, (OssBuf *) &timeStampEnc.cipher, TRUE)))
		{
			retCode = ossEncode(&world, PA_ENC_TIMESTAMP_PDU, &timeStampEnc, &encodedTimeStamp);
			if(!retCode)
			{
				data->padata_type = PA_TYPE_ENC_TIMESTAMP;
				data->padata_value.length = encodedTimeStamp.length;
				data->padata_value.value = encodedTimeStamp.value;
			}
			LocalFree(timeStampEnc.cipher.value);
		}
		else PRINT_ERROR("Encrypt\n");
		ossFreeBuf(&world, encodedTsEnc.value);
	}
	if(retCode)
		PRINT_ERROR("%s\n", ossGetErrMsg(&world));
	return retCode;
}

int kull_m_kerberos_asn1_helper_init_PA_DATA_PacRequest(PA_DATA *data, BOOL request)
{
	int retCode;
	KERB_PA_PAC_REQUEST pacRequest = {request};
	OssBuf encodedReq = {0, NULL};

	retCode = ossEncode(&world, KERB_PA_PAC_REQUEST_PDU, &pacRequest, &encodedReq);
	if(!retCode)
	{
		data->padata_type = PA_TYPE_PAC_REQUEST;
		data->padata_value.length = encodedReq.length;
		data->padata_value.value = encodedReq.value;
	}
	else PRINT_ERROR("%s\n", ossGetErrMsg(&world));
	return retCode;
}

BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_TGS_REQ(PA_DATA *data, PCSTR Username, PCSTR Domain, Ticket *ticket, EncryptionKey *key)
{
	BOOL status = FALSE;
	OssBuf encodedReq;

	data->padata_value.value = NULL;
	if(status = kull_m_kerberos_asn1_helper_build_ApReq(&encodedReq, Username, Domain, ticket, key, KRB_KEY_USAGE_TGS_REQ_PA_AUTHENTICATOR, NULL, NULL))
	{
		data->padata_type = PA_TYPE_TGS_REQ;
		data->padata_value.length = encodedReq.length;
		data->padata_value.value = encodedReq.value;
	}
	return status;
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

BOOL kull_m_kerberos_asn1_helper_build_ApReq(OssBuf * ApReqData, PCSTR Username, PCSTR Domain, Ticket *ticket, EncryptionKey *key, ULONG keyUsage, EncryptionKey *authenticatorNewKey, UInt32 *authenticatorNewSeq)
{
	BOOL status = FALSE;
	int retCode;
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
		authenticator.seq_number = *authenticatorNewSeq = 1702257953;
		authenticator.bit_mask |= Authenticator_seq_number_present;
	}

	retCode = ossEncode(&world, Authenticator_PDU, &authenticator, &encodedAuthenticator);
	if(!retCode)
	{
		if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt(keyUsage, key, &encodedAuthenticator, (OssBuf *) &req.authenticator.cipher, TRUE)))
		{
			status = !ossEncode(&world, AP_REQ_PDU, &req, ApReqData);
			LocalFree(req.authenticator.cipher.value);
		}
		else PRINT_ERROR("Encrypt\n");
		ossFreeBuf(&world, encodedAuthenticator.value);
	}

	if(authenticator.cname.name_string)
		LocalFree(authenticator.cname.name_string);
	if(!status)
		PRINT_ERROR("%s\n", ossGetErrMsg(&world));

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
		PRINT_ERROR("%s\n", ossGetErrMsg(&world));
	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_KdcReq(PCSTR Username, PCSTR Domain, EncryptionKey *key, PCSTR Service, PCSTR Target, BOOL PacRequest, Ticket *ticket, _octet1 *pac, OssBuf *OutKdcReq)
{
	BOOL status = FALSE;
	KDC_REQ req;
	PA_DATA PaEncTimeStamp, PaPacRequest, PaTgsReq;
	OssBuf AuthData;
	struct _seqof2 suppEtype = {NULL, key->keytype};
	BOOL isTgs = Service && ticket;
	DWORD kdcOptions = _byteswap_ulong(0x40800010/*0x40810010*/);//isTgs ? 0x40810010/*40810000*/ : 0x40810010);
	
	OutKdcReq->length = 0;
	OutKdcReq->value = NULL;
	
	req.bit_mask = KDC_REQ_padata_present;
	req.pvno = 5;
	req.msg_type = isTgs ? 12 : 10;

	kull_m_kerberos_asn1_helper_init_PA_DATA_PacRequest(&PaPacRequest, PacRequest);
	if(isTgs)
	{
		kull_m_kerberos_asn1_helper_init_PA_DATA_TGS_REQ(&PaTgsReq, Username, Domain, ticket, key);
		kull_m_kerberos_asn1_helper_init_PADATAs(&req.padata, 2, &PaTgsReq, &PaPacRequest);

		PaEncTimeStamp.padata_value.value = NULL;
	}
	else
	{
		kull_m_kerberos_asn1_helper_init_PA_DATA_encTimeStamp(&PaEncTimeStamp, key);
		kull_m_kerberos_asn1_helper_init_PADATAs(&req.padata, 2, &PaEncTimeStamp, &PaPacRequest);

		PaTgsReq.padata_value.value = NULL;
	}

	req.req_body.bit_mask = KDC_REQ_BODY_sname_present;
	req.req_body.kdc_options.length = sizeof(kdcOptions) * 8;
	req.req_body.kdc_options.value = (unsigned char *) &kdcOptions;
	
	if(isTgs)
	{
		req.req_body.cname.name_string = NULL;
	}
	else
	{
		req.req_body.bit_mask |= KDC_REQ_BODY_cname_present;
		kull_m_kerberos_asn1_helper_init_PrincipalName(&req.req_body.cname, KRB_NT_PRINCIPAL, 1, Username);
	}
	
	req.req_body.realm = (Realm) Domain;
	kull_m_kerberos_asn1_helper_init_PrincipalName(&req.req_body.sname, KRB_NT_SRV_INST, 2, Service ? Service : "krbtgt", Target ? Target : Domain);
	kull_m_kerberos_asn1_helper_init_KerberosTime(&req.req_body.till, NULL, TRUE);
	req.req_body.nonce = 1702257953;
	req.req_body.etype = &suppEtype;

	req.req_body.enc_authorization_data.cipher.value = NULL;
	if(isTgs && pac)
	{
		if(kull_m_kerberos_asn1_helper_build_AuthorizationData(&AuthData, pac))
		{
			if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_encrypt(KRB_KEY_USAGE_AS_REQ_AUTHORIZATION_SESSION, key, &AuthData, (OssBuf *) &req.req_body.enc_authorization_data.cipher, TRUE)))
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

	if(PaEncTimeStamp.padata_value.value)
		ossFreeBuf(&world, PaEncTimeStamp.padata_value.value);
	if(PaPacRequest.padata_value.value)
		ossFreeBuf(&world, PaPacRequest.padata_value.value);
	if(PaTgsReq.padata_value.value)
		ossFreeBuf(&world, PaTgsReq.padata_value.value);

	if(req.req_body.enc_authorization_data.cipher.value)
		LocalFree(req.req_body.enc_authorization_data.cipher.value);
	if(req.req_body.sname.name_string)
		LocalFree(req.req_body.sname.name_string);
	if(req.req_body.cname.name_string)
		LocalFree(req.req_body.cname.name_string);
	if(req.padata)
		LocalFree(req.padata);
		
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
			status = !ossEncode(&world, KRB_PRIV_PDU, &kPriv, OutKrbPriv);
			LocalFree(kPriv.enc_part.cipher.value);
		}
		else PRINT_ERROR("Encrypt\n");
		ossFreeBuf(&world, bufEncPart.value);
	}
	if(!status)
		PRINT_ERROR("%s\n", ossGetErrMsg(&world));

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
		PRINT_ERROR("%s\n", ossGetErrMsg(&world));

	return status;
}

BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep(KDC_REP *rep, EncKDCRepPart ** encRepPart, EncryptionKey *key, int pdu)
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
	return status;
}

void kull_m_kerberos_asn1_helper_util_UTCKerberosTimeToFileTime(KerberosTime *time, PFILETIME pFileTime)
{
	SYSTEMTIME systemTime;
	systemTime.wYear = time->year;
	systemTime.wMonth = time->month;
	systemTime.wDay = time->day;
	systemTime.wHour = time->hour;
	systemTime.wMinute = time->minute;
	systemTime.wSecond = time->second;
	systemTime.wMilliseconds = time->millisec;
	systemTime.wDayOfWeek = 0;
	SystemTimeToFileTime(&systemTime, pFileTime);
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
	else PRINT_ERROR("LocacteCSystem: %08x\n", status);
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
			kprintf("%s (%u)\n", kull_m_kerberos_asn1_helper_util_err_to_string(error->error_code), error->error_code);
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