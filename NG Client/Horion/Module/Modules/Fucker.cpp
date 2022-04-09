#include "Fucker.h"

#include "../../../SDK/CAttribute.h"

Fucker::Fucker()
	: IModule(VK_NUMPAD9, Category::WORLD, "Destroys specific things around you") {
	registerBoolSetting("Rotations", &rots, rots);
	registerBoolSetting("Hive Bypass", &bypass, bypass);
	registerBoolSetting("NoSwing", &noSwing, noSwing);
	registerIntSetting("Range", &range, range, 1, 10);
	registerBoolSetting("Beds", &beds, beds);
	registerBoolSetting("Eggs", &eggs, eggs);
	registerBoolSetting("Cakes", &cakes, cakes);
	registerBoolSetting("Treasures", &treasures, treasures);
	registerBoolSetting("Chests", &chests, chests);
	registerBoolSetting("Redstone", &redstone, redstone);
	registerBoolSetting("Diamonds", &diamond, diamond);
	registerBoolSetting("Emeralds", &emerald, emerald);
}

Fucker::~Fucker() {
}

const char* Fucker::getModuleName() {
	return ("Breaker");
}

void Fucker::onTick(C_GameMode* gm) {
	if (g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getClientInstance()->getLocalPlayer()->isAlive()) {
		vec3* pos = gm->player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - range; y < pos->y + range; y++) {
					blockPos = vec3i(x, y, z);
					destroy = false;
					bool eat = false;
					std::string name = gm->player->region->getBlock(blockPos)->toLegacy()->name.getText();

					static AbsorptionAttribute attribute = AbsorptionAttribute();

					if (name == "bed" && beds)
						destroy = true;  // Beds
					if (name == "dragon_egg" && eggs)
						destroy = true;  // Dragon Eggs
					if (name == "cake" && cakes)
						eat = true;  // Cakes
					if (name == "chest" && chests)
						destroy = true;  // Chests
					if (name == "lit_redstone_ore" && redstone && gm->player->getAttribute(&attribute)->currentValue < 10)
						destroy = true;  // Lit Redstone
					if (name == "redstone_ore" && redstone && gm->player->getAttribute(&attribute)->currentValue < 10)
						destroy = true;  // Redstone
					if (name == "diamond_ore" && diamond)
						destroy = true;  // Diamond
					if (name == "emerald_ore" && emerald)
						destroy = true;  // Emerald

					if (destroy) {
						if (!bypass)
							gm->destroyBlock(&blockPos, 0);
						else {
							bool isDestroyed = false;
							gm->startDestroyBlock(blockPos, 0, isDestroyed);
							gm->stopDestroyBlock(blockPos);
							gm->destroyBlock(&blockPos, 0);
							return;
						}
					}
					if (eat) {
						gm->buildBlock(&blockPos, 0);
						if (!noSwing)
							g_Data.getLocalPlayer()->swingArm();
						return;
					}
				}
			}
		}
	}
}

void Fucker::onPlayerTick(C_Player* plr) {
	if (g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getClientInstance()->getLocalPlayer()->isAlive()) {
		if (destroy && rots) {
			vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(vec3(blockPos.x, blockPos.y, blockPos.z));
			plr->bodyYaw = angle.y;
			plr->yawUnused1 = angle.y;
			plr->pitch = angle.x;
		}
	}
}

void Fucker::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>() && g_Data.getLocalPlayer() != nullptr && bypass) {
		static auto instaBreakModule = moduleMgr->getModule<InstaBreak>();
		if (destroy && g_Data.isInGame() && packet != nullptr) {
			instaBreakModule->mode.selected = 1;
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(vec3(blockPos.x, blockPos.y, blockPos.z));
			movePacket->pitch = angle.x;
			movePacket->yaw = angle.y;
			movePacket->headYaw = angle.y;
		}
	}
}

void Fucker::onLevelRender() {
	if (treasures) {
		if (g_Data.isInGame() && g_Data.canUseMoveKeys() && g_Data.getClientInstance()->getLocalPlayer()->isAlive()) {
			g_Data.forEachEntity([](C_Entity* ent, bool b) {
				std::string targetName = ent->getNameTag()->getText();
				std::string localName = g_Data.getLocalPlayer()->getNameTag()->getText();
				auto TeamsMod = moduleMgr->getModule<Teams>();
				if (targetName.find("Treasure") != std::string::npos && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= 5 && targetName.length() > 2 && localName.length() > 2 && targetName.at(2) != localName.at(2)) {
					g_Data.getCGameMode()->attack(ent);
					auto breakMod = moduleMgr->getModule<Fucker>();
					if (!breakMod->noSwing)
						g_Data.getLocalPlayer()->swingArm();
				}
			});
		}
	}
}