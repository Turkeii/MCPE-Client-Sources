#pragma once
#pragma once
#include "Module.h"

class PacketMine : public IModule {
public:
	int InstaDelay = 0.f;
	int minBreak = 0.f;
	bool dontBedrock = true;

	PacketMine();
	~PacketMine();
	// Inherited via IModule
	virtual const char* getModuleName() override;
};
