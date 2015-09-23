/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include "../kirbikator.h"

#define WCE_KERBEROS_TICKET_HEADER 0x8a8a8a8a

#pragma pack(push, 4)
typedef struct _WCE_KERBEROS_TICKET {
	DWORD header;
	DWORD sessionKeySize;
	DWORD encodedTicketSize;
	BYTE data[ANYSIZE_ARRAY];
} WCE_KERBEROS_TICKET, *PWCE_KERBEROS_TICKET;
#pragma pack(pop)

typedef struct _WCE_BUFF_TICKET {
	OssBuf SessionKey;
	OssBuf Ticket;
} WCE_BUFF_TICKET, *PWCE_BUFF_TICKET;

BOOL kiwi_wce_valid_header(OssBuf *input);
BOOL kiwi_wce_read(OssBuf *input, KRB_CRED **cred);
BOOL kiwi_wce_write(KRB_CRED *cred, OssBuf *output);