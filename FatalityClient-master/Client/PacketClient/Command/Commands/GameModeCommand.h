#pragma once
#include "ICommand.h"
class GameModeCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	GameModeCommand();
};
