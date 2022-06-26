#include "PanicCommand.h"
#include "../../Module/ModuleManager.h"
#include "pch.h"

PanicCommand::PanicCommand() : IMCCommand("panic", "Disables all Modules", "") {
}

bool PanicCommand::execute(std::vector<std::string>* args) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>> * modules = moduleMgr->getModuleList();

	for (auto it = modules->begin(); it != modules->end(); ++it) {
		auto mod = *it;
		mod->setEnabled(false);
	}
	clientMessageF("%sDisabled all Modules!", GREEN);
	return true;
}
