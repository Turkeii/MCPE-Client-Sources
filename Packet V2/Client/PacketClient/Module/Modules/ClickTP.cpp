#include "ClickTP.h"

ClickTP::ClickTP() : IModule(0, Category::MISC, "Hold Right Click to TP TO SHIT") {
	registerBoolSetting("Hand", &hand, hand);
}

ClickTP::~ClickTP() {
}

const char* ClickTP::getModuleName() {
	return "ClickTP";
}

void ClickTP::onTick(C_GameMode* gm) {
	if (!GameData::canUseMoveKeys())
		return;

	if (hand && g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot)->item != nullptr)
		return;

	if (GameData::isRightClickDown() && !hasClicked) {
		hasClicked = true;

		vec3_ti block = g_Data.getClientInstance()->getPointerStruct()->block;
		if (block == vec3_ti(0, 0, 0)) return;
		vec3_t pos = block.toFloatVector();
		pos.x += 0.5f;
		pos.z += 0.5f;

		position = pos;

		position.y += (gm->player->getPos()->y - gm->player->getAABB()->lower.y) + 1;  // eye height + 1
		gm->player->setPos(position);
		//gm->player->chorusFruitTeleport(position);
	}
	if (!GameData::isRightClickDown())
		hasClicked = false;
}

void ClickTP::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (g_Data.canUseMoveKeys() && g_Data.getLocalPlayer() != nullptr && isEnabled() && hasClicked) {
		PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
		vec3_t block = pointing->block.toVec3t();
		block = block.floor();
		vec3_t outline = pointing->block.toVec3t();
		outline = outline.floor();
		outline.x += 1.f;
		outline.y += 1.f;
		outline.z += 1.f;

		DrawUtils::setColor(0, 1, 0, 1);
		DrawUtils::drawBox(block, outline, 0.6, 1);
	}
}