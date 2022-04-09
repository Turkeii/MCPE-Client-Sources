#include "EntityFly.h"

EntityFly::EntityFly() : IModule(0x0, Category::ENTITY, "Fly will riding entities, use up and down arrows to move!") {
	registerFloatSetting("Horizontal Speed", &speed2, speed2, 0.01f, 10.00f);       //allows you to ajust your speed.
	registerFloatSetting("Vertical Speed", &upspeed, upspeed, 0.50f, 10.00f);  //allows you to ajust your speed
}

EntityFly::~EntityFly() {
}

const char* EntityFly::getModuleName() {
	return ("EntityFly");
}
static std::vector<C_Entity*> targetJoe;
void findJoe(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90 && currentEntity->getEntityTypeId() != 2186010 && currentEntity->getEntityTypeId() != 2118423 && currentEntity->getEntityTypeId() != 4876 && currentEntity->getEntityTypeId() != 2118424)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetJoe.push_back(currentEntity);
	}
}

void EntityFly::onTick(C_GameMode* gm) {
	targetJoe.clear();
	g_Data.forEachEntity(findJoe);

	if (!targetJoe.empty()) {
		//keeps you in the air
		glideModEffective = glideMod;
		targetJoe[0]->velocity.y = glideModEffective;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

		if (g_Data.canUseMoveKeys() && !targetJoe.empty()) {
			if (GameData::isKeyDown(VK_DOWN)) {
				targetJoe[0]->velocity.y -= upspeed;
			}
			if (GameData::isKeyDown(VK_UP)) {
				targetJoe[0]->velocity.y += upspeed;
			}
		}
	}
}

void EntityFly::onMove(C_MoveInputHandler* input) {
	targetJoe.clear();
	g_Data.forEachEntity(findJoe);

	if (!targetJoe.empty()) {
		float yaw = targetJoe[0]->yaw;
		if (targetJoe[0] && targetJoe[0] == nullptr) return;
		if (targetJoe[0]->isSneaking())
			return;
		vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (input->right) {
			yaw += 90.f;
			if (input->forward)
				yaw -= 20.f;

			else if (input->backward)
				yaw += 45.f;
		}
		if (input->left) {
			yaw -= 90.f;
			if (input->forward)
				yaw += 45.f;
			else if (input->backward)
				yaw -= 45.f;
		}

		if (input->backward && !input->left && !input->right)
			yaw += 180.f;

		float calcYaw = (yaw + 90.f) * (PI / 180.f);
		vec3 moveVec;
		moveVec.x = cos(calcYaw) * speed2;
		moveVec.y = targetJoe[0]->velocity.y;
		moveVec.z = sin(calcYaw) * speed2;
		if (pressed) targetJoe[0]->lerpMotion(moveVec);
		if (!pressed) {
			targetJoe[0]->velocity.x = 0;
			targetJoe[0]->velocity.z = 0;
		}
	}
}