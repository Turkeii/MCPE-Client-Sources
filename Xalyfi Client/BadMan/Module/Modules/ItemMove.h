#pragma once
#include "Module.h"

class ItemMove : public IModule {
public:	
	int place = 0;
	SettingEnum whatitem;

	ItemMove();
	~ItemMove();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
