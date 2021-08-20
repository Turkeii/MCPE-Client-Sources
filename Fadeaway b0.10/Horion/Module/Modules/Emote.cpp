#include "Emote.h"

Emote::Emote() : IModule(0x0, Category::MISC, "4x All Actions, Server Sided - Credits: eKowz") {
}

Emote::~Emote() {
}

const char* Emote::getModuleName() {
	return ("4xPacket");
}