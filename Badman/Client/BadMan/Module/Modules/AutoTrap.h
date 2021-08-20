#pragma once
#include "Module.h"
class AutoTrap : public IModule {
private:

	bool tryAutoTrap(vec3_t AutoTrap);

public:
	AutoTrap();
	~AutoTrap();
	
	int range = 7;
	bool onClick = false;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
