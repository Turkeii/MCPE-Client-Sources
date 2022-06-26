#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class AutoPlay : public IModule {
private:
    bool isHitingKeys = false;
    float distance = 1.1f;
    float animYaw = 0.f;
    int timer = 20;

public:
    AutoPlay();

    std::string name = "AutoPlay";
    SettingEnum rotations = this;
    SettingEnum server = this;

    // Inherited via IModule
    virtual void onSendPacket(C_Packet* packet);
    virtual void onPlayerTick(C_Player* plr);
    virtual const char* getRawModuleName();
    virtual const char* getModuleName();
    virtual void onTick(C_GameMode* gm);
    virtual void onLevelRender();
    virtual void onDisable();
    virtual void onEnable();
};