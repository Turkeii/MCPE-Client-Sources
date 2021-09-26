#pragma once
#include "Module.h"
class Teleport : public IModule {
private:
	float blockReach = 500.f;
	bool hasClicked = false;
	bool onlyHand = false;
	bool bypass = false;
	bool shouldTP = false;
	vec3_t tpPos;

public:
	Teleport();
	~Teleport();

	// Inherited via IModule
	inline float getBlockReach() { return blockReach; };
	inline void setBlockReach(float reach) { blockReach = reach; };
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};
