/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"
#include "../kull_m_crypto_system.h"
#include "kull_m_kerberos_asn1.h"

typedef struct _KULL_M_KERBEROS_ASN1_CRYPTO_DUAL_STRING_DWORD {
	PCWSTR	name;
	DWORD	id;
} KULL_M_KERBEROS_ASN1_CRYPTO_DUAL_STRING_DWORD, *PKULL_M_KERBEROS_ASN1_CRYPTO_DUAL_STRING_DWORD;

NTSTATUS kull_m_kerberos_asn1_crypto_ekey_create_fromHexString(LPCWSTR key, EncryptionKey *ekey);
NTSTATUS kull_m_kerberos_asn1_crypto_ekey_create_fromPassword(LPCWSTR w_realm, LPCWSTR w_short_cname, LPCWSTR w_password, EncryptionKey *ekey);
void kull_m_kerberos_asn1_crypto_ekey_free(EncryptionKey *ekey);
void kull_m_kerberos_asn1_crypto_ekey_descr(EncryptionKey *ekey);

NTSTATUS kull_m_kerberos_asn1_crypto_encrypt(DWORD keyUsage, EncryptionKey *key, OssBuf *in, OssBuf *out, BOOL encrypt);

BOOL kull_m_kerberos_asn1_crypto_get_CertInfo(PCWSTR Subject, PKULL_M_CRYPTO_CERT_INFO certInfo);
void kull_m_kerberos_asn1_crypto_free_CertInfo(PKULL_M_CRYPTO_CERT_INFO certInfo);

BOOL kull_m_kerberos_asn1_crypto_simple_message_sign(PKULL_M_CRYPTO_CERT_INFO certInfo, OssBuf *input, _octet1 *output);
BOOL kull_m_kerberos_asn1_crypto_simple_message_dec(PKULL_M_CRYPTO_PROV_INFO provInfo, _octet1 *input, OssBuf *output);
BOOL kull_m_kerberos_asn1_crypto_simple_message_get(_octet1 *input, OssBuf *output);
BOOL kull_m_kerberos_asn1_crypto_genericEncode(__in LPCSTR lpszStructType, __in const void *pvStructInfo, __inout PBYTE *pvEncoded, __inout DWORD *pcbEncoded);
BOOL kull_m_kerberos_asn1_crypto_genericDecode(__in LPCSTR lpszStructType,  __in_bcount(cbEncoded) const BYTE *pbEncoded, __in DWORD cbEncoded, __out void **ppvStructInfo);


BOOL kull_m_kerberos_asn1_crypto_get_DHKeyInfo(BOOL integrated, BOOL withNonce, PKULL_M_CRYPTO_DH_KEY_INFO keyInfo);
void kull_m_kerberos_asn1_crypto_free_DHKeyInfo(PKULL_M_CRYPTO_DH_KEY_INFO keyInfo);
BOOL kull_m_kerberos_asn1_crypto_get_DHKeyInfo_Parameters(HCRYPTKEY hKey, PCERT_X942_DH_PARAMETERS parameters);
void kull_m_kerberos_asn1_crypto_free_DHKeyInfo_Parameters(PCERT_X942_DH_PARAMETERS parameters);
void kull_m_kerberos_asn1_crypto_reverseit(PVOID data, DWORD dwData);
void kull_m_kerberos_asn1_crypto_k_truncate(PVOID input, DWORD cbInput, PVOID output, DWORD cbOutput);
BOOL kull_m_kerberos_asn1_crypto_octetstring2key(PVOID input, DWORD cbInput, DHNonce *client, DHNonce *server, EncryptionKey *ekey);

BOOL kull_m_kerberos_asn1_crypto_get_CertFromCA(PCWSTR caname, PCWSTR castore, PCWSTR upn, PCWSTR crldp, PKULL_M_CRYPTO_CERT_INFO certInfo);
void kull_m_kerberos_asn1_crypto_free_CertFromCA(PKULL_M_CRYPTO_CERT_INFO certInfo);
BOOL kull_m_kerberos_asn1_crypto_sc_auth_Ext_AltUPN(PCERT_EXTENSION pCertExtension, LPCWSTR upn);
BOOL kull_m_kerberos_asn1_crypto_sc_auth_Ext_KU(PCERT_EXTENSION pCertExtension, WORD bits);
BOOL kull_m_kerberos_asn1_crypto_sc_auth_Ext_EKU(PCERT_EXTENSION pCertExtension, DWORD count, ...);
BOOL kull_m_kerberos_asn1_crypto_sc_auth_Ext_CDP(PCERT_EXTENSION pCertExtension, DWORD count, ...);
__inline void kull_m_kerberos_asn1_crypto_sc_auth_Ext_Free(PCERT_EXTENSION pCertExtension);
DWORD kull_m_kerberos_asn1_crypto_system_store_to_dword(PCWSTR name);
PCWCHAR kull_m_kerberos_asn1_crypto_etype(LONG eType);
PCWCHAR kull_m_kerberos_asn1_crypto_ctype(LONG cType);