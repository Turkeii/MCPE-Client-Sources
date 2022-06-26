#pragma once
#include "ICommand.h"

class TeleportCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	TeleportCommand();
};
