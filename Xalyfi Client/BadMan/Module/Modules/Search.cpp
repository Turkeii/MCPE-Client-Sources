#include "Search.h"

Search::Search() : IModule('H', Category::VISUAL, "Find what you need") {
	this->registerIntSetting("radius", &this->range, this->range, 15, 100);
	registerBoolSetting("Outline shape", &this->outline, this->outline);
	this->registerFloatSetting("Thick Mode", &this->thick, this->thick, 0.1f, 0.8f);
	registerBoolSetting("Chest", &this->chest, this->chest);
	registerBoolSetting("TrapChest", &this->trapped_chest, this->trapped_chest);
	registerBoolSetting("EnderChest", &this->ender_chest, this->ender_chest);
	registerBoolSetting("ShulkerBox", &this->shulker_box, this->shulker_box);
	registerBoolSetting("Dropper", &this->dropper, this->dropper);
	registerBoolSetting("Dispenser", &this->dispenser, this->dispenser);
	registerBoolSetting("Hopper", &this->hopper, this->hopper);
	registerBoolSetting("Barrel", &this->barrel, this->barrel);     //taru
	registerBoolSetting("Furnace", &this->furnace, this->furnace); //Kamado
}

Search::~Search() {
}

const char* Search::getModuleName() {
	return ("Search");
}

void Search::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			Odelay++;
			if (Odelay > delay * 20) {
				vec3_t* pos = g_Data.getLocalPlayer()->getPos();
				for (int x = (int)pos->x - range; x < pos->x + range; x++) {
					for (int z = (int)pos->z - range; z < pos->z + range; z++) {
						for (int y = (int)pos->y - range; y < pos->y + range; y++) {
							vec3_t blockPos = vec3_t(x, y, z);

							C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
							if (block != nullptr) {
								int blockId = block->toLegacy()->blockId;
								bool render0 = false;
								bool render1 = false;
								bool render2 = false;
								bool render3 = false;
								bool render4 = false;
								bool render5 = false;
								bool render6 = false;
								bool render7 = false;
								bool render8 = false;

								if (chest) {
									if (blockId == 54) render0 = true;
								}
								if (trapped_chest) {
									if (blockId == 146) render1 = true;
								}
								if (ender_chest) {
									if (blockId == 130) render2 = true;
								}
								if (shulker_box) {
									if (blockId == 205 || blockId == 218) render3 = true;
								}
								if (barrel) {
									if (blockId == 458) render4 = true;
								}
								if (dropper) {
									if (blockId == 125) render5 = true;
								}
								if (dispenser) {
									if (blockId == 23) render6 = true;
								}
								if (hopper) {
									if (blockId == 154) render7 = true;
								}
								if (furnace) {
									if (blockId == 61 || blockId == 451 || blockId == 453) render8 = true;
								}
								//chest
								if (render0) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//trapped_chest
								if (render1) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//ender_chest
								if (render2) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//shulker_box
								if (render3) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//barrel
								if (render4) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//dropper
								if (render5) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//dispenser
								if (render6) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//hopper
								if (render7) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//furnace
								if (render8) {
									DrawUtils::setColor(1.f, 0.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
							}
						}
					}
					Odelay = 0;
				}
			}
		}
	}
}