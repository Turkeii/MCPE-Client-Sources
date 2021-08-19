#include "HiveFly.h"

#include "../../Module/ModuleManager.h"

HiveFly::HiveFly() : IModule(0, Category::MOVEMENT, "Turkey go falling off cliff wee!1!1!!") {
	//registerFloatSetting("Little SHIT", &this->Test, this->Test, 1.f, 50.f);
	//registerBoolSetting("TimerBoost", &this->timerMode, this->timerMode);
	registerBoolSetting("TimerBoost", &this->timerMode, this->timerMode);
	//registerBoolSetting("Strafe", &this->strafeMode, this->strafeMode);
	registerBoolSetting("Boost", &this->boostMode, this->boostMode);
	//registerBoolSetting("Old", &this->oldMode, this->oldMode);
	registerFloatSetting("Value", &this->speed2, this->speed2, -0.02f, 0.f);
	registerFloatSetting("Speed", &this->speedA, this->speedA, 0.10f, 1.f);
	registerIntSetting("Boost", &this->timer, this->timer, 10.f, 500.f);
}

HiveFly::~HiveFly() {
}

const char* HiveFly::getModuleName() {
	return "HiveFly";
}
void HiveFly::onEnable() {
	auto stepMod = moduleMgr->getModule<Step>();
	{
		auto player = g_Data.getLocalPlayer();
		player->animateHurt();
		stepMod->height = 0.5625f;
		if (boostMode) {
			*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
		}
		if (damageMode) {
			auto hfMod = moduleMgr->getModule<HiveFly>();
			if (hfMod->isEnabled()) {
				hfMod->setEnabled(false);
			}
			{
				vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

				vec3_t pos;
				pos.x = 0.f + pPos.x;
				pos.y = 0.f + pPos.y;
				pos.z = 0.f + pPos.z;

				g_Data.getLocalPlayer()->setPos(pos);
				*g_Data.getClientInstance()->minecraft->timer = 6000.f;
			}
			auto scaffoldMod = moduleMgr->getModule<Scaffold>();
			if (scaffoldMod->isEnabled()) {
				scaffoldMod->setEnabled(false);
			}
			auto bhopMod = moduleMgr->getModule<Bhop>();
			if (bhopMod->isEnabled()) {
				bhopMod->setEnabled(false);
			}
			auto player = g_Data.getLocalPlayer();
		}
		if (oldMode) {
			vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

			vec3_t pos;
			pos.x = 0.f + pPos.x;
			pos.y = 0.f + pPos.y;
			pos.z = 0.f + pPos.z;

			g_Data.getLocalPlayer()->setPos(pos);
		}
	}
}

bool HiveFly::isFlashMode() {
	return false;
}

void HiveFly::onTick(C_GameMode* gm) {
	if (counter == 5) {
		counter = 0;
	} else {
		counter++;
	}
	if (!timerMode) {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	if (!blinkMode) {
		auto blinkMod = moduleMgr->getModule<Blink>();
		blinkMod->setEnabled(false);
	}
	if (blinkMode) {
		testTimer++;
		if (testTimer == 8) {
			auto blinkMod = moduleMgr->getModule<Blink>();
			blinkMod->setEnabled(false);
		}
		if (testTimer >= 9) {
			auto blinkMod = moduleMgr->getModule<Blink>();
			blinkMod->setEnabled(true);
			testTimer = 0;
		}
		if (testTimer <= 7 || testTimer >= 9) {
			auto blinkMod = moduleMgr->getModule<Blink>();
			blinkMod->setEnabled(true);
		}
	}
	if (timerMode) {
		*g_Data.getClientInstance()->minecraft->timer = 25.4124367756534f;  // Timer 1
	}
	if (strafeMode) {
	}
	if (!strafeMode) {
	}
	auto player = g_Data.getLocalPlayer();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	float yaw = player->yaw;
	if (counter >= 0) {
		gm->player->velocity = vec3_t(0, 0, 0);
	}
	if (counter == 1) {
		player->velocity.y = speed2;
		if (timerMode)
			*g_Data.getClientInstance()->minecraft->timer = 26.23446256676f;  // Timer 2
	}
	if (blinkMode) {
		*g_Data.getClientInstance()->minecraft->timer = 33.246256676f;  // Timer 2 Blink
	}
	auto scaffoldMod = moduleMgr->getModule<Scaffold>();
	if (scaffoldMod->isEnabled()) {
		scaffoldMod->setEnabled(false);
	}
	auto bhopMod = moduleMgr->getModule<Bhop>();
	if (bhopMod->isEnabled()) {
		bhopMod->setEnabled(false);
	}
	if (timerMode) {
		//*g_Data.getClientInstance()->minecraft->timer = 20.f;
		auto dmgMod = moduleMgr->getModule<TestModule>();
		if (dmgMod->isEnabled()) {
			dmgMod->setEnabled(false);
		}
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	}
	if (oldMode && GameData::isKeyDown(*input->sneakKey)) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	}
	if (oldMode) {
		glideModEffective = glideMod;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

		if (g_Data.canUseMoveKeys()) {
			if (GameData::isKeyDown(*input->spaceBarKey))
				glideModEffective += 0.f;
			if (GameData::isKeyDown(*input->sneakKey))
				glideModEffective -= 0.f;
		}
		gm->player->velocity.y = glideModEffective;
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
		auto hfMod = moduleMgr->getModule<HiveFly>();
		{
			//hfMod->timerMode = false;
			hfMod->boostMode = false;
		}
	}
	if (!oldMode) {
		//*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
}

void HiveFly::onMove(C_MoveInputHandler* input) {
	if (boostMode) {
		auto player = g_Data.getLocalPlayer();
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (player->onGround && pressed)
			player->jumpFromGround();
	}
	auto player = g_Data.getLocalPlayer();
	float yaw = player->yaw;
	if (player == nullptr) return;
	if (player->isSneaking())
		return;
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (blinkMode) {  // Blink Up
		if (input->isJumping) {
			player->velocity.y += 0.5f;
			player->fallDistance = 0.f;
		}
	}
	if (input->isJumping && counter == 5) {
		player->velocity.y += 0.000000000001f;
		player->fallDistance = 0.f;
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	if (input->isSneakDown && counter == 5) {
		player->velocity.y -= 0.000000000001f;
		player->fallDistance = 0.f;
		*g_Data.getClientInstance()->minecraft->timer = 4.f;
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	if (blinkMode) {  // Blink Down
		if (input->isSneakDown) {
			player->velocity.y -= 0.5f;
			player->fallDistance = 0.f;
		}
	}
	if (input->right) {
		yaw += 90.f;
		*g_Data.getClientInstance()->minecraft->timer = 18.f;
		if (input->forward)
			yaw -= 45.f;
		else if (input->backward)
			yaw += 45.f;
		*g_Data.getClientInstance()->minecraft->timer = 18.f;
	}
	if (input->left) {
		yaw -= 90.f;
		*g_Data.getClientInstance()->minecraft->timer = 18.f;
		if (input->forward)
			yaw += 45.f;
		else if (input->backward)
			yaw -= 45.f;
	}
	if (input->backward && !input->left && !input->right)
		yaw += 180.f;
	if (pressed) {
		float calcYaw = (yaw + 90.f) * (PI / 180.f);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedA;  // 0.55 - Default Value
		moveVec.y = player->velocity.y;
		moveVec.z = sin(calcYaw) * speedA;  // 0.55 - Default Value
		if (pressed) player->lerpMotion(moveVec);
	}
	if (pressed && blinkMode) {
		float calcYaw = (yaw + 90.f) * (PI / 180.f);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * 0.55f;  // Blink Value
		moveVec.y = player->velocity.y;
		moveVec.z = sin(calcYaw) * 0.55f;  // Blink Value
		if (pressed) player->lerpMotion(moveVec);
	}
	/*if (oldMode) {
		auto player = g_Data.getLocalPlayer();
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (player->onGround && pressed)
			player->jumpFromGround();
	}
	*/
}

void HiveFly::onDisable() {
	if (blinkMode) {
		auto blinkMod = moduleMgr->getModule<Blink>();
		blinkMod->setEnabled(false);
	}
	if (strafeMode) {
		auto killauraMod = moduleMgr->getModule<Killaura>();
		killauraMod->cock = false;
		killauraMod->isMulti = true;
		killauraMod->rot = true;
	}
	auto stepMod = moduleMgr->getModule<Step>();
	{
		stepMod->height = 1.5f;

		if (timerMode) {
			*g_Data.getClientInstance()->minecraft->timer = 20.f;
		}
		if (damageMode) {
			*g_Data.getClientInstance()->minecraft->timer = 20.f;
		}
		auto player = g_Data.getLocalPlayer();
		*g_Data.getClientInstance()->minecraft->timer = 10.f;
		if (!player->onGround) {
			player->velocity.x = 0.f;
			player->velocity.z = 0.f;
		}
		if (oldMode) {
			*g_Data.getClientInstance()->minecraft->timer = 20.f;
		}
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
}