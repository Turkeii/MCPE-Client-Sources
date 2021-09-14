#pragma once
#include "ICommand.h"
class YTCommand : public IMCCommand {
public:
	YTCommand();
	~YTCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
