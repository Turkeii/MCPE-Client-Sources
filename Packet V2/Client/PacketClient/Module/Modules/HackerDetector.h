#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class HackerDetector : public IModule {
public:
	std::string str = "A Message";
	std::string name = "Player";
	int sensitivity = 0;
	int Odelay = 0;

	// Speed
	bool failedSpeedA = false;
	bool failedSpeedB = false;
	bool failedSpeed = false;
	float speed = 0.f;

	// Fly
	bool failedFlyA = false;
	bool failedFlyB = false;
	bool failedFly = false;
	int time = 0;

	// Derp
	bool failedDerp = false;

	// NoWeb
	bool failedNoWeb = false;

	HackerDetector();
	~HackerDetector();

			SettingEnum mode = this;

	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onTick(C_GameMode* gm) override;
	//virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual const char* getModuleName();
};