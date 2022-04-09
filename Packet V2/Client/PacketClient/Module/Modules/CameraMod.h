#pragma once

#include "Module.h"

class CameraMod : public IModule {
public:
	float* gammaPtr = nullptr;
	bool nohurtMode = false;
	bool fullbright = false;
	int fbAmount = 25;
	vec2_t rot;

	CameraMod();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};