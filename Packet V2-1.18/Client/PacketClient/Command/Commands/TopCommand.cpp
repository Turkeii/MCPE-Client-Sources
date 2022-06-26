#include "TopCommand.h"
#include "pch.h"

TopCommand::TopCommand() : IMCCommand("top", "Teleports to the nearest pocket of air above you - highly recommend against using this inside the Nether.", "") {
}

bool TopCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);

	C_LocalPlayer* player = g_Data.getLocalPlayer();
	vec3_t playerPos = player->eyePos0;
	bool groundAbove = false;  //Checking if ground above us.
	vec3_t blockPos;

	for (int y(0); y < 316 - playerPos.y; ++y) {
		if (player->region->getBlock(vec3_t{playerPos.x, playerPos.y + y, playerPos.z})->toLegacy()->blockId != 0) {
			groundAbove = true;
			blockPos = vec3_t{playerPos.x, playerPos.y + y, playerPos.z};
			break;
		}
	}

	if (groundAbove) {
		for (int y(0); y < 316 - blockPos.y; ++y) {  //This time we're going through loop again, but continuing where we left off to find open air pocket.
			if ((player->region->getBlock(vec3_t{blockPos.x, blockPos.y + y, blockPos.z})->toLegacy()->blockId == 0) && (player->region->getBlock(vec3_t{blockPos.x, blockPos.y + y + 1, blockPos.z})->toLegacy()->blockId == 0)) {
				player->setPos(vec3_t{blockPos.x, blockPos.y + y + 1, blockPos.z});
				clientMessageF("[Packet] Fuck!");
				return true;
			}
		}
		clientMessageF("[Packet] There is no open space above you!");
		return true;
	} else {
		clientMessageF("[Packet] There are no blocks above you!");
		return true;
	}
}