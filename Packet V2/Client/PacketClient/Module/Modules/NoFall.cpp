#include "NoFall.h"

NoFall::NoFall() : IModule(0, Category::EXPLOIT, "Prevent you from taking fall damage") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Packet", 0);
	mode.addEntry("Motion", 1);
	mode.addEntry("Hive", 2);
	registerIntSetting("Distance", &dist, dist, 3, 8);
}

const char* NoFall::getRawModuleName() {
	return "NoFall";
}

const char* NoFall::getModuleName() {
	if (mode.getSelectedValue() == 0) {
		name = std::string("NoFall ") + std::string(GRAY) + std::string("Packet");
		return name.c_str();
	} else if (mode.getSelectedValue() == 1) {
		name = std::string("NoFall ") + std::string(GRAY) + std::string("Motion");
		return name.c_str();
	} else if (mode.getSelectedValue() == 2) {
		name = std::string("NoFall ") + std::string(GRAY) + std::string("Hive");
		return name.c_str();
	}
}

void NoFall::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;
	vec3_t blockBelow = player->eyePos0;
	blockBelow.y -= player->height;
	blockBelow.y -= 2.62f;
	vec3_t pos;
	if (mode.getSelectedValue() == 0) {  // Packet
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		p.onGround = true;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
	if (mode.getSelectedValue() == 1 && gm->player->fallDistance >= dist) {  // Motion
		gm->player->velocity.y = 0.0001f;
		gm->player->fallDistance = 0;
	}
	if (mode.getSelectedValue() == 2) {  // Hive
		if (player->fallDistance >= dist) {
			C_BlockLegacy* blockLegacy = (player->region->getBlock(blockBelow)->blockLegacy);
			if (blockLegacy->blockId != 0 && blockLegacy->material->isSolid) {
				gm->player->velocity = vec3_t(0, 0, 0);
				gm->player->fallDistance = 0;
				pos.x = 0.f + pPos.x;
				pos.y = 0.3f + pPos.y;
				pos.z = 0.f + pPos.z;
				g_Data.getLocalPlayer()->setPos(pos);
			}
		}
	}

	vec3_t blockBelowBF = g_Data.getLocalPlayer()->eyePos0;
	blockBelowBF.y -= g_Data.getLocalPlayer()->height;
	blockBelowBF.y -= 1.5;
	if (mode.getSelectedValue() == 3) {
		if (gm->player->onGround)
			gm->player->fallDistance = 0;

		if (gm->player->fallDistance >= dist && ((gm->player->region->getBlock(blockBelowBF)->blockLegacy))->blockId != 0 && ((gm->player->region->getBlock(blockBelowBF)->blockLegacy))->material->isSolid) {
			gm->player->velocity.y = .001f;
			gm->player->fallDistance = 0;
		}
	}
}