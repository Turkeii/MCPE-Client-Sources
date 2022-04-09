#include "EntitySpeed.h"

EntitySpeed::EntitySpeed() : IModule(0x0, Category::ENTITY, "Makes rideable entities faster when riding them") {
	registerFloatSetting("Horizontal Speed", &speed2, speed2, 0.01f, 10.00f);       //allows you to ajust your speed.
}

EntitySpeed::~EntitySpeed() {
}

const char* EntitySpeed::getModuleName() {
	return ("EntitySpeed");
}
static std::vector<C_Entity*> targetDeez;
void findDeez(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90 && currentEntity->getEntityTypeId() != 2186010 && currentEntity->getEntityTypeId() != 2118423 && currentEntity->getEntityTypeId() != 4876 && currentEntity->getEntityTypeId() != 2118424)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetDeez.push_back(currentEntity);
	}
}

void EntitySpeed::onTick(C_GameMode* gm) {
	targetDeez.clear();
	g_Data.forEachEntity(findDeez);

	if (!targetDeez.empty()) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

		if (input == nullptr)
			return;

		float speed = speed2;
		float yaw = targetDeez[0]->yaw;

		if (GameData::isKeyDown(*input->spaceBarKey) && targetDeez[0]->onGround)
			targetDeez[0]->jumpFromGround();

		if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->backKey))
			return;
		else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 45.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 45.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 135.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 135.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->forwardKey)) {
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey)) {
			yaw += 180.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 90.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 90.f;
			keyPressed = true;
		}
		if (yaw >= 180)
			yaw -= 360.f;

		float calcYaw = (yaw + 90) * (PI / 180);
		//float calcPitch = (gm->player->pitch) * -(PI / 180);
		vec3 moveVec;
		moveVec.x = cos(calcYaw) * speed;
		moveVec.y = targetDeez[0]->velocity.y;
		moveVec.z = sin(calcYaw) * speed;
		if (keyPressed) {
			targetDeez[0]->lerpMotion(moveVec);
			keyPressed = false;
		}
	}
}