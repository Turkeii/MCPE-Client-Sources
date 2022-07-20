#include "Bps.h"

Bps::Bps() : IModule(0, Category::GUI, "Speed counter") {
	registerFloatSetting("bpsX", &this->bpsX, this->bpsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("bpsY", &this->bpsY, this->bpsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

Bps::~Bps() {
}

const char* Bps::getModuleName() {
	return ("MyItem");
}

void Bps::onMove(C_MoveInputHandler* input) {
	
}
void Bps::onTick(C_GameMode* gm) {
	
}
void Bps::onPreRender(C_MinecraftUIRenderContext* renderCtx) {

	int id = g_Data.getLocalPlayer()->getSelectedItemId();

	PointingStruct* pointingStruct = g_Data.getClientInstance()->getPointerStruct();

	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(pointingStruct->block);

	char* name = block->toLegacy()->name.getText();
	id = block->toLegacy()->blockId;
	if (g_Data.getClientInstance()->isInGame()) {
		auto theme2 = moduleMgr->getModule<AltTheme>();
		
		std::string BpsText = "ID: " + std::string(std::to_string((int)id) + " " + std::string(std::to_string((char)name)));
		DrawUtils::drawText(vec2_t(bpsX, bpsY), &BpsText, MC_Color(theme2->rFloat, theme2->gFloat, theme2->bFloat), scale);
	}
}
void Bps::onDisable() {
	auto player = g_Data.getLocalPlayer();
}
