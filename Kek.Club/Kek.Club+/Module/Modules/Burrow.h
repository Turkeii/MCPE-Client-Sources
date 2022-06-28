#pragma once
#include "Module.h"

class Burrow : public IModule {
public:
	bool spoof = false;
	bool down = false;
	bool up = false;
	bool antireversestep = true;
	vec3_t oldPos;
	bool center = true;
	bool setoldPos = true;
	bool Center();
	float motion = 0.5f;
	bool tryScaffold(vec3_t blockBelow);
	SettingEnum enum1;

	Burrow();
	~Burrow();

	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual bool isFlashMode() override;
	virtual void onSendPacket(C_Packet* packet) override;
};