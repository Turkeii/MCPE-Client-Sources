#pragma once
#include "Module.h"
class FlyBypass : public IModule {
private:
	//int timer = 100;
	float glideMod = -0.0001f;
	float glideModEffective = 0;

public:
	FlyBypass();
	~FlyBypass();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onTick(C_GameMode* gm) override;
};
