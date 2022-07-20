#pragma once
#include "Module.h"
class MineplexBP : public IModule {
private:
	int counter = 0;

public:
	MineplexBP();
	~MineplexBP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};
