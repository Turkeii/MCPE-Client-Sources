#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class BlockEsp : public IModule {
public:
	int tickTimeout = 0;
	std::vector<std::shared_ptr<AABB>> bufferedChestList;
	std::mutex listLock;

	float thick = 0.4f;
	bool copper = false;
	bool outline = false;
	bool diamond = false;
	bool emerald = false;
	bool gold = false;
	bool redstone = false;
	bool lapis = false;
	bool iron = false;
	bool coal = false;
	bool debris = false;
	bool quartz = false;
	bool invisBlocks = false;
	bool portalBlocks = false;
	bool spawner = false;

	int range = 10;
	int Odelay = 0;
	float delay = 0.14f;

	BlockEsp() : IModule(0x0, Category::VISUAL, "Draws a box around specific blocks") {
		registerIntSetting("radius", &range, range, 3, 20);
		registerBoolSetting("Outline shape", &outline, outline);
		registerFloatSetting("Outline Thickness", &thick, thick, 0.1f, 0.8f);
		registerBoolSetting("Emerald ore", &emerald, emerald);
		registerBoolSetting("Diamond ore", &diamond, diamond);
		registerBoolSetting("Gold ore", &gold, gold);
		registerBoolSetting("Redstone ore", &redstone, redstone);
		registerBoolSetting("Lapis ore", &lapis, lapis);
		registerBoolSetting("Iron ore", &iron, iron);
		registerBoolSetting("Coal ore", &coal, coal);
		registerBoolSetting("Copper ore", &copper, copper);
		registerBoolSetting("Ancient Debris", &debris, debris);
		registerBoolSetting("Nether Quartz", &quartz, quartz);
		registerBoolSetting("Invisible Blocks", &invisBlocks, invisBlocks);
		registerBoolSetting("Portal Blocks", &portalBlocks, portalBlocks);
	};
	~BlockEsp(){};
	void onPreRender(C_MinecraftUIRenderContext* renderCtx) {
		if (!g_Data.isInGame() || !GameData::canUseMoveKeys() || g_Data.getLocalPlayer() == nullptr)
			return;

		for (auto iter = bufferedChestList.begin(); iter != bufferedChestList.end(); ++iter) {
			auto storageID = g_Data.getLocalPlayer()->region->getBlock((*iter)->upper)->blockLegacy->blockId;
			float math = (float)fmax(0.3f, (float)fmin(1.f, 15));
			// DrawUtils::setColor(1.f, 1.f, 1.f, math);

			vec3 blockPos = (*iter)->lower;
			if (blockPos.x < 0)
				blockPos.x -= 1;
			if (blockPos.z < 0)
				blockPos.z -= 1;
			storageID = g_Data.getLocalPlayer()->region->getBlock(blockPos)->toLegacy()->blockId;

			auto mathVect = vec3((*iter)->upper.floor().add(vec3(1.f, 1.f, 1.f)).sub((*iter)->upper));
			mathVect.y = floor(mathVect.y);

			//if (storageID == 54) DrawUtils::setColor(1.f, 1.f, 1.f, math);                        // Normal Chest
			//	if (storageID == 130) DrawUtils::setColor(0.435294f, 0.215686f, 0.631372f, math);    // Ender Chest
			// if (storageID == 205) DrawUtils::setColor(.49f, .17f, .95f, math);                  // Undyed Shulker Box
			//	if (storageID == 218) DrawUtils::setColor(.08f, .91f, .99f, math);                 // Shulker Box

			 //if (storageID == 90 || 119 && portalBlocks) DrawUtils::setColor(.08f, .91f, .99f, math);   // portalBlocks
			// if (storageID == 95 || 416 && invisBlocks) DrawUtils::setColor(.08f, .91f, .99f, math);   // invisBlocks
			// if (storageID == 153 && quartz) DrawUtils::setColor(.08f, .91f, .99f, math);             // quartz
			// if (storageID == 566 && copper) DrawUtils::setColor(.08f, .91f, .99f, math);            // copper ore
			// if (storageID == 15 && iron) DrawUtils::setColor(.08f, .91f, .99f, math);              // iron ore
			// if (storageID == 14 && gold) DrawUtils::setColor(.08f, .91f, .99f, math);             // gold ore
			// if (storageID == 56 && diamond) DrawUtils::setColor(.08f, .91f, .99f, math);         // diamond ore
			// if (storageID == 21 && lapis) DrawUtils::setColor(.08f, .91f, .99f, math);          // lapis ore
			// if (storageID == 73 && redstone) DrawUtils::setColor(.08f, .91f, .99f, math);      // redstone ore
			// if (storageID == 16 && coal) DrawUtils::setColor(.08f, .91f, .99f, math);         // coal ore
			// if (storageID == 566 && copper) DrawUtils::setColor(.08f, .91f, .99f, math);     // copper
			// if (storageID == 129 && emerald) DrawUtils::setColor(.08f, .91f, .99f, math);   // emerald ore
			// if (storageID == 526 && debris) DrawUtils::setColor(.08f, .91f, .99f, math);   // ancient debris
			// if (storageID == 52 && spawner) DrawUtils::setColor(.08f, .91f, .99f, math);  //  mob spawner

			//DrawUtils::drawBox((*iter)->lower, (*iter)->upper, (float)fmax(0.2f, 1 / (float)fmax(1, g_Data.getLocalPlayer()->eyePos0.dist((*iter)->lower))), true);
		}
	}

	virtual const char* getModuleName() override {
		return "BlockEsp";
	}
};