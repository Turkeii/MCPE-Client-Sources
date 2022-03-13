#pragma once
#include "Module.h"

class PlayerList : public IModule {
public:
	PlayerList();
	~PlayerList();
	float scale = 1.f;
	bool thefellas = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};