#include "RelativeTeleportCommand.h"

RelativeTeleportCommand::RelativeTeleportCommand() : IMCCommand("relativeteleport", "Teleports to coordinates relative to the Player", "<X> <Y> <Z>") {
	registerAlias("reltp");
	registerAlias("rtp");
	registerAlias("vclip");
}

RelativeTeleportCommand::~RelativeTeleportCommand() {
}

bool RelativeTeleportCommand::execute(std::vector<std::string>* args) {
	vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

	vec3_t pos;
	pos.x = 0.f + pPos.x;
	pos.y = 4.f + pPos.y;
	pos.z = 0.f + pPos.z;

	g_Data.getLocalPlayer()->setPos(pos);
	clientMessageF("%sTeleported!", GREEN);
	return true;
}
