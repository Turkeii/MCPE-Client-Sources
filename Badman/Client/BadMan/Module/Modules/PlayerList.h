#pragma once
#include "Module.h"
class PlayerList : public IModule {
public:
	PlayerList();
	~PlayerList();

	float scale = 0.9f;
	bool armour = true;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
