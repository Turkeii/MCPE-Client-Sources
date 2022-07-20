#include "BoatSpeed.h"

BoatSpeed::BoatSpeed() : IModule(0, Category::MOVEMENT, "Increases your speed within boats") {
	this->registerFloatSetting("Speed", &this->speed, this->speed, 1.f, 5.f);
}

BoatSpeed::~BoatSpeed() {
}

const char* BoatSpeed::getModuleName() {
	return ("BoatSpeed");
}

static std::vector<C_Entity*> targetList;

void findEntity03(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90)//if something isnt a boat then it doesnt prok
		return;

	int range = 3;
	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < range) {
		targetList.push_back(currentEntity);
	}
}

void BoatSpeed::onTick(C_GameMode* gm) {
	targetList.clear();
	g_Data.forEachEntity(findEntity03);

	if (!targetList.empty()) {
		float yaw = gm->player->yaw;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
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
			moveVec.y = targetList[0]->velocity.y;
			moveVec.z = sin(calcYaw) * speed;
			if (keyPressed) {
				targetList[0]->lerpMotion(moveVec);
				keyPressed = false;
			}
		}
	}
}
