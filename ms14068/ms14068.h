/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#pragma once
#include "globals.h"
#include "../modules/kull_m_kerberos_helper.h"
#include "../modules/kull_m_sock.h"
#include "kuhl_m_kerberos_pac.h"

BOOL init();
BOOL term();

int main(int argc, char * argv[]);
void makeInception(PCSTR user, PCSTR domain, PSID sid, DWORD rid, EncryptionKey *key, PCSTR kdc, WORD port, PCSTR filename, PDS_DOMAIN_CONTROLLER_INFO_1 infos, DWORD nbInfos);
void impersonateToGetData(PCSTR user, PCSTR domain, PCSTR password, PCSTR kdc, PCSTR whatDC, PSID *sid, DWORD *rid, DWORD *pNbDc, PDS_DOMAIN_CONTROLLER_INFO_1 *dcInfos, PCSTR usingWhat);
BOOL giveMePac(PCSTR Username, PSID DomainSid, DWORD UserId, KerberosTime *AuthTime, DWORD SignatureType, EncryptionKey * SignatureKey, _octet1 *pac);