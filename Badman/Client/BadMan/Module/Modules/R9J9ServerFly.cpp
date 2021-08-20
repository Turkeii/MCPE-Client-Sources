#include "R9J9ServerFly.h"

R9J9ServerFly::R9J9ServerFly() : IModule(0, Category::SERVER, "A variety of bypassing flights (Credits to R9J9)") {
    registerBoolSetting("Hive", &this->Hive, this->Hive);
	registerBoolSetting("Hive Safe", &this->HiveSafe, this->HiveSafe);
	registerFloatSetting("Hive Speed", &this->HiveSpeed, this->HiveSpeed, 0.2, 0.5);
	registerIntSetting("Hive Timer", &this->HiveTimer, this->HiveTimer,  1, 50);
	registerBoolSetting("Mineplex", &this->Mineplex, this->Mineplex);
	registerFloatSetting("Mineplex Speed", &this->MineplexSpeed, this->MineplexSpeed, 0.f, 1.f);
	registerBoolSetting("Blink", &this->Test, this->Test);
	registerBoolSetting("Lifeboat", &this->Lifeboat, this->Lifeboat);
}

R9J9ServerFly::~R9J9ServerFly() {
}

const char* R9J9ServerFly::getModuleName() {
    return ("R9J9ServerFly");
}
void R9J9ServerFly::onTick(C_GameMode* gm) {
    C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (Creative) {
		gm->player->canFly = true;
	}
	if (Lifeboat) {
		localPlayer->velocity.y = -0.4f;
		localPlayer->onGround = true;
		float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		*speedAdr = 0.5;
		*g_Data.getClientInstance()->minecraft->timer = 50;
	}
	if (Hive) {
		*g_Data.getClientInstance()->minecraft->timer = (HiveTimer);
		localPlayer->velocity.y = -0.00004f;
		float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		*speedAdr = HiveSpeed;
		localPlayer->onGround = true;
	}
	if (HiveSafe) {
		localPlayer->velocity.y = -0.00003f;
		localPlayer->onGround = true;
	}
	if (Mineplex) {
		localPlayer->velocity.y = 0;
		localPlayer->onGround = true;
		float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		*speedAdr = MineplexSpeed;
	}
	if (Test) {
		gameTick++;
		localPlayer->onGround = true;
		gm->player->velocity.y = 0;
		if (gameTick >= 16) {
			this->getMovePlayerPacketHolder()->begin();
			this->getMovePlayerPacketHolder()->clear();
			this->getPlayerAuthInputPacketHolder()->clear();
		}
		if (g_Data.canUseMoveKeys()) {
			if (GameData::isKeyDown(*input->spaceBarKey))
				localPlayer->velocity.y = 0.5f;
			if (GameData::isKeyDown(*input->sneakKey))
				localPlayer->velocity.y = -0.5f;
		}
		float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		*speedAdr = 0.5;
	}
}

void R9J9ServerFly::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		if (g_Data.getLocalPlayer()->gamemode != 1)
			g_Data.getLocalPlayer()->canFly = false;
	float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
	*speedAdr = 0.10000000149011612;
	*g_Data.getClientInstance()->minecraft->timer = 20;
}