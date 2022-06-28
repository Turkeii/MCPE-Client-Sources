#pragma once
#include "../../DrawUtils.h"
#include "../ModuleManager.h"
#include "Module.h"

class Keystrokes : public IModule {
public:
	bool rainbow = false;
	Keystrokes();
	~Keystrokes();

	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	static float horizontal;
	static float vertical;
	static int rFloat;
	static int bFloat;
	static int gFloat;
	static void drawKeystroke(char key, const vec2_t& pos);
	static void drawLeftMouseKeystroke(vec2_t pos);
	static void drawRightMouseKeystroke(vec2_t pos);
};