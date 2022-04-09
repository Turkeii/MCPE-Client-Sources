#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Watermark : public IModule {
private:
public:
	std::string message = "Packet Client";
	inline std::string& getMessage() { return message; };
	bool firstLetter = false;
	float opacity = 0.6f;

	Watermark();
	~Watermark();

	SettingEnum mode = this;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};