/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include "../../../modules/asn1/kull_m_kerberos_asn1.h"
#include "../kerberos/kuhl_m_kerberos.h"

typedef BOOL (* PVALID_HEADER) (OssBuf *input);
typedef BOOL (* PREAD_DATA) (OssBuf *input, KULL_M_ASN1_KRB_CRED **cred);
typedef BOOL (* PWRITE_DATA) (KULL_M_ASN1_KRB_CRED *cred, OssBuf *output);

typedef struct _KERB_FORMAT_MODULE {
	PCWSTR shortName;
	const PVALID_HEADER validHeader;
	const PREAD_DATA readData;
	const PWRITE_DATA writeData;
	PCWSTR simpleName;
	PCWSTR multiName;
} KERB_FORMAT_MODULE, *PKERB_FORMAT_MODULE;

void addCred(KULL_M_ASN1_KRB_CRED *cred, KULL_M_ASN1_KRB_CRED **dst);
void writeData(const KERB_FORMAT_MODULE * module, BOOL multiple, KULL_M_ASN1_KRB_CRED *cred);

#include "ccache.h"
#include "krbcred.h"
#include "lsa.h"
#include "wce.h"