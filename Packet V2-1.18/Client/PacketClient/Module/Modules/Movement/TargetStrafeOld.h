#pragma once
#include "../../../../Utils/TargetUtil.h"
#include "../../ModuleManager.h"
#include "../Module.h"

class TargetStrafeOld : public IModule {
private:
	bool autoplayMode = false;
	bool jump = false;
	bool flyMode = false;
	bool testMode = true;
	bool goback = false;
	bool clockwise = false;
	int intersectingTimer = 0;
	int intersectingTimer2 = 0;
	bool avoidvoid = true;
	bool collide = true;
public:
	float StrafeDistance = 3.f;
	float speedMod = 0.5f;
	bool packetMode = false;
	bool speedCheck = true;
	bool spacekeyMode = true;
	bool isMobAura = false;
	float range = 6;
	int gayTimer = 0;

	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onMove(C_MoveInputHandler* input);
	virtual void onSendPacket(C_Packet* packet);
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onEnable();
	TargetStrafeOld();
};