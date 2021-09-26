#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class NoSlowDown : public IModule {
private:
	float speed = 0.200f;

public:
	NoSlowDown();
	~NoSlowDown();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
