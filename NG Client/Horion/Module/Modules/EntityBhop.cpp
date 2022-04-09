#include "EntityBhop.h"

EntityBhop::EntityBhop() : IModule(0x0, Category::ENTITY, "so funny") {
	registerFloatSetting("Speed", &speed, speed, 0.1f, 1.5f);
	registerBoolSetting("Lowhop", &lowhop, lowhop);
	registerFloatSetting("Lowhop UpValue", &upVal, upVal, 0.05f, 0.50f);
}

EntityBhop::~EntityBhop() {
}

const char* EntityBhop::getModuleName() {
	return ("EntityBhop");
}
static std::vector<C_Entity*> targetKid;
void findKid(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90 && currentEntity->getEntityTypeId() != 2186010 && currentEntity->getEntityTypeId() != 2118423 && currentEntity->getEntityTypeId() != 4876 && currentEntity->getEntityTypeId() != 2118424)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetKid.push_back(currentEntity);
	}
}
void EntityBhop::onMove(C_MoveInputHandler* input) {
	targetKid.clear();
	g_Data.forEachEntity(findKid);

	if (!targetKid.empty()) {
		auto player = targetKid[0];
		if (player == nullptr) return;

		if (player->isInLava() == 1 || player->isInWater() == 1)
			return;

		if (player->isSneaking())
			return;

		vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (player->onGround && pressed)
			player->jumpFromGround();

		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3 moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
		if (player->onGround && pressed && !input->isJumping && lowhop)
			player->velocity.y -= upVal;
	}
}