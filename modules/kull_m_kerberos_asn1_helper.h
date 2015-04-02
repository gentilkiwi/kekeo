/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "superglobals.h"
#include "kull_m_kerberos_asn1.h"
#include "kull_m_crypto_system.h"

BOOL kull_m_kerberos_asn1_helper_init();
BOOL kull_m_kerberos_asn1_helper_term();

void kull_m_kerberos_asn1_helper_ossFreeBuf(void *data);
int kull_m_kerberos_asn1_helper_ossFreePDU(int pdunum, void *data);
int kull_m_kerberos_asn1_helper_ossPrintPDU(int pdunum, void *data);
int kull_m_kerberos_asn1_helper_ossDecode(int pdunum, OssBuf *input, void **output);
int kull_m_kerberos_asn1_helper_ossEncode(int pdunum, void * input, OssBuf *output);
int kull_m_kerberos_asn1_helper_ossCpyValue(int pdunum, void *source, void **destination);
char * kull_m_kerberos_asn1_helper_ossGetErrMsg();

void kull_m_kerberos_asn1_helper_init_PrincipalName(PrincipalName * name, INT name_type, DWORD count, ...);
void kull_m_kerberos_asn1_helper_init_KerberosTime(KerberosTime *time, PSYSTEMTIME pSystemTime, BOOL isMaxMs2037);
void kull_m_kerberos_asn1_helper_init_KerberosTime2(KerberosTime *time, PFILETIME pFileTime, BOOL isMaxMs2037);
void kull_m_kerberos_asn1_helper_init_KerberosTime3(KerberosTime *time, time_t uTime);

void kull_m_kerberos_asn1_helper_get_KerberosTime(KerberosTime *time, PSYSTEMTIME pSystemTime);
void kull_m_kerberos_asn1_helper_get_KerberosTime2(KerberosTime *time, PFILETIME pFileTime);
void kull_m_kerberos_asn1_helper_get_KerberosTime3(KerberosTime *time, time_t * uTime);

int kull_m_kerberos_asn1_helper_init_PA_DATA_encTimeStamp(PA_DATA *data, EncryptionKey *key);
int kull_m_kerberos_asn1_helper_init_PA_DATA_PacRequest(PA_DATA *data, BOOL request);
BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_TGS_REQ(PA_DATA *data, PCSTR Username, PCSTR Domain, Ticket *ticket, EncryptionKey *key);
void kull_m_kerberos_asn1_helper_init_PADATAs(_seqof4 *padata, DWORD count, ...);

BOOL kull_m_kerberos_asn1_helper_build_ApReq(OssBuf * ApReqData, PCSTR Username, PCSTR Domain, Ticket *ticket, EncryptionKey *key, ULONG keyUsage, EncryptionKey *authenticatorNewKey, UInt32 *authenticatorNewSeq);
BOOL kull_m_kerberos_asn1_helper_build_AuthorizationData(OssBuf * AuthData, _octet1 *pac);
BOOL kull_m_kerberos_asn1_helper_build_KdcReq(PCSTR Username, PCSTR Domain, EncryptionKey *key, PCSTR Service, PCSTR Target, BOOL PacRequest, Ticket *ticket, _octet1 *pac, OssBuf *OutKdcReq);
BOOL kull_m_kerberos_asn1_helper_build_KrbPriv(_octet1 *data, EncryptionKey *key, PCSTR machineName, OssBuf *OutKrbPriv, UInt32 *seq);
BOOL kull_m_kerberos_asn1_helper_build_KrbCred(Realm *prealm, PrincipalName *pname, EncKDCRepPart *repPart, Ticket *ticket, OssBuf *OutKrbCred);
BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep(KDC_REP *rep, EncKDCRepPart ** encRepPart, EncryptionKey *key, int pdu);
BOOL kull_m_kerberos_asn1_helper_build_EncKrbPrivPart_from_Priv(KRB_PRIV *priv, EncKrbPrivPart ** encKrbPrivPart, EncryptionKey *authKey);

void kull_m_kerberos_asn1_helper_util_UTCKerberosTimeToFileTime(KerberosTime *time, PFILETIME pFileTime);
NTSTATUS kull_m_kerberos_asn1_helper_util_encrypt(ULONG keyUsage, EncryptionKey *key, OssBuf *in, OssBuf *out, BOOL encrypt);
NTSTATUS kull_m_kerberos_asn1_helper_util_stringToKey(PCSTR user, PCSTR domain, PCSTR password, PCSTR key, EncryptionKey *eKey);
PCSTR kull_m_kerberos_asn1_helper_util_etypeToString(LONG eType);
BOOL kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(OssBuf *data, int pdu, LPVOID *out);
PCSTR kull_m_kerberos_asn1_helper_util_err_to_string(DWORD id);

typedef struct _KULL_M_KERBEROS_ASN1_HELPER_UTIL_ERR{
	DWORD	id;
	PCSTR	name;
} KULL_M_KERBEROS_ASN1_HELPER_UTIL_ERR, *PKULL_M_KERBEROS_ASN1_HELPER_UTIL_ERR;

#define KRB_KEY_USAGE_AS_REQ_PA_ENC_TIMESTAMP		1
#define KRB_KEY_USAGE_AS_REP_TGS_REP				2
#define KRB_KEY_USAGE_AS_REP_EP_SESSION_KEY			3
#define KRB_KEY_USAGE_AS_REQ_AUTHORIZATION_SESSION	4

#define KRB_KEY_USAGE_TGS_REQ_PA_AUTHENTICATOR		7
#define KRB_KEY_USAGE_TGS_REP_EP_SESSION_KEY		8

#define KRB_KEY_USAGE_AP_REQ_AUTHENTICATOR			11
#define KRB_KEY_USAGE_KRB_PRIV_ENCRYPTED_PART		13

#define PA_TYPE_TGS_REQ				1
#define PA_TYPE_ENC_TIMESTAMP		2
#define PA_TYPE_PAC_REQUEST			128

#define AD_TYPE_IF_RELEVANT			1
#define AD_TYPE_KDCIssued			4
#define AD_TYPE_AND_OR				5
#define AD_TYPE_MANDATORY_FOR_KDC	8
#define AD_TYPE_WIN2K_PAC			128

NTSTATUS LsaCallKerberosPackage(PVOID ProtocolSubmitBuffer, ULONG SubmitBufferLength, PVOID *ProtocolReturnBuffer, PULONG ReturnBufferLength, PNTSTATUS ProtocolStatus);
NTSTATUS kuhl_m_kerberos_ptt_data(PVOID data, DWORD dataSize);