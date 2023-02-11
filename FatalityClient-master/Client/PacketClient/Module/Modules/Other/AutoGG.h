#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class AutoGG : public IModule {
public:
    bool send = false;

    std::string name = "AutoGG";
    SettingEnum server = this;

    virtual const char* getRawModuleName();
    virtual void onTick(C_GameMode* gm);
    virtual const char* getModuleName();
    virtual void onEnable();
    AutoGG();
};