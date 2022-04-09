#include "RelativeTeleportCommand.h"

RelativeTeleportCommand::RelativeTeleportCommand() : IMCCommand("vclip", "Teleports to coordinates relative to the Player", "<X> <Y> <Z>") {
	registerAlias("v clip");
}

RelativeTeleportCommand::~RelativeTeleportCommand() {
}

bool RelativeTeleportCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() >= 4);

	vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

	vec3_t pos;
	pos.y = assertFloat(args->at(2)) + pPos.y;

	g_Data.getLocalPlayer()->setPos(pos);
	clientMessageF("%sTeleported!", GREEN);
	return true;
}