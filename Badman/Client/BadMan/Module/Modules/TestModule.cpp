#include "TestModule.h"

#include "../../../SDK/CCamera.h"

TestModule::TestModule() : IModule(0x0, Category::MISC, "For testing purposes") {
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return ("TestModule");
}

void TestModule::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void TestModule::onAttack(C_Entity* attackedEnt) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void TestModule::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void TestModule::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void TestModule::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void TestModule::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void TestModule::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void TestModule::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}