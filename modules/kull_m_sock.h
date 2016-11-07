/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include <WinDNS.h>

typedef struct _KULL_M_SOCK {
	int protocol;
	SOCKADDR_IN address;
	SOCKET socket;
} KULL_M_SOCK, *PKULL_M_SOCK;

BOOL kull_m_sock_startup();
BOOL kull_m_sock_finish();
void kull_m_sock_error_auto(PCSTR source);
void kull_m_sock_error(int error, PCSTR source);
BOOL kull_m_sock_SendAndRecv(PKULL_M_SOCK fullsocket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize);

BOOL kull_m_sock_initSocket(PCSTR kdc, WORD Port, int protocol, PKULL_M_SOCK fullsocket);
BOOL kull_m_sock_termSocket(PKULL_M_SOCK fullsocket);

BOOL kull_m_sock_kerberos_SendAndRecv(PKULL_M_SOCK fullsocket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize);