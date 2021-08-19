#pragma once
#include "Module.h"
class NGFly : public IModule {
private:
	float glideMod = 0.0f;
	float glideModEffective = 0;
	float speed = 2.110f;

public:
	NGFly();
	~NGFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};