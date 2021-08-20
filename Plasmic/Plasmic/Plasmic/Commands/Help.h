#pragma once
#include "../Module.h"

class Help : public Command {

public:

	Help() : Command("help", mltext("Shows a list of command", "Vous montre une liste de commande")) {
	
	}

	virtual void execute(const char* args) override {
		game::sendClientChat("");
		game::sendClientChat("");
		game::sendClientChat("");

		char helpmsg[100];
		for (uint16_t i = 0; i < CommandManager::commands.size(); i++) {
			sprintf(helpmsg, ".%s - %s", CommandManager::commands[i]->command, CommandManager::commands[i]->helpMessage);
			game::sendClientChat(helpmsg);
		}
	}
};