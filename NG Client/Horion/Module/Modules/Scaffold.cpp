#include "Scaffold.h"

#include "../../../Utils/Logger.h"
#include "../ModuleManager.h"
uintptr_t HiveBypass1 = Utils::getBase() + 0x8F3895;  // Second one of 89 41 ? 0F B6 42 ? 88 41 ? F2 0F 10 42 ? F2 0F 11 41 ? 8B 42 ? 89 41 ? 8B 42 ? 89 41 ? 8B 42 ? 89 41 ? 8B 42 ? 48 83 C2 ? 89 41 ? 48 83 C1 ? E8 ? ? ? ? 0F B6 43
uintptr_t HiveBypass2 = Utils::getBase() + 0x8F87C7;  // C7 40 ? ? ? ? ? 48 8B 8D ? ? ? ? 48 33 CC E8 ? ? ? ? 4C 8D 9C 24
void* NoSneakAddress = (void*)FindSignature("75 0A 80 7B 59 00");

Scaffold::Scaffold() : IModule(VK_NUMPAD1, Category::WORLD, "Automatically build blocks beneath you") {
	registerBoolSetting("Staircase Mode", &staircaseMode, staircaseMode);
	registerBoolSetting("Tower", &fagNigas, fagNigas);
	registerFloatSetting("Tower Speed", &UpwardsFlyinNigas, UpwardsFlyinNigas, 0.3f, 1.f);
	registerBoolSetting("AirPlace", &airplace, airplace);
	registerBoolSetting("Auto Select", &autoselect, autoselect);
	registerBoolSetting("Full Select", &Fullselect, Fullselect);
	registerBoolSetting("Spoof", &spoof, spoof);
	registerBoolSetting("Predict", &predict, predict);
	registerBoolSetting("Spam", &spam, spam);
	registerBoolSetting("Y Lock", &yLock, yLock);
	registerBoolSetting("Hive", &rot, rot);
	registerBoolSetting("Rotations", &SukinMyBigJuicyAss, SukinMyBigJuicyAss);
	registerBoolSetting("NoSwing", &noSwing, noSwing);
	registerBoolSetting("Block Count", &GayNigaFags, GayNigaFags);
	registerBoolSetting("Thick Scaffold", &THICCC, THICCC);
}

Scaffold::~Scaffold() {
}

const char* Scaffold::getModuleName() {
		return "Scaffold";
}

bool Scaffold::canPlaceHere(vec3 blockPos) {
	vec3 bb = blockPos.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3i(bb));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	return blockLegacy->material->isReplaceable;
}

bool Scaffold::tryScaffold(vec3 blockBelow) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3i(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3i blok(blockBelow);
		int i = 0;
		if (airplace) {
			if (fagNigas && GameData::isKeyDown(*input->spaceBarKey) && !yLock) {
				vec3 moveVec;
				moveVec.x = g_Data.getLocalPlayer()->velocity.x;
				moveVec.y = UpwardsFlyinNigas;
				moveVec.z = g_Data.getLocalPlayer()->velocity.z;
				g_Data.getLocalPlayer()->lerpMotion(moveVec);
			}
			g_Data.getCGameMode()->buildBlock(&blok, i);
			return true;
		} else {
			static std::vector<vec3i*> checklist;
			bool foundCandidate = false;
			if (checklist.empty()) {
				checklist.push_back(new vec3i(0, -1, 0));
				checklist.push_back(new vec3i(0, 1, 0));

				checklist.push_back(new vec3i(0, 0, -1));
				checklist.push_back(new vec3i(0, 0, 1));

				checklist.push_back(new vec3i(-1, 0, 0));
				checklist.push_back(new vec3i(1, 0, 0));
			}

			for (auto current : checklist) {
				vec3i calc = blok.sub(*current);
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
				if (fagNigas && GameData::isKeyDown(*input->spaceBarKey) && !yLock) {
					vec3 moveVec;
					moveVec.x = g_Data.getLocalPlayer()->velocity.x;
					moveVec.y = UpwardsFlyinNigas;
					moveVec.z = g_Data.getLocalPlayer()->velocity.z;
					g_Data.getLocalPlayer()->lerpMotion(moveVec);
				}
				g_Data.getCGameMode()->buildBlock(&blok, i);
				return true;
			}
			//g_Data.getCGameMode()->buildBlock(&blok, i);
		}
	}
	return false;
}

bool Scaffold::tryActuallySomewhatDecentScaffold(vec3 blockPos) {
	static std::vector<vec3i> blockOffsets;
	if (blockOffsets.empty()) {
		int buildOutAmount = 3;
		for (int y = -buildOutAmount; y <= 0; y++) {
			for (int x = -buildOutAmount; x <= buildOutAmount; x++) {
				for (int z = -buildOutAmount; z <= buildOutAmount; z++) {
					blockOffsets.push_back(vec3i(x, y, z));
				}
			}
		}
		std::sort(blockOffsets.begin(), blockOffsets.end(),
				  [](vec3i a, vec3i b) {
					  return sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z)) < sqrtf((b.x * b.x) + (b.y * b.y) + (b.z * b.z));
				  });
	}

	blockPos = blockPos.floor();

	int attempts = 0;

	for (int idx = 0; idx < blockOffsets.size(); idx++) { // This algorithm loops through the list every time. This is pretty inefficient, but the list is pretty small and it works so I won't bother optimizing it 
		if (attempts >= 7) return false;
		vec3i currentBlock = vec3i(blockPos).add(blockOffsets.at(idx));
		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(currentBlock);
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		C_BlockLegacy* blockLegacy = (block->blockLegacy);
		if (blockLegacy->material->isReplaceable) {
			vec3i blok(currentBlock);
			int i = 0;
			if (airplace) {
				if (fagNigas && GameData::isKeyDown(*input->spaceBarKey) && !yLock) {
					vec3 moveVec;
					moveVec.x = g_Data.getLocalPlayer()->velocity.x;
					moveVec.y = UpwardsFlyinNigas;
					moveVec.z = g_Data.getLocalPlayer()->velocity.z;
					g_Data.getLocalPlayer()->lerpMotion(moveVec);
				}
				g_Data.getCGameMode()->buildBlock(&blok, i);
				return true;
			} else {
				static std::vector<vec3i*> checklist;
				bool foundCandidate = false;
				if (checklist.empty()) {
					checklist.push_back(new vec3i(0, -1, 0));
					checklist.push_back(new vec3i(0, 1, 0));

					checklist.push_back(new vec3i(0, 0, -1));
					checklist.push_back(new vec3i(0, 0, 1));

					checklist.push_back(new vec3i(-1, 0, 0));
					checklist.push_back(new vec3i(1, 0, 0));
				}

				for (auto current : checklist) {
					vec3i calc = blok.sub(*current);
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
					if (fagNigas && GameData::isKeyDown(*input->spaceBarKey) && !yLock) {
						vec3 moveVec;
						moveVec.x = g_Data.getLocalPlayer()->velocity.x;
						moveVec.y = UpwardsFlyinNigas;
						moveVec.z = g_Data.getLocalPlayer()->velocity.z;
						g_Data.getLocalPlayer()->lerpMotion(moveVec);
					}
					g_Data.getCGameMode()->buildBlock(&blok, i);
					if (spam && idx != 0) {
						idx = -1;
						attempts++;
					} 
					else {
						return true;
					}
				}
				//g_Data.getCGameMode()->buildBlock(&blok, i);
			}
		}
		if (idx == blockOffsets.size() - 1) return false;
	}
	return false;
}

bool Scaffold::findBlock() {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto prevSlot = supplies->selectedHotbarSlot;
	if (!Fullselect) {
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
	} else {
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
	}
	return false;
}

bool Scaffold::isUsefulBlock(C_ItemStack* itemStack) {
	std::vector<std::string> uselessSubstrings = {"_button", "chest", "boom", "vine", "pressure_plate", "fence", "_wall", "_stairs", "_table", "furnace", "trapdoor", "command_block", "torch", "carpet"};
	std::vector<std::string> uselessNames = {"cake", "ladder", "tnt", "lever", "loom", "scaffolding", "web", "sand", "gravel", "dragon_egg", "anvil"};
	std::string itemName = itemStack->getItem()->name.getText();
	for (auto substring : uselessSubstrings) {
		if (itemName.find(substring) != std::string::npos) {
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

void Scaffold::onTick(C_GameMode* gm) {
	if (spoof) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		supplies->selectedHotbarSlot = slot;
	}
	// float Pitch = (gm->player->pitch) * -(PI / 180); Correct Pitch
	if (rot) {
		g_Data.getLocalPlayer()->pointingStruct->rayHitType = 0;
		Utils::nopBytes((BYTE*)HiveBypass1, 3);
		Utils::patchBytes((BYTE*)HiveBypass2, (BYTE*)"\xC7\x40\x18\x00\x00\x00\x00", 7);
	}

	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;
	if (autoselect) {
		findBlock();
	}
	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock()) && !spoof)  // Block in hand?
		return;

	// Adjustment by velocity
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	vec3 vel = g_Data.getLocalPlayer()->velocity;
	vel = vel.normalize();  // Only use values from 0 - 1
	if (staircaseMode) {
		Utils::nopBytes((BYTE*)NoSneakAddress, 2);
	}
	if (staircaseMode && g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown) {
		blockBelowUrMom = g_Data.getLocalPlayer()->eyePos0;  // Block 1 block below the player
		blockBelowUrMom.y -= g_Data.getLocalPlayer()->height;
		blockBelowUrMom.y -= 1.5f;

		vec3 blockBelowBelow = g_Data.getLocalPlayer()->eyePos0;  // Block 2 blocks below the player
		blockBelowBelow.y -= g_Data.getLocalPlayer()->height;
		blockBelowBelow.y -= 2.0f;

		if (!tryScaffold(blockBelowUrMom) && !tryScaffold(blockBelowBelow)) {
			if (speed > 0.05f) {  // Are we actually walking?
				blockBelowUrMom.z -= vel.z * 0.4f;
				blockBelowBelow.z -= vel.z * 0.4f;
				if (!tryScaffold(blockBelowUrMom) && !tryScaffold(blockBelowBelow)) {
					blockBelowUrMom.x -= vel.x * 0.4f;
					blockBelowBelow.x -= vel.x * 0.4f;
					if (!tryScaffold(blockBelowUrMom) && !tryScaffold(blockBelowBelow) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelowUrMom.z += vel.z;
						blockBelowUrMom.x += vel.x;
						blockBelowBelow.z += vel.z;
						blockBelowBelow.x += vel.x;
						tryScaffold(blockBelowUrMom);
						tryScaffold(blockBelowBelow);
					}
				}
			}
		}
	} else {
		if (yLock) {
			blockBelowtest2 = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
			blockBelowtest2.y = blockBelowtest.y;
		} else {
			blockBelowtest2 = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
			blockBelowtest2.y -= 2.5f;
		}
		if (canPlaceHere(blockBelowtest2)) {  // There is no block below us. We won't try to predict this tick (if it's enabled)
			tryActuallySomewhatDecentScaffold(blockBelowtest2);
		} else {  // There is already a block below us
			if (predict) {
				tryScaffold(blockBelowtest2);
				blockBelowtest2.z -= vel.z * 0.4f;
				if (!tryScaffold(blockBelowtest2)) {
					blockBelowtest2.x -= vel.x * 0.4f;
					blockBelowtest2.z += vel.z;
					blockBelowtest2.x += vel.x;
					tryScaffold(blockBelowtest2);
					blockBelowtest2.z -= vel.z * 0.3f;
					if (!tryScaffold(blockBelowtest2)) {
						blockBelowtest2.x -= vel.x * 0.2f;
						blockBelowtest2.z += vel.z;
						blockBelowtest2.x += vel.x;
						tryScaffold(blockBelowtest2);
						blockBelowtest2.z -= vel.z * 0.1f;
					}
					if (!tryScaffold(blockBelowtest2)) {
						blockBelowtest2.x -= vel.x * 0.2f;
						blockBelowtest2.z += vel.z;
						blockBelowtest2.x += vel.x;
						tryScaffold(blockBelowtest2);
						blockBelowtest2.z -= vel.z * 0.1f;
					}
				}
				if (THICCC)
					tryActuallySomewhatDecentScaffold(blockBelowtest2);
			}
		}
	}
	if (spoof) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		supplies->selectedHotbarSlot = slot;
	}
}

void Scaffold::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (GayNigaFags) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		int totalCount = 0;
		for (int n = 0; n < 36; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != nullptr && stack->getItem()->isBlock() && isUsefulBlock(stack)) {
				totalCount += stack->count;
			}
		}
		vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		MC_Color Color = MC_Color();
		if (totalCount >= 64)
			Color = MC_Color(0, 255, 0);
		else if (totalCount <= 63 && totalCount >= 33)
			Color = MC_Color(255, 255, 0);
		else if (totalCount <= 32)
			Color = MC_Color(255, 0, 0);
		DrawUtils::drawText(vec2{windowSize.x / (float)1.95, windowSize.y / (float)2.05}, &std::to_string(totalCount), Color, 1.3f);
	}
}

void Scaffold::onLevelRender() {
	if (spoof) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		supplies->selectedHotbarSlot = slot;
	}
}
void Scaffold::onPlayerTick(C_Player* plr) {
	if (SukinMyBigJuicyAss) {
		vec2 joe;
		if (staircaseMode && g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown)
			joe = plr->getPos()->CalcAngle(blockBelowUrMom).normAngles();
		else
			joe = plr->getPos()->CalcAngle(blockBelowtest2).normAngles();
		if (findBlock() && g_Data.getLocalPlayer()->getBlocksPerSecond() > 0.1f) {
			plr->bodyYaw = joe.y;
			plr->yawUnused1 = joe.y;
			plr->pitch = 75.f;
		}
	}
}

void Scaffold::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
		if (g_Data.getLocalPlayer() != nullptr && g_Data.canUseMoveKeys() && rot) {
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			if (g_Data.getLocalPlayer()->getBlocksPerSecond() > 0.1f || GameData::isKeyDown(*input->spaceBarKey)) {
				vec2 angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(blockBelowtest2);
				movePacket->pitch = angle.x;
				movePacket->headYaw = angle.y;
				movePacket->yaw = angle.y;
			}
		}
	}
	//Credits Packet
}

void Scaffold::onEnable() {
	if (autoselect) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		slot = supplies->selectedHotbarSlot;
	}
	blockBelowtest = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
	blockBelowtest.y -= 2.5f;
}
void Scaffold::onDisable() {
	if (autoselect) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		supplies->selectedHotbarSlot = slot;
	}
	if (staircaseMode)
	Utils::patchBytes((BYTE*)((uintptr_t)NoSneakAddress), (BYTE*)"\x75\x0A", 2);
	Utils::patchBytes((BYTE*)HiveBypass1, (BYTE*)"\x89\x41\x18", 3);
	Utils::patchBytes((BYTE*)HiveBypass2, (BYTE*)"\xC7\x40\x18\x03\x00\x00\x00", 7);
}