#pragma once
#include "Module.h"
class NoSlowDown : public IModule {
private:
	uint8_t* opcode = 0;
	uint8_t* opcode1 = 0;
	uint8_t* opcode2 = 0;
	uint8_t* opcode3 = 0;
	uint8_t* sneakopcode = 0;

	bool keyPressed = false;

public:
	bool noWeb = false;
	bool silentSneak = false;
	bool guiMove = false;
	bool spoof = false;
	bool antii = false;
	float speed1 = 10.f;
	SettingEnum noSlow;

	NoSlowDown();
	~NoSlowDown();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
