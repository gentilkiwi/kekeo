/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "asktgt.h"

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
	FILETIME fTime;
	OssBuf AsReq;
	KDC_REP *AsRep;
	EncKDCRepPart *encAsRepPart;
	KIWI_AUTH_INFOS authInfo;
	LPCSTR szKdc = NULL, szFilename = NULL;
	LPSTR szWhatDC = NULL;

	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  " MIMIKATZ_SECOND "\n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'                                                     * * */\n\n");	

	if(init())
	{
		if(!kull_m_string_args_byName(argc, argv, "ptt", NULL, NULL))
			kull_m_string_args_byName(argc, argv, "ticket", &szFilename, TICKET_FILENAME);
		
		GetSystemTimeAsFileTime(&fTime);
		kprintf("> Current time     : "); kull_m_string_displayLocalFileTime(&fTime); kprintf("\n");
		
		if(kull_m_kerberos_helper_getAuthInfo(argc, argv, &authInfo))
		{
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
				if(!szWhatDC)
					kprintf("kdc      : %s\n", szKdc);
				if(kull_m_sock_initSocket(szKdc, KERBEROS_DEFAULT_PORT, IPPROTO_TCP, &connectSocket))
				{
					if(kull_m_kerberos_asn1_helper_build_AsReq_Generic(&authInfo, NULL, NULL, NULL, TRUE, &AsReq))
					{
						if(kull_m_kerberos_helper_net_callKdcOssBuf(&connectSocket, &AsReq, (LPVOID *) &AsRep, AS_REP_PDU))
						{
							if(kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_AsRep_Generic(&authInfo, AsRep, &encAsRepPart))
							{
								kull_m_kerberos_helper_util_SaveRepAsKrbCred(AsRep, encAsRepPart, szFilename);
								kull_m_kerberos_asn1_helper_ossFreePDU(EncASRepPart_PDU, encAsRepPart);
							}
							kull_m_kerberos_asn1_helper_ossFreePDU(AS_REP_PDU, AsRep);
						}
						kull_m_kerberos_asn1_helper_ossFreeBuf(AsReq.value);
					}
					kull_m_sock_termSocket(&connectSocket);
				}
				if(szWhatDC)
					LocalFree(szWhatDC);
			}
			else PRINT_ERROR("No KDC\n");
			kull_m_kerberos_helper_freeAuthInfo(&authInfo);
		}
		term();
	}
	else PRINT_ERROR("init() failed\n");
	return 0;
}