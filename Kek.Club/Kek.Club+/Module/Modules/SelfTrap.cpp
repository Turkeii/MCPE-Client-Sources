#include "SelfTrap.h"

SelfTrap ::~SelfTrap() {}
const char* SelfTrap::getModuleName() {
	return ("SelfTrap");
}
SelfTrap::SelfTrap() : IModule(0, Category::COMBAT, "when all else fails u can self trap") {
	registerBoolSetting("Rotate", &this->rotate, true);
}

vec3_t* BlockPos_trapPos;

int old_slot = -1;

bool isTrapped() {
	if (BlockPos_trapPos = nullptr) return false;

}
	int find_in_hotbar() {
	for (int i = 0; i < 9; ++i) {
		C_ItemStack stack = *g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);

		if (stack.item != nullptr && stack.getItem()) {
			auto block = stack.getItem()->itemId;

			if (block == 130)
				return i;

			else if (block == 49)
				return i;

			else if (stack.getItem()->isBlock())
				return i;
		}
	}
	return -1;
}

void SelfTrap::onEnable() {
	old_slot = g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot;
	if (find_in_hotbar() == -1)
		return;
}
void SelfTrap::onTick(C_GameMode* gm) {
	vec3_t BlockPos_trapPos = vec3_t(g_Data.getLocalPlayer()->getPos()->x, g_Data.getLocalPlayer()->getPos()->y + 2, g_Data.getLocalPlayer()->getPos()->z);
	//if (isTrapped()) {
	//	if (isEnabled()) {
	//		(this->disable());
	//	} else {
	//		(enabled())
	//	}
//	}
		
};
void SelfTrap::onDisable() {

}