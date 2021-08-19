#include "Teleport.h"

Teleport::Teleport() : IModule(0, Category::PLAYER, "Gach.") {
	//registerBoolSetting("Only Hand", &this->onlyHand, this->onlyHand);
	//registerBoolSetting("Test", &this->bypass, this->bypass); vec3_ti block = g_Data.getUUIDInstance()->getPointerStruct()->uuid;Reset
}

Teleport::~Teleport() {
}

const char* Teleport::getModuleName() {
	return "BlockReach";
}

void Teleport::onTick(C_GameMode* gm) {

}
