#include "SwingAnimations.h"
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
	return "SwingAnimations";
}

void SwingAnimations::onEnable() {
}

float nigr = 0.f;
float nigr2 = 0.f;
void SwingAnimations::onPlayerTick(C_Player* plr) {
	if (g_Data.isInGame() && g_Data.getLocalPlayer() != nullptr) {
		auto slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot);

		if (nigr >= 505)
			nigr = 340;
		else
			nigr += 2.f;

		if (nigr <= 339)
			nigr = 340;

		if (nigr2 >= 369)
			nigr2 = 340;
		else
			nigr2 += 1.5f;

		if (nigr2 <= 339)
			nigr2 = 340;

		if (!moduleMgr->getModule<Killaura>()->targetListA && swing.selected == 0 && slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon() && !moduleMgr->getModule<Killaura>()->noSwing) {
			float* speedAdr = reinterpret_cast<float*>(reinterpret_cast<__int64>(g_Data.getLocalPlayer()) + 0x79C);
			*speedAdr = nigr;
		} else if (!moduleMgr->getModule<Killaura>()->targetListA && swing.selected == 1 && slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon() && !moduleMgr->getModule<Killaura>()->noSwing) {
			float* speedAdr = reinterpret_cast<float*>(reinterpret_cast<__int64>(g_Data.getLocalPlayer()) + 0x79C);
			*speedAdr = nigr2;
		}
	}
}

void SwingAnimations::onTick(C_GameMode* gm) {
	auto slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot);
	if (moduleMgr->getModule<Killaura>()->isEnabled() && !moduleMgr->getModule<Killaura>()->targetListA && slot->getItem()->isWeapon() && swing.selected == 2)
		Utils::nopBytes((BYTE*)TapAddress, 4); 
	else 
		Utils::patchBytes((BYTE*)((uintptr_t)TapAddress), (BYTE*)"\xF3\x0F\x51\xF0", 4);

	if (moduleMgr->getModule<Killaura>()->isEnabled() && !moduleMgr->getModule<Killaura>()->targetListA && slot->getItem()->isWeapon())
		Utils::nopBytes((BYTE*)FluxAddress, 6);
	else
		Utils::patchBytes((BYTE*)((uintptr_t)FluxAddress), (BYTE*)"\x0F\x84\x95\x02\x00\x00", 6);
}

void SwingAnimations::onDisable() {
	Utils::patchBytes((BYTE*)((uintptr_t)TapAddress), (BYTE*)"\xF3\x0F\x51\xF0", 4);
	Utils::patchBytes((BYTE*)((uintptr_t)FluxAddress), (BYTE*)"\x0F\x84\x95\x02\x00\x00", 6);
}