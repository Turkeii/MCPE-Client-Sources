#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class XP : public IModule {
public:
	int amount = 1;

	XP() : IModule(0x0, Category::SERVER, "Gives You Shit Loads Of XP!") {
		registerIntSetting("amount", &amount, amount, 1, 5000);
	};
	~XP(){};

	void onTick(C_GameMode* gm) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		player->addLevels(amount);
	}

	virtual const char* getModuleName() override {
		return "XP";
	}
};