#pragma once
#include "ICommand.h"
#include "..\..\Config\ConfigManager.h"
#include "../../Config/SettingManager.h"

class ConfigCommand : public IMCCommand {
public:
	virtual bool execute(std::vector<std::string>* args) override;
	ConfigCommand();
};