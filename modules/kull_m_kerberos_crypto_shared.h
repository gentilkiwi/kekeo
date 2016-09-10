/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "superglobals.h"
#include "kull_m_kerberos_asn1.h"
#include "kull_m_crypto_system.h"

typedef struct _KULL_M_CRYPTO_DH_KEY_INFO {
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	DHNonce dhClientNonce;
} KULL_M_CRYPTO_DH_KEY_INFO, *PKULL_M_CRYPTO_DH_KEY_INFO;

typedef struct _KULL_M_CRYPTO_PROV_INFO {
	HCRYPTPROV hProv;
	DWORD dwKeySpec;
} KULL_M_CRYPTO_PROV_INFO, *PKULL_M_CRYPTO_PROV_INFO;

typedef struct _KULL_M_CRYPTO_CERT_INFO {
	HCERTSTORE hCertStore;
	PCCERT_CONTEXT pCertContext;
	KULL_M_CRYPTO_PROV_INFO provider;
} KULL_M_CRYPTO_CERT_INFO, *PKULL_M_CRYPTO_CERT_INFO;

typedef struct _KULL_M_CRYPTO_CERT_INFO_DH {
	KULL_M_CRYPTO_CERT_INFO certinfo;
	KULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo;
	CRYPT_KEY_PROV_INFO tmpKey;
} KULL_M_CRYPTO_CERT_INFO_DH, *PKULL_M_CRYPTO_CERT_INFO_DH;

typedef struct _KULL_M_CRYPTO_ASREQ_RSA_DH {
	OssBuf AsReqBuf;
	AS_REQ *AsReq;
	KULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo;
} KULL_M_CRYPTO_ASREQ_RSA_DH, *PKULL_M_CRYPTO_ASREQ_RSA_DH;

typedef enum _KIWI_AUTH_INFOS_TYPE {
	KIWI_AUTH_INFOS_TYPE_KEY,
	KIWI_AUTH_INFOS_TYPE_RSA,
	KIWI_AUTH_INFOS_TYPE_RSA_DH,
	KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH,
	KIWI_AUTH_INFOS_TYPE_OTF_RSA,
	KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH,
} KIWI_AUTH_INFOS_TYPE, PKIWI_AUTH_INFOS_TYPE;

typedef struct _KIWI_AUTH_INFOS {
	LPCSTR szUser;
	LPCSTR szDomain;
	LPSTR szNetbiosDomain;
	LPCSTR szPassword;
	KIWI_AUTH_INFOS_TYPE type;
	union {
		EncryptionKey userKey;
		KULL_M_CRYPTO_CERT_INFO_DH certInfoDH;
		KULL_M_CRYPTO_ASREQ_RSA_DH asReqDH;
	} u;
} KIWI_AUTH_INFOS, *PKIWI_AUTH_INFOS;