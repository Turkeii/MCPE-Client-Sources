#pragma once
#include "Module.h"
class Surround : public IModule {
public:
	SettingEnum enum1;
	bool renderSurround = true;
	bool disableOnComplete2 = true;
	bool doReset = true;
	bool silentSwitch = true;
	std::vector<vec3> surrArr;
	bool SilentSwap(const char* tile);
	std::vector<vec3> regularBlocks = {
		vec3(0, -1, 0),
		vec3(1, -1, 0),
		vec3(1, 0, 0),
		vec3(0, -1, 1),
		vec3(0, 0, 1),
		vec3(-1, -1, 0),
		vec3(-1, 0, 0),
		vec3(0, -1, -1),
		vec3(0, 0, -1),
	};
	std::vector<vec3> antiCityBlocks = {
		vec3(0, -1, 0),
		vec3(1, -1, 0),
		vec3(1, 0, 0),
		vec3(2, 0, 0),
		vec3(0, -1, 1),
		vec3(0, 0, 1),
		vec3(0, 0, 2),
		vec3(-1, -1, 0),
		vec3(-1, 0, 0),
		vec3(-2, 0, 0),
		vec3(0, -1, -1),
		vec3(0, 0, -1),
		vec3(0, 0, -2),
	};

	Surround();
	~Surround();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};