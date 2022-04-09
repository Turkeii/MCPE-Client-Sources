#pragma once
#include "Module.h"

class EntityJetpack : public IModule {
private:
	int delay = 0;
	bool isBypass = false;
	float speedMod = 1;

public:
	C_MovePlayerPacket* uwu = nullptr;
	EntityJetpack();
	~EntityJetpack();

	virtual void onTick(C_GameMode* gm) override;
	virtual bool isFlashMode() override;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};