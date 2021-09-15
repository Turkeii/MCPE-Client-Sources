#include "Velocity.h"

Velocity::Velocity() : IModule(0, Category::MOVEMENT, "No Knockback") {
	this->registerFloatSetting("Linear Modifier", &this->xModifier, this->xModifier, -50.f, 50.f);
	this->registerFloatSetting("Height Modifier", &this->yModifier, this->yModifier, -50.f, 50.f);
}

Velocity::~Velocity() {
}

const char* Velocity::getModuleName() {
	return ("Velocity");
}

void Velocity::onTick(C_GameMode* gm) {
}