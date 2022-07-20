#pragma once
#include "Module.h"
class EndermanLook : public IModule {
public:
	EndermanLook();
	~EndermanLook();
	
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};
