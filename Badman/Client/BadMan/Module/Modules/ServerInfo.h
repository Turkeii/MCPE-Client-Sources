#pragma once
#include "Module.h"
class ServerInfo : public IModule {
public:
	ServerInfo();
	~ServerInfo();

	float scale = 1.f;
	float serverInfX = 100.f;
	float serverInfY = 100.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
