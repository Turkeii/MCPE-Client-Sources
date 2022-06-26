#pragma once

#include "../Module.h"

class AutoPot : public IModule {
private:
    bool shouldThrow = false;
    int health = 15;

    int Odelay = 0;
    int delay = 1;
public:
    AutoPot();

    std::string name = "AutoPot";
    SettingEnum mode = this;

    virtual void onSendPacket(C_Packet* packet);
    virtual void onPlayerTick(C_Player* plr);
    virtual const char* getRawModuleName();
    virtual void onTick(C_GameMode* gm);
    virtual const char* getModuleName();
};
