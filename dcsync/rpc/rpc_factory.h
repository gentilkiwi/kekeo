/*	Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com / http://blog.gentilkiwi.com )
	Vincent LE TOUX ( vincent.letoux@gmail.com / http://www.mysmartlogon.com )
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "globals.h"
#include "ms-drsr_h.h"
#include "../modules/kull_m_string.h"

typedef struct _DRS_EXTENSIONS_INT {
	DWORD cb;
	DWORD dwFlags;
	GUID SiteObjGuid;
	DWORD Pid;
	DWORD dwReplEpoch;
	DWORD dwFlagsExt;
	GUID ConfigObjGUID;
} DRS_EXTENSIONS_INT, *PDRS_EXTENSIONS_INT;

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t cBytes);
void __RPC_USER midl_user_free(void __RPC_FAR * p);

BOOL rpc_factory_create(LPCWSTR server, RPC_SECURITY_CALLBACK_FN securityCallback, RPC_BINDING_HANDLE *hBinding);
BOOL rpc_factory_delete(RPC_BINDING_HANDLE *hBinding);

BOOL rpc_factory_getDomainAndUserInfos(RPC_BINDING_HANDLE *hBinding, LPCWSTR ServerName, LPCWSTR Domain, GUID *DomainGUID, LPCWSTR User, GUID *UserGuid);
BOOL rpc_factory_getDCBind(RPC_BINDING_HANDLE *hBinding, GUID *NtdsDsaObjectGuid, DRS_HANDLE *hDrs);