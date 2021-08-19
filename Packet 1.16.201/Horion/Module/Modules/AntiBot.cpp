#include "AntiBot.h"

AntiBot::AntiBot() : IModule(0, Category::PLAYER, "Enable this module to filter bots!") {
	registerBoolSetting("Invisible Check", &this->invisibleCheck, this->invisibleCheck);
	registerBoolSetting("EntityID Check", &this->entityIdCheck, this->entityIdCheck);
	registerBoolSetting("Hitbox Check", &this->hitboxCheck, this->hitboxCheck);
	registerBoolSetting("Other Check", &this->otherCheck, this->otherCheck);
	registerBoolSetting("Extra Check", &this->extraCheck, this->extraCheck);
	registerBoolSetting("Name Check", &this->nameCheck, this->nameCheck);
}

AntiBot::~AntiBot() {
}

const char* AntiBot::getModuleName() {
	return ("AntiBot");
}
