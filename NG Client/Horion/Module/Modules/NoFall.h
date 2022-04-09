#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class NoFall : public IModule {
public:
	bool groundy = false;
	int counter = 1;
	bool hive = true;
	bool motion = false;
	float glideMod = 0.f;
	float glideModEffective = 0;
	bool server = false;
	bool nopackety = false;
	float range = 3;

	NoFall() : IModule(0x0, Category::SERVER, "Prevents fall damage on various servers"){
		registerBoolSetting("OnGround", &groundy, groundy);
		registerBoolSetting("Server", &server, server);
		registerBoolSetting("NoPacket", &nopackety, nopackety);
		registerBoolSetting("Motion", &motion, motion);
		registerBoolSetting("Hive", &hive, hive);	
	};
	~NoFall(){};

	void onTick(C_GameMode* gm) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (groundy && g_Data.getLocalPlayer() != nullptr && g_Data.getLocalPlayer()->fallDistance > 2.f) {
			gm->player->onGround = true;
		}
		if (hive && gm->player->fallDistance > 4.f) {
			vec3 pos = *gm->player->getPos();
			pos.y += 50;
			gm->player->tryTeleportTo(pos, true, true, 1, 1);
			gm->player->onGround = true;
			gm->player->fallDistance = 0.f;
		}
		if (motion) {
			if (player->fallDistance > 4) {
				glideModEffective = glideMod;
				gm->player->velocity.y = glideModEffective;
				g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(0, 0.25, 0));  //sets how much u need
			}
		}
		if (counter == 5)
			counter = 0;
		else
			counter++;

		vec3 blockBelow2 = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
		blockBelow2.y -= g_Data.getLocalPlayer()->height;
		blockBelow2.y -= 1.5f;
	}

	virtual const char* getModuleName() override {
		return "NoFall";
	}
};