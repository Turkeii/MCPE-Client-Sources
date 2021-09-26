#pragma once
#include "Module.h"

class Velocity : public IModule {
public:
	float xModifier = 0.f;
	float yModifier = 0.f;
	Velocity();
	~Velocity();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
