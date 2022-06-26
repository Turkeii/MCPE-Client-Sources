#include "ShowCommand.h"
#include "../../Module/ModuleManager.h"
#include "pch.h"

ShowCommand::ShowCommand() : IMCCommand("show", "Unhide a module in the ArrayList", "<module>") {
	registerAlias("s");
}

bool ShowCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() >= 2);
	std::string moduleName = args->at(1);
	assertTrue(moduleName.size() > 0);

	if (args->at(1) == "all") {
		std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();
		for (auto& it : *moduleList) it->shouldHide = false;
		std::string textStr = "All modules are now visible!";
		//auto notification = g_Data.addNotification("Commands:", textStr); notification->duration = 5;
		return true;
	}
	else if (args->size() == 2) {
		auto modOpt = moduleMgr->getModuleByName(moduleName);
		if (!modOpt.has_value()) {
			std::string textStr = "Could not find module with name: " + moduleName;
			//auto notification = g_Data.addNotification("Commands:", textStr); notification->duration = 5;
			return true;
		}
		auto mod = modOpt.value();

		if (!mod->shouldHide) {
			std::string textStr = mod->getRawModuleName() + (std::string)" is already visible!";
			//auto notification = g_Data.addNotification("Commands:", textStr); notification->duration = 5;
			return true;
		}
		else {
			mod->shouldHide = false;
			std::string textStr = mod->getRawModuleName() + (std::string)" is now visible!";
		//	auto notification = g_Data.addNotification("Commands:", textStr); notification->duration = 5;
			return true;
		}
	}
	return false;
}