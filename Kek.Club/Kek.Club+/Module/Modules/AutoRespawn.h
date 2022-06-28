#pragma once
#include "Module.h"
class AutoRespawn : public IModule {
public:
	bool deathpos = false;
	AutoRespawn();
	~AutoRespawn();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};