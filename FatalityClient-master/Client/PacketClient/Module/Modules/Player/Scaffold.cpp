#include "Scaffold.h"
#include "../pch.h"

uintptr_t HiveRotations1 = Utils::getBase() + 0x8F3895;
uintptr_t HiveRotations2 = Utils::getBase() + 0x8F87C7;

using namespace std;
Scaffold::Scaffold() : IModule(0, Category::PLAYER, "Places blocks under you") {
	registerEnumSetting("Rotations", &rotations, 0);
	rotations.addEntry("(Normal)", 0);
	rotations.addEntry("(Flareon)", 1);
	rotations.addEntry("(Down)", 2);
	rotations.addEntry("(Back)", 3);
	rotations.addEntry("(Silent)", 4);
	rotations.addEntry("(None)", 5);
	registerEnumSetting("Tower", &tower, 0);
	tower.addEntry("Vanilla", 0);
	tower.addEntry("Hive", 1);
	tower.addEntry("Clip", 2);
	tower.addEntry("None", 3);
	registerEnumSetting("Down", &downwards, 0);
	downwards.addEntry("Vanilla", 0);
	downwards.addEntry("None", 1);
	registerBoolSetting("BlockCount", &blockCount, blockCount);
	registerBoolSetting("Sprint", &sprint, sprint);
	registerBoolSetting("Spoof", &spoof, spoof);
	registerBoolSetting("AutoJump", &autoJump, autoJump);
	registerBoolSetting("LockY", &lockY, lockY);
	registerBoolSetting("Swing", &swing, swing);
	registerIntSetting("TowerTimer", &towerTimer, towerTimer, 20, 60);
	registerIntSetting("Timer", &timer, timer, 20, 60);
	registerFloatSetting("Extend", &extend, extend, 0, 7);
}

const char* Scaffold::getRawModuleName() {
	return "Scaffold";
}

const char* Scaffold::getModuleName() {
	if (rotations.getSelectedValue() <= 4) name = string("Scaffold ") + string(GRAY) + rotations.GetEntry(rotations.getSelectedValue()).GetName();
	else name = string("Scaffold");
	return name.c_str();
}

bool Scaffold::isBlockReplacable(vec3_t blockPos) {
	return g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockPos.floor()))->blockLegacy->material->isReplaceable;
}

void Scaffold::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	blockBelowY = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelowY.y -= g_Data.getLocalPlayer()->height;
	blockBelowY.y -= 0.5f;
	blockBelowY = blockBelowY.floor();

	C_PlayerInventoryProxy* supplies = player->getSupplies();
	slot = supplies->selectedHotbarSlot;
}

void Scaffold::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto sprintMod = moduleMgr->getModule<Sprint>();
	auto speed = moduleMgr->getModule<Speed>();

	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	g_Data.getClientInstance()->minecraft->setTimerSpeed(timer);
	jumping = GameData::isKeyDown(*input->spaceBarKey);
	sneaking = GameData::isKeyDown(*input->sneakKey);

	// Select
	static bool restored = false;
	if (!selectBlock()) {
		if (!restored) restored = true;
		else {
			//auto warning = g_Data.addNotification("Scaffold", "No Blocks Found"); warning->duration = 3;
			setEnabled(false);
		}
		return;
	}
	restored = false;

	// Build Blocks
	vec3_t vel = g_Data.getLocalPlayer()->velocity; vel = vel.normalize();
	float velocityxz = g_Data.getLocalPlayer()->velocity.magnitudexz();
	float cal = (player->yaw + 90) * (PI / 180);

	vec3_t blockBelow;
	if (lockY) {
		blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
		blockBelow.y = blockBelowY.y;
	}
	else {
		blockBelow = player->eyePos0;  // Block below the player
		blockBelow.y -= player->height;
		blockBelow.y -= 0.5f;
	}
	if(autoJump) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();

		if (player->onGround) player->jumpFromGround();
	}
	vec3_t blockBelowPredict = player->eyePos0;  // Block below the player
	blockBelowPredict.y -= player->height;
	blockBelowPredict.y -= 0.5f;

	currExtend = extend;

	if (sneaking && downwards.getSelectedValue() == 0) {
		vec3_t blockBelow15 = player->eyePos0;  // Block 1 block below the player
		blockBelow15.y -= player->height;
		blockBelow15.y -= 1.5f;
		blockBelowY = blockBelow15;
		vec3_t blockBelow2 = g_Data.getLocalPlayer()->eyePos0;  // Block 2 blocks below the player
		blockBelow2.y -= g_Data.getLocalPlayer()->height;
		blockBelow2.y -= 2.0f;
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		blockBelow.x = blockBelow.x += cos(cal) * 0.5f; blockBelow.z = blockBelow.z += sin(cal) * 0.5f;
		if (!buildBlock(blockBelow15) && !buildBlock(blockBelow2)) {
			if (velocityxz > 0.f) {
				blockBelow15.z -= vel.z * 0.4f;
				blockBelow15.z -= vel.z * 0.4f;
				if (!buildBlock(blockBelow15) && !buildBlock(blockBelow2)) {
					blockBelow15.x -= vel.x * 0.4f;
					blockBelow2.x -= vel.x * 0.4f;
					if (!buildBlock(blockBelow15) && !buildBlock(blockBelow2) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelow15.z += vel.z;
						blockBelow15.x += vel.x;
						blockBelow2.z += vel.z;
						blockBelow2.x += vel.x;
						buildBlock(blockBelow15);
						buildBlock(blockBelow2);
					}
				}
			}
		}
	} else {
		if (!jumping && velocityxz >= 0.01) { blockBelow.x += vel.x * currExtend; blockBelow.z += vel.z * currExtend; }


		if (isBlockReplacable(blockBelow)) predictBlock(blockBelow);
		else if (!buildBlock(blockBelow)) {
			if (velocityxz > 0.f) {  // Are we actually walking?
				blockBelow.x -= vel.x;
				blockBelow.z -= vel.z;
				if (!buildBlock(blockBelow) && g_Data.getLocalPlayer()->isSprinting()) {
					blockBelow.x += vel.x;
					blockBelow.z += vel.z;
					buildBlock(blockBelow);
				}
			}
		}
	}

	if (!sprint) { gm->player->setSprinting(false); sprintMod->useSprint = false; }
	if (spoof) supplies->selectedHotbarSlot = slot;

	// Hive Bypass
	if (rotations.getSelectedValue() == 1) { 
		player->pointingStruct->rayHitType = 0;
		Utils::nopBytes((unsigned char*)HiveRotations1, 3);
		Utils::patchBytes((unsigned char*)HiveRotations2, (unsigned char*)"\xC7\x40\x18\x00\x00\x00\x00", 7);
	}
	backPos = vec3_t(player->getPos()->x, player->getPos()->y - 1, player->getPos()->z);
}

void Scaffold::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	// Math
	vec3_t pos = *player->getPos();
	float velocityxz = g_Data.getLocalPlayer()->velocity.magnitudexz();
	vec2_t movement = { input->forwardMovement, -input->sideMovement };
	float mathGround = round(pos.y / 0.015625) * 0.015625;
	float calcYaw = (player->yaw + 90) * (PI / 180);
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	vec3_t moveVec;

	if (jumping && foundBlock) {
		//g_Data.getClientInstance()->minecraft->setTimerSpeed(towerTimer);
		switch (tower.getSelectedValue()) {
		case 0: // Vanilla
			moveVec.x = g_Data.getLocalPlayer()->velocity.x;
			moveVec.y = 0.4f;
			moveVec.z = g_Data.getLocalPlayer()->velocity.z;
			g_Data.getLocalPlayer()->lerpMotion(moveVec);
			break;
		case 1: // Hive
			if (velocityxz <= 0.05) {
				g_Data.getClientInstance()->minecraft->setTimerSpeed(145.f); // LOL
				/*old*/
				/*movement = {movement.x * c - movement.y * s, movement.x * s + movement.y * c};
				player->setPos(vec3_t(pos.x, mathGround, pos.z));
				moveVec.y = player->velocity.y;
				player->jumpFromGround();*/
			}
			break;
		case 3: // Clip
			if (player->onGround) {
				clientMessageF("onGround");
				player->setPos(vec3_t(pos.x, pos.y + 0.5f, pos.z));
			}
			break;
		}
		if (tower.getSelectedValue() != 3) {
			vec3_t blockBelow = player->eyePos0;  // Block 1 block below the player
			blockBelow.y -= player->height;
			blockBelow.y -= 0.5f;
			blockBelowY = blockBelow;
		}
	}
}

void Scaffold::onPlayerTick(C_Player* plr) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	static float smoothing = 10.f; // 37.f;
	if (g_Data.canUseMoveKeys() && moduleMgr->getModule<Killaura>()->targetListEmpty) {
		vec3_t pPos = vec3_t(player->getPos()->x, player->getPos()->y - 1, player->getPos()->z);
		vec2_t blockPosition = player->getPos()->CalcAngle(vec3_t(calcPos));
		vec2_t back = player->getPos()->CalcAngle(backPos).normAngles();

		float speed = g_Data.getLocalPlayer()->getBlocksPerSecond();

		// Normal
		if (animYaw > blockPosition.y) animYaw -= ((animYaw - blockPosition.y) / smoothing);
		else if (animYaw < blockPosition.y) animYaw += ((blockPosition.y - animYaw) / smoothing);
		animPitch = blockPosition.x;

		// Back
		if (animBack > back.y) animBack -= ((animBack - back.y) / smoothing);
		else if (animBack < back.y) animBack += ((back.y - animBack) / smoothing);

		if (speed > 0.05f || GameData::isKeyDown(*input->spaceBarKey)) {
			switch (rotations.getSelectedValue()) {
			case 0: // Normal
			case 1: // Hive
				player->yawUnused1 = animYaw;
				player->bodyYaw = animYaw;
				player->pitch = animPitch;
				break;
			case 2: // Down
				player->pitch = 83;
				break;
			case 3: // Back
				player->yawUnused1 = animBack;
				player->bodyYaw = animBack;
				player->pitch = 80;
				break;
			}
		}
	}
}

void Scaffold::onSendPacket(C_Packet* packet) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
		if (g_Data.canUseMoveKeys()) {
			vec2_t blockPosition = player->getPos()->CalcAngle(vec3_t(calcPos));
			float speed = g_Data.getLocalPlayer()->getBlocksPerSecond();

			auto* authInputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);

			if (speed > 0.05f || GameData::isKeyDown(*input->spaceBarKey)) {
				switch (rotations.getSelectedValue()) {
				case 0: // Normal
				case 1: // Hive
				case 4: // Silent
					movePacket->headYaw = blockPosition.y;
					movePacket->yaw = blockPosition.y;
					movePacket->pitch = blockPosition.x;
					break;
				case 3: // Back
					movePacket->headYaw = animBack;
					movePacket->yaw = animBack;
					movePacket->pitch = 80;
					break;
				}
			}
		}
	}
}

void Scaffold::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	static auto clickGUI = moduleMgr->getModule<ClickGUIMod>();
	vec4_t testRect = vec4_t(scX, scY, 25 + scX, scY + 16);
	vec2_t textPos(testRect.x + 8, testRect.y + 8);
	vec2_t blockPos(testRect.x + 5, testRect.y + 7);

	if (blockCount && !clickGUI->isEnabled()) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		int totalCount = 0;

		for (int s = 0; s < 9; s++) {
			C_ItemStack* stack = inv->getItemStack(s);
			if (stack->item != nullptr && stack->getItem()->isBlock() && findBlocks(stack)) {
				totalCount += stack->count;
			}
		}

		string count = to_string(totalCount);
		MC_Color color = MC_Color();
		if (totalCount > 64) color = MC_Color(255, 255, 255);
		if (totalCount < 64) color = MC_Color(255, 255, 20);
		if (totalCount < 32) color = MC_Color(255, 196, 0);
		if (totalCount < 16) color = MC_Color(252, 62, 62);
		if (totalCount < 1) color = MC_Color(255, 0, 0);
		DrawUtils::drawText(vec2_t(textPos), &count, color, 1.f, true);
	}
}

bool Scaffold::buildBlock(vec3_t blockBelow) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	float velocityxz = g_Data.getLocalPlayer()->velocity.magnitudexz();
	static vector<vec3_ti*> checklist;
	auto player = g_Data.getLocalPlayer();
	blockBelow = blockBelow.floor();
	int i = 0;

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);
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
			calcPos = blok.toVector3().add(0.78f, 0.78f, 0.78f);
			return true;
		}
	}
	return false;
}

bool Scaffold::predictBlock(vec3_t blockBelow) {
	static vector<vec3_ti> blocks;
	if (blocks.empty()) {
		for (int y = -range; y <= 0; y++) {
			for (int x = -range; x <= range; x++) {
				for (int z = -range; z <= range; z++) {
					blocks.push_back(vec3_ti(x, y, z));
				}
			}
		}
		//https://www.mathsisfun.com/geometry/pythagoras-3d.html c2 = x2 + y2 + z2
		sort(blocks.begin(), blocks.end(), [](vec3_ti start, vec3_ti end) {
			return sqrtf((start.x * start.x) + (start.y * start.y) + (start.z * start.z)) < sqrtf((end.x * end.x) + (end.y * end.y) + (end.z * end.z));
		});
	}

	blockBelow = blockBelow.floor();

	for (const vec3_ti& offset : blocks) {
		vec3_ti currentBlock = vec3_ti(blockBelow).add(offset);
		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(currentBlock);
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		C_BlockLegacy* blockLegacy = (block->blockLegacy);
		auto player = g_Data.getLocalPlayer();
		float velocityxz = player->velocity.magnitudexz();
		if (blockLegacy->material->isReplaceable) {
			vec3_ti blok(currentBlock);
			int i = 0;
			static vector<vec3_ti*> checklist;
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
				calcPos = blok.toVector3().add(0.78f, 0.78f, 0.78f);
				return true;
			}
		}
	}
	return false;
}

bool Scaffold::selectBlock() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto prevSlot = supplies->selectedHotbarSlot;
	if (spoof) {
		for (int n = 0; n < 36; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->isBlock() && isUsefulBlock(stack)) {
					if (prevSlot != n)
						supplies->selectedHotbarSlot = n;
					return true;
				}
			}
		}
	} else {
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->isBlock() && isUsefulBlock(stack)) {
					if (prevSlot != n)
						supplies->selectedHotbarSlot = n;
					return true;
				}
			}
		}
	}
	return false;
}

bool Scaffold::isUsefulBlock(C_ItemStack* itemStack) {
	vector<string> uselessSubstrings = { "_coral", "_button", "chest", "boom", "vine", "pressure_plate", "fence", "_wall", "_stairs", "_table", "furnace", "trapdoor", "command_block", "torch", "carpet", "flower" };
	vector<string> uselessNames = { "cake", "ladder", "tnt", "lever", "loom", "scaffolding", "web", "sand", "gravel", "dragon_egg", "anvil", "bamboo"};
	string itemName = itemStack->getItem()->name.getText();

	for (auto substring : uselessSubstrings) {
		if (itemName.find(substring) != string::npos) {
			return 0;
		}
	}

	for (auto name : uselessNames) {
		if (itemName == name) {
			return 0;
		}
	}
	return 1;
}

bool Scaffold::findBlocks(C_ItemStack* itemStack) {
	if (itemStack->item == nullptr) return true;
	if ((*itemStack->item)->isBlock() && isUsefulBlock(itemStack)) return true; // Block
	return false;
}

void Scaffold::onDisable() {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
	auto sprint = moduleMgr->getModule<Sprint>();
	sprint->useSprint = true;

	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (tower.getSelectedValue() == 1 && foundBlock && jumping) player->velocity.y = 0.f;
	C_PlayerInventoryProxy* supplies = player->getSupplies();
	supplies->selectedHotbarSlot = slot;

	Utils::patchBytes((unsigned char*)HiveRotations1, (unsigned char*)"\x89\x41\x18", 3);
	Utils::patchBytes((unsigned char*)HiveRotations2, (unsigned char*)"\xC7\x40\x18\x03\x00\x00\x00", 7);
}
