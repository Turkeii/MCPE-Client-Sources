#include "BindCommand.h"
#include "pch.h"

#include "../../Module/ModuleManager.h"

BindCommand::BindCommand() : IMCCommand("bind", "Binds modules to specific keys", "<module> <key>") {
	registerAlias("b");
}

bool BindCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() >= 2);
	std::string moduleName = args->at(1);
	assertTrue(moduleName.size() > 0);

	auto modOpt = moduleMgr->getModuleByName(moduleName);
	if (!modOpt.has_value()) {
		std::string textStr = "Could not find module with name: " + moduleName;
		//auto notification = g_Data.addNotification("Commands:", textStr);
		return true;
	}
	auto mod = modOpt.value();

	if (args->size() >= 3) {
		std::string key = args->at(2);

		assertTrue(key.size() > 0);

		if (key.size() > 1) {
			std::transform(key.begin(), key.end(), key.begin(), ::tolower);
			const char* needle = key.c_str();

			if (key == "none") {
				mod->setKeybind(0x0);
				std::string textStr = "Successfully unbound " + std::string(mod->getRawModuleName());
				//auto notification = g_Data.addNotification("Commands:", textStr);
				return true;
			}

			for (int i = 0; i < 190; i++) {
				const char* haystack = KeyNames[i];
				size_t len = strlen(needle) + 1;
				char* haystackLowercase = new char[len];
				for (int i = 0; i < len; i++)
					haystackLowercase[i] = tolower(haystack[i]);

				if (strcmp(needle, haystackLowercase) == 0) {
					mod->setKeybind(i);
					std::string textStr = std::string(mod->getRawModuleName()) + std::string(" is now bound to " + std::string(haystack));
					//auto notification = g_Data.addNotification("Commands:", textStr);
					delete[] haystackLowercase;
					return true;
				}
				delete[] haystackLowercase;
			}
			clientMessageF("%sInvalid key!", RED);
			return true;
		}

		int keyCode = (int)key.at(0);
		if (keyCode >= 0x61 && keyCode <= 0x7A)  // Convert key to lower case
			keyCode -= 0x20;

		if (keyCode >= 0x30 && keyCode <= 0x5A) {
			auto modOpt = moduleMgr->getModuleByName(moduleName);
			if (!modOpt.has_value()) {
				std::string textStr = "Could not find module with name: " + moduleName;
				//auto notification = g_Data.addNotification("Commands:", textStr);
			} else {
				modOpt.value()->setKeybind(keyCode);
				std::string textStr = std::string(mod->getRawModuleName()) + std::string(" is now bound to ") + std::to_string(keyCode);
				//auto notification = g_Data.addNotification("Commands:", textStr);
			}
		} else clientMessageF("%sInvalid Key! Outside of ASCII range: %X", RED, keyCode);
		return true;
	} else {
		std::string textStr = std::string(mod->getRawModuleName()) + std::string(" is currently bound to ") + Utils::getKeybindName(mod->getKeybind());
		//auto notification = g_Data.addNotification("Commands:", textStr);
		return true;
	}
	
}
