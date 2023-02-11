#include "../../ModuleManager.h"
#include "TestModule.h"
#include <iomanip>
#include <chrono>
#include <string>
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <direct.h>
#include <conio.h>
#include <sstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <TlHelp32.h>
#include <tchar.h> 
#include <vector>
#include <thread>
#include <wtsapi32.h>
#include <psapi.h>
#include <math.h>
#include <algorithm> 
#include <playsoundapi.h>
#include <windows.h>
#include <tchar.h>
#include <urlmon.h>
#include "../pch.h"

using namespace std;
TestModule::TestModule() : IModule(0, Category::OTHER, "For testing purposes") {
	registerBoolSetting("Notification", &notification, notification);
	registerBoolSetting("DebugInfo", &debugInfo, debugInfo);
	registerBoolSetting("TestSound", &test2, test2);
	registerBoolSetting("CopyChat", &copyChatMessages, copyChatMessages);
	registerBoolSetting("Blink", &blink, blink);
	registerBoolSetting("Test", &test, test);
	registerBoolSetting("AutoDisable", &autoDisable, autoDisable);
	registerFloatSetting("SliderX", &sliderX, sliderX, -40.f, 40.f);
	registerFloatSetting("SliderY", &sliderY, sliderY, -40.f, 40.f);
	registerFloatSetting("SliderZ", &sliderZ, sliderZ, -40.f, 40.f);
	registerFloatSetting("SliderX2", &sliderX2, sliderX2, -4.f, 4.f);
	registerFloatSetting("SliderY2", &sliderY2, sliderY2, -4.f, 4.f);
	registerFloatSetting("SliderZ2", &sliderZ2, sliderZ2, -4.f, 4.f);
	registerBoolSetting("Kow", &kowBool, kowBool);
	registerFloatSetting("KowFloat", &kowFloat, kowFloat, 1.f, 100.f);
}

const char* TestModule::getModuleName() {
	return "TestModule";
}

static vector<C_Entity*> targetList;
void findEntity_TestModule(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

	if (currentEntity->getEntityTypeId() == 80)  // Arrows
		return;

	if (!TargetUtil::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() == 1677999)  // Villager
		return;

	if (currentEntity->getEntityTypeId() == 51)  // NPC
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) targetList.push_back(currentEntity);
}

void TestModule::onEnable() {
	/*auto blinkMod = moduleMgr->getModule<Blink>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	targetList.clear();

	if (notification) {
		NotificationManager notification;
		// idk it wont edik
		notification.addNotification("Title", "Message");
	}
	if (blink) testCounter = 0;

	initPos = *player->getPos();
	tick = 0;
	*/
}

void TestModule::onTick(C_GameMode* gm) {
	/*C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto blinkMod = moduleMgr->getModule<Blink>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (input == nullptr) return;
	tick++;

	float calcYaw = (gm->player->yaw + 90) * (PI / 180);

	targetList.clear();
	g_Data.forEachEntity(findEntity_TestModule);

	if (test) {
		//MoveUtil::setSpeed(1.f);
		/*static int testTick = 0;
		testTick++;

		if (testTick == 20) {
			clientMessageF("sent");
			CommandRequestPacket commandPacket;
			commandPacket.payload = string("q sky");
			commandPacket.one = 1;
			commandPacket.two = 2;
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&commandPacket);
		}
		else if (testTick == 21) testTick = 0;

		// testing random shit
	}

	if (blink) {
		if (testCounter == 60) {
			blinkMod->setEnabled(false);
			testCounter = 1;
		}
		else {
			testCounter++;
		}
		if (testCounter == 2) {
			blinkMod->setEnabled(true);
		}
	}

	if (GameData::isKeyDown(*input->sneakKey) && kowBool) g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	setEnabled(!autoDisable);*/
}

void TestModule::onMove(C_MoveInputHandler* input) {
}

void TestModule::onPlayerTick(C_Player* plr) {
	if (plr == nullptr) return;

	PointingStruct* level = plr->pointingStruct;
	vec3_t* pos = plr->getPos();

	static bool shouldFly = false;
	if (plr->damageTime >= 1) shouldFly = true;

	if (!shouldFly) {
		//MoveUtil::freeze(initPos, false);
	}

	//for (auto& i : targetList) {
		//targetList[0]->spawnDustParticles(100);
	//}
	//plr->spawnDustParticles(10000);
	//level->playSound("game.player.hurt", *pos, 1, 1); plr->animateHurt();
}

void TestModule::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	/*auto hudMod = moduleMgr->getModule<Interface>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	targetList.clear();


	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	if (kowBool) {
		string Text = "Player";
		MC_Color CumColor = MC_Color(255, 255, 255); // lol
		if (g_Data.canUseMoveKeys()) {
			int ySize = 0;
			int ind = 1;
			ind++;
			int curIndex = -ind * 75;
			auto FunkyColor = ColorUtil::waveColor(hudMod->r, hudMod->g, hudMod->b, hudMod->r2, hudMod->g2, hudMod->b2, curIndex * 2);
			float TextWidth = DrawUtils::getTextWidth(&Text, 1) + 6.5;
			vec4_t RectPos = vec4_t(4.f, 12.f + 1, TextWidth + 52.f, 12.f + 13);//Start X, Positive Y Height, how long to make width going right, bg negative y height
			vec4_t SeparaterPos = vec4_t(4.f, RectPos.y + 11, TextWidth + 52.f, RectPos.w + 1.f);
			vec2_t TextPos = vec2_t(RectPos.x + 2, RectPos.y + 3.5);

			DrawUtils::fillRectangleA(RectPos, MC_Color(0, 0, 0, 150));
			DrawUtils::fillRectangleA(SeparaterPos, FunkyColor);
			DrawUtils::drawText(TextPos, &Text, CumColor, .7f, 1);//Player Label

			for (auto& i : targetList) {
				ySize += 10;
				string EnemyIgn = i->getNameTag()->getText();
				vec2_t EnemyName = vec2_t(RectPos.x + 2, SeparaterPos.y + (3.5 + ySize));

				DrawUtils::drawText(EnemyName, &EnemyIgn, CumColor, .7f, 1);
			}
		}
	}
	else {
		vec2_t targetPosition = vec2_t(200, 200);
		vec2_t position = vec2_t(10, 10);
		position.x = lerp(position.x, targetPosition.x, 0.1f);

		string textStr = "Test";
		DrawUtils::drawGradientText(position, &textStr, 1, 255);
		//DrawUtils::fillRectangleA(vec4_t(10, 10, 50, 50), MC_Color(255, 255, 255, 255));
	}*/
	//so far can only get rendering from minecraft files
	//DrawUtils::drawImage("textures/ui/promo_creeper.png", vec2_t(100, 100), vec2_t(800, 100), vec2_t(0.f, 0.f), vec2_t(1.f, 1.f) , MC_Color(0.f, 0.f, 1.f));
	//DrawUtils::flushImage();
	auto i = ColorUtil::interfaceColor(1);
	DrawUtils::drawImage("textures/ui/promo_creeper.png", vec2_t(200, 200), vec2_t(100, 100), vec2_t(0.f, 0.f), vec2_t(1.f, 1.f) , i);
	string lol = "Custom String";
	DrawUtils::drawGradientText(vec2_t(100, 100), &lol, 10.f, 1, true);
}

void TestModule::onSendPacket(C_Packet * packet) {
	/*auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (g_Data.canUseMoveKeys()) {
		if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			if (tick <= 10) {
				clientMessageF("dam");
				if (player->onGround) movePacket->Position.y -= 2.f;
			}
		}
	}*/
}

void TestModule::onDisable() {
	/*
	auto blinkMod = moduleMgr->getModule<Blink>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	if (blink) blinkMod->setEnabled(false);
	*/
}