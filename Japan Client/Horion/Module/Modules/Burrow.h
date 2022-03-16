#pragma once
#include "Module.h"
class Burrow : public IModule {
private:
	int delay = 0;
	//bool tryBurrow (vec3_t blockBelow);

public:
	bool airplace = false;

	SettingEnum enum1;
	bool renderBurrow = true;
	bool doAirplace = false;
	Burrow();
	~Burrow();
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
		vec3_t(0, 0, 0),

	};
	std::vector<vec3_t> antiCityBlocks = {

		vec3_t(0, -1, 0),

		vec3_t(1, -1, 0),
		vec3_t(1, 0, 0),

		vec3_t(0, -1, 1),
		vec3_t(0, 0, 1),

		vec3_t(-1, -1, 0),
		vec3_t(-1, 0, 0),

		vec3_t(0, -1, -1),
		vec3_t(0, 0, -1),
		vec3_t(0, 0, 0),

	};
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onMove(C_MoveInputHandler* hand) override;
};