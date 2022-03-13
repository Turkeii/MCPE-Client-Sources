#include "surround.h"
#include "../../DrawUtils.h"

Surround::Surround() : IModule(0, Category::WORLD, "Surrounds the bottom half of you in obsidian") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("Anti-City", 1))
				.addEntry(EnumEntry("Regular", 2));

//	registerFloatSetting("float1", &this->float1, 0, -10, 10);
//	registerIntSetting("int1", &this->int1, 0, -10, 10);
	registerEnumSetting("Mode", &enum1, 2);
	registerBoolSetting("Render", &this->renderSurround, true);
	registerBoolSetting("Jump Disable", &this->jumpDisable, false);
	registerBoolSetting("Disable Complete", &this->disableOnComplete2, true);
	registerBoolSetting("Swap", &this->blockSwap, true);
}

Surround::~Surround() {
}

const char* Surround::getModuleName() {
	return "Surround";
}
bool Surround::trySurround(vec3_t blockBelow) {
	blockBelow = blockBelow.floor();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(vec3_ti(blockBelow));
	C_BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		vec3_ti blok(blockBelow);
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
				g_Data.getCGameMode()->buildBlock(&blok, i);
				return true;
			}
			//g_Data.getCGameMode()->buildBlock(&blok, i);
		
	}
	return false;
}

bool doReset = true;
bool iFuckedUp2 = false;
int tDelay2 = 0;
std::vector<vec3_t> surrArr;
void Surround::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock())) {
		setEnabled(false);
		return;
	}

	if (surrArr.empty()) {
		doReset = true;
	} else {
		doReset = false;
	}
	if (doReset == true) {
		surrArr.clear();

		if (enum1.selected == 1)
			for (auto surroundBlock : regularBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(surroundBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					surrArr.push_back(surroundBlock);
			}
		if (enum1.selected == 0)
			for (auto surroundBlock : antiCityBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(surroundBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					surrArr.push_back(surroundBlock);
			}
	}

	if (blockSwap) {
		if (!iFuckedUp2) {
			if (blockSwap) {
				prevSlot3 = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
			}
		}

		int slot = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
		for (int i = 0; i < 9; i++) {
			C_ItemStack* obby = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
			if (obby->item != NULL && (*obby->item)->itemId == 49) {
				slot = i;
				g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = slot;

				if (tDelay2 <= 2) {
					tDelay2++;
					iFuckedUp2 = true;
					return;
				} else {
					iFuckedUp2 = false;
				}
			}
		}
	}
	//cant be arsed looking at this rn

	vec3_t yR = vec3_t(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
	yR.x += 0.5f;
	//yR.y += 2.3f;
	yR.z += 0.5f;
	g_Data.getLocalPlayer()->setPos(yR);


//	if (enum1.selected == 1) {
		for (auto surroundBlock : surrArr) {
			auto playerPosition = g_Data.getLocalPlayer()->getPos();
			auto flooredPos = playerPosition->floor();
			flooredPos.y -= 1.f;
			auto mathsBlockPos = flooredPos.add(surroundBlock);
			                                                       
				gm->buildBlock(&vec3_ti(mathsBlockPos), 1);
				surrArr.erase(surrArr.begin());
				break;		
		}
	//}
		if (blockSwap) {
			g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = prevSlot3;
			iFuckedUp2 = false;
		}


		if (surrArr.empty() && disableOnComplete2) this->setEnabled(false);

}

void Surround::onMove(C_MoveInputHandler* hand) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	
	if (jumpDisable && hand->isJumping) this->setEnabled(false);
}

void Surround::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	
	if (g_Data.getLocalPlayer() == nullptr) return;
	
	if (renderSurround) {
		if (enum1.selected == 1) {
			for (auto surroundBlock : regularBlocks) {
				DrawUtils::setColor(1.f, 0.f, 1.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}

		} else if (enum1.selected == 0) {
			for (auto surroundBlock : antiCityBlocks) {
				DrawUtils::setColor(1.f, 0.f, 1.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}

		} else {
			for (auto surroundBlock : regularBlocks) {
				DrawUtils::setColor(1.f, 1.f, 0.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(surroundBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}
		}
	}
}
