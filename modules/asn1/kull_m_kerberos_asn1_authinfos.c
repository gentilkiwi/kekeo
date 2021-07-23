/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kull_m_kerberos_asn1_authinfos.h"

void kull_m_kerberos_asn1_Authinfos_refresh(PKIWI_AUTH_INFOS infos)
{
	LPCWSTR p;
	if(infos->w_cname)
	{
		if(p = wcschr(infos->w_cname, L'\\'))
		{
			if(!infos->w_short_cname && *(p + 1))
				kull_m_string_copy(&infos->w_short_cname, p + 1);
			if(!infos->w_short_realm && (p != infos->w_cname))
			{
				kull_m_string_copy(&infos->w_short_realm, infos->w_cname);
				infos->w_short_realm[p - infos->w_cname] = L'\0';
			}
		}
		else if(p = wcschr(infos->w_cname, L'@'))
		{
			if(!infos->w_realm && *(p + 1))
				kull_m_string_copy(&infos->w_realm, p + 1);
			if(!infos->w_short_cname && (p != infos->w_cname))
			{
				kull_m_string_copy(&infos->w_short_cname, infos->w_cname);
				infos->w_short_cname[p - infos->w_cname] = L'\0';
			}
		}
		else if(!wcschr(infos->w_cname, L'/'))
		{
			if(!infos->w_short_cname)
				kull_m_string_copy(&infos->w_short_cname, infos->w_cname);
		}
	}

	if(infos->w_realm)
	{
		if(!infos->w_short_realm)
		{
			if(p = wcschr(infos->w_realm, L'.'))
			{
				if(p != infos->w_realm)
				{
					kull_m_string_copy(&infos->w_short_realm, infos->w_realm);
					infos->w_short_realm[p - infos->w_realm] = L'\0';
				}
			}
			else kull_m_string_copy(&infos->w_short_realm, infos->w_realm);
		}
	}
}

BOOL kull_m_kerberos_asn1_Authinfos_create_for_key(PKIWI_AUTH_INFOS infos, int argc, wchar_t * argv[])
{
	BOOL status = FALSE;
	LPCWSTR szData;

	if(infos->w_password)
	{
		if(kull_m_string_args_byName(argc, argv, L"aes256", NULL, NULL))
			infos->u.ekey.keytype = KERB_ETYPE_AES256_CTS_HMAC_SHA1_96;
		else if(kull_m_string_args_byName(argc, argv, L"aes128", NULL, NULL))
			infos->u.ekey.keytype = KERB_ETYPE_AES128_CTS_HMAC_SHA1_96;
		else
			infos->u.ekey.keytype = KERB_ETYPE_RC4_HMAC_NT;
		status = NT_SUCCESS(kull_m_kerberos_asn1_crypto_ekey_create_fromPassword(infos->w_realm, infos->w_short_cname, infos->w_password, &infos->u.ekey));
	}
	else
	{
		if(kull_m_string_args_byName(argc, argv, L"aes256", &szData, NULL))
			infos->u.ekey.keytype = KERB_ETYPE_AES256_CTS_HMAC_SHA1_96;
		else if(kull_m_string_args_byName(argc, argv, L"aes128", &szData, NULL))
			infos->u.ekey.keytype = KERB_ETYPE_AES128_CTS_HMAC_SHA1_96;
		else if(kull_m_string_args_byName(argc, argv, L"rc4", &szData, NULL) || kull_m_string_args_byName(argc, argv, L"ntlm", &szData, NULL))
			infos->u.ekey.keytype = KERB_ETYPE_RC4_HMAC_NT;
		
		if(infos->u.ekey.keytype)
			status = NT_SUCCESS(kull_m_kerberos_asn1_crypto_ekey_create_fromHexString(szData, &infos->u.ekey));
	}
	if(status)
		infos->type = KIWI_AUTH_INFOS_TYPE_KEY;
	return status;
}

LPWSTR kull_m_kerberos_asn1_Authinfos_makeMeUpn(PKIWI_AUTH_INFOS infos)
{
	LPWSTR result = NULL;
	DWORD dwUser, dwDomain;

	if(infos->w_cname && wcschr(infos->w_cname, L'@'))
		kull_m_string_copy(&result, infos->w_cname);
	else if(infos->w_short_cname && infos->w_realm)
	{
		dwUser = lstrlen(infos->w_short_cname);
		dwDomain = lstrlen(infos->w_realm);
		if(result = (LPWSTR) LocalAlloc(LPTR, (dwUser + 1 + dwDomain + 1) * sizeof(wchar_t)))
		{
			RtlCopyMemory(result, infos->w_short_cname, dwUser * sizeof(wchar_t));
			*(result + dwUser) = L'@';
			RtlCopyMemory(result + dwUser + 1, infos->w_realm, dwDomain * sizeof(wchar_t));
		}
	}
	else PRINT_ERROR(L"Not enough data to create an UPN\n");
	return result;
}

void kull_m_kerberos_asn1_Authinfos_create_for_cert_names(PKIWI_AUTH_INFOS infos)
{
	DWORD l;
	LPWSTR buffer, p;

	if(!infos->w_cname || !infos->w_realm)
	{
		l = CertGetNameString(infos->u.certinfos.pCertContext, CERT_NAME_UPN_TYPE, 0, NULL, NULL, 0);
		if(l > 1)
		{
			if(buffer = (LPWSTR) LocalAlloc(LPTR, l * sizeof(wchar_t)))
			{
				if(CertGetNameString(infos->u.certinfos.pCertContext, CERT_NAME_UPN_TYPE, 0, NULL, buffer, l) == l)
				{
					if(!infos->w_cname)
					{
						kull_m_string_copy(&infos->w_cname, buffer);
						kull_m_kerberos_asn1_Authinfos_refresh(infos);
					}
					if(!infos->w_realm)
					{
						p = wcschr(buffer, L'@');
						if(p && *(p + 1))
						{
							kull_m_string_copy(&infos->w_realm, p + 1);
							kull_m_kerberos_asn1_Authinfos_refresh(infos);
						}
					}
				}
				LocalFree(buffer);
			}
		}
	}
}

BOOL kull_m_kerberos_asn1_Authinfos_create_for_cert(PKIWI_AUTH_INFOS infos, int argc, wchar_t * argv[])
{
	BOOL status = FALSE;
	LPCWSTR szData, szStoreCA, szCRLDP;
	LPWSTR buffer;
	LPSTR abuf;
	CRYPT_DATA_BLOB blob;

	if(kull_m_string_args_byName(argc, argv, L"subject", &szData, NULL))
	{
		if(status = kull_m_kerberos_asn1_crypto_get_CertInfo(szData, &infos->u.certinfos))
		{
			if(kull_m_string_args_byName(argc, argv, L"pin", &szData, NULL))
			{
				if(abuf = kull_m_string_unicode_to_ansi(szData))
				{
					if(!CryptSetProvParam(infos->u.certinfos.provider.hProv, PP_SIGNATURE_PIN, (LPCBYTE) abuf, 0))
						PRINT_ERROR_AUTO(L"CryptSetProvParam");
					LocalFree(abuf);
				}
			}

			infos->type = KIWI_AUTH_INFOS_TYPE_RSA;
			kull_m_kerberos_asn1_Authinfos_create_for_cert_names(infos);
		}
	}
	else if(kull_m_string_args_byName(argc, argv, L"caname", &szData, NULL))
	{
		kull_m_string_args_byName(argc, argv, L"castore", &szStoreCA, L"LOCAL_MACHINE");
		kull_m_string_args_byName(argc, argv, L"crldp", &szCRLDP, NULL);
		if(buffer = kull_m_kerberos_asn1_Authinfos_makeMeUpn(infos))
		{
			if(status = kull_m_kerberos_asn1_crypto_get_CertFromCA(szData, szStoreCA, buffer, szCRLDP, &infos->u.certinfos))
				infos->type = KIWI_AUTH_INFOS_TYPE_OTF_RSA;
			LocalFree(buffer);
		}
	}
	else if(kull_m_string_args_byName(argc, argv, L"pfx", &szData, NULL) || kull_m_string_args_byName(argc, argv, L"pkcs12", &szData, NULL))
	{
		if(kull_m_file_readData(szData, &blob.pbData, &blob.cbData))
		{
			szData = NULL;
			kull_m_string_args_byName(argc, argv, L"pfxpassword", &szData, NULL) || kull_m_string_args_byName(argc, argv, L"pkcs12password", &szData, NULL);

			if(kull_m_kerberos_asn1_crypto_get_CertInfo_FromPFX(&blob, szData, &infos->u.certinfos))
			{
				infos->type = KIWI_AUTH_INFOS_TYPE_RSA;
				kull_m_kerberos_asn1_Authinfos_create_for_cert_names(infos);
			}
			LocalFree(blob.pbData);
		}
	}
	
	if(status)
	{
		if(kull_m_string_args_byName(argc, argv, L"dh", NULL, NULL))
		{
			status = kull_m_kerberos_asn1_crypto_get_DHKeyInfo(TRUE, kull_m_string_args_byName(argc, argv, L"nonce", NULL, NULL), &infos->u.certinfos.dhKeyInfo);
			if(!status)
			{
				PRINT_ERROR_AUTO(L"kull_m_crypto_get_DHKeyInfo");
				infos->type = KIWI_AUTH_INFOS_TYPE_INVALID;
			}
			switch(infos->type)
			{
			case KIWI_AUTH_INFOS_TYPE_RSA:
				if(status)
					infos->type = KIWI_AUTH_INFOS_TYPE_RSA_DH;
				else kull_m_kerberos_asn1_crypto_free_CertInfo(&infos->u.certinfos);
				break;
			case KIWI_AUTH_INFOS_TYPE_OTF_RSA:
				if(status)
					infos->type = KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH;
				else kull_m_kerberos_asn1_crypto_free_CertFromCA(&infos->u.certinfos);
				break;
			}
		}
	}
	return status;
}

BOOL kull_m_kerberos_asn1_Authinfos_create_for_asreq(PKIWI_AUTH_INFOS infos, int argc, wchar_t * argv[])
{
	BOOL status = FALSE;
	LPCWSTR szData;
	OssBuf asReqBuff = {0, NULL};
	int pduNum;
	KULL_M_ASN1_PA_DATA *paData;
	KULL_M_ASN1_PA_PK_AS_REQ *pkAsReq = NULL;
	OssBuf AuthPackBuff = {0, NULL};
	KULL_M_ASN1_AuthPack *auth = NULL;
	PSTR buffer = NULL;

	infos->u.certinfos.tmpAsReq = NULL;
	if(kull_m_string_args_byName(argc, argv, L"asreq", &szData, NULL))
	{
		if(kull_m_file_readData(szData, &asReqBuff.value, (PDWORD) &asReqBuff.length))
		{
			pduNum = KULL_M_ASN1_AS_REQ_PDU;
			if(!ossDecode(&kull_m_kerberos_asn1_world, &pduNum, &asReqBuff, (void **) &infos->u.certinfos.tmpAsReq))
			{
				if(!infos->w_realm && infos->u.certinfos.tmpAsReq->req_body.realm)
				{
					infos->w_realm = kull_m_string_qad_ansi_to_unicode(infos->u.certinfos.tmpAsReq->req_body.realm);
					kull_m_kerberos_asn1_Authinfos_refresh(infos);
				}
				if(!infos->w_cname && (infos->u.certinfos.tmpAsReq->req_body.bit_mask & KULL_M_ASN1_KDC_REQ_BODY_cname_present))
				{
					switch(infos->u.certinfos.tmpAsReq->req_body.cname.name_type)
					{
					case KRB_NT_PRINCIPAL:
					case KRB_NT_ENTERPRISE_PRINCIPAL:
					case KRB_NT_MS_PRINCIPAL:
						infos->w_cname = kull_m_string_qad_ansi_to_unicode(infos->u.certinfos.tmpAsReq->req_body.cname.name_string->value);
						break;
					case KRB_NT_SRV_INST: // todo?
					default:
						PRINT_ERROR(L"This name_type is not supported in AS_REQ\n");
					}
					kull_m_kerberos_asn1_Authinfos_refresh(infos);
				}

				if(paData = kull_m_kerberos_asn1_PADATA_from_REQ(infos->u.certinfos.tmpAsReq, PA_TYPE_PK_AS_REQ))
				{
					pduNum = KULL_M_ASN1_PA_PK_AS_REQ_PDU;
					if(!ossDecode(&kull_m_kerberos_asn1_world, &pduNum, (OssBuf *) &paData->padata_value, (LPVOID *) &pkAsReq))
					{
						if(kull_m_kerberos_asn1_crypto_simple_message_get(&pkAsReq->signedAuthPack, &AuthPackBuff))
						{
							pduNum = KULL_M_ASN1_AuthPack_PDU;
							if(!ossDecode(&kull_m_kerberos_asn1_world, &pduNum, &AuthPackBuff, (LPVOID *) &auth))
							{
								kprintf(L"Authenticator time : ");
								kull_m_kerberos_asn1_KerberosTime_print(&auth->pkAuthenticator.ctime);
								kprintf(L"\n");
								if(status = kull_m_kerberos_asn1_crypto_get_DHKeyInfo(TRUE, FALSE, &infos->u.certinfos.dhKeyInfo))
								{
									if(auth->bit_mask & KULL_M_ASN1_clientDHNonce_present)
										if(infos->u.certinfos.dhKeyInfo.dhClientNonce.value = (PBYTE) LocalAlloc(LPTR, auth->clientDHNonce.length))
										{
											infos->u.certinfos.dhKeyInfo.dhClientNonce.length = auth->clientDHNonce.length;
											RtlCopyMemory(infos->u.certinfos.dhKeyInfo.dhClientNonce.value, auth->clientDHNonce.value, auth->clientDHNonce.length);
										}
								}
								else PRINT_ERROR_AUTO(L"kull_m_kerberos_asn1_crypto_get_DHKeyInfo(integrated)");
								ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_AuthPack_PDU, auth);
							}
							else PRINT_ERROR(L"Unable to decode AuthPack: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
							LocalFree(AuthPackBuff.value);
						}
						else PRINT_ERROR(L"Unable to get signed message\n");
						ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_PA_PK_AS_REQ_PDU, pkAsReq);
					}
					else PRINT_ERROR(L"Unable to decode PA_PK_AS_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
				}
				else PRINT_ERROR(L"No PADATA of PA_TYPE_PK_AS_REQ\n");
			}
			else PRINT_ERROR(L"Unable to decode AS_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
			LocalFree(asReqBuff.value);
		}
	}

	if(status)
		infos->type = KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH;
	else
	{
		if(infos->u.certinfos.tmpAsReq)
			ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_AS_REQ_PDU, infos->u.certinfos.tmpAsReq);
		kull_m_kerberos_asn1_crypto_free_DHKeyInfo(&infos->u.certinfos.dhKeyInfo);
	}
	return status;
}

PKIWI_AUTH_INFOS kull_m_kerberos_asn1_Authinfos_create(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS infos = NULL;
	LPCWSTR szData;

	if(infos = (PKIWI_AUTH_INFOS) LocalAlloc(LPTR, sizeof(KIWI_AUTH_INFOS)))
	{
		infos->type = KIWI_AUTH_INFOS_TYPE_INVALID;
		infos->needPac = !kull_m_string_args_byName(argc, argv, L"nopac", NULL, NULL);
				
		if(kull_m_string_args_byName(argc, argv, L"domain", &szData, NULL))
			kull_m_string_copy(&infos->w_realm, szData);
		if(kull_m_string_args_byName(argc, argv, L"user", &szData, NULL))
			kull_m_string_copy(&infos->w_cname, szData);
		if(kull_m_string_args_byName(argc, argv, L"password", &szData, NULL))
			kull_m_string_copy(&infos->w_password, szData);

		kull_m_kerberos_asn1_Authinfos_refresh(infos);
		
		if(infos->type == KIWI_AUTH_INFOS_TYPE_INVALID)
			kull_m_kerberos_asn1_Authinfos_create_for_cert(infos, argc, argv);
		if(infos->type == KIWI_AUTH_INFOS_TYPE_INVALID)
			kull_m_kerberos_asn1_Authinfos_create_for_asreq(infos, argc, argv);

		if(infos->w_cname)
			kull_m_kerberos_asn1_PrincipalName_create_fromName(&infos->cname, NULL, infos->w_cname);
		if(infos->w_short_realm && !infos->w_realm)
			kull_m_string_copy(&infos->w_realm, infos->w_short_realm);
		if(infos->w_realm)
		{
			infos->realm = kull_m_string_unicode_to_ansi(infos->w_realm);

			if(kull_m_string_args_byName(argc, argv, L"changepw", NULL, NULL))
				kull_m_kerberos_asn1_PrincipalName_create(&infos->sname, KRB_NT_SRV_INST, 2, "kadmin", "changepw");
			else if(kull_m_string_args_byName(argc, argv, L"altservice", &szData, NULL))
				kull_m_kerberos_asn1_PrincipalName_create_fromName(&infos->sname, NULL, szData);
			else kull_m_kerberos_asn1_PrincipalName_create(&infos->sname, KRB_NT_SRV_INST, 2, "krbtgt", infos->realm);

			if(kull_m_string_args_byName(argc, argv, L"anon", NULL, NULL))
				infos->type = KIWI_AUTH_INFOS_TYPE_ANON;

			if(infos->type == KIWI_AUTH_INFOS_TYPE_INVALID)
				kull_m_kerberos_asn1_Authinfos_create_for_key(infos, argc, argv);

			if(infos->type != KIWI_AUTH_INFOS_TYPE_INVALID)
				kull_m_kerberos_asn1_Authinfos_descr(infos);
			else
			{
				kull_m_kerberos_asn1_Authinfos_delete(infos);
				infos = NULL;
				PRINT_ERROR(L"No authentication infos was provided\n");
			}
		}
		else
		{
			kull_m_kerberos_asn1_Authinfos_delete(infos);
			infos = NULL;
			PRINT_ERROR(L"No domain/Realm was provided or guessed\n");
		}
	}
	return infos;
}

void kull_m_kerberos_asn1_Authinfos_delete(PKIWI_AUTH_INFOS infos)
{
	if(infos)
	{
		if(infos->w_realm)
			LocalFree(infos->w_realm);
		if(infos->realm)
			LocalFree(infos->realm);
		if(infos->w_short_realm)
			LocalFree(infos->w_short_realm);

		if(infos->w_cname)
			LocalFree(infos->w_cname);
		if(infos->w_short_cname)
			LocalFree(infos->w_short_cname);

		if(infos->w_password)
			LocalFree(infos->w_password);

		kull_m_kerberos_asn1_PrincipalName_delete(&infos->cname);
		kull_m_kerberos_asn1_PrincipalName_delete(&infos->sname);

		switch(infos->type)
		{
		case KIWI_AUTH_INFOS_TYPE_KEY:
			kull_m_kerberos_asn1_crypto_ekey_free(&infos->u.ekey);
			break;
		case KIWI_AUTH_INFOS_TYPE_RSA_DH:
			kull_m_kerberos_asn1_crypto_free_DHKeyInfo(&infos->u.certinfos.dhKeyInfo);
		case KIWI_AUTH_INFOS_TYPE_RSA:
			kull_m_kerberos_asn1_crypto_free_CertInfo(&infos->u.certinfos);
			break;
		case KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH:
			kull_m_kerberos_asn1_crypto_free_DHKeyInfo(&infos->u.certinfos.dhKeyInfo);
		case KIWI_AUTH_INFOS_TYPE_OTF_RSA:
			kull_m_kerberos_asn1_crypto_free_CertFromCA(&infos->u.certinfos);
			break;
		case KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH:
			if(infos->u.certinfos.tmpAsReq)
				ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_AS_REQ_PDU, infos->u.certinfos.tmpAsReq);
			kull_m_kerberos_asn1_crypto_free_DHKeyInfo(&infos->u.certinfos.dhKeyInfo);
			break;
		default:
			;
		}
		LocalFree(infos);
	}
}

void kull_m_kerberos_asn1_Authinfos_descr(PKIWI_AUTH_INFOS infos)
{
	if(infos)
	{
		kprintf(L"Realm        : %s (%s)\n", infos->w_realm, infos->w_short_realm);
		kprintf(L"User         : %s (%s)\n", infos->w_cname, infos->w_short_cname);
		kprintf(L"CName        : "); kull_m_kerberos_asn1_PrincipalName_descr(&infos->cname, TRUE);
		kprintf(L"\nSName        : "); kull_m_kerberos_asn1_PrincipalName_descr(&infos->sname, TRUE);
		kprintf(L"\nNeed PAC     : %s\n", infos->needPac ? L"Yes" : L"No");
		kprintf(L"Auth mode    : ");
		switch(infos->type)
		{
		case KIWI_AUTH_INFOS_TYPE_KEY:
			kull_m_kerberos_asn1_crypto_ekey_descr(&infos->u.ekey);
			break;
		case KIWI_AUTH_INFOS_TYPE_RSA:
			kprintf(L"RSA\n");
			break;
		case KIWI_AUTH_INFOS_TYPE_OTF_RSA:
			kprintf(L"RSA on-the-fly\n");
			break;
		case KIWI_AUTH_INFOS_TYPE_RSA_DH:
			kprintf(L"RSA with DH\n");
			break;
		case KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH:
			kprintf(L"RSA with DH on-the-fly\n");
			break;
		case KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH:
			kprintf(L"RSA with DH AS-REQ (PKINIT Mustiness)\n");
			break;
		case KIWI_AUTH_INFOS_TYPE_ANON:
			kprintf(L"Anonymous (without authenticator)\n");
			break;
		default:
			kprintf(L"???\n");
		}
	}
}

USHORT kull_m_kerberos_asn1_Authinfos_changepw(KULL_M_ASN1__octet1 *data, int argc, wchar_t * argv[], KULL_M_ASN1_Realm domain)
{
	USHORT version = 0;
	KULL_M_ASN1_ChangePasswdData change = {0};
	OssBuf ChangePwd = {0, NULL};
	LPCWSTR username = NULL, password;

	data->length = 0;
	data->value = NULL;
	if(kull_m_string_args_byName(argc, argv, L"new", &password, NULL))
	{
		kull_m_string_args_byName(argc, argv, L"for", &username, NULL);
		if((username && domain) || kull_m_string_args_byName(argc, argv, L"newversion", NULL, NULL))
		{
			if(change.newpasswd.value = (PBYTE) kull_m_string_unicode_to_ansi(password))
			{
				change.newpasswd.length = lstrlenA((PCHAR) change.newpasswd.value);
				if(username && domain)
				{
					kull_m_kerberos_asn1_PrincipalName_create_fromName(&change.targname, NULL, username);
					change.bit_mask |= KULL_M_ASN1_targname_present;
					change.targrealm = domain;
					kprintf(L"[changepw] targname : ");
					kull_m_kerberos_asn1_PrincipalName_descr(&change.targname, TRUE);
					kprintf(L"\n[changepw] targrealm: %S\n", change.targrealm);
				}
				if(!ossEncode(&kull_m_kerberos_asn1_world, KULL_M_ASN1_ChangePasswdData_PDU, &change, &ChangePwd))
				{
					if(data->value = (PBYTE) LocalAlloc(LPTR, ChangePwd.length))
					{
						data->length = ChangePwd.length;
						RtlCopyMemory(data->value, ChangePwd.value, data->length);
						version = 0xff80;
					}
					ossFreeBuf(&kull_m_kerberos_asn1_world, ChangePwd.value);
				}
				else PRINT_ERROR(L"Unable to encode ChangePasswdData: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
				if(change.bit_mask & KULL_M_ASN1_targname_present)
					kull_m_kerberos_asn1_PrincipalName_delete(&change.targname);
				LocalFree(change.newpasswd.value);
			}
		}
		else
		{
			if((data->value = (PBYTE) kull_m_string_unicode_to_ansi(password)))
			{
				data->length = lstrlenA((PCHAR) data->value);
				version = 1;
			}
		}
		kprintf(L"[changepw] version  : 0x%04x (%hu)\n", version, version);
	}
	else PRINT_ERROR(L"A new password is required: /new:xxx\n");
	return version;
}