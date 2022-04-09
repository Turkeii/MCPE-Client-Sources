#pragma once
#include "Module.h"

class Nuker : public IModule {
private:
	int delay = 0;
	int nukerRadius = 50;
	int up = 1;
	int down = 1;
	bool veinMiner = false;
	bool autodestroy = true;

public:
	Nuker();
	~Nuker();

	inline bool isAutoMode() { return autodestroy; };
	int getNukerRadius() { return nukerRadius; };

	inline bool isVeinMiner() { return veinMiner; };
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};