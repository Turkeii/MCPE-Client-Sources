#include "Glide.h"

#include "../../Module/ModuleManager.h"

Glide::Glide() : IModule(0, Category::MOVEMENT, "FlightModule") {
	this->registerBoolSetting("Vanilla", &this->vanillaMode, this->vanillaMode);
	this->registerBoolSetting("Boost", &this->boostMode, this->boostMode);
	registerFloatSetting("Speed", &this->speed, this->speed, 0.7f, 4.f);
	this->registerFloatSetting("value", &this->glideMod, this->glideMod, -1.f, 0.00);
}

Glide::~Glide() {
}

const char* Glide::getModuleName() {
	if (isEnabled()) {
		static char modName[30];  //Hello
		sprintf_s(modName, 30, "Flight", glideModEffective);
		return modName;
	} else
		return ("Flight");
}

const char* Glide::getRawModuleName() {
	return "Flight";
}

void Glide::onEnable() {
	auto player = g_Data.getLocalPlayer();
}

bool Glide::isFlashMode() {
	if (jetpackMode) {
		return true;
	}
	if (!jetpackMode) {
		return false;
	}
}

void Glide::onTick(C_GameMode* gm) {
	auto scaffoldMod = moduleMgr->getModule<Scaffold>();
	if (scaffoldMod->isEnabled()) {
		scaffoldMod->setEnabled(false);
		auto box = g_Data.addInfoBox("Flight", "Scaffold was disabled to prevent flags/errors");
		box->closeTimer = 13;
	}
	if (onkeydisableMode) {
		auto targetstrafeMod = moduleMgr->getModule<TargetStrafe>();
		{
			if (targetstrafeMod->spacekeyMode = true)
				;
			targetstrafeMod->spacekeyMode = false;
		}
	}
	if (!onkeydisableMode) {
		auto targetstrafeMod = moduleMgr->getModule<TargetStrafe>();
		{
			targetstrafeMod->spacekeyMode = true;
		}
	}
	if (jetpackMode) {
		float calcYaw = (gm->player->yaw + 90) * (PI / 180);
		float calcPitch = (gm->player->pitch) * -(PI / 180);

		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * speed;
		moveVec.y = sin(calcPitch) * speed;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * speed;

		gm->player->lerpMotion(moveVec);
	}
	if (boostMode) {
		auto player = g_Data.getLocalPlayer();
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		float yaw = player->yaw;
		if (input->forwardKey && input->backKey && input->rightKey && input->leftKey) {
			gm->player->velocity = vec3_t(0, 0, 0);
		}
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += 0.0f;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= 0.0f;
	}
	glideModEffective = glideMod;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (boostMode && GameData::isKeyDown(*input->sneakKey)) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	}

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += 0.0f;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= 0.0f;
	}
	if (vanillaMode && GameData::isKeyDown(*input->sneakKey)) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	}
	if (vanillaMode) {
		auto player = g_Data.getLocalPlayer();
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		float yaw = player->yaw;
		if (input->forwardKey && input->backKey && input->rightKey && input->leftKey) {
			gm->player->velocity = vec3_t(0, 0, 0);
		}
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += speed;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= speed;
	}
	gm->player->velocity.y = glideModEffective;
	if (hiveMode && GameData::isKeyDown(*input->sneakKey)) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	}
	if (hiveMode) {
		*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
		glideMod = -0.01;
		boostMode = false;
		vanillaMode = false;
		strafeMode = false;
	}
	if (!hiveMode) {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	auto bhopMod = moduleMgr->getModule<Bhop>();
	if (bhopMod->isEnabled()) {
		bhopMod->setEnabled(false);
		auto box = g_Data.addInfoBox("Flight", "Speed was disabled to prevent flags/errors");
		box->closeTimer = 13;
	}
}

void Glide::onMove(C_MoveInputHandler* input) {
	if (hiveMode) {
		auto player = g_Data.getLocalPlayer();
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (player->onGround && pressed)
			player->jumpFromGround();
	}
	if (boostMode) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		if (player->isInLava() == 1 || player->isInWater() == 1)
			return;

		if (player->isSneaking())
			return;

		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (player->onGround && pressed)
			player->jumpFromGround();

		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	}
	if (vanillaMode) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	}
}

void Glide::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	auto player = g_Data.getLocalPlayer();
	player->velocity.x = 0.f;
	player->velocity.y = 0.f;
	player->velocity.z = 0.f;
	if (hiveMode) {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	auto targetstrafeMod = moduleMgr->getModule<TargetStrafe>();
	{
		targetstrafeMod->packetMode = false;
		targetstrafeMod->spacekeyMode = true;
	}
}