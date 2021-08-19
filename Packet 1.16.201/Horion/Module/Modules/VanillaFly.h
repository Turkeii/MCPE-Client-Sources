#pragma once
#include "Module.h"
class VanillaFly : public IModule {
private:
	float glideMod = 0.0f;
	float glideModEffective = 0;
	float speed = 1.505f;

public:
	VanillaFly();
	~VanillaFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};