#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class Bhop : public IModule {
private:
	bool jumpMode = true;
	float height = 0.60f;

public:
	int timer = 20;
	bool lowMode = false;
	bool hiveMode = false;
	float speed = 0.325f;
	Bhop();
	~Bhop();

	// Inherited via IModule
	virtual void onDisable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};