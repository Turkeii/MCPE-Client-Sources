#pragma once
#include "Module.h"
class Tracer : public IModule {
public:
	static int rFloat;
	static int bFloat;
	static int gFloat;
	 float thickness;
	Tracer();
	~Tracer();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onLevelRender() override;
	void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};