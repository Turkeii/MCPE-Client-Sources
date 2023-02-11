#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Nuker : public IModule {
private:
	bool veinMiner = false;
	int radius = 4;
	int down = 4;
	int up = 4;

public:
	inline bool isAutoMode() { return !veinMiner; };
	int getNukerRadius() { return radius; };
	int getDownRadius() { return down; };
	int getUpRadius() { return up; };

	inline bool isVeinMiner() { return veinMiner; };

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	Nuker();
};
