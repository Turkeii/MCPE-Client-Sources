#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class ExtendedBlockReach : public IModule {
private:
	float blockReach = 7.f;

public:
	ExtendedBlockReach() : IModule(0x0, Category::PLAYER, "Exteneded reach for placing/breaking blocks") {
		registerFloatSetting(std::string("reach"), &blockReach, blockReach, 7, 100);
	};
	~ExtendedBlockReach(){};

	inline float getBlockReach() { return blockReach; };
	inline void setBlockReach(float reach) { blockReach = reach; };
	virtual const char* getModuleName() override {
		return "BlockReach";
	}
};
