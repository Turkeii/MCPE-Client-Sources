#include "ClickTP.h"
#include "../pch.h"

ClickTP::ClickTP() : IModule(0, Category::OTHER, "Teleports to where you are looking") {
	registerBoolSetting("Hand", &hand, hand);
}

const char* ClickTP::getModuleName() {
	return "ClickTP";
}

void ClickTP::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (hand && player->getSupplies()->inventory->getItemStack(player->getSupplies()->selectedHotbarSlot)->item != nullptr)
		return;

	if (g_Data.canUseMoveKeys() && g_Data.isRightClickDown() && !hasClicked) {
		hasClicked = true;

		vec3_ti block = g_Data.getLocalPlayer()->pointingStruct->block;
		if (block == vec3_ti(0, 0, 0)) return;

		vec3_t pos = block.toFloatVector();
		pos.x += 0.5f; pos.z += 0.5f; position = pos;

		position.y += (player->getPos()->y - player->getAABB()->lower.y) + 1;
		player->setPos(position);
	}
	if (!g_Data.isRightClickDown()) hasClicked = false;
}

void ClickTP::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (g_Data.canUseMoveKeys() && hasClicked) {
		PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;

		vec3_t block = pointing->block.toVector3();
		block = block.floor();
		vec3_t outline = pointing->block.toVector3();
		outline = outline.floor();
		outline.x += 1.f;
		outline.y += 1.f;
		outline.z += 1.f;

		DrawUtils::setColor(0, 1, 0, 1);
		DrawUtils::drawBox(block, outline, 0.6, 1);
	}
}