#pragma once
#include "Module.h"
class Tracer : public IModule {
public:
	//registered settings
	int customR = 255;
	int customG = 255;
	int customB = 255;
	bool is2d = false;
	bool chest = false;
	int customR2 = 255;
	int customG2 = 255;
	int customB2 = 255;

	//for the moddile of the screen shit
	vec3_t cameraPos;
	vec2_t cameraRot;

	//for chests
	std::vector<std::shared_ptr<AABB>> bufferedChestList;
	std::mutex listLock;

	Tracer();
	~Tracer();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onLevelRender() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* ctx) override;
	virtual void onTick(C_GameMode* gm) override;
};
