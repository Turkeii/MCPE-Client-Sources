#include "AntiBot.h"
#include "../pch.h"

using namespace std;
AntiBot::AntiBot() : IModule(0, Category::COMBAT, "Ignores anticheat generated NPCs") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Basic", 0);
	mode.addEntry("Advanced", 1);
	registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
	registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
	registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
	registerBoolSetting("Other Check", &otherCheck, otherCheck);
	registerBoolSetting("Extra Check", &extraCheck, extraCheck);
}

const char* AntiBot::getRawModuleName() {
	return "AntiBot";
}

const char* AntiBot::getModuleName() {
	if (mode.getSelectedValue() == 0) name = string("AntiBot ") + string(GRAY) + string("Basic");
	if (mode.getSelectedValue() == 1) name = string("AntiBot ") + string(GRAY) + string("Advanced");
	return name.c_str();
}
