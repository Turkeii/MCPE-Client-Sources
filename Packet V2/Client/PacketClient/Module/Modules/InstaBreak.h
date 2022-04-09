#pragma once
#include "Module.h"

class InstaBreak : public IModule {
public:
	bool breakBlocks = false;
	bool hive = false;
	int delay = 0;
	int Odelay = 0;
	int i = 0;

	InstaBreak();
	~InstaBreak();

	// Inherited via IModule
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};