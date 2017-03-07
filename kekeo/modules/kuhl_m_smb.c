/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_smb.h"

const KUHL_M_C kuhl_m_c_smb[] = {
	{kuhl_m_smb_time,		L"time",	L"Get time from remote SMB server"},
};
const KUHL_M kuhl_m_smb = {
	L"smb",	L"Tiny SMB module",	NULL,
	ARRAYSIZE(kuhl_m_c_smb), kuhl_m_c_smb, NULL, NULL
};

const PCHAR dialects[] = {/*"PC NETWORK PROGRAM 1.0", "LANMAN1.0", "Windows for Workgroups 3.1a", "LM1.2X002", "LANMAN2.1", */"NT LM 0.12", "SMB 2.002"/*, "SMB 2.???"*/};
NTSTATUS kuhl_m_smb_time(int argc, wchar_t * argv[])
{
	KULL_M_SOCK sock;
	PSMB_Header header;
	PBYTE smbData, nbSessionService;
	DWORD cbSmbData, cbSessionService;
	PVOID out;
	DWORD cbOut;

	PSMB_Header smbHeader;
	PSMB_Negotiate_Response smbnegResp;
	UCHAR cbSmbNegResp;
	PSMB2_Header smb2Header;
	PSMB2_Negotiate_Response smb2negResp;

	PCWCHAR server = argc ? argv[0] : L"localhost";

	kprintf(L"Server  : %s\n", server);
	if(kull_m_sock_init_addr_protocol(server, NULL, 445, IPPROTO_TCP, &sock))
	{
		if(kull_m_sock_connect(&sock))
		{
			if(header = kuhl_m_smb_SMB_Header_FromCommand(SMB_COM_NEGOTIATE))
			{
				if(kuhl_m_smb_SMB_Dialect_From_List(dialects, ARRAYSIZE(dialects), &smbData, &cbSmbData))
				{
					if(kuhl_m_smb_NB_SessionService(header, smbData, cbSmbData, &nbSessionService, &cbSessionService))
					{
						if(kull_m_sock_SendAndRecv(&sock, nbSessionService, cbSessionService, &out, &cbOut))
						{
							if(cbOut >= 2*sizeof(DWORD))
							{
								kprintf(L"Protocol: ");
								switch(((PDWORD) out)[1])
								{
								case SMB_MAGIC:
									kprintf(L"SMB\n");
									smbHeader = (PSMB_Header) ((PBYTE) out + sizeof(DWORD));
									if((smbHeader->Command == SMB_COM_NEGOTIATE) && (smbHeader->Status.ntStatus == STATUS_SUCCESS))
									{
										if(kuhl_m_smb_SMB_Parameters_Data_FromSimpleMessage((PBYTE) smbHeader + sizeof(SMB_Header), (LPBYTE *) &smbnegResp, &cbSmbNegResp, NULL, NULL))
										{
											if(smbnegResp->DialectIndex == 0/*5*/) // NT LM 0.12
											{
												kprintf(L" SystemTime     : ");
												kull_m_string_displayLocalFileTime(&smbnegResp->SystemTime);
												kprintf(L"\n");
											}
											else PRINT_ERROR(L"DialectIndex: %hu - %04x\n", smbnegResp->DialectIndex, smbnegResp->DialectIndex);
											LocalFree(smbnegResp);
										}
									}
									else PRINT_ERROR(L"Invalid! Command: %02x - Status: %08x\n", smbHeader->Command, smbHeader->Status.ntStatus);
									break;
								case SMBv2_MAGIC:
									kprintf(L"SMB2\n");
									smb2Header = (PSMB2_Header) ((PBYTE) out + sizeof(DWORD));
									if(smb2Header->Command == SMB2_NEGOTIATE && (smb2Header->Status == STATUS_SUCCESS))
									{
										smb2negResp = (PSMB2_Negotiate_Response) ((PBYTE) smb2Header + sizeof(SMB2_Header));
										kprintf(L" SystemTime     : ");
										kull_m_string_displayLocalFileTime(&smb2negResp->SystemTime);
										kprintf(L"\n ServerStartTime: ");
										kull_m_string_displayLocalFileTime(&smb2negResp->ServerStartTime);
										kprintf(L"\n");
									}
									else PRINT_ERROR(L"Invalid! Command: %02x - Status: %08x\n", smb2Header->Command, smb2Header->Status);
									break;
								default:
									PRINT_ERROR(L"Unknow version: %08x\n", ((PDWORD) out)[1]);
								}
							}
							else PRINT_ERROR(L"Invalid size: %u\n", cbOut);
							LocalFree(out);
						}
						LocalFree(nbSessionService);
					}
					LocalFree(smbData);
				}
				LocalFree(header);
			}
		}
		kull_m_sock_termSocket(&sock);
	}
	return STATUS_SUCCESS;
}

PSMB_Header kuhl_m_smb_SMB_Header_FromCommand(UCHAR command)
{
	PSMB_Header header = NULL;
	if(header = (PSMB_Header) LocalAlloc(LPTR, sizeof(SMB_Header)))
	{
		*(PDWORD) header->Protocol = SMB_MAGIC;
		header->Command = command;
		header->Status.ntStatus = STATUS_SUCCESS;
		header->Flags = SMB_FLAGS_CASE_INSENSITIVE | SMB_FLAGS_CANONICALIZED_PATHS;
		header->Flags2 = SMB_FLAGS2_LONG_NAMES | SMB_FLAGS2_EAS | SMB_FLAGS2_SECURITY_SIGNATURE_REQUIRED | SMB_FLAGS2_IS_LONG_NAME | SMB_FLAGS2_ESS | SMB_FLAGS2_NT_STATUS | SMB_FLAGS2_UNICODE;
		header->PIDHigh = 0;
		*(PULONGLONG) header->SecurityFeatures = 0;
		header->Reserved = 0;
		header->TID = 0xffff;
		header->PIDLow = 65279;
		header->UID = 0;
		header->MID = 0;
	}
	return header;
}

BOOL kuhl_m_smb_SMB_SimpleMessage_From_Parameters_Data(LPVOID parameters, UCHAR cbParameters, LPVOID data, USHORT cbData, LPBYTE *simpleMessage, DWORD *cbSimpleMessage)
{
	*simpleMessage = NULL;
	*cbSimpleMessage = 0;
	if(!(cbParameters % 2))
	{
		*cbSimpleMessage = sizeof(SMB_Parameters) + cbParameters + sizeof(SMB_Data) + cbData;
		if((*simpleMessage) = (PBYTE) LocalAlloc(LPTR, *cbSimpleMessage))
		{
			((PSMB_Parameters) (*simpleMessage))->WordCount = cbParameters / 2;
			if(cbParameters)
				RtlCopyMemory((*simpleMessage) + sizeof(SMB_Parameters), parameters, cbParameters);
			((PSMB_Data) ((*simpleMessage) + sizeof(SMB_Parameters) + cbParameters))->ByteCount = cbData;
			if(cbData)
				RtlCopyMemory(((*simpleMessage) + sizeof(SMB_Parameters) + cbParameters + sizeof(SMB_Data)), data, cbData);
		}
	}
	else PRINT_ERROR(L"Bad parameters size (must be multiple of 2)\n");
	return ((*simpleMessage) != NULL) ;
}

BOOL kuhl_m_smb_SMB_Parameters_Data_FromSimpleMessage(LPVOID simpleMessage, LPBYTE *parameters, UCHAR *cbParameters, LPBYTE *data, USHORT *cbData)
{
	BOOL status = FALSE, mustParam = parameters && cbParameters, mustData = data && cbData;
	UCHAR paramSize = 0;
	USHORT dataSize = 0;

	if(mustParam)
	{
		*parameters = NULL;
		*cbParameters = 0;
	}

	if(mustData)
	{
		*data = NULL;
		*cbData = 0;
	}

	// optimistic :)
	paramSize = (*(PUCHAR) simpleMessage) * sizeof(USHORT);
	dataSize = *(PUSHORT) ((PBYTE) simpleMessage + paramSize);
	if(paramSize && mustParam)
	{
		if((*parameters) = (PBYTE) LocalAlloc(LPTR, paramSize))
		{
			RtlCopyMemory(*parameters, (PBYTE) simpleMessage + sizeof(SMB_Parameters), paramSize);
			*cbParameters = paramSize;
		}
	}
	if(dataSize && mustData)
	{
		if((*data) = (PBYTE) LocalAlloc(LPTR, dataSize))
		{
			RtlCopyMemory(*parameters, (PBYTE) simpleMessage + sizeof(SMB_Parameters) + paramSize + sizeof(SMB_Data), dataSize);
			*cbData = dataSize;
		}
	}
	return (parameters || !mustParam || !paramSize) && (data || !mustData || !dataSize);
}


BOOL kuhl_m_smb_SMB_Dialect_From_List(const PCHAR dialects[], USHORT count, PBYTE *simpleMessage, DWORD *cbSimpleMessage)
{
	BOOL status = FALSE;
	DWORD i, l, tl = 0;
	PBYTE data, cur;
	for(i = 0; i < count; i++)
		tl += sizeof(SMB_Dialect) + lstrlenA(dialects[i]) + sizeof(char);

	if(data = (PBYTE) LocalAlloc(LPTR, tl))
	{
		for(i = 0, cur = data; i < count; i++, cur += sizeof(SMB_Dialect) + l)
		{
			l = lstrlenA(dialects[i]) + sizeof(char);
			((PSMB_Dialect) cur)->BufferFormat = SMB_DB_FORMAT_DIALECT;
			RtlCopyMemory(cur + sizeof(SMB_Dialect), dialects[i], l);
		}
		status = kuhl_m_smb_SMB_SimpleMessage_From_Parameters_Data(NULL, 0, data, (USHORT) tl, simpleMessage, cbSimpleMessage);
		LocalFree(data);
	}
	return status;
}

BOOL kuhl_m_smb_NB_SessionService(PSMB_Header header, LPCVOID smbRequest, DWORD cbSmbRequest, LPBYTE *sessionService, DWORD *cbSessionService)
{
	BOOL status = FALSE;
	DWORD t = sizeof(SMB_Header) + cbSmbRequest;
	*sessionService = NULL;
	*cbSessionService = 0;
	
	if(t <= 0x1ffff)
	{
		*cbSessionService = sizeof(NB_SESSION_SERVICE) + t;
		if((*sessionService) = (PBYTE) LocalAlloc(LPTR, *cbSessionService))
		{
			*(PDWORD) (*sessionService) = _byteswap_ulong(t); // 0 will be here ;)
			RtlCopyMemory((*sessionService) + sizeof(NB_SESSION_SERVICE), header, sizeof(SMB_Header));
			RtlCopyMemory((*sessionService) + sizeof(NB_SESSION_SERVICE) + sizeof(SMB_Header), smbRequest, cbSmbRequest);
			status = TRUE;
		}
	}
	else PRINT_ERROR(L"SMB message length is > 0x1ffff\n");
	return status;
}