#include "Teams.h"
#include "../pch.h"

Teams::Teams() : IModule(0, Category::COMBAT, "Automatically friends everyone on your team") {
	registerBoolSetting("Allied", &alliedCheck, alliedCheck);
	registerBoolSetting("Color", &colorCheck, colorCheck);
}

const char* Teams::getModuleName() {
	return ("Teams");
}
