#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class TargetStrafe : public IModule {
private:
public:
	bool jump = false;
	int counter = 1;
	bool hive = false;
	bool isMobAura = false;
	float range = 5;
	float Srange = 5;
	float speed = 0.325f;
	bool targetListB = false;
	vec2 hoe;

	TargetStrafe();
	~TargetStrafe();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onLevelRender() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};