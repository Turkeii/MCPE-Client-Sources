#include "ChestStealer.h"

#include "../ModuleManager.h"

ChestStealer::ChestStealer() : IModule(0, Category::PLAYER, "Automatically takes or dumps all items out of a chest or into a chest") {
	registerIntSetting("Delay", &setDelay, setDelay, 0, 10);
	registerBoolSetting("Enhanced", &enhanced, enhanced);
	registerBoolSetting("Dump", &dump, dump);
}

ChestStealer::~ChestStealer() {
}

const char* ChestStealer::getModuleName() {
	return "ChestStealer";
}

void ChestStealer::chestScreenController_tick(C_ChestScreenController* c) {
	if (dump) {
		delay++;
		if (c != nullptr) {
			std::vector<int> items = {};
			auto invcleanerMod = moduleMgr->getModule<InvManager>();
			for (int i = 0; i < 54; i++) {
				C_ItemStack* stack = c->_getItemStack(TextHolder("inventory_items"), i);
				C_ItemStack* stack2 = c->_getItemStack(TextHolder("hotbar_items"), i);
				if (stack != nullptr && stack->item != NULL || stack2 != nullptr && stack2->item != NULL)
					if (!enhanced || invcleanerMod->stackIsUseful(stack) || invcleanerMod->stackIsUseful(stack))
						items.push_back(i);
			}
			if (!items.empty()) {
				for (int i : items) {
					if (delay > setDelay && setDelay >= 1) {
						c->handleAutoPlace(0x7FFFFFFF, "inventory_items", i);
						c->handleAutoPlace(0x7FFFFFFF, "hotbar_items", i);
						delay = 0;
						return;
					}
				}
			}
			else
				c->tryExit();
		}
	}
	else {
		delay++;
		if (c != nullptr) {
			std::vector<int> items = {};
			auto invcleanerMod = moduleMgr->getModule<InvManager>();
			for (int i = 0; i < 54; i++) {
				C_ItemStack* stack = c->_getItemStack(TextHolder("container_items"), i);
				if (stack != nullptr && stack->item != NULL)
					if (!enhanced || invcleanerMod->stackIsUseful(stack))
						items.push_back(i);
			}
			if (!items.empty()) {
				for (int i : items) {
					if (delay > setDelay && setDelay >= 1) {
						c->handleAutoPlace(0x7FFFFFFF, "container_items", i);
						delay = 0;
					}
					else if (setDelay <= 0)
						c->handleAutoPlace(0x7FFFFFFF, "container_items", i);
				}
			}
			else
				c->tryExit();
		}
	}
}