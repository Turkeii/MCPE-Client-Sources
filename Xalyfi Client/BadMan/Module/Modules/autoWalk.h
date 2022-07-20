#pragma once
#include "Module.h"
class autoWalk : public IModule {
public:
	autoWalk();
	~autoWalk();
	
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
