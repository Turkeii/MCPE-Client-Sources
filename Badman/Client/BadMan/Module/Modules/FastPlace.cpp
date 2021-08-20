#include "FastPlace.h"

FastPlace::FastPlace() : IModule(0x0, Category::WORLD, "Place Blocks and End Crystals faster") {
	this->registerBoolSetting("Only Crystals", &this->onlyCrystals, this->onlyCrystals);
	registerFloatSetting("delay", &this->delay, this->delay, 0.f, 0.1f);
}

FastPlace::~FastPlace() {
}

const char* FastPlace::getModuleName() {
	return ("FastPlace");
}

void FastPlace::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (GameData::isRightClickDown()) {
		auto pStruct = g_Data.getClientInstance()->getPointerStruct();
		vec3_ti block = pStruct->block.toVec3t();
		int face = pStruct->blockSide;
		int rayType = pStruct->rayHitType;

		auto selectedItem = g_Data.getLocalPlayer()->getSelectedItem();
		auto selectedItemId = g_Data.getLocalPlayer()->getSelectedItemId();
		bool isCrystal = false;

		if (!onlyCrystals && rayType == 0) {
			//when no bools are enabled this is how i make it place end crystals fast
			if (selectedItemId == 615 && !selectedItem->count == 0 || selectedItemId == 616 && !selectedItem->count == 0) {
				isCrystal = true;
			} else {
				isCrystal = false;
			}

			if (!isCrystal) {
				if (selectedItem == nullptr || selectedItem->count == 0 || selectedItem->item == nullptr || !selectedItem->getItem()->isBlock())
					return;
			}

			Odelay++;
			if (Odelay > delay * 20) {
				gm->buildBlock(&block, face);
				Odelay = 0;
			}

		} else if(onlyCrystals && rayType == 0){
			if (selectedItemId == 615 && !selectedItem->count == 0 || selectedItemId == 616 && !selectedItem->count == 0) {

				Odelay++;
				if (Odelay > delay * 20){
					gm->buildBlock(&block, face);
					Odelay = 0;
				}
			}
		}
	}
}