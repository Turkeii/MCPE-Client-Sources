#pragma once
#include "Module.h"

class Velocity : public IModule {
public:

	Velocity();
	~Velocity();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
