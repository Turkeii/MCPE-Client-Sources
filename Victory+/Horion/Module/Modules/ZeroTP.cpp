#include "ZeroTP.h"

ZeroTP::ZeroTP() : IModule(0x0, Category::PLAYER, "0 0 0 teleporting!") {
}

ZeroTP::~ZeroTP() {
}

const char* ZeroTP::getModuleName() {
	return ("ZeroTP");
}

void ZeroTP::onTick(C_GameMode* gm) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	vec3_t pos;
	pos.x = 0;
	pos.y = 2;
	pos.z = 0;
	player->setPos(pos);
}