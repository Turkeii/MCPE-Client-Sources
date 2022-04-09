#include "InvManager.h"

#include "../ModuleManager.h"

class ArmorStruct {
public:
	ArmorStruct(C_ItemStack* item, C_ArmorItem* yot, int slot) {
		armor = yot;
		m_slot = slot;
		m_item = item;
	}
	bool isEqual(ArmorStruct& src) {
		if (this->m_item->getArmorValueWithEnchants() == src.m_item->getArmorValueWithEnchants())
			return true;
		else
			return false;
	}

	bool operator()(ArmorStruct lhs, ArmorStruct rhs) {
		return (lhs.m_item->getArmorValueWithEnchants() > rhs.m_item->getArmorValueWithEnchants());
	}
	C_ArmorItem* armor = nullptr;
	C_ItemStack* m_item = nullptr;
	int m_slot = 0;
};

InvManager::InvManager() : IModule(0, Category::PLAYER, "Manages your inventory for you") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Normal", 0);
	mode.addEntry("Inventory", 1);
	registerBoolSetting("AutoArmor", &autoArmor, autoArmor);
	registerBoolSetting("Sort", &autoSort, autoSort);
	registerIntSetting("Sword", &swordSlot, swordSlot, 0, 9);
	registerIntSetting("Pickaxe", &pickSlot, pickSlot, 0, 9);
	registerIntSetting("Axe", &axeSlot, axeSlot, 0, 9);
	registerIntSetting("Blocks", &blockSlot, blockSlot, 0, 9);
	registerBoolSetting("AutoDisable", &autoDisable, autoDisable);
	registerIntSetting("Delay", &delay, delay, 0, 30);
}

InvManager::~InvManager() {
}

const char* InvManager::getRawModuleName() {
	return "InvManager";
}

const char* InvManager::getModuleName() {
	name = std::string("InvManager ") + std::string(GRAY) + std::to_string((int)delay);
	return name.c_str();
}

void InvManager::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (g_Data.getLocalPlayer()->canOpenContainerScreen() && mode.getSelectedValue() == 1)
		return;

	// Drop items
	if (clean) {
		std::vector<int> dropSlots = findUselessItems();
		Odelay++;
		if (Odelay > delay) {
			if (!dropSlots.empty()) {
				for (int i : dropSlots) {
					Odelay++;
					if (Odelay > delay) {
						g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(i);
						dropSlots.push_back(i);
					}
				}
			}
			Odelay = 0;
		}
	}

	if (autoSort) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		float damage = 0;
		int item = 0;
		for (int n = 0; n < 36; n++) {
			C_ItemStack* stack = inv->getItemStack(n);
			if (stack->item != NULL) {
				float currentDamage = stack->getAttackingDamageWithEnchants();
				if (currentDamage > damage) {
					damage = currentDamage;
					item = n;
				}
			}
		}
		if (item != 0) {
			inv->swapSlots(item, 0);
		}
	}

	if (autoArmor) {
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();

		C_InventoryAction* first = nullptr;
		C_InventoryAction* second = nullptr;
		static C_ItemStack* emptyItemStack = nullptr;

		if (emptyItemStack == 0x0) {
			uintptr_t sigOffset = FindSignature("48 8D 3D ? ? ? ? 80 B8 ? ? ? ? ? 75 19 48 8B 88 ? ? ? ? 48 8B 11 4C 8B 42 28 8B 50 10");
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
			emptyItemStack = reinterpret_cast<C_ItemStack*>(sigOffset + offset + /*length of instruction*/ 7);
		}

		std::vector<ArmorStruct> armorList;

		struct CompareArmorStruct {
			bool operator()(ArmorStruct lhs, ArmorStruct rhs) {
				return (lhs.m_item->getArmorValueWithEnchants() > rhs.m_item->getArmorValueWithEnchants());
			}
		};

		for (int i = 0; i < 4; i++) {
			for (int n = 0; n < 36; n++) {
				C_ItemStack* stack = inv->getItemStack(n);
				if (stack->item != NULL && (*stack->item)->isArmor() && reinterpret_cast<C_ArmorItem*>(*stack->item)->getArmorSlot() == i) {
					armorList.push_back(ArmorStruct(stack, reinterpret_cast<C_ArmorItem*>(*stack->item), n));
				}
			}

			if (gm->player->getArmor(i)->item != nullptr)
				armorList.push_back(ArmorStruct(gm->player->getArmor(i), reinterpret_cast<C_ArmorItem*>(*gm->player->getArmor(i)->item), i));

			if (armorList.size() > 0) {
				std::sort(armorList.begin(), armorList.end(), CompareArmorStruct());
				C_ItemStack* armorItem = gm->player->getArmor(i);

				if (armorItem->item != nullptr && (ArmorStruct(armorItem, reinterpret_cast<C_ArmorItem*>(*armorItem->item), 0).isEqual(armorList[0])) == false) {
					int slot = inv->getFirstEmptySlot();

					first = new C_InventoryAction(i, armorItem, nullptr, 632);
					second = new C_InventoryAction(slot, nullptr, armorItem);

					*g_Data.getLocalPlayer()->getArmor(i) = *emptyItemStack;
					*inv->getItemStack(slot) = *armorItem;

					manager->addInventoryAction(*first);
					manager->addInventoryAction(*second);

					delete first;
					delete second;

					first = new C_InventoryAction(armorList[0].m_slot, armorList[0].m_item, nullptr);
					second = new C_InventoryAction(i, nullptr, armorList[0].m_item, 632);

					*g_Data.getLocalPlayer()->getArmor(i) = *inv->getItemStack(armorList[0].m_slot);
					*inv->getItemStack(armorList[0].m_slot) = *emptyItemStack;

					manager->addInventoryAction(*first);
					manager->addInventoryAction(*second);

					delete first;
					delete second;
				}
				if (armorItem->item == nullptr) {
					*g_Data.getLocalPlayer()->getArmor(i) = *inv->getItemStack(armorList[0].m_slot);

					first = new C_InventoryAction(armorList[0].m_slot, armorList[0].m_item, nullptr);
					second = new C_InventoryAction(i, nullptr, armorList[0].m_item, 632);

					*inv->getItemStack(armorList[0].m_slot) = *emptyItemStack;

					manager->addInventoryAction(*first);
					manager->addInventoryAction(*second);

					delete first;
					delete second;
				}
			}
			armorList.clear();
		}
		armorList.clear();
	}

	if (autoDisable && g_Data.getLocalPlayer() == nullptr) {
		auto notification = g_Data.addNotification("InvManager:", "Disabled");
		notification->duration = 3;
		setEnabled(false);
	}
}

std::vector<int> InvManager::findStackableItems() {
	std::vector<int> stackableSlot;

	for (int i = 0; i < 36; i++) {
		C_ItemStack* itemStack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemStack->item != nullptr) {
			if ((*itemStack->item)->getMaxStackSize(0) > itemStack->count) {
				for (int i2 = 0; i2 < 36; i2++) {
					if (i2 == i) continue;
					C_ItemStack* itemStack2 = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i2);
					if ((*itemStack2->item)->getMaxStackSize(0) > itemStack->count) {
						if (*itemStack->item == *itemStack2->item) {
							if ((std::find(stackableSlot.begin(), stackableSlot.end(), i2) == stackableSlot.end())) stackableSlot.push_back(i2);
							if ((std::find(stackableSlot.begin(), stackableSlot.end(), i) == stackableSlot.end())) stackableSlot.push_back(i);
						}
					}
				}
			}
		}
	}

	return stackableSlot;
}

std::vector<int> InvManager::findUselessItems() {
	// Filter by options

	std::vector<int> uselessItems;
	std::vector<C_ItemStack*> items;

	{
		for (int i = 0; i < 36; i++) { // 36
			C_ItemStack* itemStack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
			if (itemStack->item != nullptr) {
				if (!stackIsUseful(itemStack)) {
					if (std::find(items.begin(), items.end(), itemStack) == items.end())
						uselessItems.push_back(i);
					else
						items.push_back(itemStack);
				} else if (std::find(items.begin(), items.end(), itemStack) == items.end()) {
					if ((*itemStack->item)->itemId == 261 && !isLastItem(*itemStack->item))
						uselessItems.push_back(i);
					else
						items.push_back(itemStack);	
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (g_Data.getLocalPlayer()->getArmor(i)->item != nullptr)
				items.push_back(g_Data.getLocalPlayer()->getArmor(i));
		}
	}
	// Filter weapons
	if (items.size() > 0) {
		// Filter by attack damage
		std::sort(items.begin(), items.end(), [](const C_ItemStack* lhs, const C_ItemStack* rhs) {
			C_ItemStack* current = const_cast<C_ItemStack*>(lhs);
			C_ItemStack* other = const_cast<C_ItemStack*>(rhs);
			return current->getAttackingDamageWithEnchants() > other->getAttackingDamageWithEnchants();
		});

		bool hadTheBestItem = false;
		C_ItemStack* bestItem = items.at(0);

		for (int i = 0; i < 36; i++) { // 36
			if (std::find(uselessItems.begin(), uselessItems.end(), i) != uselessItems.end())
				continue;
			C_ItemStack* itemStack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
			if (itemStack->item != nullptr && itemStack->getAttackingDamageWithEnchants() > 1) {
				if (itemStack->getAttackingDamageWithEnchants() < bestItem->getAttackingDamageWithEnchants()) {
					uselessItems.push_back(i);
				} else {
					// Damage same as bestItem
					if (hadTheBestItem)
						uselessItems.push_back(i);
					else
						hadTheBestItem = true;
				}
			}
		}
	}
	// Filter armor
	{
		std::vector<C_ItemStack*> helmets;
		std::vector<C_ItemStack*> chestplates;
		std::vector<C_ItemStack*> leggings;
		std::vector<C_ItemStack*> boots;

		// Filter by armor value
		std::sort(items.begin(), items.end(), [](const C_ItemStack* lhs, const C_ItemStack* rhs) {
			C_ItemStack* current = const_cast<C_ItemStack*>(lhs);
			C_ItemStack* other = const_cast<C_ItemStack*>(rhs);
			return current->getArmorValueWithEnchants() > other->getArmorValueWithEnchants();
		});

		// Put armor items in their respective vectors
		for (C_ItemStack* itemsteck : items) {
			C_Item* item = itemsteck->getItem();
			if (item->isArmor()) {
				C_ArmorItem* armorItem = reinterpret_cast<C_ArmorItem*>(item);
				if (armorItem->isHelmet())
					helmets.push_back(itemsteck);
				else if (armorItem->isChestplate())
					chestplates.push_back(itemsteck);
				else if (armorItem->isLeggings())
					leggings.push_back(itemsteck);
				else if (armorItem->isBoots())
					boots.push_back(itemsteck);
			}
		}
		bool hadBest[4] = {0, 0, 0, 0};
		for (int i = 0; i < 4; i++) {
			C_ItemStack* itemsteck = g_Data.getLocalPlayer()->getArmor(i);
			C_Item** item = itemsteck->item;
			if (item != nullptr) {
				
				C_ArmorItem* armor = reinterpret_cast<C_ArmorItem*>(*item);
				
				float testArmorValue = 0;
				switch (armor->getArmorSlot()) {
				case 0:
					if (helmets.size() > 0)
						testArmorValue = helmets.at(0)->getArmorValueWithEnchants();
					break;
				case 1:
					if (chestplates.size() > 0)
						testArmorValue = chestplates.at(0)->getArmorValueWithEnchants();
					break;
				case 2:
					if (leggings.size() > 0)
						testArmorValue = leggings.at(0)->getArmorValueWithEnchants();
					break;
				case 3:
					if (boots.size() > 0)
						testArmorValue = boots.at(0)->getArmorValueWithEnchants();
					break;
				}
				if (itemsteck->getArmorValueWithEnchants() >= testArmorValue)
					hadBest[armor->getArmorSlot()] = true;
			}
		}

		for (int i = 0; i < 36; i++) { // 36
			if (std::find(uselessItems.begin(), uselessItems.end(), i) != uselessItems.end())
				continue;  // item already useless
			C_ItemStack* itemStack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
			if (itemStack->item != nullptr && (*itemStack->item)->isArmor()) {
				C_ArmorItem* armor = reinterpret_cast<C_ArmorItem*>(*itemStack->item);
				if (armor->isHelmet()) {
					if (hadBest[0] || itemStack->getArmorValueWithEnchants() < helmets.at(0)->getArmorValueWithEnchants()) {
						uselessItems.push_back(i);
					} else
						hadBest[0] = true;
				} else if (armor->isChestplate()) {
					if (hadBest[1] || itemStack->getArmorValueWithEnchants() < chestplates.at(0)->getArmorValueWithEnchants())
						uselessItems.push_back(i);
					else
						hadBest[1] = true;
				} else if (armor->isLeggings()) {
					if (hadBest[2] || itemStack->getArmorValueWithEnchants() < leggings.at(0)->getArmorValueWithEnchants())
						uselessItems.push_back(i);
					else
						hadBest[2] = true;
				} else if (armor->isBoots()) {
					if (hadBest[3] || itemStack->getArmorValueWithEnchants() < boots.at(0)->getArmorValueWithEnchants())
						uselessItems.push_back(i);
					else
						hadBest[3] = true;
				}
			}
		}
	}

	return uselessItems;
}

bool InvManager::stackIsUseful(C_ItemStack* itemStack) {
	if (itemStack->item == nullptr) return true;
	if (keep) {
		if ((*itemStack->item)->isArmor()) return true;      // Armor
		if ((*itemStack->item)->isTool()) return true;       // Tools
		if ((*itemStack->item)->isWeapon()) return true;     // Weapon
		if ((*itemStack->item)->isFood()) return true;       // Food
		if ((*itemStack->item)->isBlock()) return true;      // Block
	}
	return false;
}

bool InvManager::isLastItem(C_Item* item) {
	std::vector<C_Item*> items;
	for (int i = 0; i < 36; i++) {
		C_ItemStack* stack = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (stack->item != nullptr) items.push_back((*stack->item));
	}
	int count = 0;
	for (C_Item* a : items) {
		if (a == item) count++;
	}
	if (count > 1) return false;
	return true;
}
