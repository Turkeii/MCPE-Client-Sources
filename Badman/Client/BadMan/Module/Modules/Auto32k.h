#pragma once
#include "../../Command/CommandMgr.h"
#include "Module.h"
class Auto32k : public IModule {
private:
	std::map<std::string, int> enchantMap;
	int EnchantmentLevel = 32767;

public:
	Auto32k();
	~Auto32k();

	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};
