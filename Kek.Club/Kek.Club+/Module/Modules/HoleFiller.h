#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class HoleFiller : public IModule {
private:
	bool obsidian = true;
	bool bedrock = true;
	bool mix = true;
	bool allBlocks = false;
	int range = 5;
	int delay = 0;
	int Odelay = 0;
	SettingEnum rotations;
	static int constexpr rotations_off = 0;
	static int constexpr rotations_arora = 1;
	bool findDaBlocks();

public:
	HoleFiller();
	~HoleFiller();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onLevelRender() override;
};
