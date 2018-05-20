/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "kuhl_m.h"
#include "../../modules/kull_m_pipe.h"
#include "../../modules/asn1/kull_m_kerberos_asn1.h"

const KUHL_M kuhl_m_tsssp;

NTSTATUS kuhl_m_tsssp_server(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_tsssp_client(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_tsssp_list(int argc, wchar_t * argv[]);

void kuhl_m_tsssp_list_data(HKEY hPd);

BOOL kuhl_m_tsssp_send_recv(HANDLE hPipe, PSecBuffer toSend, PSecBuffer toRecv);
void kuhl_m_tsssp_freeBuffer(PSecBuffer buffer, BOOL isContext);
void kuhl_m_tsssp_printOctet1String(_octet1 *data);

SECURITY_STATUS kuhl_m_tsssp_AcquireCredentialsHandle(__in_opt LPWSTR pszPrincipal, __out PCredHandle phCredential);
SECURITY_STATUS kuhl_m_tsssp_AcceptSecurityContext(__in_opt PCredHandle phCredential, __in_opt PCtxtHandle phContext, __in_opt PSecBufferDesc pInput, __in_opt PCtxtHandle phNewContext, __in_opt PSecBufferDesc pOutput);
void kuhl_m_tsssp_TSCredentials(PSecBuffer data);

BOOL kuhl_m_tsssp_Encrypt(PCtxtHandle phContext, PSecBuffer data, _octet1 *out);
BOOL kuhl_m_tsssp_Decrypt(PCtxtHandle phContext, _octet1 *data, PSecBuffer out);
BOOL kuhl_m_tsssp_SHA256(BOOL isClient, _octet1 *Nonce, _octet1 *PublicKey, PSecBuffer out);

#define CLIENT_FLAGS	ISC_REQ_ALLOCATE_MEMORY | ISC_REQ_CONFIDENTIALITY | ISC_REQ_DELEGATE | ISC_REQ_EXTENDED_ERROR | ISC_REQ_REPLAY_DETECT | ISC_REQ_SEQUENCE_DETECT | ISC_REQ_STREAM

#define TSSSP_HC_CERTIFICATE_PUBLICKEY_OFFSET	158
#define TSSSP_HC_CERTIFICATE_PUBLICKEY_LENGTH	270
const BYTE TSSSP_HC_CERTIFICATE[742];