#pragma once
#include "../ModuleManager.h"
#include "Module.h"

	class EntityFly : public IModule {
private:
	bool keyPressed = false;
	float speed2 = 0.75f;   // speed = 75
	float upspeed = 0.75f;  // speed = 75
	float glideMod = 0.f;
	float glideModEffective = 0;

public:
	EntityFly();
	~EntityFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};