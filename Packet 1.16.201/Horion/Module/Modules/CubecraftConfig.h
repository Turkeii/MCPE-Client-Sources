#pragma once

#include "Module.h"

class CubecraftConfig : public IModule {
public:
	CubecraftConfig();
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
};