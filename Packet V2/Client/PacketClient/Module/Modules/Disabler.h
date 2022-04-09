#pragma once
#include "Module.h"

class Disabler : public IModule {
public:

	Disabler();
	~Disabler();

	std::string name = "Disabler";
	SettingEnum mode = this;

	// Inherited via IModule
	virtual void onEnable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};