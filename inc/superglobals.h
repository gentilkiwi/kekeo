/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <stdio.h>
#include <Windows.h>
#include <NTSecAPI.h>
#include <Sddl.h>
#include <NtDsAPI.h>
#include <NTSecAPI.h>
#include <Dsgetdc.h>
#include <LM.h>

#include "../modules/kull_m_string.h"

#define MIMIKATZ_ARCH			"x86"
#define MIMIKATZ_CODENAME		"A La Vie, A L\'Amour"
#define MIMIKATZ_FULL			MIMIKATZ " " MIMIKATZ_VERSION " (" MIMIKATZ_ARCH ") built on " TEXT(__DATE__) " " TEXT(__TIME__)
#define MIMIKATZ_SECOND			"\"" MIMIKATZ_CODENAME "\""

#define kprintf					printf

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

#ifndef PRINT_ERROR
#define PRINT_ERROR(...) (kprintf("ERROR " TEXT(__FUNCTION__) " ; " __VA_ARGS__))
#endif

#ifndef PRINT_ERROR_AUTO
#define PRINT_ERROR_AUTO(func) (kprintf("ERROR " TEXT(__FUNCTION__) " ; " func " (0x%08x)\n", GetLastError()))
#endif

#ifndef W00T
#define W00T(...) (kprintf(TEXT(__FUNCTION__) " w00t! ; " __VA_ARGS__))
#endif

DWORD MIMIKATZ_NT_MAJOR_VERSION, MIMIKATZ_NT_MINOR_VERSION, MIMIKATZ_NT_BUILD_NUMBER;
extern VOID WINAPI RtlGetNtVersionNumbers(LPDWORD pMajor, LPDWORD pMinor, LPDWORD pBuild);

#define LM_NTLM_HASH_LENGTH	16