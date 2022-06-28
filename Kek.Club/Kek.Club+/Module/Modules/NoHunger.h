#pragma once
#include "Module.h"
class NoHunger : public IModule {
private:
	bool noFunni = false;
	bool keyPressed = false;

public:
	NoHunger();
	~NoHunger();

	virtual void onSendPacket(C_Packet* packet) override;
	virtual const char* getModuleName() override;
};
