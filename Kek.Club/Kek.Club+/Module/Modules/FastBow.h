#pragma once
#include "Module.h"
class FastBow : public IModule {
private:
	int charge = 7;
	int i = 0;

public:
	FastBow();
	~FastBow();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
