/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "kuhl_m.h"
#include <winhttp.h>
#include "../../modules/kull_m_string.h"
#include "../../modules/kull_m_file.h"
#include "../../modules/kull_m_crypto_system.h"

const KUHL_M kuhl_m_ntlm;

NTSTATUS kuhl_m_ntlm_netntlm(int argc, wchar_t * argv[]);
NTSTATUS kuhl_m_ntlm_http(int argc, wchar_t * argv[]);

#define NTLMSSP_NEGOTIATE_56					0x80000000
#define NTLMSSP_NEGOTIATE_KEY_EXCH				0x40000000
#define NTLMSSP_NEGOTIATE_128					0x20000000
#define NTLMSSP_RESERVED_1						0x10000000
#define NTLMSSP_RESERVED_2						0x08000000
#define NTLMSSP_RESERVED_3						0x04000000
#define NTLMSSP_NEGOTIATE_VERSION				0x02000000
#define NTLMSSP_RESERVED_4						0x01000000
#define NTLMSSP_NEGOTIATE_TARGET_INFO			0x00800000
#define NTLMSSP_REQUEST_NON_NT_SESSION_KEY		0x00400000
#define NTLMSSP_RESERVED_5						0x00200000
#define NTLMSSP_NEGOTIATE_IDENTIFY				0x00100000
#define NTLMSSP_NEGOTIATE_EXTENDED_SESSIONSECURITY	0x00080000
#define NTLMSSP_TARGET_TYPE_SHARE				0x00040000	// RESERVED_6
#define NTLMSSP_TARGET_TYPE_SERVER				0x00020000
#define NTLMSSP_TARGET_TYPE_DOMAIN				0x00010000
#define NTLMSSP_NEGOTIATE_ALWAYS_SIGN			0x00008000
#define NTLMSSP_NEGOTIATE_LOCAL_CALL			0x00004000	// RESERVED_7
#define NTLMSSP_NEGOTIATE_OEM_WORKSTATION_SUPPLIED	0x00002000
#define NTLMSSP_NEGOTIATE_OEM_DOMAIN_SUPPLIED	0x00001000
#define NTLMSSP_NEGOTIATE_ANONYMOUS				0x00000800
#define NTLMSSP_RESERVED_8						0x00000400
#define NTLMSSP_NEGOTIATE_NTLM					0x00000200
#define NTLMSSP_RESERVED_9						0x00000100
#define NTLMSSP_NEGOTIATE_LM_KEY				0x00000080
#define NTLMSSP_NEGOTIATE_DATAGRAM				0x00000040
#define NTLMSSP_NEGOTIATE_SEAL					0x00000020
#define NTLMSSP_NEGOTIATE_SIGN					0x00000010
#define NTLMSSP_RESERVED_10						0x00000008
#define NTLMSSP_REQUEST_TARGET					0x00000004
#define NTLMSSP_NEGOTIATE_OEM					0x00000002
#define NTLMSSP_NEGOTIATE_UNICODE				0x00000001

#define NTLMSSP_Signature						"NTLMSSP"
#define NTLMSSP_Signature_ULL					0x005053534d4c544e
#define NTLMSSP_TypeOneMessage					0x00000001
#define NTLMSSP_TypeTwoMessage					0x00000002
#define NTLMSSP_TypeThreeMessage				0x00000003
#pragma pack(push, 1)

#ifndef MSV1_0_AV_FLAG_UNVERIFIED_TARGET
#define MSV1_0_AV_FLAG_UNVERIFIED_TARGET	0x00000004
#endif

typedef struct _KIWI_NTLM_Single_Host_Data {
	ULONG Size;
	ULONG Z4;
	UCHAR CustomData[8];
	UCHAR MachineID[32];
	UCHAR AdditionnalData[ANYSIZE_ARRAY];
} KIWI_NTLM_Single_Host_Data, *PKIWI_NTLM_Single_Host_Data;

typedef struct _KIWI_NTLM_AV_PAIR {
	USHORT AvId;
	USHORT AvLen;
	UCHAR Value[ANYSIZE_ARRAY];
} KIWI_NTLM_AV_PAIR, *PKIWI_NTLM_AV_PAIR;

typedef struct _KIWI_NTLM_VERSION {
	UCHAR ProductMajorVersion;
	UCHAR ProductMinorVersion;
	USHORT ProductBuild;
	UCHAR Reserved[3];
	UCHAR NTLMRevisionCurrent;
} KIWI_NTLM_VERSION, *PKIWI_NTLM_VERSION;

typedef struct _KIWI_NTLM_BUFFER {
	USHORT Len;
	USHORT MaxLen;
	ULONG Offset;
} KIWI_NTLM_BUFFER, *PKIWI_NTLM_BUFFER;

typedef struct _KIWI_NTLM_LM_RESPONSE {
	UCHAR Response[24];
} KIWI_NTLM_LM_RESPONSE, *PKIWI_NTLM_LM_RESPONSE;

typedef struct _KIWI_NTLM_NTLM_RESPONSE {
	UCHAR Response[24];
} KIWI_NTLM_NTLM_RESPONSE, *PKIWI_NTLM_NTLM_RESPONSE;

typedef struct _KIWI_NTLM_LMv2_RESPONSE {
	UCHAR Response[16];
	UCHAR ChallengeFromClient[8];
} KIWI_NTLM_LMv2_RESPONSE, *PKIWI_NTLM_LMv2_RESPONSE;

typedef struct _KIWI_NTLM_NTLMv2_CLIENT_CHALLENGE {
	UCHAR RespType;
	UCHAR HiRespType;
	USHORT Reserved1;
	ULONG Reserved2;
	FILETIME TimeStamp;
	UCHAR ChallengeFromClient[8];
	ULONG Reserved3;
	// AvPairs;
} KIWI_NTLM_NTLMv2_CLIENT_CHALLENGE, *PKIWI_NTLM_NTLMv2_CLIENT_CHALLENGE;

typedef struct _KIWI_NTLM_NTLMv2_RESPONSE {
	UCHAR Response[16];
	KIWI_NTLM_NTLMv2_CLIENT_CHALLENGE ClientChallenge;
} KIWI_NTLM_NTLMv2_RESPONSE, *PKIWI_NTLM_NTLMv2_RESPONSE;

typedef struct _KIWI_NTLM_NEGOTIATE_MESSAGE {
	ULONGLONG Signature;
	ULONG MessageType;
	ULONG NegotiateFlags;
	KIWI_NTLM_BUFFER DomainNameFields;
	KIWI_NTLM_BUFFER WorkstationFields;
	KIWI_NTLM_VERSION Version;
	UCHAR Payload[ANYSIZE_ARRAY];
} KIWI_NTLM_NEGOTIATE_MESSAGE, *PKIWI_NTLM_NEGOTIATE_MESSAGE;

typedef struct _KIWI_NTLM_CHALLENGE_MESSAGE {
	ULONGLONG Signature;
	ULONG MessageType;
	KIWI_NTLM_BUFFER TargetNameFields;
	ULONG NegotiateFlags;
	UCHAR Challenge[8];
	CHAR Reserved[8];
	KIWI_NTLM_BUFFER TargetInfoFields;
	KIWI_NTLM_VERSION Version;
	UCHAR Payload[ANYSIZE_ARRAY];
} KIWI_NTLM_CHALLENGE_MESSAGE, *PKIWI_NTLM_CHALLENGE_MESSAGE;

typedef struct _KIWI_NTLM_AUTHENTICATE_MESSAGE {
	ULONGLONG Signature;
	ULONG MessageType;
	KIWI_NTLM_BUFFER LmChallengeResponseFields;
	KIWI_NTLM_BUFFER NtChallengeResponseFields;
	KIWI_NTLM_BUFFER DomainNameFields;
	KIWI_NTLM_BUFFER UserNameFields;
	KIWI_NTLM_BUFFER WorkstationFields;
	KIWI_NTLM_BUFFER EncryptedRandomSessionKeyFields;
	ULONG NegotiateFlags;
	KIWI_NTLM_VERSION Version;
	UCHAR MIC[16];
	UCHAR Payload[ANYSIZE_ARRAY];
} KIWI_NTLM_AUTHENTICATE_MESSAGE, *PKIWI_NTLM_AUTHENTICATE_MESSAGE;
#pragma pack(pop)

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

void kuhl_m_ntlm_descrGeneric(PSecBufferDesc buff, ULONG WantedMessageType);
void kuhl_m_ntlm_descrNegotiateFlags(ULONG flags);
void kuhl_m_ntlm_descrAvPairs(PKIWI_NTLM_AV_PAIR pPair, USHORT len);
void kuhl_m_ntlm_descrAuthenticate(PKIWI_NTLM_AUTHENTICATE_MESSAGE pAuth);
void kuhl_m_ntlm_descrChallenge(PKIWI_NTLM_CHALLENGE_MESSAGE pChal);
void kuhl_m_ntlm_descrNegotiate(PKIWI_NTLM_NEGOTIATE_MESSAGE pNeg);