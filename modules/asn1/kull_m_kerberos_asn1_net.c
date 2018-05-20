/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kull_m_kerberos_asn1_net.h"

BOOL kull_m_kerberos_asn1_net_callKdcOssBuf(PKULL_M_SOCK fullsocket, OssBuf *in, LPVOID * out, int outPdu)
{
	BOOL status = FALSE;
	OssBuf receivedData;
	*out = NULL;
	if(kull_m_kerberos_asn1_net_SendAndRecv(fullsocket, in->value, in->length, (LPVOID *) &receivedData.value, (DWORD *) &receivedData.length))
	{
		status = kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(&receivedData, outPdu, out);
		LocalFree(receivedData.value);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_net_callKadminOssBuf(PKULL_M_SOCK fullsocket, USHORT version, OssBuf *ReqIn, OssBuf *KrbPrivIn, AP_REP **ApRep, KRB_PRIV **KrbPriv)
{
	BOOL status = FALSE;
	PVOID bufferIn, bufferOut;
	DWORD sizeIn = 6 + ReqIn->length + KrbPrivIn->length, sizeOut;
	OssBuf buf;

	*ApRep = NULL;
	*KrbPriv = NULL;
	if(bufferIn = LocalAlloc(LPTR, sizeIn))
	{
		((PWORD) bufferIn)[0] = _byteswap_ushort((WORD) sizeIn);
		((PWORD) bufferIn)[1] = _byteswap_ushort(version);
		((PWORD) bufferIn)[2] = _byteswap_ushort((WORD) ReqIn->length);
		RtlCopyMemory((PBYTE) bufferIn + 6, ReqIn->value, ReqIn->length);
		RtlCopyMemory((PBYTE) bufferIn + 6 + ReqIn->length, KrbPrivIn->value, KrbPrivIn->length);

		if(kull_m_kerberos_asn1_net_SendAndRecv(fullsocket, bufferIn, sizeIn, &bufferOut, &sizeOut))
		{
			if((sizeOut == _byteswap_ushort(((PWORD) bufferOut)[0])) && (sizeOut > 6)) // ok fuck, exploit me
			{
				buf.length = _byteswap_ushort(((PWORD) bufferOut)[2]);
				buf.value = (PBYTE) bufferOut + 6;
				if(kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(&buf, AP_REP_PDU, (LPVOID *) ApRep))
				{
					buf.length = sizeOut - 6 - _byteswap_ushort(((PWORD) bufferOut)[2]);
					buf.value = (PBYTE) bufferOut + 6 + _byteswap_ushort(((PWORD) bufferOut)[2]);

					status = kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(&buf, KRB_PRIV_PDU, (LPVOID *) KrbPriv);
					if(!status)
					{
						if(*KrbPriv)
							ossFreePDU(&kull_m_kerberos_asn1_world, KRB_PRIV_PDU, *KrbPriv);
						if(*ApRep)
							ossFreePDU(&kull_m_kerberos_asn1_world, AP_REP_PDU, *ApRep);
					}
				}
			}
			else PRINT_ERROR(L"Size\n");
			
			LocalFree(bufferOut);
		}
		LocalFree(bufferIn);
	}
	return status;
}

BOOL kull_m_kerberos_asn1_net_SendAndRecv(PKULL_M_SOCK fullsocket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize)
{
	PVOID data, buffer;
	DWORD dataSize, bufferSize;
	BOOL status = FALSE;

	if(fullsocket->protocol == IPPROTO_TCP)
	{
		dataSize = dataInSize + sizeof(DWORD);
		if(data = LocalAlloc(LPTR, dataSize))
		{
			*(PDWORD) data = _byteswap_ulong(dataInSize);
			RtlCopyMemory((PBYTE) data + sizeof(DWORD), dataIn, dataInSize);
			if(status = kull_m_sock_SendAndRecv(fullsocket, data, dataSize, &buffer, &bufferSize))
			{
				*dataOutSize = bufferSize - sizeof(DWORD);
				if(*dataOut = LocalAlloc(LPTR, *dataOutSize))
				{
					RtlCopyMemory(*dataOut, (PBYTE) buffer + sizeof(DWORD), *dataOutSize);
					if(!(status = (*dataOutSize == _byteswap_ulong(*(PDWORD) buffer))))
						PRINT_ERROR(L"Packet size + 4 != Kerberos Packet Size\n");

					if(!status)
						LocalFree(*dataOut);
				}
				LocalFree(buffer);
			}
			LocalFree(data);
		}
	}
	else if(fullsocket->protocol == IPPROTO_UDP)
		status = kull_m_sock_SendAndRecv(fullsocket, dataIn, dataInSize, dataOut, dataOutSize);
	return status;
}

BOOL kull_m_kerberos_asn1_helper_util_decodeOrTryKrbError(OssBuf *data, int pdu, LPVOID *out)
{
	BOOL status = FALSE;
	KRB_ERROR *error = NULL;

	if(!(status = !ossDecode(&kull_m_kerberos_asn1_world, &pdu, data, out)))
	{
		pdu = KRB_ERROR_PDU;
		if(!ossDecode(&kull_m_kerberos_asn1_world, &pdu, data, (LPVOID *) &error))
		{
			kprintf(L"%s (%u) - ", kull_m_kerberos_asn1_helper_util_err_to_string(error->error_code), error->error_code);
			kull_m_kerberos_asn1_KerberosTime_print(&error->stime);
			kprintf(L"\n");
			ossFreePDU(&kull_m_kerberos_asn1_world, pdu, error);
		}
		else PRINT_ERROR(L"Unable to decode KRB Packet: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	}
	return status;
}

const KULL_M_KERBEROS_ASN1_HELPER_UTIL_ERR kull_m_kerberos_asn1_helper_util_err[] = {
	{0,		L"KDC_ERR_NONE"},
	{1,		L"KDC_ERR_NAME_EXP"},
	{2,		L"KDC_ERR_SERVICE_EXP"},
	{3,		L"KDC_ERR_BAD_PVNO"},
	{4,		L"KDC_ERR_C_OLD_MAST_KVNO"},
	{5,		L"KDC_ERR_S_OLD_MAST_KVNO"},
	{6,		L"KDC_ERR_C_PRINCIPAL_UNKNOWN"},
	{7,		L"KDC_ERR_S_PRINCIPAL_UNKNOWN"},
	{8,		L"KDC_ERR_PRINCIPAL_NOT_UNIQUE"},
	{9,		L"KDC_ERR_NULL_KEY"},
	{10,	L"KDC_ERR_CANNOT_POSTDATE"},
	{11,	L"KDC_ERR_NEVER_VALID"},
	{12,	L"KDC_ERR_POLICY"},
	{13,	L"KDC_ERR_BADOPTION"},
	{14,	L"KDC_ERR_ETYPE_NOSUPP"},
	{15,	L"KDC_ERR_SUMTYPE_NOSUPP"},
	{16,	L"KDC_ERR_PADATA_TYPE_NOSUPP"},
	{17,	L"KDC_ERR_TRTYPE_NOSUPP"},
	{18,	L"KDC_ERR_CLIENT_REVOKED"},
	{19,	L"KDC_ERR_SERVICE_REVOKED"},
	{20,	L"KDC_ERR_TGT_REVOKED"},
	{21,	L"KDC_ERR_CLIENT_NOTYET"},
	{22,	L"KDC_ERR_SERVICE_NOTYET"},
	{23,	L"KDC_ERR_KEY_EXPIRED"},
	{24,	L"KDC_ERR_PREAUTH_FAILED"},
	{25,	L"KDC_ERR_PREAUTH_REQUIRED"},
	{26,	L"KDC_ERR_SERVER_NOMATCH"},
	{27,	L"KDC_ERR_MUST_USE_USER2USER"},
	{28,	L"KDC_ERR_PATH_NOT_ACCEPTED"},
	{29,	L"KDC_ERR_SVC_UNAVAILABLE"},
	{31,	L"KRB_AP_ERR_BAD_INTEGRITY"},
	{32,	L"KRB_AP_ERR_TKT_EXPIRED"},
	{33,	L"KRB_AP_ERR_TKT_NYV"},
	{34,	L"KRB_AP_ERR_REPEAT"},
	{35,	L"KRB_AP_ERR_NOT_US"},
	{36,	L"KRB_AP_ERR_BADMATCH"},
	{37,	L"KRB_AP_ERR_SKEW"},
	{38,	L"KRB_AP_ERR_BADADDR"},
	{39,	L"KRB_AP_ERR_BADVERSION"},
	{40,	L"KRB_AP_ERR_MSG_TYPE"},
	{41,	L"KRB_AP_ERR_MODIFIED"},
	{42,	L"KRB_AP_ERR_BADORDER"},
	{44,	L"KRB_AP_ERR_BADKEYVER"},
	{45,	L"KRB_AP_ERR_NOKEY"},
	{46,	L"KRB_AP_ERR_MUT_FAIL"},
	{47,	L"KRB_AP_ERR_BADDIRECTION"},
	{48,	L"KRB_AP_ERR_METHOD"},
	{49,	L"KRB_AP_ERR_BADSEQ"},
	{50,	L"KRB_AP_ERR_INAPP_CKSUM"},
	{51,	L"KRB_AP_PATH_NOT_ACCEPTED"},
	{52,	L"KRB_ERR_RESPONSE_TOO_BIG"},
	{60,	L"KRB_ERR_GENERIC"},
	{61,	L"KRB_ERR_FIELD_TOOLONG"},
	{62,	L"KDC_ERROR_CLIENT_NOT_TRUSTED"},
	{63,	L"KDC_ERROR_KDC_NOT_TRUSTED"},
	{64,	L"KDC_ERROR_INVALID_SIG"},
	{65,	L"KDC_ERR_KEY_TOO_WEAK"},
	{66,	L"KDC_ERR_CERTIFICATE_MISMATCH"},
	{67,	L"KRB_AP_ERR_NO_TGT"},
	{68,	L"KDC_ERR_WRONG_REALM"},
	{69,	L"KRB_AP_ERR_USER_TO_USER_REQUIRED"},
	{70,	L"KDC_ERR_CANT_VERIFY_CERTIFICATE"},
	{71,	L"KDC_ERR_INVALID_CERTIFICATE"},
	{72,	L"KDC_ERR_REVOKED_CERTIFICATE"},
	{73,	L"KDC_ERR_REVOCATION_STATUS_UNKNOWN"},
	{74,	L"KDC_ERR_REVOCATION_STATUS_UNAVAILABLE"},
	{75,	L"KDC_ERR_CLIENT_NAME_MISMATCH"},
	{76,	L"KDC_ERR_KDC_NAME_MISMATCH"},
};

PCWSTR kull_m_kerberos_asn1_helper_util_err_to_string(DWORD id)
{
	DWORD i;
	for(i = 0; i < ARRAYSIZE(kull_m_kerberos_asn1_helper_util_err); i++)
		if(kull_m_kerberos_asn1_helper_util_err[i].id == id)
			return kull_m_kerberos_asn1_helper_util_err[i].name;
	return L"ERROR ?";
}

PKULL_M_SOCK kull_m_kerberos_asn1_net_AddressSocket_create(LPCWSTR domain, WORD port, int argc, wchar_t * argv[], BOOL withConnect)
{
	BOOL status = FALSE;
	PKULL_M_SOCK fullsocket = NULL;
	LPCWSTR szData;
	IPPROTO proto;
	PDOMAIN_CONTROLLER_INFO cInfo = NULL;
	DWORD ret;
	INT size = sizeof(SOCKADDR_IN);

	if(fullsocket = (PKULL_M_SOCK) LocalAlloc(LPTR, sizeof(KULL_M_SOCK)))
	{
		if(!port)
			port = KERBEROS_DEFAULT_PORT;
		proto = kull_m_string_args_byName(argc, argv, L"udp", NULL, NULL) ? IPPROTO_UDP : IPPROTO_TCP;

		if(kull_m_string_args_byName(argc, argv, L"kdc", &szData, NULL))
		{
			kprintf(L"[kdc] name: %s\n", szData);
			status = kull_m_sock_init_addr_protocol(szData, NULL, port, proto, fullsocket);
		}
		else if(domain)
		{
			ret = DsGetDcName(NULL, domain, NULL, NULL, DS_KDC_REQUIRED | DS_IS_DNS_NAME | DS_RETURN_DNS_NAME | DS_IP_REQUIRED, &cInfo);
			if(ret == ERROR_SUCCESS)
			{
				kprintf(L"[kdc] name: %s (auto)\n", cInfo->DomainControllerName + 2);
				
				if(cInfo->DomainControllerAddressType == DS_INET_ADDRESS) // let's avoid a query
				{
					kprintf(L"[kdc] addr: %s (auto)\n", cInfo->DomainControllerAddress + 2);
					if(!fullsocket->servername)
						fullsocket->servername = _wcsdup(cInfo->DomainControllerName + 2);
					if(!(status = kull_m_sock_init_addr_string(cInfo->DomainControllerAddress + 2, port, proto, fullsocket)))
						kull_m_sock_error_auto(L"WSAStringToAddress");
				}
				if(!status)
					status = kull_m_sock_init_addr_protocol(cInfo->DomainControllerName + 2, NULL, port, proto, fullsocket);
				NetApiBufferFree(cInfo);
			}
			else PRINT_ERROR(L"DsGetDcName: %u\n", ret);
		}
		else PRINT_ERROR(L"Not enough data to get a KDC (Realm or /kdc argument\n");

		if(status && withConnect)
			status = kull_m_sock_connect(fullsocket);
		if(!status)
		{
			kull_m_kerberos_asn1_net_AddressSocket_delete(fullsocket);
			fullsocket = NULL;
		}
	}
	return fullsocket;
}

void kull_m_kerberos_asn1_net_AddressSocket_delete(PKULL_M_SOCK fullsocket)
{
	if(fullsocket)
	{
		kull_m_sock_termSocket(fullsocket);
		LocalFree(fullsocket);
	}
}