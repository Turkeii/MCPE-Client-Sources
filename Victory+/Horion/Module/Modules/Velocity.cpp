#include "Velocity.h"

Velocity::Velocity() : IModule(0, Category::MOVEMENT, "Don't ever take knockback again") {
	this->registerFloatSetting("Linear Modifier", &this->xModifier, this->xModifier, 0.f, 1.f);
	this->registerFloatSetting("Height Modifier", &this->yModifier, this->yModifier, 0.f, 1.f);
}

Velocity::~Velocity() {
}

const char* Velocity::getModName() {
	static char modName[30];
	sprintf_s(modName, 30, "%.2f, %.2f", xModifier, yModifier);
	return modName;
}

const char* Velocity::getModuleName() {
	return ("Velocity");
}
