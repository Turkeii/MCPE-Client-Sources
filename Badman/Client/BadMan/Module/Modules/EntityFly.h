#pragma once
#include "Module.h"
class EntityFly : public IModule {
public:
	EntityFly();
	~EntityFly();

	float speed = 1.f;
	float glideMod = -0.00f;
	float glideModEffective = 0;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
