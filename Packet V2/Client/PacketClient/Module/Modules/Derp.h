#pragma once
#include "Module.h"
class Derp : public IModule {
private:
	int counter = 0;
	bool headless = false;
	bool silent = false;
	bool twerk = false;
	bool spin = true;
	int Odelay = 0;
	int delay = 1;
	int tick = 0;

public:
	Derp();
	~Derp();

	// Inherited via IModule
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
