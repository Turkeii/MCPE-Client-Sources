#pragma once
#include "Module.h"
class TestHack : public IModule {
private:
	float speed = 1.5f;
	float ystart = 1.f;
	float yflying = 0.5f;
	int gameTick = 0;
	int delaytp = 5;
	int tpdist = 3;

public:
	TestHack();
	~TestHack();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual bool isFlashMode() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
