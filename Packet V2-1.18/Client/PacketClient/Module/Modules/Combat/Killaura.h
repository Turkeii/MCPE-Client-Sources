#pragma once
#include "../../../../Utils/TargetUtil.h"
#include "../../ModuleManager.h"
#include "../Module.h"

class Killaura : public IModule {
private:
    float smoothing = 6.f;
    float xRandom = 0.f;
    float yRandom = 0.f;
public:
    bool targetListEmpty = true;
    bool autoDisable = false;
    bool hurttime = false;
    bool visualize = true;
    float animYaw = 0.f;
    bool strafe = false;
    float random = 1.f;
    bool click = false;
    bool hold = false;
    bool mobs = false;

    float range = 8.f;
    int maxAPS = 20;
    int minAPS = 20;
    int delay = 0;
    int APS = 11;

    std::string name = "Killaura";
    SettingEnum rotations = this;
    SettingEnum mode = this;

    Killaura();

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