#pragma once
#include "Module.h"

class AutoJump : public IModule {
public:
	AutoJump() : IModule(0x0, Category::MOVEMENT, "Automatically jump") {}
	~AutoJump(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("AutoJump"); }
	virtual void onTick(C_GameMode* gm) override {
		C_LocalPlayer* player = g_Data.getLocalPlayer();

		if (player->onGround) player->jumpFromGround();
	}
};