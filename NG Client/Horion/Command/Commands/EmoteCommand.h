#pragma once
#include "ICommand.h"
class EmoteCommand : public IMCCommand {
public:
	EmoteCommand() : IMCCommand("emote", "plays an emote", "<Emote ID>") {
		registerAlias("e");
	}
	~EmoteCommand(){};

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		g_Data.getLocalPlayer()->playEmote(args->at(1));
		return true;
	}
};