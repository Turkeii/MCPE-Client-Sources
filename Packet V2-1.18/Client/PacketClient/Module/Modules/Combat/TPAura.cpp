#include "TPAura.h"
#include "../pch.h"

using namespace std;
TPAura::TPAura() : IModule(0, Category::COMBAT, "Attacks entities from far ranges") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Multi", 0);
	mode.addEntry("Switch", 1);
	registerIntSetting("Delay", &delay, delay, 1, 50);
	registerFloatSetting("Range", &range, range, 5.f, 250.f);
}

const char* TPAura::getModuleName() {
	return ("TPAura");
}

static vector<C_Entity*> targetList;
void findEntTPA(C_Entity* currentEntity, bool isRegularEntity) {
	static auto tpaura = moduleMgr->getModule<TPAura>();

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

	if (currentEntity->getEntityTypeId() == 80 || currentEntity->getEntityTypeId() == 69)  // XP and Arrows
		return;

	if (!TargetUtil::isValidTarget(currentEntity))
		return;

	if (currentEntity->getEntityTypeId() == 51 || currentEntity->getEntityTypeId() == 1677999)  // Villagers and NPCS
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < tpaura->range) targetList.push_back(currentEntity);
}

void TPAura::onEnable() {
	teleported = false; ticks = 0;
	targetList.clear();
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void TPAura::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	ticks++;

	int APS = 20;
	targetList.clear();
	g_Data.forEachEntity(findEntTPA);

	if (g_Data.canUseMoveKeys() && !targetList.empty() && teleported) {
		if (TimerUtil::hasTimedElapsed((1000 / APS), true)) {
			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				player->swing();

			for (auto& i : targetList) {
				// crashes
				if (mode.getSelectedValue() == 0) gm->attack(i);
				else gm->attack(targetList[0]);
				clientMessageF("attacked");
			}
		}
	}
}

void TPAura::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TPAura::onLevelRender() {
}

void TPAura::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);

		static int ticksSinceTeleport = 0;
		if (g_Data.canUseMoveKeys() && !targetList.empty()) {
			vec3_t entPos = *targetList[0]->getPos();
			vec3_t pos = *player->getPos();

			if (ticks % delay == 0) {
				clientMessageF("teleported");
				movePacket->Position.x = entPos.x;
				movePacket->Position.y = entPos.y;
				movePacket->Position.z = entPos.z;
				teleported = true;
				ticksSinceTeleport++;
			}

			if (ticksSinceTeleport >= 3) {
				teleported = false;
				clientMessageF("set back");
				movePacket->Position.x = pos.x; movePacket->Position.y = pos.y; movePacket->Position.z = pos.z;
				ticksSinceTeleport = 0;
			}
		}
	}
}

void TPAura::onDisable() {
}