#include "Antikb.h"

Antikb::Antikb() : IModule(0, Category::MOVEMENT, "No knockback") {
	this->registerFloatSetting("Linear Modifier", &this->xMod, this->xMod, 0.f, 1.f);
	this->registerFloatSetting("Height Modifier", &this->yMod, this->yMod, 0.f, 1.f);
}

Antikb::~Antikb() {
}

const char* Antikb::getModuleName() {
	return ("Antikb");
}

void Antikb::onTick(C_GameMode* gm) {
}