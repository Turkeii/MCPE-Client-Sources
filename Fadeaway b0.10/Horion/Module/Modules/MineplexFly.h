#pragma once
#include "Module.h"

class MineplexFly : public IModule {
private:
	int delay = 0;
	bool isBypass = false;
	float speedMod = 0.70;
	float yUp = 0.5;

public:
	C_MovePlayerPacket* jetpack = nullptr;
	MineplexFly();
	~MineplexFly();

	virtual void onTick(C_GameMode* gm) override;
	virtual bool isFlashMode() override;
	virtual void onDisable() override;
	virtual void onEnable() override;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
