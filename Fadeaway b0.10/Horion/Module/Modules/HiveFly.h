#pragma once
#include "Module.h"

class HiveFly : public IModule {
private:
	int delay = 0;
	bool isBypass = false;
	float speedMod = 0.55;

public:
	C_MovePlayerPacket* jetpack = nullptr;
	HiveFly();
	~HiveFly();

	virtual void onTick(C_GameMode* gm) override;
	virtual bool isFlashMode() override;
	virtual void onDisable() override;
	virtual void onEnable() override;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
