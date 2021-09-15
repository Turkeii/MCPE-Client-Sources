#pragma once
#include "Module.h"
class MineplexFly : public IModule {
private:
	int counter = 5;
	float speed2 = 0.75f;  // speed = 75

public:
	MineplexFly();
	~MineplexFly();

	SettingEnum mode;

	// Inherited via IModule
	virtual bool isFlashMode() override;
	virtual void onEnable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onDisable() override;
};