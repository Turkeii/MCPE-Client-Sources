#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class CrystalAuraBot : public IModule {
private:
	bool isHitingKeys = false;
	float distance = 1.1f;
	float animYaw = 0.f;
	int timer = 20;
public:
	CrystalAuraBot();
	~CrystalAuraBot();

	std::string name = "CrystalAuraBot";
	SettingEnum rotations = this;

	// Inherited via IModule
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLevelRender() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
};