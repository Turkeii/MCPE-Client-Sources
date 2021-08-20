#include "NoEntityRender.h"

NoEntityRender::NoEntityRender() : IModule(0x0, Category::VISUAL, "Un-renders certain entities") {
	registerBoolSetting("FallingBlocks", &this->isFallingBlock, this->isFallingBlock);
	registerBoolSetting("EffectCloud", &this->isEffectCloud, this->isEffectCloud);
	registerBoolSetting("PrimedTnt", &this->isTNT, this->isTNT);
	registerBoolSetting("Paintings", &this->isPainting, this->isPainting);
	registerBoolSetting("ArmourStands", &this->isArmourStand, this->isArmourStand);
	registerBoolSetting("Boats", &this->isBoat, this->isBoat);
	registerBoolSetting("Minecarts", &this->isMinecart, this->isMinecart);
	registerBoolSetting("Items", &this->isItems, this->isItems);
	registerBoolSetting("XP", &this->isXp, this->isXp);
}

NoEntityRender::~NoEntityRender() {
}

const char* NoEntityRender::getModuleName() {
	return ("NoEntityRender");
}


static std::vector<C_Entity*> targetList;
void boats(C_Entity* currentEntity, bool isRegularEntity) {

	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void fallingblocks(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 66)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void painting(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 83)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void Items(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 64)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void Xp(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 69)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void TNT(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 65)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void ArmourStand(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 61)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void Minecart(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 84)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void EffectCloud(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 95)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void NoEntityRender::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();

	if (isBoat)
	g_Data.forEachEntity(boats);

	if (isFallingBlock)
	g_Data.forEachEntity(fallingblocks);

	if (isPainting)
	g_Data.forEachEntity(painting);

	if (isItems)
	g_Data.forEachEntity(Items);

	if (isXp)
	g_Data.forEachEntity(Xp);

	if (isTNT)
	g_Data.forEachEntity(TNT);

	if (isArmourStand)
	g_Data.forEachEntity(ArmourStand);

	if (isMinecart)
	g_Data.forEachEntity(Minecart);

	if (isEffectCloud)
	g_Data.forEachEntity(EffectCloud);


	if (!targetList.empty()) {

		for (auto& i : targetList) {
			i->despawn();
		}
	}
}