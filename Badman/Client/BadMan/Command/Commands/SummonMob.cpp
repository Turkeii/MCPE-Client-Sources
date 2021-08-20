#include "SummonMob.h"

#include "../../../SDK/Tag.h"
#include "../../Module/ModuleManager.h"
#include <thread>

SummonMob::SummonMob() : IMCCommand("summonmob", "Spawn a Beehive that spawns a mob with god mode", "<beehive> <beenest> <bypass> <invis>") {
	registerAlias("summon");
}

SummonMob::~SummonMob() {
}

bool SummonMob::execute(std::vector<std::string>* args) {
	if (args->at(1) == "beehive") {
	assertTrue(args->size() > 2);
	std::ostringstream os;
	for (int i = 2; i < args->size(); i++) {
		if (i > 1)
			os << "";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("beehive")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{Occupants:[{ActorIdentifier:""\"minecraft:" + cmd + "<>\",SaveData:{Armor:[{Count:1b,Damage:0s,Name:""\"minecraft:netherite_helmet""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:8s,lvl:32767s},{id:6s,lvl:32767s},{id:5s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:elytra""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:netherite_leggings""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:netherite_boots""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:2s,lvl:32767s},{id:7s,lvl:32767s},{id:28s,lvl:1s}]}}],CustomName:""\"Epic BadMan User""\",Persistent:1b,Invulnerable:1b,Dead:1b,Mainhand:[{Count:1b,Damage:0s,Name:""\"minecraft:netherite_sword""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:9s,lvl:32767s},{id:13s,lvl:32767s},{id:14s,lvl:32767s},{id:28s,lvl:1s},{id:12s,lvl:32767s}]}}],definitions:[""\"+minecraft:" + cmd + "\"],identifier:""\"minecraft:" + cmd + "\",TicksLeftToStay:1}}],ench:[{id:28s,lvl:1s}],RepairCost:0,display:{Lore:[""\"§b§lBy BadMan Client""\"],Name:""\"§g§lMob Spawner Beehive""\"}";
	yot->setUserData(std::move(Mojangson::parseTag(tag)));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, yot, nullptr, 507, 99999));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sBadMan%s] %sPlace the beehive to spawn a god mob!", GOLD, WHITE, GREEN);
	return true;

}

	if (args->at(1) == "beenest") {
	assertTrue(args->size() > 2);
	std::ostringstream os;
	for (int i = 2; i < args->size(); i++) {
		if (i > 1)
			os << "";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("bee_nest")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{Occupants:[{ActorIdentifier:""\"minecraft:" + cmd + "<>\",SaveData:{Armor:[{Count:1b,Damage:0s,Name:""\"minecraft:netherite_helmet""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:8s,lvl:32767s},{id:6s,lvl:32767s},{id:5s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:elytra""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:netherite_leggings""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:netherite_boots""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:2s,lvl:32767s},{id:7s,lvl:32767s},{id:28s,lvl:1s}]}}],CustomName:""\"Epic BadMan User""\",Persistent:1b,Invulnerable:1b,Dead:1b,Mainhand:[{Count:1b,Damage:0s,Name:""\"minecraft:netherite_sword""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:9s,lvl:32767s},{id:13s,lvl:32767s},{id:14s,lvl:32767s},{id:28s,lvl:1s},{id:12s,lvl:32767s}]}}],definitions:[""\"+minecraft:" + cmd + "\"],identifier:""\"minecraft:" + cmd + "\",TicksLeftToStay:1}}],ench:[{id:28s,lvl:1s}],RepairCost:0,display:{Lore:[""\"§b§lBy BadMan Client""\"],Name:""\"§g§lMob Spawner Bee Nest""\"}";
	yot->setUserData(std::move(Mojangson::parseTag(tag)));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, yot, nullptr, 507, 99999));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sBadMan%s] %sPlace the beenest to spawn a god mob!", GOLD, WHITE, GREEN);
	return true;

}

	if (args->at(1) == "invis") {
	assertTrue(args->size() > 2);
	std::ostringstream os;
	for (int i = 2; i < args->size(); i++) {
		if (i > 1)
			os << "";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("movingblock")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{movingEntity:{id:""\"Beehive""\",Occupants:[{ActorIdentifier:""\"minecraft:" + cmd + "<>\",SaveData:{Armor:[{Count:1b,Damage:0s,Name:""\"minecraft:netherite_helmet""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:8s,lvl:32767s},{id:6s,lvl:32767s},{id:5s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:elytra""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:netherite_leggings""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:netherite_boots""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:2s,lvl:32767s},{id:7s,lvl:32767s},{id:28s,lvl:1s}]}}],CustomName:""\"Epic BadMan User""\",Persistent:1b,Invulnerable:1b,Dead:1b,Mainhand:[{Count:1b,Damage:0s,Name:""\"minecraft:netherite_sword""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:9s,lvl:32767s},{id:13s,lvl:32767s},{id:14s,lvl:32767s},{id:28s,lvl:1s},{id:12s,lvl:32767s}]}}],definitions:[""\"+minecraft:" + cmd + "\"],identifier:""\"minecraft:" + cmd + "\",TicksLeftToStay:1}}]},pistonPosX:0,movingBlock:{name:""\"minecraft:bee_nest""\"},pistonPosY:0,pistonPosZ:0,ench:[{id:28s,lvl:1s}],display:{Name:""\"§g§lMob Spawner Invis Beenest Bypass""\",Lore:[""\"§b§lby BadMan Client""\"]}}";
	yot->setUserData(std::move(Mojangson::parseTag(tag)));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, yot, nullptr, 507, 99999));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sBadMan%s] %sPlace the movingblock to spawn a invis beenest that spawns a god mob!", GOLD, WHITE, GREEN);
	return true;

}
	if (args->at(1) == "bypass") {
	assertTrue(args->size() > 2);
	std::ostringstream os;
	for (int i = 2; i < args->size(); i++) {
		if (i > 1)
			os << "";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("movingblock")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{movingEntity:{id:""\"Beehive""\",Occupants:[{ActorIdentifier:""\"minecraft:" + cmd + "<>\",SaveData:{Armor:[{Count:1b,Damage:0s,Name:""\"minecraft:netherite_helmet""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:8s,lvl:32767s},{id:6s,lvl:32767s},{id:5s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:elytra""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:netherite_leggings""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:28s,lvl:1s}]}},{Count:1b,Damage:0s,Name:""\"minecraft:netherite_boots""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:0s,lvl:32767s},{id:1s,lvl:32767s},{id:3s,lvl:32767s},{id:4s,lvl:32767s},{id:2s,lvl:32767s},{id:7s,lvl:32767s},{id:28s,lvl:1s}]}}],CustomName:""\"Epic BadMan User""\",Persistent:1b,Invulnerable:1b,Dead:1b,Mainhand:[{Count:1b,Damage:0s,Name:""\"minecraft:netherite_sword""\",tag:{Damage:0,Unbreakable:1b,ench:[{id:9s,lvl:32767s},{id:13s,lvl:32767s},{id:14s,lvl:32767s},{id:28s,lvl:1s},{id:12s,lvl:32767s}]}}],definitions:[""\"+minecraft:" + cmd + "\"],identifier:""\"minecraft:" + cmd + "\",TicksLeftToStay:1}}]},pistonPosX:0,movingBlock:{name:""\"minecraft:bee_nest""\"},pistonPosY:0,pistonPosZ:0,ench:[{id:28s,lvl:1s}],display:{Name:""\"§g§lMob Spawner Beenest Bypass""\",Lore:[""\"§b§lby BadMan Client""\"]}}";
	yot->setUserData(std::move(Mojangson::parseTag(tag)));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, yot, nullptr, 507, 99999));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sBadMan%s] %sPlace the movingblock to spawn a beenest that spawns a god mob!", GOLD, WHITE, GREEN);
	return true;
	}
}