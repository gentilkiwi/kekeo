/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "superglobals.h"

BOOL kull_m_file_writeData(PCSTR fileName, LPCVOID data, DWORD lenght);
BOOL kull_m_file_readData(PCSTR fileName, PBYTE * data, PDWORD lenght);