/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include "../modules/kull_m_sock.h"
#include "../modules/kull_m_samlib.h"
#include "../modules/kull_m_string.h"
#include <Winldap.h>
#include <Winber.h>

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

int main(int argc, char * argv[]);
PBERVAL giveBERForUser(PCANSI_STRING user, PCSTR domain);
DWORD giveUsersForServer(PCSTR server);