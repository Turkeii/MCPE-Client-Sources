#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class MCF : public IModule {
private:
	bool hasClicked = false;
public:
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	MCF();
};
