#pragma once
#include "Module.h"
class ReverseStep : public IModule {
public:
	ReverseStep();
	~ReverseStep();
	
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
