#include "InventoryCleaner.h"

#include "../ModuleManager.h"
bool isUsefulExtraCheck(C_ItemStack* itemStack);
InventoryCleaner::InventoryCleaner() : IModule(0, Category::PLAYER, "Automatically throws not needed stuff out of your inventory") {
	registerIntSetting("Delay", &setDelay, setDelay, 0, 10);
	registerBoolSetting("Armor", &keepArmor, keepArmor);
	registerBoolSetting("Pickaxe", &keepPick, keepPick);
	registerBoolSetting("Shovel", &keepShovel, keepShovel);
	registerBoolSetting("Bow", &keepBow, keepBow);
	registerBoolSetting("Food", &keepFood, keepFood);
	registerBoolSetting("Blocks", &keepBlocks, keepBlocks);
	registerBoolSetting("Extra", &keepTools, keepTools);
	registerBoolSetting("OpenInv", &openInv, openInv);
	registerBoolSetting("AutoSort", &autoSort, autoSort);
}

InventoryCleaner::~InventoryCleaner() {
}

const char* InventoryCleaner::getModuleName() {
	return ("InvCleaner");
}

void InventoryCleaner::onTick(C_GameMode* gm) {
	// std::string screenName(g_Hooks.currentScreenName);
	// if (strcmp(screenName.c_str(), "inventory_screen") == 0 && openInv)
	// return;
	if (g_Data.getLocalPlayer()->canOpenContainerScreen() && openInv)
		return;
	delay++;
	// Drop useless items
	std::vector<int> dropSlots = findUselessItems();
	if (!dropSlots.empty()) {
		for (int i : dropSlots) {
			if (delay > setDelay && setDelay >= 1) {
				g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(i);
				delay = 0;
			} else if (setDelay <= 0)
				g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(i);
		}
	}

	if (autoSort) {
		// Put sword in first slot
		{
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
	}
}

std::vector<int> InventoryCleaner::findStackableItems() {
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

std::vector<int> InventoryCleaner::findUselessItems() {
	// Filter by options

	std::vector<int> uselessItems;
	std::vector<C_ItemStack*> items;

	{
		for (int i = 0; i < 36; i++) {
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

		for (int i = 0; i < 36; i++) {
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
				switch (armor->ArmorSlot) {
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
					hadBest[armor->ArmorSlot] = true;
			}
		}

		for (int i = 0; i < 36; i++) {
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
bool isUsefulExtraCheck(C_ItemStack* itemStack) {
	std::vector<std::string> uselessSubstrings = {"_button", "chest", "vine", "pressure_plate", "fence", "_wall", "_stairs", "_table", "furnace", "trapdoor", "command_block", "torch", "carpet"};
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

bool InventoryCleaner::stackIsUseful(C_ItemStack* itemStack) {
	if (itemStack->item == nullptr) return true;
	if (keepArmor && (*itemStack->item)->isArmor()) return true;                                    // Armor
	if (keepTools && (*itemStack->item)->isTool()) return true;                                     // Tools
	if (keepFood && (*itemStack->item)->isFood()) return true;                                      // Food
	if (keepBlocks && (*itemStack->item)->isBlock() && isUsefulExtraCheck(itemStack)) return true;  // Block
	if (keepBow && (*itemStack->item)->isShooter()) return true;                                    // Bow && crossbow
	if (keepPick && (*itemStack->item)->isPickaxe()) return true;                                   // Picks
	if (keepShovel && (*itemStack->item)->isShovel()) return true;                                  // Shovels
	return false;
}

bool InventoryCleaner::isLastItem(C_Item* item) {
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