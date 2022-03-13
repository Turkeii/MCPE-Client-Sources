#include "../../DrawUtils.h"
#include "HoleSupporter.h"

HoleSupporter::HoleSupporter() : IModule(0, Category::COMBAT, "HoleSupporter!?!?!?") {

}

HoleSupporter::~HoleSupporter() {
}

const char* HoleSupporter::getModuleName() {
	return "HoleSupporter";
}



bool tryPlace22(const vec3_ti& blockPos) {
	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
	C_BlockLegacy* blockLegacy = block->toLegacy();
	if (blockLegacy->material->isReplaceable) {
		// Find neighbour
		static std::vector<vec3_ti> checklist;
		if (checklist.empty()) {
			checklist.push_back(vec3_ti(0, -1, 0));
			checklist.push_back(vec3_ti(0, 1, 0));

			checklist.push_back(vec3_ti(0, 0, -1));
			checklist.push_back(vec3_ti(0, 0, 1));

			checklist.push_back(vec3_ti(-1, 0, 0));
			checklist.push_back(vec3_ti(1, 0, 0));
		}

		auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock()))
			return false;

		bool foundCandidate = false;
		int i = 0;
		for (const auto& current : checklist) {
			vec3_ti calc = blockPos.sub(current);
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				//g_Data.getCGameMode()->buildBlock(&calc, i);

				return true;
				break;
			}
			i++;
		}
	}
	return false;
}

bool tryPlace2(const vec3_ti& blockPos) {
	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(blockPos);
	C_BlockLegacy* blockLegacy = block->toLegacy();
	if (blockLegacy->material->isReplaceable) {
		// Find neighbour
		static std::vector<vec3_ti> checklist;
		if (checklist.empty()) {
			checklist.push_back(vec3_ti(0, -1, 0));
			checklist.push_back(vec3_ti(0, 1, 0));

			checklist.push_back(vec3_ti(0, 0, -1));
			checklist.push_back(vec3_ti(0, 0, 1));

			checklist.push_back(vec3_ti(-1, 0, 0));
			checklist.push_back(vec3_ti(1, 0, 0));
		}

		auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock()))
			return false;

		bool foundCandidate = true;
		int i = 0;
		for (const auto& current : checklist) {
			vec3_ti calc = blockPos.sub(current);
			if (!((g_Data.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				//g_Data.getCGameMode()->buildBlock(&calc, i);

				return true;
				break;
			}
			i++;
		}
	}
	return false;
}
bool doReset2 = true;
bool iFuckedUp21 = false;
int tDelay2A = 0;
std::vector<vec3_t> surrArr2;
void HoleSupporter::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
	if ((selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock())) {
		setEnabled(false);
		return;
	}

	if (surrArr2.empty()) {
		doReset2 = true;
	} else {
		doReset2 = false;
	}
	if (doReset2 == true) {
		surrArr2.clear();

		if (enum1.selected == 1)
			for (auto HoleSupporterBlock : regularBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(HoleSupporterBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					surrArr2.push_back(HoleSupporterBlock);
			}
		if (enum1.selected == 0)
			for (auto HoleSupporterBlock : antiCityBlocks) {
				auto playerPosition = g_Data.getLocalPlayer()->getPos();
				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;
				auto mathsBlockPos = flooredPos.add(HoleSupporterBlock);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					surrArr2.push_back(HoleSupporterBlock);
			}
	}

	/*if (blockSwap) {
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
				
				if (tDelay2A <= 2) {
					tDelay2A++;
					iFuckedUp2 = true;
					return;
				} else {
					iFuckedUp2 = false;
				}
			}
		}
	}*/
	//cant be arsed looking at this rn

	vec3_t yR = vec3_t(floor(g_Data.getLocalPlayer()->getPos()->x), g_Data.getLocalPlayer()->getPos()->y, floor(g_Data.getLocalPlayer()->getPos()->z));
	yR.x += 0.5f;
	//yR.y += 2.3f;
	yR.z += 0.5f;
	g_Data.getLocalPlayer()->setPos(yR);

	//	if (enum1.selected == 1) {
	for (auto HoleSupporterBlock : surrArr2) {
		auto playerPosition = g_Data.getLocalPlayer()->getPos();
		auto flooredPos = playerPosition->floor();
		flooredPos.y -= 1.f;
		auto mathsBlockPos = flooredPos.add(HoleSupporterBlock);

		gm->buildBlock(&vec3_ti(mathsBlockPos), 0);
		surrArr2.erase(surrArr2.begin());
		break;
	}
	//}
	/*if (blockSwap) {
			g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot = prevSlot3;
			iFuckedUp2 = false;
		}*/

	if (surrArr2.empty() && disableOnComplete2) this->setEnabled(false);
}

void HoleSupporter::onMove(C_MoveInputHandler* hand) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (jumpDisable && hand->isJumping) this->setEnabled(false);
}

void HoleSupporter::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getLocalPlayer() == nullptr) return;

	if (renderHoleSupporter) {
		if (enum1.selected == 1) {
			for (auto HoleSupporterBlock : regularBlocks) {
				DrawUtils::setColor(1.f, 0.f, 1.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(HoleSupporterBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}

		} else if (enum1.selected == 0) {
			for (auto HoleSupporterBlock : antiCityBlocks) {
				DrawUtils::setColor(1.f, 0.f, 1.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(HoleSupporterBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}

		} else {
			for (auto HoleSupporterBlock : regularBlocks) {
				DrawUtils::setColor(1.f, 1.f, 0.f, 1.f);

				auto playerPosition = g_Data.getLocalPlayer()->getPos();

				auto flooredPos = playerPosition->floor();
				flooredPos.y -= 1.f;

				auto mathsBlockPos = flooredPos.add(HoleSupporterBlock);

				auto vec1 = vec3_t(1.f, 0.2f, 1.f);

				if (g_Data.getLocalPlayer()->region->getBlock(mathsBlockPos)->toLegacy()->blockId == 0)
					DrawUtils::drawBox(mathsBlockPos, mathsBlockPos.add(vec1), 1.f, true);
			}
		}
	}
}
