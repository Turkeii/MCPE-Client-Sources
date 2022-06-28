#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class NoFall : public IModule {
public:
	int counter = 1;
	float glideMod = 0.f;
	float glideModEffective = 0;
	bool server = false;
	bool nopackety = false;
	float range = 3;
	SettingEnum fallMode;
	int fallTime = 0;

	NoFall() : IModule(0x0, Category::MOVEMENT, "Prevents fall damage on various servers") {
		registerEnumSetting("Mode", &fallMode, 0);
		fallMode = SettingEnum(this)
					   .addEntry(EnumEntry("Vanilla", 0))
					   .addEntry(EnumEntry("Motion", 1))
					   .addEntry(EnumEntry("Clip", 2))
					   .addEntry(EnumEntry("Packet", 3))
					   .addEntry(EnumEntry("PacketV2", 4))
					   .addEntry(EnumEntry("Test", 5));
	};
	~NoFall(){};

	void onSendPacket(C_Packet* packet) {
		if (g_Data.getLocalPlayer() == nullptr) return;

		if (fallMode.selected == 3) {
			if (packet->isInstanceOf<C_MovePlayerPacket>()) {
				C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				movePacket->onGround = true;
			}
		}

	}
	void onTick(C_GameMode* gm) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (g_Data.getLocalPlayer() == nullptr) return;

		if (fallMode.selected == 5) {
			fallTime++;
			if (fallTime == 11,12) {
				C_MovePlayerPacket offG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), false);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&offG);
			} else if (fallTime >= 13) {
				C_MovePlayerPacket onG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), true);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&onG);
				fallTime = 0;
			}
		}

		if (fallMode.selected == 4) {
			C_MovePlayerPacket onG(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos(), true);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&onG);
		}
		if (fallMode.selected == 0 && g_Data.getLocalPlayer()->fallDistance > 2.f) {
			gm->player->onGround = true;
		}
		if (fallMode.selected == 2 && gm->player->fallDistance > 4.f) {
			vec3_t pos = *gm->player->getPos();
			pos.y += 50;
			gm->player->tryTeleportTo(pos, true, true, 1, 1);
			gm->player->onGround = true;
			gm->player->fallDistance = 0.f;
		}
		if (fallMode.selected == 1) {
			if (player->fallDistance > 4) {
				glideModEffective = glideMod;
				gm->player->velocity.y = glideModEffective;
				g_Data.getLocalPlayer()->setPos((*g_Data.getLocalPlayer()->getPos()).add(0, 0.25, 0));
			}
		}
		if (counter == 5)
			counter = 0;
		else
			counter++;

		vec3_t blockBelow2 = g_Data.getLocalPlayer()->eyePos0; //Feet
		blockBelow2.y -= g_Data.getLocalPlayer()->height;
		blockBelow2.y -= 1.5f;// Block below the player
	}

	virtual const char* getModuleName() override {
		return "NoFall";
	}
	const char* NoFall::getModName() {
		if (fallMode.selected == 0)
			return " [Vanilla]";
		if (fallMode.selected == 1)
			return " [Motion]";
		if (fallMode.selected == 2)
			return " [Clip]";
		if (fallMode.selected == 3)
			return " [Packet]";
		if (fallMode.selected == 4)
			return " [PacketV2]";
		return "";
	}
};