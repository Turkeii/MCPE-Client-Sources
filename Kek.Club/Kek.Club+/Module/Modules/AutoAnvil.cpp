#include "AutoAnvil.h"

#include "../../../Utils/Logger.h"
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

AutoAnvil::AutoAnvil() : IModule(0, Category::PLAYER, "drops anvils on people/urself") {
	registerEnumSetting("Swap", &mode, 0);
	mode = SettingEnum(this)
				  .addEntry(EnumEntry("None", 0))
				  .addEntry(EnumEntry("Normal", 1))
				  .addEntry(EnumEntry("Slient", 2));
	registerBoolSetting("OnClick", &onClick, onClick);
	registerBoolSetting("AirPlace", &airplace, airplace);
	registerIntSetting("Range", &range, range, 1, 12);
	registerBoolSetting("AnvilSwap", &blockSwap, blockSwap);
	registerBoolSetting("SlientSwitch", &slientSwitch, slientSwitch);
}

AutoAnvil::~AutoAnvil() {
}

const char* AutoAnvil::getModuleName() {
	return ("AutoAnvil");
}
bool SilentSwap2(int Itemid) {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->itemId != 0) {
				if (stack->getItem()->itemId == Itemid) {
					C_MobEquipmentPacket a(id, *stack, n, n);
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
					return true;
				}
			}
		}
	}
	C_MobEquipmentPacket a(id, *g_Data.getLocalPlayer()->getSelectedItem(), supplies->selectedHotbarSlot, supplies->selectedHotbarSlot);
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
	return false;
}

bool isInInv2(int Itemid) {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->itemId != 0) {
				if (stack->getItem()->itemId == Itemid) {
					return true;
				}
			}
		}
	}
	return false;
}
static std::vector<C_Entity*> targetList15;

void findEntity150(C_Entity* currentEntity15, bool isRegularEntity) {
	static auto CrystalAuraOWMod = moduleMgr->getModule<AutoAnvil>();

	if (currentEntity15 == nullptr)
		return;

	if (currentEntity15 == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity15->getNameTag()->getTextLength() <= 1 && currentEntity15->getEntityTypeId() == 71)  // crystal
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity15, false))
		return;

	// if (!g_Data.getLocalPlayer()->isAlive())
	// return;

	if (!currentEntity15->isAlive())
		return;

	if (currentEntity15->getNameTag()->getTextLength() <= 1 && currentEntity15->getEntityTypeId() == 63)
		return;

	if (currentEntity15->width <= 0.01f || currentEntity15->height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
		return;

	if (!Target::isValidTarget(currentEntity15))
		return;

	float dist = (*currentEntity15->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < CrystalAuraOWMod->range) {
		targetList15.push_back(currentEntity15);

		float dist = (*currentEntity15->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

		if (dist < CrystalAuraOWMod->range) {
			targetList15.push_back(currentEntity15);
		}
	}
}

bool AutoAnvil::Spoof() {
	__int64 id = *g_Data.getLocalPlayer()->getUniqueId();
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if ((*stack->item)->isBlock() && (*stack->item)->itemId != 145) {
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

bool AutoAnvil::tryAutoTrap(vec3_t AutoTrap) {
	AutoTrap = AutoTrap.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(AutoTrap));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(AutoTrap);
		int i = 0;
		if (airplace) {
			if (spoofC) Spoof();
			bool idk = true;
			g_Data.getCGameMode()->buildBlock(&blok, i, idk);
			return true;
		} else {
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
				if (isInInv2(145)) SilentSwap2(145);
				bool idk = true;
				g_Data.getCGameMode()->buildBlock(&blok, i, idk);

				return true;
			}
		}

		return false;
	}
}
void AutoAnvil::onTick(C_GameMode* gm) {
	switch (mode.selected) {
	case 0:
		none = true;
		spoofC = false;
		slientSwitch = false;
		break;
	case 1:
		none = false;
		spoofC = true;
		slientSwitch = false;
		break;
	case 2:
		none = false;
		spoofC = false;
		slientSwitch = true;
		break;
	}
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;

	if (blockSwap) {
		for (int n = 0; n < 9; n++) {
			C_ItemStack* stack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(n);
			if (stack->item != nullptr) {
				if (stack->getItem()->itemId == 145) {
					g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = n;
				}
			}
		}
	}

	targetList15.clear();
	g_Data.forEachEntity(findEntity150);

	int place = 1;

	if (onClick) {
		if (GameData::isRightClickDown()) {
			place = 0;
		} else {
			place = 1;
		}
	}

	if (!onClick) {
		place = 0;
	}

	int crystal = 0;

	crystal = 145;
	crystal = 145;

	if (!targetList15.empty()) {
		if (g_Data.getLocalPlayer()->getSelectedItemId() == crystal) {
			// above players head
			vec3_t blockAbove = targetList15[0]->eyePos0;
			vec3_t blockAbove1 = targetList15[0]->eyePos0;
			vec3_t blockAbove2 = targetList15[0]->eyePos0;
			vec3_t blockAbove3 = targetList15[0]->eyePos0;
			vec3_t blockAbove4 = targetList15[0]->eyePos0;

			// above players head
			blockAbove.y -= targetList15[0]->height - 3;

			blockAbove1.y -= targetList15[0]->height - 3;

			blockAbove2.y -= targetList15[0]->height - 3;

			blockAbove3.y -= targetList15[0]->height - 3;

			blockAbove4.y -= targetList15[0]->height - 3;

			if (place == 0) {
				// placing block above players head (3blocks up from the ground)
				if (!tryAutoTrap(blockAbove)) {
					blockAbove.y -= 0;
				}

				if (!tryAutoTrap(blockAbove1)) {
					blockAbove1.y -= 0;
				}

				if (!tryAutoTrap(blockAbove2)) {
					blockAbove2.y -= 0;
				}

				if (!tryAutoTrap(blockAbove3)) {
					blockAbove3.y -= 0;
				}

				if (!tryAutoTrap(blockAbove4)) {
					blockAbove4.y -= 0;
				}
			}
		}
		++place;
		if (place != blocks_per_tick)
			return;
	}
}