#include "DupeCommand.h"

DupeCommand::DupeCommand() : IMCCommand("dupe", "Duplicates the item in hand", "<count> <mode: give / offhand : 1/0>")
{
}

DupeCommand::~DupeCommand()
{
}
std::byte isGive;
bool DupeCommand::execute(std::vector<std::string>* args)
{
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	auto transactionManager = g_Data.getLocalPlayer()->getTransactionManager();

	int selectedSlot = supplies->selectedHotbarSlot;
	C_ItemStack* item = inv->getItemStack(selectedSlot);

	int count = item->count;
	
	isGive |= std::byte(1);

	if (args->size() > 1)
		item->count = assertInt(args->at(1));
	if (args->size() > 2)
		isGive |= static_cast<bool>(assertInt(args->at(2))) ? std::byte(1) : std::byte(0);

	if ((isGive & std::byte(1)) == std::byte(1))
	{
		int slot = inv->getFirstEmptySlot();

		C_InventoryAction* firstAction = nullptr;
		C_InventoryAction* secondAction = nullptr;

		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "mco.mineplex.com") == 0)
		{
			firstAction = new C_InventoryAction(slot, nullptr, item, 32512);
			secondAction = new C_InventoryAction(0, item, nullptr, 156, 100);
		}
		else
		{
			firstAction = new C_InventoryAction(0, item, nullptr, 507, 99999);
			secondAction = new C_InventoryAction(slot, nullptr, item);
		}

		transactionManager->addInventoryAction(*firstAction);
		transactionManager->addInventoryAction(*secondAction);

		inv->addItemToFirstEmptySlot(item);
	}
	else
		g_Data.getLocalPlayer()->setOffhandSlot(item);

	if (args->size() > 1)
		item->count = count;

	clientMessageF("%sSuccessfully duplicated the item!", GREEN);
	return true;
}
