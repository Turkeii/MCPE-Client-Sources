#pragma once
#include "Module.h"
class PacketLogger : public IModule {
public:
	bool packetadd;
	bool showauthinput;
	bool showsubchunk;
	SettingEnum addressType;
	PacketLogger();
	~PacketLogger();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};
