/*	Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com / http://blog.gentilkiwi.com )
	Vincent LE TOUX ( vincent.letoux@gmail.com / http://www.mysmartlogon.com )
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include <DsGetDC.h>
#include <LM.h>
#include "modules/kull_m_string.h"
#include "modules/kull_m_crypto_system.h"
#include "rpc/rpc_factory.h"

#define ATT_RDN							589825
#define ATT_OBJECT_SID					589970
#define ATT_WHEN_CREATED				131074
#define ATT_WHEN_CHANGED				131075

#define ATT_SAM_ACCOUNT_NAME			590045
#define ATT_USER_PRINCIPAL_NAME			590480
#define ATT_SERVICE_PRINCIPAL_NAME		590595
#define ATT_SID_HISTORY					590433

#define ATT_SAM_ACCOUNT_TYPE			590126
#define ATT_LOGON_HOURS					589888
#define ATT_LOGON_WORKSTATION			589889
#define ATT_LAST_LOGON					589876
#define ATT_PWD_LAST_SET				589920
#define ATT_ACCOUNT_EXPIRES				589983
#define ATT_LOCKOUT_TIME				590486

#define ATT_UNICODE_PWD					589914
#define ATT_NT_PWD_HISTORY				589918
#define ATT_DBCS_PWD					589879
#define ATT_LM_PWD_HISTORY				589984
#define ATT_SUPPLEMENTAL_CREDENTIALS	589949

#define ATT_CURRENT_VALUE				589851

#define ATT_TRUST_ATTRIBUTES			590294
#define ATT_TRUST_AUTH_INCOMING			589953
#define ATT_TRUST_AUTH_OUTGOING			589959
#define ATT_TRUST_DIRECTION				589956
#define ATT_TRUST_PARENT				590295
#define ATT_TRUST_PARTNER				589957
#define ATT_TRUST_TYPE					589960

#pragma pack(push, 1) 
typedef struct _USER_PROPERTY {
	USHORT NameLength;
	USHORT ValueLength;
	USHORT Reserved;
	wchar_t PropertyName[ANYSIZE_ARRAY];
	// PropertyValue in HEX !
} USER_PROPERTY, *PUSER_PROPERTY;

typedef struct _USER_PROPERTIES {
	DWORD Reserved1;
	DWORD Length;
	USHORT Reserved2;
	USHORT Reserved3;
	BYTE Reserved4[96];
	wchar_t PropertySignature;
	USHORT PropertyCount;
	USER_PROPERTY UserProperties[ANYSIZE_ARRAY];
} USER_PROPERTIES, *PUSER_PROPERTIES;
#pragma pack(pop)

typedef struct _WDIGEST_CREDENTIALS {
	BYTE	Reserverd1;
	BYTE	Reserverd2;
	BYTE	Version;
	BYTE	NumberOfHashes;
	BYTE	Reserverd3[12];
	BYTE	Hash[ANYSIZE_ARRAY][MD5_DIGEST_LENGTH];
} WDIGEST_CREDENTIALS, *PWDIGEST_CREDENTIALS;

typedef struct _KERB_KEY_DATA {
	USHORT	Reserverd1;
	USHORT	Reserverd2;
	ULONG	Reserverd3;
	LONG	KeyType;
	ULONG	KeyLength;
	ULONG	KeyOffset;
} KERB_KEY_DATA, *PKERB_KEY_DATA;

typedef struct _KERB_STORED_CREDENTIAL {
	USHORT	Revision;
	USHORT	Flags;
	USHORT	CredentialCount;
	USHORT	OldCredentialCount;
	USHORT	DefaultSaltLength;
	USHORT	DefaultSaltMaximumLength;
	ULONG	DefaultSaltOffset;
	//KERB_KEY_DATA	Credentials[ANYSIZE_ARRAY];
	//KERB_KEY_DATA	OldCredentials[ANYSIZE_ARRAY];
	//BYTE	DefaultSalt[ANYSIZE_ARRAY];
	//BYTE	KeyValues[ANYSIZE_ARRAY];
} KERB_STORED_CREDENTIAL, *PKERB_STORED_CREDENTIAL;

typedef struct _KERB_KEY_DATA_NEW {
	USHORT	Reserverd1;
	USHORT	Reserverd2;
	ULONG	Reserverd3;
	ULONG	IterationCount;
	LONG	KeyType;
	ULONG	KeyLength;
	ULONG	KeyOffset;
} KERB_KEY_DATA_NEW, *PKERB_KEY_DATA_NEW;

typedef struct _KERB_STORED_CREDENTIAL_NEW {
	USHORT	Revision;
	USHORT	Flags;
	USHORT	CredentialCount;
	USHORT	ServiceCredentialCount;
	USHORT	OldCredentialCount;
	USHORT	OlderCredentialCount;
	USHORT	DefaultSaltLength;
	USHORT	DefaultSaltMaximumLength;
	ULONG	DefaultSaltOffset;
	ULONG	DefaultIterationCount;
	//KERB_KEY_DATA_NEW	Credentials[ANYSIZE_ARRAY];
	//KERB_KEY_DATA_NEW	ServiceCredentials[ANYSIZE_ARRAY];
	//KERB_KEY_DATA_NEW	OldCredentials[ANYSIZE_ARRAY];
	//KERB_KEY_DATA_NEW	OlderCredentials[ANYSIZE_ARRAY];
	//BYTE	DefaultSalt[ANYSIZE_ARRAY];
	//BYTE	KeyValues[ANYSIZE_ARRAY];
} KERB_STORED_CREDENTIAL_NEW, *PKERB_STORED_CREDENTIAL_NEW;

SecPkgContext_SessionKey g_sKey;

int wmain(int argc, wchar_t * argv[]);
void RPC_ENTRY RpcSecurityCallback(_In_ void *Context);
PVOID findMonoAttr(ATTRBLOCK *attributes, ATTRTYP type, PVOID data, DWORD *size);
void findPrintMonoAttr(LPCWSTR prefix, ATTRBLOCK *attributes, ATTRTYP type, BOOL newLine);
void descrUser(ATTRBLOCK *attributes);
void descrUserProperties(PUSER_PROPERTIES properties);
PKERB_KEY_DATA kuhl_m_lsadump_lsa_keyDataInfo(PVOID base, PKERB_KEY_DATA keys, USHORT Count, PCWSTR title);
PKERB_KEY_DATA_NEW kuhl_m_lsadump_lsa_keyDataNewInfo(PVOID base, PKERB_KEY_DATA_NEW keys, USHORT Count, PCWSTR title);
BOOL decrypt(PBYTE encodedData, DWORD encodedDataSize, DWORD rid, LPCWSTR prefix, BOOL isHistory);
PCWCHAR kuhl_m_kerberos_ticket_etype(LONG eType);