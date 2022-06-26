#pragma once

#include "Module.h"

class DebugMenu : public IModule {
public:
    DebugMenu();

    std::string name = "DebugMenu";
    SettingEnum mode = this;

    virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx);
    virtual const char* getRawModuleName();
    virtual void onTick(C_GameMode* gm);
    virtual const char* getModuleName();
};