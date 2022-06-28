#pragma once
#include "Module.h"

class SelfWeb : public IModule {
public:
	bool center = false;
	bool Center();
	bool CenterBlock();
	bool centerblock = false;
	float motion = 0.5f;
	bool tryScaffold(vec3_t blockBelow);
	bool webz = true;
	bool rots = false;
	bool spoof = false;
	SelfWeb();
	~SelfWeb();

	virtual const char* getModuleName() override;
	virtual bool isFlashMode() override;
	virtual void onPreTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPlayerTick(C_Player* plr) override;
};