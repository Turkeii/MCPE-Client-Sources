#pragma once
#include "Module.h"
class FlyBypass : public IModule {
private:
	float glideModEffective = 0;

public:
	FlyBypass();
	~FlyBypass();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual bool isFlashMode() override;
	virtual void onEnable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};