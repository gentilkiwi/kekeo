/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "common.h"

BOOL kiwi_ccache_valid_header(OssBuf *input);
BOOL kiwi_ccache_read(OssBuf *input, KULL_M_ASN1_KRB_CRED **cred);
BOOL kiwi_ccache_write(KULL_M_ASN1_KRB_CRED *cred, OssBuf *output);


DWORD kiwi_ccache_size_header_krbcred(KULL_M_ASN1_KRB_CRED *cred, KULL_M_ASN1_EncKrbCredPart * encKrbCredPart, KULL_M_ASN1_PrincipalName ** pname, KULL_M_ASN1_Realm ** prealm);
void kiwi_ccache_skip_buffer(PBYTE *data);
void kiwi_ccache_skip_struct_with_buffer(PBYTE *data);

void kiwi_ccache_free_ticketInfo(struct KULL_M_ASN1__seqof5 * infos);
void kiwi_ccache_free_ticket(struct KULL_M_ASN1__seqof3 * ticket);
DWORD kiwi_ccache_size_principal_realm(KULL_M_ASN1_PrincipalName *name, KULL_M_ASN1_Realm *realm);
void kiwi_ccache_create_principal_realm(PBYTE *data, KULL_M_ASN1_PrincipalName *name, KULL_M_ASN1_Realm *realm);
void kiwi_ccache_copy_principal_realm(KULL_M_ASN1_PrincipalName *srcName, KULL_M_ASN1_Realm *srcRealm, KULL_M_ASN1_PrincipalName *dstName, KULL_M_ASN1_Realm *dstRealm);
void kiwi_ccache_free_principal_realm(KULL_M_ASN1_PrincipalName *name, KULL_M_ASN1_Realm *realm);
void kiwi_ccache_write_principal_realm(PBYTE *data, KULL_M_ASN1_PrincipalName *name, KULL_M_ASN1_Realm *realm);