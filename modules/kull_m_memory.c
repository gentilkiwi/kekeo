/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kull_m_memory.h"

PVOID kull_m_memory_search(IN LPCVOID Pattern, IN SIZE_T PatternSize, IN LPCVOID Start, IN SIZE_T Size)
{
	BOOL status = FALSE;
	PBYTE Result = NULL, CurrentPtr, limite = (PBYTE) Start + Size;
	for(CurrentPtr = (PBYTE) Start; !status && (CurrentPtr + PatternSize <= limite); CurrentPtr++)
		status = RtlEqualMemory(Pattern, CurrentPtr, PatternSize);
	if(status)
		Result = CurrentPtr - 1;
	return Result;
}