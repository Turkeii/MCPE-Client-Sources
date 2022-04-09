#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"
class TriggerBot : public IModule {
public:
	int delay = 0;
	int Odelay = 0;
	bool sword = true;

	TriggerBot() : IModule(0x0, Category::COMBAT, "Attacks entities you're looking at") {
		registerIntSetting("delay", &delay, delay, 0, 20);
	};
	~TriggerBot(){};

	void onEnable() {
		C_Entity* target = g_Data.getLocalPlayer()->pointingStruct->getEntity();
		if (!Target::isValidTarget(target))
			return;
	}

	void onDisable() {
		C_Entity* target = g_Data.getLocalPlayer()->pointingStruct->getEntity();
		if (!Target::isValidTarget(target))
			return;
	}
	void onTick(C_GameMode* gm) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		C_Entity* target = g_Data.getLocalPlayer()->pointingStruct->getEntity();

		Odelay++;
		if (target > 0 && Odelay >= delay) {
			localPlayer->swingArm();
			gm->attack(target);

			Odelay = 0;
		}
	}

	virtual const char* getModuleName() override {
		return "TriggerBot";
	}
};