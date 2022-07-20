#pragma once
#include "Module.h"

class Freecam : public IModule {
private:
	vec3_t oldPos;
	float speed = 0.325f;
	float vspeed = 0.3f;

public:
	Freecam();
	~Freecam();

	vec3_t targetPos;
	vec2_t cameraRot = {0.f, 0.f};
	vec3_t lastPos;
	bool wasDisabled = false;
	float glideMod = -0.00f;
	float glideModEffective = 0;
	int Oldgamemode = 0;
	bool gCam = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPostRender(C_MinecraftUIRenderContext*) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};