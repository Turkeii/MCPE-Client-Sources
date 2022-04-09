#include "../../Module/ModuleManager.h"
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
#include<TlHelp32.h>
#include <tchar.h> 
#include <vector>
#include <thread>
#include <wtsapi32.h>
#include <psapi.h>
#include <math.h>
#include <algorithm> 
#include <playsoundapi.h>
#include<windows.h>
#include <tchar.h>
#include <urlmon.h>

TestModule::TestModule() : IModule(0, Category::MISC, "Description") {
	registerBoolSetting("AlertBox", &alertBox, alertBox);
	registerBoolSetting("Teleport", &istpMode, istpMode);
	//registerBoolSetting("Teleport2", &istpModeTwo, istpModeTwo);
	registerBoolSetting("Damage", &dmgMode, dmgMode);
	registerBoolSetting("Blink", &blink, blink);
	registerBoolSetting("TestSong", &test, test);
	registerBoolSetting("TestSound", &test2, test2);
	registerBoolSetting("AutoDisable", &autoDisable, autoDisable);
	registerFloatSetting("SliderX", &sliderX, sliderX, -80, 80);
	registerFloatSetting("SliderY", &sliderY, sliderY, -20, 20);
	registerFloatSetting("SliderZ", &sliderZ, sliderZ,  -40, 40);
	registerBoolSetting("Kow", &kowBool, kowBool);
	registerFloatSetting("KowFloat", &kowFloat, kowFloat, 0.2f, 10.f);
}

const char* TestModule::getModuleName() {
	return "TestModule";
}

void TestModule::onEnable() {
	auto blinkMod = moduleMgr->getModule<Blink>();
	auto speed = moduleMgr->getModule<Speed>();
	auto player = g_Data.getLocalPlayer();
	if (g_Data.getLocalPlayer() == nullptr)
		setEnabled(false);
	if (banUMode) {
		if (counter == 5) {
			counter = 0;
		}
		else {
			counter++;
			*g_Data.getClientInstance()->minecraft->timer = 2.f;
			//auto bhopMod = moduleMgr->getModule<Bhop>();
			vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

			vec3_t pos;
			if (counter >= 0) {
				pos.x = 0.00000000000005f;
				pos.y = -0.000000000000001f + pPos.y;
				pos.z = 0.00000000000005f;
				g_Data.getLocalPlayer()->setPos(pos);
			}
		}
	}

	if (alertBox) {
		auto box = g_Data.addNotification("Test Module:", "Notification");
		box->duration = 100;
	}
	if (dmgMode) {
		auto speedMod = moduleMgr->getModule<Speed>();
		speedMod->setEnabled(false);
	}
	if (dmgMode) {
		vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

		vec3_t pos;
		pos.x = 0.f + pPos.x;
		pos.y = 4.5f + pPos.y;
		pos.z = 0.f + pPos.z;

		g_Data.getLocalPlayer()->setPos(pos);
		*g_Data.getClientInstance()->minecraft->timer = 6000.f;
	}
	if (blink)
		testCounter = 0;

	if (kowBool) {
		kowBool2 = true;
		blinkMod->setEnabled(true);
		kowInt2 = 0;
		kowInt1 = 0;
		if (player->onGround)
			player->jumpFromGround();
	}
	if (test) {
		//PlaySoundA((LPCSTR)("C:\\Users\\ggpac\\AppData\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\PacketClient\\Assets\\Sounds\\song.wav"), NULL, SND_FILENAME | SND_ASYNC);
		counter = 0;
		sliderX = -5;
	}
	if (test2) { 
	//PlaySoundA((LPCSTR)("C:\\Users\\ggpac\\AppData\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\PacketClient\\Assets\\Sounds\\sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

bool TestModule::isFlashMode() {
		return false;
}

void TestModule::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (input == nullptr) return;
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	auto player = g_Data.getLocalPlayer();
	auto blinkMod = moduleMgr->getModule<Blink>();
	if (autoDisable) {
		auto testmoduleMod = moduleMgr->getModule<TestModule>();
		if (testmoduleMod->isEnabled()) {
			*g_Data.getClientInstance()->minecraft->timer = 20.f;
			testmoduleMod->setEnabled(false);
		}
	}
	if (blink) {
		if (testCounter == 60) {
			blinkMod->setEnabled(false);
			testCounter = 1;
		} else {
			testCounter++;
		}
		if (testCounter == 2) {
			blinkMod->setEnabled(true);
		}
	}
	if (test) {
		//g_Data.getLocalPlayer()->setGameModeType(3);
		//auto player = g_Data.getLocalPlayer();
		//player->velocity.x = 6.f;
		//player->velocity.y = 7.f;
		//*g_Data.getClientInstance()->minecraft->timer = 20.f;
		//player->velocity.z = 5.f;
		//player->animateHurt();
		//player->setSleeping(true);
		//player->setSleeping(true);
		//player->updateWalkAnim();
		//player->getAttackAnim(1);
		//player->setSize(300, 0);
		//if (player->isInWater()) {
		//gm->player->onGround = true;
		//gm->player->velocity.y = 1;
		//}
		/*auto flight = moduleMgr->getModule<Flight>();
		auto speed = moduleMgr->getModule<Speed>();
		auto freetp = moduleMgr->getModule<FreeTP>();
		auto longjump = moduleMgr->getModule<LongJump>();
		for (int i = 0; i < 50; i++) {
			if (counter == 8) {
				counter = 1;
			} else {
				counter++;
			}

			if (counter == 2) {
				flight->setEnabled(true);
			} else if (counter == 3) {
				flight->setEnabled(false);
			} else if (counter == 5) {
				longjump->setEnabled(true);
			} else if (counter == 7) {
				longjump->setEnabled(false);
			}
			//clientMessageF("hi");
		}*/
		//vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

		//	vec3_t pos;
		//pos.x = 0.f + pPos.x;
		//pos.y = 300.f + pPos.y;
		//pos.z = 0.f + pPos.z;

		//g_Data.getLocalPlayer()->setPos(pos);
		//player->startSpinAttack();
		//player->actuallyHurt(1, player, true);
		//C_LocalPlayer* localHost = g_Data.getLocalPlayer();
		//g_Data.getLocalPlayer()->setGameModeType(1);
		//if (legacyMode) {
		//gm->player->onGround = true;
		//return;
		//}
		/*C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		float calcYaw = (gm->player->yaw + 90) * (PI / 180);

		counter++;

		vec3_t pos = *g_Data.getLocalPlayer()->getPos();
		pos.y += 0.1f;
		C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
		pos.y -= 0.1f;
		C_MovePlayerPacket a2(g_Data.getLocalPlayer(), pos);
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a2);

			static auto flight = moduleMgr->getModule<Flight>();
		vec3_t moveVec;
			moveVec.x = cos(calcYaw) * 0.0001;
		moveVec.z = sin(calcYaw) * 0.0001;

		gm->player->lerpMotion(moveVec);

		if (counter >= 3) {
			counter = 0;
			float yaw = gm->player->yaw * (PI / 180);
			float length = 0.f;

			float x = -sin(yaw) * length;
			float z = cos(yaw) * length;

			gm->player->setPos(pos.add(vec3_t(x, 1.f, z)));
		}*/
		//std::string msg = "AAAAAAAAA fuck";
		//if (!(sliderX >= 400)) sliderX++;
		//for (float x = sliderX; x++; sliderX++) {
		//}
		/*vec3_t* pos = gm->player->getPos();
		auto player = g_Data.getLocalPlayer();
		vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;
		blockBelow.y == g_Data.getLocalPlayer()->height;
			if (player->region->getBlock(vec3_t{blockBelow})->toLegacy()->blockId == 30) {
				clientMessageF("cobweb");
		}*/
		/*vec3_t* pos = gm->player->getPos();
		bool isOverVoid = false;
		for (int x = (int)pos->x - 1; x < pos->x + 1; x++) {
			for (int z = (int)pos->z - 1; z < pos->z + 1; z++) {
				for (int y = (int)pos->y - 255; y < pos->y + 0; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
					int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

					if (id != 0) isOverVoid = false;
					else isOverVoid = true;
				}
			}
		}
		if (isOverVoid) {
			clientMessageF("void!!!");
		}*/
		//g_Data.getClientInstance()->dimension->weather->isRaining = true;
	}
			if (istpMode) {
				auto player = g_Data.getLocalPlayer();
				C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
				float yaw = player->yaw;
				if (input->forwardKey && input->backKey && input->rightKey && input->leftKey) {
					gm->player->velocity = vec3_t(0, 0, 0);
				}
			}

			if (kowBool && kowBool2 && kowInt2 <= 3) {
				kowInt1++;
				if (kowInt1 >= 6 && kowInt1 <= 7) {
					blinkMod->setEnabled(false);
					*g_Data.getClientInstance()->minecraft->timer = 4;
				}
				if (kowInt1 >= 8) {
					kowInt1 = 0;
					blinkMod->setEnabled(true);
					kowInt2++;
					*g_Data.getClientInstance()->minecraft->timer = 20;
				}
			}
			if (kowInt2 >= 3) {
				blinkMod->setEnabled(false);
				kowBool2 = false;
				kowInt1 = 0;
				kowInt2 = 0;
				*g_Data.getClientInstance()->minecraft->timer = 20;
			}
			if (GameData::isKeyDown(*input->sneakKey) && kowBool)
				g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
			if (kowBool) {
				if (g_Data.canUseMoveKeys()) {
					if (GameData::isKeyDown(*input->spaceBarKey))
						glideModEffective += kowFloat;
					if (GameData::isKeyDown(*input->sneakKey))
						glideModEffective -= kowFloat;
				}

				float yaw = player->yaw;
				if (input->forwardKey && input->backKey && input->rightKey && input->leftKey)
					gm->player->velocity = vec3_t(0.f, -.0001f, -0.f);
				gm->player->velocity.y = glideModEffective-0.0001f;
				glideModEffective = glideMod;
			}
		}

void TestModule::onMove(C_MoveInputHandler* input) {
	if (istpMode) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * tpSpeed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * tpSpeed;
		if (pressed) player->lerpMotion(moveVec);
	}

	if (kowBool) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * kowFloat;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * kowFloat;
		if (pressed) player->lerpMotion(moveVec);
		if (g_Data.getLocalPlayer()->velocity.squaredxzlen() > 0.01) {
			C_MovePlayerPacket p = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(moveVec.x / 1.3f, 0.f, moveVec.z / 1.3f)));
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			C_MovePlayerPacket p2 = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(player->velocity.x / 1.3f, 0.f, player->velocity.z / 2.3f)));
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p2);
		}
	}
}

void TestModule::onDisable() {
	auto blinkMod = moduleMgr->getModule<Blink>();
	auto flight = moduleMgr->getModule<Flight>();
	auto player = g_Data.getLocalPlayer();
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	if (istpMode) {
			if (!player->onGround) {
				player->velocity.x = 0.f;
				player->velocity.z = 0.f;
			}
		}
	if (test) {
			auto speed = moduleMgr->getModule<Speed>();
			auto freetp = moduleMgr->getModule<FreeTP>();
			flight->setEnabled(false);
			speed->setEnabled(false);
			freetp->setEnabled(false);
		//g_Data.getLocalPlayer()->setGameModeType(0);
	}
	if (blink)
		blinkMod->setEnabled(false);
	if (kowBool) {
		player->velocity = vec3_t(0.f, .01f, 0.f);
		blinkMod->setEnabled(false);
	}
}

void TestModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	/*vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	auto player = g_Data.getLocalPlayer();
	auto raknet = g_Data.getRakNetInstance();
	if (GameData::canUseMoveKeys()) {
		if (!(g_Data.getLocalPlayer() == nullptr)) {
			if (raknet == nullptr) return;

			std::string servIp = raknet->serverIp.getText();
			std::string servPort = std::to_string(raknet->serverPort);

			vec2_t textPos = vec2_t(g_Data.getClientInstance()->getGuiData()->windowSize.y / 30.f + -16.f, g_Data.getClientInstance()->getGuiData()->windowSize.x - 12.1f);

			if (raknet->serverIp.getTextLength() < 1 || raknet->serverIp.getText() == nullptr)
				servIp = "localhost";
			if (raknet->serverIp.getText() == 0)
				servIp = "0.0.0.0";
			if (raknet->serverPort == 0)
				servPort = "0";
			if (servPort.c_str() == nullptr)
				servPort = "localhost";

			std::string serverInfo = "IP: " + servIp + " " + "Port: " + servPort;

			float x = windowSize.x / 30.f + -16.f;
			float y = windowSize.y - 12.1f;

			DrawUtils::drawText(vec2_t(x, y), &serverInfo, MC_Color(255, 255, 255), 1, 1, true);
		}
	}*/
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	auto player = g_Data.getLocalPlayer();
	if (test) {
		float x = windowSize.x / 114 + 1;
		float x2 = windowSize.x / sliderX + 1;
		float y = windowSize.y - 20;
		float y2 = windowSize.y - 30;
		float y3 = windowSize.y - 40;
		float y4 = windowSize.y - sliderY;

		auto hudMod = moduleMgr->getModule<HudModule>();

		std::string textStr = "Animation test";
		float startY = hudMod->tabGUI ? 10 * 15 : 145;
		float l = DrawUtils::getTextWidth(&textStr, 1.064) + 10.f;
		vec4_t rectPos = vec4_t(sliderX, startY + 4.f * 1, l, startY + 20.f * 1);
		vec2_t textPos = vec2_t(rectPos.x + 15, rectPos.y + 10.f);
		vec2_t pPos = vec2_t(rectPos.x + 6, rectPos.y + 4.f);

		float animationPos = -5;
		animationPos++;
		float xpos = windowSize.x / animationPos + 1;
		DrawUtils::drawText(vec2_t(pPos), &textStr, MC_Color(255, 255, 255), 1, 1, true);
		DrawUtils::drawRoundRectangle(rectPos, MC_Color(0, 0, 0), 0.5);
		static float tick = 1;
		if (tick >= sliderX)
			tick = 1;
		else tick++;

		if (duration >= 600)
			duration = 1;
		else if (tick >= sliderZ)
			duration++;

		//clientMessageF("duration: %s", std::to_string((int)(duration)).c_str());

		std::string aids = std::string("-"); 
		int l65 = DrawUtils::getTextWidth(&aids, 1) + duration;
		//MC_Color color = DrawUtils::getRainbow(5, 1, 1, 8 * 2); // transition RGB
		//DrawUtils::drawAnimatedLine(vec2_t(4, 4), vec2_t(l65, 4), color, 1.f, 1.f, 1.f);
		


		//std::string fpsText = "Player Pitch: " + std::to_string(player->pitch);
		//std::string fpsText2 = "Player Yaw: " + std::to_string(player->yaw);
		//std::string fpsText3 = "Body Yaw: " + std::to_string(player->bodyYaw);
		//DrawUtils::drawText(vec2_t(x, y), &fpsText, MC_Color(255, 255, 255), 1, 1, true);
		//DrawUtils::drawText(vec2_t(x, y2), &fpsText2, MC_Color(255, 255, 255), 1, 1, true);

		DrawUtils::drawText(vec2_t(x2, y4), &textStr, MC_Color(255, 255, 255), 1, 1, true);
		DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), 0.5);

		//std::string filePath = "../../../assets/images/logo.png";
		//DrawUtils::drawImage(filePath, vec2_t(x2, y4), vec2_t(755, 175), vec2_t(0, 0));
		//DrawUtils::drawText(vec2_t(x, y), &BpsText, MC_Color(255, 255, 255), 1);

		/*for (int i = 0; i < 1; i++) {
			player->bodyYaw = sliderX;
			player->pitch = sliderY;
			player->pitch2 = sliderY;
			player->viewAngles2;
			player->viewAngles;
		}*/
	}
}
