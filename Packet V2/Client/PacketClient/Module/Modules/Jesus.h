#pragma once
#include "Module.h"
class Jesus : public IModule {
private:
	bool tryJesus(vec3_t blockBelow);
	float height = 0.5;
	bool smthwateridk = false;

public:
	Jesus();
	~Jesus();

	SettingEnum mode = this;
	std::string name = "Jesus";

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
};