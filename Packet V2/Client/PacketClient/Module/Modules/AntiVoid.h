#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class AntiVoid : public IModule {
private:
	std::vector<vec3_t> below;
	bool foundVoid = false;
	bool voidCheck = true;
	int distance = 5;
	vec3_t savedPos;
	int tick = 0;

public:
	bool blink = false;

	AntiVoid();
	~AntiVoid();

	C_MoveInputHandler* inputHandler = nullptr;
	SettingEnum mode = this;

	// Inherited via IModule
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
