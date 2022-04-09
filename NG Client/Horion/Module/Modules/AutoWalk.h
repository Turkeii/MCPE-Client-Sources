#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AutoWalk : public IModule {
public:
	bool sprint = false;
	bool jump = false;

	AutoWalk() : IModule(0x0, Category::MOVEMENT, "Automatically walk for you") {
		registerBoolSetting("Sprint", &sprint, sprint);
		registerBoolSetting("Jump", &jump, jump);
	};
	~AutoWalk(){};

	void onTick(C_GameMode* gm) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();

		g_Data.getClientInstance()->getMoveTurnInput()->forward = true;

		if (sprint) gm->player->setSprinting(true);
		if (!sprint) gm->player->setSprinting(false);

		if (player->onGround && jump) gm->player->jumpFromGround();
	}

	void onDisable() {
		g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
	}

	virtual const char* getModuleName() override {
		return "AutoWalk";
	}
};