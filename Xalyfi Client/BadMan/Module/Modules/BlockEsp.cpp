#include "BlockEsp.h"

BlockEsp::BlockEsp() : IModule(0x0, Category::VISUAL, "Draws a box around specific blocks") {
	this->registerIntSetting("radius", &this->range, this->range, 5, 35);
	registerBoolSetting("Outline shape", &this->outline, this->outline);
	this->registerFloatSetting("Outline Thickness", &this->thick, this->thick, 0.1f, 0.8f);
	registerBoolSetting("Emerald ore", &this->emerald, this->emerald);
	registerBoolSetting("Diamond ore", &this->diamond, this->diamond);
	registerBoolSetting("All Gold ores", &this->gold, this->gold);
	registerBoolSetting("Redstone ore", &this->redstone, this->redstone);
	registerBoolSetting("Lapis ore", &this->lapis, this->lapis);
	registerBoolSetting("Iron ore", &this->iron, this->iron);
	registerBoolSetting("Coal ore", &this->coal, this->coal);
	registerBoolSetting("Ancient Debris", &this->debris, this->debris);
	registerBoolSetting("Nether Quartz", &this->quartz, this->quartz);
	registerBoolSetting("Invisible Blocks", &this->invisBlocks, this->invisBlocks);
	registerBoolSetting("Portal Blocks", &this->portalBlocks, this->portalBlocks);
}

BlockEsp::~BlockEsp() {
}

const char* BlockEsp::getModuleName() {
	return ("BlockESP");
}

void BlockEsp::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
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

								if (diamond) {
									if (blockId == 56) render0 = true;
								}
								if (emerald) {
									if (blockId == 129) render1 = true;
								}
								if (gold) {
									if (blockId == 14 || blockId == 536 || blockId == 543) render2 = true;
								}
								if (redstone) {
									if (blockId == 73 || blockId == 74) render3 = true;
								}
								if (lapis) {
									if (blockId == 21) render4 = true;
								}
								if (iron) {
									if (blockId == 15) render5 = true;
								}
								if (coal) {
									if (blockId == 16) render6 = true;
								}
								if (debris) {
									if (blockId == 526) render7 = true;
								}
								if (quartz) {
									if (blockId == 153) render8 = true;
								}
								if (invisBlocks) {
									if (blockId == 95 || blockId == 416) render9 = true;
								}
								if (portalBlocks) {
									if (blockId == 90 || blockId == 119) render10 = true;
								}
								//diamond
								if (render0) {
									DrawUtils::setColor(0.f, 1.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//emerald
								if (render1) {
									DrawUtils::setColor(0.1f, 0.9f, 0.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//gold
								if (render2) {
									DrawUtils::setColor(0.9f, 1.f, 0.1f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//redstone
								if (render3) {
									DrawUtils::setColor(1.f, 0.1f, 0, 1.f);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//lapis
								if (render4) {
									DrawUtils::setColor(0.1f, 0.2f, 0.7f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//iron
								if (render5) {
									DrawUtils::setColor(0.7f, 0.5f, 0.4f, 1.f);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//coal
								if (render6) {
									DrawUtils::setColor(0.f, 0.f, 0.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//debris
								if (render7) {
									DrawUtils::setColor(0.5f, 0.2f, 0.f, 1.f);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//quartz
								if (render8) {
									DrawUtils::setColor(1.f, 1.f, 1.f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//invisBlocks
								if (render9) {
									DrawUtils::setColor(0.3f, 0.1f, 0.6f, 1);
									DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)thick / (float)1.f, outline);
								}
								//portals
								if (render10) {
									DrawUtils::setColor(0.9f, 0.4f, 1.f, 1);
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
