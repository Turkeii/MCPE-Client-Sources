#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class FastUse : public IModule {
public:
    virtual const char* getModuleName() override;
    virtual void onTick(C_GameMode* gm) override;
    FastUse();
};