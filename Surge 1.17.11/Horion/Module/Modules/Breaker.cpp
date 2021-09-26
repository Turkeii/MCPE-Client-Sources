#include "Breaker.h"

Breaker::Breaker() : IModule(VK_NUMPAD9, Category::WORLD, "Destroys specific things around you") {
	registerIntSetting("Range", &this->range, this->range, 1, 10);
	registerBoolSetting("Beds", &this->beds, this->beds);
	registerBoolSetting("Eggs", &this->eggs, this->eggs);
	registerBoolSetting("Cakes", &this->cakes, this->cakes);
	registerBoolSetting("Treasures", &this->treasures, this->treasures);
	registerBoolSetting("Chests", &this->chests, this->chests);
	registerBoolSetting("Redstone", &this->redstone, this->redstone);
	registerBoolSetting("Diamonds", &this->diamond, this->diamond);
	registerBoolSetting("Emeralds", &this->emerald, this->emerald);
	//registerBoolSetting("HiveNuker", &this->Andisite, this->Andisite);
}

Breaker::~Breaker() {
}

const char* Breaker::getModuleName() {
	return ("Breaker");
}

void Breaker::onTick(C_GameMode* gm) {
	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z);
				bool destroy = false;
				bool eat = false;
				int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (id == 26 && this->beds) destroy = true;      // Beds
				if (id == 122 && this->eggs) destroy = true;     // Dragon Eggs
				if (id == 92 && this->cakes) eat = true;         // Cakes
				if (id == 54 && this->chests) destroy = true;    // Chests
				if (id == 73 && this->redstone) destroy = true;
				if (id == 74 && this->redstone) destroy = true;  // Redstone
				if (id == 56 && this->diamond) destroy = true;   // Diamond
				if (id == 129 && this->emerald) destroy = true;  // Emerald
																 /*	
				if (id == 1 && this->andisite) destroy = true;  // Andisite
				if (id == 56 && this->andisite) destroy = true;  // Andisite
				if (id == 73 && this->andisite) destroy = true;  // Andisite
				if (id == 3 && this->andisite) destroy = true;  // Andisite
				if (id == 2 && this->andisite) destroy = true;  // Andisite
				if (id == 82 && this->andisite) destroy = true;  // Andisite
				if (id == 44 && this->andisite) destroy = true;  // Andisite
				if (id == 107 && this->andisite) destroy = true;   // Andisite
				if (id == 15 && this->andisite) destroy = true;   // Andisite
				if (id == 21 && this->andisite) destroy = true;  // Andisite
				if (id == 14 && this->andisite) destroy = true;   // Andisite
				if (id == 129 && this->andisite) destroy = true;  // Andisite
				if (id == 35 && this->andisite) destroy = true;   // Andisite
				if (id == 159 && this->andisite) destroy = true;   // Andisite
				if (id == 252 && this->andisite) destroy = true;   // Andisite
				if (id == 5 && this->andisite) destroy = true;    // Andisite
				if (id == 17 && this->andisite) destroy = true;     // Andisite
				if (id == 139 && this->andisite) destroy = true;    // Andisite
				if (id == 188 && this->andisite) destroy = true;     // Andisite
				if (id == 251 && this->andisite) destroy = true;    // Andisite
				if (id == 12 && this->andisite) destroy = true;     // Andisite
				if (id == 44 && this->andisite) destroy = true;    // Andisite
				if (id == 24 && this->andisite) destroy = true;     // Andisite
				if (id == 164 && this->andisite) destroy = true;    // Andisite
				if (id == 160 && this->andisite) destroy = true;     // Andisite
				if (id == 4 && this->andisite) destroy = true;      // Andisite
				if (id == 155 && this->andisite) destroy = true;       // Andisite
				if (id == 156 && this->andisite) destroy = true;      // Andisite
				if (id == 189 && this->andisite) destroy = true;         // Andisite
				if (id == 18 && this->andisite) destroy = true;        // Andisite
				if (id == 168 && this->andisite) destroy = true;           // Andisite
				if (id == 216 && this->andisite) destroy = true;         // Andisite
				if (id == 172 && this->andisite) destroy = true;             // Andisite
				if (id == 162 && this->andisite) destroy = true;         // Andisite
				if (id == 126 && this->andisite) destroy = true;             // Andisite
				*/
				//ORIGIONAL IDEA FROM PACKET

				if (destroy) {
					gm->destroyBlock(&blockPos, 0);
					g_Data.getLocalPlayer()->swingArm();
					return;
				}
				if (eat) {
					gm->buildBlock(&blockPos, 0);
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
				g_Data.getLocalPlayer()->swingArm();
			}
		});
	}
}
