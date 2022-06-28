#pragma once
#include "Module.h"

class Verification : public IModule {
private:
	bool passedTest = false;
	bool test = false;

public:
	Verification();
	~Verification();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable();
};