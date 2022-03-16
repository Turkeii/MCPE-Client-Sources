#pragma once
#include "Module.h"
class NoSlowDown : public IModule {
private:
	//uint8_t* targetAddress = 0;
	//uint8_t* opcode1 = 0;

public:
	NoSlowDown();
	~NoSlowDown();
	//static void patchBytes(BYTE* dst, BYTE* src, unsigned int size);
	//void targetAddress();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
