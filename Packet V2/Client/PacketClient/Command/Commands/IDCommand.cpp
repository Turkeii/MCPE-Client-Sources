#include "IDCommand.h"

IDCommand::IDCommand() : IMCCommand("id", "Get item/block/entity IDS", "<pointing/holding>") {
}

IDCommand::~IDCommand() {
}

bool IDCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	std::string option = args->at(1);
	std::transform(option.begin(), option.end(), option.begin(), ::tolower);

	if (args->at(1) == "pointing") {
		PointingStruct* pointingStruct = g_Data.getLocalPlayer()->pointingStruct;
		C_Block* block = g_Data.getLocalPlayer()->region->getBlock(pointingStruct->block);
		int blockID = (int)block->toLegacy()->blockId;
		char* blockName = block->toLegacy()->name.getText();

		if (g_Data.getClientInstance()->getPointerStruct()->hasEntity()) {
			C_Entity* entity = g_Data.getClientInstance()->getPointerStruct()->getEntity();
			if (entity != nullptr) {
				std::string entityName = entity->getNameTag()->getText();
				std::string entityID = std::to_string(entity->getEntityTypeId());
				clientMessageF("[Packet] %sEntity Name: %s", entityName.c_str());
				clientMessageF("[Packet] %sEntity ID: %d", entityID.c_str());
			}
		} else {
			clientMessageF("[Packet] Block Name: %s", blockName);
			clientMessageF("[Packet] Block ID: %d", blockID);
		}
		return true;
	} else if (args->at(1) == "holding") {
		clientMessageF("[Packet] ID: s");
		return true;
	}
	return false;
}