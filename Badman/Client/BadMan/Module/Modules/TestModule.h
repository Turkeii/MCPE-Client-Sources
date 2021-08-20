#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class TestModule : public IModule {
private:

public:
	TestModule();
	~TestModule();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onAttack(C_Entity* attackedEnt) override;
	virtual void onLevelRender() override;
};
