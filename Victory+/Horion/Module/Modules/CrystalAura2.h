#pragma once
#include "Module.h"
class CrystalAura2 : public IModule {
private:
	int prevSlot;

	int delay = 3;
	bool autoplace = true;
	bool crystalCheck = true;
	bool yLock = false;
	bool isClick = false;
	bool doMultiple = false;
	bool blockSwap = true;
	bool FinishSelect = false;
	C_PlayerInventoryProxy* supplies = nullptr;
	C_Inventory* inv = nullptr;

public:
	CrystalAura2();
	~CrystalAura2();
	
	SettingEnum mode;

	// Inherited via IModule
	virtual const char* getModName() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm);
	virtual void onEnable() override;
	virtual void onDisable() override;
	int range = 7;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	vec3_t espPosUpper2;
	vec3_t espPosLower2;
};
