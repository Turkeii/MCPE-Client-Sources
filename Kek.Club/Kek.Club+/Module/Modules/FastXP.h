#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class FastXP : public IModule {
public:

	FastXP() : IModule(0x0, Category::PLAYER, "use things faster") {};
	~FastXP(){};

	void onTick(C_GameMode* gm) {
		C_ItemStack* stack = g_Data.getLocalPlayer()->getSelectedItem();
		if (GameData::isRightClickDown() && g_Data.canUseMoveKeys() && stack->item != nullptr && (*stack->item)->itemId != 0)
			gm->baseUseItem(*stack);
	}

	virtual const char* getModuleName() override {
		return "FastUse";
	}
};