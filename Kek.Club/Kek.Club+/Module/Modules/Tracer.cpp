#include "Tracer.h"

#include "../../../SDK/CCamera.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"
int Tracer::rFloat{255};
int Tracer::gFloat{255};
int Tracer::bFloat{255};
float opacity = 1.f;
bool old = false;
Tracer::Tracer() : IModule('R', Category::VISUAL, "DRAWS LINES") {
	registerBoolSetting("3D", &old, old);
	registerIntSetting("Red", &rFloat, rFloat, 0, 255);
	registerIntSetting("Green", &gFloat, gFloat, 0, 255);
	registerIntSetting("Blue", &bFloat, bFloat, 0, 255);
	registerFloatSetting("Thickness", &thickness, thickness, 0.2f, 1.f);
	registerFloatSetting("Opacity", &opacity, opacity, 0.1f, 1.f);
}

Tracer::~Tracer() {
}

const char* Tracer::getModuleName() {
	return "Tracer";
}

void Tracer::onLevelRender() {
	if (old) {
		if (!g_Data.getLocalPlayer()) return;
		float calcYaw = (g_Data.getLocalPlayer()->yaw + 90) * (PI / 180);
		float calcPitch = (g_Data.getLocalPlayer()->pitch) * -(PI / 180);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * 0.5f;
		moveVec.y = sin(calcPitch) * 0.5f;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * 0.5f;

		const vec3_t origin = g_Data.getClientInstance()->levelRenderer->getOrigin().add(moveVec); /*place the start of the line slightly forward so it won't get clipped*/
		g_Data.forEachEntity([&](C_Entity* ent, bool valid) {
			if (ent != g_Data.getLocalPlayer() && Target::isValidTarget(ent)) {
				DrawUtils::setColor(rFloat, gFloat, bFloat, opacity);
				DrawUtils::drawLine3d(origin, *ent->getPos());
			}
		});
	}
}

std::shared_ptr<glmatrixf> refdef2;
void Tracer::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	glmatrixf* badrefdef = g_Data.getClientInstance()->getRefDef();
	refdef2 = std::shared_ptr<glmatrixf>(badrefdef->correct());
	if (!old) {
		g_Data.forEachEntity([&](C_Entity* ent, bool valid) {
			if (ent != g_Data.getLocalPlayer() && Target::isValidTarget(ent) && g_Data.canUseMoveKeys()) {
				static auto tracerMod = moduleMgr->getModule<Tracer>();
				vec2_t target;
				vec2_t screenSize;
				screenSize.x = g_Data.getGuiData()->widthGame;
				screenSize.y = g_Data.getGuiData()->heightGame;
				refdef2->OWorldToScreen(g_Data.getClientInstance()->levelRenderer->getOrigin(), ent->eyePos0, target, g_Data.getClientInstance()->getFov(), screenSize);
				vec2_t mid(((g_Data.getClientInstance()->getGuiData()->widthGame) / 2), ((g_Data.getClientInstance()->getGuiData()->heightGame) / 2));
				if (target != vec2_t(0, 0)) {
					DrawUtils::setColor(Tracer::rFloat, Tracer::gFloat, Tracer::bFloat, opacity);

					DrawUtils::drawLine(mid, target, thickness);
				}
			}
		});
	}
}