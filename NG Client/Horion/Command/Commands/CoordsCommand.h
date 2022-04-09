#pragma once

#include "ICommand.h"

class CoordsCommand : public IMCCommand {
public:
	CoordsCommand() : IMCCommand("coords", "Prints your coordinates", "X, Y, Z") {
		registerAlias("pos");
	}
	~CoordsCommand(){};

	bool execute(std::vector<std::string>* args) {
		vec3* pos = g_Data.getLocalPlayer()->getPos();
		float yPos = pos->y - 1.62f;
		clientMessageF("[%sNG%s] %sX: %.2f Y: %.2f Z: %.2f", GOLD, WHITE, LIGHT_PURPLE, pos->x, yPos /* eye height */, pos->z);
		return true;
	}
};