#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class LongJump : public IModule {
private:
	int counter = 1;
	bool disable;
	float upvel = 0.f;
	float speedMod = 0.1f;

public:
	C_MovePlayerPacket* jetpack = nullptr;
	LongJump();
	~LongJump();


	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
