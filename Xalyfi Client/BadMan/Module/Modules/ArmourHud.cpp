#include "ArmourHud.h"
#include "../../DrawUtils.h"

ArmourHud::ArmourHud() : IModule(0x0, Category::GUI, "Renders the armour that you are wearing") {
	registerFloatSetting("armorX", &this->armorX, this->armorX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("armorY", &this->armorY, this->armorY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
}

ArmourHud::~ArmourHud() {
}

const char* ArmourHud::getModuleName() {
	return ("ArmourHud");
}

void ArmourHud::onPostRender(C_MinecraftUIRenderContext* renderCtx){
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
				DrawUtils::drawItem(stack, vec2_t(xVal, yVal), opacity, scale, stack->isEnchanted());
				xVal += scale * spacing;
			}
		}
		C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
		C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
		//x += scale * spacing;
		if (item->item != nullptr)
			DrawUtils::drawItem(item, vec2_t(xVal, yVal), opacity, scale, item->isEnchanted());
	}
}
