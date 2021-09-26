#pragma once
#include "Module.h"

class Totem : public IModule {
public:
	Totem();
	~Totem();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};