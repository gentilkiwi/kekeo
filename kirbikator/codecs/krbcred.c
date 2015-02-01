/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#include "krbcred.h"

BOOL kiwi_krbcred_valid_header(OssBuf *input)
{
	return ((input->length > 4) && (_byteswap_ushort(*(PUSHORT) input->value) == 0x7682));
}

BOOL kiwi_krbcred_read(OssBuf *input, KRB_CRED **cred)
{
	BOOL status = FALSE;
	*cred = NULL;
	status = !kull_m_kerberos_asn1_helper_ossDecode(KRB_CRED_PDU, input, (LPVOID *) cred);
	if(!status)
		PRINT_ERROR("%s", kull_m_kerberos_asn1_helper_ossGetErrMsg());

	return status;
}

BOOL kiwi_krbcred_write(KRB_CRED *cred, OssBuf *output)
{
	BOOL status = FALSE;
	OssBuf tmp = {0, NULL};

	output->length = 0;
	output->value = NULL;
	if(!kull_m_kerberos_asn1_helper_ossEncode(KRB_CRED_PDU, cred, &tmp))
	{
		if(output->value = (unsigned char *) LocalAlloc(LPTR, tmp.length))
		{
			RtlCopyMemory(output->value, tmp.value, tmp.length);
			output->length = tmp.length;
			status = TRUE;
		}
		kull_m_kerberos_asn1_helper_ossFreeBuf(tmp.value);
	}
	else PRINT_ERROR("%s", kull_m_kerberos_asn1_helper_ossGetErrMsg());

	return status;
}