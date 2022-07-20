#include "PacketMine.h"

PacketMine::PacketMine() : IModule(VK_NUMPAD4, Category::WORLD, "Break packet in world") {
	//	this->registerIntSetting("PacketDelay", &this->InstaDelay, this->InstaDelay, 0.f, 10.f);
}

PacketMine::~PacketMine() {
}

const char* PacketMine::getModuleName() {
	return ("PacketMine");
}
