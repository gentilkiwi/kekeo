/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "kuhl_m.h"
#include "../../modules/asn1/kull_m_kerberos_asn1.h"
#include "../../modules/kull_m_file.h"
#include "kerberos/kuhl_m_kerberos_pac.h"
#include "kerberos/kuhl_m_kerberos.h"

const KUHL_M kuhl_m_tgs;

NTSTATUS kuhl_m_tgs_ask(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_tgs_s4u(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_tgs_renew(int argc, wchar_t * argv[]);