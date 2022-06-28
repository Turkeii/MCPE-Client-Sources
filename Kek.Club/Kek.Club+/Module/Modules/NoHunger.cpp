#include "NoHunger.h"

NoHunger::NoHunger() : IModule(0, Category::PLAYER, "Prevents you from getting Hungry") {
	registerBoolSetting("CancelSprint", &noFunni, noFunni);
}
NoHunger::~NoHunger() {
}

const char* NoHunger::getModuleName() {
	return "NoHunger";
}

void NoHunger::onSendPacket(C_Packet* packet) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->onGround = (player->fallDistance >= 0.0f);

		if (noFunni) {
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			if (noFunni || GameData::isKeyDown(*input->forwardKey))
				g_Data.getCGameMode()->player->setSprinting(false);
		}
	}
}
//haha ported phobos code troll