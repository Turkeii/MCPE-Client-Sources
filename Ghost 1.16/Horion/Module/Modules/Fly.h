#pragma once
#include "Module.h"
class Fly : public IModule {
private:
	float speed2 = 0.75f;  // speed = 75
	float glideMod = 0.f;
	float glideModEffective = 0;

public:
	Fly();
	~Fly();

	SettingEnum mode;

	// Inherited via IModule
	virtual bool isFlashMode() override;
	virtual void onEnable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onDisable() override;
};
