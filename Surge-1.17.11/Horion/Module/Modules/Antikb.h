#pragma once
#include "Module.h"

class Antikb : public IModule {
public:
	float xMod = 0.f;
	float yMod = 0.f;
	Antikb();
	~Antikb();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
