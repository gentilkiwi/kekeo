/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "kuhl_m.h"
#include <winhttp.h>
#include "../../modules/kull_m_string.h"
#include "../../modules/kull_m_file.h"
#include "../../modules/kull_m_crypto_system.h"
#include "../../modules/kull_m_ntlm.h"

const KUHL_M kuhl_m_ntlm;

NTSTATUS kuhl_m_ntlm_netntlm(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_ntlm_http(int argc, wchar_t * argv[]);

typedef struct _KIWI_HTTP {
	HINTERNET hSession;
	HINTERNET hConnect;
	HINTERNET hRequest;
} KIWI_HTTP, *PKIWI_HTTP;

BOOL kuhl_m_ntlm_netntlm_buildChallenge(SecBuffer *buffer, const wchar_t *FileName, const UCHAR Challenge[8], KIWI_NTLM_VERSION *Version, const wchar_t *TargetName, const wchar_t *DomainName, const wchar_t *ComputerName, const FILETIME *timeStamp, ULONG AdditionnalFlags);
void kuhl_m_ntlm_netntlm_buildAvPairs(PUCHAR *buffer, USHORT *size, ...);

PKIWI_HTTP kuhl_m_ntlm_http_giveHTTP(LPCWSTR url, LPCWSTR verb);
void kuhl_m_ntlm_http_closeHTTP(PKIWI_HTTP kHttp, BOOL freeIt);
BOOL kuhl_m_ntlm_http_getHeaders(PKIWI_HTTP pHttp, DWORD dwInfoLevel, PDWORD pdwIndex, PBYTE *data, DWORD *len);
BOOL kuhl_m_ntlm_http_sendReceiveHTTP(PKIWI_HTTP pHttp, PCWCHAR headers, PBYTE *data, DWORD *len, WORD *httpStatus);
PWCHAR kuhl_m_ntlm_http_encodeAuthNTLMB64(LPCWCHAR Scheme, BOOL isProxy, PSecBufferDesc pBuf);
BOOL kuhl_m_ntlm_http_decodeB64NTLMAuth(LPCWCHAR Scheme, PCWCHAR b64, PSecBufferDesc pBuf);