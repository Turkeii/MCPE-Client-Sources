#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class ChestAura : public IModule {
private:
	int range = 3;
	bool enderchests = false;

public:
	C_MoveInputHandler* inputHandler = nullptr;
	ChestAura() : IModule(0x0, Category::PLAYER, "Aura for opening chests") {
		registerIntSetting("Range", &this->range, this->range, 1, 10);
		registerBoolSetting("EnderChests", &this->enderchests, this->enderchests);
	}
	~ChestAura(){};

	std::vector<vec3i> chestlist;

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("ChestAura"); }
	virtual void onTick(C_GameMode* gm) override {
		if (g_Data.getLocalPlayer()->getSupplies()->inventory->isFull())
			return;
		if (!g_Data.getLocalPlayer()->canOpenContainerScreen())
			return;

		vec3* pos = gm->player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - range; y < pos->y + range; y++) {
					vec3i pos = vec3i(x, y, z);
					C_Block* block = gm->player->region->getBlock(pos);
					if (block != nullptr && g_Data.canUseMoveKeys()) {
						auto id = gm->player->region->getBlock(pos)->toLegacy()->blockId;
						bool open = false;
						if (id == 54) open = true;                  // Chests
						if (id == 130 && enderchests) open = true;  // EnderCheats
						if (open)
							if (!(std::find(chestlist.begin(), chestlist.end(), pos) != chestlist.end())) {
								gm->buildBlock(&pos, 0);
								chestlist.push_back(pos);
								return;
							}
					}
				}
			}
		}
	}
	virtual void onDisable() override { this->chestlist.clear(); }  // this code should be changed later, the chestlist has to be cleared when loading into a new world
};