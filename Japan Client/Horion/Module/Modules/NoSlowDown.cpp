#include "NoSlowDown.h"

#include <Windows.h>

#include "../../../Utils/Logger.h"
#include "../../../Utils/Utils.h"

NoSlowDown::NoSlowDown() : IModule(0, Category::VISUAL, "Makes your swing animation looks like flux (a java client)") {
}

NoSlowDown::~NoSlowDown() {
}

const char* NoSlowDown::getModuleName() {
	return ("FluxSwing");
}
void* targetAddress;
void patchBytes(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}
void NoSlowDown::onEnable() {
	if (targetAddress == nullptr)
		targetAddress = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 46 40 48 85 C0");
	BYTE* patch = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
	//patchBytes((BYTE*)((uintptr_t)targetAddress), patch, 6);
}
void NoSlowDown::onDisable() {
	BYTE* patch = (BYTE*)"\x0F\x84\x83\x02\x00\x00\x48\x8B\x46\x40\x48\x85\xC0";
	//patchBytes((BYTE*)((uintptr_t)targetAddress), patch, 6);
}
