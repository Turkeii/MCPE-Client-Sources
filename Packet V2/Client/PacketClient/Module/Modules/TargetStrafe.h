#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class TargetStrafe : public IModule {
private:
	bool edgeCheck = true;
	bool drawCircle = true;
	bool testMode = true;
	bool control = false;
	bool collide = true;
	bool test = false;
	bool onKey = true;

	bool clockwise = false;
	int intersectingTimer = 0;
	int intersectingTimer2 = 0;
	bool initRender = false;
	int renderTimer = 0;
	bool useVel = false;

public:
	bool targetListEmpty = true;
	float radius = 2.5f;
	float speed = 0.5f;
	float range = 6;

	vec3_t playerVel;

	TargetStrafe();
	~TargetStrafe();

		SettingEnum mode = this;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onLevelRender() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};