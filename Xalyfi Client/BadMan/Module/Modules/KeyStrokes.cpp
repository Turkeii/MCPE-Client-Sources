#include "KeyStrokes.h"
#include "../../DrawUtils.h"

KeyStrokes::KeyStrokes() : IModule(0x0, Category::GUI, "Renders Keystrokes on your screen") {
	registerFloatSetting("keystrokesX", &this->keystrokesX, this->keystrokesX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("keystrokesY", &this->keystrokesY, this->keystrokesY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
}

KeyStrokes::~KeyStrokes() {
}

const char* KeyStrokes::getModuleName() {
	return ("Keystrokes");
}

void KeyStrokes::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;

	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(32.f, windowSize.y - 74));
		DrawUtils::drawKeystroke(*input->leftKey, vec2_t(10.f, windowSize.y - 52));
		DrawUtils::drawKeystroke(*input->backKey, vec2_t(32.f, windowSize.y - 52));
		DrawUtils::drawKeystroke(*input->rightKey, vec2_t(54.f, windowSize.y - 52));
		DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(10.f, windowSize.y - 30));
	}
}
