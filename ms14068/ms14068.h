/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#pragma once
#include "globals.h"
#include "../modules/kull_m_kerberos_helper.h"
#include "../modules/kull_m_sock.h"
#include "../modules/kuhl_m_kerberos_pac.h"

BOOL init();
BOOL term();

int main(int argc, char * argv[]);
void makeInception(PCSTR user, PCSTR domain, PSID sid, DWORD rid, EncryptionKey *key, PGROUP_MEMBERSHIP groups, DWORD cbGroups, PKERB_SID_AND_ATTRIBUTES sids, DWORD cbSids, PCSTR kdc, WORD port, PCSTR filename, PDS_DOMAIN_CONTROLLER_INFO_1 infos, DWORD nbInfos);
void impersonateToGetData(PCSTR user, PCSTR domain, PCSTR password, PCSTR kdc, PCSTR whatDC, PSID *sid, DWORD *rid, DWORD *pNbDc, PDS_DOMAIN_CONTROLLER_INFO_1 *dcInfos, PCSTR usingWhat);