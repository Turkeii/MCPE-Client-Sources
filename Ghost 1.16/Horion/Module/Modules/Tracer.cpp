#include "Tracer.h"
#include "../../DrawUtils.h"

#include "../../../SDK/CCamera.h"
#include "../ModuleManager.h"

Tracer::Tracer() : IModule('R', Category::VISUAL, "Draws lines to ESP highlighted entities") {
	registerBoolSetting("2D", &this->is2d, this->is2d);
	this->registerIntSetting("Red", &this->customR, this->customR, 0, 255);
	this->registerIntSetting("Green", &this->customG, this->customG, 0, 255);
	this->registerIntSetting("Blue", &this->customB, this->customB, 0, 255);
	registerBoolSetting("Chests", &this->chest, this->chest);
	this->registerIntSetting("Red", &this->customR2, this->customR2, 0, 255);
	this->registerIntSetting("Green", &this->customG2, this->customG2, 0, 255);
	this->registerIntSetting("Blue", &this->customB2, this->customB2, 0, 255);
}

Tracer::~Tracer() {
}

const char* Tracer::getModuleName() {
	return "Tracer";

	float customColors[4];
	float customRF;
	float customGF;
	float customBF;
}

void doRenderStuff3(C_Entity* ent, bool isRegularEntitie) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	static auto tracerMod = moduleMgr->getModule<Tracer>();
	static auto freecamMod = moduleMgr->getModule<Freecam>();
	if (ent == nullptr) return;

	vec3_t forwardVec = tracerMod->cameraPos;
	vec2_t facing = tracerMod->cameraRot;

	float calcYaw = (facing.y + 90) * (PI / 180);
	float calcPitch = (facing.x) * -(PI / 180);

	forwardVec.x += cos(calcYaw) * cos(calcPitch) * 0.2f;
	forwardVec.y += sin(calcPitch) * 0.2f;
	forwardVec.z += sin(calcYaw) * cos(calcPitch) * 0.2f;
	auto entPosition = ent->aabb.centerPoint();
	entPosition.y = ent->aabb.upper.y;

	if (ent != g_Data.getLocalPlayer() && Target::isValidTarget(ent)) {
		DrawUtils::setColor(((float)tracerMod->customR / (float)255), ((float)tracerMod->customG / (float)255), ((float)tracerMod->customB / (float)255), (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->damageTime + 1))));
		DrawUtils::drawLine3d(forwardVec, entPosition);
	}
}

void Tracer::onLevelRender() {
	if (g_Data.getLocalPlayer() == nullptr) return;
	static auto tracerMod = moduleMgr->getModule<Tracer>();

	if (!is2d) {
		g_Data.forEachEntity(doRenderStuff3);
	}

	if (chest) {
		if (!g_Data.isInGame() || !GameData::canUseMoveKeys() || g_Data.getLocalPlayer() == nullptr)
			return;

		vec3_t forwardVec = cameraPos;
		vec2_t facing = cameraRot;

		float calcYaw = (facing.y + 90) * (PI / 180);
		float calcPitch = (facing.x) * -(PI / 180);

		forwardVec.x += cos(calcYaw) * cos(calcPitch) * 0.2f;
		forwardVec.y += sin(calcPitch) * 0.2f;
		forwardVec.z += sin(calcYaw) * cos(calcPitch) * 0.2f;

		for (auto iter = bufferedChestList.begin(); iter != bufferedChestList.end(); ++iter) {
			DrawUtils::setColor(((float)tracerMod->customR2 / (float)255), ((float)tracerMod->customG2 / (float)255), ((float)tracerMod->customB2 / (float)255), 1.f);
			DrawUtils::drawLine3d(forwardVec, (*iter)->upper);
		//	auto uhhhhhhhhh = (*iter)->upper;
		//	DrawUtils::drawBox(uhhhhhhhhh.floor(), uhhhhhhhhh, 1.f);
		}
	}
}

void Tracer::onTick(C_GameMode* gm) {
	auto listLock = g_Data.lockChestList();
	auto* chestList = g_Data.getChestList();
	auto ourListLock = std::scoped_lock(this->listLock);

	this->bufferedChestList.clear();
	this->bufferedChestList.insert(this->bufferedChestList.end(), chestList->begin(), chestList->end());
	chestList->clear();
}

void Tracer::onPreRender(C_MinecraftUIRenderContext* ctx) {
	if (GameData::canUseMoveKeys())  //sexy 2d shit
		g_Data.forEachEntity([](C_Entity* ent, bool valid) {
			if (Target::isValidTarget(ent) && ent != g_Data.getLocalPlayer())
				DrawUtils::drawTracer(ent);
		});
}