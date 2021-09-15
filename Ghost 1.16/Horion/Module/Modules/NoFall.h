#pragma once
#include "Module.h"
class NoFall : public IModule {
public:
	NoFall();
	~NoFall();
	
	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onTick(C_GameMode* gm);
};
