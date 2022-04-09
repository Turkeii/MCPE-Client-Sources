#pragma once
#include "../ModuleManager.h"
#include "Module.h"
#include "../../DrawUtils.h"
class ArmourHud : public IModule {
public:
	float armorX = 210.f;
	float armorY = 55.f;

	ArmourHud() : IModule(0x0, Category::GUI, "Renders the armour that you are wearing") {
		registerFloatSetting("armorX", &armorX, armorX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
		registerFloatSetting("armorY", &armorY, armorY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	};
	~ArmourHud(){};

	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		auto player = g_Data.getLocalPlayer();
		if (player == nullptr) return;

		if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
			static float constexpr scale = 1.f;
			static float constexpr opacity = 0.25f;
			static float constexpr spacing = scale + 16.f;
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			float yVal = armorY;
			float xVal = armorX;
			for (int i = 0; i < 4; i++) {
				C_ItemStack* stack = player->getArmor(i);
				if (stack->item != nullptr) {
					DrawUtils::drawItem(stack, vec2(xVal, yVal), opacity, scale, stack->isEnchanted());
					xVal += scale * spacing;
				}
			}
			C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
			C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			if (item->item != nullptr)
				DrawUtils::drawItem(item, vec2(xVal, yVal), opacity, scale, item->isEnchanted());
		}
	}

	virtual const char* getModuleName() override {
		return "ArmourHud";
	}
};