#include "Nuker.h"

Nuker::Nuker() : IModule(VK_NUMPAD5, Category::WORLD, "Break multiple blocks at once") {
	registerIntSetting("Radius", &nukerRadius, nukerRadius, 1, 10);
	registerBoolSetting("Veinminer", &veinMiner, veinMiner);
	registerBoolSetting("Auto Destroy", &autodestroy, autodestroy);
	registerBoolSetting("Auto Tool", &autotool, autotool);
}

Nuker::~Nuker() {
}

const char* Nuker::getModuleName() {
	return ("Nuker");
}

void Nuker::onLevelRender() {
	if (!autodestroy) return;
	vec3_ti tempPos = *g_Data.getCGameMode()->player->getPos();
	for (int x = -nukerRadius; x < nukerRadius; x++) {
		for (int y = -nukerRadius; y < nukerRadius; y++) {
			for (int z = -nukerRadius; z < nukerRadius; z++) {
				tempPos.x = (int)g_Data.getCGameMode()->player->getPos()->x + x;
				tempPos.y = (int)g_Data.getCGameMode()->player->getPos()->y + y;
				tempPos.z = (int)g_Data.getCGameMode()->player->getPos()->z + z;
				if (tempPos.y > -64 && g_Data.getCGameMode()->player->region->getBlock(tempPos)->toLegacy()->material->isSolid) {
					if (autotool) {
						findTool();
					}
					g_Data.getCGameMode()->destroyBlock(&tempPos, 1);
				}
			}
		}
	}
}
void Nuker::findTool() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;

	int slot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);

		if (stack->item != nullptr) {
			if ((*stack->item)->isPickaxe()) {
				slot = n;
			}
		}
	}
	supplies->selectedHotbarSlot = slot;
}