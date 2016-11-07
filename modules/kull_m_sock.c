/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
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
BOOL kull_m_sock_SendAndRecv(PKULL_M_SOCK fullsocket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize)
{
	BOOL status = FALSE;
	int iResult;

	*dataOutSize = DEFAULT_BUFLEN;
	if(*dataOut = LocalAlloc(LPTR, DEFAULT_BUFLEN))
	{
		if(fullsocket->protocol == IPPROTO_TCP)
		{
			if(send(fullsocket->socket, (const char *) dataIn, dataInSize,  0) != SOCKET_ERROR)
			{
				iResult = recv(fullsocket->socket, (char *) *dataOut, *dataOutSize, 0);
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
		}
		else if(fullsocket->protocol == IPPROTO_UDP)
		{
			if(sendto(fullsocket->socket, (const char *) dataIn, dataInSize, 0, (SOCKADDR *) &fullsocket->address, sizeof(SOCKADDR_IN)) != SOCKET_ERROR)
			{
				iResult = recvfrom(fullsocket->socket, (char *) *dataOut, *dataOutSize, 0, NULL, NULL);
				if (iResult > 0)
				{
					status = TRUE;
					*dataOutSize = iResult;
				}
				else if (iResult == 0)
					kull_m_sock_error(0, "recvfrom/Connection closed");
				else kull_m_sock_error_auto("recvfrom");
			}
		}
		if(!status)
			LocalFree(*dataOut);
	}
	return status;
}

BOOL kull_m_sock_initSocket(PCSTR kdc, WORD Port, int protocol, PKULL_M_SOCK fullsocket)
{
	BOOL status = FALSE;
	PDNS_RECORD pRecords;
	DNS_STATUS dnsStatus;

	fullsocket->protocol = protocol;
	dnsStatus = DnsQuery(kdc, DNS_TYPE_A, DNS_QUERY_NO_NETBT | DNS_QUERY_NO_MULTICAST | DNS_QUERY_TREAT_AS_FQDN, NULL, &pRecords, NULL);
	if(!dnsStatus && (pRecords->wType == DNS_TYPE_A))
	{
		RtlZeroMemory(&fullsocket->address, sizeof(SOCKADDR_IN));
		fullsocket->address.sin_family = AF_INET;
		fullsocket->address.sin_port = htons(Port);
		fullsocket->address.sin_addr.s_addr = pRecords->Data.A.IpAddress;

		fullsocket->socket = socket(AF_INET, (protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, protocol);
		if(status = (fullsocket->socket != INVALID_SOCKET))
		{
			if(protocol == IPPROTO_TCP)
				if(!(status = (connect(fullsocket->socket, (SOCKADDR *) &fullsocket->address, sizeof(SOCKADDR_IN)) == ERROR_SUCCESS)))
					kull_m_sock_error_auto("connect");
		}
		else kull_m_sock_error_auto("socket");
		DnsRecordListFree(pRecords, DnsFreeRecordList);
	}
	else PRINT_ERROR("DnsQuery: %08x\n", dnsStatus);
	return status;
}

BOOL kull_m_sock_termSocket(PKULL_M_SOCK fullsocket)
{
	BOOL status = FALSE;
	if(!(status = (closesocket(fullsocket->socket) == ERROR_SUCCESS)))
		kull_m_sock_error_auto("closesocket");
	return status;
}

BOOL kull_m_sock_kerberos_SendAndRecv(PKULL_M_SOCK fullsocket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize)
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
						PRINT_ERROR("Packet size + 4 != Kerberos Packet Size\n");

					if(!status)
						LocalFree(*dataOut);
				}
				LocalFree(buffer);
			}
			LocalFree(data);
		}
	}
	else if(fullsocket->protocol == IPPROTO_UDP)
	{
		status = kull_m_sock_SendAndRecv(fullsocket, dataIn, dataInSize, dataOut, dataOutSize);
	}
	return status;
}