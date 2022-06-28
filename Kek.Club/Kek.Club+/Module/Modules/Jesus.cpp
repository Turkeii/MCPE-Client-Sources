#include "Jesus.h"
#include "../../../Utils/Logger.h"
int jesusChrist = 0;
Jesus::Jesus() : IModule(0, Category::MOVEMENT, "its jebus, say hello jebus SHGDFYGSDKJHFGSDHJ.") {
	registerBoolSetting("test", &jesus1, jesus1);
}

Jesus::~Jesus() {
}

const char* Jesus::getModuleName() {
	return "Jesus";
}
const char* Jesus::getModName() {
		return " [Solid]";
	}
void Jesus::onLevelRender() {
		if (g_Data.getCGameMode() == nullptr)
			return;
	if (g_Data.getCGameMode()->player->isSneaking()) return;
	if (g_Data.getCGameMode()->player->isOnFire()) return;

	vec3_t pos = *g_Data.getCGameMode()->player->getPos();
	pos.y -= 1.62f;

	pos.z = g_Data.getCGameMode()->player->aabb.upper.z;
	pos.x = g_Data.getCGameMode()->player->aabb.upper.x;  // upper upper

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);

	if (blockLegacy->material->isLiquid && g_Data.getCGameMode()->player->velocity.y <= 0) {
		vec3_t pos = *g_Data.getCGameMode()->player->getPos();
		pos.y -= 0.62f;
		pos.y = ceilf(pos.y);
		pos.y += 0.61f;
		g_Data.getCGameMode()->player->setPos(pos);
		g_Data.getCGameMode()->player->onGround = true;
		g_Data.getCGameMode()->player->velocity.y = 0.f;
	}

	pos.x = g_Data.getCGameMode()->player->aabb.lower.x;
	pos.z = g_Data.getCGameMode()->player->aabb.lower.z;  // lower lower

	block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
	blockLegacy = (block->blockLegacy);

	if (blockLegacy->material->isLiquid && g_Data.getCGameMode()->player->velocity.y <= 0) {
		vec3_t pos = *g_Data.getCGameMode()->player->getPos();
		pos.y -= 0.62f;
		pos.y = ceilf(pos.y);
		pos.y += 0.61f;
		g_Data.getCGameMode()->player->setPos(pos);
		g_Data.getCGameMode()->player->onGround = true;
		g_Data.getCGameMode()->player->velocity.y = 0.f;
	}

	pos.x = g_Data.getCGameMode()->player->aabb.upper.x;  // upper x and lower z

	block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
	blockLegacy = (block->blockLegacy);

	if (blockLegacy->material->isLiquid && g_Data.getCGameMode()->player->velocity.y <= 0) {
		vec3_t pos = *g_Data.getCGameMode()->player->getPos();
		pos.y -= 0.62f;
		pos.y = ceilf(pos.y);
		pos.y += 0.61f;
		g_Data.getCGameMode()->player->setPos(pos);
		g_Data.getCGameMode()->player->onGround = true;
		g_Data.getCGameMode()->player->velocity.y = 0.f;
	}

	pos.x = g_Data.getCGameMode()->player->aabb.lower.x;
	pos.z = g_Data.getCGameMode()->player->aabb.upper.z;  // lower x and upper z

	block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
	blockLegacy = (block->blockLegacy);

	if (blockLegacy->material->isLiquid && g_Data.getCGameMode()->player->velocity.y <= 0) {
		vec3_t pos = *g_Data.getCGameMode()->player->getPos();
		pos.y -= 0.62f;
		pos.y = ceilf(pos.y);
		pos.y += 0.61f;
		g_Data.getCGameMode()->player->setPos(pos);
		g_Data.getCGameMode()->player->onGround = true;
		g_Data.getCGameMode()->player->velocity.y = 0.f;
	}

	if (g_Data.getCGameMode()->player->isInWater() || g_Data.getCGameMode()->player->isInLava()) {
		g_Data.getCGameMode()->player->velocity.y = 0.1f;
		g_Data.getCGameMode()->player->onGround = true;
	}
}