/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include "kull_m_rpce.h"
#include "kull_m_crypto_system.h"
#include "kull_m_samlib.h"
#include "kull_m_kerberos_asn1_helper.h"

#define KERB_NON_KERB_SALT					16
#define KERB_NON_KERB_CKSUM_SALT			17

#define PACINFO_TYPE_LOGON_INFO				0x00000001
#define PACINFO_TYPE_CHECKSUM_SRV			0x00000006
#define PACINFO_TYPE_CHECKSUM_KDC			0x00000007
#define PACINFO_TYPE_CNAME_TINFO			0x0000000a

#define PACINFO_ID_KERB_VALINFO				0x00020000
#define PACINFO_ID_KERB_EFFECTIVENAME		0x00020004
#define PACINFO_ID_KERB_FULLNAME			0x00020008
#define PACINFO_ID_KERB_LOGONSCRIPT			0x0002000c
#define PACINFO_ID_KERB_PROFILEPATH			0x00020010
#define PACINFO_ID_KERB_HOMEDIRECTORY		0x00020014
#define PACINFO_ID_KERB_HOMEDIRECTORYDRIVE	0x00020018
#define PACINFO_ID_KERB_GROUPIDS			0x0002001c
#define PACINFO_ID_KERB_LOGONSERVER			0x00020020
#define PACINFO_ID_KERB_LOGONDOMAINNAME		0x00020024
#define PACINFO_ID_KERB_LOGONDOMAINID		0x00020028
#define PACINFO_ID_KERB_EXTRASIDS			0x0002002c
#define PACINFO_ID_KERB_EXTRASID			0x00020030
#define PACINFO_ID_KERB_RESGROUPDOMAINSID	0x00020034
#define PACINFO_ID_KERB_RESGROUPIDS			0x00020038

#define USER_NORMAL_ACCOUNT			0x00000010
#define USER_DONT_EXPIRE_PASSWORD	0x00000200

#define DEFAULT_GROUP_ATTRIBUTES	(SE_GROUP_MANDATORY | SE_GROUP_ENABLED_BY_DEFAULT | SE_GROUP_ENABLED)
#define KIWI_NEVERTIME(filetime)	(*(PLONGLONG) filetime = MAXLONGLONG)

typedef struct _USER_SESSION_KEY {
	UCHAR data[16];
} USER_SESSION_KEY;

typedef struct _KERB_SID_AND_ATTRIBUTES {
	PISID Sid;
	DWORD Attributes;
} KERB_SID_AND_ATTRIBUTES, *PKERB_SID_AND_ATTRIBUTES;

typedef struct _KERB_VALIDATION_INFO {
	FILETIME LogonTime;
	FILETIME LogoffTime;
	FILETIME KickOffTime;
	FILETIME PasswordLastSet;
	FILETIME PasswordCanChange;
	FILETIME PasswordMustChange;
	LSA_UNICODE_STRING EffectiveName;
	LSA_UNICODE_STRING FullName;
	LSA_UNICODE_STRING LogonScript;
	LSA_UNICODE_STRING ProfilePath;
	LSA_UNICODE_STRING HomeDirectory;
	LSA_UNICODE_STRING HomeDirectoryDrive;
	USHORT LogonCount;
	USHORT BadPasswordCount;
	DWORD UserId;
	DWORD PrimaryGroupId;
	DWORD GroupCount;
	PGROUP_MEMBERSHIP GroupIds;
	ULONG UserFlags;
	USER_SESSION_KEY UserSessionKey;
	LSA_UNICODE_STRING LogonServer;
	LSA_UNICODE_STRING LogonDomainName;
	PISID LogonDomainId;
	ULONG Reserved1[2];
	ULONG UserAccountControl;
	ULONG SubAuthStatus;
	FILETIME LastSuccessfulILogon;
	FILETIME LastFailedILogon;
	ULONG FailedILogonCount;
	ULONG Reserved3;
	ULONG SidCount;
	PKERB_SID_AND_ATTRIBUTES ExtraSids;
	PISID ResourceGroupDomainSid;
	ULONG ResourceGroupCount;
	PGROUP_MEMBERSHIP ResourceGroupIds;
} KERB_VALIDATION_INFO, *PKERB_VALIDATION_INFO;

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

typedef struct _MARSHALLED_UNICODE_STRING {
	ULONG64 ReservedElements;
	ULONG32 Elements;
} MARSHALLED_UNICODE_STRING, *PMARSHALLED_UNICODE_STRING;

typedef struct _MARSHALL_UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	RPCEID ElementId;
} MARSHALL_UNICODE_STRING, *PMARSHALL_UNICODE_STRING;

typedef struct _MARSHALL_KERB_VALIDATION_INFO {
	FILETIME LogonTime;
	FILETIME LogoffTime;
	FILETIME KickOffTime;
	FILETIME PasswordLastSet;
	FILETIME PasswordCanChange;
	FILETIME PasswordMustChange;
	MARSHALL_UNICODE_STRING EffectiveName;
	MARSHALL_UNICODE_STRING FullName;
	MARSHALL_UNICODE_STRING LogonScript;
	MARSHALL_UNICODE_STRING ProfilePath;
	MARSHALL_UNICODE_STRING HomeDirectory;
	MARSHALL_UNICODE_STRING HomeDirectoryDrive;
	USHORT LogonCount;
	USHORT BadPasswordCount;
	ULONG UserId;
	ULONG PrimaryGroupId;
	ULONG GroupCount;
	RPCEID GroupIds;
	ULONG UserFlags;
	USER_SESSION_KEY UserSessionKey;
	MARSHALL_UNICODE_STRING LogonServer;
	MARSHALL_UNICODE_STRING LogonDomainName;
	RPCEID LogonDomainId;
	ULONG Reserved1[2];
	ULONG UserAccountControl;
	ULONG SubAuthStatus;
	FILETIME LastSuccessfulILogon;
	FILETIME LastFailedILogon;
	ULONG FailedILogonCount;
	ULONG Reserved3;
	ULONG SidCount;
	RPCEID ExtraSids;
	RPCEID ResourceGroupDomainSid;
	ULONG ResourceGroupCount;
	RPCEID ResourceGroupIds;
} MARSHALL_KERB_VALIDATION_INFO, *PMARSHALL_KERB_VALIDATION_INFO;

typedef struct _RPCE_KERB_VALIDATION_INFO {
	RPCE_COMMON_TYPE_HEADER	typeHeader;
	RPCE_PRIVATE_HEADER	privateHeader;
	RPCEID RootElementId;
	MARSHALL_KERB_VALIDATION_INFO infos;
} RPCE_KERB_VALIDATION_INFO, *PRPCE_KERB_VALIDATION_INFO;
#pragma pack(pop)

typedef struct _PAC_CLIENT_INFO {
	FILETIME ClientId;
	USHORT NameLength;
	WCHAR Name[ANYSIZE_ARRAY];
} PAC_CLIENT_INFO, *PPAC_CLIENT_INFO;

BOOL kuhl_m_pac_validationInfo_to_PAC(PKERB_VALIDATION_INFO validationInfo, DWORD SignatureType, PPACTYPE * pacType, DWORD * pacLength);
BOOL kuhl_m_pac_validationInfo_to_LOGON_INFO(PKERB_VALIDATION_INFO validationInfo, PRPCE_KERB_VALIDATION_INFO * rpceValidationInfo, DWORD * rpceValidationInfoLength);
BOOL kuhl_m_pac_validationInfo_to_CNAME_TINFO(PKERB_VALIDATION_INFO validationInfo, PPAC_CLIENT_INFO * pacClientInfo, DWORD * pacClientInfoLength);
NTSTATUS kuhl_m_pac_signature(PPACTYPE pacType, DWORD pacLenght, DWORD SignatureType, LPCVOID key, DWORD keySize);
BOOL kuhl_m_pac_giveMePac(PCSTR Username, PSID DomainSid, DWORD UserId, PGROUP_MEMBERSHIP groups, DWORD cbGroups, PKERB_SID_AND_ATTRIBUTES sids, DWORD cbSids, KerberosTime *AuthTime, DWORD SignatureType, EncryptionKey * SignatureKey, _octet1 *pac);