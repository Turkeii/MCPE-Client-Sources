#pragma once
#include "Module.h"
class Tracer : public IModule {
public:
	//registered settings
	int customR = 255;
	int customG = 255;
	int customB = 255;
	bool is2d = true;
	bool chest = false;
	int customR2 = 255;
	int customG2 = 255;
	int customB2 = 255;
	//Tracer
	bool isMob = false;
	bool RGB = true;
	SettingEnum type;

	//for the moddile of the screen shit
	vec3 cameraPos;
	vec2 cameraRot;

	//for chests
	std::vector<AABB> bufferedChestList;
	std::mutex listLock;

	Tracer();
	~Tracer();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onLevelRender() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* ctx) override;
	virtual void onTick(C_GameMode* gm) override;
};
