#include "Killaura.h"

Killaura::Killaura() : IModule(0, Category::COMBAT, "Automatically attacks entites") {
	registerEnumSetting("Rotations", &mode, 0);
	mode.addEntry("Normal", 0);
	mode.addEntry("Smooth", 1);
	mode.addEntry("Silent", 2);
	mode.addEntry("None", 3);
	registerBoolSetting("Visualize", &visualize, visualize);
	registerBoolSetting("Strafe", &strafe, strafe);
	registerBoolSetting("Multi", &multi, multi);
	registerBoolSetting("Mobs", &mobs, mobs);
	registerBoolSetting("Click", &click, click);
	registerBoolSetting("Hold", &hold, hold);
	registerFloatSetting("Range", &range, range, 3.f, 8.f);
	registerIntSetting("MaxAPS", &maxAPS, maxAPS, 1, 20);
	registerIntSetting("MinAPS", &minAPS, minAPS, 1, 20);
}

Killaura::~Killaura() {
}

const char* Killaura::getRawModuleName() {
	return "Killaura";
}

const char* Killaura::getModuleName() {
	if (multi) name = std::string("Killaura ") + std::string(GRAY) + std::string("Multi");
	else if (!multi) name = std::string("Killaura ") + std::string(GRAY) + std::string("Switch");
	return name.c_str();
}

static std::vector<C_Entity*> targetList;

void findEntity(C_Entity* currentEntity, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<Killaura>();

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

	if (currentEntity->getEntityTypeId() == 80)  // Arrows
		return;

	if (killauraMod->mobs) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  //item
			return;

	}
	else {
		if (!Target::isValidTarget(currentEntity))
			return;

		if (currentEntity->getEntityTypeId() == 1677999)  // Villager
			return;

		if (currentEntity->getEntityTypeId() == 51)  // NPC
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void Killaura::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	targetList.clear();
}

void Killaura::onTick(C_GameMode* gm) {
	auto clickGUI = moduleMgr->getModule<ClickGuiMod>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetListEmpty = targetList.empty();
	if (clickGUI->isEnabled()) targetListEmpty = true;

	targetList.clear();

	g_Data.forEachEntity(findEntity);

	if (g_Data.canUseMoveKeys()) {
		if (hold && !g_Data.isLeftClickDown())
			return;

		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		for (auto& i : targetList) {
			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				player->swingArm();
			if (multi) gm->attack(i);
			else gm->attack(targetList[0]);
		}
	}
	else targetListEmpty = true;

	for (auto& i : targetList) {
		PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
		/*Odelay++;

		if (click && !targetList.empty()) {
			if (Odelay >= delay) {
				g_Data.leftclickCount++;
				if (pointing->hasEntity())
					gm->attack(pointing->getEntity());
			}
		}*/
	}
}

void Killaura::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();
	g_Data.forEachEntity(findEntity);
	if (g_Data.canUseMoveKeys()) {
		if (hold && !g_Data.isLeftClickDown())
			return;
		if (!targetList.empty() && g_Data.isInGame()) {
			vec2_t angle;
			angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());

			// Normal
			if (mode.getSelectedValue() == 0) {
				plr->bodyYaw = angle.y;
				plr->yawUnused1 = angle.y;
				plr->pitch = angle.x;
			}
			// Smooth
			/*if (mode.getSelectedValue() == 1) {
				plr->bodyYaw = angle.y;
				plr->yawUnused1 = angle.y;
				plr->pitch = angle.x;
			}*/
			// Strafe
			// put the strafe inside the strafe
		}
	}
}

void Killaura::onSendPacket(C_Packet* packet) {
	targetList.clear();
	g_Data.forEachEntity(findEntity);
	if (g_Data.canUseMoveKeys()) {
		if (hold && !g_Data.isLeftClickDown())
			return;
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr && mode.getSelectedValue() == 0 || mode.getSelectedValue() == 1 && g_Data.isInGame()) {
			if (!targetList.empty()) {
				vec2_t angle;
				angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
				//This adds randomization for bypasses :)
				auto* pkt = reinterpret_cast<C_MovePlayerPacket*>(packet);
				float xChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.f));
				xChange -= 1.5f;

				pkt->yaw = angle.y + xChange;
				pkt->headYaw = angle.y + xChange;
				float yChange = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.5f));
				yChange -= 0.75f;
				pkt->pitch = angle.x + yChange;
			}
		}
	}
}

void Killaura::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void Killaura::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}