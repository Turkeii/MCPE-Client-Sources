#pragma once
#include "Module.h"
#include "../../../Utils/Target.h"

class EntityDerp : public IModule {
private:
	int counter = 0;
	bool epicStroke = false;
	bool packetMode = false;

public:
	EntityDerp();
	~EntityDerp();

	// Inherited via IModule
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};
