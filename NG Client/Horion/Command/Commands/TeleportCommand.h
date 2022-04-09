#pragma once
#include "ICommand.h"
class TeleportCommand : public IMCCommand {
public:
	TeleportCommand() : IMCCommand("tp", "Teleports to coordinates", "<X> <Y> <Z>") {
		registerAlias("teleport");
		registerAlias("setpos");
	}
	~TeleportCommand(){};

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		assertTrue(g_Data.getLocalPlayer() != nullptr);
		assertTrue(args->size() >= 4);

		vec3 pos;
		pos.x = assertFloat(args->at(1));
		pos.y = assertFloat(args->at(2)) + 1;
		pos.z = assertFloat(args->at(3));

		g_Data.getLocalPlayer()->setPos(pos);
		clientMessageF("%sTeleported!", GREEN);
		return true;
	}
};