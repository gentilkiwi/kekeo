/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#define SECURITY_WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <security.h>
#include <stdio.h>
#include <sddl.h>
#include <ntsecapi.h>
#include <ntsecpkg.h>
#include <wchar.h>
#include "../modules/kull_m_output.h"
#ifdef _M_X64
	#define MIMIKATZ_ARCH L"x64"
#else ifdef _M_IX86
	#define MIMIKATZ_ARCH L"x86"
#endif

#define MIMIKATZ				L"kekeo"
#define MIMIKATZ_VERSION		L"2.1"
#define MIMIKATZ_CODENAME		L"A La Vie, A L\'Amour"
#define MIMIKATZ_FULL			MIMIKATZ L" " MIMIKATZ_VERSION L" (" MIMIKATZ_ARCH L") built on " TEXT(__DATE__) L" " TEXT(__TIME__)
#define MIMIKATZ_SECOND			L"\"" MIMIKATZ_CODENAME L"\""
#define MIMIKATZ_SPECIAL		L"                                "
#define MIMIKATZ_DEFAULT_LOG	MIMIKATZ L".log"
#define MIMIKATZ_KERBEROS_EXT	L"kirbi"
#define MIMIKATZ_NONCE			1853451123

#ifdef _WINDLL
	#define MIMIKATZ_AUTO_COMMAND_START		0
	#define MIMIKATZ_AUTO_COMMAND_STRING	L"powershell"
#else
	#define MIMIKATZ_AUTO_COMMAND_START		1
	#define MIMIKATZ_AUTO_COMMAND_STRING	L"commandline"
#endif

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

#ifndef PRINT_ERROR
#define PRINT_ERROR(...) (kprintf(L"ERROR " TEXT(__FUNCTION__) L" ; " __VA_ARGS__))
#endif

#ifndef PRINT_ERROR_AUTO
#define PRINT_ERROR_AUTO(func) (kprintf(L"ERROR " TEXT(__FUNCTION__) L" ; " func L" (0x%08x)\n", GetLastError()))
#endif

#ifndef W00T
#define W00T(...) (kprintf(TEXT(__FUNCTION__) L" w00t! ; " __VA_ARGS__))
#endif

DWORD MIMIKATZ_NT_MAJOR_VERSION, MIMIKATZ_NT_MINOR_VERSION, MIMIKATZ_NT_BUILD_NUMBER;
BOOL g_isBreak;

#define SIZE_ALIGN(size, alignment)	(size + ((size % alignment) ? (alignment - (size % alignment)) : 0))
#define KIWI_NEVERTIME(filetime)	(*(PLONGLONG) filetime = MAXLONGLONG)

#define LM_NTLM_HASH_LENGTH	16