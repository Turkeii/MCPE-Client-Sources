#pragma once
#include "Module.h"
class Tracer : public IModule {
public:
	SettingEnum type;
	bool isMob = false;
	bool RGB = true;
	bool isPlayer = true;
	Tracer();
	~Tracer();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* ctx) override;
};
