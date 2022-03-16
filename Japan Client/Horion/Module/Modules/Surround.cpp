
/*
#include "Surround.h"
#include "../../DrawUtils.h"

Surround::Surround() : IModule(0, Category::COMBAT, "Protect yourself from crystals :)") {
	registerBoolSetting("City-Switch", &this->citySwitch, true);
	registerBoolSetting("Render", &this->renderSurround, true);
	registerBoolSetting("First Swap", &this->blockSwap, true);
	registerBoolSetting("Rotations", &this->rotations, true);

	registerBoolSetting("AirPlace", &this->doAirplace, false);
}


Surround::~Surround() {
}

const char* Surround::getModuleName() {
	return "Surround";
}
const char* Surround::getModeName() {
	if (citySwitch)
		return "City-Switch";
	else
		return ("");
}
bool Surround::isFlashMode() {
	return false;
}

void getObby() {
	auto supplies = g_Data.getLocalPlayer()->getSupplies();
	auto inv = supplies->inventory;  // g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies())->getItem()->itemID
	for (int n = 0; n < 9; n++) {
		C_ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			if (stack->getItem()->itemId == 49) {  // select obsid
				supplies->selectedHotbarSlot = n;
				return;
			}
		}
	}
}

bool Surround::isSideEmpty() {
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
	}
	else {return false;}
}

void Surround::onMove(C_MoveInputHandler* hand) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (jumpDisable && hand->isJumping) this->setEnabled(false);
}

bool tryPlace(vec3_t blkPlacement) {
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

void Surround::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr) return;
	origSlot = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
	getObby();
	swapChecker = 1;
}

bool doReset = true;
std::vector<vec3_t> surrArr;
bool stopSwitch = false;

void Surround::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	
	if (citySwitch && isSideEmpty() && !stopSwitch) {  // auto grab blocks when side empty/broken
		auto box = g_Data.addInfoBox("Surround", "You have been citied! Replacing block");
		box->closeTimer = 3;

		//clientMessageF("");
		origSlot = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
		getObby();
		auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->itemId == 49)) {
			setEnabled(false);
			return;
		}
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

		for (auto surroundBlock : regularBlocks) {
			auto playerPosition = g_Data.getLocalPlayer()->getPos();
			auto flooredPos = playerPosition->floor();
			flooredPos.y -= 1.f;
			auto mathsBlockPos = flooredPos.add(surroundBlock);

			if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0) // if that *block* empty, don't place blok
				surrArr.push_back(surroundBlock);
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

			if (doAirplace) {
				gm->buildBlock(&vec3_ti(mathsBlockPos.x, mathsBlockPos.y - 1.f, mathsBlockPos.z), 0, false);  // ah so this causes the airplace
			} else if (!doAirplace) {
				tryPlace(mathsBlockPos);
			}

			surrArr.erase(surrArr.begin());
			break;
			auto mathsBlockPos2 = flooredPos.add(surroundBlock);
			return;

		     angle = g_Data.getLocalPlayer()->getPos()->CalcAngle(mathsBlockPos2);

			if (rotations) {
		
				gm->player->bodyYaw = angle.y;
				gm->player->yawUnused1 = angle.y;

				//return;
			}
		}
	}

	if (citySwitch && !isSideEmpty() && stopSwitch) {
		stopSwitch = false;
		g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = origSlot;
	}
	if (swapChecker == 1 && blockSwap && !isSideEmpty()) {
		g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = origSlot;
		swapChecker = 0;
	}
}


void Surround::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	
	if (g_Data.getLocalPlayer() == nullptr) return;
	
	if (renderSurround) {

		for (auto surroundBlock : regularBlocks) {
			DrawUtils::setColor(1.f, 0.f, 0.f, 1.f);  // 231,125,17

			auto playerPosition = g_Data.getLocalPlayer()->getPos();

			auto flooredPos = playerPosition->floor();
			flooredPos.y -= 1.f;

			auto mathsBlockPos = flooredPos.add(surroundBlock);

			auto vec1 = vec3_t(1.f, 1.f, 1.f);
			                          
			if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
				DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
		} 
	}
}
*/