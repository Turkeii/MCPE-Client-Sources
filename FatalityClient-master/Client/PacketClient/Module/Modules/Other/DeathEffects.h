#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class DeathEffects : public IModule {
public:
    bool killed = false;

    std::string name = "DeathEffects";
    SettingEnum mode = this;

    virtual void onTick(C_GameMode* gm) override;
    virtual const char* getRawModuleName();
    virtual const char* getModuleName();
    virtual void onEnable() override;
    DeathEffects();
};