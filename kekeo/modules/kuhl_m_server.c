/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_server.h"

const KUHL_M_C kuhl_m_c_server[] = {
	{kuhl_m_server_http,	L"http",	L"HTTP server to deal with Kerberos (and NTLM?)"},
};
const KUHL_M kuhl_m_server = {
	L"server",	NULL, NULL,
	ARRAYSIZE(kuhl_m_c_server), kuhl_m_c_server, NULL, NULL
};

NTSTATUS kuhl_m_server_http(int argc, wchar_t * argv[])
{
	LPCWSTR szData;
	LPSTR redirectUrl = NULL;
	int ret, clientAddrSize;
	SOCKET listenSocket, clientSocket;
	SOCKADDR_IN listenAddr = {AF_INET, htons(80), {0}}, clientAddr = {0};
	PKUHL_M_SERVER_HTTP_THREAD_DATA pData;
	HANDLE hThread;
	DWORD threadId;

	if(kull_m_string_args_byName(argc, argv, L"port", &szData, NULL))
		listenAddr.sin_port = htons((USHORT) wcstoul(szData, NULL, 0));
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
						if(pData = (PKUHL_M_SERVER_HTTP_THREAD_DATA) LocalAlloc(LPTR, sizeof(KUHL_M_SERVER_HTTP_THREAD_DATA)))
						{
							pData->clientAddr = clientAddr;
							pData->clientSocket = clientSocket;
							pData->aRedirectHeader = redirectUrl;
							if(hThread = CreateThread(NULL, 0, kuhl_m_server_http_thread, pData, 0, &threadId))
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

	return STATUS_SUCCESS;
}


DWORD WINAPI kuhl_m_server_http_thread(IN LPVOID lpParameter)
{
	PKUHL_M_SERVER_HTTP_THREAD_DATA pData = (PKUHL_M_SERVER_HTTP_THREAD_DATA) lpParameter;
	PBYTE buf;
	DWORD bufLen, timeout = 2000;
	PSTR authData = NULL;
	FILETIME fTime;
	BOOL mustRedir = TRUE;

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
		if(kuhl_m_server_http_recvForMe(pData->clientSocket, &buf, &bufLen))
		{
			if(authData = kuhl_m_server_http_dealWithHeaders((LPCSTR) buf, bufLen, "Authorization: "))
			{
				if(pData->UserCallback)
					mustRedir = pData->UserCallback(authData, pData->UserData);
				if(mustRedir)
				{
					if(pData->aRedirectHeader)
						kuhl_m_server_http_sendForMe(pData->clientSocket, 302, "Found", pData->aRedirectHeader);
					else kuhl_m_server_http_sendForMe(pData->clientSocket, 403, "Forbidden", NULL);
				}
				LocalFree(authData);
			}
			else kuhl_m_server_http_sendForMe(pData->clientSocket, 401, "Unauthorized", "WWW-Authenticate: Negotiate\r\n");
			LocalFree(buf);
		}
		shutdown(pData->clientSocket, SD_BOTH);
		closesocket(pData->clientSocket);
		LocalFree(pData);
	}
	kprintf(L"=====<\n");
	return ERROR_SUCCESS;
}

BOOL kuhl_m_server_http_decodeB64NTLMAuth(LPCSTR Scheme, LPCSTR b64, PBYTE *data, DWORD *dataLen)
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

BOOL kuhl_m_server_http_recvForMe(SOCKET clientSocket, LPBYTE *data, DWORD *dataLen)
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

BOOL kuhl_m_server_http_sendForMe(SOCKET clientSocket, USHORT Code, LPCSTR Reason, LPCSTR Header)
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

PSTR kuhl_m_server_http_dealWithHeaders(LPCSTR data, DWORD size, LPCSTR toFind)
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