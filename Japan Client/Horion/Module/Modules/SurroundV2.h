
#pragma once
#include "Module.h"

class SurroundV2 : public IModule {
private:
	int delay = 0;
	//bool citySwitch = true;

public:
	SettingEnum switchmode;
	static int constexpr none = 0;
	static int constexpr normal2 = 1;
	static int constexpr swap = 2;  
	static int constexpr spoof = 3;
	static int constexpr spoof_old = 4;

	SettingEnum blockmode;
	static int constexpr normal = 0;
	static int constexpr anticity = 1;

	SettingEnum rotations;
	static int constexpr none1 = 0;
	static int constexpr client = 1;
	static int constexpr silent = 2; 
	static int constexpr smooth = 3;  

	int origSlot;
	bool jumpDisable = true;
	bool renderSurround = true;
	bool blockface = false;
	SurroundV2();
	~SurroundV2();
	int BlockPerTick = 1;
	vec2_t angle;
	std::vector<vec3_t> Normal3 = {

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
	std::vector<vec3_t> antiCityBlocks = {

		vec3_t(0, -1, 0),

		vec3_t(1, -1, 0),
		vec3_t(1, 0, 0),
		vec3_t(2, 0, 0),

		vec3_t(0, -1, 1),
		vec3_t(0, 0, 1),
		vec3_t(0, 0, 2),

		vec3_t(-1, -1, 0),
		vec3_t(-1, 0, 0),
		vec3_t(-2, 0, 0),

		vec3_t(0, -1, -1),
		vec3_t(0, 0, -1),
		vec3_t(0, 0, -2),

	};

	bool isSideEmpty();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModeName() override;

	virtual void onTick(C_GameMode* gm) override;
	//virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable();
	virtual void onMove(C_MoveInputHandler* hand) override;
};
