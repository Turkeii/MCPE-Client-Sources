#pragma once
#include "ICommand.h"

class TestCommand : public IMCCommand {
public:
	void listEnts() {
		PointingStruct* pointingStruct = g_Data.getLocalPlayer()->pointingStruct;
		auto entity = pointingStruct->getEntity();
		if (entity != nullptr) {
			auto id = entity->getUniqueId();
			char* name = entity->getNameTag()->getText();
			g_Data.getGuiData()->displayClientMessageF("---------------");
			g_Data.getGuiData()->displayClientMessageF("Entity Name: %s", name);
			g_Data.getGuiData()->displayClientMessageF("Entity ID: %lld", id);
			g_Data.getGuiData()->displayClientMessageF("---------------");
		}
	}

	void itemId() {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv = supplies->inventory;
		auto n = supplies->selectedHotbarSlot;
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			auto id = stack->getItem()->itemId;
			char* name = stack->getItem()->name.getText();
			g_Data.getGuiData()->displayClientMessageF("---------------");
			g_Data.getGuiData()->displayClientMessageF("Item Name: %s", name);
			g_Data.getGuiData()->displayClientMessageF("Item ID: %lld", id);
			g_Data.getGuiData()->displayClientMessageF("---------------");
		}
	}

	void showAimedBlockInfo() {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		PointingStruct* pointingStruct = g_Data.getLocalPlayer()->pointingStruct;
		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(pointingStruct->block);
		auto entity = pointingStruct->getEntity();
		if (block != nullptr && pointingStruct != nullptr && entity == nullptr && block->blockLegacy->blockId != 7) {
			char* name = block->toLegacy()->name.getText();
			auto id = block->toLegacy()->blockId;
			g_Data.getGuiData()->displayClientMessageF("---------------");
			g_Data.getGuiData()->displayClientMessageF("Block Name: %s", name);
			g_Data.getGuiData()->displayClientMessageF("Block ID: %lld", id);
			g_Data.getGuiData()->displayClientMessageF("---------------");
		}
	}
	TestCommand() : IMCCommand("test", "Test for Debugging purposes", ""){};
	~TestCommand(){};

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		listEnts();
		itemId();
		showAimedBlockInfo();
		return true;
	}
};