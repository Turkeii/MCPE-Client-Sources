#include "Disabler.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

Disabler::Disabler() : IModule(0, Category::EXPLOIT, "Disables AntiCheats") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Nethergames", 0);
	mode.addEntry("Cubecraft", 1);
	mode.addEntry("Hive", 2);
}

Disabler::~Disabler() {
}

const char* Disabler::getRawModuleName() {
	return "Disabler";
}

const char* Disabler::getModuleName() {
	if (mode.getSelectedValue() == 0) name = std::string("Disabler ") + std::string(GRAY) + std::string("Nethergames");
	if (mode.getSelectedValue() == 1) name = std::string("Disabler ") + std::string(GRAY) + std::string("Cubecraft");
	if (mode.getSelectedValue() == 2) name = std::string("Disabler ") + std::string(GRAY) + std::string("Hive");
	return name.c_str();
}

void Disabler::onEnable() {
}

void Disabler::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	// Nethergames
	if (mode.getSelectedValue() == 0 && !player->onGround) {
		C_MovePlayerPacket pNether(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&pNether);
	}
}

void Disabler::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	// Nethergames
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		if (mode.getSelectedValue() == 0 && !player->onGround) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->onGround = true;
		}
	}

	// Cubecraft
	if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
		PlayerAuthInputPacket* authInputPacket = (PlayerAuthInputPacket*)packet;
		if (mode.getSelectedValue() == 1) authInputPacket->velocity = vec3_t(0, 0, 0);
	}
}