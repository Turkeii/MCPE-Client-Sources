#include "../../DrawUtils.h"
#include "SurroundV2.h"

void getObsidians() {
	auto supplies = g_Data.getLocalPlayer()->getSupplies();
	auto inv = supplies->inventory;  // g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies())->getItem()->itemID
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (stack->getItem()->isObsidian()) {  // select obsid
				supplies->selectedHotbarSlot = n;
				return;
			}
		}
	}
}

SurroundV2::SurroundV2() : IModule(0, Category::COMBAT, "Protecting yourself on expload") {
	blockmode = SettingEnum(this)
					.addEntry(EnumEntry("Normal", normal))
					.addEntry(EnumEntry("AntiCity", anticity));
	registerEnumSetting("Block Mode", &blockmode, normal);

	switchmode = SettingEnum(this)
				  .addEntry(EnumEntry("None", none))
				  .addEntry(EnumEntry("Normal", normal2))
				  .addEntry(EnumEntry("City-Switch", swap))
  		    	  .addEntry(EnumEntry("Spoof", spoof))
	              .addEntry(EnumEntry("OldSpoof", spoof_old));
	registerEnumSetting("SwitchMode", &switchmode, swap);

	rotations = SettingEnum(this)
				  .addEntry(EnumEntry("None", none1))
				  .addEntry(EnumEntry("Silent", silent))
				  .addEntry(EnumEntry("Client", client))
				  .addEntry(EnumEntry("Smooth", smooth));
	registerEnumSetting("Rotate", &rotations, smooth);

	registerBoolSetting("Render", &this->renderSurround, true);
	registerBoolSetting("BlockFace", &this->blockface, false);
	registerIntSetting("BlockPerTick", &this->BlockPerTick, this->BlockPerTick, 0, 10);
}

SurroundV2::~SurroundV2() {
}

const char* SurroundV2::getModuleName() {
	return "Surround";
}
const char* SurroundV2::getModeName() {
	return "";
}
bool SurroundV2::isSideEmpty() {
	bool sendBack = false;

	for (auto checkThis : sidesBlocksOnly) {
		auto playerOn = g_Data.getLocalPlayer()->getPos();
		auto rndOffPlayerOn = playerOn->floor();
		rndOffPlayerOn.y -= 1.f;

		auto calcSides = rndOffPlayerOn.add(checkThis);
		if (g_Data.getLocalPlayer()->region->getBlock(vec3_ti(calcSides))->toLegacy()->blockId == 0) {
			sendBack = true;
		}
	}
	if (sendBack == true) {
		return true;
	} else {
		return false;
	}
}

void SurroundV2::onMove(C_MoveInputHandler* hand) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (jumpDisable && hand->isJumping) this->setEnabled(false);
}

bool tryPlace2(vec3_t blkPlacement) {
	blkPlacement = blkPlacement.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blkPlacement));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blkPlacement);
		int i = 0;

		static std::vector<vec3_ti*> checklist;
		bool foundCandidate = false;
		if (checklist.empty()) {
			checklist.push_back(new vec3_ti(0, -1, 0));
			checklist.push_back(new vec3_ti(0, 1, 0));

			checklist.push_back(new vec3_ti(0, 0, -1));
			checklist.push_back(new vec3_ti(0, 0, 1));

			checklist.push_back(new vec3_ti(-1, 0, 0));
			checklist.push_back(new vec3_ti(1, 0, 0));
		}

		for (auto current : checklist) {
			vec3_ti calc = blok.sub(*current);
			bool Y = ((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable;
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate) {
			g_Data.getCGameMode()->buildBlock(&blok, i, false);
			return true;
		}
	}
	return false;
}

void SurroundV2::onEnable() {
	int switch1 = switchmode.GetSelectedEntry().GetValue();

	if (g_Data.getLocalPlayer() == nullptr) return;
	if (switch1 != none) getObsidians();
}
bool doReset = true;
std::vector<vec3_t> surrArr;
bool stopSwitch = false;

void SurroundV2::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	int switch1 = switchmode.GetSelectedEntry().GetValue();
	int place = blockmode.GetSelectedEntry().GetValue();
	int rot = rotations.GetSelectedEntry().GetValue();

	if (switch1 == spoof_old) getObsidians();

	if (switch1 == swap && isSideEmpty() && !stopSwitch) {  // auto grab blocks when side empty/broken
		auto box = g_Data.addInfoBox("Surround", "You have been citied! Replacing block");
		box->closeTimer = 3;

		origSlot = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
		getObsidians();

		stopSwitch = true;
		return;
	}

	if (surrArr.empty()) {
		doReset = true;
	} else {
		doReset = false;
	}
	if (doReset == true) {
		surrArr.clear();
	
		if (place == normal2) {
			for (auto surroundBlock : Normal3) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(surroundBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)  // if that *block* empty, don't place blok
					surrArr.push_back(surroundBlock);
			}
		} else {
			for (auto surroundBlock : antiCityBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(surroundBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)  // if that *block* empty, don't place blok
					surrArr.push_back(surroundBlock);
			}
		}
	}
	
	// LOCK PLAYER POS
	vec3_t yR = vec3_t(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
	yR.x += 0.5f;
	yR.z += 0.5f;
	g_Data.getLocalPlayer()->setPos(yR);

	// GET BUILD BLOCK
	if (isSideEmpty()) {
		for (auto surroundBlock : surrArr) {
			auto playerPosition = g_Data.getLocalPlayer()->getPos();
			auto flooredPos = playerPosition->floor();
			flooredPos.y -= 1.f;
			auto mathsBlockPos = flooredPos.add(surroundBlock);

			if (!blockface) {
				gm->buildBlock(&vec3_ti(mathsBlockPos.x, mathsBlockPos.y, mathsBlockPos.z), 0, false);  // ah so this causes the airplace
			} else if (blockface) {
				tryPlace2(mathsBlockPos);
			}

			surrArr.erase(surrArr.begin());
			break;
			auto mathsBlockPos2 = flooredPos.add(surroundBlock);
			return;

			angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(mathsBlockPos2);

			if (rot != none) {
				gm->player->bodyYaw = angle.y;
				gm->player->yawUnused1 = angle.y;

				// return;
			}
		}
	}

	if ((switch1 == swap && !isSideEmpty() && stopSwitch) || switch1 == spoof_old) {
		stopSwitch = false;
		g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = origSlot;
	}
}