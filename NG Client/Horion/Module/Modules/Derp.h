#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Derp : public IModule {
public:
		int counter = 0;
		bool epicStroke = false;
		bool packetMode = false;
		bool hive = false;
		bool twerk = false;

	Derp() : IModule(0x0, Category::PLAYER, "lol you stupid") {
			registerBoolSetting("Twerk", &twerk, twerk);
			registerBoolSetting("Have A Stroke", &epicStroke, epicStroke);
			registerBoolSetting("Hive", &hive, hive);
			registerBoolSetting("Packet Mode", &packetMode, packetMode);
	};
	~Derp(){};

	void onTick(C_GameMode* gm) {
		if (twerk) {
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
			if (packetMode) {
				C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
				if (epicStroke && !hive) {
					C_LocalPlayer* player = g_Data.getLocalPlayer();
					player->yaw = player->bodyYaw + 180;
					p.pitch = (float)(rand() % 360);
					p.yaw = (float)(rand() % 360);
				} else {
					C_LocalPlayer* player = g_Data.getLocalPlayer();
					player->yaw = player->bodyYaw + 180;
					p.pitch = (float)(counter % 360);
					p.yaw = (float)(counter % 360);
				}
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			} else {
				if (epicStroke && !hive) {
					C_LocalPlayer* player = g_Data.getLocalPlayer();
					player->yaw = player->bodyYaw + 180;
					gm->player->pitch = (float)(rand() % 360);
					gm->player->bodyYaw = (float)(rand() % 360);
				} else if (!hive) {
					C_LocalPlayer* player = g_Data.getLocalPlayer();
					player->yaw = player->bodyYaw - 180;
				}
			}

			if (counter <= 360)
				counter++;
			else
				counter = 0;
		}
	}

	float randFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	void onSendPacket(C_Packet* packet) {
		if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && hive && g_Data.isInGame()) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->pitch = randFloat(-90, 90);
			movePacket->yaw = randFloat(-180, 180);
		}
	}

	virtual const char* getModuleName() override {
		return "Derp";
	}
};