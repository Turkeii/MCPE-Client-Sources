#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Glide : public IModule {
public:
	float glideMod = -0.01f;
	float glideModEffective = 0;
	bool fart = false;

	Glide() : IModule(0x0, Category::FLYS, "Float down") {
		registerFloatSetting("value", &glideMod, glideMod, -2, 1);
		registerBoolSetting("Test", &fart, fart);
	};
	~Glide(){};

	
void onTick(C_GameMode* gm) {
		glideModEffective = glideMod;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

		if (g_Data.canUseMoveKeys()) {
			if (GameData::isKeyDown(*input->spaceBarKey))
				glideModEffective += 0.2f;
			if (GameData::isKeyDown(*input->sneakKey))
				glideModEffective -= 0.2f;
		}
		gm->player->velocity.y = glideModEffective;
	}

	virtual const char* getModuleName() override {
		return "Glide";
	}
};