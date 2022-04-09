#include "EntityJesus.h"

#include "../../../Utils/Logger.h"

int EntityJesusChrist = 0;

EntityJesus::EntityJesus() : IModule(0x0, Category::ENTITY, "Allows entities to walk on water and lava!") {
	registerFloatSetting("Up-ness", &upness, upness, 0.01f, 1.00f);  //allows you to ajust your speed.
}

EntityJesus::~EntityJesus() {
}

const char* EntityJesus::getModuleName() {
	return "EntityJesus";
}
static std::vector<C_Entity*> targetBo;
void findBo(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90 && currentEntity->getEntityTypeId() != 2186010 && currentEntity->getEntityTypeId() != 2118423 && currentEntity->getEntityTypeId() != 4876 && currentEntity->getEntityTypeId() != 2118424)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetBo.push_back(currentEntity);
	}
}

void EntityJesus::onTick(C_GameMode* gm) {
	targetBo.clear();
	g_Data.forEachEntity(findBo);

	if (!targetBo.empty()) {
		if (targetBo[0]->isSneaking()) return;
		if (targetBo[0]->isOnFire()) return;

		vec3 pos = *targetBo[0]->getPos();
		pos.y -= upness;

		pos.z = targetBo[0]->aabb.upper.z;
		pos.x = targetBo[0]->aabb.upper.x;  // upper upper

		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
		C_BlockLegacy* blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->velocity.y <= 0) {
			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->onGround = true;
			targetBo[0]->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb.lower.x;
		pos.z = targetBo[0]->aabb.lower.z;  // lower lower

		block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->velocity.y <= 0) {
			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->onGround = true;
			targetBo[0]->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb.upper.x;  // upper x and lower z

		block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->velocity.y <= 0) {
			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->onGround = true;
			targetBo[0]->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb.lower.x;
		pos.z = targetBo[0]->aabb.upper.z;  // lower x and upper z

		block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->velocity.y <= 0) {
			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->onGround = true;
			targetBo[0]->velocity.y = 0.f;
		}

		if (targetBo[0]->isInWater() || targetBo[0]->isInLava()) {
			targetBo[0]->velocity.y = 0.1f;
			targetBo[0]->onGround = true;

			if (targetBo[0]->isSneaking()) return;
			if (targetBo[0]->isOnFire()) return;

			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;

			pos.z = targetBo[0]->aabb.upper.z;
			pos.x = targetBo[0]->aabb.upper.x;  // upper upper

			C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
			C_BlockLegacy* blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->velocity.y <= 0) {
				vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->onGround = true;
				targetBo[0]->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb.lower.x;
			pos.z = targetBo[0]->aabb.lower.z;  // lower lower

			block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->velocity.y <= 0) {
				vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += 0.01f;
				targetBo[0]->setPos(pos);
				targetBo[0]->onGround = true;
				targetBo[0]->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb.upper.x;  // upper x and lower z

			block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->velocity.y <= 0) {
				vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->onGround = true;
				targetBo[0]->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb.lower.x;
			pos.z = targetBo[0]->aabb.upper.z;  // lower x and upper z

			block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->velocity.y <= 0) {
				vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->onGround = true;
				targetBo[0]->velocity.y = 0.f;
			}

			if (targetBo[0]->isOnHotBlock() || targetBo[0]->isOnHotBlock()) {
				targetBo[0]->velocity.y = 0.1f;
				targetBo[0]->onGround = true;
			}
		}
	}
}

void EntityJesus::onLevelRender() {
	targetBo.clear();
	g_Data.forEachEntity(findBo);

	if (!targetBo.empty()) {
		if (targetBo[0]->isSneaking()) return;
		if (targetBo[0]->isOnFire()) return;

		vec3 pos = *targetBo[0]->getPos();
		pos.y -= upness;

		pos.z = targetBo[0]->aabb.upper.z;
		pos.x = targetBo[0]->aabb.upper.x;  // upper upper

		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
		C_BlockLegacy* blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->velocity.y <= 0) {
			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->onGround = true;
			targetBo[0]->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb.lower.x;
		pos.z = targetBo[0]->aabb.lower.z;  // lower lower

		block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->velocity.y <= 0) {
			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->onGround = true;
			targetBo[0]->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb.upper.x;  // upper x and lower z

		block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->velocity.y <= 0) {
			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->onGround = true;
			targetBo[0]->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb.lower.x;
		pos.z = targetBo[0]->aabb.upper.z;  // lower x and upper z

		block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->velocity.y <= 0) {
			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->onGround = true;
			targetBo[0]->velocity.y = 0.f;
		}

		if (targetBo[0]->isInWater() || targetBo[0]->isInLava()) {
			targetBo[0]->velocity.y = 0.1f;
			targetBo[0]->onGround = true;

			if (targetBo[0]->isSneaking()) return;
			if (targetBo[0]->isOnFire()) return;

			vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;

			pos.z = targetBo[0]->aabb.upper.z;
			pos.x = targetBo[0]->aabb.upper.x;  // upper upper

			C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
			C_BlockLegacy* blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->velocity.y <= 0) {
				vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->onGround = true;
				targetBo[0]->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb.lower.x;
			pos.z = targetBo[0]->aabb.lower.z;  // lower lower

			block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->velocity.y <= 0) {
				vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += 0.01f;
				targetBo[0]->setPos(pos);
				targetBo[0]->onGround = true;
				targetBo[0]->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb.upper.x;  // upper x and lower z

			block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->velocity.y <= 0) {
				vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->onGround = true;
				targetBo[0]->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb.lower.x;
			pos.z = targetBo[0]->aabb.upper.z;  // lower x and upper z

			block = g_Data.getLocalPlayer()->region->getBlock(vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->velocity.y <= 0) {
				vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->onGround = true;
				targetBo[0]->velocity.y = 0.f;
			}

			if (targetBo[0]->isOnHotBlock() || targetBo[0]->isOnHotBlock()) {
				targetBo[0]->velocity.y = 0.1f;
				targetBo[0]->onGround = true;
			}
		}
	}
}