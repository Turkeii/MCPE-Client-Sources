#include "BlockFly.h"

BlockFly::BlockFly() : IModule(0, Category::MOVEMENT, "Block Fly") {
	registerFloatSetting("Speed", &this->speed, this->speed, 0.1f, 0.7f);
	registerIntSetting("Timer Speed", &this->timer, this->timer, 20, 200);
	registerBoolSetting("Timer", &this->time, this->time);
	registerBoolSetting("Damage", &this->dmg, this->dmg);
	registerBoolSetting("Fail Safe", &this->safe, this->safe);
}

BlockFly::~BlockFly() {
}

const char* BlockFly::getModuleName() {
	return ("BlockFly");
}
bool BlockFly::tryScaffold(vec3_t blockBelow) {
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);


		// Find neighbour
		static std::vector<vec3_ti*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}

		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			vec3_ti calc = blok.sub(*current);
			bool Y = ((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable;
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate) {
			g_Data.getCGameMode()->buildBlock(&blok, i, false);

			return true;
		}
	}
	return false;
}
bool BlockFly::tryTower(vec3_t blockBelow) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (input == nullptr)
		return false;

	blockBelow = blockBelow.floor();

	DrawUtils::drawBox(blockBelow, vec3_t(blockBelow).add(1), 0.4f);

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);

		// Find neighbour
		static std::vector<vec3_ti*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}
		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			vec3_ti calc = blok.sub(*current);
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate && GameData::isKeyDown(*input->spaceBarKey)) {
			vec3_t moveVec;
			moveVec.x = g_Data.getLocalPlayer()->velocity.x;
			moveVec.y = motion;
			moveVec.z = g_Data.getLocalPlayer()->velocity.z;
			g_Data.getLocalPlayer()->lerpMotion(moveVec);
			g_Data.getCGameMode()->buildBlock(&blok, i, false);

			return true;
		}
		if (!g_Data.getLocalPlayer()->onGround && GameData::isKeyDown(*input->spaceBarKey)) {
			vec3_t moveVec;
			moveVec.x = g_Data.getLocalPlayer()->velocity.x;
			moveVec.y -= motion;
			moveVec.z = g_Data.getLocalPlayer()->velocity.z;
		}
		if (GameData::isKeyDown(*input->sneakKey)) {
			g_Data.getLocalPlayer()->velocity.y = -motion;
		}
	}
	return false;
}

void BlockFly::onEnable() {
	if (this->dmg) {
		auto player = g_Data.getLocalPlayer();
		player->animateHurt();
	}
}
void BlockFly::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;
	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if (!selectedItem->isValid() || !(*selectedItem->item)->isBlock())  // Block in hand?
		return;

	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5f;

	// Adjustment by velocity
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexy();
	vec3_t vel = g_Data.getLocalPlayer()->velocity;
	vel.normalize();  // Only use values from 0 - 1

	if (!tryTower(blockBelow)) {
		if (speed > 0.05f) {
			blockBelow.z -= vel.z * 0.4f;
			if (!tryTower(blockBelow)) {
				blockBelow.x -= vel.x * 0.4f;
				if (!tryTower(blockBelow) && g_Data.getLocalPlayer()->isSprinting()) {
					blockBelow.z += vel.z;
					blockBelow.x += vel.x;
					tryTower(blockBelow);
				}
			}
		}
	}
}

void BlockFly::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (!player->onGround) {
		g_Data.getGuiData()->displayClientMessageF("[%sBlockFly%s] %sU Cant Start In The Air Idiot%s!", BLUE, WHITE, BLUE, WHITE, configMgr, WHITE);
		if (this->safe) {
			player->velocity.y = 0.00f;
			player->velocity.y = 0.00f;
			player->velocity.y = 0.00f;
			// auto scaff = moduleMgr->getModule<Scaffold>();
			// scaff->setEnabled(true);
		}
		              this->setEnabled(false);
		return;
	}
	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock())) {  // Block in hand?
	clientMessageF("U Have No Blocks In Ur Inventory :/");
	this->setEnabled(false);
	}
	if (pressed) {
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3_t moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = 0.00f;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	}

	if (pressed && counter == 6) {
		// auto blinkMod = moduleMgr->getModule<Scaffold>();
		if (this->Fly) {
			// blinkMod->setEnabled(true);
		}
	}
	if (pressed && counter == 4) {
		// auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		// if (!selectedItem->isValid() || !(*selectedItem->item)->isBlock())  // Block in hand?
		// return;
		player->velocity.x = 0.f;
		player->velocity.y = 0.00f;
		player->velocity.z = 0.f;
		// auto player = g_Data.getLocalPlayer();
		// player->jumpFromGround();
	}
	if (pressed && counter == 5) {
		player->velocity.x = 0.f;
		player->velocity.y = 0.00f;
		player->velocity.z = 0.f;
	}
	if (pressed && counter == 6) {
		player->velocity.x = 0.f;
		player->velocity.y = 0.0f;
		player->velocity.z = 0.f;
	}
	if (pressed && counter == 7) {
		player->velocity.x = 0.f;
		player->velocity.y = -0.01f;
		player->velocity.z = 0.f;
	}
	if (pressed && counter == 8) {
		player->velocity.x = 0.f;
		player->velocity.y = 0.00f;
		player->velocity.z = 0.f;
	}

	if (counter == 11) {
		counter = 0;
	} else {
		counter++;
	}
	if (timer) {
		*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
	} else {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
}
void BlockFly::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock()))  // Block in hand?
		return;

	// Adjustment by velocity
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	vec3_t vel = g_Data.getLocalPlayer()->velocity;
	vel = vel.normalize();  // Only use values from 0 - 1

	vec3_t blockBelow2 = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelow2.y -= g_Data.getLocalPlayer()->height;
	blockBelow2.y -= 0.5f;

	blockBelow2.z -= vel.z * 0.4f;
	if (!tryScaffold(blockBelow2)) {
		blockBelow2.x -= vel.x * 0.4f;
		blockBelow2.z += vel.z;
		blockBelow2.x += vel.x;
		tryScaffold(blockBelow2);
		blockBelow2.z -= vel.z * 0.3f;
		if (!tryScaffold(blockBelow2)) {
			blockBelow2.x -= vel.x * 0.2f;
			blockBelow2.z += vel.z;
			blockBelow2.x += vel.x;
			tryScaffold(blockBelow2);
			blockBelow2.z -= vel.z * 0.1f;
		}
	}

		vec3_t blockBelow32 = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
		blockBelow32.y -= g_Data.getLocalPlayer()->height;
		blockBelow32.y -= 0.5f;

		blockBelow32.z -= vel.z * 0.4f;
		if (!tryScaffold(blockBelow32)) {
			blockBelow32.x -= vel.x * 0.4f;
			blockBelow32.z += vel.z;
			blockBelow32.x += vel.x;
			tryScaffold(blockBelow32);
			blockBelow32.z -= vel.z * 0.3f;
			if (!tryScaffold(blockBelow32)) {
				blockBelow32.x -= vel.x * 0.2f;
				blockBelow32.z += vel.z;
				blockBelow32.x += vel.x;
				tryScaffold(blockBelow32);
				blockBelow32.z -= vel.z * 0.1f;
			}
		}
	
}

void BlockFly::onDisable() {
	auto player = g_Data.getLocalPlayer();
	
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}