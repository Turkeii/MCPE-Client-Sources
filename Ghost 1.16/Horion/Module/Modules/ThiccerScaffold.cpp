#include "ThiccerScaffold.h"

#include "../../../Utils/Logger.h"

ThiccerScaffold::ThiccerScaffold() : IModule(VK_NUMPAD1, Category::PLAYER, "Automatically build blocks beneath you. Credit to Packet") {
	registerBoolSetting("Staircase Mode", &this->staircaseMode, this->staircaseMode);
	registerBoolSetting("Timer", &this->timerBool, this->timerBool);
	registerBoolSetting("Rotations/Bypass", &this->rot, this->rot);
	this->registerIntSetting("TPS", &this->timer, this->timer, 20, 50);
}

ThiccerScaffold::~ThiccerScaffold() {
}

const char* ThiccerScaffold::getModuleName() {
	return "ThiccerScaffold";
}

bool ThiccerScaffold::tryScaffold(vec3_t blockBelow) {
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);

		// Find neighbour
		static std::vector<vec3_ti*> checklist;
		//if (checklist.empty()) {
		//}

		bool foundCandidate = true;
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
			g_Data.getCGameMode()->buildBlock(&blok, i);

			return true;
		}
	}
	return false;
}

bool ThiccerScaffold::findBlock() {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->isBlock() && (*stack->item)->itemId != 0) {
				C_MobEquipmentPacket a(id, *stack, n, n);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
				return true;
			}
		}
	}
	C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
	return false;
}

void ThiccerScaffold::onTick(C_GameMode* gm) {
	if (timerBool) {
		*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
	}
	if (!timerBool) {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}

	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();

	// Adjustment by velocity
	float speed = g_Data.getLocalPlayer()->velocity.magnitudexz();
	vec3_t vel = g_Data.getLocalPlayer()->velocity;
	vel = vel.normalize();  // Only use values from 0 - 1

	if (this->staircaseMode) {
		vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block 1 block below the player
		blockBelow.y -= g_Data.getLocalPlayer()->height;
		blockBelow.y -= 1.5f;

		vec3_t blockBelowBelow = g_Data.getLocalPlayer()->eyePos0;  // Block 2 blocks below the player
		blockBelowBelow.y -= g_Data.getLocalPlayer()->height;
		blockBelowBelow.y -= 2.0f;

		if (!tryScaffold(blockBelow) && !tryScaffold(blockBelowBelow)) {
			if (speed > 0.05f) {  // Are we actually walking?
				blockBelow.z -= vel.z * 1.0f;
				blockBelowBelow.z -= vel.z * 1.0f;
				if (!tryScaffold(blockBelow) && !tryScaffold(blockBelowBelow)) {
					blockBelow.x -= vel.x * 1.0f;
					blockBelowBelow.x -= vel.x * 1.0f;
					if (!tryScaffold(blockBelow) && !tryScaffold(blockBelowBelow) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelow.z += vel.z;
						blockBelow.x += vel.x;
						blockBelowBelow.z += vel.z;
						blockBelowBelow.x += vel.x;
						tryScaffold(blockBelow);
						tryScaffold(blockBelowBelow);
					}
				}
			}
		}
	} else {
		vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;  // Block below the player
		blockBelow.y -= g_Data.getLocalPlayer()->height;
		blockBelow.y -= 0.5f;
		if (this->rot) {
			for (int i = 0; i < 40; i++) {
				auto player = g_Data.getLocalPlayer();
				player->pitch = blockBelow.y;
				player->bodyYaw = blockBelow.y;
			}
		}
		if (!tryScaffold(blockBelow)) {
			if (speed > 0.05f) {  // Are we actually walking?
				blockBelow.z -= vel.z * 1.0f;
				if (!tryScaffold(blockBelow)) {
					blockBelow.x -= vel.x * 1.0f;
					if (!tryScaffold(blockBelow) && g_Data.getLocalPlayer()->isSprinting()) {
						blockBelow.z += vel.z;
						blockBelow.x += vel.x;
						tryScaffold(blockBelow);
					}
				}
			}
		}
	}
}

void ThiccerScaffold::onDisable() {
	if (timerBool) {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
}