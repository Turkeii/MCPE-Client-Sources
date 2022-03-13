#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class CrystalMove : public IModule {
private:
	int prevSlot;
	int eRange = 3;
	C_PlayerInventoryProxy* supplies = nullptr;
	C_Inventory* inv = nullptr;

public:
	CrystalMove();
	~CrystalMove();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;

	int cRange = 10;
	int pRange = 5;
	int range = 10;
};
;