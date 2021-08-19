#pragma once
#include "Module.h"
class Glide : public IModule {
private:
	float glideMod = 0.00f;
	float glideModEffective = 0;
	bool hiveMode = false;
	bool jetpackMode = false;
	bool onkeydisableMode = false;
	bool strafeMode = false;
	bool boostMode = false;
	int timer = 230;
	bool penis = true;
	bool vanillaModeOld = false;

public:
	bool vanillaMode = false;
	int counter = 1;
	float speed2 = 0.f;
	bool hiveModeNew = false;
	float speed = 1.f;

	//SettingEnum dumbnigga;
	//static int constexpr nigga = 0;
	//static int constexpr bakkar = 1;

	Glide();
	~Glide();

	// Inherited via IModule
	virtual void onDisable() override;
	virtual bool isFlashMode() override;
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};