#include "HighJump.h"

HighJump::HighJump() : IModule(0, Category::MOVEMENT, "Jump higher than ever before"){
	this->registerFloatSetting("range", &this->jumpPower, this->jumpPower, 2.f, 20.f);
}

HighJump::~HighJump() {
}

const char* HighJump::getModuleName() {
	return "HighJump";
}
void HighJump::onEnable() {
}
void HighJump::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
}
void HighJump::onDisable() {
	auto player = g_Data.getLocalPlayer();
}
