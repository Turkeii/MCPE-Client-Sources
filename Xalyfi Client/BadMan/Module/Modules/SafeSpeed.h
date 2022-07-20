#pragma once
#include "Module.h"
class SafeSpeed : public IModule {
private:
	int timer = 25;

public:
	SafeSpeed();
	~SafeSpeed();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
};
#pragma once
