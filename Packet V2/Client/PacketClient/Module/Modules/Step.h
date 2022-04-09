#pragma once
#include "..\ModuleManager.h"
#include "Module.h"
class Step : public IModule {
public:
	bool reverse = false;
	float height = 1.5f;
	int timer = 20;

	Step();
	~Step();

	std::string name = "Step";
	SettingEnum mode = this;

	// Inherited via IModule
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual const char* getRawModuleName() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
