#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class EntityLongJump : public IModule {
private:
	int counter = 1;
public:
	float upVal = 0.325f;
	float speed = 0.325f;

	EntityLongJump();
	~EntityLongJump();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};