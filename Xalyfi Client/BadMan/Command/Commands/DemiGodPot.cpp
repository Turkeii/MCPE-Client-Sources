#include "DemiGodPot.h"

#include "../../../SDK/Tag.h"
#include "../../Module/ModuleManager.h"
#include <thread>

DemiGodPot::DemiGodPot() : IMCCommand("godpot", "Spawn a Beehive that gives you a demi-god potion", "<beehive> <beenest> <bypass> <strength>") {
	registerAlias("god");
}

DemiGodPot::~DemiGodPot() {
}

bool DemiGodPot::execute(std::vector<std::string>* args) {
	if (args->at(1) == "beehive") {
	assertTrue(args->size() > 1);
	std::ostringstream os;
	for (int i = 1; i < args->size(); i++) {
		if (i > 1)
			os << " ";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("beehive")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{Occupants:[{ActorIdentifier:""\"minecraft:area_effect_cloud<>""\",SaveData:{definitions:[""\"+minecraft:area_effect_cloud""\"],identifier:""\"minecraft:area_effect_cloud""\",Persistent:1b,Duration:60,ParticleId:66,Radius:2.0f,mobEffects:[{Amplifier:254b,Duration:30000000,Id:10b},{Amplifier:254b,Duration:30000000,Id:11b},{Amplifier:254b,Duration:30000000,Id:12b},{Amplifier:254b,Duration:30000000,Id:13b},{Ambient:0b,Amplifier:4b,Duration:30000000,Id:21b},{Amplifier:254b,Duration:30000000,Id:22b},{Amplifier:254b,Duration:30000000,Id:29b}],TicksLeftToStay:1}}],ench:[{id:28s,lvl:1s}],display:{Name:""\"§g§lDemi God Pot Beehive""\",Lore:[""\"§b§lby BadMan Client""\"]}}";
	yot->setUserData(std::move(Mojangson::parseTag(tag)));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, yot, nullptr, 507, 99999));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sBadMan%s] %sPlace the beehive to spawn a demi god potion!", GOLD, WHITE, GREEN);
	return true;

}

	if (args->at(1) == "beenest") {
	assertTrue(args->size() > 1);
	std::ostringstream os;
	for (int i = 1; i < args->size(); i++) {
		if (i > 1)
			os << " ";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("bee_nest")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{Occupants:[{ActorIdentifier:""\"minecraft:area_effect_cloud<>""\",SaveData:{definitions:[""\"+minecraft:area_effect_cloud""\"],identifier:""\"minecraft:area_effect_cloud""\",Persistent:1b,Duration:60,ParticleId:66,Radius:2.0f,mobEffects:[{Amplifier:254b,Duration:30000000,Id:10b},{Amplifier:254b,Duration:30000000,Id:11b},{Amplifier:254b,Duration:30000000,Id:12b},{Amplifier:254b,Duration:30000000,Id:13b},{Ambient:0b,Amplifier:4b,Duration:30000000,Id:21b},{Amplifier:254b,Duration:30000000,Id:22b},{Amplifier:254b,Duration:30000000,Id:29b}],TicksLeftToStay:1}}],ench:[{id:28s,lvl:1s}],display:{Name:""\"§g§lDemi God Pot Beenest""\",Lore:[""\"§b§lby BadMan Client""\"]}}";
	yot->setUserData(std::move(Mojangson::parseTag(tag)));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, yot, nullptr, 507, 99999));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sBadMan%s] %sPlace the beenest to spawn a demi god potion!", GOLD, WHITE, GREEN);
	return true;

}

	if (args->at(1) == "strength") {
	assertTrue(args->size() > 1);
	std::ostringstream os;
	for (int i = 1; i < args->size(); i++) {
		if (i > 1)
			os << " ";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("bee_nest")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{Occupants:[{ActorIdentifier:""\"minecraft:area_effect_cloud<>""\",SaveData:{definitions:[""\"+minecraft:area_effect_cloud""\"],identifier:""\"minecraft:area_effect_cloud""\",Persistent:1b,Duration:60,ParticleId:66,Radius:2.0f,mobEffects:[{Amplifier:25b,Duration:30000000,Id:5b},{Amplifier:254b,Duration:30000000,Id:10b},{Amplifier:254b,Duration:30000000,Id:11b},{Amplifier:254b,Duration:30000000,Id:12b},{Amplifier:254b,Duration:30000000,Id:13b},{Ambient:0b,Amplifier:4b,Duration:30000000,Id:21b},{Amplifier:254b,Duration:30000000,Id:22b},{Amplifier:254b,Duration:30000000,Id:29b}],TicksLeftToStay:1}}],ench:[{id:28s,lvl:1s}],display:{Name:""\"§g§lDemi God Pot Beenest""\",Lore:[""\"§b§lby BadMan Client""\"]}}";
	yot->setUserData(std::move(Mojangson::parseTag(tag)));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, yot, nullptr, 507, 99999));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sBadMan%s] %sPlace the beenest to spawn a demi god potion!", GOLD, WHITE, GREEN);
	return true;

}
	if (args->at(1) == "bypass") {
	assertTrue(args->size() > 1);
	std::ostringstream os;
	for (int i = 1; i < args->size(); i++) {
		if (i > 1)
			os << " ";
		os << args->at(i);
	}
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("movingblock")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string cmd = os.str();
	std::string tag = "{movingEntity:{id:""\"Beehive""\",Occupants:[{ActorIdentifier:""\"minecraft:area_effect_cloud<>""\",SaveData:{definitions:[""\"+minecraft:area_effect_cloud""\"],identifier:""\"minecraft:area_effect_cloud""\",Persistent:1b,Duration:60,ParticleId:66,Radius:2.0f,mobEffects:[{Amplifier:254b,Duration:30000000,Id:10b},{Amplifier:254b,Duration:30000000,Id:11b},{Amplifier:254b,Duration:30000000,Id:12b},{Amplifier:254b,Duration:30000000,Id:13b},{Ambient:0b,Amplifier:4b,Duration:30000000,Id:21b},{Amplifier:254b,Duration:30000000,Id:22b},{Amplifier:254b,Duration:30000000,Id:29b}],TicksLeftToStay:1}}]},pistonPosX:0,movingBlock:{name:""\"minecraft:bee_nest""\"},pistonPosY:0,pistonPosZ:0,ench:[{id:28s,lvl:1s}],display:{Name:""\"§g§lDemi God Pot Beenest Bypass""\",Lore:[""\"§b§lby BadMan Client""\"]}}";
	yot->setUserData(std::move(Mojangson::parseTag(tag)));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, yot, nullptr, 507, 99999));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(slot, nullptr, yot));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sBadMan%s] %sPlace the movingblock to spawn a beenest that spawns a demi god potion!", GOLD, WHITE, GREEN);
	return true;
	}
}
