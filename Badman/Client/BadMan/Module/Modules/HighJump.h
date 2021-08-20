#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class HighJump : public IModule {
public:
	float jumpPower = 1.8f;
	HighJump();
	~HighJump();

	// Inherited via IModule

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
