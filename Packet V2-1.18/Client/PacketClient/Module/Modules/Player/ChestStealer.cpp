#include "ChestStealer.h"
#include "../pch.h"

using namespace std;
ChestStealer::ChestStealer() : IModule(0, Category::PLAYER, "Takes/Dumps items from chests") {
	//registerBoolSetting("Auto Disable", &autoDisable, autoDisable);
	registerBoolSetting("Enhanced", &enhanced, enhanced);
	registerBoolSetting("Dump", &dump, dump);
	registerIntSetting("Delay", &setDelay, setDelay, 0, 30);
}

const char* ChestStealer::getRawModuleName() {
	return "ChestStealer";
}

const char* ChestStealer::getModuleName() {
	name = string("ChestStealer ") + string(GRAY) + to_string((int)setDelay);
	return name.c_str();
}

void ChestStealer::chestScreenController_tick(C_ChestScreenController* c) {
	if (dump) {
		if (c != nullptr) {
			delay++;
			vector<int> items = {};
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
			else c->tryExit();
		}
	}
	else {
		if (c != nullptr) {
			delay++;
			vector<int> items = {};
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
			else c->tryExit();
		}
	}
}