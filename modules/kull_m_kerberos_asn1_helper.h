/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "superglobals.h"
#include "kull_m_kerberos_asn1.h"
#include "kull_m_kerberos_crypto_shared.h"
#include "kull_m_crypto_pkinit.h"

#define KERB_KDCOPTION_reserved					0x80000000
#define KERB_KDCOPTION_forwardable				0x40000000
#define KERB_KDCOPTION_forwarded				0x20000000
#define KERB_KDCOPTION_proxiable				0x10000000
#define KERB_KDCOPTION_proxy					0x08000000
#define KERB_KDCOPTION_allow_postdate			0x04000000
#define KERB_KDCOPTION_postdated				0x02000000
#define KERB_KDCOPTION_renewable				0x00800000
#define KERB_KDCOPTION_opt_hardware_auth		0x00100000
#define KERB_KDCOPTION_request_anonymous		0x00020000
#define KERB_KDCOPTION_canonicalize				0x00010000
#define KERB_KDCOPTION_constrained_delegation	0x00008000
#define KERB_KDCOPTION_disable_transition_check	0x00000020
#define KERB_KDCOPTION_renewable_ok				0x00000010
#define KERB_KDCOPTION_enc_tkt_in_skey			0x00000008
#define KERB_KDCOPTION_renew					0x00000002
#define KERB_KDCOPTION_validate					0x00000001

#define KERB_KDCOPTION_standard					KERB_KDCOPTION_forwardable | KERB_KDCOPTION_renewable | KERB_KDCOPTION_renewable_ok

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
void kull_m_kerberos_asn1_helper_display_KerberosTime(KerberosTime *time);
void kull_m_kerberos_asn1_helper_util_UTCKerberosTimeToFileTime(KerberosTime *time, PFILETIME pFileTime);

// PA_DATA
PA_DATA * kull_m_kerberos_asn1_helper_get_PADATA_from_REP(KDC_REP *Rep, Int32 type);
PA_DATA * kull_m_kerberos_asn1_helper_get_PADATA_from_REQ(KDC_REQ *Req, Int32 type);

void kull_m_kerberos_asn1_helper_init_PADATAs(_seqof4 *padata, DWORD count, ...);

BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_encTimeStamp(PA_DATA *data, EncryptionKey *key);
BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_PacRequest(PA_DATA *data, BOOL request);
BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_TGS_REQ(PA_DATA *data, PCSTR Username, PCSTR Domain, Ticket *ticket, EncryptionKey *key);
BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_PA_PK_AS_REQ_old(PA_DATA *data, PCSTR Domain, KerberosTime *time, struct _KULL_M_CRYPTO_CERT_INFO *certSignInfo);
BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_PA_PK_AS_REQ(PA_DATA *data, KerberosTime *time, struct _KULL_M_CRYPTO_CERT_INFO *certSignInfo, struct _KULL_M_CRYPTO_DH_KEY_INFO *dhKeyInfo, PSHA_DIGEST digest);
BOOL kull_m_kerberos_asn1_helper_init_PA_DATA_FOR_USER(PA_DATA *data, PCSTR Username, PCSTR Domain, EncryptionKey *key);

// KDC_REQ & KDC_REP
BOOL kull_m_kerberos_asn1_helper_build_AsReq_Generic(PKIWI_AUTH_INFOS authInfo, PCSTR Service, PCSTR Target, KerberosTime *time, BOOL PacRequest, OssBuf *AsReq);
BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_AsRep_Generic(PKIWI_AUTH_INFOS authInfo, KDC_REP *AsRep, EncKDCRepPart **encAsRepPart);

void kull_m_kerberos_asn1_helper_build_KdcReqBody(KDC_REQ_BODY *body, PCSTR cname, PCSTR Domain, DWORD Options, struct _seqof2 *suppEtype, PCSTR Service, PCSTR Target, PCSTR sDomain, BOOL isS4USelf);
void kull_m_kerberos_asn1_helper_build_FreeReqBody(KDC_REQ_BODY *body);

BOOL kull_m_kerberos_asn1_helper_build_KdcReqS4U2Self(EncKrbCredPart *encCred, KRB_CRED *cred, PCSTR username, PCSTR domain, OssBuf *OutKdcReq);
BOOL kull_m_kerberos_asn1_helper_build_KdcReqS4U2Proxy(EncKrbCredPart *encCred, KRB_CRED *cred, Ticket *ticket, PCSTR Service, PCSTR Target, OssBuf *OutKdcReq);
BOOL kull_m_kerberos_asn1_helper_build_KdcReq_key(PCSTR Username, PCSTR Domain, EncryptionKey *key, PCSTR Service, PCSTR Target, PCSTR sDomain, BOOL PacRequest, Ticket *ticket, _octet1 *pac, OssBuf *OutKdcReq);
BOOL kull_m_kerberos_asn1_helper_build_KdcReq_RSA(PCSTR Username, PCSTR Domain, PKULL_M_CRYPTO_CERT_INFO certInfo, PCSTR Service, PCSTR Target, KerberosTime *time, BOOL PacRequest, OssBuf *OutKdcReq);
BOOL kull_m_kerberos_asn1_helper_build_KdcReq_RSA_DH(PCSTR Username, PCSTR Domain, PKULL_M_CRYPTO_CERT_INFO certInfo, PKULL_M_CRYPTO_DH_KEY_INFO keyInfo, PCSTR Service, PCSTR Target, KerberosTime *time, BOOL PacRequest, OssBuf *OutKdcReq);
BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_key(KDC_REP *rep, EncKDCRepPart ** encRepPart, EncryptionKey *key, int pdu);
BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_RSA(KDC_REP *rep, PKULL_M_CRYPTO_PROV_INFO provInfo, int pdu, EncKDCRepPart ** encRepPart);
BOOL kull_m_kerberos_asn1_helper_build_EncKDCRepPart_from_Rep_RSA_DH(KDC_REP *rep, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, int pdu, EncKDCRepPart **encRepPart);

// 
BOOL kull_m_kerberos_asn1_helper_build_ApReq(OssBuf * ApReqData, PCSTR Username, PCSTR Domain, Ticket *ticket, EncryptionKey *key, ULONG keyUsage, EncryptionKey *authenticatorNewKey, UInt32 *authenticatorNewSeq);
BOOL kull_m_kerberos_asn1_helper_build_AuthorizationData(OssBuf * AuthData, _octet1 *pac);
BOOL kull_m_kerberos_asn1_helper_build_KrbPriv(_octet1 *data, EncryptionKey *key, PCSTR machineName, OssBuf *OutKrbPriv, UInt32 *seq);
BOOL kull_m_kerberos_asn1_helper_build_KrbCred(Realm *prealm, PrincipalName *pname, EncKDCRepPart *repPart, Ticket *ticket, OssBuf *OutKrbCred);
BOOL kull_m_kerberos_asn1_helper_build_EncKrbPrivPart_from_Priv(KRB_PRIV *priv, EncKrbPrivPart ** encKrbPrivPart, EncryptionKey *authKey);
BOOL kull_m_kerberos_asn1_helper_build_ForUser(OssBuf * ForUserData, PCSTR Username, PCSTR Domain, EncryptionKey *key);
BOOL kull_m_kerberos_asn1_helper_build_AuthPackOld(OssBuf *AuthPackOld, PCSTR Domain, KerberosTime *time);
BOOL kull_m_kerberos_asn1_helper_build_AuthPack(OssBuf *authPack, KerberosTime *time, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, PSHA_DIGEST digest);

// Signature
BOOL kull_m_kerberos_asn1_helper_build_AuthPackOld_signed(_octet1 *signedInfo, PCSTR Domain, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo);
BOOL kull_m_kerberos_asn1_helper_build_AuthPack_signed(_octet1 * signedInfo, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, PSHA_DIGEST digest);

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
#define KRB_KEY_USAGE_AS_DATA_ENCRYPTED_NO_SPEC		16

#define KRB_KEY_USAGE_TGS_REQ_PA_AUTHENTICATOR		7
#define KRB_KEY_USAGE_TGS_REP_EP_SESSION_KEY		8

#define KRB_KEY_USAGE_AP_REQ_AUTHENTICATOR			11
#define KRB_KEY_USAGE_KRB_PRIV_ENCRYPTED_PART		13

#define PA_TYPE_TGS_REQ				1
#define PA_TYPE_ENC_TIMESTAMP		2
#define PA_TYPE_PK_AS_REP_OLD		15
#define PA_TYPE_PK_AS_REQ			16
#define PA_TYPE_PK_AS_REP			17
#define PA_TYPE_PAC_REQUEST			128
#define PA_TYPE_FOR_USER			129
#define PA_TYPE_X509_USER			130

#define AD_TYPE_IF_RELEVANT			1
#define AD_TYPE_KDCIssued			4
#define AD_TYPE_AND_OR				5
#define AD_TYPE_MANDATORY_FOR_KDC	8
#define AD_TYPE_WIN2K_PAC			128