#pragma once
#include "../CommandMgr.h"
#include "ICommand.h"

class SetprefixCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	SetprefixCommand();
};
