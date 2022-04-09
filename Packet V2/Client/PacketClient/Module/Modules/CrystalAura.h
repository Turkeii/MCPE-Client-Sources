#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class CrystalAura : public IModule {
private:
	int prevSlot;
	int delay = -50;
	int eRange = 3;
	bool autoplace = true;
	bool pEnhanced = false;
	bool dEnhanced = false;
	bool Preview = false;
	bool AutoSelect = true;
	bool FinishSelect = false;
	C_PlayerInventoryProxy* supplies = nullptr;
	C_Inventory* inv = nullptr;

public:
	CrystalAura();
	~CrystalAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable() override;
	virtual void onDisable() override;

	int cRange = 10;
	int pRange = 5;
	int range = 10;

	void CPlace(C_GameMode* gm, vec3_t* pos);
	void DestroyC(C_Entity* ent, int range);
};