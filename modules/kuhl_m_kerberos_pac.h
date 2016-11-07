/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include "kull_m_crypto_system.h"
#include "kull_m_kerberos_asn1_helper.h"
#include "kull_m_rpc_ms-pac.h"

#define KERB_NON_KERB_SALT					16
#define KERB_NON_KERB_CKSUM_SALT			17

#define PACINFO_TYPE_LOGON_INFO				0x00000001
#define PACINFO_TYPE_CHECKSUM_SRV			0x00000006
#define PACINFO_TYPE_CHECKSUM_KDC			0x00000007
#define PACINFO_TYPE_CNAME_TINFO			0x0000000a

#define DEFAULT_GROUP_ATTRIBUTES	(SE_GROUP_MANDATORY | SE_GROUP_ENABLED_BY_DEFAULT | SE_GROUP_ENABLED)
#define KIWI_NEVERTIME(filetime)	(*(PLONGLONG) filetime = MAXLONGLONG)

typedef struct _PAC_INFO_BUFFER {
	ULONG ulType;
	ULONG cbBufferSize;
	ULONG64 Offset;
} PAC_INFO_BUFFER, *PPAC_INFO_BUFFER;

typedef struct _PACTYPE {
	ULONG cBuffers;
	ULONG Version;
	PAC_INFO_BUFFER Buffers[ANYSIZE_ARRAY];
} PACTYPE, *PPACTYPE;

#pragma pack(push, 4) 
typedef struct _PAC_SIGNATURE_DATA {
	ULONG  SignatureType;
	UCHAR  Signature[ANYSIZE_ARRAY];// LM_NTLM_HASH_LENGTH];
	//USHORT RODCIdentifier;
	//USHORT  Reserverd;
} PAC_SIGNATURE_DATA, *PPAC_SIGNATURE_DATA;
#pragma pack(pop)

typedef struct _PAC_CLIENT_INFO {
	FILETIME ClientId;
	USHORT NameLength;
	WCHAR Name[ANYSIZE_ARRAY];
} PAC_CLIENT_INFO, *PPAC_CLIENT_INFO;

BOOL kuhl_m_pac_giveMePac(PCSTR Username, PCSTR LogonDomainName, PSID DomainSid, DWORD UserId, PGROUP_MEMBERSHIP groups, DWORD cbGroups, PKERB_SID_AND_ATTRIBUTES sids, DWORD cbSids, KerberosTime *AuthTime, DWORD SignatureType, EncryptionKey * SignatureKey, _octet1 *pac);

BOOL kuhl_m_pac_validationInfo_to_PAC(PKERB_VALIDATION_INFO validationInfo, DWORD SignatureType, PPACTYPE * pacType, DWORD * pacLength);
BOOL kuhl_m_pac_validationInfo_to_CNAME_TINFO(PKERB_VALIDATION_INFO validationInfo, PPAC_CLIENT_INFO * pacClientInfo, DWORD * pacClientInfoLength);
NTSTATUS kuhl_m_pac_signature(PPACTYPE pacType, DWORD pacLenght, DWORD SignatureType, LPCVOID key, DWORD keySize);