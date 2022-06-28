#pragma region includes
#include "AirJump.h"

#include <Windows.h>

#include "../../../Utils/Logger.h"
#include "../../../Utils/Utils.h"
#pragma endregion

AirJump::AirJump() : IModule('G', Category::MOVEMENT, "Jump even you're not on the ground") {
}

AirJump::~AirJump() {
}

const char* AirJump::getModuleName() {
	return ("AirJump");
}

void* yeaaaa;

void AirJump::onEnable() {
	if (yeaaaa == nullptr)
		yeaaaa = (void*)(FindSignature("0f b6 80 ? ? ? ? c3 cc cc cc cc 48 8b 41 ? f3 0f 11 88"));
	Utils::nopBytes((unsigned char*)((uintptr_t)yeaaaa), 7);
}

void AirJump::onDisable() {
	unsigned char* patch = (unsigned char*)"\x0f\xb6\x80\xD8\x01\x00\x00\xc3\xcc\xcc\xcc\xcc\x48\x8b\x41\x10\xf3\x0f\x11\x88";
	Utils::patchBytes((unsigned char*)((uintptr_t)yeaaaa), patch, 7);
}
