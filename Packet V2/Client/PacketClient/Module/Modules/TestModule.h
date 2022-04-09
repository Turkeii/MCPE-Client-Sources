#pragma once

#include "Module.h"

class TestModule : public IModule {
private:
	int duration = 1;
	bool test2 = false;
	float speed = 0.f;
	float glideModEffective = -0;
	int counter = 1;
	int testCounter = 0;
	bool test = false;
	bool autoDisable = true;
	bool alertBox = false;
	bool blink = false;
	bool serverMode = false;
	bool banUMode = false;
	bool istpMode = false;
	bool istpModeTwo = false;
	bool dmgflyMode = false;
	bool dmgMode = false;
	float tpSpeed = 3288.50f;
	bool randomThing = false;
	int testTimer = 0;
	int hasJumped = 0;

	float speedDetector = 0;
	bool detectedSpeed = false;
	bool kowBool = false;
	bool kowBool2 = false;
	int kowInt1 = 0;
	int kowInt2 = 0;
	float glideMod = -0.0f;
	float kowFloat = 2;

public:
	// testing
	float sliderX = 0.f;
	float sliderY = 0.f;
	float sliderZ = 0.f;

	TestModule();
	virtual const char* getModuleName();
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual bool isFlashMode() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};