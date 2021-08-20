#pragma once
#include "Module.h"

class BoatSpeed : public IModule {
private:
	float speed = 1.f;

public:
	BoatSpeed();
	~BoatSpeed();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
