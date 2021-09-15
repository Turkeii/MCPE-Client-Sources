#pragma once
#include "Module.h"
class Insane : public IModule {
private:
	bool insane = false;
	bool die = false;
	bool dimension = false;
	bool totem = false;

	public:
	Insane();
	~Insane();

	SettingEnum mode;

	// Inherited via IModule
	virtual void onEnable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
