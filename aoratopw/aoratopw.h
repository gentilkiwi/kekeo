/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include "../modules/kull_m_kerberos_helper.h"
#include "../modules/kull_m_sock.h"

BOOL init();
BOOL term();

int main(int argc, char * argv[]);
void makeInception(PCSTR user, PCSTR domain, PCSTR newpassword, EncryptionKey *key, PCSTR kdc, WORD port, WORD kadminPort);

PCSTR kull_m_kadmin_passwd_err_to_string(DWORD id);
void retFromKadmin(_octet1 * data);

typedef struct _KULL_M_KADMIN_PASSWD_ERR{
	DWORD	id;
	PCSTR	name;
} KULL_M_KADMIN_PASSWD_ERR, *PKULL_M_KADMIN_PASSWD_ERR;