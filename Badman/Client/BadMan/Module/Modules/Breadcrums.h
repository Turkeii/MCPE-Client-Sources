#pragma once
#include "Module.h"
class Breadcrums : public IModule {
public:
	Breadcrums();
	~Breadcrums();

	std::vector<vec3_t> linePoints;
	vec3_t startPos;
	vec3_t startPosTop;

	//settings
	bool clearOndisable = true;
	bool stopBreadCrums = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLevelRender() override;
	virtual void onDisable() override;
};
