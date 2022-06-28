#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class AutoCrystalRewrite : public IModule {
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
	bool CanPlaceC(vec3_ti* pos);
	C_PlayerInventoryProxy* supplies = nullptr;
	C_Inventory* inv = nullptr;
	bool space = true;
	vec3_t _pos;
	bool shouldChange = false;
	vec3_t rots;


public:
	AutoCrystalRewrite();
	~AutoCrystalRewrite();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onLevelRender() override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable() override;
	virtual void onDisable() override;

	int cRange = 10;
	int pRange = 5;
	int range = 10;

	void CPlace(C_GameMode* gm, vec3_t* pos);
	void DestroyC(C_Entity* ent, int range);
};