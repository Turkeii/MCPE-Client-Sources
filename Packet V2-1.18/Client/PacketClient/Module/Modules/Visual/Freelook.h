#pragma once
#include "../Module.h"
#include "../pch.h"

// what the aids

class Freelook : public IModule {
public:
	vec2_t oldPos;
	vec2_t Pos;

	Freelook() : IModule(0, Category::VISUAL, "Move straight while moving your camera around") {}

	virtual const char* getModuleName() { return "Freelook"; }
	void onEnable() { oldPos = g_Data.getLocalPlayer()->viewAngles; }
	void onDisable() { g_Data.getLocalPlayer()->applyTurnDelta(&oldPos); }
	bool callWhenDisabled() {
		return true;
	}
};