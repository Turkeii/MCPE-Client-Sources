#pragma once
#include "Module.h"
class MinevilleFly : public IModule {
private:
	float glideMod = 0.0f;
	float glideModEffective = 0;
	float speed = 1.505f;

public:
	MinevilleFly();
	~MinevilleFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
