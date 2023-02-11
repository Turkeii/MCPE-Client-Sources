#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class ToggleSounds : public IModule {
public:
    float volume = 0.8f;

    std::string name = "ToggleSounds";
    SettingEnum sound = this;

    virtual const char* getRawModuleName() override;
    virtual const char* getModuleName() override;
    ToggleSounds();
};