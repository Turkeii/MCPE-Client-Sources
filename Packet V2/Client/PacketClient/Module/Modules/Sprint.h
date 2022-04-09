#pragma once
#include "../../DrawUtils.h"
#include "Module.h"

class Sprint : public IModule {
public:
	bool useSprint = true;
	Sprint() : IModule(0, Category::MOVEMENT, "Sprint") {
	}
	~Sprint(){};

	virtual const char* getModuleName() override { return "Sprint"; }

	void onTick(C_GameMode* gm) override {
		if (!gm->player->isSprinting() && gm->player->velocity.magnitudexz() > 0.01f && useSprint) {
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			if (GameData::isKeyDown(*input->forwardKey) && !GameData::isKeyDown(*input->sneakKey))
				gm->player->setSprinting(true);
		}
	}
};