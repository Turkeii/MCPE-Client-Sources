#pragma once
#include "Module.h"
class XPFast : public IModule {
private:
	int charge = 7;

	int i = 0;

public:
	bool shotOnce = false;

	XPFast();
	~XPFast();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	//virtual void onPostRender(C_MinecraftUIRenderContext*) override;
	virtual void onTick(C_GameMode* gm) override;
	//virtual void onDisable() override;
};
