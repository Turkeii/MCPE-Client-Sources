#include "IDinfoCommand.h"

IDinfoCommand::IDinfoCommand() : IMCCommand("id", "Get a item id by holding it or get a block id by looking at a block", "<block/item>") {
}

IDinfoCommand::~IDinfoCommand() {
	registerAlias("info");
}

bool IDinfoCommand::execute(std::vector<std::string>* args) {
	if (args->at(1) == "item") {
	int id = g_Data.getLocalPlayer()->getSelectedItemId();
		
	clientMessageF("Item ID: %d", id);
	
	}

	else if (args->at(1) == "block") {
	
	PointingStruct* pointingStruct = g_Data.getClientInstance()->getPointerStruct();
	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(pointingStruct->block);
	int id = block->toLegacy()->blockId;
	char* name = block->toLegacy()->name.getText();
	
	clientMessageF("Block Name: %s", name);
	
	clientMessageF("Block ID: %d", id);

	}
}