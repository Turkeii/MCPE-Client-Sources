#include "Breadcrums.h"
#include "../../DrawUtils.h"

Breadcrums::Breadcrums() : IModule(0x0, Category::VISUAL, "Leaves a trail behind you so that you dont get lost") {
	registerBoolSetting("ClearOnDisable", &clearOndisable, clearOndisable);
	registerBoolSetting("StopBreadcrums", &stopBreadCrums, stopBreadCrums);
}

Breadcrums::~Breadcrums() {
}

const char* Breadcrums::getModuleName() {
	return ("Breadcrums");
}

void Breadcrums::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	vec3_t floorPos = *g_Data.getLocalPlayer()->getPos();
	floorPos.y = g_Data.getLocalPlayer()->getAABB()->lower.y + 0.2f;

	if (!stopBreadCrums)
	linePoints.push_back(floorPos);
}

void Breadcrums::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (!linePoints.empty()) {
		DrawUtils::setColor(1.f, 1.f, 1.f, 1.f);
		DrawUtils::drawLinestrip3d(linePoints);
	}
}

void Breadcrums::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (clearOndisable)
	linePoints.clear();
}
