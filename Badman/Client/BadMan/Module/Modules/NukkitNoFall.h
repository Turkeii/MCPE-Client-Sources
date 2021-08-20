#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class NukkitNoFall : public IModule {
private:

public:
	NukkitNoFall();
	~NukkitNoFall();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};
