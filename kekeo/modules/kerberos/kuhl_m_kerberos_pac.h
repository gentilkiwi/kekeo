/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m.h"
#include "kuhl_m_kerberos_claims.h"
#include "../modules/kull_m_file.h"
#include "../modules/kull_m_crypto_system.h"
#include "../modules/rpc/kull_m_rpc_ms-pac.h"
#include "../modules/asn1/kull_m_kerberos_asn1.h"

#define DEFAULT_GROUP_ATTRIBUTES	(SE_GROUP_MANDATORY | SE_GROUP_ENABLED_BY_DEFAULT | SE_GROUP_ENABLED)

#pragma pack(push, 4) 
typedef struct _PAC_SIGNATURE_DATA {
	LONG  SignatureType;
	UCHAR  Signature[ANYSIZE_ARRAY];// LM_NTLM_HASH_LENGTH];
	//USHORT RODCIdentifier;
	//USHORT  Reserverd;
} PAC_SIGNATURE_DATA, *PPAC_SIGNATURE_DATA;
#pragma pack(pop)

BOOL kuhl_m_pac_validationInfo_to_PAC(PKERB_VALIDATION_INFO validationInfo, PFILETIME authtime, LPCWSTR clientname, LONG SignatureType, PCLAIMS_SET pClaimsSet, PPACTYPE * pacType, DWORD * pacLength);
BOOL kuhl_m_pac_validationInfo_to_CNAME_TINFO(PFILETIME authtime, LPCWSTR clientname, PPAC_CLIENT_INFO * pacClientInfo, DWORD * pacClientInfoLength);
NTSTATUS kuhl_m_pac_signature(PPACTYPE pacType, DWORD pacLenght, LONG SignatureType, LPCVOID key, DWORD keySize);
PKERB_VALIDATION_INFO kuhl_m_pac_infoToValidationInfo(PFILETIME authtime, LPCWSTR username, LPCWSTR domainname, LPCWSTR LogonDomainName, PISID sid, ULONG rid, PGROUP_MEMBERSHIP groups, DWORD cbGroups, PKERB_SID_AND_ATTRIBUTES sids, DWORD cbSids);
BOOL kuhl_m_pac_stringToGroups(PCWSTR szGroups, PGROUP_MEMBERSHIP *groups, DWORD *cbGroups);
BOOL kuhl_m_pac_stringToSids(PCWSTR szSids, PKERB_SID_AND_ATTRIBUTES *sids, DWORD *cbSids);

BOOL kuhl_m_kerberos_pac_to_infos(PPACTYPE pacType, DWORD pacLenght, PISID *sid, DWORD *rid);
void kuhl_m_kerberos_pac_info_data(PPACTYPE pacType, DWORD pacLenght, EncryptionKey *AsRepKey);
void kuhl_m_kerberos_pac_info_data_credentialinfo(PPAC_CREDENTIAL_INFO pCredentialInfo, ULONG uCredentialInfo, EncryptionKey *AsRepKey);