#pragma once
#include "Module.h"
class HiveFly : public IModule {
private:
public:
	int counter = 1;
	bool strafeMode = false;
	bool blinkMode = false;
	bool damageMode = false;
	bool boostMode = true;
	float TimerOFG = 20;
	float speedA = 0.30183640122413635;  // Speed
	float TimerUp = 20;
	int delay = 0;
	int timer = 60;
	bool penis = true;
	float speed = 0.225f;
	float glideMod = -0.03f;
	float glideModEffective = 0;
	float value = -0.004993199370801449;
	float Up = .01f;
	float UpSpeed = 0.1f;
	float Test = 0.005f;
	int boostCounter = 1;
	bool speedWasEnabled = false;
	bool scfWasEnabled = false;

	HiveFly();
	~HiveFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};