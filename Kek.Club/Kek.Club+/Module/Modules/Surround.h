#pragma once
#include "Module.h"
class Surround : public IModule {	
public:
	SettingEnum enum1;
	SettingEnum sound;
	SettingEnum render;
	bool renderSurround = true;
	bool disableOnComplete2 = true;
	bool doReset = true;
	bool silentSwitch = false;
	std::vector<vec3_t> surrArr;
	SettingEnum rotations;
	bool playSound = false;
	int tick_for_place = 4;
	static int constexpr rotations_off = 0;
	static int constexpr rotation = 1;
	static int constexpr rotations_arora = 2;
	bool jumpDisable = false;
	float Surround::rFloat{0};
	float Surround::gFloat{255};
	float Surround::bFloat{0};
	float Surround::thickness{1};
	float Surround::alpha{1};

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
	int y_level = 0;

	int tick_runs = 0;

	int offset_step = 0;

	int old_slot = -1;
	Surround();
	~Surround();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onLevelRender() override;
	virtual void onMove(C_MoveInputHandler* hand) override;
	virtual void onEnable() override;
};