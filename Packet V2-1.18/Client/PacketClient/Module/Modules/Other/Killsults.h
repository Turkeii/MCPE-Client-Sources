#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Killsults : public IModule {
public:
    bool killed = false;

    std::string name = "Killsults";
    SettingEnum mode = this;

    virtual void onPlayerTick(C_Player* plr);
    virtual const char* getRawModuleName();
    virtual const char* getModuleName();
    virtual void onEnable();
    Killsults();
};