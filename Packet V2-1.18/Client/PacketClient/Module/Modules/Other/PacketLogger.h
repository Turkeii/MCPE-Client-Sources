#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class PacketLogger : public IModule {
public:
    virtual void onSendPacket(C_Packet* packet) override;
    virtual const char* getModuleName() override;
    PacketLogger();
};