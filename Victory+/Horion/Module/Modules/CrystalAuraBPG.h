#pragma once
#include "../../../Utils/Logger.h"
#include "../../../Utils/Utils.h"
#include "../ModuleManager.h"
#include "Module.h"

class CrystalAuraBPG : public IModule {
private:
	int delay = 0;               // how many ticks t wait before calculating next position
	int amount = 1;              // how many crystals to place. It is a bit complicated how this value is used for MultiAura
	int proximity = 3;           // how close to the enemy the crystal must be
	bool dontautoplace = false;  // whether to place crystals.
	bool multiaura = false;      // whether to calculate crystal positions for multiple enemies.
	bool lowpower = true;        // only run sorting algorithm once
	bool onclick = false;
	bool doRender = true;  // whether to do rendering stuff at all
	bool renderPlacement = false;
	bool renderCrystal = false;
	bool renderTrace = false;
	bool java = true;
	bool SilentSwitch = false;
	bool findSwitchId();

	int mode = 1;

	vec3_t placePos;
	vec3_t crystalPosition;
	vec3_t traceStart;
	vec3_t traceEnd;

public:
	CrystalAuraBPG();
	~CrystalAuraBPG();

	std::vector<vec3_t> validPositions;

	int minrange = 2;   // the minimum distance to place crystals
	int maxrange = 10;  // the maximum distance to place crystals because anticheat

	int calculations;
	int sorts;

	std::vector<float> packFloatArray(vec3_t a);
	vec3_t unpackFloatArray(std::vector<float> a);

	bool safe = false;  // only explode crystals that where placed by the player

	std::vector<std::vector<C_Entity*>> ents;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	void findOptimalBlock(std::vector<C_Entity*> list, C_GameMode* gm);
	std::vector<vec3_t> sortByDamage(std::vector<vec3_t> posList, std::vector<int> damageValues, bool preferLow);
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	std::vector<int> dmgVals;
	int getExplosionDamage(vec3_t pos1, vec3_t pos2);
	bool checkSurrounded(C_Entity* entC);
	vec3_t getGucciPlacement(C_Entity* entD);
};
