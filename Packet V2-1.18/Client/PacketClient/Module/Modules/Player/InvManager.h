#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class InvManager : public IModule {
private:
	bool sorted = false;

	std::vector<int> findStackableItems();
	std::vector<int> findUselessItems();
	bool isLastItem(C_Item* item);
	int Odelay = 0;
	int delay = 0;

	bool autoArmor = true;
	bool autoSort = true;
	bool clean = true;
	bool keep = true;
	// Slots
	int swordSlot = 1;
	int pickSlot = 2;
	int axeSlot = 3;
	int blockSlot = 9;

public:
	bool stackIsUseful(C_ItemStack* itemStack);
	std::vector<int> dropSlots;
	bool autoDisable = false;
	bool shouldSwing = false;
	bool swing = false;

	std::string name = "InvManager";
	SettingEnum mode = this;

	virtual const char* getRawModuleName() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLevelRender() override;
	InvManager();
};
