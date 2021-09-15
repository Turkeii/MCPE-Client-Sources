#pragma once
#include "Module.h"
class SuperSaiyan : public IModule {
public:
	int amount = 1;
	SuperSaiyan();
	~SuperSaiyan();

private:
	virtual const char* getModuleName() override;
	void onLevelRender();
};