#pragma once

#include "../../ModuleManager.h"
#include "../Module.h"

class Regen : public IModule {
private:
    bool selectPickaxe();
    float animYaw = 0.f;
    vec3_ti blockPos;

    float range = 4.5f;
    int delay = 6;

    int tick = 0;
    int slot = 0;
public:
    bool hasDestroyed = false;
    bool destroy = false;
    int blocksBroke = 0;
    bool swing = false;

    std::string name = "Regen";
    SettingEnum mode = this;

    virtual void onSendPacket(C_Packet* packet);
    virtual void onPlayerTick(C_Player* plr);
    virtual const char* getRawModuleName();
    virtual const char* getModuleName();
    virtual void onTick(C_GameMode* gm);
    virtual void onDisable();
    virtual void onEnable();
    Regen();
};