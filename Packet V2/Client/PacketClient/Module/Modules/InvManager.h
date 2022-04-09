#pragma once
#include "Module.h"
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
	int swordSlot = 0;
	int pickSlot = 1;
	int axeSlot = 2;
	int blockSlot = 9;

public:
	bool stackIsUseful(C_ItemStack* itemStack);
	bool autoDisable = false;

	InvManager();
	~InvManager();

		std::string name = "InvManager";
		SettingEnum mode = this;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
};
