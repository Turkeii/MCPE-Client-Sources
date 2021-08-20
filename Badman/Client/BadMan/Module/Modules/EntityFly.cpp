#include "EntityFly.h"

EntityFly::EntityFly() : IModule(0x0, Category::MOVEMENT, "Fly with certain entites") {
	registerFloatSetting("speed", &this->speed, this->speed, 0.5f, 2.f);
}

EntityFly::~EntityFly() {
}

const char* EntityFly::getModuleName() {
	return ("EntityFly");
}

static std::vector<C_Entity*> targetList;

void findEntity06(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 23 && currentEntity->getEntityTypeId() != 24 && currentEntity->getEntityTypeId() != 25)
		return;
	//horse = 23
	//donkey = 24
	//mule = 25
	//skeleton horse = 26

	int range = 4;
	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < range) {
		targetList.push_back(currentEntity);
	}
}

void EntityFly::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();
	g_Data.forEachEntity(findEntity06);

	if (!targetList.empty()) {
		float yaw = gm->player->yaw;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

		//Vertical
		glideModEffective = glideMod;
		if (GameData::isKeyDown(VK_SPACE))
			glideModEffective += speed;
		if (GameData::isKeyDown(VK_CONTROL))
			glideModEffective -= speed;

		targetList[0]->velocity.y = glideModEffective;

		//Horizontal
		bool keyPressed = false;
		if (GameData::canUseMoveKeys()) {
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
			float calcYaw = (yaw + 90) * (PI / 180);
			float calcPitch = (gm->player->pitch) * -(PI / 180);
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * speed;
			moveVec.y = glideModEffective;
			moveVec.z = sin(calcYaw) * speed;
			if (keyPressed) {
				targetList[0]->lerpMotion(moveVec);
				//targetList[0]->velocity = moveVec; //does the same thing but may be a bool in the future 
				keyPressed = false;
			}
		}
	}
}
