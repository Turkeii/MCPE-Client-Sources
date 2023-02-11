#include "ESP.h"
#include "../pch.h"

ESP::ESP() : IModule(0, Category::VISUAL, "Outlines players") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Normal", 0);
	mode.addEntry("Hitbox", 1);
	mode.addEntry("2D", 2);
	registerBoolSetting("Tracers", &tracers, tracers);
}

const char* ESP::getModuleName() {
	return "ESP";
}

void doRenderStuff(C_Entity* ent, bool isRegularEntitie) {
	static auto esp = moduleMgr->getModule<ESP>();

	auto player = g_Data.getLocalPlayer();
	if (ent->timeSinceDeath > 0) return;

	if (TargetUtil::isValidTarget(ent)) DrawUtils::setColor(0.9f, 0.9f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
	else if (esp->mobs) {
		if (ent->getNameTag()->getTextLength() <= 1 && ent->getEntityTypeId() == 63)
			return;

		if (ent->isInvisible())
			return;

		if (!g_Data.getLocalPlayer()->canAttack(ent, false))
			return;
		DrawUtils::setColor(0.2f, 0.2f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
	}
	else return;

	if (esp->mode.getSelectedValue() == 2) DrawUtils::drawBetter2D(ent, (float)fmax(0.3f, 1 / (float)fmax(1, (*player->getPos()).dist(*ent->getPos()) * 3.f)));
	else DrawUtils::drawEntityBox(ent, (float)fmax(0.2f, 1 / (float)fmax(1, (*player->getPos()).dist(*ent->getPos()))));
}

void ESP::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	if (tracers) {
		/*auto cameraMgr = g_Data.getClientInstance()->getCameraManager();
		if(cameraMgr == nullptr) return;
		auto cam = cameraMgr->getCameraOrDebugCamera();
		if(cam == nullptr) return;
		vec3_t forward{};
		cam->getForwardVector(&forward);*/
		//idk how to find that, too lazy to update soooooooo lets do it like jetpack, LMAO og ass comment

		float calcYaw = (player->yaw + 90) * (PI / 180);
		float calcPitch = (player->pitch) * -(PI / 180);

		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * 0.5f;
		moveVec.y = sin(calcPitch) * 0.5f;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * 0.5f;

		const vec3_t origin = g_Data.getClientInstance()->levelRenderer->getOrigin().add(moveVec);
		g_Data.forEachEntity([&](C_Entity* ent, bool valid) {
			if (ent != g_Data.getLocalPlayer() && TargetUtil::isValidTarget(ent)) {
				DrawUtils::setColor(255, 255, 255, 1);
				DrawUtils::drawLine3d(origin, *ent->getPos());
			}
		});
	}
}

void ESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (g_Data.canUseMoveKeys()) g_Data.forEachEntity(doRenderStuff);
}