/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_ntlm.h"

const KUHL_M_C kuhl_m_c_ntlm[] = {
	{kuhl_m_ntlm_netntlm,	L"netntlm",	NULL},
	{kuhl_m_ntlm_http,		L"http",	NULL},
};
const KUHL_M kuhl_m_ntlm = {
	L"ntlm",	L"NTLM module", NULL,
	ARRAYSIZE(kuhl_m_c_ntlm), kuhl_m_c_ntlm, NULL, NULL
};

NTSTATUS kuhl_m_ntlm_netntlm(int argc, wchar_t * argv[])
{
	SECURITY_STATUS status;
	CredHandle Credentials;
	TimeStamp CredentialsExpiry, SecurityContextExpiry;
	CtxtHandle NewContext = {0};
	SecBuffer InBuff, OutBuff = {0, SECBUFFER_TOKEN, NULL}, Out2Buff = {0, SECBUFFER_TOKEN, NULL};
	SecBufferDesc Output = {SECBUFFER_VERSION, 1, &OutBuff}, Input = {SECBUFFER_VERSION, 1, &InBuff}, Output2 = {SECBUFFER_VERSION, 1, &Out2Buff};
	ULONG ContextAttr, flags = 0;
	PCWCHAR TargetName = NULL, DomainName = NULL, ComputerName = NULL, FileName = NULL;

	if(!kull_m_string_args_byName(argc, argv, L"in", &FileName, NULL))
	{
		kull_m_string_args_byName(argc, argv, L"target", &TargetName, NULL);
		kull_m_string_args_byName(argc, argv, L"domain", &DomainName, NULL);
		kull_m_string_args_byName(argc, argv, L"computer", &ComputerName, NULL);
		if(!kull_m_string_args_byName(argc, argv, L"no56", NULL, NULL))
			flags |= NTLMSSP_NEGOTIATE_56;
		if(!kull_m_string_args_byName(argc, argv, L"no128", NULL, NULL))
			flags |= NTLMSSP_NEGOTIATE_128;
		if(!kull_m_string_args_byName(argc, argv, L"noAlwaysSign", NULL, NULL))
			flags |= NTLMSSP_NEGOTIATE_ALWAYS_SIGN;
		if(!kull_m_string_args_byName(argc, argv, L"noESS", NULL, NULL))
			flags |= NTLMSSP_NEGOTIATE_EXTENDED_SESSIONSECURITY;
		if(kull_m_string_args_byName(argc, argv, L"keyx", NULL, NULL))
			flags |= NTLMSSP_NEGOTIATE_KEY_EXCH;
		if(kull_m_string_args_byName(argc, argv, L"seal", NULL, NULL))
			flags |= NTLMSSP_NEGOTIATE_SEAL;
		if(kull_m_string_args_byName(argc, argv, L"sign", NULL, NULL))
			flags |= NTLMSSP_NEGOTIATE_SIGN;
	}
	status = AcquireCredentialsHandle(NULL, L"NTLM", SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &Credentials, &CredentialsExpiry);
	if(status == SEC_E_OK)
	{
		kprintf(L"NEGOTIATE   :\n");
		status = InitializeSecurityContext(&Credentials, NULL, NULL, ISC_REQ_CONNECTION | ISC_REQ_ALLOCATE_MEMORY, 0, SECURITY_NATIVE_DREP, NULL, 0, &NewContext, &Output, &ContextAttr, &SecurityContextExpiry);
		if(status == SEC_I_CONTINUE_NEEDED)
		{
			kull_m_ntlm_descrGeneric(&Output, NTLMSSP_TypeOneMessage);
			kprintf(L"CHALLENGE   :\n");
			if(kuhl_m_ntlm_netntlm_buildChallenge(&InBuff, FileName, NULL, NULL, TargetName, DomainName, ComputerName, NULL, flags))
			{
				kull_m_ntlm_descrGeneric(&Input, NTLMSSP_TypeTwoMessage);
				kprintf(L"AUTHENTICATE:\n"); 
				status = InitializeSecurityContext(&Credentials, &NewContext, NULL, ISC_REQ_CONNECTION | ISC_REQ_ALLOCATE_MEMORY, 0, SECURITY_NATIVE_DREP, &Input, 0, &NewContext, &Output2, &ContextAttr, &SecurityContextExpiry);
				if(status == SEC_E_OK)
				{
					kull_m_ntlm_descrGeneric(&Output2, NTLMSSP_TypeThreeMessage);
					FreeContextBuffer(Out2Buff.pvBuffer);
				}
				else PRINT_ERROR(L"InitializeSecurityContext(2/2): 0x%08x\n", status);
				LocalFree(InBuff.pvBuffer);
			}
			FreeContextBuffer(OutBuff.pvBuffer);
			DeleteSecurityContext(&NewContext);
		}
		else PRINT_ERROR(L"InitializeSecurityContext(1/2): 0x%08x\n", status);
		FreeCredentialHandle(&Credentials);
	}
	else PRINT_ERROR(L"AcquireCredentialsHandle: 0x%08x\n", status);
	return STATUS_SUCCESS;
}

BOOL kuhl_m_ntlm_netntlm_buildChallenge(SecBuffer *buffer, const wchar_t *FileName, const UCHAR Challenge[8], KIWI_NTLM_VERSION *Version, const wchar_t *TargetName, const wchar_t *DomainName, const wchar_t *ComputerName, const FILETIME *timeStamp, ULONG AdditionnalFlags)
{
	PUCHAR TiBuffer = NULL;
	USHORT TaSize = 0, TiSize = 0;
	ULONG FileLen;
	PKIWI_NTLM_CHALLENGE_MESSAGE pChal;
	FILETIME ft;

	buffer->cbBuffer = 0;
	buffer->pvBuffer = NULL;
	buffer->BufferType = SECBUFFER_TOKEN;
	
	if(FileName)
	{
		if(kull_m_file_readData(FileName, (PBYTE *) &buffer->pvBuffer, &FileLen))
		{
			if((FileLen > (sizeof(ULONGLONG) + sizeof(ULONG))) && (FileLen <= MAXWORD))
				buffer->cbBuffer = (USHORT) FileLen;
			else
			{
				PRINT_ERROR(L"File size: %u\n", FileLen);
				LocalFree(buffer->pvBuffer);
				buffer->pvBuffer = NULL;
			}
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	}
	else
	{
		if(TargetName)
			TaSize = (USHORT) lstrlen(TargetName) * sizeof(wchar_t);
		if(DomainName && ComputerName)
		{
			if(!timeStamp)
			{
				GetSystemTimeAsFileTime(&ft);
				timeStamp = &ft;
			}
			kuhl_m_ntlm_netntlm_buildAvPairs(&TiBuffer, &TiSize, MsvAvNbDomainName, DomainName, MsvAvNbComputerName, ComputerName, MsvAvTimestamp, timeStamp, MsvAvEOL);
		}
		buffer->cbBuffer = FIELD_OFFSET(KIWI_NTLM_CHALLENGE_MESSAGE, Payload) + TaSize + TiSize;
		if(buffer->pvBuffer = LocalAlloc(LPTR, buffer->cbBuffer))
		{
			pChal = (PKIWI_NTLM_CHALLENGE_MESSAGE) buffer->pvBuffer;
			pChal->Signature = NTLMSSP_Signature_ULL;
			pChal->MessageType = NTLMSSP_TypeTwoMessage;
			pChal->TargetNameFields.Len = pChal->TargetNameFields.MaxLen = TaSize;
			pChal->TargetNameFields.Offset = FIELD_OFFSET(KIWI_NTLM_CHALLENGE_MESSAGE, Payload);
			pChal->NegotiateFlags = NTLMSSP_NEGOTIATE_UNICODE | NTLMSSP_NEGOTIATE_NTLM | NTLMSSP_NEGOTIATE_VERSION | AdditionnalFlags;
			if(Challenge)
				RtlCopyMemory(pChal->Challenge, Challenge, sizeof(pChal->Challenge));
			else
				CDGenerateRandomBits(pChal->Challenge, sizeof(pChal->Challenge));
			RtlZeroMemory(pChal->Reserved, 8);
			pChal->TargetInfoFields.Len = pChal->TargetInfoFields.MaxLen = TiSize;
			pChal->TargetInfoFields.Offset = pChal->TargetNameFields.Offset + pChal->TargetNameFields.MaxLen;
			if(Version)
				pChal->Version = *Version;
			else
			{
				pChal->Version.ProductMajorVersion = 6;
				pChal->Version.ProductMinorVersion = 1;
				pChal->Version.ProductBuild = 7601;
				RtlZeroMemory(pChal->Version.Reserved, sizeof(pChal->Version.Reserved));
				pChal->Version.NTLMRevisionCurrent = 15;
			}
			if(TaSize)
			{
				pChal->NegotiateFlags |= NTLMSSP_REQUEST_TARGET | NTLMSSP_TARGET_TYPE_DOMAIN;
				RtlCopyMemory((PUCHAR) pChal + pChal->TargetNameFields.Offset, TargetName, TaSize);
			}
			if(TiSize)
			{
				pChal->NegotiateFlags |= NTLMSSP_NEGOTIATE_TARGET_INFO;
				RtlCopyMemory((PUCHAR) pChal + pChal->TargetInfoFields.Offset, TiBuffer, TiSize);
			}
		}
		if(TiBuffer)
			LocalFree(TiBuffer);
	}
	return (buffer->pvBuffer != NULL);
}

void kuhl_m_ntlm_netntlm_buildAvPairs(PUCHAR *buffer, USHORT *size, ...)
{
	va_list vaList;
	MSV1_0_AVID type;
	PKIWI_NTLM_AV_PAIR pair;
	PVOID data;

	*buffer = NULL;
	*size = 0;
	va_start(vaList, size); 
	do
	{
		type = va_arg(vaList, MSV1_0_AVID);
		*size += FIELD_OFFSET(KIWI_NTLM_AV_PAIR, Value);
		switch(type)
		{
			case MsvAvNbComputerName:
			case MsvAvNbDomainName:
			case MsvAvDnsComputerName:
			case MsvAvDnsDomainName:
			case MsvAvDnsTreeName:
			case MsvAvTargetName:
				*size += lstrlen(va_arg(vaList, wchar_t *)) * (USHORT) sizeof(wchar_t);
				break;
			case MsvAvFlags:
				*size += sizeof(ULONG);
				va_arg(vaList, ULONG);
				break;
			case MsvAvTimestamp:
				*size += sizeof(FILETIME);
				va_arg(vaList, FILETIME *);
				break;
			case MsvAvRestrictions:
				*size += (USHORT) va_arg(vaList, PKIWI_NTLM_Single_Host_Data)->Size;
				break;
			case MsvAvChannelBindings:
				*size += MD5_DIGEST_LENGTH;
				va_arg(vaList, PVOID);
				break;
			case MsvAvEOL:
				break;
		}
	} while(type != MsvAvEOL);
	va_end(vaList);

	if(*buffer = (PUCHAR) LocalAlloc(LPTR, *size))
	{
		va_start(vaList, size); 
		pair = (PKIWI_NTLM_AV_PAIR) *buffer;
		do
		{
			data = NULL;
			type = va_arg(vaList, MSV1_0_AVID);
			pair->AvId = type;
			switch(type)
			{
			case MsvAvNbComputerName:
			case MsvAvNbDomainName:
			case MsvAvDnsComputerName:
			case MsvAvDnsDomainName:
			case MsvAvDnsTreeName:
			case MsvAvTargetName:
				data = va_arg(vaList, wchar_t *);
				pair->AvLen = (USHORT) lstrlen((wchar_t *) data) * sizeof(wchar_t);
				break;
			case MsvAvFlags:
				data = vaList;
				va_arg(vaList, ULONG);
				pair->AvLen = sizeof(ULONG);
				break;
			case MsvAvTimestamp:
				data = va_arg(vaList, FILETIME *);
				pair->AvLen = sizeof(FILETIME);
				break;
			case MsvAvRestrictions:
				data = va_arg(vaList, PKIWI_NTLM_Single_Host_Data);
				pair->AvLen = (USHORT) ((PKIWI_NTLM_Single_Host_Data) data)->Size;
				break;
			case MsvAvChannelBindings:
				data = va_arg(vaList, PVOID);
				pair->AvLen = MD5_DIGEST_LENGTH;
				break;
			case MsvAvEOL:
			default:
				pair->AvLen = 0;
				data = NULL;
				break;
			}
			if(pair->AvLen && data)
				RtlCopyMemory(pair->Value, data, pair->AvLen);
			pair = (PKIWI_NTLM_AV_PAIR) ((PUCHAR) pair + FIELD_OFFSET(KIWI_NTLM_AV_PAIR, Value) + pair->AvLen);
		} while(type != MsvAvEOL);
		va_end(vaList);
	}
}

DECLARE_UNICODE_STRING(uNTLM, L"NTLM");
DECLARE_UNICODE_STRING(uNegotiate, L"Negotiate");
NTSTATUS kuhl_m_ntlm_http(int argc, wchar_t * argv[])
{
	PKIWI_HTTP pHttp;
	DWORD dwIndex, dwLen, dwDisableRedirect = WINHTTP_OPTION_REDIRECT_POLICY_NEVER, dwInfoLevel;
	WORD httpStatus;
	wchar_t *text, *inputChallenge;
	UNICODE_STRING scheme;
	BOOL isNTLM, isNego, isProxy;

	SECURITY_STATUS status;
	CredHandle Credentials;
	TimeStamp CredentialsExpiry, SecurityContextExpiry;
	CtxtHandle NewContext = {0};
	SecBuffer InBuff, OutBuff = {0, SECBUFFER_TOKEN, NULL}, Out2Buff = {0, SECBUFFER_TOKEN, NULL};
	SecBufferDesc Output = {SECBUFFER_VERSION, 1, &OutBuff}, Input = {SECBUFFER_VERSION, 1, &InBuff}, Output2 = {SECBUFFER_VERSION, 1, &Out2Buff};
	ULONG ContextAttr;
	PCWCHAR szUrl, szHeader;
	PWCHAR package, negoHeader, authHeader;
	SEC_WINNT_AUTH_IDENTITY altIdentity = {NULL, 0, NULL, 0, NULL, 0, SEC_WINNT_AUTH_IDENTITY_UNICODE};

	if(kull_m_string_args_byName(argc, argv, L"url", &szUrl, NULL))
	{
		if(kull_m_string_args_byName(argc, argv, L"user", (PCWCHAR *) &altIdentity.User, NULL))
		{
			altIdentity.UserLength = lstrlen((LPCWSTR) altIdentity.User);
			if(kull_m_string_args_byName(argc, argv, L"domain", (PCWCHAR *) &altIdentity.Domain, NULL))
				altIdentity.DomainLength = lstrlen((LPCWSTR) altIdentity.Domain);
			if(kull_m_string_args_byName(argc, argv, L"password", (PCWCHAR *) &altIdentity.Password, NULL))
				altIdentity.PasswordLength = lstrlen((LPCWSTR) altIdentity.Password);
		}

		if(pHttp = kuhl_m_ntlm_http_giveHTTP(szUrl, NULL))
		{
			kprintf(L"\n[Server]\n");
			if(kuhl_m_ntlm_http_sendReceiveHTTP(pHttp, WINHTTP_NO_ADDITIONAL_HEADERS, NULL, NULL, &httpStatus))
			{
				if(kuhl_m_ntlm_http_getHeaders(pHttp, WINHTTP_QUERY_SERVER, WINHTTP_NO_HEADER_INDEX, (PBYTE *) &text, &dwLen))
				{
					kprintf(L"  Server: %.*s\n", dwLen / sizeof(wchar_t), text);
					LocalFree(text);
				}
				if((httpStatus == HTTP_STATUS_DENIED) || (httpStatus == HTTP_STATUS_PROXY_AUTH_REQ))
				{
					if(httpStatus == HTTP_STATUS_DENIED)
					{
						isProxy = FALSE;
						dwInfoLevel = WINHTTP_QUERY_WWW_AUTHENTICATE;
						szHeader = L"WWW-Authenticate";
					}
					else
					{
						isProxy = TRUE;
						dwInfoLevel = WINHTTP_QUERY_PROXY_AUTHENTICATE;
						szHeader = L"Proxy-Authenticate";
					}
					kprintf(L"  %s: ", szHeader);
					for(isNTLM = isNego = FALSE, dwIndex = 0; kuhl_m_ntlm_http_getHeaders(pHttp, dwInfoLevel, &dwIndex, (PBYTE *) &text, &dwLen);)
					{
						scheme.Length = scheme.MaximumLength = (WORD) dwLen;
						scheme.Buffer = text;
						kprintf(L"`%wZ`, ", &scheme);
						if(RtlEqualUnicodeString(&uNTLM, &scheme, TRUE))
							isNTLM = TRUE;
						else if(RtlEqualUnicodeString(&uNegotiate, &scheme, TRUE))
							isNego = TRUE;
						LocalFree(text);
					}
					kprintf(L"\n");
					if(isNego || isNTLM)
					{
						package = isNego ? L"Negotiate" : L"NTLM";
						status = AcquireCredentialsHandle(NULL, L"NTLM"/*package*/, SECPKG_CRED_OUTBOUND, NULL, altIdentity.UserLength ? &altIdentity : NULL, NULL, NULL, &Credentials, &CredentialsExpiry);
						if(status == SEC_E_OK)
						{
							kprintf(L"\n[SSPI - NEGOTIATE]\n");
							status = InitializeSecurityContext(&Credentials, NULL, NULL, ISC_REQ_CONNECTION | ISC_REQ_ALLOCATE_MEMORY, 0, SECURITY_NATIVE_DREP, NULL, 0, &NewContext, &Output, &ContextAttr, &SecurityContextExpiry);
							if(status == SEC_I_CONTINUE_NEEDED)
							{
								kull_m_ntlm_descrGeneric(&Output, NTLMSSP_TypeOneMessage);
								if(negoHeader = kuhl_m_ntlm_http_encodeAuthNTLMB64(package, isProxy, &Output))
								{
									kprintf(L"[Client]\n  %s\n\n[Server]\n", negoHeader);
									if(kuhl_m_ntlm_http_sendReceiveHTTP(pHttp, negoHeader, NULL, NULL, &httpStatus))
									{
										kprintf(L"  %s: ", szHeader);
										if(kuhl_m_ntlm_http_getHeaders(pHttp, dwInfoLevel, WINHTTP_NO_HEADER_INDEX, (PBYTE *) &inputChallenge, &dwLen))
										{
											kprintf(L"%.*s\n[SSPI - CHALLENGE]\n", dwLen / sizeof(wchar_t), inputChallenge);
											if(kuhl_m_ntlm_http_decodeB64NTLMAuth(package, inputChallenge, &Input))
											{
												kull_m_ntlm_descrGeneric(&Input, NTLMSSP_TypeTwoMessage);
												if(altIdentity.UserLength || kull_m_string_args_byName(argc, argv, L"auth", NULL, NULL))
												{
													kprintf(L"\n[SSPI - AUTHENTICATE]\n");
													status = InitializeSecurityContext(&Credentials, &NewContext, NULL, ISC_REQ_CONNECTION | ISC_REQ_ALLOCATE_MEMORY, 0, SECURITY_NATIVE_DREP, &Input, 0, &NewContext, &Output2, &ContextAttr, &SecurityContextExpiry);
													if(status == SEC_E_OK)
													{
														kull_m_ntlm_descrGeneric(&Output2, NTLMSSP_TypeThreeMessage);
														if(authHeader = kuhl_m_ntlm_http_encodeAuthNTLMB64(package, isProxy, &Output2))
														{
															kprintf(L"[Client]\n  %s\n\n[Server]\n", authHeader);
															if(!WinHttpSetOption(pHttp->hRequest, WINHTTP_OPTION_REDIRECT_POLICY, &dwDisableRedirect, sizeof(dwDisableRedirect)))
																PRINT_ERROR_AUTO(L"WinHttpSetOption(WINHTTP_OPTION_REDIRECT_POLICY, WINHTTP_OPTION_REDIRECT_POLICY_NEVER)");
															if(kuhl_m_ntlm_http_sendReceiveHTTP(pHttp, authHeader, NULL, NULL, &httpStatus))
															{
																if((httpStatus >= 300) && (httpStatus < 400))
																{
																	if(kuhl_m_ntlm_http_getHeaders(pHttp, WINHTTP_QUERY_LOCATION, WINHTTP_NO_HEADER_INDEX, (PBYTE *) &text, &dwLen))
																	{
																		kprintf(L"  Location: %.*s\n", dwLen / sizeof(wchar_t), text);
																		LocalFree(text);
																	}
																}
															}
															LocalFree(authHeader);
														}
														FreeContextBuffer(Out2Buff.pvBuffer);
													}
													else PRINT_ERROR(L"InitializeSecurityContext(2/2): 0x%08x\n", status);
												}
												LocalFree(Input.pBuffers[0].pvBuffer);
											}
											LocalFree(inputChallenge);
										}
									}
									LocalFree(negoHeader);
								}
								FreeContextBuffer(OutBuff.pvBuffer);
							}
							else PRINT_ERROR(L"InitializeSecurityContext(1/2): 0x%08x\n", status);
							FreeCredentialHandle(&Credentials);
						}
						else PRINT_ERROR(L"AcquireCredentialsHandle: 0x%08x\n", status);
					}
				}
			}
			kuhl_m_ntlm_http_closeHTTP(pHttp, TRUE);
		}
	}
	else PRINT_ERROR(L"Missing /url:http[s]://server[:port][/...]\n");
	return STATUS_SUCCESS;
}

PKIWI_HTTP kuhl_m_ntlm_http_giveHTTP(LPCWSTR url, LPCWSTR verb)
{
	KIWI_HTTP kHttp = {0}, *kReturn = NULL;
	BOOL status = FALSE;
	URL_COMPONENTS urlComponents = {0};
	DWORD dwDisableAuth = WINHTTP_DISABLE_AUTHENTICATION, dwDisableCertErrors = SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_CERT_CN_INVALID | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID | SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE;
	wchar_t *hostname = NULL;

	urlComponents.dwStructSize = sizeof(urlComponents);
	urlComponents.dwHostNameLength = (DWORD) -1;
	urlComponents.dwUrlPathLength = (DWORD) -1;
	if(WinHttpCrackUrl(url, 0, 0, &urlComponents))
	{
		kprintf(L"Using: %.*s on port %hu for \'%s\'", urlComponents.dwHostNameLength, urlComponents.lpszHostName, urlComponents.nPort, urlComponents.lpszUrlPath);
		if(urlComponents.nScheme == INTERNET_SCHEME_HTTPS)
			kprintf(L" - SSL\n");
		else kprintf(L"\n");
		if(hostname = (wchar_t *) LocalAlloc(LPTR, (urlComponents.dwHostNameLength + 1) * sizeof(wchar_t)))
		{
			RtlCopyMemory(hostname, urlComponents.lpszHostName, urlComponents.dwHostNameLength * sizeof(wchar_t));
			if(kHttp.hSession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0))
			{
				if(kHttp.hConnect = WinHttpConnect(kHttp.hSession, hostname, urlComponents.nPort, 0))
				{
					if(kHttp.hRequest = WinHttpOpenRequest(kHttp.hConnect, verb ? verb : L"GET", urlComponents.lpszUrlPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, (urlComponents.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0))
					{
						if(WinHttpSetOption(kHttp.hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &dwDisableAuth, sizeof(dwDisableAuth)))
						{
							if(!(status = WinHttpSetOption(kHttp.hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwDisableCertErrors, sizeof(dwDisableCertErrors))))
								PRINT_ERROR_AUTO(L"WinHttpSetOption(WINHTTP_OPTION_SECURITY_FLAGS, certificate)");
						}
						else PRINT_ERROR_AUTO(L"WinHttpSetOption(WINHTTP_OPTION_DISABLE_FEATURE, WINHTTP_DISABLE_AUTHENTICATION)");
					}
					else PRINT_ERROR_AUTO(L"WinHttpOpenRequest");
				}
				else PRINT_ERROR_AUTO(L"WinHttpConnect");
			}
			else PRINT_ERROR_AUTO(L"WinHttpOpen");
			LocalFree(hostname);
		}
	}
	else PRINT_ERROR_AUTO(L"WinHttpCrackUrl");

	if(status)
	{
		if(kReturn = (PKIWI_HTTP) LocalAlloc(LPTR, sizeof(KIWI_HTTP)))
			*kReturn = kHttp;
	}
	else kuhl_m_ntlm_http_closeHTTP(&kHttp, FALSE);
	return kReturn;
}

void kuhl_m_ntlm_http_closeHTTP(PKIWI_HTTP kHttp, BOOL freeIt)
{
	if(kHttp)
	{
		if(kHttp->hRequest)
			WinHttpCloseHandle(kHttp->hRequest);
		if(kHttp->hConnect)
			WinHttpCloseHandle(kHttp->hConnect);
		if(kHttp->hSession)
			WinHttpCloseHandle(kHttp->hSession);
		if(freeIt)
			LocalFree(kHttp);
	}
}

BOOL kuhl_m_ntlm_http_getHeaders(PKIWI_HTTP pHttp, DWORD dwInfoLevel, PDWORD pdwIndex, PBYTE *data, DWORD *len)
{
	BOOL status = FALSE;
	if(!WinHttpQueryHeaders(pHttp->hRequest, dwInfoLevel, WINHTTP_HEADER_NAME_BY_INDEX, WINHTTP_NO_OUTPUT_BUFFER, len, pdwIndex) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
	{
		if(*data = (PBYTE) LocalAlloc(LPTR, *len))
		{
			if(!(status = WinHttpQueryHeaders(pHttp->hRequest, dwInfoLevel, WINHTTP_HEADER_NAME_BY_INDEX, *data, len, pdwIndex)))
			{
				PRINT_ERROR_AUTO(L"WinHttpQueryHeaders(2/2");
				LocalFree(*data);
			}
		}
	}
	else if(GetLastError() != ERROR_WINHTTP_HEADER_NOT_FOUND) PRINT_ERROR_AUTO(L"WinHttpQueryHeaders(1/2)");
	return status;
}

BOOL kuhl_m_ntlm_http_sendReceiveHTTP(PKIWI_HTTP pHttp, PCWCHAR headers, PBYTE *data, DWORD *len, WORD *httpStatus)
{
	BOOL status = FALSE;
	DWORD dwStatusCode, dwLen = sizeof(dwStatusCode), dwText;
	PBYTE text;

	if(WinHttpSendRequest(pHttp->hRequest, headers, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
	{
		if(WinHttpReceiveResponse(pHttp->hRequest, NULL))
		{
			kprintf(L"  Status: ");
			if(WinHttpQueryHeaders(pHttp->hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &dwStatusCode, &dwLen, WINHTTP_NO_HEADER_INDEX))
			{
				if(dwStatusCode <= MAXWORD)
				{
					kprintf(L"%u", dwStatusCode);
					if(httpStatus)
						*httpStatus = (WORD) dwStatusCode;
				}
			}
			kprintf(L" - ");
			if(kuhl_m_ntlm_http_getHeaders(pHttp, WINHTTP_QUERY_STATUS_TEXT, WINHTTP_NO_HEADER_INDEX, &text, &dwText))
				kprintf(L"%.*s", dwText / sizeof(wchar_t), text);
			kprintf(L"\n");

			if(data && len)
			{
				if(WinHttpQueryDataAvailable(pHttp->hRequest, &dwLen))
				{
					if(*data = (PBYTE) LocalAlloc(LPTR, dwLen))
					{
						*len = 0;
						if(!(status = WinHttpReadData(pHttp->hRequest, *data, dwLen, len)))
						{
							PRINT_ERROR_AUTO(L"WinHttpReadData");
							LocalFree(*data);
						}
					}
				}
				else PRINT_ERROR_AUTO(L"WinHttpQueryDataAvailable");
			}
			else status = TRUE;
		}
		else PRINT_ERROR_AUTO(L"WinHttpReceiveResponse");
	}
	else PRINT_ERROR_AUTO(L"WinHttpSendRequest");
	return status;
}

PWCHAR kuhl_m_ntlm_http_encodeAuthNTLMB64(LPCWCHAR Scheme, BOOL isProxy, PSecBufferDesc pBuf)
{
	PWCHAR out = NULL, Base64, ptr;
	DWORD dwNeed = 0;
	if(CryptBinaryToString((LPCBYTE) pBuf->pBuffers[0].pvBuffer, pBuf->pBuffers[0].cbBuffer, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, NULL, &dwNeed))
	{
		if(Base64 = (PWCHAR) LocalAlloc(LPTR, dwNeed * sizeof(wchar_t)))
		{
			if(CryptBinaryToString((LPCBYTE) pBuf->pBuffers[0].pvBuffer, pBuf->pBuffers[0].cbBuffer, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, Base64, &dwNeed))
			{
				if(MIMIKATZ_NT_MAJOR_VERSION < 6)
					for(ptr = Base64; ptr = wcsstr(ptr, L"\r\n"); RtlMoveMemory(ptr, ptr + 2, (lstrlen(ptr + 2) + 1) * sizeof(wchar_t)));
				kull_m_string_sprintf(&out, L"%s: %s %s", isProxy ? L"Proxy-Authorization": L"Authorization", Scheme, Base64);
			}
			else PRINT_ERROR_AUTO(L"CryptBinaryToString(data)");
			LocalFree(Base64);
		}
	}
	else PRINT_ERROR_AUTO(L"CryptBinaryToString(init)");
	return out;
}

BOOL kuhl_m_ntlm_http_decodeB64NTLMAuth(LPCWCHAR Scheme, PCWCHAR b64, PSecBufferDesc pBuf)
{
	BOOL status = FALSE;
	PWCHAR tmp;
	size_t off;
	pBuf->pBuffers[0].cbBuffer = 0;
	pBuf->pBuffers[0].pvBuffer = NULL;
	pBuf->pBuffers[0].BufferType = SECBUFFER_TOKEN;

	if(kull_m_string_sprintf(&tmp, L"%s ", Scheme))
	{
		if(wcsstr(b64, tmp) == b64)
		{
			off = wcslen(tmp);
			if(CryptStringToBinary(b64 + off, 0, CRYPT_STRING_BASE64, NULL, &pBuf->pBuffers[0].cbBuffer, NULL, NULL))
			{
				if(pBuf->pBuffers[0].pvBuffer = LocalAlloc(LPTR, pBuf->pBuffers[0].cbBuffer))
				{
					if(!(status = CryptStringToBinary(b64 + off, 0, CRYPT_STRING_BASE64, (PBYTE) pBuf->pBuffers[0].pvBuffer, &pBuf->pBuffers[0].cbBuffer, NULL, NULL)))
					{
						PRINT_ERROR_AUTO(L"CryptStringToBinary(data)");
						LocalFree(pBuf->pBuffers[0].pvBuffer);
						pBuf->pBuffers[0].cbBuffer = 0;
						pBuf->pBuffers[0].pvBuffer = NULL;
					}
				}
			}
			else PRINT_ERROR_AUTO(L"CryptStringToBinary(init)");
		}
		LocalFree(tmp);
	}
	return status;
}