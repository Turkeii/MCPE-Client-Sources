#include "AntiBot.h"

AntiBot::AntiBot() : IModule(0, Category::PLAYER, "Enable this module to filter bots!") {
	registerEnumSetting("Mode", &mode, 0);
	mode = SettingEnum(this)
				   .addEntry(EnumEntry("Basic", 0))
				   .addEntry(EnumEntry("Advance", 1));
	registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
	//registerBoolSetting("Name Check", &nameCheck, nameCheck);
	registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
	registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
	registerBoolSetting("Other Check", &otherCheck, otherCheck);
	registerBoolSetting("Extra Check", &extraCheck, extraCheck);
}

AntiBot::~AntiBot() {
}

const char* AntiBot::getModuleName() {
	return ("AntiBot");
}
const char* AntiBot::getModName() {
	if (mode.selected == 1) {
		return " [Advanced]";
	} else {
		return " [Basic]";
	}
}