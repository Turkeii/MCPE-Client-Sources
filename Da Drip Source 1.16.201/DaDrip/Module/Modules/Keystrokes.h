#pragma once
#include "Module.h"
#include "../../DrawUtils.h"
#include "ColorCustomizer.h"
#include "../ModuleManager.h"

class Keystrokes : public IModule {
public:

	Keystrokes();
	~Keystrokes();

	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	static float horizontal;
	static float vertical;
	static float rFloat;
	static float bFloat;
	static float gFloat;
	static bool chroma;
	static bool outline;
	static bool cps;
};