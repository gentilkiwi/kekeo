/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#include "kull_m_sock.h"

WSADATA kull_m_sock_wsData;

BOOL kull_m_sock_startup()
{
	BOOL status;
	int error = WSAStartup(MAKEWORD(2, 2), &kull_m_sock_wsData);
	status = (error == ERROR_SUCCESS);
	if(!status)
		kull_m_sock_error(error, "WSAStartup");
	return status;
}

BOOL kull_m_sock_finish()
{
	BOOL status;
	status = (WSACleanup() == ERROR_SUCCESS);
	if(!status)
		kull_m_sock_error_auto("WSACleanup");
	return status;
}

void kull_m_sock_error_auto(PCSTR source)
{
	kull_m_sock_error(WSAGetLastError(), source);
}

void kull_m_sock_error(int error, PCSTR source)
{
	PRINT_ERROR("[SOCKET] %s : %i\n", source, error);
}

#define DEFAULT_BUFLEN (64*1024)
BOOL kull_m_sock_SendAndRecv(SOCKET *Socket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize)
{
	BOOL status = FALSE;
	int iResult;

	*dataOutSize = DEFAULT_BUFLEN;
	if(*dataOut = LocalAlloc(LPTR, DEFAULT_BUFLEN))
	{
		if(send(*Socket, (const char *) dataIn, dataInSize,  0) != SOCKET_ERROR)
		{
			iResult = recv(*Socket, (char *) *dataOut, *dataOutSize, 0);
			if (iResult > 0)
			{
				status = TRUE;
				*dataOutSize = iResult;
			}
			else if (iResult == 0)
				kull_m_sock_error(0, "recv/Connection closed");
			else kull_m_sock_error_auto("recv");
		}
		else kull_m_sock_error_auto("send");

		if(!status)
			LocalFree(*dataOut);
	}
	return status;
}

BOOL kull_m_sock_initSocket(PCSTR kdc, WORD Port, SOCKET *Socket)
{
	BOOL status = FALSE;
	PDNS_RECORD pRecords;
	DNS_STATUS dnsStatus;
	SOCKADDR_IN clientService;

	dnsStatus = DnsQuery(kdc, DNS_TYPE_A, DNS_QUERY_NO_NETBT | DNS_QUERY_NO_MULTICAST | DNS_QUERY_TREAT_AS_FQDN, NULL, &pRecords, NULL);
	if(!dnsStatus && (pRecords->wType == DNS_TYPE_A))
	{
		RtlZeroMemory(&clientService, sizeof(SOCKADDR_IN));
		clientService.sin_family = AF_INET;
		clientService.sin_port = htons(Port);
		clientService.sin_addr.s_addr = pRecords->Data.A.IpAddress;

		*Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(status = (*Socket != INVALID_SOCKET))
		{
			if(!(status = (connect(*Socket, (SOCKADDR *) &clientService, sizeof(SOCKADDR_IN)) == ERROR_SUCCESS)))
				kull_m_sock_error_auto("connect");
		}
		else kull_m_sock_error_auto("socket");
		DnsRecordListFree(pRecords, DnsFreeRecordList);
	}
	else PRINT_ERROR("DnsQuery: %08x\n", dnsStatus);
	return status;
}

BOOL kull_m_sock_termSocket(SOCKET *Socket)
{
	BOOL status = FALSE;
	if(!(status = (closesocket(*Socket) == ERROR_SUCCESS)))
		kull_m_sock_error_auto("closesocket");
	return status;
}