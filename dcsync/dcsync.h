/*	Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com / http://blog.gentilkiwi.com )
	Vincent LE TOUX ( vincent.letoux@gmail.com / http://www.mysmartlogon.com )
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include <DsGetDC.h>
#include <LM.h>
#include "modules/kull_m_string.h"
#include "modules/kull_m_crypto_system.h"
#include "rpc/rpc_factory.h"

#define ATT_RDN							589825
#define ATT_OBJECT_GUID					589826
#define ATT_OBJECT_SID					589970
#define ATT_WHEN_CREATED				131074
#define ATT_WHEN_CHANGED				131075

#define ATT_SAM_ACCOUNT_NAME			590045
#define ATT_USER_PRINCIPAL_NAME			590480
#define ATT_SERVICE_PRINCIPAL_NAME		590595
#define ATT_SID_HISTORY					590433

#define ATT_SAM_ACCOUNT_TYPE			590126
#define ATT_LOGON_HOURS					589888
#define ATT_LOGON_WORKSTATION			589889
#define ATT_LAST_LOGON					589876
#define ATT_PWD_LAST_SET				589920
#define ATT_ACCOUNT_EXPIRES				589983
#define ATT_LOCKOUT_TIME				590486

#define ATT_UNICODE_PWD					589914
#define ATT_NT_PWD_HISTORY				589918
#define ATT_DBCS_PWD					589879
#define ATT_LM_PWD_HISTORY				589984
#define ATT_SUPPLEMENTAL_CREDENTIALS	589949

#define ATT_CURRENT_VALUE				589851

#define ATT_TRUST_ATTRIBUTES			590294
#define ATT_TRUST_AUTH_INCOMING			589953
#define ATT_TRUST_AUTH_OUTGOING			589959
#define ATT_TRUST_DIRECTION				589956
#define ATT_TRUST_PARENT				590295
#define ATT_TRUST_PARTNER				589957
#define ATT_TRUST_TYPE					589960

SecPkgContext_SessionKey g_sKey;

int wmain(int argc, wchar_t * argv[]);
void RPC_ENTRY RpcSecurityCallback(_In_ void *Context);
PVOID findMonoAttr(ATTRBLOCK *attributes, ATTRTYP type, PVOID data, DWORD *size);
void findPrintMonoAttr(LPCWSTR prefix, ATTRBLOCK *attributes, ATTRTYP type, BOOL newLine);
void descrUser(ATTRBLOCK *attributes);
BOOL decryptHash(PBYTE encodedData, DWORD encodedDataSize, DWORD rid, PBYTE data);