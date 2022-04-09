#include "NbtCommand.h"
#include "../../../Utils/Utils.h"
#include "../../../Utils/Logger.h"
#include "../../../SDK/Tag.h"
#include "../../Module/ModuleManager.h"

NbtCommand::NbtCommand() : IMCCommand("nbt", "read and write NBT tags to/from your clipboard (You have to point at an entity/block entity)", "<read/write/load>") {
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
	PointingStruct* pointingStruct = g_Data.getLocalPlayer()->pointingStruct;
	C_BlockActor* blockActor = g_Data.getLocalPlayer()->region->getBlockEntity(pointingStruct->block);
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	C_InventoryTransactionManager* manager = g_Data.getLocalPlayer()->getTransactionManager();
	C_ItemStack* item = g_Data.getLocalPlayer()->getSelectedItem();

	if (args->at(1) == "read" || args->at(1) == "save") {
		std::unique_ptr<CompoundTag> tag = std::make_unique<CompoundTag>();
		std::stringstream build;

		if (args->at(1) == "save" && item != nullptr) {
			auto* boy = new CompoundTag();
			item->save(&boy);
			boy->write(build);
			delete boy;
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
		Utils::setClipboardText(builtStr);
		clientMessageF("%s%s", GREEN, "CompoundTag copied:");
		clientMessageF(builtStr.c_str());
	} else if ((args->at(1) == "write" || args->at(1) == "load") && item) {
		if (!Packetz->isEnabled()) {
			//Packetz->setEnabled(true);
		}
		std::string tag;
		if(isRaw){
			std::ostringstream os;
			for (int i = 2; i < args->size(); i++) {
				if (i > 2)
					os << " ";
				os << args->at(i);
			}
			tag = os.str();
		}else
			tag = Utils::getClipboardText();

		if (tag.size() > 1 && tag.front() == MojangsonToken::COMPOUND_START.getSymbol() && tag.back() == MojangsonToken::COMPOUND_END.getSymbol()) {
				if (args->at(1) == "write") {
					item->setUserData(std::move(Mojangson::parseTag(tag)));
					manager->addInventoryAction(C_InventoryAction(0, nullptr, item, 507, 99999));
				} else if (args->at(1) == "load") {
				std::unique_ptr<Tag> result = std::move(Mojangson::parseTag(tag));
				item->fromTag(*result.get());
				item->count = 64;
				memset(&result, 0, sizeof(std::unique_ptr<Tag>));
			}
		} else {
			clientMessageF("%sInvalid NBT tag!", RED);
			return true;
		}
			ItemDescriptor desc((*item->item)->itemId, *(short*)(&item->count - 2));
			g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, &desc, nullptr, item, nullptr, 1, 507, 99999));

		clientMessageF("%s%s", GREEN, "Successfully loaded mojangson !");

			if (Packetz->isEnabled()) {
				//Packetz->setEnabled(false);
			}
		//dupe item
		C_InventoryAction* firstAction = nullptr;
		auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr))  // Item in hand?
			return false;
		auto transactionMan = g_Data.getLocalPlayer()->getTransactionManager();
		int count = item->count;
		bool isGive = true;
		firstAction = new C_InventoryAction(0, item, nullptr, 507, 99999);
		transactionMan->addInventoryAction(*firstAction);
		inv->addItemToFirstEmptySlot(item);
	} else {
		clientMessageF("%s%s", RED, "Couldn't execute command correctly");
		if (Packetz->isEnabled()) {
			//Packetz->setEnabled(false);
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
