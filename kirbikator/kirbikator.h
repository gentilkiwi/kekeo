/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#pragma once
#include "globals.h"
#include "../modules/kull_m_file.h"
#include "codecs/ccache.h"
#include "codecs/krbcred.h"
#include "codecs/lsa.h"

typedef BOOL (* PVALID_HEADER) (OssBuf *input);
typedef BOOL (* PREAD_DATA) (OssBuf *input, KRB_CRED **cred);
typedef BOOL (* PWRITE_DATA) (KRB_CRED *cred, OssBuf *output);

typedef struct _KERB_FORMAT_MODULE {
	const char * shortName;
	const PVALID_HEADER validHeader;
	const PREAD_DATA readData;
	const PWRITE_DATA writeData;
	const char * simpleName;
	const char * multiName;
} KERB_FORMAT_MODULE, *PKERB_FORMAT_MODULE;

BOOL init();
BOOL term();

int main(int argc, char * argv[]);
void addCred(KRB_CRED *cred, KRB_CRED **dst);
void writeData(const KERB_FORMAT_MODULE * module, BOOL multiple, KRB_CRED *cred);