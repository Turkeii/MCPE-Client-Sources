#pragma once
#include "Module.h"
class Fly : public IModule {
private:
	float speed = 1.5f;
	int gameTick = 0;
	bool viewBobbing = true;

public:
	float value = 0.f;

public:
	Fly();
	~Fly();

	SettingEnum mode;

	// Inherited via IModule
	virtual bool isFlashMode() override;
	virtual void onEnable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
