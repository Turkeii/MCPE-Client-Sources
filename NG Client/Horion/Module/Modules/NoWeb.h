#pragma once
#include "Module.h"
class NoWeb : public IModule {
public:
	NoWeb() : IModule(0x0, Category::MOVEMENT, "Ignore cobwebs slowdown") {}
	~NoWeb(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("NoWeb"); }
	virtual void onTick(C_GameMode* gm) override { gm->player->slowdownFactor = {0, 0, 0}; }
};