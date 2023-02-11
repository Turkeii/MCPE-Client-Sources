#include "CoordsCommand.h"
#include "pch.h"

CoordsCommand::CoordsCommand() : IMCCommand("coords", "Prints your coordinates", "") {
	registerAlias("pos");
}

bool CoordsCommand::execute(std::vector<std::string>* args) {
	vec3_t* pos = g_Data.getLocalPlayer()->getPos();
	float yPos = pos->y - 1.62f;
	clientMessageF("[F] %sX: %.2f Y: %.2f Z: %.2f", RED, pos->x, yPos /* eye height */, pos->z);
	return true;
}
