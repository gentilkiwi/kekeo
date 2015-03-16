/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include <WinDNS.h>

BOOL kull_m_sock_startup();
BOOL kull_m_sock_finish();
void kull_m_sock_error_auto(PCSTR source);
void kull_m_sock_error(int error, PCSTR source);
BOOL kull_m_sock_SendAndRecv(SOCKET *Socket, LPCVOID dataIn, DWORD dataInSize, LPVOID *dataOut, DWORD *dataOutSize);

BOOL kull_m_sock_initSocket(PCSTR kdc, WORD Port, SOCKET *Socket);
BOOL kull_m_sock_termSocket(SOCKET *Socket);