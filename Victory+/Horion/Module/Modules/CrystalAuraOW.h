#pragma once
#include "Module.h"
class CrystalAuraOW : public IModule {
private:

	bool tryCrystalAuraOW(vec3_t CrystalAuraOW);

public:
	CrystalAuraOW();
	~CrystalAuraOW();
	

	bool placed = false;
	int range = 7;
	bool onClick = false;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
