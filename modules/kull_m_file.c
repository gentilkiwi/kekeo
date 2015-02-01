/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#include "kull_m_file.h"

BOOL kull_m_file_writeData(PCSTR fileName, LPCVOID data, DWORD lenght)
{
	BOOL reussite = FALSE;
	DWORD dwBytesWritten = 0;
	HANDLE hFile = NULL;
	
	if((hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) && hFile != INVALID_HANDLE_VALUE)
	{
		if(WriteFile(hFile, data, lenght, &dwBytesWritten, NULL) && (lenght == dwBytesWritten))
			reussite = FlushFileBuffers(hFile);
		CloseHandle(hFile);
	}
	return reussite;
}

BOOL kull_m_file_readData(PCSTR fileName, PBYTE * data, PDWORD lenght)	// for little files !
{
	BOOL reussite = FALSE;
	DWORD dwBytesReaded;
	LARGE_INTEGER filesize;

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile && hFile != INVALID_HANDLE_VALUE)
	{
		if(GetFileSizeEx(hFile, &filesize) && !filesize.HighPart)
		{
			*lenght = filesize.LowPart;
			if(*data = (PBYTE) LocalAlloc(LPTR, *lenght))
			{
				if(!(reussite = ReadFile(hFile, *data, *lenght, &dwBytesReaded, NULL) && (*lenght == dwBytesReaded)))
					LocalFree(*data);
			}
		}
		CloseHandle(hFile);
	}
	return reussite;
}