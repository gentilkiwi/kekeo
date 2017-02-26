/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "krbcred.h"

BOOL kiwi_krbcred_valid_header(OssBuf *input)
{
	return ((input->length > 4) && ((_byteswap_ushort(*(PUSHORT) input->value) & 0xfff0) == 0x7680));
}

BOOL kiwi_krbcred_read(OssBuf *input, KRB_CRED **cred)
{
	BOOL status = FALSE;
	int pduNum = KRB_CRED_PDU;
	*cred = NULL;
	status = !ossDecode(&kull_m_kerberos_asn1_world, &pduNum, input, (LPVOID *) cred);
	if(!status)
		PRINT_ERROR(L"Unable to decode KRB_CRED: %S\n", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	return status;
}

BOOL kiwi_krbcred_write(KRB_CRED *cred, OssBuf *output)
{
	BOOL status = FALSE;
	OssBuf tmp = {0, NULL};

	output->length = 0;
	output->value = NULL;
	if(!ossEncode(&kull_m_kerberos_asn1_world, KRB_CRED_PDU, cred, &tmp))
	{
		if(output->value = (unsigned char *) LocalAlloc(LPTR, tmp.length))
		{
			RtlCopyMemory(output->value, tmp.value, tmp.length);
			output->length = tmp.length;
			status = TRUE;
		}
		ossFreeBuf(&kull_m_kerberos_asn1_world, tmp.value);
	}
	else PRINT_ERROR(L"Unable to encode KRB_CRED: %S", ossGetErrMsg(&kull_m_kerberos_asn1_world));
	if(!status && output->value)
	{
		output->length = 0;
		LocalFree(output->value);
	}
	return status;
}