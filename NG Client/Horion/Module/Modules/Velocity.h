#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Velocity : public IModule {
public:

	std::string name = "Velocity";
	std::string fullname = "Velocity";

	float xModifier = 0.f;
	float yModifier = 0.f;

	Velocity() : IModule(0x0, Category::MOVEMENT, "Replaces Sounds") {
		registerFloatSetting("Linear Modifier", &xModifier, xModifier, 0.f, 1.f);
		registerFloatSetting("Height Modifier", &yModifier, yModifier, 0.f, 1.f);
};
	~Velocity(){};

	virtual const char* getModuleName() override {
		name = std::string("Velocity [") + std::to_string((int)xModifier) + std::string(".") + std::to_string((int)(xModifier * 10) - ((int)xModifier * 10));
		fullname = name + std::string("% ") + std::to_string((int)yModifier) + std::string(".") + std::to_string((int)(yModifier * 10) - ((int)yModifier * 10)) + std::string("%]");
		return fullname.c_str();
	}
};