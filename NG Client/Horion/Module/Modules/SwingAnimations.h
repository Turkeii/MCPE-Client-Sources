#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class SwingAnimations : public IModule {
public:
	SettingEnum swing;
	SwingAnimations();
	~SwingAnimations();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPlayerTick(C_Player* plr) override;
};