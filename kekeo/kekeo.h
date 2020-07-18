/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once

#include "globals.h"
#include "modules/kuhl_m_standard.h"
#include "modules/kuhl_m_tgt.h"
#include "modules/kuhl_m_tgs.h"
#include "modules/kuhl_m_exploit.h"
#include "modules/kuhl_m_misc.h"
#include "modules/kerberos/kuhl_m_kerberos.h"
#include "modules/kuhl_m_smb.h"
#include "modules/kuhl_m_ntlm.h"
#include "modules/kuhl_m_tsssp.h"
#include "modules/kuhl_m_server.h"

#include "../modules/kull_m_file.h"
#include "../modules/asn1/kull_m_kerberos_asn1.h"

extern VOID WINAPI RtlGetNtVersionNumbers(LPDWORD pMajor, LPDWORD pMinor, LPDWORD pBuild);

int wmain(int argc, wchar_t * argv[]);

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType);

NTSTATUS mimikatz_initOrClean(BOOL Init);

NTSTATUS mimikatz_doLocal(wchar_t * input);
NTSTATUS mimikatz_dispatchCommand(wchar_t * input);