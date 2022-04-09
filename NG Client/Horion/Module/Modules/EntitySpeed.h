#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class EntitySpeed : public IModule {
private:
	bool keyPressed = false;
	float speed2 = 0.75f;   // speed = 75

public:
	EntitySpeed();
	~EntitySpeed();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
