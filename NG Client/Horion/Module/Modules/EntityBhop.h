#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class EntityBhop : public IModule {
private:
	int counter = 1;
public:
	bool lowhop = true;
	float upVal = 0.325f;
	float speed = 0.325f;

	EntityBhop();
	~EntityBhop();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};