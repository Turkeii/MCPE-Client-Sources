#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class NoRotate : public IModule {
public:
	bool body = false;
	SettingEnum mode;
	NoRotate();
	~NoRotate();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onSendPacket(C_Packet* packet) override;
};
