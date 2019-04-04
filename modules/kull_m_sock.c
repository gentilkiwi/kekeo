/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "kull_m_sock.h"

WSADATA kull_m_sock_wsData;
BOOL kull_m_sock_isInit = FALSE;

BOOL kull_m_sock_startup()
{
	int error = WSAStartup(MAKEWORD(2, 2), &kull_m_sock_wsData);
	kull_m_sock_isInit = (error == ERROR_SUCCESS);
	if(!kull_m_sock_isInit)
		kull_m_sock_error(error, L"WSAStartup");
	return kull_m_sock_isInit;
}

BOOL kull_m_sock_finish()
{
	BOOL status = FALSE;
	if(kull_m_sock_isInit)
	{
		status = (WSACleanup() == ERROR_SUCCESS);
		if(status)
			kull_m_sock_isInit = FALSE;
		else kull_m_sock_error_auto(L"WSACleanup");
	}
	return status;
}

void kull_m_sock_error_auto(PCWSTR source)
{
	kull_m_sock_error(WSAGetLastError(), source);
}

void kull_m_sock_error(int error, PCWSTR source)
{
	PRINT_ERROR(L"[SOCKET] %s : %i\n", source, error);
}

BOOL kull_m_sock_SendAndRecv(PKULL_M_SOCK fullsocket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize)
{
	BOOL status = FALSE;
	int iResult;

	*dataOutSize = KULL_M_SOCK_DEFAULT_BUFLEN;
	if(*dataOut = LocalAlloc(LPTR, KULL_M_SOCK_DEFAULT_BUFLEN))
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
					kull_m_sock_error(0, L"recv/Connection closed");
				else kull_m_sock_error_auto(L"recv");
			}
			else kull_m_sock_error_auto(L"send");
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
					kull_m_sock_error(0, L"recvfrom/Connection closed");
				else kull_m_sock_error_auto(L"recvfrom");
			}
		}
		if(!status)
			LocalFree(*dataOut);
	}
	return status;
}

//BOOL kull_m_sock_initSocket(PCWSTR Server, WORD Port, IPPROTO protocol, PKULL_M_SOCK fullsocket)
//{
//	BOOL status = FALSE;
//	PDNS_RECORD pRecords;
//	DNS_STATUS dnsStatus;
//	
//	fullsocket->protocol = protocol;
//	dnsStatus = DnsQuery(Server, DNS_TYPE_A, DNS_QUERY_NO_NETBT | DNS_QUERY_NO_MULTICAST | DNS_QUERY_TREAT_AS_FQDN, NULL, &pRecords, NULL);
//	if(!dnsStatus && (pRecords->wType == DNS_TYPE_A))
//	{
//		RtlZeroMemory(&fullsocket->address, sizeof(SOCKADDR_IN));
//		fullsocket->address.sin_family = AF_INET;
//		fullsocket->address.sin_port = htons(Port);
//		fullsocket->address.sin_addr.s_addr = pRecords->Data.A.IpAddress;
//
//		fullsocket->socket = socket(AF_INET, (protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, protocol);
//		if(status = (fullsocket->socket != INVALID_SOCKET))
//		{
//			if(protocol == IPPROTO_TCP)
//				if(!(status = (connect(fullsocket->socket, (SOCKADDR *) &fullsocket->address, sizeof(SOCKADDR_IN)) == ERROR_SUCCESS)))
//					kull_m_sock_error_auto(L"connect");
//		}
//		else kull_m_sock_error_auto(L"socket");
//		DnsRecordListFree(pRecords, DnsFreeRecordList);
//	}
//	else PRINT_ERROR(L"DnsQuery: %08x\n", dnsStatus);
//	return status;
//}

BOOL kull_m_sock_termSocket(PKULL_M_SOCK fullsocket)
{
	BOOL status = FALSE;
	if(fullsocket->servername)
		free(fullsocket->servername);
	if(!(status = (closesocket(fullsocket->socket) == ERROR_SUCCESS)))
		kull_m_sock_error_auto(L"closesocket");
	return status;
}

void kull_m_sock_descr(PKULL_M_SOCK fullsocket)
{
	PCWSTR proto;
	kprintf(L"Server  : %s\n", fullsocket->servername);
	kprintf(L"Address : ");
	kull_m_sock_descr_addrin(&fullsocket->address);
	switch(fullsocket->protocol)
	{
	case IPPROTO_TCP:
		proto = L"TCP (STREAM)";
		break;
	case IPPROTO_UDP:
		proto = L"UDP (DGRAM)";
		break;
	default:
		proto = L"?";
	}
	kprintf(L"Protocol: %s\n", proto);
}

void kull_m_sock_descr_addrin(PSOCKADDR_IN addr)
{
	LPWSTR buffer;
	DWORD size = 0;
	if((WSAAddressToString((LPSOCKADDR) addr, sizeof(SOCKADDR_IN), NULL, NULL, &size) == SOCKET_ERROR) && (WSAGetLastError() == WSAEFAULT))
	{
		if(buffer = (LPWSTR) LocalAlloc(LPTR, size * sizeof(wchar_t)))
		{
			if(WSAAddressToString((LPSOCKADDR) addr, sizeof(SOCKADDR_IN), NULL, buffer, &size) == ERROR_SUCCESS)
				kprintf(L"%s\n", buffer);
			else kull_m_sock_error_auto(L"WSAAddressToString");
			LocalFree(buffer);
		}
	}
}

BOOL kull_m_sock_init_addr_protocol(PCWSTR Server, PCWSTR Service, WORD Port, IPPROTO Protocol, PKULL_M_SOCK fullsocket)
{
	BOOL status = FALSE;
	ADDRINFOW hints = {0, AF_INET, (Protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, Protocol, 0, NULL, NULL, NULL};
	PADDRINFOW ainfos = NULL;
	INT error;
	PDNS_RECORD pRecords = NULL;
	DNS_STATUS dnsStatus;

	RtlZeroMemory(fullsocket, sizeof(KULL_M_SOCK));
	fullsocket->protocol = Protocol;
	if(Service)
	{
		error = GetAddrInfoW(Server, Service, &hints, &ainfos);
		if(error == ERROR_SUCCESS)
		{
			if(ainfos) // only deal with 1st
			{
				fullsocket->address = *((SOCKADDR_IN *) ainfos->ai_addr);
				if(!fullsocket->address.sin_port)
					fullsocket->address.sin_port = htons(Port);
				if(!fullsocket->servername)
					fullsocket->servername = _wcsdup(Server);
				fullsocket->socket = WSASocket(fullsocket->address.sin_family, (fullsocket->protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, fullsocket->protocol, NULL, 0, 0);
				if(!(status = (fullsocket->socket != INVALID_SOCKET)))
					kull_m_sock_error_auto(L"WSASocket");

			}
			FreeAddrInfo(ainfos);
		}
		else kull_m_sock_error(error, L"GetAddrInfoW");
	}
	else if(!(status = kull_m_sock_init_addr_string(Server, Port, Protocol, fullsocket)))
	{
		dnsStatus = DnsQuery(Server, DNS_TYPE_A, DNS_QUERY_NO_NETBT | DNS_QUERY_NO_MULTICAST | DNS_QUERY_TREAT_AS_FQDN, NULL, &pRecords, NULL);
		if((dnsStatus == ERROR_SUCCESS) && pRecords)
		{
			if(pRecords->wType == DNS_TYPE_A)
			{
				fullsocket->address.sin_family = AF_INET;
				fullsocket->address.sin_port = htons(Port);
				fullsocket->address.sin_addr.s_addr = pRecords->Data.A.IpAddress;
				if(!fullsocket->servername)
					fullsocket->servername = _wcsdup(Server);
				fullsocket->socket = WSASocket(fullsocket->address.sin_family, (fullsocket->protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, fullsocket->protocol, NULL, 0, 0);
				if(!(status = (fullsocket->socket != INVALID_SOCKET)))
					kull_m_sock_error_auto(L"WSASocket");
			}
			else PRINT_ERROR(L"DnsQuery no A record\n");
			DnsRecordListFree(pRecords, DnsFreeRecordList);
		}
		else PRINT_ERROR(L"DnsQuery: %08x\n", dnsStatus);
	}
	return status;
}

BOOL kull_m_sock_init_addr_string(PCWSTR String, WORD Port, IPPROTO Protocol, PKULL_M_SOCK fullsocket)
{
	BOOL status = FALSE;
	INT size = sizeof(SOCKADDR_IN);
	if(status = (WSAStringToAddress((LPWSTR) String, AF_INET, NULL, (LPSOCKADDR) &fullsocket->address, &size) == ERROR_SUCCESS))
	{
		fullsocket->protocol = Protocol;
		if(!fullsocket->address.sin_port)
			fullsocket->address.sin_port = htons(Port);
		if(!fullsocket->servername)
			fullsocket->servername = _wcsdup(String);
		fullsocket->socket = WSASocket(fullsocket->address.sin_family, (fullsocket->protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, fullsocket->protocol, NULL, 0, 0);
		if(!(status = (fullsocket->socket != INVALID_SOCKET)))
			kull_m_sock_error_auto(L"WSASocket");
	}
	//else kull_m_sock_error_auto(L"WSAStringToAddress");
	return status;
}

//BOOL kull_m_sock_init_socket_from_socket(PSOCKADDR_IN oSocket, IPPROTO protocol, PKULL_M_SOCK fullsocket)
//{
//	BOOL status = FALSE;
//	fullsocket->protocol = protocol;
//	fullsocket->address = *oSocket;
//	fullsocket->socket = WSASocket(fullsocket->address.sin_family, (fullsocket->protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, fullsocket->protocol, NULL, 0, 0);
//	if(!(status = (fullsocket->socket != INVALID_SOCKET)))
//		kull_m_sock_error_auto(L"WSASocket");
//	return status;
//}

//BOOL kull_m_sock_init_socket_from_socket_port(PKULL_M_SOCK sourceSocket, USHORT port, PKULL_M_SOCK fullsocket)
//{
//	BOOL status = FALSE;
//	fullsocket->protocol = sourceSocket->protocol;
//	fullsocket->address = sourceSocket->address;
//	fullsocket->address.sin_port = htons(port);
//	fullsocket->socket = WSASocket(fullsocket->address.sin_family, (fullsocket->protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, fullsocket->protocol, NULL, 0, 0);
//	if(!(status = (fullsocket->socket != INVALID_SOCKET)))
//		kull_m_sock_error_auto(L"WSASocket");
//	return status;
//}

//BOOL kull_m_sock_initSocket2(PCWSTR Server, PCWSTR Service, WORD Port, IPPROTO Protocol, PKULL_M_SOCK fullsocket)
//{
//	BOOL status = FALSE;
//	if(kull_m_sock_init_addr_protocol(Server, Service, Port, Protocol, fullsocket))
//	{
//		fullsocket->socket = WSASocket(fullsocket->address.sin_family, (fullsocket->protocol == IPPROTO_TCP) ? SOCK_STREAM : SOCK_DGRAM, fullsocket->protocol, NULL, 0, 0);
//		if(status = (fullsocket->socket != INVALID_SOCKET))
//		{
//			if(fullsocket->protocol == IPPROTO_TCP)
//				if(!(status = (WSAConnect(fullsocket->socket, (SOCKADDR *) &fullsocket->address, sizeof(SOCKADDR_IN), NULL, NULL, NULL, NULL) == ERROR_SUCCESS)))
//					kull_m_sock_error_auto(L"WSAConnect");
//		}
//		else kull_m_sock_error_auto(L"WSASocket");
//	}
//	return status;
//}

BOOL kull_m_sock_connect(PKULL_M_SOCK fullsocket)
{
	BOOL status = FALSE;
	if(fullsocket->protocol == IPPROTO_TCP)
	{
		if(!(status = (WSAConnect(fullsocket->socket, (SOCKADDR *) &fullsocket->address, sizeof(SOCKADDR_IN), NULL, NULL, NULL, NULL) == ERROR_SUCCESS)))
			kull_m_sock_error_auto(L"WSAConnect");
	}
	else if(fullsocket->protocol == IPPROTO_UDP)
		status = TRUE;
	return status;
}