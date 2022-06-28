#pragma once
#include "Module.h"
class MCP : public IModule {
private:
	bool hasClicked = false;

public:
	MCP();
	~MCP();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};