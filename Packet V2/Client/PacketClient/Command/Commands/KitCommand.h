#pragma once
#include "ICommand.h"

class KitCommand : public IMCCommand {
public:
	KitCommand();
	~KitCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};