#pragma once
#include "Module.h"
class InventoryCleaner : public IModule {
public:
	bool stackIsUseful(C_ItemStack* itemStack);
	InventoryCleaner();
	~InventoryCleaner();

	bool sorted = false;
	int delay = 0;
	int setDelay = 0;

	std::vector<int> findStackableItems();
	std::vector<int> findUselessItems();
	bool isLastItem(C_Item* item);

	bool keepTools = true;
	bool keepArmor = true;
	bool keepBlocks = true;
	bool keepFood = true;

	bool openInv = true;
	bool autoSort = false;
	bool keepBow = false;
	bool keepPick = false;
	bool keepShovel = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
