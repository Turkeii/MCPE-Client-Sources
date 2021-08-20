#include "NukkitNoFall.h"

NukkitNoFall::NukkitNoFall() : IModule(0x0, Category::SERVER, "Negates fall damage on some nukkit servers") {
}

NukkitNoFall::~NukkitNoFall() {
}

const char* NukkitNoFall::getModuleName() {
	return ("NukkitNoFall");
}

void NukkitNoFall::onSendPacket(C_Packet* packet) {

	if (g_Data.getLocalPlayer() != nullptr && g_Data.getLocalPlayer()->fallDistance > 2.f) {
			if (packet->isInstanceOf<C_MovePlayerPacket>()) {
				C_PlayerActionPacket p;
				p.action = 15;  //startglide action
				p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			}
	}
}