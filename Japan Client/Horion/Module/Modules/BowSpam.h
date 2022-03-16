#pragma once
#include "Module.h"
class BowSpam : public IModule {
private:
	int charge = 0;
	bool findUseItem();
	int i = 0;
	bool autoshot = false;

public:
	bool shotOnce = false;

	BowSpam();
	~BowSpam();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModeName() override;

	//virtual void onPostRender(C_MinecraftUIRenderContext*) override;
	virtual void onTick(C_GameMode* gm) override;
	//virtual void onDisable() override;
};
