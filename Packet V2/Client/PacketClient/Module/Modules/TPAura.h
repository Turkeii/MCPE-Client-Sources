#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class TPAura : public IModule {
public:
	std::vector<vec3_t> position;
	float distance = 3.5f;
	bool visualize = true;
	bool behind = false;
	bool multi = false;
	float range = 250;
	int targethud = 0;
	int tpDelay = 0;
	int Odelay = 0;
	int delay = 0;
	int tick = 0;

	TPAura();
	~TPAura();

		//std::string name = "TPAura";
		SettingEnum mode = this;

	// Inherited via IModule
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onLevelRender() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	//virtual const char* getRawModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};