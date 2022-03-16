#pragma once
#include "Module.h"
class Scaffold : public IModule {
private:
	bool automaticBlock = true;
	int expandMode = 1;
	bool expandModeBool = true;
	bool isSneaking = false;
	bool spoof = false;
	bool timerBoost = true;
	bool staircaseMode = false;
	bool tryScaffold(vec3_t blockBelow);
	bool findBlock();
	float motion = 0.45f;
	bool tryTower(vec3_t blockBelow);
	int prevSlot = 0;
	bool selectBlock();

	int yLock = -1;

public:
	bool towerMode = true;
	int timer = 20;
	bool lockY = false;

	Scaffold();
	~Scaffold();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};