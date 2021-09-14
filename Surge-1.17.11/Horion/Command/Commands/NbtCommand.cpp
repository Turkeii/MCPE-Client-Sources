#include "NbtCommand.h"
#include "../../../Utils/Utils.h"
#include "../../../Utils/Logger.h"
#include "../../../SDK/Tag.h"
#include "../../Module/ModuleManager.h"

NbtCommand::NbtCommand() : IMCCommand("nbt", "read and write NBT tags to/from your clipboard (You have to point at an entity/block entity)", "<read/write/load/save>") {
	registerAlias("nbtraw");
}

NbtCommand::~NbtCommand() {
}

bool NbtCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	bool isRaw = args->at(0) == "nbtraw";
	if(isRaw){
		assertTrue(args->at(1) == "write");
		assertTrue(args->size() > 2);
	}
	static auto Packetz = moduleMgr->getModule<NoPacket>();
	PointingStruct* pointingStruct = g_Data.getClientInstance()->getPointerStruct();
	C_BlockActor* blockActor = g_Data.getLocalPlayer()->region->getBlockEntity(pointingStruct->block);
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* item = g_Data.getLocalPlayer()->getSelectedItem();

	if (args->at(1) == "read" || args->at(1) == "save") {
		static auto Packetz = moduleMgr->getModule<NoPacket>();
		//if (!Packetz->isEnabled()) {
		//	Packetz->setEnabled(true);
		//}
		std::unique_ptr<CompoundTag> tag = std::make_unique<CompoundTag>();
		std::stringstream build;

		if (args->at(1) == "save" && item != nullptr) {
			if (pointingStruct->getEntity() != nullptr) {
				if (g_Data.getRakNetInstance()->serverIp.getTextLength() >= 1) {
					clientMessageF("%sNBT tags for mobs only works in local world!", RED);
					return true;
				}
				pointingStruct->getEntity()->save(tag.get());
				tag->write(build);
			} else if (blockActor != nullptr) {
				blockActor->save(tag.get());
				tag->write(build);
			} else if (item != nullptr && item->tag != nullptr) {
				item->tag->write(build);
			} else {
				clientMessageF("%sCouldn't find NBT tags!", RED);
				return true;
			}
		} else {
			if (pointingStruct->getEntity() != nullptr) {
				if (g_Data.getRakNetInstance()->serverIp.getTextLength() >= 1) {
					clientMessageF("%sNBT tags for mobs only works in local world!", RED);
					return true;
				}
				pointingStruct->getEntity()->save(tag.get());
				tag->write(build);
			} else if (blockActor != nullptr) {
				blockActor->save(tag.get());
				tag->write(build);
			} else if (item != nullptr && item->tag != nullptr) {
				item->tag->write(build);
			} else {
				clientMessageF("%sCouldn't find NBT tags!", RED);
				return true;
			}
		}

		auto builtStr = build.str();
		if (args->at(1) == "save") {
			Utils::setClipboardText("{Count:1b,Damage:15s,Name:\"minecraft:Shulker_box\",tag:" + builtStr + "}");
		} else {
			Utils::setClipboardText(builtStr);
		}
		clientMessageF("%s%s", GREEN, "CompoundTag copied:");
		clientMessageF(builtStr.c_str());
	} else if ((args->at(1) == "write") && item) {
		clientMessageF("This Does Not Work. Pls Use .kit write insted");
		std::string tag;
		if(isRaw){
			std::ostringstream os;
			for (int i = 2; i < args->size(); i++) {
				if (i > 2)
					os << " ";
				os << args->at(i);
			}

			tag = os.str();
		}else{
			tag = Utils::getClipboardText();
		}

		{
			manager->addInventoryAction(C_InventoryAction(supplies->selectedHotbarSlot, item, nullptr));
			manager->addInventoryAction(C_InventoryAction(0, nullptr, item, 507, 99999));
		}

		if (tag.size() > 1 && tag.front() == MojangsonToken::COMPOUND_START.getSymbol() && tag.back() == MojangsonToken::COMPOUND_END.getSymbol()) {
			if (args->at(1) == "write")
				item->setUserData(std::move(Mojangson::parseTag(tag)));
		} else {
			if (args->at(1) == "write") {
				clientMessageF("%sInvalid NBT tag!", RED);
				return true;
			}
		}

		{
			manager->addInventoryAction(C_InventoryAction(0, item, nullptr, 507, 99999));
		//	manager->addInventoryAction(C_InventoryAction(supplies->selectedHotbarSlot, nullptr, item));
		}

		clientMessageF("%s%s", GREEN, "Successfully loaded mojangson !");
		inv->addItemToFirstEmptySlot(item);
	} else {
		//clientMessageF("%s%s", RED, "Could Not Execute Command Correctly");
	}
	//if (Packetz->isEnabled()) {
	//	Packetz->setEnabled(false);
	//}
	if (args->at(1) == "load") {
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("shulker_box")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::string tag = Utils::getClipboardText();
	yot->fromTag(*Mojangson::parseTag(tag));
	g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
	g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
	clientMessageF("[%sSurge%s] %sSucessfully Loaded Your NBT!", BLUE, WHITE, BLUE);
	return true;
	} else {
		if (args->at(1) == "load") {
			clientMessageF("%sInvalid NBT tag!", RED);
		}
	}
	return true;
}
const char* NbtCommand::getUsage(const char* alias) {
	if(strcmp(alias, "nbtraw") == 0){
		return "write <nbt>";
	}

	return IMCCommand::getUsage(alias);
}
