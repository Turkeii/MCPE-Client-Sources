#pragma once
#include "ICommand.h"

class DemiGodPot : public IMCCommand {
public:
	DemiGodPot();
	~DemiGodPot();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
