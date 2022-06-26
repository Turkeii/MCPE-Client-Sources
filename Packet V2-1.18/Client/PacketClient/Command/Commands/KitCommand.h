#pragma once
#include "ICommand.h"

class KitCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	KitCommand();
};