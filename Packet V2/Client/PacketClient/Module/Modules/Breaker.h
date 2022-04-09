#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class Breaker : public IModule {
private:
	bool ezHiveBypass = true;
	bool switchSlot = false;
	bool treasures = false;
	bool destroy = false;
	bool chests = false;
	bool cakes = false;
	bool beds = false;
	bool eggs = false;
	bool rOre = false;
	bool dOre = false;
	bool eOre = false;
	bool gOre = false;
	int counter = 1;
	int Odelay = 0;
	int delay = 0;
	int range = 5;
	int slot = 1;

public:
	bool rotations = false;
	bool gold = false;
	vec3_t blockPos;

	Breaker();
	~Breaker();

	std::string name = "Breaker";

	// Inherited via IModule
	virtual void onDisable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};