#pragma once
#include "../Module.h"


class SayCommand : public Command {

public:
	SayCommand() : Command("say", mltext("<message> send a message in the chat", "<message> envoie un message dans le chat")) {

	}

	virtual void execute(const char* args) override {
		//to not send empty messages (which are illegal)
		if (args[0] == 0)
			return;
		TextPacket newpacket(args, game::localPlayer->username, game::minecraftGame->xuid);
		game::sendPacket(&newpacket);
	}

};