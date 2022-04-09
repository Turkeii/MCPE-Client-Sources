#include "Packet.h"

Packet::Packet() : IModule(0, Category::EXPLOIT, "Multiply/Cancel all actions server sided") {
	registerBoolSetting("NoPacket", &noPacket, noPacket);
	registerBoolSetting("Multiply", &multiply, multiply);
	registerIntSetting("MultiplyValue", &multipltBy, multipltBy, 2, 10);
	//registerBoolSetting("Multiply4x", &fourx, fourx);
}

Packet::~Packet() {
}

const char* Packet::getRawModuleName() {
	return "Packet";
}

const char* Packet::getModuleName() {
	if (multiply) {
		name = std::string("Packet ") + std::string(GRAY) + std::string("Multiply");
		return name.c_str();
	} else if (!multiply) {
		return "Packet";
	}
}

bool Packet::allowAutoStart() {
	return false;
}

void Packet::onEnable() {
	if (!g_Data.isInGame())
		setEnabled(false);
}