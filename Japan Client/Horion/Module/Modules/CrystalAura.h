#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class CrystalAura : public IModule {
private:
	int delay = 0;
	bool autoplace = true;
	bool spoof = false;
	bool Surrounded;
	int placed;
	bool doMultiple = false;
	bool autoswitch = false;
	int OldSlot;
	bool switched = false;
	bool HurtTime = false;
	bool VisTarget = false;
	bool multi = true;

	SettingEnum RotMode;
	static int constexpr rot_none = 0;  // TODO: Implement ray tracing
	static int constexpr rot_silent = 1;
	static int constexpr rot_client = 2;

public:
	CrystalAura();
	~CrystalAura();

	int range = 7;
	int timer5 = 0;
	bool info = false;
	bool render = false;
	std::vector<vec3_t> SurChecker = {
		vec3_t(1, 0, 0),
		vec3_t(0, 0, 1),
		vec3_t(-1, 0, 0),
		vec3_t(0, 0, -1),
		vec3_t(0, -1, 0),
	};

	SettingEnum dmgEnum;
	static int constexpr dmg_vanilla = 0;  // TODO: Implement ray tracing
	static int constexpr dmg_java = 1;
	static int constexpr dmg_2b2e = 2;
	static int constexpr dmg_2b2elow = 3;
	int previousSlot = -1;
	bool noSilent = false;
	bool silent = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	//virtual void onLevelRender() override;
	// virtual const char* getModName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	bool findCrystal(C_GameMode* gm);
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
