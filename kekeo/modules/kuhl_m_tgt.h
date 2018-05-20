/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "kuhl_m.h"
#include "../../modules/asn1/kull_m_kerberos_asn1.h"
#include "../../modules/asn1/kull_m_kerberos_asn1_authinfos.h"
#include "../../modules/kull_m_file.h"
#include "kerberos/kuhl_m_kerberos_pac.h"
#include "kerberos/kuhl_m_kerberos.h"

const KUHL_M kuhl_m_tgt;

NTSTATUS kuhl_m_tgt_ask(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_tgt_pac(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_tgt_asreq(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_tgt_deleg(int argc, wchar_t * argv[]);

BOOL kuhl_m_tgt_pac_cred(_octet1 *buf, EncryptionKey *AsRepKey);
BOOL kuhl_m_tgt_asreq_export(DWORD cookie, PFILETIME fTime, PKIWI_AUTH_INFOS authInfo, OssBuf *asReq);

PBYTE kuhl_m_tgt_deleg_searchDataAferOIDInSecBuffer(IN PSecBuffer data);
PVOID kuhl_m_tgt_deleg_searchInMemory(IN const OssEncodedOID *oid, IN LPCVOID Start, IN SIZE_T Size);
BOOL kuhl_m_tgt_deleg_EncryptionKeyFromCache(LPCWCHAR Target, Int32 etype, EncryptionKey *key);