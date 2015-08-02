/*	Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com / http://blog.gentilkiwi.com )
	Vincent LE TOUX ( vincent.letoux@gmail.com / http://www.mysmartlogon.com )
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "rpc_factory.h"

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t cBytes)
{
	void __RPC_FAR * ptr = NULL;
	if(ptr = malloc(cBytes))
		RtlZeroMemory(ptr, cBytes);
	return ptr;
}

void __RPC_USER midl_user_free(void __RPC_FAR * p)
{
	free(p);
}

const wchar_t PREFIX_LDAP[] = L"ldap/";
BOOL rpc_factory_create(LPCWSTR server, RPC_SECURITY_CALLBACK_FN securityCallback, RPC_BINDING_HANDLE *hBinding)
{
	BOOL status = FALSE;
	RPC_STATUS rpcStatus;
	RPC_WSTR StringBinding = NULL;
	RPC_SECURITY_QOS SecurityQOS = {RPC_C_SECURITY_QOS_VERSION, RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH, RPC_C_QOS_IDENTITY_STATIC, RPC_C_IMP_LEVEL_DEFAULT};
	LPWSTR fullServer = NULL;
	DWORD szServer = wcslen(server) * sizeof(wchar_t), szPrefix = sizeof(PREFIX_LDAP); // includes NULL;

	*hBinding = NULL;
	rpcStatus = RpcStringBindingCompose(NULL, (RPC_WSTR) L"ncacn_ip_tcp", (RPC_WSTR) server, NULL, NULL, &StringBinding);
	if(rpcStatus == RPC_S_OK)
	{
		rpcStatus = RpcBindingFromStringBinding(StringBinding, hBinding);
		if(rpcStatus == RPC_S_OK)
		{
			if(*hBinding)
			{
				if(fullServer = (LPWSTR) LocalAlloc(LPTR, szPrefix + szServer))
				{
					RtlCopyMemory(fullServer, PREFIX_LDAP, szPrefix);
					RtlCopyMemory((PBYTE) fullServer + (szPrefix - sizeof(wchar_t)), server, szServer);

					rpcStatus = RpcBindingSetAuthInfoEx(*hBinding, (RPC_WSTR) fullServer, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_AUTHN_GSS_NEGOTIATE, NULL, 0, &SecurityQOS);
					status = (rpcStatus == RPC_S_OK);
					if(!status)
						PRINT_ERROR(L"RpcBindingSetAuthInfoEx: 0x%08x (%u)\n", rpcStatus, rpcStatus);

					if(status && securityCallback)
					{
						rpcStatus = RpcBindingSetOption(*hBinding, RPC_C_OPT_SECURITY_CALLBACK, (ULONG_PTR) securityCallback);
						status = (rpcStatus == RPC_S_OK);
						if(!status)
							PRINT_ERROR(L"RpcBindingSetOption: 0x%08x (%u)\n", rpcStatus, rpcStatus);
					}
					LocalFree(fullServer);
				}
			}
			else PRINT_ERROR(L"No Binding!\n");
		}
		else PRINT_ERROR(L"RpcBindingFromStringBinding: 0x%08x (%u)\n", rpcStatus, rpcStatus);
		RpcStringFree(&StringBinding);
	}
	else PRINT_ERROR(L"RpcStringBindingCompose: 0x%08x (%u)\n", rpcStatus, rpcStatus);
	return status;
}

BOOL rpc_factory_delete(RPC_BINDING_HANDLE *hBinding)
{
	BOOL status = FALSE;
	if(status = (RpcBindingFree(hBinding) == RPC_S_OK))
		*hBinding = NULL;
	return status;
}

UUID DRSUAPI_DS_BIND_UUID_Standard = {0xe24d201a, 0x4fd6, 0x11d1, {0xa3, 0xda, 0x00, 0x00, 0xf8, 0x75, 0xae, 0x0d}};
BOOL rpc_factory_getDomainAndUserInfos(RPC_BINDING_HANDLE *hBinding, LPCWSTR ServerName, LPCWSTR Domain, GUID *DomainGUID, LPCWSTR User, GUID *UserGuid)
{
	BOOL DomainGUIDfound = FALSE, UserGUIDfound = FALSE;
	DWORD i;
	ULONG drsStatus;
	DRS_HANDLE hDrs = NULL;
	DRS_EXTENSIONS_INT DrsExtensionsInt = {0};
	DRS_EXTENSIONS *pDrsExtensionsOutput = NULL;
	DRS_MSG_DCINFOREQ dcInfoReq = {0};
	DWORD dcOutVersion = 0;
	DRS_MSG_DCINFOREPLY dcInfoRep = {0};
	DRS_MSG_CRACKREQ nameCrackReq = {0};
	DWORD nameCrackOutVersion = 0, nameStatus;
	DRS_MSG_CRACKREPLY nameCrackRep = {0};
	UNICODE_STRING uGuid;

	__try
	{
		DrsExtensionsInt.cb = sizeof(DRS_EXTENSIONS_INT) - sizeof(DWORD);
		drsStatus = IDL_DRSBind(*hBinding, &DRSUAPI_DS_BIND_UUID_Standard, (DRS_EXTENSIONS *) &DrsExtensionsInt, &pDrsExtensionsOutput, &hDrs);
		if(drsStatus == 0)
		{
			dcInfoReq.V1.InfoLevel = 2;
			dcInfoReq.V1.Domain = (LPWSTR) Domain;
			drsStatus = IDL_DRSDomainControllerInfo(hDrs, 1, &dcInfoReq, &dcOutVersion, &dcInfoRep);
			if(drsStatus == 0)
			{
				if(dcOutVersion == 2)
				{
					for(i = 0; i < dcInfoRep.V2.cItems; i++)
					{
						if(!DomainGUIDfound && ((_wcsicmp(ServerName, dcInfoRep.V2.rItems[i].DnsHostName) == 0) || (_wcsicmp(ServerName, dcInfoRep.V2.rItems[i].NetbiosName) == 0)))
						{
							DomainGUIDfound = TRUE;
							*DomainGUID = dcInfoRep.V2.rItems[i].NtdsDsaObjectGuid;
						}
						// to free
					}
					if(!DomainGUIDfound)
						PRINT_ERROR(L"DomainControllerInfo: DC \'%s\' not found\n", ServerName);
				}
				else PRINT_ERROR(L"DomainControllerInfo: bad version (%u)\n", dcOutVersion);
			}
			else PRINT_ERROR(L"DomainControllerInfo: 0x%08x (%u)\n", drsStatus, drsStatus);

			nameCrackReq.V1.formatOffered = 0xFFFFFFF9; // DS_NT4_ACCOUNT_NAME_SANS_DOMAIN //0; // DS_UNKNOWN_NAME
			nameCrackReq.V1.formatDesired = 6; // DS_UNIQUE_ID_NAME
			nameCrackReq.V1.cNames = 1;
			nameCrackReq.V1.rpNames = (LPWSTR *) &User;
			drsStatus = IDL_DRSCrackNames(hDrs, 1, &nameCrackReq, &nameCrackOutVersion, &nameCrackRep);
			if(drsStatus == 0)
			{
				if(nameCrackRep.V1.pResult->cItems == 1)
				{
					nameStatus = nameCrackRep.V1.pResult->rItems[0].status;
					if(!nameStatus)
					{
						RtlInitUnicodeString(&uGuid, nameCrackRep.V1.pResult->rItems[0].pName);
						UserGUIDfound = NT_SUCCESS(RtlGUIDFromString(&uGuid, UserGuid));
						// to free !
					}
					else PRINT_ERROR(L"CrackNames (name status): 0x%08x (%u)\n", nameStatus, nameStatus);
				}
				else PRINT_ERROR(L"CrackNames: no item!\n");
			}
			else PRINT_ERROR(L"CrackNames: 0x%08x (%u)\n", drsStatus, drsStatus);
			drsStatus = IDL_DRSUnbind(&hDrs);
		}

	}
	__except(  (RpcExceptionCode() != STATUS_ACCESS_VIOLATION) &&
		(RpcExceptionCode() != STATUS_DATATYPE_MISALIGNMENT) &&
		(RpcExceptionCode() != STATUS_PRIVILEGED_INSTRUCTION) &&
		(RpcExceptionCode() != STATUS_ILLEGAL_INSTRUCTION) &&
		(RpcExceptionCode() != STATUS_BREAKPOINT) &&
		(RpcExceptionCode() != STATUS_STACK_OVERFLOW) &&
		(RpcExceptionCode() != STATUS_IN_PAGE_ERROR) &&
		(RpcExceptionCode() != STATUS_ASSERTION_FAILURE) &&
		(RpcExceptionCode() != STATUS_STACK_BUFFER_OVERRUN) &&
		(RpcExceptionCode() != STATUS_GUARD_PAGE_VIOLATION)
		)
	{
		PRINT_ERROR(L"RPC Exception 0x%08x (%u)\n", RpcExceptionCode(), RpcExceptionCode());
	}
	return (DomainGUIDfound && UserGUIDfound);
}

BOOL rpc_factory_getDCBind(RPC_BINDING_HANDLE *hBinding, GUID *NtdsDsaObjectGuid, DRS_HANDLE *hDrs)
{
	BOOL status = FALSE;
	ULONG drsStatus;
	DRS_EXTENSIONS_INT DrsExtensionsInt = {0};
	DRS_EXTENSIONS *pDrsExtensionsOutput = NULL;

	DrsExtensionsInt.cb = sizeof(DRS_EXTENSIONS_INT) - sizeof(DWORD);
	DrsExtensionsInt.dwFlags = 0xffffffff;
	DrsExtensionsInt.dwFlagsExt = 0xffffffff;

	__try
	{

		drsStatus = IDL_DRSBind(*hBinding, NtdsDsaObjectGuid, (DRS_EXTENSIONS *) &DrsExtensionsInt, &pDrsExtensionsOutput, hDrs);
	}
	__except(  (RpcExceptionCode() != STATUS_ACCESS_VIOLATION) &&
		(RpcExceptionCode() != STATUS_DATATYPE_MISALIGNMENT) &&
		(RpcExceptionCode() != STATUS_PRIVILEGED_INSTRUCTION) &&
		(RpcExceptionCode() != STATUS_ILLEGAL_INSTRUCTION) &&
		(RpcExceptionCode() != STATUS_BREAKPOINT) &&
		(RpcExceptionCode() != STATUS_STACK_OVERFLOW) &&
		(RpcExceptionCode() != STATUS_IN_PAGE_ERROR) &&
		(RpcExceptionCode() != STATUS_ASSERTION_FAILURE) &&
		(RpcExceptionCode() != STATUS_STACK_BUFFER_OVERRUN) &&
		(RpcExceptionCode() != STATUS_GUARD_PAGE_VIOLATION)
		)
	{
		PRINT_ERROR(L"RPC Exception 0x%08x (%u)\n", RpcExceptionCode(), RpcExceptionCode());
	}
	return (drsStatus == 0);
}