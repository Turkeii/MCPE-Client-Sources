#pragma once

#include "../Module.h"

class DebugCommand : public Command {
public:

	DebugCommand() : Command("debug", "used to debug") {}


	virtual void execute(const char* args) {

		if (!strcmp(args, "localplayer"))
			game::sendClientChat("LocalPlayer: %p", (void*)game::localPlayer);
		if (!strcmp(args, "player"))
			game::sendClientChat("LocalPlayer: %p", (void*)game::localPlayer);

		if (!strcmp(args, "clientinstance"))
			game::sendClientChat("ClientInstance: %p", (void*)game::clientinstance);
		if (!strcmp(args, "minecraftgame"))
			game::sendClientChat("MinecraftGame: %p", (void*)game::minecraftGame);


	}

};
