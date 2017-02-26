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