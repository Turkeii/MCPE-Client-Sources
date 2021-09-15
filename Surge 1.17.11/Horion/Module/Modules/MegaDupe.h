#pragma once
#include "Module.h"
class MegaDupe : public IModule {
private:
	bool sorted = false;

	std::vector<int> findStackableItems();
	std::vector<int> findUselessItems();
	bool isLastItem(C_Item* item);

	bool keepTools = false;
	bool keepArmor = false;
	bool keepBlocks = false;
	bool keepFood = false;
	float amount = 64;
	float slotnum;

	bool openInv = false;
	bool autoSort = false;

public:
	bool stackIsUseful(C_ItemStack* itemStack);
	MegaDupe();
	~MegaDupe();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
