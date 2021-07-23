/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "wce.h"

BOOL kiwi_wce_valid_header(OssBuf *input)
{
	return ((input->length > 3 * sizeof(DWORD)) && (*(PDWORD) input->value) == WCE_KERBEROS_TICKET_HEADER);
}

BOOL kiwi_wce_read(OssBuf *input, KULL_M_ASN1_KRB_CRED **cred)
{
	PWCE_KERBEROS_TICKET pWce;
	OssBuf buffer;
	KULL_M_ASN1_KRB_CRED *bufferCred;
	DWORD i, curTicket, nbTicket = 0;
	BOOL isKey = FALSE;

	*cred = NULL;
	for(pWce = (PWCE_KERBEROS_TICKET) input->value, curTicket = 0; (pWce->header == WCE_KERBEROS_TICKET_HEADER) && (pWce->encodedTicketSize + pWce->sessionKeySize) ; pWce = (PWCE_KERBEROS_TICKET) (pWce->data + pWce->encodedTicketSize + pWce->sessionKeySize), curTicket++)
	{
		buffer.length = pWce->encodedTicketSize;
		buffer.value = pWce->data + pWce->sessionKeySize;
		for(i = 0; !isKey && (i < pWce->sessionKeySize); i++)
			isKey |= pWce->data[i];
		if(!isKey)
			kprintf(L"\n[ticket %u] session Key is NULL, maybe a TGT without enough rights when WCE dumped it.", curTicket);

		if(kiwi_krbcred_valid_header(&buffer))
		{
			if(kiwi_krbcred_read(&buffer, &bufferCred))
			{
				addCred(bufferCred, cred);
				nbTicket++;
				ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_KRB_CRED_PDU, bufferCred);
			}
			else PRINT_ERROR(L"[ticket %u] reading KRB-CRED from wce cache\n", curTicket);
		}
		else PRINT_ERROR(L"[ticket %u] validating KRB-CRED from wce cache\n", curTicket);
	}
	return (nbTicket > 0);
}

BOOL kiwi_wce_write(KULL_M_ASN1_KRB_CRED *cred, OssBuf *output)
{
	BOOL status = FALSE;
	PWCE_BUFF_TICKET outputTmp = NULL;
	KULL_M_ASN1_EncKrbCredPart * encKrbCredPart = NULL, credpart;
	struct KULL_M_ASN1__seqof5 * nextInfos, infos;
	struct KULL_M_ASN1__seqof3 * nextTicket, ticket;
	KULL_M_ASN1_KRB_CRED tmp;
	DWORD i, count = 0;
	PWCE_KERBEROS_TICKET pWce;
	int pduNum = KULL_M_ASN1_EncKrbCredPart_PDU;
	output->length = 0;
	output->value = NULL;
	if(!ossDecode(&kull_m_kerberos_asn1_world, &pduNum, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &encKrbCredPart))
	{
		status = TRUE;
		for(nextTicket = cred->tickets, nextInfos = encKrbCredPart->ticket_info; nextTicket && nextInfos && status; nextTicket = nextTicket->next, nextInfos = nextInfos->next)
			count++;
		if(count && (outputTmp = (PWCE_BUFF_TICKET) LocalAlloc(LPTR, count * sizeof(WCE_BUFF_TICKET))))
		{
			for(nextTicket = cred->tickets, nextInfos = encKrbCredPart->ticket_info, i = 0; nextTicket && nextInfos && status; nextTicket = nextTicket->next, nextInfos = nextInfos->next, i++)
			{
				tmp.pvno = 5;
				tmp.msg_type = 22;
				tmp.enc_part.bit_mask = 0;
				tmp.enc_part.etype = KERB_ETYPE_NULL;
				tmp.enc_part.cipher.length = 0;
				tmp.enc_part.cipher.value = NULL;
				tmp.tickets = &ticket;
				credpart.bit_mask = 0;
				credpart.ticket_info = &infos;

				ticket = *nextTicket;
				ticket.next = NULL;
				infos = *nextInfos;
				infos.next = NULL;

				outputTmp[i].SessionKey.length = infos.value.key.keyvalue.length;
				if(outputTmp[i].SessionKey.length && (outputTmp[i].SessionKey.value = (PBYTE) LocalAlloc(LPTR, outputTmp[i].SessionKey.length)))
				{
					RtlCopyMemory(outputTmp[i].SessionKey.value, infos.value.key.keyvalue.value, outputTmp[i].SessionKey.length);
					if(!ossEncode(&kull_m_kerberos_asn1_world, KULL_M_ASN1_EncKrbCredPart_PDU, &credpart, (OssBuf *) &tmp.enc_part.cipher))
					{
						if(!kiwi_krbcred_write(&tmp, &outputTmp[i].Ticket))
							PRINT_ERROR(L"writing KRB_CRED\n");
						ossFreeBuf(&kull_m_kerberos_asn1_world, tmp.enc_part.cipher.value);
					}
					else PRINT_ERROR(L"Unable to encode EncKrbCredPart: %S", ossGetErrMsg(&kull_m_kerberos_asn1_world));
				}
			}
			ossFreePDU(&kull_m_kerberos_asn1_world, KULL_M_ASN1_EncKrbCredPart_PDU, encKrbCredPart);
		
			for(i = 0; i < count; i++)
				output->length += FIELD_OFFSET(WCE_KERBEROS_TICKET, data) + outputTmp[i].SessionKey.length + outputTmp[i].Ticket.length;
			output->length += FIELD_OFFSET(WCE_KERBEROS_TICKET, data);
		
			if(output->value = (PBYTE) LocalAlloc(LPTR, output->length))
			{
				status = TRUE;
				for(pWce = (PWCE_KERBEROS_TICKET) output->value, i = 0; i < count; pWce = (PWCE_KERBEROS_TICKET) (pWce->data + pWce->encodedTicketSize + pWce->sessionKeySize), i++)
				{
					pWce->header = WCE_KERBEROS_TICKET_HEADER;
					pWce->sessionKeySize = outputTmp[i].SessionKey.length;
					pWce->encodedTicketSize = outputTmp[i].Ticket.length;

					if(outputTmp[i].SessionKey.length && outputTmp[i].SessionKey.value)
					{
						RtlCopyMemory(pWce->data, outputTmp[i].SessionKey.value, pWce->sessionKeySize);
						LocalFree(outputTmp[i].SessionKey.value);
					}
					
					if(outputTmp[i].Ticket.length && outputTmp[i].Ticket.value)
					{
						RtlCopyMemory(pWce->data + pWce->sessionKeySize, outputTmp[i].Ticket.value, pWce->encodedTicketSize);
						LocalFree(outputTmp[i].Ticket.value);
					}
				}
				pWce->header = WCE_KERBEROS_TICKET_HEADER;		
				pWce->sessionKeySize = 0;
				pWce->encodedTicketSize = 0;
			}
		}
		else PRINT_ERROR(L"Unable to decode EncKrbCredPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	}

	if(!status && output->value)
		LocalFree(output->value);

	return status;
}