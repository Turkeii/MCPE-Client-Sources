#pragma once
#include "ICommand.h"
class TopCommand : public IMCCommand {
public:
	TopCommand() : IMCCommand("top", "Teleports to the nearest pocket of air above you - highly recommend against using this inside the Nether.", "[Hive]") {}
	~TopCommand(){};

	bool TopCommand::execute(std::vector<std::string>* args) {
		assertTrue(g_Data.getLocalPlayer() != nullptr);

		C_LocalPlayer* player = g_Data.getLocalPlayer();
		vec3 playerPos = player->eyePos0;
		bool groundAbove = false;  //Checking if ground above us.
		vec3 blockPos;

		for (int y(0); y < 256 - playerPos.y; ++y) {
			if (player->region->getBlock(vec3{playerPos.x, playerPos.y + y, playerPos.z})->toLegacy()->blockId != 0) {
				groundAbove = true;
				blockPos = vec3{playerPos.x, playerPos.y + y, playerPos.z};
				break;
			}
		}

		if (groundAbove) {
			for (int y(0); y < 256 - blockPos.y; ++y) {  //This time we're going through loop again, but continuing where we left off to find open air pocket.
				if ((player->region->getBlock(vec3{blockPos.x, blockPos.y + y, blockPos.z})->toLegacy()->blockId == 0) && (player->region->getBlock(vec3{blockPos.x, blockPos.y + y + 1, blockPos.z})->toLegacy()->blockId == 0)) {
					player->setPos(vec3{blockPos.x, blockPos.y + y + 1, blockPos.z});
					clientMessageF("Whoosh!");
					return true;
				}
			}
			clientMessageF("There is no open space above you!");
			return true;
		} else {
			clientMessageF("There are no blocks above you!");
			return true;
		}
	}
};