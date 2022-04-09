#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class NoFriends : public IModule {
public:
	NoFriends() : IModule(0x0, Category::PLAYER, "Ignores friend list check"){

				  };
	~NoFriends(){};

	virtual const char* getModuleName() override {
		return "NoFriends";
	}
};