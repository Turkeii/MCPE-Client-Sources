#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class Animations : public IModule {
private:
    bool reset = false;
    bool swing = true;
public:
    float xPos = 0.f, yPos = 0.f, zPos = 0.f;
    bool shouldBlock = false;
    bool isAttacking = false;
    bool smoothSwing = false;

    // Unused
    bool translate = true;
    bool rotate = false;
    float xRotate = 0.f, yRotate = 0.f, zRotate = 0.f;

    bool scale = true;
    float xScale = 1.f, yScale = 1.f, zScale = 1.f;

    std::string name = "Animations";
    SettingEnum mode = this;

    virtual void onPlayerTick(C_Player* plr);
    virtual const char* getRawModuleName();
    virtual const char* getModuleName();
    virtual void onTick(C_GameMode* gm);
    virtual void onDisable();
    virtual void onEnable();
    Animations();
};