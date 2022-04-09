#pragma once

#include "Module.h"

class EZspam : public IModule {
private:

public:
	SettingEnum mode;
	bool ezTogglev3 = false;
	bool ezTogglev2 = false;
	bool ezToggle = false;
	int onLength = 5;
	int offLength = 5;
	int timer1 = 0;
	int timer2 = 0;
	bool blinkBool1 = false;
	bool blinkBool2 = false;

	EZspam();
	virtual const char* getModuleName();
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual bool isFlashMode() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};