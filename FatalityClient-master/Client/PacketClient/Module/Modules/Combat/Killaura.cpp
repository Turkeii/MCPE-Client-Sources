#include "Killaura.h"
#include "../pch.h"

using namespace std;
Killaura::Killaura() : IModule(0, Category::COMBAT, "Attacks entities") {
	registerEnumSetting("Rotations", &rotations, 0);
	rotations.addEntry("Exhibition", 0);
	rotations.addEntry("Smooth", 1);
	rotations.addEntry("Silent", 2);
	rotations.addEntry("None", 3);
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Multi", 0);
	mode.addEntry("Switch", 1);
	mode.addEntry("Single", 2);
	registerBoolSetting("Visualize", &visualize, visualize);
	registerBoolSetting("Strafe", &strafe, strafe);
	registerBoolSetting("Click", &click, click);
	registerBoolSetting("Hold", &hold, hold);
	registerFloatSetting("Smoothing", &smoothing, smoothing, 1.f, 80.f);
	registerFloatSetting("Random", &random, random, 0.f, 15.f);
	registerFloatSetting("Range", &range, range, 3.f, 8.f);
	//registerMinMaxSetting("APS", &maxAPS, maxAPS, 1, 69);
	registerIntSetting("MaxAPS", &maxAPS, maxAPS, 1, 69);
	registerIntSetting("MinAPS", &minAPS, minAPS, 1, 69);
}

const char* Killaura::getRawModuleName() {
	return "KillAura";
}

const char* Killaura::getModuleName() { 
	switch (mode.getSelectedValue()) {
	case 0: name = string("KillAura ") + string(GRAY) + string("(Multi)"); break;
	case 1: name = string("KillAura ") + string(GRAY) + string("(Switch)"); break;
	case 2: name = string("KillAura ") + string(GRAY) + string("(Single)"); break; }
	return name.c_str();
}

static vector<C_Entity*> targetList;
void findEntity(C_Entity* currentEntity, bool isRegularEntity) {
	static auto killaura = moduleMgr->getModule<Killaura>();

	if (currentEntity == nullptr) return;
	if (currentEntity == g_Data.getLocalPlayer()) return;
	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false)) return;
	if (!g_Data.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;
	if (currentEntity->getEntityTypeId() == 80 || currentEntity->getEntityTypeId() == 69) return;

	if (killaura->mobs) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63) return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f) return;
		if (currentEntity->getEntityTypeId() == 64) return;
	}
	else {
		if (!TargetUtil::isValidTarget(currentEntity)) return;
		if (currentEntity->getEntityTypeId() == 51 || currentEntity->getEntityTypeId() == 1677999) return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < killaura->range) targetList.push_back(currentEntity);
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

	targetListEmpty = true;
	targetList.clear();
}

void Killaura::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
	auto clickGUI = moduleMgr->getModule<ClickGUIMod>();
	if (clickGUI->isEnabled()) targetListEmpty = true;
	targetListEmpty = targetList.empty();

	targetList.clear();
	g_Data.forEachEntity(findEntity);

	if (g_Data.canUseMoveKeys() && !targetList.empty()) {
		if (TimerUtil::hasTimedElapsed((1000 / APS), true)) {
			if (hold && !g_Data.isLeftClickDown())
				return;

			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				player->swing();

			for (auto& i : targetList) {
				if (mode.getSelectedValue() == 0) gm->attack(i);
				else gm->attack(targetList[0]);
			}
		}

		for (auto& i : targetList) {
			delay++;
			if (click && !targetList.empty()) {
				if (delay >= 0) {
					g_Data.leftclickCount++;
					if (pointing->hasEntity()) gm->attack(pointing->getEntity());
				}
			}
		}
	}
	else targetListEmpty = true;
}

void Killaura::onPlayerTick(C_Player* plr) {
	if (plr == nullptr) return;

	if (g_Data.canUseMoveKeys() && !targetList.empty()) {
		APS = randomFloat(maxAPS, minAPS);
		if (maxAPS < minAPS) maxAPS = minAPS;
		if (hold && !g_Data.isLeftClickDown())
			return;

		xRandom = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / random));
		yRandom = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / random));
		if (random >= 0.f) { yRandom += 1.75f; xRandom -= 3.5f; }

		sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		for (auto& i : targetList) {
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			vec2_t pos = g_Data.getLocalPlayer()->getPos()->CalcAngle(*i->getPos());

			if (animYaw > angle.y) animYaw -= ((animYaw - angle.y) / smoothing);
			else if (animYaw < angle.y) animYaw += ((angle.y - animYaw) / smoothing);

			switch (rotations.getSelectedValue()) {
			case 0: // Normal
				plr->yawUnused1 = animYaw + xRandom;
				plr->pitch = 69;
				plr->bodyYaw = animYaw + xRandom;
				break;
			case 1: // Smooth
				plr->yawUnused1 = animYaw + xRandom;
				plr->pitch = angle.x + yRandom;
				break;
			}

			// Strafe
			if (mode.getSelectedValue() <= 2 && strafe) plr->setRot(angle);
		}
	}
}

void Killaura::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (g_Data.canUseMoveKeys()) {
		if (hold && !g_Data.isLeftClickDown())
			return;

		sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (packet->isInstanceOf<C_MovePlayerPacket>() && rotations.getSelectedValue() != 3 && !targetList.empty()) {
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(targetList[0]->eyePos0);
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);

			movePacket->pitch = angle.x + yRandom;
			movePacket->headYaw = animYaw + xRandom;
			movePacket->yaw = animYaw + xRandom;
		}
	}
}

void Killaura::onLevelRender() {
	auto targetStrafe = moduleMgr->getModule<TargetStrafe>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr || targetStrafe->isEnabled() || !visualize) return;

	static float n = 0;
	static float anim = 0;
	if (g_Data.canUseMoveKeys() && !targetList.empty()) {
		if (hold && !g_Data.isLeftClickDown())
			return;
		if (mode.getSelectedValue() == 2) sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (!targetList.empty()) {
			DrawUtils::setColor(1, 1, 1, 0.9f);

			vec3_t permutations[699];
			for (int i = 0; i < 699; i++) {
				permutations[i] = { sinf((i * 30.f) / (180 / PI)), -0.9f, cosf((i * 30.f) / (180 / PI)) };
			}
			vec3_t permutations2[699];
			n++;
			if (n == 12240)
				n = 0;
			for (int i = 0; i < 699; i++) {
				permutations2[i] = { sinf((i * 30.f) / (180 / PI)), sinf((i * 30.f) / (180 / PI)) ,cosf((i * 30.f) / (180 / PI)) };
			}

			const float coolAnim = 0.9f + 0.9f * sin((anim / 60) * PI * 1);

			vec3_t* start = targetList[0]->getPosOld();
			vec3_t* end = targetList[0]->getPos();

			auto te = DrawUtils::getLerpTime();
			vec3_t pos = start->lerp(end, te);

			auto yPos = pos.y;
			yPos -= 1.6f;
			yPos += coolAnim;

			vector<vec3_t> posList;
			posList.reserve(56);
			for (auto& perm : permutations) {
				vec3_t curPos(pos.x, yPos, pos.z);
				posList.push_back(curPos.add(perm));
			}
			DrawUtils::drawLineStrip3D(posList, 5);
			
			//Draw Sims Esp
			/*vector<vec3_t> posList2;
			posList2.clear();
			// Iterate through phi, theta then convert r,theta,phi to XYZ
			for (double phi = 0.; phi < 2 * PI; phi += PI / 100.) // Azimuth [0, 2PI]
			{
				for (double theta = 0.; theta < PI; theta += PI / 100.) // Elevation [0, PI]
				{
					vec3_t point;
					point.x = 0.2 * cos(phi) * sin(theta);
					point.y = 0.2 * sin(phi) * sin(theta);
					point.z = 0.2 * cos(theta);
					vec3_t curPos = targetList[0]->eyePos0;
					curPos.y += 0.5f;
					posList2.push_back(curPos.add(point));
				}
			}
			DrawUtils::setColor(0.1f,0.9f,0.1f,255);
			DrawUtils::drawLineStrip3D(posList2, 4);*/
		}
	}
}

void Killaura::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetListEmpty = true;
	targetList.clear();
}