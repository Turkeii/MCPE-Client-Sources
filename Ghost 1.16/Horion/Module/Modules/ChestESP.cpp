#include "ChestESP.h"

#include "../../DrawUtils.h"
#include "../ModuleManager.h"

ChestESP::ChestESP() : IModule('H', Category::VISUAL, "ESP for chests") {
}

ChestESP::~ChestESP() {
}

const char* ChestESP::getModuleName() {
	return ("ChestESP");
}

void ChestESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	static auto chestEspMod = moduleMgr->getModule<ChestESP>();
	if (!g_Data.isInGame() || !GameData::canUseMoveKeys() || g_Data.getLocalPlayer() == nullptr)
		return;

	auto ourListLock = std::scoped_lock(this->listLock);

	for (auto iter = bufferedChestList.begin(); iter != bufferedChestList.end(); ++iter) {
		auto storageID = g_Data.getLocalPlayer()->region->getBlock((*iter)->upper)->blockLegacy->blockId;
		float sexyMathHack = (float)fmax(0.3f, (float)fmin(1.f, 15));
		DrawUtils::setColor(1.f, 1.f, 1.f, sexyMathHack);

		vec3_t blockPos = (*iter)->lower;
		if (blockPos.x < 0)
			blockPos.x -= 1;
		if (blockPos.z < 0)
			blockPos.z -= 1;
		storageID = g_Data.getLocalPlayer()->region->getBlock(blockPos)->toLegacy()->blockId;

		auto mathVect = vec3_t((*iter)->upper.floor().add(vec3_t(1.f, 1.f, 1.f)).sub((*iter)->upper));
		mathVect.y = floor(mathVect.y);

		if (storageID == 54) DrawUtils::setColor(191.f / 255.f, 114.f / 255.f, 59.f / 255.f, sexyMathHack);
		if (storageID == 146) DrawUtils::setColor(1.f, 0.f, 0.f, sexyMathHack);

		if (storageID == 205 || storageID == 218) DrawUtils::setColor(55.f / 255.f, 155.f / 255.f, 161.f / 255.f, sexyMathHack);

		if (storageID == 130) DrawUtils::setColor(111.f / 255.f, 55.f / 255.f, 161.f / 255.f, sexyMathHack);

		DrawUtils::drawBox((*iter)->upper.floor().add(mathVect), (*iter)->upper, (float)fmax(0.2f, 1 / (float)fmax(1, g_Data.getLocalPlayer()->eyePos0.dist((*iter)->lower))), true);  // Fancy math to give an illusion of good esp
	}
}

void ChestESP::onTick(C_GameMode* gm) {
	auto listLock = g_Data.lockChestList();
	auto* chestList = g_Data.getChestList();
	auto ourListLock = std::scoped_lock(this->listLock);

	this->bufferedChestList.clear();
	this->bufferedChestList.insert(this->bufferedChestList.end(), chestList->begin(), chestList->end());
	chestList->clear();
}