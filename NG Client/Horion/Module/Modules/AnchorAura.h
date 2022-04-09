#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class AnchorAura : public IModule {
public:
	int prevSlot;
	int delay = 0;
	int give = 0;
	int eRange = 3;
	bool autoplace = true;
	bool dump = false;
	bool Give = false;
	bool pEnhanced = true;
	bool dEnhanced = false;
	bool Preview = true;
	bool AutoSelect = true;
	bool FinishSelect = false;
	C_PlayerInventoryProxy* supplies = nullptr;
	C_Inventory* inv = nullptr;
	int cRange = 10;
	int pRange = 5;
	int range = 10;

	AnchorAura();
	~AnchorAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onLevelRender() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	void CPlace(C_GameMode* gm, vec3* pos);
	void DestroyC(C_Entity* ent, int range);
};