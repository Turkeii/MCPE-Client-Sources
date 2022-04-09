#pragma once
#include "Module.h"
class Freelook : public IModule {
public:
	vec2 oldPos;
	vec2 Pos;

	Freelook() : IModule(0x0, Category::VISUAL, "Move straight while moving your camera around") {}
	~Freelook(){};

	virtual const char* getModuleName() override { return "Freelook"; }
	void onEnable() override { oldPos = g_Data.getLocalPlayer()->viewAngles; }
	void onDisable() override { g_Data.getLocalPlayer()->applyTurnDelta(&oldPos); }
	bool callWhenDisabled() override {
		return true;
	}
};