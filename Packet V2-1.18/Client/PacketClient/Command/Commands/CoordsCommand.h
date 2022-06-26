#pragma once
#include "ICommand.h"

class CoordsCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	CoordsCommand();
};
