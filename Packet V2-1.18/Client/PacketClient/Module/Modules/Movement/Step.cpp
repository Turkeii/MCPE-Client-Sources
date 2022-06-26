#include "Step.h"
#include "../pch.h"

using namespace std;
Step::Step() : IModule(0, Category::MOVEMENT, "Increases your step height") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Vanilla", 0);
	mode.addEntry("None", 1);
	registerBoolSetting("Reverse", &reverse, reverse);
	registerFloatSetting("Height", &height, height, 1.f, 2.f);
}

const char* Step::getRawModuleName() {
	return "Step";
}

const char* Step::getModuleName() {
	if (mode.getSelectedValue() == 0) name = string("Step ") + string(GRAY) + to_string((int)height) + string(".") + to_string((int)(height * 10) - ((int)height * 10));
	if (mode.getSelectedValue() == 1) {
		if (reverse) name = string("Step ") + string(GRAY) + string("Reverse");
		else return "Step";
	}
	return name.c_str();
}

void Step::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (mode.getSelectedValue() == 0) player->stepHeight = height; // nORmal
	else g_Data.getLocalPlayer()->stepHeight = 0.5625f;

	if (reverse && player->onGround && !player->isInWater() && !player->isInLava() && !moduleMgr->getModule<Jesus>()->foundWater)
		player->velocity.y = -1.f;
}

void Step::onMove(C_MoveInputHandler* input) {
}

void Step::onDisable() {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	player->stepHeight = 0.5625f;
}