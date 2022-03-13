#include "HoleEsp.h" 

HoleEsp::HoleEsp() : IModule(0x0, Category::VISUAL, "Your can visible hole.") {
	this->registerBoolSetting("Box", &this->box, this->box);
	this->registerBoolSetting("Obsidian Hole", &this->obsidian, this->obsidian);
	this->registerBoolSetting("Bedrock Hole", &this->bedrock, this->bedrock);
	//this->registerBoolSetting("Check Hole", &this->Check, this->Check);
	//registerFloatSetting("Opacity", &this->Opacity, 1, 0.f, 1.f);  //Opacity
	//registerFloatSetting("LineSize", &this->LineSize, 1, 0.1f, 2.f);
	registerIntSetting("Range", &this->range, 1, 3.f, 15.f);
}

HoleEsp::~HoleEsp() {
}

const char* HoleEsp::getModName() {
	if (box) {
		return "Box";
	} else {
		return "Slab";
	}
}

const char* HoleEsp::getModuleName() {
	return ("HoleESP");
}

void HoleEsp::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.isInGame()) {
			/*	// Rainbow colors
			static float rcolors[4];

			{
				if (rcolors[3] < 1) {
					rcolors[0] = 0.2f;
					rcolors[1] = 0.2f;
					rcolors[2] = 1.f;
					rcolors[3] = 1;
				}

				Utils::ApplyRainbow(rcolors, 0.015f);
			}
			*/
			//Odelay++;
			//if (Odelay > delay * 20) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();
			for (int x = (int)pos->x - range; x < pos->x + range; x++) {
				for (int z = (int)pos->z - range; z < pos->z + range; z++) {
					for (int y = (int)pos->y - range; y < pos->y + range; y++) {
						vec4_t underline;
						vec3_t blockPos = vec3_t(x, y, z);
						vec3_t air = vec3_t(x, y + 1, z);
						vec3_t air2 = vec3_t(x, y + 2, z);

						vec3_t blockPos2 = vec3_t(x + 1, y, z);
						vec3_t blockPos3 = vec3_t(x, y, z + 1);
						vec3_t blockPos4 = vec3_t(x, y - 1, z);
						vec3_t blockPos5 = vec3_t(x - 1, y, z);
						vec3_t blockPos6 = vec3_t(x, y, z - 1);

						vec3_t blockPos22 = vec3_t(x + 1, y + 1, z);
						vec3_t blockPos32 = vec3_t(x, y + 1, z + 1);
						vec3_t blockPos52 = vec3_t(x - 1, y + 1, z);
						vec3_t blockPos62 = vec3_t(x, y + 1, z - 1);

						C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
						C_Block* airpos = g_Data.getLocalPlayer()->region->getBlock(air);
						C_Block* airpos2 = g_Data.getLocalPlayer()->region->getBlock(air2);
						C_Block* block2 = g_Data.getLocalPlayer()->region->getBlock(blockPos2);
						C_Block* block3 = g_Data.getLocalPlayer()->region->getBlock(blockPos3);
						C_Block* block4 = g_Data.getLocalPlayer()->region->getBlock(blockPos4);
						C_Block* block5 = g_Data.getLocalPlayer()->region->getBlock(blockPos5);
						C_Block* block6 = g_Data.getLocalPlayer()->region->getBlock(blockPos6);

						C_Block* block22 = g_Data.getLocalPlayer()->region->getBlock(blockPos22);
						C_Block* block32 = g_Data.getLocalPlayer()->region->getBlock(blockPos32);
						C_Block* block52 = g_Data.getLocalPlayer()->region->getBlock(blockPos52);
						C_Block* block62 = g_Data.getLocalPlayer()->region->getBlock(blockPos62);

						if (block != nullptr && block2 != nullptr && block3 != nullptr && block4 != nullptr) {
							int blockId = block->toLegacy()->blockId;
							int aircheck = airpos->toLegacy()->blockId;
							int aircheck2 = airpos2->toLegacy()->blockId;
							int blockId2 = block2->toLegacy()->blockId;
							int blockId3 = block3->toLegacy()->blockId;
							int blockId4 = block4->toLegacy()->blockId;
							int blockId5 = block5->toLegacy()->blockId;
							int blockId6 = block6->toLegacy()->blockId;

							int blockId22 = block22->toLegacy()->blockId;
							int blockId32 = block32->toLegacy()->blockId;
							int blockId52 = block52->toLegacy()->blockId;
							int blockId62 = block62->toLegacy()->blockId;

							bool obs = false;

							if (blockId == 0) obs = true;

							//Draw Bedrock Hole
							if (bedrock) {
								if ((blockId2 == 7 && blockId3 == 7 && blockId4 == 7 && blockId5 == 7 && blockId6 == 7 && blockId == 0) && (aircheck == 0)) {
									//if (targetList[0]->getPos()) {
									//	DrawUtils::setColor(0.f, 0.f, 1.f, Opacity);
									//} else {
									DrawUtils::setColor(0.f, 1.f, 0.f, Opacity);
									if (!box) {
										DrawUtils::drawBoxv2(blockPos, vec3_t(blockPos).add(1), (float)LineSize);
										//DrawUtils::drawX(blockPos, vec3_t(blockPos).add(0.2f, 0.f, 0.f), 0.4f);
									} else {
										DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)LineSize);
									}
									//DrawUtils::setColor(0.f, 0.f, 1.f, Opacity);
									//if ((blockId2 == 7 && blockId3 == 7 && blockId4 == 7 && blockId5 == 7 && blockId6 == 7 && blockId == 0) && (aircheck == 0) && (blockId22 == 7 && blockId32 == 7 && blockId52 == 7 && blockId62 == 7 && blockId == 0) && (aircheck2 == 0)) {
									//DrawUtils::drawBox2X(blockPos, vec3_t(blockPos).add(1), (float)LineSize);
									//}
								}
								//Draw Obsidian Hole
								if (obsidian) {
									if ((blockId2 == 49 || blockId2 == 7) && (blockId3 == 49 || blockId3 == 7) && (blockId4 == 49 || blockId4 == 7) && (blockId5 == 49 || blockId5 == 7) && (blockId6 == 49 || blockId6 == 7) && (blockId == 0) && (aircheck == 0) && !((blockId2 == 7 && blockId3 == 7 && blockId4 == 7 && blockId5 == 7 && blockId6 == 7 && blockId == 0) && (aircheck == 0))) {
										//if (targetList[0]->getPos()) {
										//	DrawUtils::setColor(0.f, 0.f, 1.f, Opacity);
										//} else {
										DrawUtils::setColor(1.f, 0.f, 0.f, Opacity);
										if (!box) {
											DrawUtils::drawBoxv2(blockPos, vec3_t(blockPos).add(1), (float)LineSize);
										} else {
											DrawUtils::drawBox(blockPos, vec3_t(blockPos).add(1), (float)LineSize);
										}

										//DrawUtils::setColor(0.f, 0.f, 1.f, Opacity);
										//if ((blockId2 == 49 || blockId2 == 7) && (blockId3 == 49 || blockId3 == 7) && (blockId4 == 49) && (blockId5 == 49 || blockId5 == 7) && (blockId6 == 49 || blockId6 == 7) && (blockId == 0) && (aircheck == 0) && (blockId22 == 49 || blockId22 == 7) && (blockId32 == 49 || blockId32 == 7) && (blockId52 == 49 || blockId52 == 7) && (blockId62 == 49 || blockId62 == 7) && (blockId == 0) && (aircheck2 == 0)) {
										//DrawUtils::drawBox2X(blockPos, vec3_t(blockPos).add(1), (float)LineSize);
									}
								}
								//Odelay = 0;
							}
						}
					}
				}
			}
		}
	}
}