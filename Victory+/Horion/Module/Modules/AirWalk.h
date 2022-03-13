#pragma once
#include "Module.h"

class AirWalk : public IModule {
public:
	AirWalk();
	~AirWalk();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};