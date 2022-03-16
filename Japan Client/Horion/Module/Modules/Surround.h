/*
#pragma once
#include "Module.h"

class Surround : public IModule {


private:
	int delay = 0;
	bool citySwitch = true;

public:
	bool on = false;
	bool rotations = true;
	int origSlot;
	
	SettingEnum enum1;
	bool renderSurround = true;
	bool doAirplace = false;
	Surround();
	~Surround();
	bool blockSwap = true;
	int prevSlot3 = -1;
	int swapChecker = 0;
	bool jumpDisable = true;
	bool disableOnComplete2 = true;
	vec2_t angle;
	std::vector<vec3_t> regularBlocks = {

		vec3_t(0, -1, 0),

		vec3_t(1, -1, 0),
		vec3_t(1, 0, 0),

		vec3_t(0, -1, 1),
		vec3_t(0, 0, 1),

		vec3_t(-1, -1, 0),
		vec3_t(-1, 0, 0),

		vec3_t(0, -1, -1),
		vec3_t(0, 0, -1),

	};


	std::vector<vec3_t> sidesBlocksOnly = {
		vec3_t(1, 0, 0),
		vec3_t(0, 0, 1),
		vec3_t(-1, 0, 0),
		vec3_t(0, 0, -1),
		vec3_t(0, -1, 0),
	};

	//void getObby();
	bool isSideEmpty();
	void onMove(C_MoveInputHandler* hand);
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModeName() override; 

	virtual bool isFlashMode() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	//virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable();
	//virtual void onMove(C_MoveInputHandler* hand) override;
	
};
*/