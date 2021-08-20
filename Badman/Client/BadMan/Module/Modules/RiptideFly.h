#pragma once
#include "Module.h"

class RiptideFly : public IModule {
	
private: 
	float speed = 0.325f;
	float upanddown = 0.6f;
	float glideMod = -0.00f;
	float glideModEffective = 0;
	
public:
	RiptideFly();
	~RiptideFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};