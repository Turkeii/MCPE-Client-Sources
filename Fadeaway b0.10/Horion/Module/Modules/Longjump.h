#pragma once
#include "Module.h"

class Longjump : public IModule {
private:
	int delay = 0;
	int hasJumped = 0;
	float speedMod = 1;
	float upvel = 0.35f;
	bool isBypass = false;
	bool yoight = false;
	int doot = 0;

public:
	C_MovePlayerPacket* jetpack = nullptr;
	Longjump();
	~Longjump();

	virtual void onTick(C_GameMode* gm) override;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
