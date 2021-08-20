#pragma once
#include "Module.h"
class Surround : public IModule {
private:
	int delay = 0;

public:
	float float1 = 0;
	
	SettingEnum enum1;
	bool renderSurround = true;
	bool doAirplace = false;
	Surround();
	~Surround();
	bool blockSwap = true;
	int prevSlot3 = -1;

	bool jumpDisable = false;
	bool disableOnComplete2 = true;

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


	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual bool isFlashMode() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onMove(C_MoveInputHandler* hand) override;
};