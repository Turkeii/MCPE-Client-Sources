#pragma once
#include "Module.h"
#include "../../Command/CommandMgr.h"
class ForceTotem : public IModule {
private:
	std::map<std::string, int> enchantMap;
	int EnchantLevel = 32767;
	bool Enchant = false;
	bool Old = false;

public:
	ForceTotem();
	~ForceTotem();

	
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};
