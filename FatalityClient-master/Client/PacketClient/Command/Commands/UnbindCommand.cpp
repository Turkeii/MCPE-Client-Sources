#include "UnbindCommand.h"

#include "../../Module/ModuleManager.h"
#include "pch.h"

UnbindCommand::UnbindCommand() : IMCCommand("unbind", "unbind modules", "<module | all>") {
}

bool UnbindCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() >= 2);
	std::string moduleName = args->at(1);

	assertTrue(moduleName.size() > 0);

	if (moduleName == "all") {
		if (args->size() >= 3 && args->at(2) == "force") {
			auto lock = moduleMgr->lockModuleList();
			std::vector<std::shared_ptr<IModule>>* modules = moduleMgr->getModuleList();
			for (auto it = modules->begin(); it != modules->end(); ++it) {
				auto mod = *it;
				mod->setKeybind(0x0);
			}
			clientMessageF("[F] %sUnbound all modules!", RED);
		} else {
			clientMessageF("[F] %sAre you sure? This will unbind %sALL%s%s modules!", RED, BOLD, RESET, RED);
			clientMessageF("[F] %sUse %s.unbind all force%s to unbind all modules", RED, WHITE, RED);
		}
		return true;
	}

	auto modOpt = moduleMgr->getModuleByName(moduleName);
	if (!modOpt.has_value()) {
		clientMessageF("[F] %sCould not find module with name: %s", RED, moduleName.c_str());
		return true;
	} 

	auto mod = modOpt.value();
	mod->setKeybind(0x0);
	clientMessageF("[F] %sSuccessfully unbound %s!", RED, mod->getRawModuleName());
	return true;
}
