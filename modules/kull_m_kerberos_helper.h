/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "kull_m_kerberos_asn1_helper.h"
#include "kull_m_sock.h"
#include "kull_m_file.h"
#include "kull_m_samlib.h"

BOOL kull_m_kerberos_helper_init();
BOOL kull_m_kerberos_helper_term();

BOOL kull_m_kerberos_helper_net_SendAndRecv(SOCKET *Socket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize);
BOOL kull_m_kerberos_helper_net_callKdcOssBuf(SOCKET *Socket, OssBuf *in, LPVOID * out, int outPdu);
BOOL kull_m_kerberos_helper_net_callKadminOssBuf(SOCKET *Socket, OssBuf *ReqIn, OssBuf *KrbPrivIn, AP_REP **ApRep, KRB_PRIV **KrbPriv);

BOOL kull_m_kerberos_helper_util_SaveRepAsKrbCred(KDC_REP *rep, EncKDCRepPart *encRepPart, LPCSTR filename);

NTSTATUS kull_m_kerberos_helper_util_LsaCallKerberosPackage(PVOID ProtocolSubmitBuffer, ULONG SubmitBufferLength, PVOID *ProtocolReturnBuffer, PULONG ReturnBufferLength, PNTSTATUS ProtocolStatus);
NTSTATUS kull_m_kerberos_helper_util_ptt_data(PVOID data, DWORD dataSize);
BOOL kull_m_kerberos_helper_net_getDC(LPCSTR fullDomainName, DWORD altFlags, LPSTR * fullDCName);
void kull_m_kerberos_helper_util_impersonateToGetData(PCSTR user, PCSTR domain, PCSTR password, PCSTR kdc, PSID *sid, DWORD *rid, DWORD *pNbDc, PDS_DOMAIN_CONTROLLER_INFO_1 *dcInfos);