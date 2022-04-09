#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AirJump : public IModule {
public:
	int hasJumped = 0;
	bool legacyMode = false;

	AirJump() : IModule(0x0, Category::MOVEMENT, "Jump even you're not on the ground") {
		registerBoolSetting("Legacy", &legacyMode, legacyMode);
	};
	~AirJump(){};

	void onTick(C_GameMode* gm) {
		if (legacyMode) {
			gm->player->onGround = true;
			return;
		}
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

		if (input == nullptr)
			return;

		if (GameData::isKeyDown(*input->spaceBarKey) && hasJumped == 0) {
			gm->player->onGround = true;
			hasJumped = 1;
		} else if (!GameData::isKeyDown(*input->spaceBarKey)) {
			hasJumped = 0;
		}
	}

	virtual const char* getModuleName() override {
		return "AirJump";
	}
};