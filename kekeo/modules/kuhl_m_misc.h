/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "kuhl_m.h"
#include "../../modules/asn1/kull_m_kerberos_asn1.h"
#include "../../modules/asn1/kull_m_kerberos_asn1_authinfos.h"
#include "../../modules/kull_m_string.h"
#include "../../modules/kull_m_samlib.h"
#include "codecs/common.h"
#include <Winldap.h>
#include <Winber.h>

const KUHL_M kuhl_m_misc;

NTSTATUS kuhl_m_misc_changepw(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_misc_convert(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_misc_storm(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_misc_arch(int argc, wchar_t * argv[]);

typedef struct _KULL_M_KADMIN_PASSWD_ERR{
	DWORD	id;
	PCWSTR	name;
} KULL_M_KADMIN_PASSWD_ERR, *PKULL_M_KADMIN_PASSWD_ERR;

PCWSTR kull_m_kadmin_passwd_err_to_string(DWORD id);
void kull_m_kadmin_passwd_retFromKadmin(_octet1 * data);

#define DIRTY_ASN1_ID_GENERAL_STRING	0x1b
#define DIRTY_ASN1_ID_GENERALIZED_TIME	0x18
#define DIRTY_ASN1_ID_SEQUENCE			0x30
#define DIRTY_ASN1_MASK_APPLICATION		0x60
#define DIRTY_ASN1_MASK_CONTEXT			0xa0

#define MAKE_APP_TAG(AppId)		((ber_tag_t) (DIRTY_ASN1_MASK_APPLICATION | AppId))
#define MAKE_CTX_TAG(CtxId)		((ber_tag_t) (DIRTY_ASN1_MASK_CONTEXT | CtxId))

typedef struct _KIWI_USERNAMEA {
	LIST_ENTRY navigator;
	ANSI_STRING username;
} KIWI_USERNAMEA, *PKIWI_USERNAMEA;

BOOL kuhl_m_misc_storm_add(PCUNICODE_STRING name);
PBERVAL kuhl_m_misc_storm_giveBERForUser(PCANSI_STRING user);
DWORD kuhl_m_misc_storm_giveUsersForServer(PCWSTR server);

//static const RPC_SYNTAX_IDENTIFIER AbstractSyntax =			{{0xe1af8308, 0x5d1f, 0x11c9, {0x91, 0xa4, 0x08, 0x00, 0x2b, 0x14, 0xa0, 0xfa}}, {3, 0}};
//static const RPC_SYNTAX_IDENTIFIER NdrTransferSyntax =		{{0x8a885d04, 0x1ceb, 0x11c9, {0x9f, 0xe8, 0x08, 0x00, 0x2b, 0x10, 0x48, 0x60}}, {2, 0}};
//static const RPC_SYNTAX_IDENTIFIER Ndr64TransferSyntax =	{{0x71710533, 0xbeba, 0x4937, {0x83, 0x19, 0xb5, 0xdb, 0xef, 0x9c, 0xcc, 0x36}}, {1, 0}};

#define RPC_CONT_DEF_RESULT_acceptance									0
#define RPC_CONT_DEF_RESULT_user_rejection								1
#define RPC_CONT_DEF_RESULT_provider_rejection							2

#define RPC_PROVIDER_REASON_reason_not_specified						0
#define RPC_PROVIDER_REASON_abstract_syntax_not_supported				1
#define RPC_PROVIDER_REASON_proposed_transfer_syntaxes_not_supported	2
#define RPC_PROVIDER_REASON_local_limit_exceeded						3

#define RPC_PDU_bind		11
#define RPC_PDU_bind_ack	12

#pragma pack(push, 1)
typedef struct _p_cont_elem_t {
	USHORT p_cont_id;
	UCHAR n_transfer_syn; /* number of items */
	UCHAR reserved; /* alignment pad, m.b.z. */
	RPC_SYNTAX_IDENTIFIER abstract_syntax; /* transfer syntax list */
	RPC_SYNTAX_IDENTIFIER /*[size_is(n_transfer_syn)]*/ transfer_syntaxes[ANYSIZE_ARRAY];
} p_cont_elem_t, *pp_cont_elem_t;

typedef struct _p_cont_list_t {
	UCHAR n_context_elem; /* number of items */
	UCHAR reserved; /* alignment pad, m.b.z. */
	USHORT reserved2; /* alignment pad, m.b.z. */
	p_cont_elem_t /*[size_is(n_cont_elem)]*/ p_cont_elem[ANYSIZE_ARRAY];
} p_cont_list_t, *pp_cont_list_t;

typedef struct _rpcconn_bind_hdr_t {
	UCHAR rpc_vers; /* 00:01 RPC version */
	UCHAR rpc_vers_minor; /* 01:01 minor version */
	UCHAR PTYPE; /* 02:01 bind PDU */
	UCHAR pfc_flags; /* 03:01 flags */
	DWORD packed_drep; /* 04:04 NDR data rep format label*/
	USHORT frag_length; /* 08:02 total length of fragment */
	USHORT auth_length; /* 10:02 length of auth_value */
	ULONG call_id; /* 12:04 call identifier */
	USHORT max_xmit_frag; /* 16:02 max transmit frag size, bytes */
	USHORT max_recv_frag; /* 18:02 max receive frag size, bytes */
	DWORD assoc_group_id; /* 20:04 incarnation of client-server assoc group presentation context list */
	p_cont_list_t p_context_elem; /* variable size */
} rpcconn_bind_hdr_t, *prpcconn_bind_hdr_t;

typedef struct _p_result_t {
	USHORT result;
	USHORT reason; /* only relevant if result != acceptance */
	RPC_SYNTAX_IDENTIFIER transfer_syntax;
} p_result_t, *pp_result_t;

typedef struct _p_result_list_t {
	UCHAR n_results; /* count */
	UCHAR reserved; /* alignment pad, m.b.z. */
	USHORT reserved2; /* alignment pad, m.b.z. */
	p_result_t /*[size_is(n_results)]*/ p_results[ANYSIZE_ARRAY];
} p_result_list_t, *pp_result_list_t;

typedef struct _port_any_t {
	USHORT length;
	char /*[size_is(length)]*/ port_spec[ANYSIZE_ARRAY];
} port_any_t, *pport_any_t;

typedef struct _rpcconn_bind_ack_hdr_t {
	UCHAR rpc_vers; /* 00:01 RPC version */
	UCHAR rpc_vers_minor; /* 01:01 minor version */
	UCHAR PTYPE; /* 02:01 bind ack PDU */
	UCHAR pfc_flags; /* 03:01 flags */
	DWORD packed_drep; /* 04:04 NDR data rep format label*/
	USHORT frag_length; /* 08:02 total length of fragment */
	USHORT auth_length; /* 10:02 length of auth_value */
	DWORD call_id; /* 12:04 call identifier */
	USHORT max_xmit_frag; /* 16:02 max transmit frag size */
	USHORT max_recv_frag; /* 18:02 max receive frag size */
	DWORD assoc_group_id; /* 20:04 returned assoc_group_id */
	port_any_t sec_addr; /* 24:yy optional secondary address for process incarnation; local port part of address only */
	/* restore 4-octet alignment */
	p_result_list_t p_result_list; /* variable size */
} rpcconn_bind_ack_hdr_t, *prpcconn_bind_ack_hdr_t;
#pragma pack(pop)