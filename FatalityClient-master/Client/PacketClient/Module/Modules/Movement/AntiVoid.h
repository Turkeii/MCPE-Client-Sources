#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

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

	C_MoveInputHandler* inputHandler = nullptr;
	SettingEnum mode = this;

	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onDisable();
	virtual void onEnable();
	AntiVoid();
};
