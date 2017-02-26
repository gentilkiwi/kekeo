/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "common.h"

void addCred(KRB_CRED *cred, KRB_CRED **dst)
{
	EncKrbCredPart *encCred = NULL, *encDst = NULL;
	OssBuf original;
	KRB_CRED *tmp = NULL;
	struct _seqof3 **tickets = NULL;
	struct _seqof5 **ticket_info = NULL;
	int pduNum;
	if(!*dst)
	{
		if(ossCpyValue(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, cred, (LPVOID *) dst))
			PRINT_ERROR(L"Unable to copy KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	}
	else
	{
		pduNum = EncKrbCredPart_PDU;
		if(!ossDecode(&kull_m_kerberos_asn1_world, &pduNum, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &encCred))
		{
			pduNum = EncKrbCredPart_PDU;
			if(!ossDecode(&kull_m_kerberos_asn1_world, &pduNum, (OssBuf *) &(*dst)->enc_part.cipher, (LPVOID *) &encDst))
			{
				if((tickets = &(*dst)->tickets) && (ticket_info = &encDst->ticket_info))
				{
					while((*tickets)->next)
						tickets = &(*tickets)->next;
					while((*ticket_info)->next)
						ticket_info = &(*ticket_info)->next;

					(*tickets)->next = cred->tickets;
					(*ticket_info)->next = encCred->ticket_info;

					original = *(OssBuf *) &(*dst)->enc_part.cipher;
					(*dst)->enc_part.cipher.length = 0;
					(*dst)->enc_part.cipher.value = NULL;
					if(!ossEncode(&kull_m_kerberos_asn1_world, EncKrbCredPart_PDU, encDst, (OssBuf *) &(*dst)->enc_part.cipher))
					{
						if(ossCpyValue(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, *dst, (LPVOID *) &tmp))
							PRINT_ERROR(L"Unable to copy KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
						ossFreeBuf(&kull_m_kerberos_asn1_world, (*dst)->enc_part.cipher.value);
					}
					else PRINT_ERROR(L"Unable to encode EncKrbCredPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
					(*dst)->enc_part.cipher = *(_octet1 *) &original;
					(*tickets)->next = NULL;
					(*ticket_info)->next = NULL;
				}
				if(tmp)
				{
					ossFreePDU(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, *dst);
					*dst = tmp;
				}
				ossFreePDU(&kull_m_kerberos_asn1_world, EncKrbCredPart_PDU, encDst);
			}
			else PRINT_ERROR(L"Unable to decode EncKrbCredPart(dst): %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
			ossFreePDU(&kull_m_kerberos_asn1_world, EncKrbCredPart_PDU, encCred);
		}
		else PRINT_ERROR(L"Unable to decode EncKrbCredPart(cred): %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	}
}

void writeData(const KERB_FORMAT_MODULE * module, BOOL multiple, KRB_CRED *cred)
{
	OssBuf output = {0, NULL};
	EncKrbCredPart * encKrbCredPart = NULL, credpart;
	struct _seqof5 * nextInfos, infos;
	struct _seqof3 * nextTicket, ticket;
	DWORD i;
	KRB_CRED tmp;
	LPWSTR filename;
	int pduNum = EncKrbCredPart_PDU;

	if(!ossDecode(&kull_m_kerberos_asn1_world, &pduNum, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &encKrbCredPart))
	{
		if(multiple)
		{
			for(i = 0, nextTicket = cred->tickets, nextInfos = encKrbCredPart->ticket_info; nextTicket && nextInfos; nextTicket = nextTicket->next, nextInfos = nextInfos->next, i++)
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

				if(!ossEncode(&kull_m_kerberos_asn1_world, EncKrbCredPart_PDU, &credpart, (OssBuf *) &tmp.enc_part.cipher))
				{
					if(module->writeData(&tmp, &output))
					{
						if(module->validHeader)
						{
							if(filename = kull_m_kerberos_asn1_KrbCred_filename(&tmp, NULL, module->simpleName))
							{
								kprintf(L" > %s", filename);
								if(kull_m_file_writeData(filename, output.value, output.length))
									kprintf(L"\n");
								else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
								LocalFree(filename);
							}
						}
						else
						{
							kprintf(L" > ");
							kull_m_kerberos_asn1_PrincipalName_descr(&tmp.tickets->value.sname, FALSE);
							kprintf(L" : ");
							if(NT_SUCCESS(kuhl_m_kerberos_ptt_data(output.value, output.length, NULL)))
								kprintf(L"injected!\n");
						}
						LocalFree(output.value);
					}
					ossFreeBuf(&kull_m_kerberos_asn1_world, tmp.enc_part.cipher.value);
				}
				else PRINT_ERROR(L"Unable to encode EncKrbCredPart: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
			}
		}
		else
		{
			if(module->writeData(cred, &output))
			{
				if(filename = kull_m_kerberos_asn1_KrbCred_filename(cred, NULL, module->multiName))
				{
					kprintf(L" > %s", filename);
					if(kull_m_file_writeData(filename, output.value, output.length))
						kprintf(L"\n");
					else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
					LocalFree(filename);
				}
				LocalFree(output.value);
			}
		}
		ossFreePDU(&kull_m_kerberos_asn1_world, EncKrbCredPart_PDU, encKrbCredPart);
	}
}