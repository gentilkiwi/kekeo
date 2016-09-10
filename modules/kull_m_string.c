/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include "kull_m_string.h"

wchar_t * kull_m_string_qad_ansi_to_unicode(const char * ansi)
{
	wchar_t * buffer = NULL;
	if(ansi)
		buffer = kull_m_string_qad_ansi_c_to_unicode(ansi, strlen(ansi));
	return buffer;
}

wchar_t * kull_m_string_qad_ansi_c_to_unicode(const char * ansi, SIZE_T szStr)
{
	wchar_t * buffer = NULL;
	SIZE_T i;

	if(ansi && szStr)
		if(buffer = (wchar_t *) LocalAlloc(LPTR, (szStr + 1) * sizeof(wchar_t)))
			for(i = 0; i < szStr; i++)
				buffer[i] = ansi[i];
	return buffer;
}

BOOL kull_m_string_stringToHex(IN LPCSTR string, IN LPBYTE hex, IN DWORD size)
{
	DWORD i, j;
	BOOL result = (strlen(string) == (size * 2));
	if(result)
	{
		for(i = 0; i < size; i++)
		{
			sscanf_s(&string[i*2], "%02x", &j);
			hex[i] = (BYTE) j;
		}
	}
	return result;
}

PCSTR PRINTF_TYPES[] =
{
	"%02x",		// PRINTF_HEX_SHORT
	"%02x ",	// PRINTF_HEX_SPACE
	"0x%02x, ",	// PRINTF_HEX_C
	"\\x%02x",	// PRINTF_HEX_PYTHON
};

void kull_m_string_printf_hex(LPCVOID lpData, DWORD cbData, DWORD flags)
{
	DWORD i, sep;
	PCSTR pType = PRINTF_TYPES[flags & 0x0000000f];
	sep = flags >> 16;

	for(i = 0; i < cbData; i++)
	{
		kprintf(pType, ((LPCBYTE) lpData)[i]);
		if(sep && !((i+1) % sep))
			kprintf("\n");
	}
}

void kull_m_string_displayFileTime(IN PFILETIME pFileTime)
{
	SYSTEMTIME st;
	char buffer[0xff];
	if(pFileTime)
	{
		if(FileTimeToSystemTime(pFileTime, &st ))
		{
			if(GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, NULL, buffer, ARRAYSIZE(buffer)))
			{
				kprintf("%s ", buffer);
				if(GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, NULL, buffer, ARRAYSIZE(buffer)))
					kprintf("%s", buffer);
			}
		}
	}
}

void kull_m_string_displayLocalFileTime(IN PFILETIME pFileTime)
{
	FILETIME ft;
	if(pFileTime)
		if(FileTimeToLocalFileTime(pFileTime, &ft))
			kull_m_string_displayFileTime(&ft);
}

BOOL kull_m_string_LocalFileTimeToString(IN PFILETIME pFileTime, OUT CHAR string[14 + 1])
{
	BOOL status = FALSE;
	FILETIME ft;
	SYSTEMTIME st;
	if(pFileTime)
		if(FileTimeToLocalFileTime(pFileTime, &ft))
			if(FileTimeToSystemTime(&ft, &st))
				if(GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, "yyyyMMdd", string, 8 + 1))
					status = GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, "HHmmss", string + 8, 6 + 1);
	return status;
}

void kull_m_string_displaySID(IN PSID pSid)
{
	LPSTR stringSid;
	if(ConvertSidToStringSid(pSid, &stringSid))
	{
		kprintf("%s", stringSid);
		LocalFree(stringSid);
	}
	else PRINT_ERROR_AUTO("ConvertSidToStringSid");
}

PWSTR kull_m_string_getRandomGUID()
{
	UNICODE_STRING uString;
	GUID guid;
	PWSTR buffer = NULL;
	if(NT_SUCCESS(UuidCreate(&guid)))
	{
		if(NT_SUCCESS(RtlStringFromGUID(&guid, &uString)))
		{
			if(buffer = (PWSTR) LocalAlloc(LPTR, uString.MaximumLength))
				RtlCopyMemory(buffer, uString.Buffer, uString.MaximumLength);
			RtlFreeUnicodeString(&uString);
		}
	}
	return buffer;
}

BOOL kull_m_string_args_byName(const int argc, const char * argv[], const char * name, const char ** theArgs, const char * defaultValue)
{
	BOOL result = FALSE;
	const char *pArgName, *pSeparator;
	SIZE_T argLen, nameLen = strlen(name);
	int i;
	for(i = 0; i < argc; i++)
	{
		if((strlen(argv[i]) > 1) && ((argv[i][0] == '/') || (argv[i][0] == '-')))
		{
			pArgName = argv[i] + 1;
			if(!(pSeparator = strchr(argv[i], ':')))
				pSeparator = strchr(argv[i], '=');

			argLen =  (pSeparator) ? (pSeparator - pArgName) : strlen(pArgName);
			if((argLen == nameLen) && _strnicmp(name, pArgName, argLen) == 0)
			{
				if(theArgs)
				{
					if(pSeparator)
					{
						*theArgs = pSeparator + 1;
						result = *theArgs[0] != L'\0';
					}
				}
				else
					result = TRUE;
				break;
			}
		}
	}

	if(!result && theArgs && defaultValue)
	{
		*theArgs = defaultValue;
		result = TRUE;
	}

	return result;
}

BOOL kull_m_string_copy(LPSTR *dst, LPCSTR src)
{
	BOOL status = FALSE;
	size_t size;
	if(src && dst && (size = strlen(src)))
	{
		size = (size + 1);
		if(*dst = (LPSTR) LocalAlloc(LPTR, size))
		{
			RtlCopyMemory(*dst, src, size);
			status = TRUE;
		}
	}
	return status;
}