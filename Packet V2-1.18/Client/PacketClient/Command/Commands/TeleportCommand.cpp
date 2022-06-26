#include "TeleportCommand.h"
#include "pch.h"

TeleportCommand::TeleportCommand() : IMCCommand("tp", "Teleports to coordinates", "<X> <Y> <Z>") {
	registerAlias("teleport");
	registerAlias("setpos");
}

bool TeleportCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() >= 4);

	vec3_t pos;
	pos.x = assertFloat(args->at(1));
	pos.y = assertFloat(args->at(2));
	pos.z = assertFloat(args->at(3));

	g_Data.getLocalPlayer()->setPos(pos);
	clientMessageF("[Packet] %sTeleported!", GREEN);
	return true;
}