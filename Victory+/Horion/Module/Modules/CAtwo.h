/*#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class CAtwo : public IModule {
private:
	int prevSlot;
	int delay = 0;
	int eRange = 3;
	bool autoplace = true;
	bool pEnhanced = true;
	bool dEnhanced = true;
	bool Preview = true;
	bool AutoSelect = true;
	bool FinishSelect = false;
	C_PlayerInventoryProxy* supplies = nullptr;
	C_Inventory* inv = nullptr;

public:
	CAtwo();
	~CAtwo();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;


	int cRange = 10;
	int pRange = 5;
	int range = 10;

	void CPlace(C_GameMode* gm, vec3_t* pos);
	void DestroyC(C_Entity* ent, int range);
};*/