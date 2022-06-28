#include "NoPush.h"

NoPush::NoPush() : IModule(0, Category::COMBAT, "Don't Get Pushed Around By Liquids") {
}

NoPush::~NoPush() {
}

const char* NoPush::getModuleName() {
	return "GhostHand";
}
void* target;

void NoPush::onEnable() {
	target = (void*)(FindSignature("76 0F C6 44 24 50 01"));

	Utils::nopBytes((unsigned char*)((uintptr_t)target), 7);
}

void NoPush::onDisable() {
	unsigned char* patch = (unsigned char*)"\x76\x0F\xC6\x44\x24\x50\x01";
	Utils::patchBytes((unsigned char*)((uintptr_t)target), patch, 7);
}
