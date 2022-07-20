#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class K3SReCrystal : public IModule {
private:
	SettingEnum dmgEnum;
	static int constexpr dmg_vanilla = 0;  // TODO: Implement ray tracing
	static int constexpr dmg_java = 1;
	bool isClick = false;
	int delay = 0;
	bool autoplace = true;
	bool spoof = false;
	bool Surrounded;
	int placed;
	bool doMultiple = false;

public:

	K3SReCrystal();
	~K3SReCrystal();

	int range = 7;

	bool isSideEmpty();

	bool checkSurrounded(C_Entity* entC);

	std::vector<vec3_t> SurChecker = {
		vec3_t(1, 0, 0),
		vec3_t(0, 0, 1),
		vec3_t(-1, 0, 0),
		vec3_t(0, 0, -1),
		vec3_t(0, -1, 0),
	};

	// Inherited via IModule
	virtual const char* getModuleName() override;
	//virtual const char* getModName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
