#include "BreadCrumbs.h"

BreadCrumbs::BreadCrumbs() : IModule(0, Category::VISUAL, "ezpssssz") {
	registerBoolSetting("Clear", &clear, clear);
}

BreadCrumbs::~BreadCrumbs() {
}

const char* BreadCrumbs::getModuleName() {
	return ("BreadCrumbs");
}

void BreadCrumbs::onTick(C_GameMode* gm) {
	vec3_t eyePos = gm->player->eyePos0;
	eyePos.y = eyePos.y - 1.5;
	blockBelow.push_back(eyePos);
	if (clear) {
		blockBelow.clear();
		clear = false;
	}
}

void BreadCrumbs::onLevelRender() {
	DrawUtils::setColor(1, 1, 1, 1);
	DrawUtils::drawLinestrip3d(blockBelow);
}

void BreadCrumbs::onDisable() {
	blockBelow.clear();
}