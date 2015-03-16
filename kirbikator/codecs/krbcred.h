/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"

BOOL kiwi_krbcred_valid_header(OssBuf *input);
BOOL kiwi_krbcred_read(OssBuf *input, KRB_CRED **cred);
BOOL kiwi_krbcred_write(KRB_CRED *cred, OssBuf *output);