#include "Breaker.h"

Breaker::Breaker() : IModule(0, Category::MISC, "fuck hive") {
	registerBoolSetting("Rotations", &rotations, rotations);
	registerBoolSetting("Treasures", &treasures, treasures);
	registerBoolSetting("Redstone", &rOre, rOre);
	/*registerBoolSetting("Emerald", &eOre, eOre);
	registerBoolSetting("Diamond", &dOre, dOre);
	registerBoolSetting("Gold", &gold, gold);*/
	registerBoolSetting("Chests", &chests, chests);
	registerBoolSetting("Cakes", &cakes, cakes);
	registerBoolSetting("Beds", &beds, beds);
	registerBoolSetting("Eggs", &eggs, eggs);
	registerIntSetting("Range", &range, range, 1, 10);
	//registerIntSetting("Delay", &range, range, 0, 10);
}

Breaker::~Breaker() {
}

const char* Breaker::getRawModuleName() {
	return "Breaker";
}

const char* Breaker::getModuleName() {
	name = std::string("Breaker ") + std::string(GRAY) + std::to_string((int)range);
	return name.c_str();
}

void Breaker::onTick(C_GameMode* gm) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	vec3_t* pos = gm->player->getPos();
	bool eat = false;
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				vec3_ti iBlockPos = vec3_ti(x, y, z);
				blockPos = vec3_t(x, y, z);
				destroy = false;

				int id = (int)gm->player->region->getBlock(iBlockPos)->toLegacy()->blockId;

				if (id == 73 || id == 74 && rOre) destroy = true; // Redstone Ore
				if (id == 129 && eOre) destroy = true;     // Emerald Ore
				if (id == 56 && dOre) destroy = true;     // Diamond Ore
				if (id == 54 && chests) destroy = true;  // Chests
				if (id == 14 && gold) destroy = true;   // Gold
				if (id == 122 && eggs) destroy = true; // Eggs
				if (id == 26 && beds) destroy = true; // Beds
				if (id == 92 && cakes) eat = true;   // Cakes


				if (destroy /* && g_Data.canUseMoveKeys()*/) {
					bool isDestroyed = false;
					if (ezHiveBypass)
						gm->startDestroyBlock(iBlockPos, 1, isDestroyed);
					gm->destroyBlock(&iBlockPos, 0);
					if (!moduleMgr->getModule<NoSwing>()->isEnabled())
						g_Data.getLocalPlayer()->swingArm();
					return;
				}
				if (eat /* && g_Data.canUseMoveKeys()*/) {
					gm->buildBlock(&iBlockPos, 0);
					if (!moduleMgr->getModule<NoSwing>()->isEnabled())
						g_Data.getLocalPlayer()->swingArm();
					return;
				}
			}
		}

		if (treasures) {
			g_Data.forEachEntity([](C_Entity* ent, bool b) {
				std::string name = ent->getNameTag()->getText();
				int id = ent->getEntityTypeId();
				if (name.find("Treasure") != std::string::npos && g_Data.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= 5) {
					g_Data.getCGameMode()->attack(ent);
					if (!moduleMgr->getModule<NoSwing>()->isEnabled())
						g_Data.getLocalPlayer()->swingArm();
				}
			});
		}
	}
}

void Breaker::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (rotations && destroy && g_Data.canUseMoveKeys()) {
		vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(blockPos);
		auto rotation = g_Data.getLocalPlayer();
		float prevyaw = rotation->yawUnused1;
		float prevyaw2 = rotation->yaw;
		float prevyaw3 = rotation->yaw2;
		rotation->setRot(angle);

		// Head
		rotation->yawUnused1 = angle.y;
		rotation->pitch = angle.x;
		rotation->yaw2 = angle.y;
		rotation->yaw = prevyaw2;
		rotation->pitch2 = angle.x;

		// Body
		rotation->bodyYaw = angle.y;
		rotation->yawUnused2 = prevyaw2;
	}
}

void Breaker::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && rotations && destroy) {
		auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(blockPos);
		movePacket->pitch = angle.x;
		movePacket->headYaw = angle.y;
		movePacket->yaw = angle.y;
	}
}

void Breaker::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}