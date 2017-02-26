/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"
#include "kull_m_kerberos_asn1.h"
#include "kull_m_kerberos_asn1_crypto.h"
#include "../kull_m_string.h"

PKIWI_AUTH_INFOS kull_m_kerberos_asn1_Authinfos_create(int argc, wchar_t * argv[]);
void kull_m_kerberos_asn1_Authinfos_delete(PKIWI_AUTH_INFOS infos);
void kull_m_kerberos_asn1_Authinfos_descr(PKIWI_AUTH_INFOS infos);
USHORT kull_m_kerberos_asn1_Authinfos_changepw(_octet1 *data, int argc, wchar_t * argv[], Realm domain);