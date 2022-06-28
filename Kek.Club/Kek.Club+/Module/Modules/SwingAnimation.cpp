#include "SwingAnimation.h"
void* FluxAddress = (void*)FindSignature("0F 84 ? ? ? ? 48 8B 56 ? 48 85 D2 74 ? 48 8B 02");
void* TapAddress = (void*)FindSignature("F3 0F 51 F0 0F 28 C8");
SwingAnimations::SwingAnimations() : IModule(0x0, Category::VISUAL, "SwingAnimations for killaura") {
	registerEnumSetting("BlockHit", &swing, 2);
	swing = SettingEnum(this)
				.addEntry(EnumEntry("SlideBlock", 0))
				.addEntry(EnumEntry("SmoothBlock", 1))
				.addEntry(EnumEntry("Tap", 2))
				.addEntry(EnumEntry("Normal", 3));
}

SwingAnimations::~SwingAnimations() {
}

const char* SwingAnimations::getModuleName() {
	return "Animations";
}
const char* SwingAnimations::getModName() {
	if (swing.selected == 0) {
		return " [Block]";
		if (swing.selected == 2) {
			return " [Tap]";
			if (swing.selected == 3) {
				return " [Flux]";
			}
		}
	}
}
	void SwingAnimations::onEnable() {
}

float ok2 = 0.f;
float ok3 = 0.f;
void SwingAnimations::onPlayerTick(C_Player* plr) {
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr) {
		auto slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot);

		if (ok2 >= 505)
			ok2 = 340;
		else
			ok2 += 2.f;

		if (ok2 <= 339)
			ok2 = 340;
		 
		if (ok3 >= 369)
			ok3 = 340;
		else
			ok3 += 1.5f;

		if (ok3 <= 339)
			ok3 = 340;

		if (slot->item != nullptr && !moduleMgr->getModule<Killaura>()->targetListA && swing.selected == 0 && slot != nullptr && slot->getItem()->isWeapon() && !moduleMgr->getModule<Killaura>()->noSwing) {
			float* speedAdr = reinterpret_cast<float*>(reinterpret_cast<__int64>(g_Data.getLocalPlayer()) + 0x79C);
			*speedAdr = ok2;
		} else if (slot->item != nullptr  && !moduleMgr->getModule<Killaura>()->targetListA && swing.selected == 1 && slot != nullptr && slot->getItem()->isWeapon() && !moduleMgr->getModule<Killaura>()->noSwing) {
			float* speedAdr = reinterpret_cast<float*>(reinterpret_cast<__int64>(g_Data.getLocalPlayer()) + 0x79C);
			*speedAdr = ok3;
		}
	}
}

void SwingAnimations::onTick(C_GameMode* gm) {
	auto slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot);
	if (slot->item != nullptr && moduleMgr->getModule<Killaura>()->isEnabled() && !moduleMgr->getModule<Killaura>()->targetListA && slot->getItem()->isWeapon() && swing.selected == 2)
		Utils::nopBytes((unsigned char*)TapAddress, 4);
	else
		Utils::patchBytes((unsigned char*)((uintptr_t)TapAddress), (unsigned char*)"\xF3\x0F\x51\xF0", 4);

	if (slot->item != nullptr && moduleMgr->getModule<Killaura>()->isEnabled() && !moduleMgr->getModule<Killaura>()->targetListA && slot->getItem()->isWeapon())
		Utils::nopBytes((unsigned char*)FluxAddress, 6);
	else
		Utils::patchBytes((unsigned char*)((uintptr_t)FluxAddress), (unsigned char*)"\x0F\x84\x95\x02\x00\x00", 6);
}

void SwingAnimations::onDisable() {
	Utils::patchBytes((unsigned char*)((uintptr_t)TapAddress), (unsigned char*)"\xF3\x0F\x51\xF0", 4);
	Utils::patchBytes((unsigned char*)((uintptr_t)FluxAddress), (unsigned char*)"\x0F\x84\x95\x02\x00\x00", 6);
}