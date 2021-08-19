#pragma once
#include "Module.h"

class Watermark : public IModule {
public:
	Watermark();
	~Watermark();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};