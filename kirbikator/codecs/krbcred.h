/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#pragma once
#include "globals.h"

BOOL kiwi_krbcred_valid_header(OssBuf *input);
BOOL kiwi_krbcred_read(OssBuf *input, KRB_CRED **cred);
BOOL kiwi_krbcred_write(KRB_CRED *cred, OssBuf *output);