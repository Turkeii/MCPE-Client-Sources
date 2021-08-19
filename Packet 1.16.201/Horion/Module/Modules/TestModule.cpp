#include "../../Module/ModuleManager.h"
#include "TestModule.h"

TestModule::TestModule() : IModule(0, Category::MISC, "Description") {
	this->registerBoolSetting("AlertBox", &this->alertBox, this->alertBox);
	this->registerBoolSetting("Teleport", &this->istpMode, this->istpMode);
	this->registerBoolSetting("Damage", &this->dmgMode, this->dmgMode);
	this->registerBoolSetting("Server", &this->serverMode, this->serverMode);
	this->registerBoolSetting("Test", &this->test, this->test);
	//this->registerBoolSetting("HiveDmgFly", &this->dmgflyMode, this->dmgflyMode);
}

const char* TestModule::getModuleName() {
	return "TestModule";
}

void TestModule::onEnable() {
	if (serverMode) {
		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "mco.cubecraft.net") == 0) {  //1 Cubecraft
			g_Data.getGuiData()->displayClientMessageF("Cubecraft");
		}
		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "geo.hivebedrock.network") == 0) {  //2 The Hive
			g_Data.getGuiData()->displayClientMessageF("The Hive");
		}
		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "play.inpvp.net") == 0) {  //3 Mineville
			g_Data.getGuiData()->displayClientMessageF("Mineville/InPvP");
		}
		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "play.lbsg.net") == 0) {  //4 Lifeboat
			g_Data.getGuiData()->displayClientMessageF("Lifeboat");
		}
		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "mco.mineplex.com") == 0) {  //5 Mineplex
			g_Data.getGuiData()->displayClientMessageF("Mineplex");
		}
		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "play.galaxite.net") == 0) {  //6 Furry server
			g_Data.getGuiData()->displayClientMessageF("Galaxite");
		}
	}

	if (alertBox) {
		auto box = g_Data.addInfoBox("Test", "Notification");
		box->closeTimer = 30;
		auto testmoduleMod = moduleMgr->getModule<TestModule>();
		if (testmoduleMod->isEnabled()) {
			testmoduleMod->setEnabled(false);
		}
	}
	if (dmgMode) {
		auto bhopMod = moduleMgr->getModule<Bhop>();
		bhopMod->setEnabled(false);
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
	if (dmgflyMode) {
		auto hfMod = moduleMgr->getModule<HiveFly>();
		if (hfMod->isEnabled()) {
			hfMod->setEnabled(true);
		}
		if (dmgflyMode) {
			vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

			vec3_t pos;
			pos.x = 0.f + pPos.x;
			pos.y = 4.5f + pPos.y;
			pos.z = 0.f + pPos.z;

			g_Data.getLocalPlayer()->setPos(pos);
			*g_Data.getClientInstance()->minecraft->timer = 6000.f;
		}
	}
}

bool TestModule::isFlashMode() {
		return false;
}

void TestModule::onTick(C_GameMode* gm) {
	if (test) {
		//sendCommand("/title @s title message"); - onix86 LMAO
	}
	if (serverMode) {
		auto testmoduleMod = moduleMgr->getModule<TestModule>();
		if (testmoduleMod->isEnabled()) {
			testmoduleMod->setEnabled(false);
		}
	}
			if (istpMode) {
				auto player = g_Data.getLocalPlayer();
				C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
				float yaw = player->yaw;
				if (input->forwardKey && input->backKey && input->rightKey && input->leftKey) {
					gm->player->velocity = vec3_t(0, 0, 0);
				}
				if (GameData::isKeyDown(*input->spaceBarKey))
					glideModEffective += 0.0f;
				if (GameData::isKeyDown(*input->sneakKey))
					glideModEffective -= 0.0f;
			}
			if (dmgMode) {
				*g_Data.getClientInstance()->minecraft->timer = 20.f;
				auto bhopMod = moduleMgr->getModule<Bhop>();
				bhopMod->setEnabled(false);
				auto dmgMod = moduleMgr->getModule<TestModule>();
				if (dmgMod->isEnabled()) {
					dmgMod->setEnabled(false);
				}
			}
			if (dmgflyMode) {
				*g_Data.getClientInstance()->minecraft->timer = 20.f;
			}
			if (dmgMode) {
				auto testmoduleMod = moduleMgr->getModule<TestModule>();
				if (testmoduleMod->isEnabled()) {
					testmoduleMod->setEnabled(false);
				}
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
	if (istpMode) {
		auto tpMod = moduleMgr->getModule<TestModule>();
		if (tpMod->isEnabled()) {
			tpMod->setEnabled(false);
		}
	}
	if (dmgflyMode) {
		// Damage Fly
	}
}

void TestModule::onDisable() {
	if (dmgMode) {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	if (dmgflyMode) {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	if (istpMode) {
		auto player = g_Data.getLocalPlayer(); {
			if (!player->onGround) {
				player->velocity.x = 0.f;
				player->velocity.z = 0.f;
			}
		}
	}
}