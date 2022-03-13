#pragma once

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class CrystalPlace : public IModule {
private:
	int prevSlot;
	int delay = 0;
	int eRange = 10;
	bool autoplace = true;
	bool ServerMode = false;
	bool pEnhanced = true;
	bool dEnhanced = true;
	bool Preview = false;
	bool AutoSelect = false;
	bool FinishSelect = false;
	float Odelay = 0.f;
	int PlacerRadius = 1;


	C_PlayerInventoryProxy* supplies = nullptr;
	C_Inventory* inv = nullptr;

public:
	CrystalPlace();
	~CrystalPlace();

	// Inherited via IModule
	bool TargetPlayer = false;
	int targethud2 = 0;
	bool hurttime = false;
	int Odelay2 = 0;

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;

	inline int getPlacerRadius() { return PlacerRadius; };

	bool isMulti = false;
	bool targethud = false;
	bool isMobAura = false;
	int range = 10;

	void CPlace(C_GameMode* gm, vec3_t* pos);
	void DestroyC(C_Entity* ent, int range);
};