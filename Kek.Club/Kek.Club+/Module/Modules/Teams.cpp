#include "Teams.h"

Teams::Teams() : IModule(0, Category::PLAYER, "Don't attack team members!") {
	registerBoolSetting("is allied", &alliedCheck, alliedCheck);
	registerBoolSetting("same color", &colorCheck, colorCheck);
}

Teams::~Teams() {
}

const char* Teams::getModuleName() {
	return ("Teams");
}
