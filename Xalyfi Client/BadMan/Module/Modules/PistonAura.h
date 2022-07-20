#pragma once
#include "Module.h"

class PistonAura : public IModule {
private:
	int delay = 0;
	int PlacerRadius = 4;
	bool inWater = false;
	bool inAir = false;

public:
	PistonAura();
	~PistonAura();

	bool TargetPlayer = false;
	float range = 6;

	inline int getPlacerRadius() { return PlacerRadius; };

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};