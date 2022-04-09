#include "HoleESP.h"

HoleESP::HoleESP() : IModule(0x0, Category::VISUAL, "You can see visible holes.") {
	enum1 = (*new SettingEnum(this)).addEntry(EnumEntry("FullBox", 1)).addEntry(EnumEntry("Outline", 2)).addEntry(EnumEntry("Lines", 3));
	registerEnumSetting("HoleRender", &enum1, 3);
	registerIntSetting("Range", &range, 1, 1.f, 15.f);

	registerBoolSetting("Obsidian Hole", &obsidian, obsidian);
	registerFloatSetting("Red", &rSelect1, rSelect1, 0.f, 1.f);
	registerFloatSetting("Green", &gSelect1, gSelect1, 0.f, 1.f);
	registerFloatSetting("Blue", &bSelect1, bSelect1, 0.f, 1.f);

	registerBoolSetting("Bedrock Hole", &bedrock, bedrock);
	registerFloatSetting("Red", &rSelect, rSelect, 0.f, 1.f);
	registerFloatSetting("Green", &gSelect, gSelect, 0.f, 1.f);
	registerFloatSetting("Blue", &bSelect, bSelect, 0.f, 1.f);

	registerBoolSetting("Mix Hole", &mix, mix);
	registerFloatSetting("Red", &rSelect2, rSelect2, 0.f, 1.f);
	registerFloatSetting("Green", &gSelect2, gSelect2, 0.f, 1.f);
	registerFloatSetting("Blue", &bSelect2, bSelect2, 0.f, 1.f);
}

HoleESP::~HoleESP() {
}

const char* HoleESP::getModuleName() {
	return ("HoleESP");
}
void HoleESP::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			vec3* pos = g_Data.getLocalPlayer()->getPos();
			for (int x = (int)pos->x - range; x < pos->x + range; x++) {
				for (int z = (int)pos->z - range; z < pos->z + range; z++) {
					for (int y = (int)pos->y - range; y < pos->y + range; y++) {
						vec3 blockPos = vec3(x, y, z);
						vec3 blockPos2 = vec3(x + 1, y, z);
						vec3 blockPos3 = vec3(x, y, z + 1);
						vec3 blockPos4 = vec3(x, y - 1, z);
						vec3 blockPos5 = vec3(x - 1, y, z);
						vec3 blockPos6 = vec3(x, y, z - 1);

						C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
						C_Block* block2 = g_Data.getLocalPlayer()->region->getBlock(blockPos2);
						C_Block* block3 = g_Data.getLocalPlayer()->region->getBlock(blockPos3);
						C_Block* block4 = g_Data.getLocalPlayer()->region->getBlock(blockPos4);
						C_Block* block5 = g_Data.getLocalPlayer()->region->getBlock(blockPos5);
						C_Block* block6 = g_Data.getLocalPlayer()->region->getBlock(blockPos6);

						if (block != nullptr && block2 != nullptr && block3 != nullptr && block4 != nullptr) {
							int blockId = block->toLegacy()->blockId;
							int blockId2 = block2->toLegacy()->blockId;
							int blockId3 = block3->toLegacy()->blockId;
							int blockId4 = block4->toLegacy()->blockId;
							int blockId5 = block5->toLegacy()->blockId;
							int blockId6 = block6->toLegacy()->blockId;

							bool obs = false;

							if (blockId == 0) obs = true;

							// Draw Obsidian Hole
							if (obsidian) {
								auto vec1 = vec3(1.f, 0.1f, 1.f);
								if ((blockId2 == 49 && blockId3 == 49 && blockId4 == 49 && blockId5 == 49 && blockId6 == 49 && blockId == 0)) {
									if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
										continue;

									if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
										continue;
									if (enum1.selected == 2) {
										DrawUtils::drawBoxv2(blockPos, vec3(blockPos).add(1), (float)0.4f);
										DrawUtils::setColor(rSelect1, gSelect1, bSelect1, 1);
									}
									if (enum1.selected == 1) {
										DrawUtils::drawBox(blockPos, blockPos.add(vec1), 0.5f, true);
										DrawUtils::setColor(rSelect1, gSelect1, bSelect1, 1);
									}
									if (enum1.selected == 0) {
										DrawUtils::drawBox(blockPos, vec3(blockPos).add(1), (float)0.4f);
										DrawUtils::setColor(rSelect1, gSelect1, bSelect1, 1);
									}
								}
							}

							if (mix) {
								auto vec1 = vec3(1.f, 0.1f, 1.f);
								if ((blockId2 == 49 || blockId2 == 7) && (blockId3 == 49 || blockId3 == 7) && (blockId4 == 49) && (blockId5 == 49 || blockId5 == 7) && (blockId6 == 49 || blockId6 == 7) && (blockId == 0)) {
									if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
										continue;

									if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
										continue;
									if (enum1.selected == 2) {
										DrawUtils::drawBoxv2(blockPos, vec3(blockPos).add(1), (float)0.4f);
										DrawUtils::setColor(rSelect2, gSelect2, bSelect2, 1);
									}
									if (enum1.selected == 1) {
										DrawUtils::drawBox(blockPos, blockPos.add(vec1), 0.5f, true);
										DrawUtils::setColor(rSelect2, gSelect2, bSelect2, 1);
									}
									if (enum1.selected == 0) {
										DrawUtils::drawBox(blockPos, vec3(blockPos).add(1), (float)0.4f);
										DrawUtils::setColor(rSelect2, gSelect2, bSelect2, 1);
									}
								}
							}
							if (mix) {
								auto vec1 = vec3(1.f, 0.1f, 1.f);
								if ((blockId2 == 49 || blockId2 == 7) && (blockId3 == 49 || blockId3 == 7) && (blockId4 == 7) && (blockId5 == 49 || blockId5 == 7) && (blockId6 == 49 || blockId6 == 7) && (blockId == 0)) {
									if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
										continue;

									if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
										continue;
									DrawUtils::setColor(rSelect2, gSelect2, bSelect2, 1);
									if (enum1.selected == 2) {
										DrawUtils::drawBoxv2(blockPos, vec3(blockPos).add(1), (float)0.4f);
										DrawUtils::setColor(rSelect, gSelect, bSelect, 1);
									}
									if (enum1.selected == 1) {
										DrawUtils::drawBox(blockPos, blockPos.add(vec1), 0.5f, true);
										DrawUtils::setColor(rSelect, gSelect, bSelect, 1);
									}
									if (enum1.selected == 0) {
										DrawUtils::drawBox(blockPos, vec3(blockPos).add(1), (float)0.4f);
										DrawUtils::setColor(rSelect, gSelect, bSelect, 1);
									}
								}
							}

							// Draw Bedrock Hole
							if (bedrock) {
								auto vec1 = vec3(1.f, 0.1f, 1.f);
								if ((blockId2 == 7 && blockId3 == 7 && blockId4 == 7 && blockId5 == 7 && blockId6 == 7 && blockId == 0)) {
									if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
										continue;

									if (g_Data.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
										continue;
									if (enum1.selected == 2) {
										DrawUtils::drawBoxv2(blockPos, vec3(blockPos).add(1), (float)0.4f);
										DrawUtils::setColor(rSelect, gSelect, bSelect, 1);
									}
									if (enum1.selected == 1) {
										DrawUtils::drawBox(blockPos, blockPos.add(vec1), 0.5f, true);
										DrawUtils::setColor(rSelect, gSelect, bSelect, 1);
									}
									if (enum1.selected == 0) {
										DrawUtils::drawBox(blockPos, vec3(blockPos).add(1), (float)0.4f);
										DrawUtils::setColor(rSelect, gSelect, bSelect, 1);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}