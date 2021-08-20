#pragma once
#include <vector>
#include <Windows.h>
#include "Module.h"


//it ends with a if that will get executed if the variable isn't null
#define getmodbyname(variableName, ModuleName, ModuleType) if (!variableName) variableName = (ModuleType*)ModuleManager::getModuleByName(ModuleName); if (variableName)
//it ends with a if that will get executed if the variable isn't null
#define getvisualmodbyname(variableName, ModuleName, ModuleType) if (!variableName) variableName = (ModuleType*)ModuleManager::getVisualModuleByName(ModuleName); if (variableName)


namespace ModuleManager {
	//List of modules
	extern std::vector<Module*> moduleList;
	//List of visual modules
	extern std::vector<VisualModule*> visualModuleList;
	extern Module GetClickGuiModule;


	extern void InitModules();

	//Free all the modules
	extern void DeInit();

	//don't forget to nullcheck!
	extern Module* getModuleByName(const char* NameOfTheModule);
	extern void BlockModuleByName(const char* NameOfTheModule);
	//don't forget to nullcheck!
	extern VisualModule* getVisualModuleByName(const char* NameOfTheModule);

};


namespace HookManager {

	extern std::vector<Hook*> hooks;

	extern void DisableAllHooks();
	extern void EnableAllHooks();
	extern Hook* GetHookByName(const char* NameOfTheHook);

	extern void DeInit();
	extern void init();
}


extern bool cmpAfterFirstSpace(const char* text, const char* compareTo);
extern bool cmpAfterFirstOrSecondSpace(const char* text, const char* compareTo);

extern bool endWith(const char* text, size_t textLenght, const char* compareTo, size_t compareToLenght);
extern bool startWith(const char* text, size_t textLenght, const char* compareTo, size_t compareToLenght);

namespace CommandManager {

	extern std::vector<Command*> commands;

	extern void onCommand(const char* text);

	extern void DeInit();
	extern void init();
}