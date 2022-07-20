#include "Module/Modules/Module.h"
#include "DrawUtils.h"
#include "Module/ModuleManager.h"
#include "Command/Commands/ICommand.h"

std::string playerName = std::string(g_Data.getLocalPlayer()->getNameTag()->getText());

class Login : public IMCCommand {
public:
	Login();
	~Login();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;

	bool Login::execute(std::vector<std::string>* args) {
		if (playerName != "ShinX54") {
			GameData::terminate();
			return true;
		}
	}
};






