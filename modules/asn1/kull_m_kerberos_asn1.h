/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"
#include "../kull_m_string.h"
#include "kull_m_kerberos_oss_asn1_internal.h"
#include "../kull_m_sock.h"
#include "../kull_m_file.h"

typedef struct _KULL_M_CRYPTO_DH_KEY_INFO {
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	DHNonce dhClientNonce;
} KULL_M_CRYPTO_DH_KEY_INFO, *PKULL_M_CRYPTO_DH_KEY_INFO;

typedef struct _KULL_M_CRYPTO_PROV_INFO {
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	DWORD dwKeySpec;
} KULL_M_CRYPTO_PROV_INFO, *PKULL_M_CRYPTO_PROV_INFO;

typedef struct _KULL_M_CRYPTO_CERT_INFO {
	HCERTSTORE hCertStore;
	PCCERT_CONTEXT pCertContext;
	KULL_M_CRYPTO_PROV_INFO provider;
	
	KULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo;
	//CRYPT_KEY_PROV_INFO tmpKey;
	AS_REQ *tmpAsReq;
} KULL_M_CRYPTO_CERT_INFO, *PKULL_M_CRYPTO_CERT_INFO;

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

#define KRB_KEY_USAGE_AS_REQ_PA_ENC_TIMESTAMP		1
#define KRB_KEY_USAGE_AS_REP_TGS_REP				2
#define KRB_KEY_USAGE_AS_REP_EP_SESSION_KEY			3
#define KRB_KEY_USAGE_AS_REQ_AUTHORIZATION_SESSION	4
#define KRB_KEY_USAGE_AS_DATA_ENCRYPTED_NO_SPEC		16

#define KRB_KEY_USAGE_TGS_REQ_PA_AUTHENTICATOR		7
#define KRB_KEY_USAGE_TGS_REP_EP_SESSION_KEY		8

#define KRB_KEY_USAGE_AP_REQ_AUTHENTICATOR			11
#define KRB_KEY_USAGE_KRB_PRIV_ENCRYPTED_PART		13
#define KRB_KEY_USAGE_KRB_CRED_ENCRYPTED_PART		14

#define PA_TYPE_TGS_REQ				1
#define PA_TYPE_ENC_TIMESTAMP		2
#define PA_TYPE_PK_AS_REP_OLD		15
#define PA_TYPE_PK_AS_REQ			16
#define PA_TYPE_PK_AS_REP			17
#define PA_TYPE_ETYPE_INFO2			19
#define PA_TYPE_PAC_REQUEST			128
#define PA_TYPE_FOR_USER			129
#define PA_TYPE_X509_USER			130
#define PA_TYPE_PAC_OPTIONS			167

#define AD_TYPE_IF_RELEVANT			1
#define AD_TYPE_KDCIssued			4
#define AD_TYPE_AND_OR				5
#define AD_TYPE_MANDATORY_FOR_KDC	8
#define AD_TYPE_WIN2K_PAC			128

#define GSS_C_DELEG_FLAG		0x00000001
#define GSS_C_MUTUAL_FLAG		0x00000002
#define GSS_C_REPLAY_FLAG		0x00000004
#define GSS_C_SEQUENCE_FLAG		0x00000008
#define GSS_C_CONF_FLAG			0x00000010
#define GSS_C_INTEG_FLAG		0x00000020
#define GSS_C_ANON_FLAG			0x00000040
#define GSS_C_PROT_READY_FLAG	0x00000080
#define GSS_C_TRANS_FLAG		0x00000100

#define GSS_CHECKSUM_TYPE		0x8003

#define TOK_ID_KRB_AP_REQ		0x0001
#define TOK_ID_KRB_AP_REP		0x0002
#define TOK_ID_KRB_ERROR		0x0003

typedef enum _KIWI_AUTH_INFOS_TYPE {
	KIWI_AUTH_INFOS_TYPE_INVALID,
	KIWI_AUTH_INFOS_TYPE_KEY,
	KIWI_AUTH_INFOS_TYPE_RSA,
	KIWI_AUTH_INFOS_TYPE_RSA_DH,
	KIWI_AUTH_INFOS_TYPE_OTF_RSA,
	KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH,
	KIWI_AUTH_INFOS_TYPE_ASREQ_RSA_DH,
	KIWI_AUTH_INFOS_TYPE_ANON,
} KIWI_AUTH_INFOS_TYPE, *PKIWI_AUTH_INFOS_TYPE;

typedef struct _KIWI_AUTH_INFOS {
	LPWSTR w_realm;
	Realm realm;
	LPWSTR w_short_realm;


	LPWSTR w_cname;
	LPWSTR w_short_cname;
	PrincipalName cname;

	BOOL needPac;
	PrincipalName sname;

	KIWI_AUTH_INFOS_TYPE type;
	
	// for future negociation
	LPWSTR w_password;
	union {
		EncryptionKey ekey;
		KULL_M_CRYPTO_CERT_INFO certinfos;
	} u;
	
} KIWI_AUTH_INFOS, *PKIWI_AUTH_INFOS;

typedef struct _KIWI_AUTHENTICATOR_CKSUM {
	ULONG Lgth; // of Bnd
	BYTE Bnd[16];
	ULONG Flags;
	USHORT DlgOpt;
	USHORT Dlgth;
	BYTE Deleg[ANYSIZE_ARRAY];
	// BYTE Exts[];
} KIWI_AUTHENTICATOR_CKSUM, *PKIWI_AUTHENTICATOR_CKSUM;

typedef NTSTATUS (CALLBACK * PKULL_M_KERBEROS_ASN1_SAVEKDCREP_CALLBACK) (PVOID data, DWORD len, PrincipalName *sname);

#include "kull_m_kerberos_asn1_crypto.h"
#include "kull_m_kerberos_asn1_net.h"

OssGlobal kull_m_kerberos_asn1_world;

BOOL kull_m_kerberos_asn1_init();
void kull_m_kerberos_asn1_term();

void kull_m_kerberos_asn1_PrincipalName_create(PrincipalName *principal_name, Int32 name_type, DWORD count, ...);
void kull_m_kerberos_asn1_PrincipalName_create_fromName(PrincipalName *principal_name, Realm *pRealm, LPCWSTR name);
void kull_m_kerberos_asn1_PrincipalName_delete(PrincipalName *principal_name);
void kull_m_kerberos_asn1_PrincipalName_descr(PrincipalName *principal_name, BOOL withType);

void kull_m_kerberos_asn1_KerberosTime_build_systemtime(KerberosTime *time, PSYSTEMTIME pSystemTime, BOOL isMaxMs2037);
void kull_m_kerberos_asn1_KerberosTime_build_filetime(KerberosTime *time, PFILETIME pFileTime, BOOL isMaxMs2037);
void kull_m_kerberos_asn1_KerberosTime_build_time_t(KerberosTime *time, time_t uTime);
void kull_m_kerberos_asn1_KerberosTime_to_systemtime(KerberosTime *time, PSYSTEMTIME pSystemTime);
void kull_m_kerberos_asn1_KerberosTime_to_filetime(KerberosTime *time, PFILETIME pFileTime);
void kull_m_kerberos_asn1_KerberosTime_to_time_t(KerberosTime *time, time_t * uTime);
void kull_m_kerberos_asn1_KerberosTime_print(KerberosTime *time);


void kull_m_kerberos_asn1_KdcReqBody_build(KDC_REQ_BODY *body, PrincipalName *cname, Realm realm, PrincipalName *sname, DWORD Options, struct _seqof2 *suppEtype);
void kull_m_kerberos_asn1_KdcReqBody_free(KDC_REQ_BODY *body);


BOOL kull_m_kerberos_asn1_AsReqAsRep(PKIWI_AUTH_INFOS authinfos, PKULL_M_SOCK fullsocket, KerberosTime *time, PrincipalName *altService, AS_REP **AsRep, EncKDCRepPart **encAsRepPart, EncryptionKey *replyKey);
BOOL kull_m_kerberos_asn1_AsReqGenericRep(PKIWI_AUTH_INFOS authinfos, PKULL_M_SOCK fullsocket, KerberosTime *time, PrincipalName *altService, int pduRep, LPVOID *Rep);

BOOL kull_m_kerberos_asn1_AsReq_build(PKIWI_AUTH_INFOS authinfos, KerberosTime *time, PrincipalName *altService, OssBuf *OutKdcReq);
void kull_m_kerberos_asn1_PA_DATAs_build(_seqof4 *padata, DWORD count, ...);
PA_DATA * kull_m_kerberos_asn1_PADATA_from_REP(KDC_REP *Rep, Int32 type);
PA_DATA * kull_m_kerberos_asn1_PADATA_from_REQ(KDC_REQ *Req, Int32 type);
_octet1 * kull_m_kerberos_asn1_AuthorizationData_from_Type(AuthorizationData data, Int32 ad_type);

BOOL kull_m_kerberos_asn1_PA_DATA_encTimeStamp_build(PA_DATA *data, KerberosTime *time, EncryptionKey *key);
BOOL kull_m_kerberos_asn1_PA_DATA_PA_PK_AS_REQ_old_build(PA_DATA *data, PrincipalName *sname, Realm srealm, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo);
BOOL kull_m_kerberos_asn1_AuthPackOld_signed_build(_octet1 *signedInfo, PrincipalName *sname, Realm srealm, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo);
BOOL kull_m_kerberos_asn1_AuthPackOld_build(OssBuf *AuthPackOld, PrincipalName *sname, Realm srealm, KerberosTime *time);

BOOL kull_m_kerberos_asn1_PA_DATA_PA_PK_AS_REQ_build(PA_DATA *data, PSHA_DIGEST digest, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo);
BOOL kull_m_kerberos_asn1_AuthPack_signed_build(_octet1 * signedInfo, PSHA_DIGEST digest, KerberosTime *time, PKULL_M_CRYPTO_CERT_INFO certSignInfo, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo);
BOOL kull_m_kerberos_asn1_AuthPack_build(OssBuf *authPack, PSHA_DIGEST digest, KerberosTime *time, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo);

BOOL kull_m_kerberos_asn1_PA_DATA_FOR_USER_build(PA_DATA *data, PrincipalName *user, Realm realm, EncryptionKey *key);
BOOL kull_m_kerberos_asn1_ForUser_build(OssBuf *ForUserData, PrincipalName *user, Realm realm, EncryptionKey *key);

BOOL kull_m_kerberos_asn1_TgsReq_build(OssBuf *OutKdcReq, PrincipalName *cname, Realm crealm, PrincipalName *sname, Realm srealm, DWORD options, Ticket *ticket, EncryptionKey *key, Ticket *addTicket, _octet1 *pac, PA_DATA *optPa);

BOOL kull_m_kerberos_asn1_PA_DATA_PacRequest_build(PA_DATA *data, BOOL request);

BOOL kull_m_kerberos_asn1_PA_DATA_TGS_REQ_build(PA_DATA *data, PrincipalName *pname, Realm prealm, Ticket *ticket, EncryptionKey *key);
BOOL kull_m_kerberos_asn1_ApReq_build(OssBuf *ApReqData, PrincipalName *pname, Realm prealm, Ticket *ticket, EncryptionKey *key, ULONG keyUsage, EncryptionKey *authenticatorNewKey, UInt32 *authenticatorNewSeq);
BOOL kull_m_kerberos_asn1_AuthorizationData_from_PAC_build(OssBuf *AuthData, _octet1 *pac);

BOOL kull_m_kerberos_asn1_EncKDCRepPart_from_AsRep_build(PKIWI_AUTH_INFOS authInfo, KDC_REP *AsRep, EncKDCRepPart **encAsRepPart, EncryptionKey *replyKey);
BOOL kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_Key_build(KDC_REP *rep, EncryptionKey *key, int pdu, EncKDCRepPart **encRepPart);
BOOL kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_Rsa_build(KDC_REP *rep, PKULL_M_CRYPTO_PROV_INFO provInfo, int pdu, EncKDCRepPart **encRepPart, EncryptionKey *replyKey);
BOOL kull_m_kerberos_asn1_EncKDCRepPart_from_Rep_RsaDh_build(KDC_REP *rep, PKULL_M_CRYPTO_DH_KEY_INFO dhKeyInfo, int pdu, EncKDCRepPart **encRepPart, EncryptionKey *replyKey);

BOOL kull_m_kerberos_asn1_PAC_from_EncTicketPart(EncryptionKey *key, EncryptedData *data, _octet1 *pac);

BOOL kull_m_kerberos_asn1_KrbPriv_build(_octet1 *data, EncryptionKey *key, PCSTR machineName, OssBuf *OutKrbPriv, UInt32 *seq);
BOOL kull_m_kerberos_asn1_EncKrbPrivPart_from_Priv_build(KRB_PRIV *priv, EncKrbPrivPart ** encKrbPrivPart, EncryptionKey *authKey);
BOOL kull_m_kerberos_asn1_KrbCred_build(KDC_REP *rep, EncKDCRepPart *repPart, OssBuf *OutKrbCred);
LPWSTR kull_m_kerberos_asn1_KdcRep_filename(KDC_REP *rep, EncKDCRepPart *enc, PCWCHAR opt, PCWCHAR ext);
LPWSTR kull_m_kerberos_asn1_KrbCred_filename(KRB_CRED *cred, PCWCHAR opt, PCWCHAR ext);
BOOL kull_m_kerberos_asn1_KdcRep_save(KDC_REP *rep, EncKDCRepPart *encRepPart, LPCWSTR filename, LPCWSTR opt, PKULL_M_KERBEROS_ASN1_SAVEKDCREP_CALLBACK callback);
BOOL kull_m_kerberos_asn1_KrbCred_decode(OssBuf *ossBuf, EncryptionKey *key, KRB_CRED **KrbCred, EncKrbCredPart **encKrbCred);
BOOL kull_m_kerberos_asn1_KrbCred_load(LPCWSTR filename, EncryptionKey *key, KRB_CRED **KrbCred, EncKrbCredPart **encKrbCred);