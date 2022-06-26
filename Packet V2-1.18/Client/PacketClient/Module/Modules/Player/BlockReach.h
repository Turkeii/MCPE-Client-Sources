#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class BlockReach : public IModule {
public:
	int distance = 255.f;

	inline float getBlockReach() { return distance; };
	inline void setBlockReach(float reach) { distance = reach; };
	virtual const char* getModuleName();
	BlockReach();
};