#include "FluxSwing.h"

FluxSwing::FluxSwing() : IModule(0, Category::MOVEMENT, "Fall Down Fast") {
}

FluxSwing::~FluxSwing() {
}

const char* FluxSwing::getModuleName() {
	return "FastFall";
}
void* yeaaa;

void FluxSwing::onEnable() {
	if (yeaaa == nullptr)
		yeaaa = (void*)(FindSignature("C7 40 1C 00 00 00 00 48 83 C4 28"));
	Utils::nopBytes((unsigned char*)((uintptr_t)yeaaa), 7);
}

void FluxSwing::onDisable() {
	unsigned char* patch = (unsigned char*)"\xC7\x40\x1C\x00\x00\x00\x00";
	Utils::patchBytes((unsigned char*)((uintptr_t)yeaaa), patch, 7);
}