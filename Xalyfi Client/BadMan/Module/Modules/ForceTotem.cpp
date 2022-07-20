#include "ForceTotem.h"

ForceTotem::ForceTotem() : IModule(0, Category::PLAYER, "Sets last Two Slots To a Totem Every Tick To Any LvL credits to 12brendon24") {
	Enchant = false;
	registerBoolSetting("Enchantments", &this->Enchant, this->Enchant);
	this->registerIntSetting("Enchantment lvl", &this->EnchantLevel, 32767, 0, 32767);
	enchantMap["protection"] = 0;
	enchantMap["fire_protection"] = 1;
	enchantMap["feather_falling"] = 2;
	enchantMap["blast_protection"] = 3;
	enchantMap["projectile_protection"] = 4;
	enchantMap["thorns"] = 5;
	enchantMap["respiration"] = 6;
	enchantMap["depth_strider"] = 7;
	enchantMap["aqua_affinity"] = 8;
	enchantMap["frost_walker"] = 25;
	enchantMap["sharpness"] = 9;
	enchantMap["smite"] = 10;
	enchantMap["bane_of_arthropods"] = 11;
	enchantMap["knockback"] = 12;
	enchantMap["fire_aspect"] = 13;
	enchantMap["looting"] = 14;
	enchantMap["channeling"] = 32;
	enchantMap["impaling"] = 29;
	enchantMap["loyalty"] = 31;
	enchantMap["riptide"] = 30;
	enchantMap["silktouch"] = 16;
	enchantMap["fortune"] = 18;
	enchantMap["unbreaking"] = 17;
	enchantMap["efficiency"] = 15;
	enchantMap["mending"] = 26;
	enchantMap["power"] = 19;
	enchantMap["punch"] = 20;
	enchantMap["flame"] = 21;
	enchantMap["infinity"] = 22;
	enchantMap["multishot"] = 33;
	enchantMap["quick_charge"] = 35;
	enchantMap["piercing"] = 34;
	enchantMap["luck_of_sea"] = 23;
	enchantMap["lure"] = 24;
	enchantMap["soul_speed"] = 36;
}

ForceTotem::~ForceTotem() {
}

const char* ForceTotem::getModuleName() {
	return ("ForceTotem");
}

void ForceTotem::onTick(C_GameMode* gm) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = g_Data.getLocalPlayer()->getSupplies()->inventory;
	C_ItemStack* handslot7 = inv->getItemStack(7);
	C_ItemStack* handslot8 = inv->getItemStack(8);
	if (handslot7->item == NULL or handslot8->item == NULL) {
		//if ((*handslot7->item)->itemId == 558 && (*handslot7->item)->itemId == 558) {
			if (Enchant) {
				int itemId = 0;  // ignore and just put the name in
				char count = 1;
				char itemData = 0;
				int enchantId = 0;
				int enchantLevel = EnchantLevel;

				bool isAuto = true;

				std::string data = "all";
				std::transform(data.begin(), data.end(), data.begin(), ::tolower);

				auto convertedString = enchantMap.find(data);
				if (convertedString != enchantMap.end())
					enchantId = convertedString->second;

				using getEnchantsFromUserData_t = void(__fastcall*)(C_ItemStack*, void*);
				using addEnchant_t = bool(__fastcall*)(void*, __int64);
				using saveEnchantsToUserData_t = void(__fastcall*)(C_ItemStack*, void*);

				static getEnchantsFromUserData_t getEnchantsFromUserData = reinterpret_cast<getEnchantsFromUserData_t>(FindSignature("48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B F2 48 8B D9 48 89 54 24 ? 33 FF 89 7C 24 ? E8 ? ? ? ? 84 C0"));
				static addEnchant_t addEnchant = reinterpret_cast<addEnchant_t>(FindSignature("48 89 5C 24 ?? 48 89 54 24 ?? 57 48 83 EC ?? 45 0F"));

				static saveEnchantsToUserData_t saveEnchantsToUserData = 0x0;
				if (!saveEnchantsToUserData) {
					saveEnchantsToUserData = reinterpret_cast<saveEnchantsToUserData_t>(FindSignature("48 89 5C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B FA 4C 8B C1 48 8B 41 08 48 85 C0"));
				}

				try {
					itemId = std::stoi("Totem");
				} catch (const std::invalid_argument&) {
				}

				C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
				C_Inventory* inv = supplies->inventory;
				C_ItemStack* yot = nullptr;
				auto transactionManager = g_Data.getLocalPlayer()->getTransactionManager();
				void* ItemPtr = malloc(0x8);
				void* idk = malloc(0x0);
				TextHolder tempText("Totem");
				C_Item*** cStack = ItemRegistry::lookUpByName(ItemPtr, idk, tempText);
				if (*cStack == nullptr) {
					clientMessageF("%sItem Name Incorrect Check Code Bro!", RED);
				}
				yot = new C_ItemStack(***cStack, count, itemData);
				free(ItemPtr);
				free(idk);
				if (yot != nullptr)
					yot->count = count;

				for (int i = 0; i < 38; i++) {
					void* EnchantData = malloc(0x60);
					if (EnchantData != nullptr)
						memset(EnchantData, 0x0, 0x60);

					getEnchantsFromUserData(yot, EnchantData);

					__int64 enchantPair = ((__int64)enchantLevel << 32) | i;

					if (addEnchant(EnchantData, enchantPair)) {  // Upper 4 bytes = level, lower 4 bytes = enchant type
						saveEnchantsToUserData(yot, EnchantData);
						__int64 proxy = reinterpret_cast<__int64>(g_Data.getLocalPlayer()->getSupplies());
						if (!*(uint8_t*)(proxy + 168))
							(*(void(__fastcall**)(unsigned long long, unsigned long long, C_ItemStack*))(**(unsigned long long**)(proxy + 176) + 72i64))(
								*(unsigned long long*)(proxy + 176),
								*(unsigned int*)(proxy + 16),
								yot);  // Player::selectItem

						//g_Data.getLocalPlayer()->sendInventory();
					}
					free(EnchantData);
				}
				int slot8 = 8;
				int slot7 = 7;

				C_InventoryAction* firstAction = nullptr;
				C_InventoryAction* secondAction = nullptr;
				C_InventoryAction* thirdAction = nullptr;
				C_InventoryAction* fourthAction = nullptr;
				firstAction = new C_InventoryAction(10, yot, nullptr, 507, 99999);
				secondAction = new C_InventoryAction(slot7, nullptr, yot);
				thirdAction = new C_InventoryAction(11, yot, nullptr, 507, 99999);
				fourthAction = new C_InventoryAction(slot8, nullptr, yot);

				transactionManager->addInventoryAction(*firstAction);
				transactionManager->addInventoryAction(*secondAction);
				transactionManager->addInventoryAction(*thirdAction);
				transactionManager->addInventoryAction(*fourthAction);

				delete firstAction;
				delete secondAction;
				delete thirdAction;
				delete fourthAction;

			} else {
				int itemId = 0;  // ignore and just put the name in
				char count = 1;
				char itemData = 0;

				try {
					itemId = std::stoi("Totem");
				} catch (const std::invalid_argument&) {
				}

				C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
				C_Inventory* inv = supplies->inventory;
				C_ItemStack* yot = nullptr;
				auto transactionManager = g_Data.getLocalPlayer()->getTransactionManager();
				void* ItemPtr = malloc(0x8);
				void* idk = malloc(0x0);
				TextHolder tempText("Totem");
				C_Item*** cStack = ItemRegistry::lookUpByName(ItemPtr, idk, tempText);
				if (*cStack == nullptr) {
					clientMessageF("%sItem Name Incorrect Check Code Bro!", RED);
				}
				yot = new C_ItemStack(***cStack, count, itemData);
				free(ItemPtr);
				free(idk);
				if (yot != nullptr)
					yot->count = count;

				int slot8 = 8;
				int slot7 = 7;

				C_InventoryAction* firstAction = nullptr;
				C_InventoryAction* secondAction = nullptr;
				C_InventoryAction* thirdAction = nullptr;
				C_InventoryAction* fourthAction = nullptr;
				firstAction = new C_InventoryAction(10, yot, nullptr, 507, 99999);
				secondAction = new C_InventoryAction(slot7, nullptr, yot);
				thirdAction = new C_InventoryAction(11, yot, nullptr, 507, 99999);
				fourthAction = new C_InventoryAction(slot8, nullptr, yot);

				transactionManager->addInventoryAction(*firstAction);
				transactionManager->addInventoryAction(*secondAction);
				transactionManager->addInventoryAction(*thirdAction);
				transactionManager->addInventoryAction(*fourthAction);

				delete firstAction;
				delete secondAction;
				delete thirdAction;
				delete fourthAction;
			}
		//}
	}
}
