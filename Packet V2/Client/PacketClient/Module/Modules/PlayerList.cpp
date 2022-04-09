#include "PlayerList.h"

PlayerList::PlayerList() : IModule(VK_TAB, Category::CONFIG, "PlayerList") {
}

const char* PlayerList::getModuleName() {
	return "PlayerList";
}

PlayerList::~PlayerList() {
}

static std::vector<C_Entity*> playerList;

void findPlayers(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() != 319)
		return;

	playerList.push_back(currentEntity);
}

bool PlayerList::isFlashMode() {
	return true;
}

void PlayerList::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	playerList.clear();
	g_Data.forEachEntity(findPlayers);
}

void PlayerList::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}