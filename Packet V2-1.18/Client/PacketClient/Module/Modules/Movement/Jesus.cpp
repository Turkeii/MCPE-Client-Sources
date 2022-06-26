#include "Jesus.h"
#include "../pch.h"
uintptr_t ViewBobbingJesusChristMan = FindSignature("0F B6 80 DB 01 00 00");

using namespace std;
Jesus::Jesus() : IModule(0, Category::MOVEMENT, "Allows you to walk on Liquids") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Solid", 0);
	mode.addEntry("Bounce", 1);
	registerFloatSetting("Height", &height, height, 0.1, 3);
}

const char* Jesus::getRawModuleName() {
	return "Jesus";
}

const char* Jesus::getModuleName() {
	if (mode.getSelectedValue() == 0) name = string("Jesus ") + string(GRAY) + string("Solid");
	if (mode.getSelectedValue() == 1) name = string("Jesus ") + string(GRAY) + string("Bounce");
	return name.c_str();
}

void Jesus::onTick(C_GameMode* gameMode) {
	if (gameMode->player->isSneaking()) return;

	if (gameMode->player->hasEnteredWater()) {
		gameMode->player->velocity.y = height;
		gameMode->player->onGround = true;
		wasInWater = true;
	}
	else if (gameMode->player->isInWater() || gameMode->player->isInLava()) {
		gameMode->player->velocity.y = height;
		gameMode->player->onGround = true;
		wasInWater = true;
	}
	else {
		if (wasInWater) {
			wasInWater = false;
			gameMode->player->velocity.x *= 1.2f;
			gameMode->player->velocity.x *= 1.2f;
		}
	}
	if (mode.selected == 1) return;
	{
		if (gameMode->player->isSneaking()) return;
		if (gameMode->player->isOnFire()) return;

		vec3_t pos = *gameMode->player->getPos();
		pos.y -= 1.62f;

		pos.z = gameMode->player->aabb.upper.z;
		pos.x = gameMode->player->aabb.upper.x;  // upper upper

		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		C_BlockLegacy* blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && gameMode->player->velocity.y <= 0) {
			vec3_t pos = *gameMode->player->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			gameMode->player->setPos(pos);
			gameMode->player->onGround = true;
			gameMode->player->velocity.y = 0.f;
		}

		pos.x = gameMode->player->aabb.lower.x;
		pos.z = gameMode->player->aabb.lower.z;  // lower lower

		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && gameMode->player->velocity.y <= 0) {
			vec3_t pos = *gameMode->player->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			gameMode->player->setPos(pos);
			gameMode->player->onGround = true;
			gameMode->player->velocity.y = 0.f;
		}

		pos.x = gameMode->player->aabb.upper.x;  // upper x and lower z
		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && gameMode->player->velocity.y <= 0) {
			vec3_t pos = *gameMode->player->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			gameMode->player->setPos(pos);
			gameMode->player->velocity.y = 0.f;
		}

		pos.x = gameMode->player->aabb.lower.x;
		pos.z = gameMode->player->aabb.upper.z;  // lower x and upper z

		block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && gameMode->player->velocity.y <= 0) {
			vec3_t pos = *gameMode->player->getPos();
			pos.y -= 0.62f;
			pos.y = ceilf(pos.y);
			pos.y += 0.61f;
			gameMode->player->setPos(pos);
			gameMode->player->onGround = true;
			gameMode->player->velocity.y = 0.f;
		}

		if (gameMode->player->isInWater()) {
			gameMode->player->velocity.y = 0.1f;
			gameMode->player->onGround = true;
		}
	}
}
void Jesus::onMove(C_MoveInputHandler* input) {
	if (viewBobbingEffective)
		Utils::patchBytes((unsigned char*)ViewBobbingJesusChristMan, (unsigned char*)"\xB8\x01\x00\x00\x00\x90\x90", 7);
	else
		Utils::patchBytes((unsigned char*)ViewBobbingJesusChristMan, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);
}
void Jesus::onDisable() {
	Utils::patchBytes((unsigned char*)ViewBobbingJesusChristMan, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);
	viewBobbingEffective = false;
	velocityEffective = false;
}