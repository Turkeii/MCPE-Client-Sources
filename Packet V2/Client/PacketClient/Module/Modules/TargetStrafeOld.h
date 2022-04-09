#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

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

	TargetStrafeOld();
	~TargetStrafeOld();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	//void onLevelRender() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};