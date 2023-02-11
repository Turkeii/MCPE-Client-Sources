#pragma once
#include "ICommand.h"

class NbtCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	const char* getUsage(const char* alias) override;
	NbtCommand();
};
