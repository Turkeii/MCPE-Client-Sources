#include "Fucker.h"

Fucker::Fucker() : IModule(0, Category::MISC, "Destroys Beds, Eggs, Treasures Etc. A litte buggy on Mineplex.") {
	registerBoolSetting("Treasures", &this->treasures, this->treasures);
	registerBoolSetting("Redstone", &this->rOre, this->rOre);
	registerBoolSetting("Diamond", &this->dOre, this->dOre);
	registerBoolSetting("Emerald", &this->eOre, this->eOre);
	//registerBoolSetting("Carrots", &this->carrots, this->carrots);
	//registerBoolSetting("Chests", &this->chests, this->chests);
	registerBoolSetting("Cakes", &this->cakes, this->cakes);
	registerBoolSetting("Beds", &this->beds, this->beds);
	registerBoolSetting("Eggs", &this->eggs, this->eggs);
	registerBoolSetting("---------", &this->air, this->air);
	registerBoolSetting("Sandstone", &this->sandstone, this->sandstone);
	registerBoolSetting("grass", &this->grass, this->grass);
	registerBoolSetting("stone", &this->stone, this->stone);
	registerBoolSetting("Iron", &this->iron, this->iron);
	registerBoolSetting("Gold", &this->gold, this->gold);
	registerBoolSetting("Dirt", &this->dirt, this->dirt);
	registerIntSetting("Range", &this->range, this->range, 1, 10);
	//registerBoolSetting("Barrels", &this->barrels, this->barrels);
}

Fucker::~Fucker() {
}

const char* Fucker::getModuleName() {
	return ("Breaker");
}

void Fucker::onTick(C_GameMode* gm) {
	if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "geo.hivebedrock.network") == 0) {  // Only on The Hive
		*g_Data.getClientInstance()->minecraft->timer = 18.f;
	}
	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z);
				bool destroy = false;
				int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (id == 26 && this->beds) destroy = true;      // Beds
				if (id == 122 && this->eggs) destroy = true;     // Dragon Eggs
				if (id == 92 && this->cakes) destroy = true;     // Cakes
				if (id == 73 && this->rOre) destroy = true;      // Redstone Ore
				if (id == 56 && this->dOre) destroy = true;      // Diamond Ore
				if (id == 129 && this->eOre) destroy = true;     // Emerald Ore
				if (id == 1 && this->stone) destroy = true;      // Stone
				if (id == 2 && this->grass) destroy = true;      // Grass
				if (id == 3 && this->dirt) destroy = true;       // Dirt
				if (id == 15 && this->iron) destroy = true;      // Iron
				if (id == 14 && this->gold) destroy = true;      // Gold
				if (id == 24 && this->sandstone) destroy = true; // Sand
				if (id == 54 && this->chests) destroy = true;    // Chests
				if (id == 458 && this->barrels) destroy = true;  // Barrels
				if (id == 141 && this->carrots) destroy = true;  // Carrots

				if (destroy) {
					gm->destroyBlock(&blockPos, 0);
					if (!moduleMgr->getModule<NoSwing>()->isEnabled()) 
						g_Data.getLocalPlayer()->swingArm();
					return;
				}
			}
		}
	}

	if (this->treasures) {
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

void Fucker::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}