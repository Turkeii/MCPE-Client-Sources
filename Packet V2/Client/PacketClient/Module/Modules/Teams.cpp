#include "Teams.h"

Teams::Teams() : IModule(0, Category::COMBAT, "Don't attack team members!") {
	registerBoolSetting("Server", &this->alliedCheck, this->alliedCheck);
	registerBoolSetting("Color", &this->colorCheck, this->colorCheck);
}

Teams::~Teams() {
}

const char* Teams::getModuleName() {
	return ("Teams");
}
