#include "Jesus.h"
#include "../../../Utils/Logger.h"

int jesusChrist = 0;

Jesus::Jesus() : IModule(0, Category::MOVEMENT, "Walk over water, like Jesus") {
	this->registerBoolSetting("Old Jesus", &this->walk, this->walk);
}

Jesus::~Jesus() {
}

const char* Jesus::getModuleName() {
	return "Jesus";
}

void Jesus::onTick(C_GameMode* gm) {
	if (gm->player->isSneaking()) return;

	if (gm->player->hasEnteredWater()) {
		gm->player->velocity.y = 0.06f;
		gm->player->onGround = true;
		wasInWater = true;
	} else if (gm->player->isInWater() || gm->player->isInLava()) {
		gm->player->velocity.y = 0.1f;
		gm->player->onGround = true;
		wasInWater = true;
	} else {
		if (wasInWater) {
			wasInWater = false;
			gm->player->velocity.x *= 1.2f;
			gm->player->velocity.x *= 1.2f;
		}
	}
	if (walk) return;
	{
		if (gm->player->isSneaking()) return;
		if (gm->player->isOnFire()) return;

		vec3_t pos = *gm->player->getPos();
		pos.y -= 1.62f;

		pos.z = gm->player->aabb.upper.z;
		pos.x = gm->player->aabb.upper.x;  // upper upper

		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		C_BlockLegacy* blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && gm->player->velocity.y <= 0) {
			vec3_t pos = *gm->player->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			gm->player->setPos(pos);
			gm->player->onGround = true;
			gm->player->velocity.y = 0.f;
		}

		pos.x = gm->player->aabb.lower.x;
		pos.z = gm->player->aabb.lower.z;  // lower lower

		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && gm->player->velocity.y <= 0) {
			vec3_t pos = *gm->player->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			gm->player->setPos(pos);
			gm->player->onGround = true;
			gm->player->velocity.y = 0.f;
		}

		pos.x = gm->player->aabb.upper.x;  // upper x and lower z
		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && gm->player->velocity.y <= 0) {
			vec3_t pos = *gm->player->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			gm->player->setPos(pos);
			gm->player->velocity.y = 0.f;
		}

		pos.x = gm->player->aabb.lower.x;
		pos.z = gm->player->aabb.upper.z;  // lower x and upper z

		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && gm->player->velocity.y <= 0) {
			vec3_t pos = *gm->player->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			gm->player->setPos(pos);
			gm->player->onGround = true;
			gm->player->velocity.y = 0.f;
		}

		if (gm->player->isInWater() || gm->player->isInLava()) {
			gm->player->velocity.y = 0.1f;
			gm->player->onGround = true;
		}
	}
}