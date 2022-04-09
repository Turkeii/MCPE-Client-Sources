#include "AntiBot.h"

AntiBot::AntiBot() : IModule(0, Category::PLAYER, "Filter bots") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Basic", 0);
	mode.addEntry("Advanced", 1);
	registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
	registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
	registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
	registerBoolSetting("Other Check", &otherCheck, otherCheck);
	registerBoolSetting("Extra Check", &extraCheck, extraCheck);
}

AntiBot::~AntiBot() {
}

const char* AntiBot::getRawModuleName() {
	return "AntiBot";
}

const char* AntiBot::getModuleName() {
	if (mode.getSelectedValue() == 0) {
		name = std::string("AntiBot ") + std::string(GRAY) + std::string("Basic");
		return name.c_str();
	} else if (mode.getSelectedValue() == 1) {
		name = std::string("AntiBot ") + std::string(GRAY) + std::string("Advanced");
		return name.c_str();
	}
}
