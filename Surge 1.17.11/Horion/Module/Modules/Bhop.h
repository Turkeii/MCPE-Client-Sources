#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class Bhop : public IModule {
private:
	float speed = 0.325f;
	float tspeed = 0.325f;
	bool bhopspeed = false;
	int counter = 1;
	bool LowHop = false;
	bool timer = true;
	float hight = 0.15f;

public:
	Bhop();
	~Bhop();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	void onTick(C_GameMode* gm);
	virtual void onDisable() override;
};
