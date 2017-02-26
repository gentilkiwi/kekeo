/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include <windns.h>

#define KULL_M_SOCK_DEFAULT_BUFLEN (64*1024)

typedef struct _KULL_M_SOCK {
	IPPROTO protocol;
	SOCKADDR_IN address;
	SOCKET socket;
	PWSTR servername;
} KULL_M_SOCK, *PKULL_M_SOCK;

WSADATA kull_m_sock_wsData;

BOOL kull_m_sock_startup();
BOOL kull_m_sock_finish();
void kull_m_sock_error_auto(PCWSTR source);
void kull_m_sock_error(int error, PCWSTR source);
BOOL kull_m_sock_SendAndRecv(PKULL_M_SOCK fullsocket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize);

//BOOL kull_m_sock_initSocket(PCWSTR Server, WORD Port, IPPROTO protocol, PKULL_M_SOCK fullsocket);
BOOL kull_m_sock_termSocket(PKULL_M_SOCK fullsocket);

BOOL kull_m_sock_init_addr_protocol(PCWSTR Server, PCWSTR Service, WORD Port, IPPROTO Protocol, PKULL_M_SOCK fullsocket);
void kull_m_sock_descr(PKULL_M_SOCK fullsocket);
BOOL kull_m_sock_init_addr_string(PCWSTR String, WORD Port, IPPROTO Protocol, PKULL_M_SOCK fullsocket);
BOOL kull_m_sock_init_socket_from_socket(PSOCKADDR_IN oSocket, IPPROTO protocol, PKULL_M_SOCK fullsocket);
BOOL kull_m_sock_init_socket_from_socket_port(PKULL_M_SOCK sourceSocket, USHORT port, PKULL_M_SOCK fullsocket);
BOOL kull_m_sock_initSocket2(PCWSTR Server, PCWSTR Service, WORD Port, IPPROTO Protocol, PKULL_M_SOCK fullsocket);
BOOL kull_m_sock_connect(PKULL_M_SOCK fullsocket);