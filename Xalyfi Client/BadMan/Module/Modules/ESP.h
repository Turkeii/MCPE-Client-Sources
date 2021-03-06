#pragma once

#include "Module.h"
#include "../ModuleManager.h"

class ESP : public IModule {
public:
	bool isMobEsp = false;
	bool is2d = false;
	bool itemEsp = true;
	
	ESP();
	~ESP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
