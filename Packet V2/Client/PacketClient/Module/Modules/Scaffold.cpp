#include "Scaffold.h"

#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Module/ModuleManager.h"

Scaffold::Scaffold() : IModule(0, Category::PLAYER, "BasicallyBly") {
	//registerBoolSetting("Downwards", &staircase, staircase);
	registerBoolSetting("Rotations", &rotations, rotations);
	registerBoolSetting("AirPlace", &airplace, airplace);
	registerBoolSetting("Sprint", &sprint, sprint);
	registerBoolSetting("Tower", &tower, tower);
	registerBoolSetting("LockY", &lockY, lockY);
	registerBoolSetting("Spoof", &spoof, spoof);
	registerIntSetting("Timer", &timer, timer, 20, 80);
	registerIntSetting("Extend", &expand, expand, 0, 7);
}

Scaffold::~Scaffold() {
}

const char* Scaffold::getRawModuleName() {
	return "Scaffold";
}

const char* Scaffold::getModuleName() {
	return "Scaffold";
}

void Scaffold::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	prevSlot = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
	auto player = g_Data.getLocalPlayer();
}

void Scaffold::onTick(C_GameMode* gm) {
	isOnHive = strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "geo.hivebedrock.network") == 0;
	if (g_Data.getLocalPlayer() == nullptr || !g_Data.canUseMoveKeys())
		return;

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(timer);
	auto speedMod = moduleMgr->getModule<Speed>();

	// Select Block
	static bool restored = false;
	if (!selectBlock()) {
		if (!restored) {
			restored = true;
			g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = prevSlot;
			if (restored == true) {
				auto warning = g_Data.addNotification("Scaffold:", "Scaffold: No blocks found");
				warning->duration = 17;
				setEnabled(false);
			}
		}
		return;
	}
	restored = false;

	isHoldingSpace = GameData::isKeyDown(*input->spaceBarKey);
	isSneaking = GameData::isKeyDown(*input->sneakKey);

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock()))  // Block in hand?
		return;

	if (!sprint) {
		auto sprint = moduleMgr->getModule<Sprint>();
		gm->player->setSprinting(false);
		sprint->useSprint = false;
	}

	// Adjustment by velocity
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	vec3_t vel = g_Data.getLocalPlayer()->velocity;
	vel = vel.normalize();  // Only use values from 0 - 1

	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block 1 block below the player
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5;

	vec3_t blockBelow15 = g_Data.getLocalPlayer()->eyePos0;  // Block 1 block below the player
	blockBelow15.y -= g_Data.getLocalPlayer()->height;
	blockBelow15.y -= 1.5f;

	vec3_t blockBelow2 = g_Data.getLocalPlayer()->eyePos0;  // Block 2 blocks below the player
	blockBelow2.y -= g_Data.getLocalPlayer()->height;
	blockBelow2.y -= 2.0f;

	if (extendOut) {
		float cal = (gm->player->yaw + 90) * (PI / 180);

		if (tower && speed <= 0.05) {
			if (!isHoldingSpace) {
				blockBelow.x = blockBelow.x += cos(cal) * expand;  // Block(s) ahead the player X
				blockBelow.z = blockBelow.z += sin(cal) * expand;  // Block(s) ahead the player Z
			}
		} else {
			blockBelow.x = blockBelow.x += cos(cal) * expand;  // Block(s) ahead the player X
			blockBelow.z = blockBelow.z += sin(cal) * expand;  // Block(s) ahead the player Z
		}
		if (!tryScaffold(blockBelow)) {
			if (speed > 0.05f) {  // Are we actually walking?
				blockBelow.z -= vel.z;
				if (!tryScaffold(blockBelow)) {
					blockBelow.x -= vel.x;

					if (!tryScaffold(blockBelow) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelow.z += vel.z;
						blockBelow.x += vel.x;
						tryScaffold(blockBelow);
					}
				}
			}
		}
	}
	if (!tryScaffold(blockBelow)) {
		blockBelow.z -= vel.z * 0.4f;
		if (!tryScaffold(blockBelow)) {
			blockBelow.x -= vel.x * 0.4f;
			if (!tryScaffold(blockBelow) && g_Data.getLocalPlayer()->isSprinting()) {
				blockBelow.z += vel.z;
				blockBelow.x += vel.x;
				tryScaffold(blockBelow);
			}
		}
	}

	/*if (staircase && isSneaking) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		if (!tryScaffold(blockBelow15) && !tryScaffold(blockBelow2)) {
			if (speed > 0.05f) {
				blockBelow15.z -= vel.z;
				blockBelow2.z -= vel.z;
				if (!tryScaffold(blockBelow15) && !tryScaffold(blockBelow2)) {
					blockBelow15.x -= vel.x;
					blockBelow2.x -= vel.x;
					if (!tryScaffold(blockBelow15) && !tryScaffold(blockBelow2) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelow15.z += vel.z;
						blockBelow15.x += vel.x;
						blockBelow2.z += vel.z;
						blockBelow2.x += vel.x;
						tryScaffold(blockBelow15);
						tryScaffold(blockBelow2);
					}
				}
			}
		}
	}*/

	if (spoof) gm->player->getSupplies()->selectedHotbarSlot = prevSlot;

	if (rotations) {
		auto player = g_Data.getLocalPlayer();
		vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;
		blockBelow.y -= g_Data.getLocalPlayer()->height;
		blockBelow.y -= 0.5f;
		if (speed >= 0.05 || isHoldingSpace) {
			vec2_t angleBelow = g_Data.getLocalPlayer()->getPos()->CalcAngle(blockBelow);
			auto rotation = g_Data.getLocalPlayer();
			float prevyaw = rotation->yawUnused1;
			float prevyaw2 = rotation->yaw;
			float prevyaw3 = rotation->yaw2;
			rotation->setRot(angleBelow);
			rotation->yawUnused1 = angleBelow.y;
			rotation->pitch = angleBelow.x;
			rotation->yaw2 = angleBelow.y;
			rotation->yaw = prevyaw2;
			rotation->pitch2 = angleBelow.x;
			useRot = false;
		} else {
			useRot = true;
		}
	}
}

void Scaffold::onMove(C_MoveInputHandler* input) {
	if (g_Data.getLocalPlayer() == nullptr || !g_Data.canUseMoveKeys())
		return;

	C_GameSettingsInput* inpute = g_Data.getClientInstance()->getGameSettingsInput();
	auto clickGUI = moduleMgr->getModule<ClickGuiMod>();

	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	auto player = g_Data.getLocalPlayer();

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if (!selectedItem->isValid() || !(*selectedItem->item)->isBlock())
		return;

	// Tower
	if (tower && isHoldingSpace && !clickGUI->isEnabled() && speed <= 0.05) {
		float trueStop = 1000 - 1 + NULL;
		if (foundBlock) {
			vec2_t movement = {input->forwardMovement, -input->sideMovement};
			bool pressed = movement.magnitude() > 0.f;
			float calcYaw = (player->yaw + 90) * (PI / 180);
			vec3_t moveVec;
			float c = cos(calcYaw);
			float s = sin(calcYaw);

			movement = {movement.x * c - movement.y * s, movement.x * s + movement.y * c};
			player->jumpFromGround();
			moveVec.y = player->velocity.y;
		}
	}
}

bool Scaffold::tryScaffold(vec3_t blockBelow) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	static std::vector<vec3_ti*> checklist;
	blockBelow = blockBelow.floor();
	int i = 0;

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);
		if (lockY) {
			if (!GameData::isKeyDown(*input->spaceBarKey)) {
				if (g_Data.getLocalPlayer()->onGround)
					yLock = blok.y;
				else if (yLock > -1)
					blok.y = yLock;
			}
		}

		if (airplace) {
			g_Data.getCGameMode()->buildBlock(&blok, i);
			return true;
		} else {
			if (checklist.empty()) {
				checklist.push_back(new vec3_ti(0, -1, 0));
				checklist.push_back(new vec3_ti(0, 1, 0));

				checklist.push_back(new vec3_ti(0, 0, -1));
				checklist.push_back(new vec3_ti(0, 0, 1));

				checklist.push_back(new vec3_ti(-1, 0, 0));
				checklist.push_back(new vec3_ti(1, 0, 0));
			}
			foundBlock = false;
			for (auto current : checklist) {
				vec3_ti calc = blok.sub(*current);
				if (!g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy->material->isReplaceable) {
					foundBlock = true;
					blok = calc;
					break;
				}
				i++;
			}
			if (foundBlock) {
				g_Data.getCGameMode()->buildBlock(&blok, i);
				return true;
			}
		}
	}
	return false;
}

void Scaffold::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() == nullptr || !g_Data.canUseMoveKeys())
		return;

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	auto player = g_Data.getLocalPlayer();

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if (!selectedItem->isValid() || selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock())
		return;

	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5f;

	if (speed >= 0.f)
		return;

	if (tower) {
		if (isHoldingSpace && speed == 0) {  // look down
			vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(blockBelow);
			auto weewee = g_Data.getLocalPlayer();
			weewee->setRot(angle);
			vec2_t angleBelow = g_Data.getLocalPlayer()->getPos()->CalcAngle(blockBelow);
			auto rotation = g_Data.getLocalPlayer();
			float prevyaw = rotation->yawUnused1;
			float prevyaw2 = rotation->yaw;
			float prevyaw3 = rotation->yaw2;
			rotation->setRot(angleBelow);
			rotation->yawUnused1 = angleBelow.y;
			rotation->pitch = angleBelow.x;
			rotation->yaw2 = angleBelow.y;
			rotation->yaw = prevyaw2;
			rotation->pitch2 = angleBelow.x;
		}
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
	}
}

bool Scaffold::selectBlock() {
	C_PlayerInventoryProxy* inv = g_Data.getLocalPlayer()->getSupplies();
	for (int i = 0; i < 9; i++) {
		C_Block* block = *(C_Block**)(((char*)&inv->inventory->getItemStack(i)->tag) + 8);
		if (block != nullptr && block->toLegacy()->material->isSolid) {
			inv->selectedHotbarSlot = i;
			return true;
		}
	}
	return false;
}

void Scaffold::onSendPacket(C_Packet* packet) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5f;

	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
		if (g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys()) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			if (rotations && speed >= 0.05 || GameData::isKeyDown(*input->spaceBarKey)) {
				vec2_t angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(blockBelow);
				movePacket->pitch = angle.x;
				movePacket->headYaw = angle.y;
				movePacket->yaw = angle.y;
			}
		}
	}
}

void Scaffold::onDisable() {
	auto sprint = moduleMgr->getModule<Sprint>();
	sprint->useSprint = true;
	useRot = true;
	if (g_Data.getLocalPlayer() == nullptr || !g_Data.canUseMoveKeys())
		return;

	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	//__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	*g_Data.getClientInstance()->minecraft->timer = 20;
	//auto player = g_Data.getLocalPlayer();
	//C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = prevSlot;
}