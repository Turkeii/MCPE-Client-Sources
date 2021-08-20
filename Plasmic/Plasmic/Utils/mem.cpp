#include "mem.h"
#include <Psapi.h>



uintptr_t mem::mod;
HMODULE mem::g_hModule;
bool mem::isRunning;

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

void mem::writeBytes(uintptr_t location, BYTE* bytes, size_t amountOfBytes) {
	//Be sure that we can write to the memory
	DWORD oldProtect;
	VirtualProtect((LPVOID)location, amountOfBytes, PAGE_EXECUTE_READWRITE, &oldProtect);

	//Set the memory
	memcpy((void*)location, bytes, amountOfBytes);

	//restore the old protection
	DWORD noWarning;
	VirtualProtect((LPVOID)location, amountOfBytes, oldProtect, &noWarning);
}

void mem::readBytes(uintptr_t location, BYTE* bytes, size_t amountOfBytes) {
	//Set the memory
	memcpy(bytes, (void*)location, amountOfBytes);
}



void mem::nop(uintptr_t location, size_t amountOfBytes, BYTE* OriginalBytes) {

	if (OriginalBytes != nullptr) 
		readBytes(location, OriginalBytes, amountOfBytes);
	
	//Be sure that we can write to the memory
	DWORD oldProtect;
	VirtualProtect((LPVOID)location, amountOfBytes, PAGE_EXECUTE_READWRITE, &oldProtect);

	//write the nops
	memset((void*)location, 0x90, amountOfBytes);

	//restore the old protection
	DWORD noWarning;
	VirtualProtect((LPVOID)location, amountOfBytes, oldProtect, &noWarning);
}

uintptr_t mem::FindSignature(const char* szSignature) {
	const char* pattern = szSignature;
	uintptr_t firstMatch = 0;
	static const uintptr_t rangeStart = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
	static MODULEINFO miModInfo;
	static bool init = false;
	if (!init) {
		init = true;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	}
	static const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;

	BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;

	for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++) {
		if (!*pattern)
			return firstMatch;

		while (*(PBYTE)pattern == ' ')
			pattern++;

		if (!*pattern)
			return firstMatch;

		if (oldPat != pattern) {
			oldPat = pattern;
			if (*(PBYTE)pattern != '\?')
				patByte = GET_BYTE(pattern);
		}

		if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {
			if (!firstMatch)
				firstMatch = pCur;

			if (!pattern[2])
				return firstMatch;

			pattern += 2;
		} else {
			pattern = szSignature;
			firstMatch = 0;
		}
	}
	return NULL;
}

uintptr_t mem::FindSignatureInModule(const char* modName, const char* szSignature) {
	const char* pattern = szSignature;
	uintptr_t firstMatch = 0;
	const uintptr_t rangeStart = (uintptr_t)GetModuleHandleA(modName);
	MODULEINFO miModInfo;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;

	BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;

	for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++) {
		if (!*pattern)
			return firstMatch;

		while (*(PBYTE)pattern == ' ')
			pattern++;

		if (!*pattern)
			return firstMatch;

		if (oldPat != pattern) {
			oldPat = pattern;
			if (*(PBYTE)pattern != '\?')
				patByte = GET_BYTE(pattern);
		}

		if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {
			if (!firstMatch)
				firstMatch = pCur;

			if (!pattern[2])
				return firstMatch;

			pattern += 2;
		}
		else {
			pattern = szSignature;
			firstMatch = 0;
		}
	}
	return NULL;
}

uintptr_t mem::ResolvePointer(uint16_t* offsets, uint8_t offsetCount) {
	uintptr_t curr = mod + offsets[0];

	if (curr != NULL) 
		for (uint16_t i = 1; i < offsetCount; i++) {
			curr = *(uintptr_t*)(curr += offsets[i]);
			if (curr == NULL)
				return NULL;
		}
	
	return curr;
}


uintptr_t** mem::getVtable(void* object) {
	//convert the pointer to the object to a normal datatype pointer (uintptr_t in this case)
	//then we are at the start and the vtable is at the start so
	//it points to it already, just need to treat it as uintptr_t**
	return (uintptr_t**)(*(uintptr_t*)object);
}

void mem::ApplyVtable(void* object, uintptr_t** Vtable) {
	(*(uintptr_t*)object) = (uintptr_t)Vtable;
}