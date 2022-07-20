#include "Fucker.h"

Fucker::Fucker() : IModule(VK_NUMPAD9, Category::WORLD, "Destroys beds around you") {
	registerIntSetting("Range", &this->range, this->range, 1, 10);
	registerIntSetting("Hotbar", &this->hotbar, this->hotbar, 0, 9);
	registerBoolSetting("Health", &this->health, this->health);
	registerBoolSetting("Switch", &this->swith23, this->swith23);
	registerBoolSetting("Beds", &this->beds, this->beds);
	registerBoolSetting("Eggs", &this->eggs, this->eggs);
	registerBoolSetting("Cakes", &this->cakes, this->cakes);
	registerBoolSetting("Treasures", &this->treasures, this->treasures);
	registerBoolSetting("Chests", &this->chests, this->chests);
	registerBoolSetting("Barrels", &this->barrels, this->barrels);
	registerBoolSetting("Redstone", &this->redstone, this->redstone);
	registerBoolSetting("Emerald", &this->emerald, this->emerald);
	registerBoolSetting("Diamond", &this->diamond, this->diamond);
}

Fucker::~Fucker() {
}

const char* Fucker::getModuleName() {
	return ("Fucker");
}

void Fucker::onTick(C_GameMode* gm) {
	vec3_t* pos = gm->player->getPos();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	if (g_Data.isInGame()) {
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - range; y < pos->y + range; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
					bool destroy = false;
					bool eat = false;
					int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

					if (id == 26 && this->beds) destroy = true;                                         // Beds
					if (id == 122 && this->eggs) destroy = true;                                        // Dragon Eggs
					if (id == 92 && this->cakes) eat = true;                                            // Cakes
					if (id == 54 && this->chests) destroy = true;                                       // Chests
					if (id == 458 && this->barrels) destroy = true;                                     // Barrels
					if (id == 73 && this->redstone && !this->health && !this->swith23) destroy = true;  // Redstone
					if (id == 129 && this->emerald && !this->health && !this->swith23) destroy = true;  // Emerald
					if (id == 56 && this->diamond && !this->health && !this->swith23) destroy = true;   // Diamond

					if (id == 73 && this->redstone && this->health && gm->player->getHealth() < gm->player->getMaxHealth()) destroy = true;
					if (id == 73 && this->redstone && this->health && this->swith23 && gm->player->getHealth() < gm->player->getMaxHealth()) destroy = true, supplies->selectedHotbarSlot = hotbar;

					if (id == 56 && this->diamond && this->health && gm->player->getHealth() < gm->player->getMaxHealth()) destroy = true;
					if (id == 56 && this->diamond && this->health && this->swith23 && gm->player->getHealth() < gm->player->getMaxHealth()) destroy = true, supplies->selectedHotbarSlot = hotbar;

					if (id == 129 && this->emerald && this->health && gm->player->getHealth() < gm->player->getMaxHealth()) destroy = true;
					if (id == 129 && this->emerald && this->health && this->swith23 && gm->player->getHealth() < gm->player->getMaxHealth()) destroy = true, supplies->selectedHotbarSlot = hotbar;

					if (destroy) {
						gm->destroyBlock(&blockPos, 0);
						if (!moduleMgr->getModule<NoSwing>()->isEnabled())
							g_Data.getLocalPlayer()->swingArm();
						return;
					} else if (this->swith23)
						supplies->selectedHotbarSlot = 0;

					if (eat) {
						gm->buildBlock(&blockPos, 0);
						if (!moduleMgr->getModule<NoSwing>()->isEnabled())
							g_Data.getLocalPlayer()->swingArm();
						return;
					}
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