/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "kuhl_m.h"
#include "../../modules/kull_m_string.h"
#include "../../modules/kull_m_sock.h"

const KUHL_M kuhl_m_smb;

NTSTATUS kuhl_m_smb_time(int argc, wchar_t * argv[]);

#define SMB_MAGIC	'BMS\xff'

#define SMB_COM_NEGOTIATE	0x72

#define SMB_FLAGS_CASE_INSENSITIVE		0x08
#define SMB_FLAGS_CANONICALIZED_PATHS	0x10

#define SMB_FLAGS2_LONG_NAMES					0x0001
#define SMB_FLAGS2_EAS							0x0002

#define SMB_FLAGS2_SECURITY_SIGNATURE_REQUIRED	0x0010	
#define SMB_FLAGS2_IS_LONG_NAME					0x0040

#define SMB_FLAGS2_ESS							0x0800

#define SMB_FLAGS2_NT_STATUS					0x4000
#define SMB_FLAGS2_UNICODE						0x8000

#define SMB_DB_FORMAT_DIALECT 0x02

#define SMBv2_MAGIC	'BMS\xfe'

#define SMB2_NEGOTIATE		0x0000

#pragma pack(push, 1)
typedef struct _NB_SESSION_SERVICE {
	UCHAR Zero;
	UCHAR StreamProtocolLength[3];
	// message;
} NB_SESSION_SERVICE, *PNB_SESSION_SERVICE;

typedef struct _SMBSTATUS {
	UCHAR  ErrorClass;
	UCHAR  Reserved;
	USHORT ErrorCode;
} SMBSTATUS, *PSMBSTATUS;

typedef union _SMB_ERROR {
	 NTSTATUS ntStatus;
	 SMBSTATUS smbStatus;
} SMB_ERROR, *PSMB_ERROR;

typedef struct _SMB_Header {
	UCHAR  Protocol[4];
	UCHAR  Command;
	SMB_ERROR Status;
	UCHAR  Flags;
	USHORT Flags2;
	USHORT PIDHigh;
	UCHAR  SecurityFeatures[8];
	USHORT Reserved;
	USHORT TID;
	USHORT PIDLow;
	USHORT UID;
	USHORT MID;
} SMB_Header, *PSMB_Header;

typedef struct _SMB2_Header {
	UCHAR  ProtocolId[4];
	USHORT StructureSize;
	USHORT CreditCharge;
	NTSTATUS Status; // to do SMB3
	USHORT Command;
	USHORT CreditRequest_Response;
	ULONG Flags;
	ULONG NextCommand;
	ULONGLONG MessageId;
	ULONG Reserved;
	ULONG TreeId;
	ULONGLONG SessionId;
	BYTE Signature[16];
} SMB2_Header, *PSMB2_Header;

typedef struct _SMB_Dialect {
	UCHAR BufferFormat;
	//CHAR *DialectString;
} SMB_Dialect, *PSMB_Dialect;

typedef struct _SMB_Negotiate_Response{
	USHORT DialectIndex;
	UCHAR SecurityMode;
	USHORT MaxMpxCount;
	USHORT MaxNumberVcs;
	ULONG MaxBufferSize;
	ULONG MaxRawSize;
	ULONG SessionKey;
	ULONG Capabilities;
	FILETIME SystemTime;
	SHORT ServerTimeZone;
	UCHAR ChallengeLength;
} SMB_Negotiate_Response, *PSMB_Negotiate_Response;

typedef struct _SMB2_Negotiate_Response{
	USHORT StructureSize;
	USHORT SecurityMode;
	USHORT DialectRevision;
	USHORT Reserved;
	GUID ServerGuid;
	ULONG Capabilities;
	ULONG MaxTransactSize;
	ULONG MaxReadSize;
	ULONG MaxWriteSize;
	FILETIME SystemTime;
	FILETIME ServerStartTime;
	USHORT SecurityBufferOffset;
	USHORT SecurityBufferLength;
	ULONG Reserved2;
	// Buffer
} SMB2_Negotiate_Response, *PSMB2_Negotiate_Response;

typedef struct _SMB_Parameters {
	UCHAR WordCount;
	//USHORT Words[WordCount] (variable);
} SMB_Parameters, *PSMB_Parameters;

typedef struct _SMB_Data {
	USHORT ByteCount;
	//UCHAR Bytes[ByteCount] (variable);
} SMB_Data, *PSMB_Data;
#pragma pack(pop)

PSMB_Header kuhl_m_smb_SMB_Header_FromCommand(UCHAR command);
BOOL kuhl_m_smb_SMB_SimpleMessage_From_Parameters_Data(LPVOID parameters, UCHAR cbParameters, LPVOID data, USHORT cbData, LPBYTE *simpleMessage, DWORD *cbSimpleMessage);
BOOL kuhl_m_smb_SMB_Parameters_Data_FromSimpleMessage(LPVOID simpleMessage, LPBYTE *parameters, UCHAR *cbParameters, LPBYTE *data, USHORT *cbData);
BOOL kuhl_m_smb_SMB_Dialect_From_List(const PCHAR dialects[], USHORT count, PBYTE *simpleMessage, DWORD *cbSimpleMessage);
BOOL kuhl_m_smb_NB_SessionService(PSMB_Header header, LPCVOID smbRequest, DWORD cbSmbRequest, LPBYTE *sessionService, DWORD *cbSessionService);