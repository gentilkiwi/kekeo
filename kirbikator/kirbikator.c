/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "kirbikator.h"

BOOL g_isAsn1Init = FALSE, g_isKerberos = FALSE;

const KERB_FORMAT_MODULE modules[] = {
	{"MIT Credential Cache", kiwi_ccache_valid_header, kiwi_ccache_read, kiwi_ccache_write, "ccache", "ccaches"},
	{"RFC KRB-CRED (#22)", kiwi_krbcred_valid_header, kiwi_krbcred_read, kiwi_krbcred_write, "kirbi", "kirbis"},
	{"WCE \'windows wce\'", kiwi_wce_valid_header, kiwi_wce_read, kiwi_wce_write, "wce", "wces"},
	{"Microsoft LSA API", NULL, NULL, kiwi_lsa_write, NULL, "lsa"},
};

BOOL init()
{
	BOOL status = FALSE;
	RtlGetNtVersionNumbers(&MIMIKATZ_NT_MAJOR_VERSION, &MIMIKATZ_NT_MINOR_VERSION, &MIMIKATZ_NT_BUILD_NUMBER);
	MIMIKATZ_NT_BUILD_NUMBER &= 0x00003fff;

	if(g_isAsn1Init = kull_m_kerberos_asn1_helper_init())
		if(g_isKerberos = kull_m_kerberos_helper_init())
			status = TRUE;
	return status;
}

BOOL term()
{
	if(g_isAsn1Init)
		g_isAsn1Init = !kull_m_kerberos_asn1_helper_term();
	if(g_isKerberos)
		g_isKerberos = !kull_m_kerberos_helper_term();

	return !(g_isAsn1Init || g_isKerberos);
}

int main(int argc, char * argv[])
{
	DWORD i, j;
	KERB_FORMAT_MODULE const * readModule, * writeModule;
	OssBuf input, output = {0, NULL};
	KRB_CRED *cred = NULL, *dst = NULL;
	BOOL explodeIt;

	kprintf("\n"
		"  .#####.   " MIMIKATZ_FULL "\n"
		" .## ^ ##.  " MIMIKATZ_SECOND "\n"
		" ## / \\ ##  /* * *\n"
		" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		" '## v ##'   http://blog.gentilkiwi.com                      (oe.eo)\n"
		"  '#####'                                                     * * */\n\n");

	if(argc > 2)
	{
		if(init())
		{
			writeModule = NULL;
			for(j = 0; j < ARRAYSIZE(modules); j++)
			{
				if(modules[j].simpleName && !_stricmp(modules[j].simpleName, argv[1]))
				{
					writeModule = &modules[j];
					explodeIt = FALSE;
					break;
				}
				else if(modules[j].multiName && !_stricmp(modules[j].multiName, argv[1]))
				{
					writeModule = &modules[j];
					explodeIt = TRUE;
					break;
				}
			}

			if(writeModule)
			{
				kprintf("Destination : %s (%s)\n", writeModule->shortName, explodeIt ? "multiple" : "simple");
				for(i = 2; i < (DWORD) argc ; i++)
				{
					kprintf(" < %s ", argv[i]);
					if(kull_m_file_readData(argv[i], &input.value, (PDWORD) &input.length))
					{
						readModule = NULL;
						for(j = 0; j < ARRAYSIZE(modules); j++)
						{
							if(modules[j].validHeader)
							{
								if(modules[j].validHeader(&input))
								{
									readModule = &modules[j];
									break;
								}
							}
						}

						if(readModule)
						{
							kprintf("(%s) ", readModule->shortName);
							if(readModule->readData && readModule->readData(&input, &cred))
							{
								addCred(cred, &dst);
								kull_m_kerberos_asn1_helper_ossFreePDU(KRB_CRED_PDU, cred);
							}
							else kprintf(": error when reading!");
						}
						else kprintf(": format not recognized!");
						kprintf("\n");
						LocalFree(input.value);
					}
					else PRINT_ERROR_AUTO("kull_m_file_readData");
				}

				if(dst)
				{
					writeData(writeModule, explodeIt, dst);
					kull_m_kerberos_asn1_helper_ossFreePDU(KRB_CRED_PDU, dst);
				}
			}
		}
		else PRINT_ERROR("init() failed\n");
		term();
	}
	else PRINT_ERROR("Arguments missing! kirbi|ccache|wce|lsa|kirbis|ccaches|wces ticket1 [ticket2] [...]\n");

	return 0;
}

void addCred(KRB_CRED *cred, KRB_CRED **dst)
{
	EncKrbCredPart *encCred = NULL, *encDst = NULL;
	OssBuf original;
	KRB_CRED *tmp = NULL;
	struct _seqof3 **tickets = NULL;
	struct _seqof5 **ticket_info = NULL;

	if(!*dst)
	{
		if(kull_m_kerberos_asn1_helper_ossCpyValue(KRB_CRED_PDU, cred, (LPVOID *) dst))
			PRINT_ERROR("%s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
	}
	else
	{
		if(!kull_m_kerberos_asn1_helper_ossDecode(EncKrbCredPart_PDU, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &encCred))
		{
			if(!kull_m_kerberos_asn1_helper_ossDecode(EncKrbCredPart_PDU, (OssBuf *) &(*dst)->enc_part.cipher, (LPVOID *) &encDst))
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
					if(!kull_m_kerberos_asn1_helper_ossEncode(EncKrbCredPart_PDU, encDst, (OssBuf *) &(*dst)->enc_part.cipher))
					{
						if(kull_m_kerberos_asn1_helper_ossCpyValue(KRB_CRED_PDU, *dst, (LPVOID *) &tmp))
							PRINT_ERROR("%s", kull_m_kerberos_asn1_helper_ossGetErrMsg());	
						kull_m_kerberos_asn1_helper_ossFreeBuf((*dst)->enc_part.cipher.value);
					}
					else PRINT_ERROR("%s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
					(*dst)->enc_part.cipher = *(_octet1 *) &original;
					(*tickets)->next = NULL;
					(*ticket_info)->next = NULL;
				}
				if(tmp)
				{
					kull_m_kerberos_asn1_helper_ossFreePDU(KRB_CRED_PDU, *dst);
					*dst = tmp;
				}
				kull_m_kerberos_asn1_helper_ossFreePDU(EncKrbCredPart_PDU, encDst);
			}
			else PRINT_ERROR("(dst) %s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
			kull_m_kerberos_asn1_helper_ossFreePDU(EncKrbCredPart_PDU, encCred);
		}
		else PRINT_ERROR("(cred) %s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
	}
}

void writeData(const KERB_FORMAT_MODULE * module, BOOL multiple, KRB_CRED *cred)
{
	OssBuf output = {0, NULL};
	EncKrbCredPart * encKrbCredPart = NULL, credpart;
	struct _seqof5 * nextInfos, infos;
	struct _seqof3 * nextTicket, ticket;
	DWORD i;
	size_t stringLen;
	char * fileNameBuffer;
	KRB_CRED tmp;
	
	if(!kull_m_kerberos_asn1_helper_ossDecode(EncKrbCredPart_PDU, (OssBuf *) &cred->enc_part.cipher, (LPVOID *) &encKrbCredPart))
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

				if(!kull_m_kerberos_asn1_helper_ossEncode(EncKrbCredPart_PDU, &credpart, (OssBuf *) &tmp.enc_part.cipher))
				{
					if(!module->validHeader)
						kprintf(" > Ticket %s@%s-%s~%s@%s : ", infos.value.pname.name_string->value, infos.value.prealm, infos.value.sname.name_string->value, infos.value.sname.name_string->next ? infos.value.sname.name_string->next->value : "-", infos.value.srealm);
					
					if(module->writeData(&tmp, &output))
					{
						if(module->validHeader)
						{
							stringLen = sizeof(DWORD) + sizeof(DWORD) * 2 + strlen(infos.value.pname.name_string->value) + strlen(infos.value.prealm) + strlen(infos.value.sname.name_string->value) + strlen(infos.value.sname.name_string->next ? infos.value.sname.name_string->next->value : "-") + strlen(infos.value.srealm) + (module->simpleName ? strlen(module->simpleName) : 0) + 7; // - - @ - ~ @ . \0
							if(fileNameBuffer = (char * ) LocalAlloc(LPTR, stringLen))
							{
								if(sprintf_s(fileNameBuffer, stringLen, "%u-%08x-%s@%s-%s~%s@%s.%s", i, _byteswap_ulong(*(PDWORD) infos.value.flags.value), infos.value.pname.name_string->value, infos.value.prealm, infos.value.sname.name_string->value, infos.value.sname.name_string->next ? infos.value.sname.name_string->next->value : "-", infos.value.srealm, module->simpleName ? module->simpleName : "") > 0)
								{
									if(kull_m_file_writeData(fileNameBuffer, output.value, output.length))
										kprintf(" > File : %s\n", fileNameBuffer);
								}
								LocalFree(fileNameBuffer);
							}
						}
						LocalFree(output.value);
					}

					kull_m_kerberos_asn1_helper_ossFreeBuf(tmp.enc_part.cipher.value);
				}
				else PRINT_ERROR("%s", kull_m_kerberos_asn1_helper_ossGetErrMsg());
			}
		}
		else
		{
			if(!module->validHeader)
				kprintf(" > Ticket %s@%s : ", encKrbCredPart->ticket_info->value.pname.name_string->value, encKrbCredPart->ticket_info->value.prealm);

			if(module->writeData(cred, &output))
			{
				stringLen = strlen(encKrbCredPart->ticket_info->value.pname.name_string->value) + strlen(encKrbCredPart->ticket_info->value.prealm) + (module->simpleName ? strlen(module->simpleName) : 0) + 3; // @ . \0
				if(fileNameBuffer = (char * ) LocalAlloc(LPTR, stringLen))
				{
					if(sprintf_s(fileNameBuffer, stringLen, "%s@%s.%s", encKrbCredPart->ticket_info->value.pname.name_string->value, encKrbCredPart->ticket_info->value.prealm, module->simpleName ? module->simpleName : "") > 0)
					{
						if(module->validHeader)
							if(kull_m_file_writeData(fileNameBuffer, output.value, output.length))
								kprintf(" > Single file : %s\n", fileNameBuffer);
					}
					LocalFree(fileNameBuffer);
				}
				LocalFree(output.value);
			}
		}
		kull_m_kerberos_asn1_helper_ossFreePDU(EncKrbCredPart_PDU, encKrbCredPart);
	}
}