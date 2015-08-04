/*	Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com / http://blog.gentilkiwi.com )
	Vincent LE TOUX ( vincent.letoux@gmail.com / http://www.mysmartlogon.com )
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#define SECURITY_WIN32
#include <windows.h>
#include <security.h>
#include <stdio.h>
#include <sddl.h>
#include <NTSecAPI.h>

#define MIMIKATZ				L"DCSync"
#define MIMIKATZ_VERSION		L"1.0"
#define MIMIKATZ_CODENAME		L"S**c me I\'m famous"
#define MIMIKATZ_FULL			MIMIKATZ L" " MIMIKATZ_VERSION L" \"" MIMIKATZ_CODENAME L"\" (" TEXT(__DATE__) L" " TEXT(__TIME__) L")"

#define kprintf wprintf

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

#define LM_NTLM_HASH_LENGTH	16