#pragma once
#include "../../../../Utils/TargetUtil.h"
#include "../../ModuleManager.h"
#include "../Module.h"

class TargetStrafe : public IModule {
private:
	bool edgeCheck = true;
	bool visualize = true;
	bool testMode = true;
	bool control = false;
	float animYaw = 0.f;
	bool collide = true;
	bool behind = false;
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
	bool isStrafing = false;
	float radius = 2.5f;
	float speed = 0.5f;
	vec3_t playerVel;
	float range = 6;

	SettingEnum mode = this;

	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onMove(C_MoveInputHandler* input);
	virtual void onSendPacket(C_Packet* packet);
	virtual void onPlayerTick(C_Player* plr);
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onLevelRender();
	virtual void onDisable();
	virtual void onEnable();
	TargetStrafe();
};