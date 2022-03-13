#pragma once
#include "../../../Utils/Target.h"
#include "Module.h"
class SpeedBypass : public IModule {
private:
	int timer = 50;
	bool endzone = false;
	bool Bypass = false;
	int Odelay = 0;

public:
	SpeedBypass();
	~SpeedBypass();

	std::vector<vec3_t> linePoints;
	vec3_t startPos;
	vec3_t startPosTop;

	// Inherited via IModule
	void onLevelRender() override;
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	//virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
	bool clearOndisable = true;
	bool stopBreadCrums = false;
};