/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include "../../../modules/asn1/kull_m_kerberos_asn1.h"
#include "../kerberos/kuhl_m_kerberos.h"

typedef BOOL (* PVALID_HEADER) (OssBuf *input);
typedef BOOL (* PREAD_DATA) (OssBuf *input, KRB_CRED **cred);
typedef BOOL (* PWRITE_DATA) (KRB_CRED *cred, OssBuf *output);

typedef struct _KERB_FORMAT_MODULE {
	PCWSTR shortName;
	const PVALID_HEADER validHeader;
	const PREAD_DATA readData;
	const PWRITE_DATA writeData;
	PCWSTR simpleName;
	PCWSTR multiName;
} KERB_FORMAT_MODULE, *PKERB_FORMAT_MODULE;

void addCred(KRB_CRED *cred, KRB_CRED **dst);
void writeData(const KERB_FORMAT_MODULE * module, BOOL multiple, KRB_CRED *cred);

#include "ccache.h"
#include "krbcred.h"
#include "lsa.h"
#include "wce.h"