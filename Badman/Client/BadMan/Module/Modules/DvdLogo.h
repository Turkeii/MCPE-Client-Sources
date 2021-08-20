#pragma once
#include "Module.h"
class DvdLogo : public IModule {
public:
	DvdLogo();
	~DvdLogo();

	float scale = 2.0f;
	vec2_t pos;
	bool positiveX = false;
	bool positiveY = false;
	int colorR;
	int colorG;
	int colorB;
	
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
