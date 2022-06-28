#pragma once
#include "Module.h"

class Jetpack : public IModule {
private:
	int delay = 0;
	bool isBypass = false;
	float speedMod = 1;

public:
	C_MovePlayerPacket* jetpack = nullptr;
	Jetpack();
	~Jetpack();

	virtual void onLevelRender() override;
	virtual bool isFlashMode() override;
	virtual const char* getModuleName() override;
};
