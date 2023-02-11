#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class HitEffects : public IModule {
private:
    float volume = 0.8f;
    int delay = 0;
    int tick = 0;
public:
    std::string name = "HitEffects";
    SettingEnum sound = this;

    virtual void onAttack(C_Entity* entity) override;
    virtual const char* getRawModuleName() override;
    virtual void onTick(C_GameMode* gm) override;
    virtual const char* getModuleName() override;
    void onEnable() override;
    HitEffects();
};