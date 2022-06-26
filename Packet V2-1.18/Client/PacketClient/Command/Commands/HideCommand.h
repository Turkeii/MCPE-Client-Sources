#pragma once
#include "ICommand.h"

class HideCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	HideCommand();
};
