#include "Breadcrumbs.h"

#include "../../../SDK/CCamera.h"
#include "../../DrawUtils.h"
int Breadcrumbs::rFloat{255};
int Breadcrumbs::gFloat{255};
int Breadcrumbs::bFloat{255};
Breadcrumbs::Breadcrumbs() : IModule(0x0, Category::VISUAL, "Draws a path from the places you have gone through") {
	registerIntSetting("Red", &rFloat, rFloat, 0, 255);
	registerIntSetting("Green", &gFloat, gFloat, 0, 255);
	registerIntSetting("Blue", &bFloat, bFloat, 0, 255);
	registerFloatSetting("Thickness", &thickness, thickness, 0.2f, 1.f);
	registerBoolSetting("Show Orgin", &show, show);
}

Breadcrumbs::~Breadcrumbs() {
}

const char* Breadcrumbs::getModuleName() {
	return ("Breadcrumbs");
}

void Breadcrumbs::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	vec3_t floorPos = *g_Data.getLocalPlayer()->getPos();
	floorPos.y = g_Data.getLocalPlayer()->getAABB()->lower.y + 0.1f;

	linePoints.push_back(floorPos);
}

void Breadcrumbs::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr) return;
		startPos = g_Data.getLocalPlayer()->aabb.lower;
		startPosTop = g_Data.getLocalPlayer()->aabb.upper;
}

void Breadcrumbs::onDisable() {
	if (g_Data.getLocalPlayer() == nullptr) return;

	linePoints.clear();
}

void Breadcrumbs::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (!linePoints.empty()) {
		if (show) {
			DrawUtils::drawText(DrawUtils::worldToScreen(linePoints[0]), &std::string("0"), MC_Color(1.f, 1.f, 1.f, 1.f));
		}
	}
}

void Breadcrumbs::onLevelRender() {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (!linePoints.empty()) {
		DrawUtils::setColor(Breadcrumbs::rFloat, Breadcrumbs::gFloat, Breadcrumbs::bFloat, thickness);
		DrawUtils::drawLinestrip3d(linePoints);
	}
}