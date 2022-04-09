#include "KeyStrokes.h"
#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"


KeyStrokes::KeyStrokes() : IModule(0x0, Category::GUI, "Renders Keystrokes on your screen") {
	registerBoolSetting("Keystrokes RGB", &keybindsRGB, keybindsRGB);
	registerFloatSetting("keystrokesX", &keystrokesX, keystrokesX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("keystrokesY", &keystrokesY, keystrokesY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Opacity", &opacity, opacity, 0.0f, 1.f);

}

KeyStrokes::~KeyStrokes() {
}

const char* KeyStrokes::getModuleName() {
	return ("Keystrokes");
}

static float currColor[4];

void KeyStrokes::onPreRender(C_MinecraftUIRenderContext* renderCtx) {

		// rainbow colors
	{
		if (currColor[3] < 1) {
			currColor[0] = 1;
			currColor[1] = 0.2f;
			currColor[2] = 0.2f;
			currColor[3] = 1;
		}
		Utils::ApplyRainbow(currColor, 0.00025f);
	}

	static auto partner = moduleMgr->getModule<Partner>();
	static auto hud = moduleMgr->getModule<HudModule>();

	vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		if (partner->Partnered.selected == 1) {
			DrawUtils::setColor(150, 30, 255, 1);
			DrawUtils::drawKeystroke(*input->forwardKey, vec2(26.f, windowSize.y - 94));
			DrawUtils::drawKeystroke(*input->leftKey, vec2(4.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->backKey, vec2(26.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->rightKey, vec2(48.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->spaceBarKey, vec2(4.f, windowSize.y - 50));
			DrawUtils::drawLeftMouseKeystroke(vec2(4.f, windowSize.y - 37));
			DrawUtils::drawRightMouseKeystroke(vec2(37.f, windowSize.y - 37));
			DrawUtils::CPS(vec2(4.f, windowSize.y - 15));
		} else {
		if (partner->Partnered.selected == 0) 
			DrawUtils::setColor(0, 0, 255, 1);
			DrawUtils::drawKeystroke(*input->forwardKey, vec2(26.f, windowSize.y - 94));
			DrawUtils::drawKeystroke(*input->leftKey, vec2(4.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->backKey, vec2(26.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->rightKey, vec2(48.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->spaceBarKey, vec2(4.f, windowSize.y - 50));
			DrawUtils::drawLeftMouseKeystroke(vec2(4.f, windowSize.y - 37));
			DrawUtils::drawRightMouseKeystroke(vec2(37.f, windowSize.y - 37));
			DrawUtils::CPS(vec2(4.f, windowSize.y - 15));
		}
		if (hud->rgb) {
			DrawUtils::setColor(*currColor, *currColor, *currColor, *currColor);
			DrawUtils::drawKeystroke(*input->forwardKey, vec2(26.f, windowSize.y - 94));
			DrawUtils::drawKeystroke(*input->leftKey, vec2(4.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->backKey, vec2(26.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->rightKey, vec2(48.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->spaceBarKey, vec2(4.f, windowSize.y - 50));
			DrawUtils::drawLeftMouseKeystroke(vec2(4.f, windowSize.y - 37));
			DrawUtils::drawRightMouseKeystroke(vec2(37.f, windowSize.y - 37));
			DrawUtils::CPS(vec2(4.f, windowSize.y - 15));
		} else {
			DrawUtils::drawKeystroke(*input->forwardKey, vec2(26.f, windowSize.y - 94));
			DrawUtils::drawKeystroke(*input->leftKey, vec2(4.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->backKey, vec2(26.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->rightKey, vec2(48.f, windowSize.y - 72));
			DrawUtils::drawKeystroke(*input->spaceBarKey, vec2(4.f, windowSize.y - 50));
			DrawUtils::drawLeftMouseKeystroke(vec2(4.f, windowSize.y - 37));
			DrawUtils::drawRightMouseKeystroke(vec2(37.f, windowSize.y - 37));
			DrawUtils::CPS(vec2(4.f, windowSize.y - 15));
		}
	}
}