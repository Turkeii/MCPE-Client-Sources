#pragma once
#include "Module.h"

class Watermark : public IModule {
public:
	SettingEnum watermark;
	float opacity = 0.f;
	Watermark();
	~Watermark();

	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};