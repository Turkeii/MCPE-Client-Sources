#pragma once
#include "Module.h"
class AutoSneak : public IModule {
public:
	bool doSilent = false;
	AutoSneak() : IModule(0x0, Category::MOVEMENT, "Automatically sneak without holding the key") {
		registerBoolSetting("Silent", &doSilent, doSilent);
	}
	~AutoSneak(){};

	virtual const char* getModuleName() override { return ("AutoSneak"); }
	virtual void onTick(C_GameMode* gm) override {
		if (!doSilent)
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
	}
	virtual void onMove(C_MoveInputHandler* input) {
		if (input->isSneakDown && doSilent) {
			input->sideMovement *= 8;
			input->forwardMovement *= 8;
		}
	}
	virtual void onDisable() override {
		if (g_Data.getLocalPlayer() == nullptr)
			return;
		if (!doSilent) {
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
			return;
		}
	}
	virtual void onEnable() override {
		if (g_Data.getLocalPlayer() == nullptr)
			return;
	}
};