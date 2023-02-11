#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class InvMove : public IModule {
private:
	bool keyPressed = false;
public:
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	InvMove();
};