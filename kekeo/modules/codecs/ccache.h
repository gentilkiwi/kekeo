/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "common.h"

BOOL kiwi_ccache_valid_header(OssBuf *input);
BOOL kiwi_ccache_read(OssBuf *input, KRB_CRED **cred);
BOOL kiwi_ccache_write(KRB_CRED *cred, OssBuf *output);


DWORD kiwi_ccache_size_header_krbcred(KRB_CRED *cred, EncKrbCredPart * encKrbCredPart, PrincipalName ** pname, Realm ** prealm);
void kiwi_ccache_skip_buffer(PBYTE *data);
void kiwi_ccache_skip_struct_with_buffer(PBYTE *data);

void kiwi_ccache_free_ticketInfo(struct _seqof5 * infos);
void kiwi_ccache_free_ticket(struct _seqof3 * ticket);
DWORD kiwi_ccache_size_principal_realm(PrincipalName *name, Realm *realm);
void kiwi_ccache_create_principal_realm(PBYTE *data, PrincipalName *name, Realm *realm);
void kiwi_ccache_copy_principal_realm(PrincipalName *srcName, Realm *srcRealm, PrincipalName *dstName, Realm *dstRealm);
void kiwi_ccache_free_principal_realm(PrincipalName *name, Realm *realm);
void kiwi_ccache_write_principal_realm(PBYTE *data, PrincipalName *name, Realm *realm);