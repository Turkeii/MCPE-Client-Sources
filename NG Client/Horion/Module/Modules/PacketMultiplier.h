#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class PacketMultiplier : public IModule {
public:
	int multiplier = 1;

	PacketMultiplier::PacketMultiplier() : IModule(0x0, Category::SERVER, "funni packet exploit") {
		registerIntSetting("Multiplier", &multiplier, multiplier, 1, 10);
	};
	~PacketMultiplier(){};

	virtual const char* getModuleName() override {
		return "PacketMultiplier";
	}
};
