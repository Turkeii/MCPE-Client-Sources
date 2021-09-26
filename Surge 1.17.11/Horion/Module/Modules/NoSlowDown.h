#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class NoSlowDown : public IModule {
private:
	bool keyPressed = false;

public:
	NoSlowDown();
	~NoSlowDown();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
