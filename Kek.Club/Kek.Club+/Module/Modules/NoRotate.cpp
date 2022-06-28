#include "NoRotate.h"

#include "../../../SDK/CAttribute.h"
#include "../../../Utils/TimerUtils.h"

NoRotate::NoRotate() : IModule(0, Category::PLAYER, "Prevents servers from setting your rotation") {
	registerBoolSetting("Body", &body, body);
}

NoRotate::~NoRotate() {
}

const char* NoRotate::getModuleName() {
	return "NoRotate";
}
void NoRotate::onTick(C_GameMode* gm) {
	static TimerUtils* timerUtil = new TimerUtils();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}
void NoRotate::onPlayerTick(C_Player* plr) {
	auto killaura = moduleMgr->getModule<Killaura>();
	if (!killaura->targetListA) return;
	if (plr == nullptr) return;
	if (body) plr->bodyYaw = plr->yaw;
}
void NoRotate::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
		if (g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys() && body) {
		}
	}
}