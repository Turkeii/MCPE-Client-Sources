#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AutoSprint : public IModule {
public:
	bool alldirections = true;

	AutoSprint() : IModule(0x0, Category::MOVEMENT, "Automatically sprint without holding the key") {
		registerBoolSetting("all directions", &alldirections, alldirections);
	};
	~AutoSprint(){};

	void onTick(C_GameMode* gm) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		if (!GameData::isKeyDown(*input->sneakKey)) {
			if (!gm->player->isSprinting() && gm->player->velocity.magnitudexz() > 0.01f) {
				if (alldirections || GameData::isKeyDown(*input->forwardKey))
					gm->player->setSprinting(true);
			}
		}
	}

	virtual const char* getModuleName() override {
		return "AutoSprint";
	}
};