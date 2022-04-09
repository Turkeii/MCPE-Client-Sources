#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Animations : public IModule {
public:
    bool shouldBlock = false;
    bool smoothSwing = false;
    bool translate = true;
    float xPos = 0.f;
    float yPos = 0.f;
    float zPos = 0.f;
    bool rotate = false;
    float xRotate = 0.f;
    float yRotate = 0.f;
    float zRotate = 0.f;
    bool scale = true;
    float xScale = 1.f;
    float yScale = 1.f;
    float zScale = 1.f;
    bool reset = false;

	Animations();
	~Animations();

    std::string name = "Animations";
    SettingEnum mode = this;


	// Inherited via IModule
    virtual void onEnable() override;
    virtual void onDisable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
};