#include "TargetStrafe.h"

TargetStrafe::TargetStrafe() : IModule(0x0, Category::COMBAT, "Hop around like a bunny!") {
	registerBoolSetting("Mobs", &isMobAura, isMobAura);
	registerBoolSetting("Jump", &jump, jump);
	registerBoolSetting("Hive", &hive, hive);
	registerFloatSetting("Strafe Range", &Srange, Srange, 1.f, 7.f);
	registerFloatSetting("range", &range, range, 3.f, 20.f);
	registerFloatSetting("Speed", &speed, speed, 0.1f, 1.5f);
}

TargetStrafe::~TargetStrafe() {
}

const char* TargetStrafe::getModuleName() {
	return ("TargetStrafe");
}

struct CompareTargetEnArray {
	bool operator()(C_Entity* lhs, C_Entity* rhs) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

static std::vector<C_Entity*> targetGist;
void findGist(C_Entity* currentEntity, bool isRegularEntity) {
	std::sort(targetGist.begin(), targetGist.end(), CompareTargetEnArray());
	static auto killauraMod = moduleMgr->getModule<TargetStrafe>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

	if (killauraMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 319)
			return;
		if (currentEntity->width <= 0.01f || currentEntity->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;
		if (currentEntity->getEntityTypeId() == 68)  // XP Bottle
			return;
		if (currentEntity->getEntityTypeId() == 66)  // Falling Block
			return;
		if (currentEntity->getEntityTypeId() == 69)  // XP
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < killauraMod->range)
		targetGist.push_back(currentEntity);
}

void TargetStrafe::onMove(C_MoveInputHandler* input) {
	targetGist.clear();
	g_Data.forEachEntity(findGist);

	if (!targetGist.empty()) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		if (player->isInLava() == 1 || player->isInWater() == 1)
			return;

		if (player->isSneaking())
			return;

		vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (player->onGround && pressed && jump)
			player->jumpFromGround();

		if (player->onGround && hive) {
			float calcYaw = (player->yaw + 90) * (PI / 180);
			vec3 moveVec;
			float c = cos(calcYaw);
			float s = sin(calcYaw);
			moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
			moveVec.x = moveVec2d.x * speed;
			moveVec.y = player->velocity.y;
			moveVec.z = moveVec2d.y * speed;
			if (pressed) player->lerpMotion(moveVec);
		} else if (!hive) {
			float calcYaw = (player->yaw + 90) * (PI / 180);
			vec3 moveVec;
			float c = cos(calcYaw);
			float s = sin(calcYaw);
			moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
			moveVec.x = moveVec2d.x * speed;
			moveVec.y = player->velocity.y;
			moveVec.z = moveVec2d.y * speed;
			if (pressed) player->lerpMotion(moveVec);
		}
	}
}

void TargetStrafe::onLevelRender() {
	if (!targetGist.empty()) {
		std::sort(targetGist.begin(), targetGist.end(), CompareTargetEnArray());
		for (auto& i : targetGist) {
			float dist = (*i->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
			if (dist < Srange) {
				g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
				g_Data.getClientInstance()->getLocalPlayer()->setSprinting(false);
			}
		}
	}
}

void TargetStrafe::onTick(C_GameMode* gm) {
	std::sort(targetGist.begin(), targetGist.end(), CompareTargetEnArray());
	targetListB = targetGist.empty();
	if (g_Data.getClientInstance()->isInGame()) {
		targetGist.clear();
		g_Data.forEachEntity(findGist);
		if (!targetGist.empty()) {
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetGist[0]->getPos()).normAngles();
			player->yawUnused2 = angle.x;
			player->yawUnused2 = angle.y;
			player->bodyYaw = angle.x;
			player->bodyYaw = angle.y;
			//g_Data.getClientInstance()->getMoveTurnInput()->left = true;
			g_Data.getClientInstance()->getMoveTurnInput()->forward = true;
			g_Data.getClientInstance()->getLocalPlayer()->setSprinting(true);
			hoe = g_Data.getLocalPlayer()->getPos()->CalcAngle(*targetGist[0]->getPos());
		}
	}
}

void TargetStrafe::onDisable() {
	g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
	//g_Data.getClientInstance()->getMoveTurnInput()->left = false;
	g_Data.getClientInstance()->getLocalPlayer()->setSprinting(false);
}