#include "BreadCrumbs.h"
#include "../pch.h"

BreadCrumbs::BreadCrumbs() : IModule(0, Category::VISUAL, "Shows a trail where you've walked") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Normal", 0);
	mode.addEntry("Strip", 1);
	registerBoolSetting("Clear", &clear, clear);
}

const char* BreadCrumbs::getModuleName() {
	return ("BreadCrumbs");
}

void BreadCrumbs::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (clear) { blockBelow.clear(); clear = false; }

	vec3_t eyePos = player->eyePos0;
	eyePos.y = eyePos.y - 1.5f;
	blockBelow.push_back(eyePos);
}

void BreadCrumbs::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	DrawUtils::setColor(1, 1, 1, 1);
	switch (mode.getSelectedValue()) {
	case 0: // Normal
		DrawUtils::drawLineStrip3D(blockBelow, 5);
		break;
	case 1: // Strip
		DrawUtils::drawLineStrip3D(blockBelow, 4);
		break;
	}
}

void BreadCrumbs::onDisable() {
	blockBelow.clear();
}