#include "Disabler.h"
void Disabler::onPlayerTick(C_Player* plr) {
	int server = Server.selected;
	if (g_Data.getLocalPlayer() != nullptr && plr == g_Data.getLocalPlayer() && server == 0 && (moduleMgr->getModule<AutoCrystal>()->isEnabled() || moduleMgr->getModule<Surround>()->isEnabled() || moduleMgr->getModule<HoleFiller>()->isEnabled() || moduleMgr->getModule<SelfWeb>()->isEnabled()))
		plr->pitch = -90;
}
void Disabler::onSendPacket(C_Packet* packet) {
	//int server = Server.selected;
	//(server == 1 && packet->isInstanceOf<PlayerAuthInputPacket>()); 
	//	PlayerAuthInputPacket* packet1 = (PlayerAuthInputPacket*)packet;
	//	packet1->velocity = vec3_t(0, 0, 0);
	}
