#pragma once
#include "Module.h"
class pvpResources : public IModule {
public:
	pvpResources();
	~pvpResources();

	float scale = 1.f;
	float pvpX = 0.f;
	float pvpY = 0.f;
	bool text = true;


	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual bool isThereCrystal();
	virtual bool isThereGapples();
	virtual bool isThereTotem();
	virtual bool isThereXp();
	int pullSlot(int itemIDPog);
	virtual int countItem(int itemIDCount);
};
