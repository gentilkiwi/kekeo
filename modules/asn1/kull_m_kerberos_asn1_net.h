/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"
#include "kull_m_kerberos_asn1.h"
#include <dsgetdc.h>
#include "../kull_m_sock.h"

#define KERBEROS_DEFAULT_PORT	((WORD) 88)
#define KPASSWD_DEFAULT_PORT	((WORD) 464)

typedef struct _KULL_M_KERBEROS_ASN1_HELPER_UTIL_ERR{
	DWORD	id;
	PCWSTR	name;
} KULL_M_KERBEROS_ASN1_HELPER_UTIL_ERR, *PKULL_M_KERBEROS_ASN1_HELPER_UTIL_ERR;

BOOL kull_m_kerberos_asn1_net_callKdcOssBuf(PKULL_M_SOCK fullsocket, OssBuf *in, LPVOID * out, int outPdu);
BOOL kull_m_kerberos_asn1_net_callKadminOssBuf(PKULL_M_SOCK fullsocket, USHORT version, OssBuf *ReqIn, OssBuf *KrbPrivIn, AP_REP **ApRep, KRB_PRIV **KrbPriv);
BOOL kull_m_kerberos_asn1_net_SendAndRecv(PKULL_M_SOCK fullsocket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize);
BOOL kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(OssBuf *data, int pdu, LPVOID *out);
PCWSTR kull_m_kerberos_asn1_helper_util_err_to_string(DWORD id);

PKULL_M_SOCK kull_m_kerberos_asn1_net_AddressSocket_create(LPCWSTR domain, WORD port, int argc, wchar_t * argv[], BOOL withConnect);
void kull_m_kerberos_asn1_net_AddressSocket_delete(PKULL_M_SOCK fullsocket);