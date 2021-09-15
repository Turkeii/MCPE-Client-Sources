#pragma once
#include "ICommand.h"

class GodmodeCommand : public IMCCommand {
public:
	GodmodeCommand();
	~GodmodeCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
