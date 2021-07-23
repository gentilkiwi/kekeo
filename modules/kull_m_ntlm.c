/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kull_m_ntlm.h"

const PCWCHAR KIWI_NEGOTIATE_FLAGS[] = {
	L"UNICODE", L"OEM", L"ReqTARGET", L"RESERVED_10", L"SIGN", L"SEAL", L"DATAGRAM", L"LM_KEY",
	L"RESERVED_9", L"NTLM", L"RESERVED_8", L"ANONYMOUS", L"OEM_DOMAIN_SUPPLIED", L"OEM_WORKSTATION_SUPPLIED", L"LOCAL_CALL", L"ALWAYS_SIGN", 
	L"TARGET_TYPE_DOMAIN", L"TARGET_TYPE_SERVER", L"TARGET_TYPE_SHARE", L"EXTENDED_SESSIONSECURITY",  L"IDENTIFY", L"RESERVED_5", L"ReqNON_NT_SESSION_KEY", L"TARGET_INFO", 
	L"RESERVED_4", L"VERSION", L"RESERVED_3", L"RESERVED_2",  L"RESERVED_1", L"128", L"KEY_EXCH", L"56",
};
void kull_m_ntlm_descrNegotiateFlags(ULONG flags)
{
	BYTE i;
	kprintf(L"0x%08x ( ", flags);
	for(i = 0; i < sizeof(ULONG) * 8; i++)
		if((flags >> i) & 1)
			kprintf(L"%s ", KIWI_NEGOTIATE_FLAGS[i]);
	kprintf(L")\n");
}

const PCWCHAR KIWI_MSV1_0_AVIDS[] = {L"EOL", L"NbComputerName", L"NbDomainName", L"DnsComputerName", L"DnsDomainName", L"DnsTreeName", L"Flags", L"Timestamp", L"Restrictions", L"TargetName", L"ChannelBindings",};
const PCWCHAR KIWI_MSV1_0_AVFLAGS[] = {L"FORCE_GUEST", L"MIC_HANDSHAKE_MESSAGES", L"UNVERIFIED_TARGET"};
void kull_m_ntlm_descrAvPairs(PKIWI_NTLM_AV_PAIR pPair, USHORT len)
{
	ULONG i, flags;
	PKIWI_NTLM_Single_Host_Data pData;
	while(pPair->AvId)
	{
		kprintf(L"    [%04x] %-15s - ", pPair->AvId, (pPair->AvId < ARRAYSIZE(KIWI_MSV1_0_AVIDS)) ? KIWI_MSV1_0_AVIDS[pPair->AvId] : L"?");
		switch(pPair->AvId)
		{
			case MsvAvNbComputerName:
			case MsvAvNbDomainName:
			case MsvAvDnsComputerName:
			case MsvAvDnsDomainName:
			case MsvAvDnsTreeName:
			case MsvAvTargetName:
				kprintf(L"\'%.*s\'", pPair->AvLen / sizeof(wchar_t), pPair->Value);
				break;
			case MsvAvFlags:
				flags = *(PULONG) pPair->Value;
				kprintf(L"%08x - ", flags);
				for(i = 0; i < sizeof(flags) * 8; i++)
					if((flags >> i) & 1)
						kprintf(L"%s ; ", (i < ARRAYSIZE(KIWI_MSV1_0_AVFLAGS)) ? KIWI_MSV1_0_AVFLAGS[i] : L"?");
				break;
			case MsvAvTimestamp:
				kull_m_string_displayLocalFileTime((PFILETIME) pPair->Value);
				break;
			case MsvAvRestrictions:
				pData = (PKIWI_NTLM_Single_Host_Data) pPair->Value;
				kprintf(L"CustomData: ");
				kull_m_string_wprintf_hex(pData->CustomData, sizeof(pData->CustomData), 0);
				kprintf(L" ; MachineID: ");
				kull_m_string_wprintf_hex(pData->MachineID, sizeof(pData->MachineID), 0);
				if(pData->Size > (ULONG) FIELD_OFFSET(KIWI_NTLM_Single_Host_Data, AdditionnalData))
				{
					kprintf(L" ; ?: ");
					kull_m_string_wprintf_hex(pData->AdditionnalData, pData->Size - FIELD_OFFSET(KIWI_NTLM_Single_Host_Data, AdditionnalData), 0);
				}
				break;
			case MsvAvChannelBindings:
			default:
				kull_m_string_wprintf_hex(pPair->Value, pPair->AvLen, 0);
				break;
		}
		kprintf(L"\n");
		pPair = (PKIWI_NTLM_AV_PAIR) ((PUCHAR) pPair + FIELD_OFFSET(KIWI_NTLM_AV_PAIR, Value) + pPair->AvLen);
	}
}

void kull_m_ntlm_descrAuthenticate(PKIWI_NTLM_AUTHENTICATE_MESSAGE pAuth)
{
	PKIWI_NTLM_LMv2_RESPONSE pLMv2;
	PKIWI_NTLM_NTLMv2_RESPONSE pNTLMv2;
	PKIWI_NTLM_LM_RESPONSE pLMv1;
	PKIWI_NTLM_NTLM_RESPONSE pNTLMv1;

	kprintf(L"  NegotiateFlags: ");
	kull_m_ntlm_descrNegotiateFlags(pAuth->NegotiateFlags);
	kprintf(L"  DomainName    : ");
	if(pAuth->DomainNameFields.Len)
		kprintf(L"%.*s\n", pAuth->DomainNameFields.Len / sizeof(wchar_t), (PBYTE) pAuth + pAuth->DomainNameFields.Offset);
	else kprintf(L"<NULL>\n");
	kprintf(L"  UserName      : ");
	if(pAuth->UserNameFields.Len)
		kprintf(L"%.*s\n", pAuth->UserNameFields.Len / sizeof(wchar_t), (PBYTE) pAuth + pAuth->UserNameFields.Offset);
	else kprintf(L"<NULL>\n");
	kprintf(L"  Workstation   : ");
	if(pAuth->WorkstationFields.Len)
		kprintf(L"%.*s\n", pAuth->WorkstationFields.Len / sizeof(wchar_t), (PBYTE) pAuth + pAuth->WorkstationFields.Offset);
	else kprintf(L"<NULL>\n");
	if(pAuth->NegotiateFlags & NTLMSSP_NEGOTIATE_KEY_EXCH)
	{
		kprintf(L"  SessionKey    : ");
		if(pAuth->EncryptedRandomSessionKeyFields.Len)
			kull_m_string_wprintf_hex((PBYTE) pAuth + pAuth->EncryptedRandomSessionKeyFields.Offset, pAuth->EncryptedRandomSessionKeyFields.Len, 0);
		else kprintf(L"<NULL>");
		kprintf(L"\n");
	}
	if(pAuth->NegotiateFlags & NTLMSSP_NEGOTIATE_VERSION)
		kprintf(L"  Version       : %hhu.%hhu (%hu) - rev. %hhu\n", pAuth->Version.ProductMajorVersion, pAuth->Version.ProductMinorVersion, pAuth->Version.ProductBuild, pAuth->Version.NTLMRevisionCurrent);
	if((MIMIKATZ_NT_BUILD_NUMBER > 3790) || (pAuth->Version.ProductBuild > 3790))
	{
		kprintf(L"  MIC           : ");
		kull_m_string_wprintf_hex(pAuth->MIC, sizeof(pAuth->MIC), 0);
		kprintf(L"\n");
	}
	if(pAuth->NtChallengeResponseFields.Len >= sizeof(KIWI_NTLM_NTLMv2_RESPONSE))
	{
		if(pAuth->LmChallengeResponseFields.Len == sizeof(KIWI_NTLM_LMv2_RESPONSE))
		{
			pLMv2 = (PKIWI_NTLM_LMv2_RESPONSE) ((PBYTE) pAuth + pAuth->LmChallengeResponseFields.Offset);
			kprintf(L"  LMv2:\n    Response       : ");
			kull_m_string_wprintf_hex(pLMv2->Response, sizeof(pLMv2->Response), 0);
			kprintf(L"\n    ClientChallenge: ");
			kull_m_string_wprintf_hex(pLMv2->ChallengeFromClient, sizeof(pLMv2->ChallengeFromClient), 0);
			kprintf(L"\n");
		}
		pNTLMv2 = (PKIWI_NTLM_NTLMv2_RESPONSE) ((PBYTE) pAuth + pAuth->NtChallengeResponseFields.Offset);
		kprintf(L"  NTLMv2:\n    Response       : ");
		kull_m_string_wprintf_hex(pNTLMv2->Response, sizeof(pNTLMv2->Response), 0);
		kprintf(L"\n    ClientChallenge: ");
		kull_m_string_wprintf_hex(pNTLMv2->ClientChallenge.ChallengeFromClient, sizeof(pNTLMv2->ClientChallenge.ChallengeFromClient), 0);
		kprintf(L"\n    TimeStamp      : ");
		kull_m_string_displayLocalFileTime(&pNTLMv2->ClientChallenge.TimeStamp);
		kprintf(L"\n");
		if(pAuth->NtChallengeResponseFields.Len >= (sizeof(KIWI_NTLM_NTLMv2_RESPONSE) + FIELD_OFFSET(KIWI_NTLM_AV_PAIR, Value)))
			kull_m_ntlm_descrAvPairs((PKIWI_NTLM_AV_PAIR) ((PUCHAR) pNTLMv2 + sizeof(KIWI_NTLM_NTLMv2_RESPONSE)), pAuth->NtChallengeResponseFields.Len - sizeof(KIWI_NTLM_NTLMv2_RESPONSE));
	}
	else if(pAuth->NtChallengeResponseFields.Len == sizeof(KIWI_NTLM_NTLM_RESPONSE))
	{
		if(pAuth->LmChallengeResponseFields.Len == sizeof(KIWI_NTLM_LM_RESPONSE))
		{
			pLMv1 = (PKIWI_NTLM_LM_RESPONSE) ((PBYTE) pAuth + pAuth->LmChallengeResponseFields.Offset);
			kprintf(L"  LMv1:\n");
			if(pAuth->NegotiateFlags & NTLMSSP_NEGOTIATE_EXTENDED_SESSIONSECURITY)
			{
				kprintf(L"    NTLM2 ESS      : ");
				kull_m_string_wprintf_hex(pLMv1->Response, 8, 0);
			}
			else
			{			
				kprintf(L"    Response       : ");
				kull_m_string_wprintf_hex(pLMv1->Response, sizeof(pLMv1->Response), 0);
			}
			kprintf(L"\n");
		}
		pNTLMv1 = (PKIWI_NTLM_NTLM_RESPONSE) ((PBYTE) pAuth + pAuth->NtChallengeResponseFields.Offset);
		kprintf(L"  NTLMv1:\n    Response       : ");
		kull_m_string_wprintf_hex(pNTLMv1->Response, sizeof(pNTLMv1->Response), 0);
		kprintf(L"\n");
	}
	else PRINT_ERROR(L"NtChallengeResponseFields.Len = %hu\n", pAuth->NtChallengeResponseFields.Len);
}

const BYTE KIWI_NTLM_BLACK_CHALLENGES[][8] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88},
	{0x00, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00},
	{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
	{'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A'},
	{0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef},
};
void kull_m_ntlm_descrChallenge(PKIWI_NTLM_CHALLENGE_MESSAGE pChal)
{
	DWORD i;
	kprintf(L"  NegotiateFlags: ");
	kull_m_ntlm_descrNegotiateFlags(pChal->NegotiateFlags);
	kprintf(L"  Challenge     : "); kull_m_string_wprintf_hex(pChal->Challenge, sizeof(pChal->Challenge), 0); kprintf(L"\n");
	for(i = 0; i < ARRAYSIZE(KIWI_NTLM_BLACK_CHALLENGES); i++)
		if(RtlEqualMemory(KIWI_NTLM_BLACK_CHALLENGES[i], pChal->Challenge, 8))
		{
			kprintf(L"  ** BLACKLISTED CHALLENGE! **\n");
			break;
		}
	if(pChal->NegotiateFlags & NTLMSSP_REQUEST_TARGET)
		kprintf(L"  TargetName    : %.*s\n", pChal->TargetNameFields.Len / sizeof(wchar_t), (PUCHAR) pChal + pChal->TargetNameFields.Offset);
	if(pChal->NegotiateFlags & NTLMSSP_NEGOTIATE_TARGET_INFO)
	{
		kprintf(L"  TargetInfo    :\n");
		kull_m_ntlm_descrAvPairs((PKIWI_NTLM_AV_PAIR) ((PBYTE) pChal + pChal->TargetInfoFields.Offset), pChal->TargetInfoFields.Len);
	}
	if(pChal->NegotiateFlags & NTLMSSP_NEGOTIATE_VERSION)
		kprintf(L"  Version       : %hhu.%hhu (%hu) - rev. %hhu\n", pChal->Version.ProductMajorVersion, pChal->Version.ProductMinorVersion, pChal->Version.ProductBuild, pChal->Version.NTLMRevisionCurrent);
}

void kull_m_ntlm_descrNegotiate(PKIWI_NTLM_NEGOTIATE_MESSAGE pNeg)
{
	kprintf(L"  NegotiateFlags: ");
	kull_m_ntlm_descrNegotiateFlags(pNeg->NegotiateFlags);
	if(pNeg->NegotiateFlags & NTLMSSP_NEGOTIATE_OEM_DOMAIN_SUPPLIED)
	{
		kprintf(L"  DomainName    : ");
		if(pNeg->DomainNameFields.Len)
			kprintf(L"%.*S\n", pNeg->DomainNameFields.Len, (PBYTE) pNeg + pNeg->DomainNameFields.Offset);
		else kprintf(L"<NULL>\n");
	}
	if(pNeg->NegotiateFlags & NTLMSSP_NEGOTIATE_OEM_WORKSTATION_SUPPLIED)
	{
		kprintf(L"  Workstation   : ");
		if(pNeg->WorkstationFields.Len)
			kprintf(L"%.*S\n", pNeg->WorkstationFields.Len, (PBYTE) pNeg + pNeg->WorkstationFields.Offset);
		else kprintf(L"<NULL>\n");
	}
	if(pNeg->NegotiateFlags & NTLMSSP_NEGOTIATE_VERSION)
		kprintf(L"  Version       : %hhu.%hhu (%hu) - rev. %hhu\n", pNeg->Version.ProductMajorVersion, pNeg->Version.ProductMinorVersion, pNeg->Version.ProductBuild, pNeg->Version.NTLMRevisionCurrent);
}

void kull_m_ntlm_descrGeneric(PSecBufferDesc buff, ULONG WantedMessageType)
{
	ULONGLONG Signature;
	ULONG MessageType;
	if(buff)
	{
		if(buff->ulVersion == SECBUFFER_VERSION)
		{
			if(buff->cBuffers == 1)
			{
				if(buff->pBuffers)
				{
					if((buff->pBuffers[0].BufferType & ~SECBUFFER_ATTRMASK) == SECBUFFER_TOKEN)
					{
						if(buff->pBuffers[0].cbBuffer > (sizeof(ULONGLONG) + sizeof(ULONG)))
						{
							if(buff->pBuffers[0].pvBuffer)
							{
								Signature = *(PULONGLONG) buff->pBuffers[0].pvBuffer;
								MessageType = ((PULONG) buff->pBuffers[0].pvBuffer)[2];
								if(Signature == NTLMSSP_Signature_ULL)
								{
									if(!WantedMessageType || (WantedMessageType == MessageType))
									{
										switch(MessageType)
										{
										case NTLMSSP_TypeOneMessage:
											kull_m_ntlm_descrNegotiate((PKIWI_NTLM_NEGOTIATE_MESSAGE) buff->pBuffers[0].pvBuffer);
											break;
										case NTLMSSP_TypeTwoMessage:
											kull_m_ntlm_descrChallenge((PKIWI_NTLM_CHALLENGE_MESSAGE) buff->pBuffers[0].pvBuffer);
											break;
										case NTLMSSP_TypeThreeMessage:
											kull_m_ntlm_descrAuthenticate((PKIWI_NTLM_AUTHENTICATE_MESSAGE) buff->pBuffers[0].pvBuffer);
											break;
										default:
											PRINT_ERROR(L"Unknown MessageType: 0x%08x\n", MessageType);
										}
									}
									else PRINT_ERROR(L"Invalid MessageType: 0x%08x\n", MessageType);
								}
								else PRINT_ERROR(L"Invalid Signature: %016llx\n", _byteswap_uint64(Signature));
							}
							else PRINT_ERROR(L"SecBuffer - pvBuffer is NULL\n");
						}
						else PRINT_ERROR(L"SecBuffer - cbBuffer (%u)\n", buff->pBuffers[0].BufferType);
					}
					else PRINT_ERROR(L"SecBuffer - BufferType (0x%08x)\n", buff->pBuffers[0].BufferType);
				}
				else PRINT_ERROR(L"SecBufferDesc - pBuffers is NULL\n");
			}
			else PRINT_ERROR(L"SecBufferDesc - cbBuffers (%u)\n", buff->cBuffers);
		}
		else PRINT_ERROR(L"SecBufferDesc - ulVersion (%u)\n", buff->ulVersion);
	}
	else PRINT_ERROR(L"SecBufferDesc - No buffer\n");
}

///////////////////////////////////////////////////////////////////////////////////
typedef struct _GENERICKEY_BLOB {
	BLOBHEADER Header;
	DWORD dwKeyLen;
} GENERICKEY_BLOB, *PGENERICKEY_BLOB;

BOOL kull_m_crypto_hkey(HCRYPTPROV hProv, ALG_ID calgid, LPCVOID key, DWORD keyLen, DWORD flags, HCRYPTKEY *hKey, HCRYPTPROV *hSessionProv)
{
	BOOL status = FALSE;
	PGENERICKEY_BLOB keyBlob;
	DWORD szBlob = sizeof(GENERICKEY_BLOB) + keyLen;
	
	if(calgid != CALG_3DES)
	{
		if(keyBlob = (PGENERICKEY_BLOB) LocalAlloc(LPTR, szBlob))
		{
			keyBlob->Header.bType = PLAINTEXTKEYBLOB;
			keyBlob->Header.bVersion = CUR_BLOB_VERSION;
			keyBlob->Header.reserved = 0;
			keyBlob->Header.aiKeyAlg = calgid;
			keyBlob->dwKeyLen = keyLen;
			RtlCopyMemory((PBYTE) keyBlob + sizeof(GENERICKEY_BLOB), key, keyBlob->dwKeyLen);
			status = CryptImportKey(hProv, (LPCBYTE) keyBlob, szBlob, 0, flags, hKey);
			LocalFree(keyBlob);
		}
	}
	//else if(hSessionProv)
	//	status = kull_m_crypto_hkey_session(calgid, key, keyLen, flags, hKey, hSessionProv);
	
	return status;
}

BOOL kull_m_crypto_hmac(DWORD calgid, LPCVOID key, DWORD keyLen, LPCVOID message, DWORD messageLen, LPVOID hash, DWORD hashWanted) // for keyLen > 1
{
	BOOL status = FALSE;
	DWORD hashLen;
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	HCRYPTHASH hHash;
	HMAC_INFO HmacInfo = {calgid, NULL, 0, NULL, 0};
	PBYTE buffer;

	if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		if(kull_m_crypto_hkey(hProv, CALG_RC2, key, keyLen, CRYPT_IPSEC_HMAC_KEY, &hKey, NULL))
		{
			if(CryptCreateHash(hProv, CALG_HMAC, hKey, 0, &hHash))
			{
				if(CryptSetHashParam(hHash, HP_HMAC_INFO, (LPCBYTE) &HmacInfo, 0))
				{
					if(CryptHashData(hHash, (LPCBYTE) message, messageLen, 0))
					{
						if(CryptGetHashParam(hHash, HP_HASHVAL, NULL, &hashLen, 0))
						{
							if(buffer = (PBYTE) LocalAlloc(LPTR, hashLen))
							{
								status = CryptGetHashParam(hHash, HP_HASHVAL, buffer, &hashLen, 0);
								RtlCopyMemory(hash, buffer, min(hashLen, hashWanted));
								LocalFree(buffer);
							}
						}
					}
				}
				CryptDestroyHash(hHash);
			}
			CryptDestroyKey(hKey);
		}
		CryptReleaseContext(hProv, 0);
	}

	return status;
}

BOOL kull_m_ntlm_HMAC_MD5(IN const BYTE pbKey[MD5_DIGEST_LENGTH], IN LPCBYTE pbMessage, IN const DWORD cbMessage, OUT BYTE pbDigest[MD5_DIGEST_LENGTH])
{
	return kull_m_crypto_hmac(CALG_MD5, pbKey, MD5_DIGEST_LENGTH, pbMessage, cbMessage, pbDigest, MD5_DIGEST_LENGTH);
}

BOOL kull_m_ntlm_LMHASH(IN LPCWSTR szPassword, OUT BYTE pbLMHash[LM_NTLM_HASH_LENGTH])
{
	BOOL status = FALSE;
	UNICODE_STRING uPassword;
	OEM_STRING oTmp;
	RtlInitUnicodeString(&uPassword, szPassword);

	if(NT_SUCCESS(RtlUpcaseUnicodeStringToOemString(&oTmp, &uPassword, TRUE)))
	{
		status = NT_SUCCESS(RtlCalculateLmOwfPassword(oTmp.Buffer, pbLMHash));
		RtlFreeOemString(&oTmp);
	}
	return status;
}

BOOL kull_m_ntlm_NTHASH(IN LPCWSTR szPassword, OUT BYTE pbNTLMHash[LM_NTLM_HASH_LENGTH])
{
	UNICODE_STRING uPassword;
	RtlInitUnicodeString(&uPassword, szPassword);
	return NT_SUCCESS(RtlCalculateNtOwfPassword(&uPassword, pbNTLMHash));
}

BOOL kull_m_ntlm_LMOWFv1(IN OPTIONAL LPCWSTR szPassword, IN OPTIONAL BYTE pbLMHash[LM_NTLM_HASH_LENGTH], OUT BYTE pbLMKey[LM_NTLM_HASH_LENGTH])
{
	BOOL status = FALSE;

	if(pbLMHash)
	{
		RtlCopyMemory(pbLMKey, pbLMHash, LM_NTLM_HASH_LENGTH);
		status = TRUE;
	}
	else
	{
		status = kull_m_ntlm_LMHASH(szPassword, pbLMKey);
	}

	return status;
}

BOOL kull_m_ntlm_NTOWFv1(IN OPTIONAL LPCWSTR szPassword, IN OPTIONAL BYTE pbNTLMHash[LM_NTLM_HASH_LENGTH], OUT BYTE pbNTLMKey[LM_NTLM_HASH_LENGTH])
{
	BOOL status;

	if(pbNTLMHash)
	{
		RtlCopyMemory(pbNTLMKey, pbNTLMHash, LM_NTLM_HASH_LENGTH);
		status = TRUE;
	}
	else
	{
		status = kull_m_ntlm_NTHASH(szPassword, pbNTLMKey);
	}

	return status;
}

BOOL kull_m_ntlm_NTOWFv2(IN LPCWSTR szUserName, IN LPCWSTR szDomainName, IN OPTIONAL LPCWSTR szPassword, IN OPTIONAL BYTE pbNTLMHash[LM_NTLM_HASH_LENGTH], OUT BYTE pbNTLMv2Key[LM_NTLM_HASH_LENGTH])
{
	BOOL status = FALSE;
	BYTE NTOWFv1[LM_NTLM_HASH_LENGTH];
	UNICODE_STRING uUserName, uDomainName, uUpUserName, uConcat;

	if(kull_m_ntlm_NTOWFv1(szPassword, pbNTLMHash, NTOWFv1))
	{
		RtlInitUnicodeString(&uUserName, szUserName ? szUserName : L"");
		RtlInitUnicodeString(&uDomainName, szDomainName ? szDomainName : L"");
		if(NT_SUCCESS(RtlUpcaseUnicodeString(&uUpUserName, &uUserName, TRUE)))
		{
			uConcat.Length = 0;
			uConcat.MaximumLength = uUpUserName.Length + uDomainName.Length + sizeof(wchar_t);
			uConcat.Buffer = (PWSTR) LocalAlloc(LPTR, uConcat.MaximumLength);
			if(uConcat.Buffer)
			{
				if(NT_SUCCESS(RtlAppendUnicodeStringToString(&uConcat, &uUpUserName)))
				{
					if(NT_SUCCESS(RtlAppendUnicodeStringToString(&uConcat, &uDomainName)))
					{
						status = kull_m_ntlm_HMAC_MD5(NTOWFv1, (LPCBYTE) uConcat.Buffer, uConcat.Length, pbNTLMv2Key);
					}
				}
				LocalFree(uConcat.Buffer);
			}
			RtlFreeUnicodeString(&uUpUserName);
		}
	}

	return status;
}

BOOL kull_m_ntlm_NTLMv1Response(IN BYTE pbLMorNTLMHash[LM_NTLM_HASH_LENGTH], IN BYTE pbChallenge[DES_BLOCK_LENGTH], OUT BYTE pbResponse[3 * DES_BLOCK_LENGTH])
{
	return NT_SUCCESS(RtlCalculateLmResponse(pbChallenge, pbLMorNTLMHash, pbResponse));
}