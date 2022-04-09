#include "Aimbot.h"

Aimbot::Aimbot() : IModule(0, Category::COMBAT, "Automatically aims at the nearest entity") {
	registerBoolSetting("Vertical", &vertical, vertical);
	registerBoolSetting("Lock", &lock, lock); // autism
	registerBoolSetting("Hold", &click, click);
	registerFloatSetting("range", &range, range, 3.f, 8.f);
	//registerBoolSetting("Weaponsssssz", &sword, sword);
	registerFloatSetting("Speed", &speedAm, speedAm, 10.f, 90.f);
	registerFloatSetting("Angle", &rangeAm, rangeAm, 20.f, 180.f);
}

Aimbot::~Aimbot() {
}

const char* Aimbot::getModuleName() {
	return ("Aimbot");
}

static std::vector<C_Entity*> lockList;

void lockOnEntity(C_Entity* currentEntity, bool isRegularEntity) {
	static auto aimbot = moduleMgr->getModule<Aimbot>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

		if (!Target::isValidTarget(currentEntity))
			return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < aimbot->range) {
		lockList.push_back(currentEntity);
	}
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void Aimbot::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (!lock) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		if (localPlayer == nullptr)
			return;
		C_EntityList* entList = g_Data.getEntityList();
		if (entList == nullptr)
			return;
		size_t listSize = entList->getListSize();

		if (listSize > 1000) {
			return;
		}

		vec3_t origin = g_Data.getClientInstance()->levelRenderer->getOrigin();

		//Loop through all our players and retrieve their information
		static std::vector<C_Entity*> targetList;
		targetList.clear();
		for (size_t i = 0; i < listSize; i++) {
			C_Entity* currentEntity = entList->get(i);

			if (!Target::isValidTarget(currentEntity))
				continue;

			float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

			if (dist < range)
				targetList.push_back(currentEntity);
		}

		if (targetList.size() > 0) {
			std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
			vec2_t angle = origin.CalcAngle(*targetList[0]->getPos());
			vec2_t appl = angle.sub(localPlayer->viewAngles).normAngles();
			appl.x = -appl.x;
			if ((appl.x < rangeAm && appl.x > -rangeAm) && (appl.y < rangeAm && appl.y > -rangeAm) && GameData::canUseMoveKeys()) {
				auto selectedItemId = localPlayer->getSelectedItemId();
				if (sword && !(selectedItemId == 268 || selectedItemId == 267 || selectedItemId == 272 || selectedItemId == 276 || selectedItemId == 283 || selectedItemId == 271 || selectedItemId == 275 || selectedItemId == 279 || selectedItemId == 286 || selectedItemId == 258 /*axes*/))
					return;

				if (click && !g_Data.isLeftClickDown())
					return;

				appl.x /= (100.f - speedAm);
				appl.y /= (100.f - speedAm);
				if (appl.x >= 1 || appl.x <= -1) appl.div(abs(appl.x));
				if (appl.y >= 1 || appl.y <= -1) appl.div(abs(appl.y));
				if (!vertical)
					appl.x = 0;
				localPlayer->applyTurnDelta(&appl);
			}
		}
	} else {
		if (click && !g_Data.isLeftClickDown())
			return;
		lockList.clear();
		g_Data.forEachEntity(lockOnEntity);
		for (auto& i : lockList) {
			if (!lockList.empty() && g_Data.canUseMoveKeys()) {
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());
				auto weewee = g_Data.getLocalPlayer();
				weewee->setRot(angle);
				player->resetRot();
			}
		}
	}
}
