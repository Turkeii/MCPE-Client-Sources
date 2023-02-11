#include "ChestESP.h"
#include "../pch.h"

using namespace std;
ChestESP::ChestESP() : IModule(0, Category::VISUAL, "Outlines Chests") {
}

const char* ChestESP::getModuleName() {
	return ("ChestESP");
}

void ChestESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (g_Data.canUseMoveKeys()) {
		auto ourListLock = scoped_lock(this->listLock);

		for (auto iter = bufferedChestList.begin(); iter != bufferedChestList.end(); ++iter) {
			auto storageID = g_Data.getLocalPlayer()->region->getBlock((*iter)->upper)->blockLegacy->blockId;
			float storage = (float)fmax(0.3f, (float)fmin(1.f, 15));
			DrawUtils::setColor(1.f, 1.f, 1.f, storage);

			vec3_t blockPos = (*iter)->lower;
			if (blockPos.x < 0)
				blockPos.x -= 1;
			if (blockPos.z < 0)
				blockPos.z -= 1;
			storageID = g_Data.getLocalPlayer()->region->getBlock(blockPos)->toLegacy()->blockId;

			auto mathVect = vec3_t((*iter)->upper.floor().add(vec3_t(1.f, 1.f, 1.f)).sub((*iter)->upper));
			mathVect.y = floor(mathVect.y);

			if (storageID == 54) DrawUtils::setColor(1.f, 1.f, 1.f, storage);       // Normal Chest
			if (storageID == 146) DrawUtils::setColor(1.f, 1.f, 1.f, storage);      // Trapped Chest
			if (storageID == 130) DrawUtils::setColor(0.56f, 0.f, 0.56f, storage);  // Ender Chest

			DrawUtils::drawBox((*iter)->lower, (*iter)->upper, (float)fmax(0.2f, 1 / (float)fmax(1, g_Data.getLocalPlayer()->eyePos0.dist((*iter)->lower))), true);  // Fancy math to give an illusion of good esp
		}
	}
}

void ChestESP::onTick(C_GameMode* gm) {
	auto listLock = g_Data.lockChestList();
	auto* chestList = g_Data.getChestList();
	auto ourListLock = scoped_lock(this->listLock);

	this->bufferedChestList.clear();
	this->bufferedChestList.insert(this->bufferedChestList.end(), chestList->begin(), chestList->end());
	chestList->clear();
}

/*void ChestESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!g_Data.isInGame() || !GameData::canUseMoveKeys() || g_Data.getLocalPlayer() == nullptr)
		return;
	//if (listSize < 1000 && listSize > 1) {
	auto ourListLock = scoped_lock(this->listLock);

	for (auto iter = bufferedChestList.begin(); iter != bufferedChestList.end(); ++iter) {
		DrawUtils::setColor(1.f, 0.3f, 0.3f, 0.6f);
		DrawUtils::drawBox((*iter)->lower, (*iter)->upper, (float)fmax(0.2f, 1 / (float)fmax(1, g_Data.getLocalPlayer()->eyePos0.dist((*iter)->lower))), true);  // Fancy math to give an illusion of good esp
	}
}*/