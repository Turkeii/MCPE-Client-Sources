#pragma once
#include "Module.h"
class Mineplex : public IModule {
private:
	bool delayMode = false;
	int speedMod = 1;
	int speedMod0 = 0;

public:
	Mineplex();
	~Mineplex();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
