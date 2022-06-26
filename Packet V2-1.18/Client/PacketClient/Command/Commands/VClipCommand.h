#pragma once
#include "ICommand.h"

class VClipCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	VClipCommand();
};
