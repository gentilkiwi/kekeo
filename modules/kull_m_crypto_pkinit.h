/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "kull_m_kerberos_crypto_shared.h"
#include "kull_m_file.h"

typedef struct _KULL_M_CRYPTO_DUAL_STRING_DWORD {
	PCWSTR	name;
	DWORD	id;
} KULL_M_CRYPTO_DUAL_STRING_DWORD, *PKULL_M_CRYPTO_DUAL_STRING_DWORD;

BOOL kull_m_crypto_get_CertInfo(PCSTR Subject, PKULL_M_CRYPTO_CERT_INFO certInfo);
void kull_m_crypto_free_CertInfo(PKULL_M_CRYPTO_CERT_INFO certInfo);
BOOL kull_m_crypto_simple_message_sign(PKULL_M_CRYPTO_CERT_INFO certInfo, OssBuf *input, _octet1 *output);
BOOL kull_m_crypto_simple_message_dec(PKULL_M_CRYPTO_PROV_INFO provInfo, _octet1 *input, OssBuf *output);
BOOL kull_m_crypto_simple_message_get(_octet1 *input, OssBuf *output);

BOOL kull_m_crypto_get_DHKeyInfo(BOOL integrated, BOOL withNonce, PKULL_M_CRYPTO_DH_KEY_INFO keyInfo);
void kull_m_crypto_free_DHKeyInfo(PKULL_M_CRYPTO_DH_KEY_INFO keyInfo);
BOOL kull_m_crypto_get_DHKeyInfo_Parameters(HCRYPTKEY hKey, PCERT_X942_DH_PARAMETERS parameters);
void kull_m_crypto_free_DHKeyInfo_Parameters(PCERT_X942_DH_PARAMETERS parameters);

BOOL kull_m_crypto_get_CertFromCA(PCSTR sNameCA, PCSTR sStoreCA, PCSTR sUPN, PKULL_M_CRYPTO_CERT_INFO certInfo, PCRYPT_KEY_PROV_INFO keyInfo);
void kull_m_crypto_free_CertFromCA(PKULL_M_CRYPTO_CERT_INFO certInfo, PCRYPT_KEY_PROV_INFO keyInfo);

void k_truncate(PVOID input, DWORD cbInput, PVOID output, DWORD cbOutput);
BOOL octetstring2key(PVOID input, DWORD cbInput, DHNonce *client, DHNonce *server, EncryptionKey *ekey);

BOOL kull_m_crypto_genericEncode(__in LPCSTR lpszStructType, __in const void *pvStructInfo, __inout PBYTE *pvEncoded, __inout DWORD *pcbEncoded);
BOOL kull_m_crypto_genericDecode(__in LPCSTR lpszStructType,  __in_bcount(cbEncoded) const BYTE *pbEncoded, __in DWORD cbEncoded, __out void **ppvStructInfo);

DWORD kull_m_crypto_system_store_to_dword(PCWSTR name);