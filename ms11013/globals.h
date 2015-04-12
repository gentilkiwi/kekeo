/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "superglobals.h"

#define MIMIKATZ				"MS11-013 POC"
#define MIMIKATZ_VERSION		"1.0"
#define TICKET_FILENAME			"tgs.kirbi"

#define USER_NORMAL_ACCOUNT			0x00000010
#define USER_DONT_EXPIRE_PASSWORD	0x00000200

#define DEFAULT_GROUP_ATTRIBUTES	(SE_GROUP_MANDATORY | SE_GROUP_ENABLED_BY_DEFAULT | SE_GROUP_ENABLED)
#define KIWI_NEVERTIME(filetime)	(*(PLONGLONG) filetime = MAXLONGLONG)