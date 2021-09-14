#pragma once
#include "ICommand.h"
class PlayerLoggerCommand : public IMCCommand {
public:
	PlayerLoggerCommand();
	~PlayerLoggerCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};