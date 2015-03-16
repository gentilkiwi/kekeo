/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "ccache.h"

BOOL kiwi_ccache_valid_header(OssBuf *input)
{
	return ((input->length > 4) && (_byteswap_ushort(*(PUSHORT) input->value) == 0x0504));
}

BOOL kiwi_ccache_read(OssBuf *input, KRB_CRED **cred)
{
	BOOL status = FALSE;
	PBYTE data = input->value;
	KRB_CRED lCred;
	struct _seqof3 **lTickets;
	
	EncKrbCredPart lEncPart;
	struct _seqof5 **lTicket_info;

	PrincipalName principal;
	Realm realm = NULL;

	OssBuf encodedTicket, output = {0 , NULL};
	Ticket *ticket;

	*cred = NULL;
	if(_byteswap_ushort(*(PUSHORT) data) == 0x0504)
	{
		data += sizeof(USHORT);
		data += sizeof(USHORT) + _byteswap_ushort(*(PUSHORT) data);
		
		kiwi_ccache_create_principal_realm(&data, &principal, &realm);
		
		lCred.pvno = 5;
		lCred.msg_type = 22;
		lCred.tickets = NULL;
		lCred.enc_part.bit_mask = 0;
		lCred.enc_part.etype = KERB_ETYPE_NULL;
		
		lTickets = &lCred.tickets;
		
		lEncPart.bit_mask = 0;
		lEncPart.ticket_info = NULL;
				
		lTicket_info = &lEncPart.ticket_info;
		
		while(data < (input->value + input->length))
		{
			if(*lTicket_info = (struct _seqof5 *) LocalAlloc(LPTR, sizeof(struct _seqof5)))
			{
				(*lTicket_info)->value.bit_mask = pname_present | authtime_present | KrbCredInfo_starttime_present | endtime_present | KrbCredInfo_renew_till_present | KrbCredInfo_sname_present;

				kiwi_ccache_create_principal_realm(&data, &(*lTicket_info)->value.pname, &(*lTicket_info)->value.prealm);
				kiwi_ccache_create_principal_realm(&data, &(*lTicket_info)->value.sname, &(*lTicket_info)->value.srealm);

				(*lTicket_info)->value.key.keytype = _byteswap_ushort(*(PUSHORT) data); data += 2*sizeof(USHORT);
				(*lTicket_info)->value.key.keyvalue.length = _byteswap_ushort(*(PUSHORT) data); data += sizeof(USHORT);
				if((*lTicket_info)->value.key.keyvalue.value = (unsigned char *) LocalAlloc(LPTR, (*lTicket_info)->value.key.keyvalue.length))
					RtlCopyMemory((*lTicket_info)->value.key.keyvalue.value, data, (*lTicket_info)->value.key.keyvalue.length);
				data += (*lTicket_info)->value.key.keyvalue.length;

				kull_m_kerberos_asn1_helper_init_KerberosTime3(&(*lTicket_info)->value.authtime, _byteswap_ulong(*(PDWORD) data)); data += sizeof(DWORD);
				kull_m_kerberos_asn1_helper_init_KerberosTime3(&(*lTicket_info)->value.starttime, _byteswap_ulong(*(PDWORD) data)); data += sizeof(DWORD);
				kull_m_kerberos_asn1_helper_init_KerberosTime3(&(*lTicket_info)->value.endtime, _byteswap_ulong(*(PDWORD) data)); data += sizeof(DWORD);
				kull_m_kerberos_asn1_helper_init_KerberosTime3(&(*lTicket_info)->value.renew_till, _byteswap_ulong(*(PDWORD) data)); data += sizeof(DWORD);
				
				data += sizeof(UCHAR); // skey
				if((*lTicket_info)->value.flags.value = (unsigned char *) LocalAlloc(LPTR, sizeof(DWORD)))
				{
					(*lTicket_info)->value.bit_mask |= flags_present;
					(*lTicket_info)->value.flags.length = sizeof(DWORD) * 8;
					*(PDWORD) (*lTicket_info)->value.flags.value = *(PDWORD) data; data += sizeof(DWORD);
				}
				
				kiwi_ccache_skip_struct_with_buffer(&data); // address  !! todo / KrbCredInfo_caddr_present 0x01
				kiwi_ccache_skip_struct_with_buffer(&data); // authdata !!

				encodedTicket.length = _byteswap_ulong(*(PDWORD) data); data += sizeof(DWORD);
				encodedTicket.value = data;
				data += encodedTicket.length;
				kiwi_ccache_skip_buffer(&data); // second ticket ?

				if(_stricmp((*lTicket_info)->value.srealm, "X-CACHECONF:") && encodedTicket.length)
				{
					ticket = NULL;
					if(!kull_m_kerberos_asn1_helper_ossDecode(Ticket_PDU, &encodedTicket, (void **) &ticket))
					{
						if(*lTickets = (struct _seqof3 *) LocalAlloc(LPTR, sizeof(struct _seqof3)))
						{
							(*lTickets)->value.tkt_vno = ticket->tkt_vno;
							(*lTickets)->value.enc_part = ticket->enc_part;

							kiwi_ccache_copy_principal_realm(&ticket->sname, &ticket->realm, &(*lTickets)->value.sname, &(*lTickets)->value.realm);
							if((*lTickets)->value.enc_part.cipher.value = (unsigned char *) LocalAlloc(LPTR, (*lTickets)->value.enc_part.cipher.length))
								RtlCopyMemory((*lTickets)->value.enc_part.cipher.value, ticket->enc_part.cipher.value, (*lTickets)->value.enc_part.cipher.length);

							lTickets = &(*lTickets)->next;
						}
						kull_m_kerberos_asn1_helper_ossFreePDU(Ticket_PDU, ticket);
					}
					else kprintf("%s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());
					lTicket_info = &(*lTicket_info)->next;
				}
				else kiwi_ccache_free_ticketInfo(*lTicket_info);
			}
		}

		if(!kull_m_kerberos_asn1_helper_ossEncode(EncKrbCredPart_PDU, &lEncPart, &output))
		{
			lCred.enc_part.cipher = *(_octet1 *) &output;
			status = !kull_m_kerberos_asn1_helper_ossCpyValue(KRB_CRED_PDU, &lCred, (void **) cred);
			if(!status)
				PRINT_ERROR("%s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());
			kull_m_kerberos_asn1_helper_ossFreeBuf(output.value);
		}
		else PRINT_ERROR("%s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());
		
		kiwi_ccache_free_ticket(lCred.tickets);
		kiwi_ccache_free_ticketInfo(lEncPart.ticket_info);
		kiwi_ccache_free_principal_realm(&principal, &realm);
	}
	else PRINT_ERROR("CCACHE version != 0x0504\n");

	return status;
}

BOOL kiwi_ccache_write(KRB_CRED *cred, OssBuf *output)
{
	BOOL status = FALSE;
	EncKrbCredPart * encKrbCredPart = NULL;
	struct _seqof5 * nextInfos;
	struct _seqof3 * nextTicket;
	OssBuf ticketBuf;
	PrincipalName * pname;
	Realm * prealm;
	PBYTE data;
	time_t t;

	output->length = 0;
	output->value = NULL;
	if(!kull_m_kerberos_asn1_helper_ossDecode(EncKrbCredPart_PDU, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &encKrbCredPart))
	{
		output->length = kiwi_ccache_size_header_krbcred(cred, encKrbCredPart, &pname, &prealm);
		if(output->value = (PBYTE) LocalAlloc(LPTR, output->length))
		{
			status = TRUE;

			data = output->value;
			*(PUSHORT) data = _byteswap_ushort(0x0504); data += sizeof(USHORT);
			*(PUSHORT) data = 0; data += sizeof(USHORT);
			kiwi_ccache_write_principal_realm(&data, pname, prealm);

			for(nextTicket = cred->tickets, nextInfos = encKrbCredPart->ticket_info; nextTicket && nextInfos && status; nextTicket = nextTicket->next, nextInfos = nextInfos->next)
			{
				kiwi_ccache_write_principal_realm(&data, &nextInfos->value.pname, &nextInfos->value.prealm); // ok, I presume it's here
				kiwi_ccache_write_principal_realm(&data, &nextInfos->value.sname, &nextInfos->value.srealm); // ok, I presume it's here

				*(PUSHORT) data = _byteswap_ushort((USHORT) nextInfos->value.key.keytype); data += sizeof(USHORT);
				*(PUSHORT) data = 0; data += sizeof(USHORT);
				*(PUSHORT) data = _byteswap_ushort((USHORT) nextInfos->value.key.keyvalue.length); data += sizeof(USHORT);
				RtlCopyMemory(data, nextInfos->value.key.keyvalue.value, nextInfos->value.key.keyvalue.length); data += nextInfos->value.key.keyvalue.length;

				if(nextInfos->value.bit_mask & authtime_present)
					kull_m_kerberos_asn1_helper_get_KerberosTime3(&nextInfos->value.authtime, &t);
				else t = 0;
				*(PDWORD) data = _byteswap_ulong((DWORD) t); data += sizeof(DWORD);

				if(nextInfos->value.bit_mask & KrbCredInfo_starttime_present)
					kull_m_kerberos_asn1_helper_get_KerberosTime3(&nextInfos->value.starttime, &t);
				else t = 0;
				*(PDWORD) data = _byteswap_ulong((DWORD) t); data += sizeof(DWORD);

				if(nextInfos->value.bit_mask & endtime_present)
					kull_m_kerberos_asn1_helper_get_KerberosTime3(&nextInfos->value.endtime, &t);
				else t = 0;
				*(PDWORD) data = _byteswap_ulong((DWORD) t); data += sizeof(DWORD);

				if(nextInfos->value.bit_mask & KrbCredInfo_renew_till_present)
					kull_m_kerberos_asn1_helper_get_KerberosTime3(&nextInfos->value.renew_till, &t);
				else t = 0;
				*(PDWORD) data = _byteswap_ulong((DWORD) t); data += sizeof(DWORD);
								
				*(PUCHAR) data = 0; data += sizeof(UCHAR);
				*(PDWORD) data = ((nextInfos->value.bit_mask & flags_present) && (nextInfos->value.flags.length >= (sizeof(DWORD) * 8))) ? (*(PDWORD) nextInfos->value.flags.value) : 0; data += sizeof(DWORD);
				*(PDWORD) data = 0; data += sizeof(DWORD); // address
				*(PDWORD) data = 0; data += sizeof(DWORD); // authdata

				ticketBuf.length = 0;
				ticketBuf.value = NULL;
				if(!kull_m_kerberos_asn1_helper_ossEncode(Ticket_PDU, &nextTicket->value, &ticketBuf))
				{
					*(PDWORD) data = _byteswap_ulong(ticketBuf.length); data += sizeof(DWORD);
					RtlCopyMemory(data, ticketBuf.value, ticketBuf.length); data += ticketBuf.length;
					kull_m_kerberos_asn1_helper_ossFreeBuf(ticketBuf.value);
				}
				else
				{
					status = FALSE;
					PRINT_ERROR("%s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());
				}
				*(PDWORD) data = 0; data += sizeof(DWORD);
			}
		}
		kull_m_kerberos_asn1_helper_ossFreePDU(EncKrbCredPart_PDU, encKrbCredPart);
	}
	else PRINT_ERROR("%s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());

	if(!status && output->value)
		LocalFree(output->value);

	return status;
}

DWORD kiwi_ccache_size_header_krbcred(KRB_CRED *cred, EncKrbCredPart * encKrbCredPart, PrincipalName ** pname, Realm ** prealm)
{
	DWORD size = 2 * sizeof(USHORT);
	struct _seqof5 * nextInfos;
	struct _seqof3 * nextTicket;
	OssBuf ticketBuf;

	for(nextTicket = cred->tickets, nextInfos = encKrbCredPart->ticket_info; nextTicket && nextInfos; nextTicket = nextTicket->next, nextInfos = nextInfos->next)
	{
		if(nextInfos == encKrbCredPart->ticket_info)
		{
			*pname = &nextInfos->value.pname;
			*prealm = &nextInfos->value.prealm;
			size += kiwi_ccache_size_principal_realm(*pname, *prealm);
		}
		size += kiwi_ccache_size_principal_realm(&nextInfos->value.pname, &nextInfos->value.prealm);
		size += kiwi_ccache_size_principal_realm(&nextInfos->value.sname, &nextInfos->value.srealm);
		size += 3 * sizeof(USHORT) + nextInfos->value.key.keyvalue.length;
		size += 4 * sizeof(DWORD);
		size += sizeof(UCHAR);
		size += sizeof(DWORD);
		size += sizeof(DWORD); //size += address;
		size += sizeof(DWORD); //size += authdata;

		ticketBuf.length = 0;
		ticketBuf.value = NULL;
		if(!kull_m_kerberos_asn1_helper_ossEncode(Ticket_PDU, &nextTicket->value, &ticketBuf))
		{
			size += sizeof(DWORD) + ticketBuf.length;
			kull_m_kerberos_asn1_helper_ossFreeBuf(ticketBuf.value);
		}
		else PRINT_ERROR("%s\n", kull_m_kerberos_asn1_helper_ossGetErrMsg());
		size += sizeof(DWORD);
	}
	return size;
}


void kiwi_ccache_free_ticketInfo(struct _seqof5 * infos)
{
	struct _seqof5 * nextInfos = infos;
	while(nextInfos)
	{
		kiwi_ccache_free_principal_realm(&nextInfos->value.pname, &nextInfos->value.prealm);
		kiwi_ccache_free_principal_realm(&nextInfos->value.sname, &nextInfos->value.srealm);
		if(nextInfos->value.key.keyvalue.value)
			LocalFree(nextInfos->value.key.keyvalue.value);

		if(nextInfos->value.flags.value)
			LocalFree(nextInfos->value.flags.value);

		infos = nextInfos;
		nextInfos = nextInfos->next;
		LocalFree(infos);
	}
}

void kiwi_ccache_free_ticket(struct _seqof3 * ticket)
{
	struct _seqof3 * nextTicket = ticket;
	while(nextTicket)
	{
		kiwi_ccache_free_principal_realm(&nextTicket->value.sname, &nextTicket->value.realm);
		if(nextTicket->value.enc_part.cipher.value)
			LocalFree(nextTicket->value.enc_part.cipher.value);
		
		ticket = nextTicket;
		nextTicket = nextTicket->next;
		LocalFree(ticket);
	}
}

void kiwi_ccache_skip_buffer(PBYTE *data)
{
	*data += sizeof(DWORD) + _byteswap_ulong(*(PDWORD) *data);
}

void kiwi_ccache_skip_struct_with_buffer(PBYTE *data)
{
	DWORD i, numBuff = _byteswap_ulong(*(PDWORD) *data); *data += sizeof(DWORD);
	for (i = 0; i < numBuff; i++)
	{
		*data += sizeof(USHORT);
		kiwi_ccache_skip_buffer(data);
	}
}

DWORD kiwi_ccache_size_principal_realm(PrincipalName *name, Realm *realm)
{
	DWORD size = sizeof(DWORD) * 3 + strlen(*realm);
	struct _seqof1 * seq;
	for(seq = name->name_string; seq; seq = seq->next)
		size += sizeof(DWORD) + strlen(seq->value);
	return size;
}

void kiwi_ccache_create_principal_realm(PBYTE *data, PrincipalName *name, Realm *realm)
{
	struct _seqof1 ** seq;
	DWORD numName, numChar;

	name->name_type = _byteswap_ulong(*(PDWORD) *data); *data += sizeof(DWORD);
	numName =  _byteswap_ulong(*(PDWORD) *data); *data += sizeof(DWORD);

	numChar = _byteswap_ulong(*(PDWORD) *data); *data += sizeof(DWORD);
	if(*realm = (Realm) LocalAlloc(LPTR, numChar + sizeof(char)))
		RtlCopyMemory(*realm, *data, numChar);
	*data += numChar;

	seq = &name->name_string;
	while(numName)
	{
		if(*seq = (struct _seqof1 *) LocalAlloc(LPTR, sizeof(struct _seqof1)))
		{
			numChar = _byteswap_ulong(*(PDWORD) *data); *data += sizeof(DWORD);
			if((*seq)->value = (KerberosString) LocalAlloc(LPTR, numChar + sizeof(char)))
				RtlCopyMemory((*seq)->value, *data, numChar);
			*data += numChar;
			seq = &(*seq)->next;
		}
		numName--;
	}
}

void kiwi_ccache_copy_principal_realm(PrincipalName *srcName, Realm *srcRealm, PrincipalName *dstName, Realm *dstRealm)
{
	DWORD szString;
	struct _seqof1 *seq, **ptrSeq;

	szString = strlen(*srcRealm);
	if(*dstRealm = (Realm) LocalAlloc(LPTR, szString + sizeof(char)))
		RtlCopyMemory(*dstRealm, *srcRealm, szString);

	dstName->name_type = srcName->name_type;
	for(seq = srcName->name_string, ptrSeq = &dstName->name_string; seq ; seq = seq->next, ptrSeq = &(*ptrSeq)->next)
	{
		if(*ptrSeq = (struct _seqof1 *) LocalAlloc(LPTR, sizeof(struct _seqof1)))
		{
			szString = strlen(seq->value);
			if((*ptrSeq)->value = (KerberosString) LocalAlloc(LPTR, szString + sizeof(char)))
				RtlCopyMemory((*ptrSeq)->value, seq->value, szString);
		}
	}
}

void kiwi_ccache_free_principal_realm(PrincipalName *name, Realm *realm)
{
	struct _seqof1 *seq, *next;
	if(realm && *realm)
		LocalFree(*realm);

	if(name)
	{
		next = name->name_string;
		while(next)
		{
			seq = next;
			if(seq->value)
				LocalFree(seq->value);
			next = seq->next;
			LocalFree(seq);
		}
	}
}

void kiwi_ccache_write_principal_realm(PBYTE *data, PrincipalName *name, Realm *realm)
{
	PDWORD numCom;
	DWORD numCar, numName = 0;
	struct _seqof1 *seq;
	
	*(PDWORD) *data = _byteswap_ulong(name->name_type); *data += sizeof(DWORD);
	numCom = (PDWORD) *data; *data += sizeof(DWORD);

	numCar = strlen(*realm);
	*(PDWORD) *data = _byteswap_ulong(numCar); *data += sizeof(DWORD);
	RtlCopyMemory(*data, *realm, numCar); *data += numCar;

	for(seq = name->name_string; seq; seq = seq->next)
	{
		numCar = strlen(seq->value);
		*(PDWORD) *data = _byteswap_ulong(numCar); *data += sizeof(DWORD);
		RtlCopyMemory(*data, seq->value, numCar); *data += numCar;
		numName++;
	}
	*numCom = _byteswap_ulong(numName);
}