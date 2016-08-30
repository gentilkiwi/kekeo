/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "kull_m_kerberos_helper.h"

STRING	kerberosPackageName = {8, 9, MICROSOFT_KERBEROS_NAME_A};
DWORD	g_AuthenticationPackageId_Kerberos = 0;
BOOL	g_isAuthPackageKerberos = FALSE;
HANDLE	g_hLSA = NULL;

BOOL kull_m_kerberos_helper_init()
{
	if(NT_SUCCESS(LsaConnectUntrusted(&g_hLSA)))
		g_isAuthPackageKerberos = NT_SUCCESS(LsaLookupAuthenticationPackage(g_hLSA, &kerberosPackageName, &g_AuthenticationPackageId_Kerberos));
	return g_isAuthPackageKerberos;
}

BOOL kull_m_kerberos_helper_term()
{
	BOOL status = FALSE;
	if(g_hLSA)
		status = NT_SUCCESS(LsaDeregisterLogonProcess(g_hLSA));
	return status;
}

BOOL kull_m_kerberos_helper_net_SendAndRecv(SOCKET *Socket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize)
{
	PVOID data, buffer;
	DWORD dataSize, bufferSize;
	BOOL status = FALSE;

	dataSize = dataInSize + sizeof(DWORD);
	if(data = LocalAlloc(LPTR, dataSize))
	{
		*(PDWORD) data = _byteswap_ulong(dataInSize);
		RtlCopyMemory((PBYTE) data + sizeof(DWORD), dataIn, dataInSize);
		if(status = kull_m_sock_SendAndRecv(Socket, data, dataSize, &buffer, &bufferSize))
		{
			*dataOutSize = bufferSize - sizeof(DWORD);
			if(*dataOut = LocalAlloc(LPTR, *dataOutSize))
			{
				RtlCopyMemory(*dataOut, (PBYTE) buffer + sizeof(DWORD), *dataOutSize);
				if(!(status = (*dataOutSize == _byteswap_ulong(*(PDWORD) buffer))))
					PRINT_ERROR("Packet size + 4 != Kerberos Packet Size\n");

				if(!status)
					LocalFree(*dataOut);
			}
			LocalFree(buffer);
		}
		LocalFree(data);
	}
	return status;
}

BOOL kull_m_kerberos_helper_net_callKdcOssBuf(SOCKET *Socket, OssBuf *in, LPVOID * out, int outPdu)
{
	BOOL status = FALSE;
	OssBuf receivedData;
	*out = NULL;
	if(kull_m_kerberos_helper_net_SendAndRecv(Socket, in->value, in->length, (LPVOID *) &receivedData.value, (DWORD *) &receivedData.length))
	{
		status = kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(&receivedData, outPdu, out);
		LocalFree(receivedData.value);
	}
	return status;
}

BOOL kull_m_kerberos_helper_net_callKadminOssBuf(SOCKET *Socket, OssBuf *ReqIn, OssBuf *KrbPrivIn, AP_REP **ApRep, KRB_PRIV **KrbPriv)
{
	BOOL status = FALSE;
	PVOID bufferIn, bufferOut;
	DWORD sizeIn = 6 + ReqIn->length + KrbPrivIn->length, sizeOut;
	OssBuf buf;

	*ApRep = NULL;
	*KrbPriv = NULL;
	if(bufferIn = LocalAlloc(LPTR, sizeIn))
	{
		((PWORD) bufferIn)[0] = _byteswap_ushort((WORD) sizeIn);
		((PWORD) bufferIn)[1] = _byteswap_ushort(1/*0xff80*/);
		((PWORD) bufferIn)[2] = _byteswap_ushort((WORD) ReqIn->length);
		RtlCopyMemory((PBYTE) bufferIn + 6, ReqIn->value, ReqIn->length);
		RtlCopyMemory((PBYTE) bufferIn + 6 + ReqIn->length, KrbPrivIn->value, KrbPrivIn->length);

		if(kull_m_kerberos_helper_net_SendAndRecv(Socket, bufferIn, sizeIn, &bufferOut, &sizeOut))
		{
			if((sizeOut == _byteswap_ushort(((PWORD) bufferOut)[0])) && (sizeOut > 6)) // ok fuck, exploit me
			{
				buf.length = _byteswap_ushort(((PWORD) bufferOut)[2]);
				buf.value = (PBYTE) bufferOut + 6;
				if(kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(&buf, AP_REP_PDU, (LPVOID *) ApRep))
				{
					buf.length = sizeOut - 6 - _byteswap_ushort(((PWORD) bufferOut)[2]);
					buf.value = (PBYTE) bufferOut + 6 + _byteswap_ushort(((PWORD) bufferOut)[2]);

					status = kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(&buf, KRB_PRIV_PDU, (LPVOID *) KrbPriv);
					if(!status)
					{
						if(*KrbPriv)
							kull_m_kerberos_asn1_helper_ossFreePDU(KRB_PRIV_PDU, *KrbPriv);
						if(*ApRep)
							kull_m_kerberos_asn1_helper_ossFreePDU(AP_REP_PDU, *ApRep);
					}
				}
			}
			else PRINT_ERROR("Size\n");
			
			LocalFree(bufferOut);
		}
		LocalFree(bufferIn);
	}
	return status;
}

BOOL kull_m_kerberos_helper_util_SaveRepAsKrbCred(KDC_REP *rep, EncKDCRepPart *encRepPart, LPCSTR filename)
{
	BOOL status = FALSE;
	OssBuf KrbCred;
	if(kull_m_kerberos_asn1_helper_build_KrbCred(&rep->crealm, &rep->cname, encRepPart, &rep->ticket, &KrbCred))
	{
		if(filename)
		{
			if(status = kull_m_file_writeData(filename, KrbCred.value, KrbCred.length))
				kprintf("  * Ticket in file \'%s\'\n", filename);
			else PRINT_ERROR_AUTO("kull_m_file_writeData");
		}
		else
		{
			if(status = NT_SUCCESS(kull_m_kerberos_helper_util_ptt_data(KrbCred.value, KrbCred.length)))
				kprintf("  * Ticket successfully submitted for current session\n");
		}
		kull_m_kerberos_asn1_helper_ossFreeBuf(KrbCred.value);
	}
	return status;
}

NTSTATUS kull_m_kerberos_helper_util_LsaCallKerberosPackage(PVOID ProtocolSubmitBuffer, ULONG SubmitBufferLength, PVOID *ProtocolReturnBuffer, PULONG ReturnBufferLength, PNTSTATUS ProtocolStatus)
{
	NTSTATUS status = STATUS_HANDLE_NO_LONGER_VALID;
	if(g_hLSA && g_isAuthPackageKerberos)
		status = LsaCallAuthenticationPackage(g_hLSA, g_AuthenticationPackageId_Kerberos, ProtocolSubmitBuffer, SubmitBufferLength, ProtocolReturnBuffer, ReturnBufferLength, ProtocolStatus);
	return status;
}

NTSTATUS kull_m_kerberos_helper_util_ptt_data(PVOID data, DWORD dataSize)
{
	NTSTATUS status = STATUS_MEMORY_NOT_ALLOCATED, packageStatus;
	DWORD submitSize, responseSize;
	PKERB_SUBMIT_TKT_REQUEST pKerbSubmit;
	PVOID dumPtr;
	
	submitSize = sizeof(KERB_SUBMIT_TKT_REQUEST) + dataSize;
	if(pKerbSubmit = (PKERB_SUBMIT_TKT_REQUEST) LocalAlloc(LPTR, submitSize))
	{
		pKerbSubmit->MessageType = KerbSubmitTicketMessage;
		pKerbSubmit->KerbCredSize = dataSize;
		pKerbSubmit->KerbCredOffset = sizeof(KERB_SUBMIT_TKT_REQUEST);
		RtlCopyMemory((PBYTE) pKerbSubmit + pKerbSubmit->KerbCredOffset, data, dataSize);

		status = kull_m_kerberos_helper_util_LsaCallKerberosPackage(pKerbSubmit, submitSize, &dumPtr, &responseSize, &packageStatus);
		if(NT_SUCCESS(status))
		{
			status = packageStatus;
			if(!NT_SUCCESS(status))
				PRINT_ERROR("LsaCallAuthenticationPackage KerbSubmitTicketMessage / Package : %08x\n", status);
		}
		else PRINT_ERROR("LsaCallAuthenticationPackage KerbSubmitTicketMessage : %08x\n", status);

		LocalFree(pKerbSubmit);
	}
	return status;
}

BOOL kull_m_kerberos_helper_getAuthInfo(int argc, char * argv[], PKIWI_AUTH_INFOS authInfo)
{
	BOOL status = FALSE, isSpecial = FALSE;
	LPCSTR baseDot, szKey = NULL, szSubject, szPin, szAsreq;
	DWORD i, j;
	PA_DATA *paData;
	PA_PK_AS_REQ *pkAsReq = NULL;
	OssBuf AuthPackBuff = {0, NULL};
	AuthPack *auth = NULL;
	RtlZeroMemory(authInfo, sizeof(KIWI_AUTH_INFOS));

	if(isSpecial = kull_m_string_args_byName(argc, argv, "asreq", &szAsreq, NULL))
	{
		authInfo->type = KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH;
		kprintf("crypto mode        : PKINIT mustiness mode\n");
		if(kull_m_crypto_get_DHKeyInfo(TRUE, FALSE, &authInfo->u.asReqDH.dhKeyInfo))
		{
			if(kull_m_file_readData(szAsreq, &authInfo->u.asReqDH.AsReqBuf.value, (PDWORD) &authInfo->u.asReqDH.AsReqBuf.length))
			{
				if(!kull_m_kerberos_asn1_helper_ossDecode(AS_REQ_PDU, &authInfo->u.asReqDH.AsReqBuf, (LPVOID *) &authInfo->u.asReqDH.AsReq))
				{
					kull_m_string_copy((LPSTR *) &authInfo->szDomain, authInfo->u.asReqDH.AsReq->req_body.realm);
					if(authInfo->u.asReqDH.AsReq->req_body.bit_mask & KDC_REQ_BODY_cname_present)
						if(authInfo->u.asReqDH.AsReq->req_body.cname.name_type == KRB_NT_PRINCIPAL)
							kull_m_string_copy((LPSTR *) &authInfo->szUser, authInfo->u.asReqDH.AsReq->req_body.cname.name_string->value);

					if(paData = kull_m_kerberos_asn1_helper_get_PADATA_from_REQ(authInfo->u.asReqDH.AsReq, PA_TYPE_PK_AS_REQ))
					{
						if(!kull_m_kerberos_asn1_helper_ossDecode(PA_PK_AS_REQ_PDU, (OssBuf *) &paData->padata_value, (LPVOID *) &pkAsReq))
						{
							if(kull_m_crypto_simple_message_get(&pkAsReq->signedAuthPack, &AuthPackBuff))
							{
								if(status = !kull_m_kerberos_asn1_helper_ossDecode(AuthPack_PDU, &AuthPackBuff, (LPVOID *) &auth))
								{
									kprintf("Authenticator time : ");
									kull_m_kerberos_asn1_helper_display_KerberosTime(&auth->pkAuthenticator.ctime);
									kprintf("\n");
									if(auth->bit_mask & clientDHNonce_present)
										if(authInfo->u.asReqDH.dhKeyInfo.dhClientNonce.value = (PBYTE) LocalAlloc(LPTR, auth->clientDHNonce.length))
										{
											authInfo->u.asReqDH.dhKeyInfo.dhClientNonce.length = auth->clientDHNonce.length;
											RtlCopyMemory(authInfo->u.asReqDH.dhKeyInfo.dhClientNonce.value, auth->clientDHNonce.value, auth->clientDHNonce.length);
										}
									kull_m_kerberos_asn1_helper_ossFreePDU(AuthPack_PDU, auth);
								}
								else PRINT_ERROR("Unable to decode AuthPack: %s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());
								LocalFree(AuthPackBuff.value);
							}
							else PRINT_ERROR("Unable to get signed message\n");
							kull_m_kerberos_asn1_helper_ossFreePDU(PA_PK_AS_REQ_PDU, pkAsReq);
						}
						else PRINT_ERROR("Unable to decode PA_PK_AS_REQ: %s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());
					}
					else PRINT_ERROR("No PADATA of PA_TYPE_PK_AS_REQ\n");
				}
				else PRINT_ERROR("Unable to decode AS_REQ: %s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());
			}
			else PRINT_ERROR_AUTO("kull_m_file_readData (asreq)");
		}
		else PRINT_ERROR_AUTO("kull_m_crypto_get_DHKeyInfo");
	}

	if((isSpecial && status) || kull_m_string_args_byName(argc, argv, "user", &authInfo->szUser, NULL))
	{
		kprintf("username           : %s\n", authInfo->szUser);
		if((isSpecial && status) || kull_m_string_args_byName(argc, argv, "domain", &authInfo->szDomain, NULL))
		{
			if(baseDot = strchr(authInfo->szDomain, L'.'))
			{
				i = (PBYTE) baseDot - (PBYTE) authInfo->szDomain;
				if(authInfo->szNetbiosDomain = (PSTR) LocalAlloc(LPTR, i + 1))
				{
					for(j = 0; j < i ; j++)
						authInfo->szNetbiosDomain[j] = toupper(authInfo->szDomain[j]);
					kprintf("domain             : %s (%s)\n", authInfo->szDomain, authInfo->szNetbiosDomain);

					// password part
					if(kull_m_string_args_byName(argc, argv, "key", &szKey, NULL) || kull_m_string_args_byName(argc, argv, "password", &authInfo->szPassword, NULL))
					{
						authInfo->type = KIWI_AUTH_INFOS_TYPE_KEY;

						if(kull_m_string_args_byName(argc, argv, "aes256", NULL, NULL))
							authInfo->u.userKey.keytype = KERB_ETYPE_AES256_CTS_HMAC_SHA1_96;
						else if(kull_m_string_args_byName(argc, argv, "aes128", NULL, NULL))
							authInfo->u.userKey.keytype = KERB_ETYPE_AES128_CTS_HMAC_SHA1_96;
						else
							authInfo->u.userKey.keytype = KERB_ETYPE_RC4_HMAC_NT;

						if(status = NT_SUCCESS(kull_m_kerberos_asn1_helper_util_stringToKey(authInfo->szUser, authInfo->szDomain, authInfo->szPassword, szKey, &authInfo->u.userKey)))
						{
							kprintf("password           : %s\n"
								"key                : "
								, szKey ? "<NULL>" : "***");
							kull_m_string_printf_hex(authInfo->u.userKey.keyvalue.value, authInfo->u.userKey.keyvalue.length, 0);
							kprintf(" (%s)\n", kull_m_kerberos_asn1_helper_util_etypeToString(authInfo->u.userKey.keytype));
						}
					}
					else if(kull_m_string_args_byName(argc, argv, "subject", &szSubject, NULL))
					{
						kprintf("certificate subject: %s\n", szSubject);
						if(kull_m_crypto_get_CertInfo(szSubject, &authInfo->u.certInfoDH.certinfo))
						{
							kprintf("crypto mode        : ");
							if(kull_m_string_args_byName(argc, argv, "dh", NULL, NULL))
							{
								kprintf("RSA/DH\n");
								authInfo->type = KIWI_AUTH_INFOS_TYPE_RSA_DH;
								if(!(status = kull_m_crypto_get_DHKeyInfo(TRUE, kull_m_string_args_byName(argc, argv, "nonce", NULL, NULL), &authInfo->u.certInfoDH.dhKeyInfo)))
									PRINT_ERROR_AUTO("kull_m_crypto_get_DHKeyInfo");
							}
							else
							{
								kprintf("RSA\n");
								authInfo->type = KIWI_AUTH_INFOS_TYPE_RSA;
								status = TRUE;
							}

							if(kull_m_string_args_byName(argc, argv, "pin", &szPin, NULL))
							{
								kprintf("smartcard pin code : %s", szPin);
								if(CryptSetProvParam(authInfo->u.certInfoDH.certinfo.provider.hProv, PP_SIGNATURE_PIN, (LPCBYTE) szPin, 0))
									kprintf("\n");
								else PRINT_ERROR_AUTO("CryptSetProvParam");
							}
						}
						else PRINT_ERROR("Unable to find a certificate and its private key with this subject\n");
					}
					else if(!status) PRINT_ERROR("Missing authentication information (password/key/subject)\n");
				}
			}
			else PRINT_ERROR("Domain name (%s) does not look like a FQDN\n", authInfo->szDomain);
		}
		else if(!isSpecial) PRINT_ERROR("Missing domain argument\n");
	}
	else if(!isSpecial) PRINT_ERROR("Missing user argument\n");

	if(!status)
		kull_m_kerberos_helper_freeAuthInfo(authInfo);
	return status;
}

void kull_m_kerberos_helper_freeAuthInfo(PKIWI_AUTH_INFOS authInfo)
{
	if(authInfo->szNetbiosDomain)
		LocalFree(authInfo->szNetbiosDomain);
	switch(authInfo->type)
	{
	case KIWI_AUTH_INFOS_TYPE_KEY:
		if(authInfo->u.userKey.keyvalue.value)
			LocalFree(authInfo->u.userKey.keyvalue.value);
		break;
	case KIWI_AUTH_INFOS_TYPE_RSA:
	case KIWI_AUTH_INFOS_TYPE_RSA_DH:
		kull_m_crypto_free_CertInfo(&authInfo->u.certInfoDH.certinfo);
		if(authInfo->type == KIWI_AUTH_INFOS_TYPE_RSA_DH)
			kull_m_crypto_free_DHKeyInfo(&authInfo->u.certInfoDH.dhKeyInfo);
		break;
	case KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH:
		if(authInfo->szUser)
			LocalFree((HLOCAL) authInfo->szUser);
		if(authInfo->szDomain)
			LocalFree((HLOCAL) authInfo->szDomain);
		if(authInfo->u.asReqDH.AsReqBuf.value)
			LocalFree(authInfo->u.asReqDH.AsReqBuf.value);
		if(authInfo->u.asReqDH.AsReq)
			kull_m_kerberos_asn1_helper_ossFreePDU(AS_REQ_PDU, authInfo->u.asReqDH.AsReq);
		kull_m_crypto_free_DHKeyInfo(&authInfo->u.asReqDH.dhKeyInfo);
	default:
		;
	}
}

#ifdef MIMIKATZ_DS_NEEDED
BOOL kull_m_kerberos_helper_net_getDC(LPCSTR fullDomainName, DWORD altFlags, LPSTR * fullDCName)
{
	BOOL status = FALSE;
	DWORD ret, size;
	PDOMAIN_CONTROLLER_INFO cInfo = NULL;
	ret = DsGetDcName(NULL, fullDomainName, NULL, NULL, altFlags | DS_IS_DNS_NAME | DS_RETURN_DNS_NAME, &cInfo);
	if(ret == ERROR_SUCCESS)
	{
		size = (strlen(cInfo->DomainControllerName + 2) + 1) * sizeof(char);
		if(*fullDCName = (char *) LocalAlloc(LPTR, size))
		{
			status = TRUE;
			RtlCopyMemory(*fullDCName, cInfo->DomainControllerName + 2, size);
		}
		NetApiBufferFree(cInfo);
	}
	else PRINT_ERROR("DsGetDcName: %u\n", ret);
	return status;
}
#endif

#ifdef MIMIKATZ_SAMLIB_NEEDED
const wchar_t PREFIX_CIFS[] = L"cifs/";
void kull_m_kerberos_helper_util_impersonateToGetData(PCSTR user, PCSTR domain, PCSTR password, PCSTR kdc, PSID *sid, DWORD *rid, DWORD *pNbDc, PDS_DOMAIN_CONTROLLER_INFO_1 *dcInfos)
{
	NTSTATUS status;
	DWORD ret, *aRid, *usage, unk0 = 0, szPrefix = sizeof(PREFIX_CIFS); // includes NULL;
	ANSI_STRING aUser, aKdc, aDomain, aPass, aProg;
	UNICODE_STRING uUser, uKdc, uDomain, uPass, uProg;
	SAMPR_HANDLE hServerHandle = 0, hDomainHandle = 0;
	PSID domainSid;
	HANDLE hToken, hNewToken, hPds;
	RPC_AUTH_IDENTITY_HANDLE hRPCAuth;
	LPWSTR fullServer;
	PROCESS_INFORMATION processInfos;
	STARTUPINFOW startupInfo = {0};

	startupInfo.cb = sizeof(STARTUPINFOW);
	RtlInitString(&aUser, user);
	RtlInitString(&aKdc, kdc);
	RtlInitString(&aDomain, domain);
	RtlInitString(&aPass, password);
#pragma warning(push)
#pragma warning(disable:4996)
	RtlInitString(&aProg, _pgmptr);
#pragma warning(pop)
	if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&uUser, &aUser, TRUE)))
	{
		if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&uKdc, &aKdc, TRUE)))
		{
			if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&uDomain, &aDomain, TRUE)))
			{
				ret = DsMakePasswordCredentials(user, domain, password, &hRPCAuth);
				if(ret == ERROR_SUCCESS)
				{
					if(pNbDc && dcInfos)
					{
						ret = DsBindWithCred(kdc, domain, hRPCAuth, &hPds);
						if(ret == ERROR_SUCCESS)
						{
							ret = DsGetDomainControllerInfo(hPds, domain, 1, pNbDc, (PVOID *) dcInfos);
							if(ret == ERROR_SUCCESS)
								kprintf("[KDC] %u server(s) in list\n", *pNbDc);
							else PRINT_ERROR("DsGetDomainControllerInfo: %u\n", ret);
							DsUnBind(&hPds);
						}
						else PRINT_ERROR("DsBindWithCred: %u\n", ret);
					}

					if(sid || rid)
					{
						kprintf("[SID/RID] \'%s @ %s\' must be translated to SID/RID\n", user, domain);
						if(fullServer = (LPWSTR) LocalAlloc(LPTR, szPrefix + uKdc.Length))
						{
							RtlCopyMemory(fullServer, PREFIX_CIFS, szPrefix);
							RtlCopyMemory((PBYTE) fullServer + (szPrefix - sizeof(wchar_t)), uKdc.Buffer, uKdc.Length);
							status = SamConnectWithCreds(&uKdc, &hServerHandle, SAM_SERVER_CONNECT | SAM_SERVER_LOOKUP_DOMAIN, NULL, hRPCAuth, fullServer, &unk0);
							if(status == RPC_NT_UNKNOWN_AUTHN_SERVICE)
								status = SamConnectWithCreds(&uKdc, &hServerHandle, SAM_SERVER_CONNECT | SAM_SERVER_LOOKUP_DOMAIN, NULL, hRPCAuth, NULL, &unk0);
							else if(status == STATUS_INVALID_HANDLE) // 2000 :(
							{
								kprintf("[AUTH] Impersonation (Windows 2000 target ?)\n");
								if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&uPass, &aPass, TRUE)))
								{
									if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&uProg, &aProg, TRUE)))
									{
										if(CreateProcessWithLogonW(uUser.Buffer, uDomain.Buffer, uPass.Buffer, LOGON_NETCREDENTIALS_ONLY, uProg.Buffer, NULL, CREATE_SUSPENDED, NULL, NULL, &startupInfo, &processInfos))
										{
											if(OpenProcessToken(processInfos.hProcess, TOKEN_DUPLICATE, &hToken))
											{
												if(DuplicateTokenEx(hToken, TOKEN_QUERY | TOKEN_IMPERSONATE, NULL, SecurityDelegation, TokenImpersonation, &hNewToken))
												{
													if(SetThreadToken(NULL, hNewToken))
													{
														status = SamConnect(&uKdc, &hServerHandle, SAM_SERVER_CONNECT | SAM_SERVER_LOOKUP_DOMAIN, FALSE);
														RevertToSelf();
													}
													else PRINT_ERROR_AUTO("SetThreadToken");
													CloseHandle(hNewToken);
												}
												else PRINT_ERROR_AUTO("DuplicateTokenEx");
												CloseHandle(hToken);
											}
											else PRINT_ERROR_AUTO("OpenProcessToken");
											TerminateProcess(processInfos.hProcess, STATUS_SUCCESS);
											CloseHandle(processInfos.hProcess);
											CloseHandle(processInfos.hThread);
										}
										else PRINT_ERROR_AUTO("CreateProcessWithLogonW");
										RtlFreeUnicodeString(&uProg);
									}
									RtlFreeUnicodeString(&uPass);
								}
							}
							if(NT_SUCCESS(status))
							{
								status = SamLookupDomainInSamServer(hServerHandle, &uDomain, &domainSid);
								if(NT_SUCCESS(status))
								{
									status = SamOpenDomain(hServerHandle, DOMAIN_LIST_ACCOUNTS | DOMAIN_LOOKUP, domainSid, &hDomainHandle);
									if(NT_SUCCESS(status))
									{
										if(rid)
										{
											status = SamLookupNamesInDomain(hDomainHandle, 1, &uUser, &aRid, &usage);
											if(NT_SUCCESS(status))
												*rid = aRid[0];
											else PRINT_ERROR("SamLookupNamesInDomain %08x\n", status);
										}
									}
									else PRINT_ERROR("SamOpenDomain %08x\n", status);

									if(sid)
									{
										ret = GetLengthSid(domainSid);
										if(*sid = (PSID) LocalAlloc(LPTR, ret))
										{
											if(!CopySid(ret, *sid, domainSid))
											{
												*sid = (PSID) LocalFree(*sid);
												PRINT_ERROR_AUTO("CopySid");
											}
										}
									}
									SamFreeMemory(domainSid);
								}
								else PRINT_ERROR("SamLookupDomainInSamServer %08x\n", status);
								SamCloseHandle(hServerHandle);
							}
							else PRINT_ERROR("SamConnectWithCreds %08x\n", status);
							LocalFree(fullServer);
						}
					}
					DsFreePasswordCredentials(hRPCAuth);
				}
				else PRINT_ERROR("DsMakePasswordCredentials: %u\n", ret);
				RtlFreeUnicodeString(&uDomain);
			}
			RtlFreeUnicodeString(&uKdc);
		}
		RtlFreeUnicodeString(&uUser);
	}
}
#endif