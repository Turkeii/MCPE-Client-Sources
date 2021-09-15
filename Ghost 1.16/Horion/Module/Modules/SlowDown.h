#pragma once
#include "Module.h"
class SlowDown : public IModule {
private:
	int timer = 5;

public:
	SlowDown();
	~SlowDown();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
};
