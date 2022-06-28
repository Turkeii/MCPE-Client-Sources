#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class NoRender : public IModule {
public:
	bool fire = false;
	bool weather = false;
	bool nausea = false;
	bool entities = false;
	bool blockEntities = false;
	bool particles = false;
	NoRender() : IModule(0x0, Category::VISUAL, "Stop certain animations & unrender objects/entities") {
		registerBoolSetting("Fire", &fire, fire);
		registerBoolSetting("Weather", &weather, weather);
		registerBoolSetting("Nausea", &nausea, nausea);
		registerBoolSetting("Entites", &entities, entities);
		registerBoolSetting("Block Entities", &blockEntities, blockEntities);
		registerBoolSetting("Particles", &particles, particles);
	}
	~NoRender() {}

	virtual const char* getModuleName() override {
		return "NoRender";
	}
};