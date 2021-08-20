#pragma once
#include <Windows.h>
#include <cstdint>

namespace mem {
extern HMODULE g_hModule;
extern uintptr_t mod;
extern bool isRunning;


	void writeBytes(uintptr_t location, BYTE* bytes, size_t amountOfBytes);
	//Will write the bytes in "bytes", be sure that there is enough room.
	void readBytes(uintptr_t location, BYTE* bytes, size_t amountOfBytess);

	
	//Original bytes can be null if you don't need them
	void nop(uintptr_t location, size_t amountOfBytes, BYTE* OriginalBytes = NULL);

	//Use this to find paterns in memory, you can use ??
	uintptr_t FindSignature(const char* Signature);
	uintptr_t FindSignatureInModule(const char* modName, const char* szSignature);

	///Use this if you want to resolve a pointer
	///will return 0 if a part of the path is null
	uintptr_t ResolvePointer(uint16_t* offsets, uint8_t offsetCount);

	//will return the vtable of an object
	uintptr_t** getVtable(void* object);
	//will set the vtable of an object
	void ApplyVtable(void* object, uintptr_t** Vtable);
}