/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m.h"
#include "../modules/kull_m_file.h"
#include "../modules/asn1/kull_m_kerberos_asn1.h"

const KUHL_M kuhl_m_kerberos;

NTSTATUS kuhl_m_kerberos_init();
NTSTATUS kuhl_m_kerberos_clean();

NTSTATUS LsaCallKerberosPackage(PVOID ProtocolSubmitBuffer, ULONG SubmitBufferLength, PVOID *ProtocolReturnBuffer, PULONG ReturnBufferLength, PNTSTATUS ProtocolStatus);

NTSTATUS kuhl_m_kerberos_ptt(int argc, wchar_t * argv[]);
BOOL CALLBACK kuhl_m_kerberos_ptt_directory(DWORD level, PCWCHAR fullpath, PCWCHAR path, PVOID pvArg);
void kuhl_m_kerberos_ptt_file(PCWCHAR filename, PrincipalName *pAltService);
NTSTATUS CALLBACK kuhl_m_kerberos_ptt_data(PVOID data, DWORD dataSize, PrincipalName *sname);
NTSTATUS kuhl_m_kerberos_list(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_kerberos_ask(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_kerberos_purge(int argc, wchar_t * argv[]);