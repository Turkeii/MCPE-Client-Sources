#pragma once
#include "Module.h"
class HiveFly : public IModule {
private:
	int counter = 1;
	float speed2 = 0.30f;  // speed = 30

	public:
	HiveFly();
	~HiveFly();

	SettingEnum mode;

	// Inherited via IModule
	virtual bool isFlashMode() override;
	virtual void onEnable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onDisable() override;
};
