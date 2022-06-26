#pragma once
#include "ICommand.h"
class PlayerTPCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	PlayerTPCommand();
};