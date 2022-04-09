#include "AutoTotem.h"

#include "../../../SDK/Tag.h"

AutoTotem::AutoTotem()
	: IModule(0x0, Category::COMBAT, "Automatically puts totems into your hand") {
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModuleName() {
	return ("ForceTotem");
}

void AutoTotem::onEnable() {
	g_Data.getLocalPlayer()->getSupplies()->inventory->dropSlot(8);
	savedSlot = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;  // saves slot ur on
}

void AutoTotem::onLevelRender() {
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("shulker_box")), 1, 0);
	std::string tag = R"({Count:1b,Damage:0s,Name:" minecraft : totem_of_undying ",WasPickedUp:0b,tag:{ench:[{id:0s,lvl:32767s},{id:2s,lvl:32767s},{id:5s,lvl:32767s},{id:6s,lvl:32767s},{id:7s,lvl:32767s},{id:8s,lvl:32767s},{id:36s,lvl:32767s},{id:9s,lvl:32767s},{id:13s,lvl:32767s},{id:14s,lvl:32767s},{id:16s,lvl:32767s},{id:17s,lvl:32767s},{id:21s,lvl:32767s},{id:23s,lvl:32767s},{id:29s,lvl:32767s},{id:12s,lvl:32767s},{id:15s,lvl:32767s},{id:19s,lvl:32767s},{id:20s,lvl:32767s},{id:22s,lvl:32767s},{id:24s,lvl:32767s},{id:27s,lvl:32767s},{id:28s,lvl:32767s},{id:30s,lvl:32767s},{id:33s,lvl:32767s},{id:35s,lvl:32767s}]}})";
	yot->fromTag(*Mojangson::parseTag(tag));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
	// g_Data.getLocalPlayer()->setOffhandSlot(yot); // working, but a fake item for some reason :/
	g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = 8;  // sets ur slot to 8
	g_Data.getLocalPlayer()->setCarriedItem(yot);                    // sets selected slot to the item
}

void AutoTotem::onDisable() {
	g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = savedSlot;  // sets ur slot back to the slot it was when u turned on
}

void AutoTotem::onTick(C_GameMode* gm) {}