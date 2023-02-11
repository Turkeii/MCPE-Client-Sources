#include "BlockOutline.h"
#include "../pch.h"

BlockOutline::BlockOutline() : IModule(0, Category::VISUAL, "Outlines the block your looking at") {
	registerBoolSetting("Rainbow", &rainbow, rainbow);
	registerFloatSetting("Red", &red, red, 0, 1);
	registerFloatSetting("Green", &green, green, 0, 1);
	registerFloatSetting("Blue", &blue, blue, 0, 1);
	registerFloatSetting("Width", &width, width, 0.3, 1);
}

const char* BlockOutline::getModuleName() {
	return ("BlockOutline");
}

void BlockOutline::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
	if (g_Data.canUseMoveKeys()) {
		vec3_t outline = pointing->block.toVector3();
		vec3_t block = pointing->block.toVector3();
		outline = outline.floor();
		block = block.floor();
		outline.x += 1.f;
		outline.y += 1.f;
		outline.z += 1.f;

		if (!rainbow) DrawUtils::setColor(red, green, blue, 1.f);
		if (block != vec3_t{0, 0, 0}) DrawUtils::drawBox(block, outline, width, 1.f, false);
	}
}