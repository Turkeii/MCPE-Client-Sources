#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class TestModule : public IModule {
public:
	C_Entity* player;
	int delay = 0;
	void* targetAddress;  //Yes
	int counter = 0;
	vec3i block;
	float float1 = 0;
	int int1 = 0;
	bool bool1 = true;
	SettingEnum enum1;

	TestModule();
	~TestModule();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onWorldTick(C_GameMode* gm) override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onSendPacket(C_Packet* p) override;
	virtual void onMove(C_MoveInputHandler* hand) override;
	virtual void onDisable() override;
	virtual void onLevelRender() override;
};