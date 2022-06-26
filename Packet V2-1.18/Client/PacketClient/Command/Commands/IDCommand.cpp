#include "IDCommand.h"
#include "pch.h"

IDCommand::IDCommand() : IMCCommand("id", "Get item/block/entity IDS", "<pointing/holding>") {
}

bool IDCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	std::string option = args->at(1);
	std::transform(option.begin(), option.end(), option.begin(), ::tolower);

	if (args->at(1) == "pointing") {
		PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(pointing->block);
		int blockID = (int)block->toLegacy()->blockId;
		char* blockName = block->toLegacy()->name.getText();

		if (pointing->hasEntity()) {
			C_Entity* entity = pointing->getEntity();
			if (entity != nullptr) {
				std::string entityName = entity->getNameTag()->getText();
				std::string entityID = std::to_string(entity->getEntityTypeId());
				clientMessageF("[Packet] Entity Name: %s", entityName.c_str());
				clientMessageF("[Packet] Entity ID: %s", entityID.c_str());
			}
		} else {
			clientMessageF("[Packet] Block Name: %s", blockName);
			clientMessageF("[Packet] Block ID: %d", blockID);
		}
		return true;
	} else if (args->at(1) == "holding") {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		auto n = supplies->selectedHotbarSlot;
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			auto id = stack->getItem()->itemId;
			char* name = stack->getItem()->name.getText();
			g_Data.getGuiData()->displayClientMessageF("[Packet] Item Name: %s", name);
			g_Data.getGuiData()->displayClientMessageF("[Packet] Item ID: %lld", id);
		}
		return true;
	}
	return false;
}