#include "ItemId.h"

ItemId::ItemId() : IModule(0, Category::VISUAL, "Get a item id by holding it") {
	registerFloatSetting("ItemX", &this->ItemIdX, this->ItemIdX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("ItemY", &this->ItemIdY, this->ItemIdY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

ItemId::~ItemId() {
}

const char* ItemId::getModuleName() {
	return ("ItemId");
}

void ItemId::onMove(C_MoveInputHandler* input) {
}

void ItemId::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (g_Data.getClientInstance()->isInGame()) {
		float yVal = ItemIdY;
		float xVal = ItemIdX;
		int id = g_Data.getLocalPlayer()->getSelectedItemId();
		std::string name = g_Data.getLocalPlayer()->getSelectedItem()->getItem()->tileName.getText();

		std::string ItemIdText = "ID : " + std::string(std::to_string((int)id)) + "\nName : " + std::string(name);

		DrawUtils::drawText(vec2_t(ItemIdX, ItemIdY), &ItemIdText, MC_Color(1.f, 1.f, 1.f), scale);
	}
}
void ItemId::onDisable() {
	auto player = g_Data.getLocalPlayer();
}
