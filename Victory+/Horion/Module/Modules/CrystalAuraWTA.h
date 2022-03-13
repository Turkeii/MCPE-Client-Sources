#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class CrystalAuraWTA : public IModule {
private:
	int delay = 3;
	bool autoplace = true;
	bool crystalCheck = true;
	bool yLock = false;
	bool isClick = false;
	bool doMultiple = false;

public:
	CrystalAuraWTA();
	~CrystalAuraWTA();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	int range = 7;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	vec3_t espPosUpper;
	vec3_t espPosLower;
};
