/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "common.h"

BOOL kiwi_krbcred_valid_header(OssBuf *input);
BOOL kiwi_krbcred_read(OssBuf *input, KULL_M_ASN1_KRB_CRED **cred);
BOOL kiwi_krbcred_write(KULL_M_ASN1_KRB_CRED *cred, OssBuf *output);