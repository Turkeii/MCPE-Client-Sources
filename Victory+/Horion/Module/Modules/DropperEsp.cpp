#include "DropperEsp.h"

DropperEsp::DropperEsp() : IModule(0x0, Category::VISUAL, "Draws a box around specific storages") {
	this->registerBoolSetting("Chest", &this->chest, this->chest);
	this->registerBoolSetting("TrapChest", &this->tchest, this->tchest);
	this->registerBoolSetting("EnderChest", &this->echest, this->echest);
	this->registerBoolSetting("Dispenser", &this->dispenser, this->dispenser);
	this->registerBoolSetting("Dropper", &this->dropper, this->dropper);
	this->registerBoolSetting("Furnace", &this->kamado, this->kamado);
	this->registerBoolSetting("Hopper", &this->hopper, this->hopper);
	this->registerBoolSetting("ShulkerBox", &this->shulker, this->shulker);
	this->registerBoolSetting("Barrel", &this->barrel, this->barrel);
	this->registerIntSetting("Range", &this->range, this->range, 5, 85);
}

DropperEsp::~DropperEsp() {
}

const char* DropperEsp::getModuleName() {
	return ("StorageESP");
}

void DropperEsp::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
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
								bool render9 = false;
								bool render10 = false;

								if (dropper) {
									if (blockId == 125) render0 = true;
								}
								if (chest) {
									if (blockId == 54) render1 = true;
								}
								if (tchest) {
									if (blockId == 146) render2 = true;
								}
								if (dispenser) {
									if (blockId == 23) render3 = true;
								}
								if (kamado) {
									if (blockId == 61 || blockId == 62 || blockId == 451 || blockId == 453 || blockId == 454 || blockId == 469) render4 = true;
								}
								if (hopper) {
									if (blockId == 154) render5 = true;
								}
								if (shulker) {
									if (blockId == 205 || blockId == 218) render6 = true;
								}
								if (barrel) {
									if (blockId == 458) render7 = true;
								}
								if (echest) {
									if (blockId == 130) render8 = true;
								}
								//Dropper
								if (render0) {
									DrawUtils::setColor(0.5f, 0.5f, 0.5f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)1.f, outline);
								}
								//chest
								if (render1) {
									DrawUtils::setColor(0.f, 1.f, 0.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//trap
								if (render2) {
									DrawUtils::setColor(1.f, 0.f, 0.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//dispenser
								if (render3) {
									DrawUtils::setColor(0.f, 0.5f, 0.5f, 1.f);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//kamado
								if (render4) {
									DrawUtils::setColor(0.1f, 0.f, 0.8f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//hopper
								if (render5) {
									DrawUtils::setColor(0.f, 0.f, 0.f, 1.f);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//shulker
								if (render6) {
									DrawUtils::setColor(1.f, 1.f, 0.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//barrel
								if (render7) {
									DrawUtils::setColor(0.5f, 0.2f, 0.f, 1.f);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//echest
								if (render8) {
									DrawUtils::setColor(1.f, 1.f, 1.f, 1);
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
