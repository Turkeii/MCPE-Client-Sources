#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class Breaker : public IModule {
private:
	int range = 5;
	bool beds = false;
	bool eggs = false;
	bool cakes = false;
	bool treasures = false;
	bool chests = true;
	bool redstone = false;
	bool diamond = false;
	bool emerald = false;
	//bool andisite = false;
	//bool nuke = true;

public:
	Breaker();
	~Breaker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
