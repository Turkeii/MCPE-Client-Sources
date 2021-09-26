#include "Teams.h"

Teams::Teams() : IModule(0, Category::COMBAT, "Don't attack team members! Dosnt work on most servers!") {
	registerBoolSetting("is allied", &this->alliedCheck, this->alliedCheck);
	registerBoolSetting("same color", &this->colorCheck, this->colorCheck);
	registerBoolSetting("large enough pp", &this->ppCheck, this->ppCheck);
}

Teams::~Teams() {
}

const char* Teams::getModuleName() {
	return ("Teams");
}
