#pragma once
#include "Module.h"

class CrystalReplenishment : public IModule {
private:
	int slot = 0;

public:
	CrystalReplenishment();
	~CrystalReplenishment();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
