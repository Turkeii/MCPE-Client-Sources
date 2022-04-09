#include "ESP.h"

#include "../../../SDK/CCamera.h"
#include "../../../Utils/Target.h"
#include "../../DrawUtils.h"

ESP::ESP() : IModule(0, Category::VISUAL, "Outlines a players hitbox") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Normal", 0);
	mode.addEntry("HitBox", 1);
	registerBoolSetting("Tracers", &tracerMode, tracerMode);
}

ESP::~ESP() {
}

const char* ESP::getModuleName() {
	return "ESP";
}

static float rcolors[4];

void doRenderStuff(C_Entity* ent, bool isRegularEntitie) {
	static auto espMod = moduleMgr->getModule<ESP>();

	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (ent != localPlayer) {
		if (ent->timeSinceDeath > 0)
			return;
		if (FriendList::findPlayer(ent->getNameTag()->getText()) && !moduleMgr->getModule<NoFriends>()->isEnabled()) {
			DrawUtils::setColor(0.1f, 0.9f, 0.1f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else if (Target::isValidTarget(ent)) {
			DrawUtils::setColor(0.9f, 0.9f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else if (espMod->isMobEsp) {
			if (ent->getNameTag()->getTextLength() <= 1 && ent->getEntityTypeId() == 63)
				return;

			if (ent->isInvisible())
				return;

			if (!g_Data.getLocalPlayer()->canAttack(ent, false))
				return;
			DrawUtils::setColor(0.2f, 0.2f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		} else
			return;
		if (espMod->is2d)
			DrawUtils::draw2D(ent, (float)fmax(0.4f, 1 / (float)fmax(1, (*localPlayer->getPos()).dist(*ent->getPos()) * 3.f)));
		else
			DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, (*localPlayer->getPos()).dist(*ent->getPos()))));
	}
}

void ESP::onLevelRender() {
	if (tracerMode) {
		if (!g_Data.getLocalPlayer()) return;
		/*auto cameraMgr = g_Data.getClientInstance()->getCameraManager();
    if(cameraMgr == nullptr)
        return;
    auto cam = cameraMgr->getCameraOrDebugCamera();
    if(cam == nullptr)
        return;
    vec3_t forward{};
    cam->getForwardVector(&forward);*/
		//idk how to find that, too lazy to update soooooooo lets do it like jetpack

		float calcYaw = (g_Data.getLocalPlayer()->yaw + 90) * (PI / 180);
		float calcPitch = (g_Data.getLocalPlayer()->pitch) * -(PI / 180);

		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * 0.5f;
		moveVec.y = sin(calcPitch) * 0.5f;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * 0.5f;

		const vec3_t origin = g_Data.getClientInstance()->levelRenderer->getOrigin().add(moveVec); /*place the start of the line slightly forward so it won't get clipped*/
		g_Data.forEachEntity([&](C_Entity* ent, bool valid) {
			if (ent != g_Data.getLocalPlayer() && Target::isValidTarget(ent)) {
				DrawUtils::setColor(255, 255, 255, 1);
				DrawUtils::drawLine3d(origin, *ent->getPos());
			}
		});
	}
}

void ESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	if (localPlayer != nullptr && GameData::canUseMoveKeys())
		g_Data.forEachEntity(doRenderStuff);
}