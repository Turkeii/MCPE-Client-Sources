#include "Breaker.h"
#include "../pch.h"

using namespace std;
Breaker::Breaker() : IModule(0, Category::OTHER, "Breaks certain blocks around you") {
	registerEnumSetting("Rotations", &rotations, 0);
	rotations.addEntry("Normal", 0);
	rotations.addEntry("Silent", 1);
	rotations.addEntry("None", 2);
	registerBoolSetting("Treasures", &treasures, treasures);
	registerBoolSetting("Cakes", &cakes, cakes);
	registerBoolSetting("Beds", &beds, beds);
	registerBoolSetting("Eggs", &eggs, eggs);
	registerBoolSetting("Swing", &swing, swing);
	registerIntSetting("Range", &range, range, 1, 10);
	//registerIntSetting("Delay", &delay, delay, 0, 20);
}

const char* Breaker::getRawModuleName() {
	return "Breaker";
}

const char* Breaker::getModuleName() {
	name = string("Breaker ") + string(GRAY) + to_string((int)range);
	return name.c_str();
}

void Breaker::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				blockPos = vec3_ti(x, y, z);
				destroy = false;
				eat = false;
				auto id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (id == 74 && redstone) destroy = true; // Lit Redstone Ore
				if (id == 73 && redstone) destroy = true; // Redstone Ore
				if (id == 26 && beds) destroy = true;      // Beds
				if (id == 122 && eggs) destroy = true;     // Eggs
				if (id == 92 && cakes) eat = true;         // Cakes

				if (g_Data.canUseMoveKeys()) {
					if (destroy) {
						bool isDestroyed = false;
						gm->startDestroyBlock(blockPos, 1, isDestroyed);
						gm->destroyBlock(&blockPos, 0);
						g_Data.getLocalPlayer()->swing();
						return;
					}

					if (eat) {
						gm->buildBlock(&blockPos, 0);
						g_Data.getLocalPlayer()->swing();
						return;
					}
				}
			}
		}
	}

	if (treasures) {
		static auto breaker = moduleMgr->getModule<Breaker>();
		g_Data.forEachEntity([](C_Entity* ent, bool b) {
			string name = ent->getNameTag()->getText();
			int id = ent->getEntityTypeId();

			if (name.find("Treasure") != string::npos && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= 5) {
				breaker->delay++;
				if (breaker->delay >= 20) {
					if (breaker->swing) g_Data.getLocalPlayer()->swing();
					g_Data.getCGameMode()->attack(ent);
					breaker->delay = 0;
				}
			}
		});
	}
}

void Breaker::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (destroy || eat && g_Data.canUseMoveKeys()) {
		// draw Abstraction on eggs what is a distraction what the hell is a giraffe's you don't like what the fuc what is a fractional rate
	}
}

void Breaker::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	vec2_t angle = player->getPos()->CalcAngle(vec3_t(blockPos.x, blockPos.y, blockPos.z));
	if (animYaw > angle.y)
		animYaw -= ((animYaw - angle.y) / 10);
	else if (animYaw < angle.y)
		animYaw += ((angle.y - animYaw) / 10);

	// Normal
	if (g_Data.canUseMoveKeys() && !moduleMgr->getModule<Killaura>()->targetListEmpty&& rotations.getSelectedValue() == 0) {
		if (destroy || eat) {
			plr->bodyYaw = animYaw;
			plr->yawUnused1 = animYaw;
			plr->pitch = angle.x;
		}
	}
}

void Breaker::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	// Silent
	if (packet->isInstanceOf<C_MovePlayerPacket>() && rotations.getSelectedValue() == 1) {
		if (destroy || eat) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(vec3_t(blockPos.x, blockPos.y, blockPos.z));
			movePacket->headYaw = animYaw;
			movePacket->yaw = animYaw;
			movePacket->pitch = angle.x;
		}
	}
}

void Breaker::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}