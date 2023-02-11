#include "ConfigManagerMenu.h"
#include <Windows.h>

static bool rightClickDown = false;
static bool leftClickDown = false;

static bool hasInitializedCM = false;
static int timesRenderedCM = 0;

using namespace std;
void ConfigManagerMenu::render() {
	auto player = g_Data.getLocalPlayer();

	vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2_t mousePos = *g_Data.getClientInstance()->getMousePos();
	rightClickDown = g_Data.isRightClickDown();
	leftClickDown = g_Data.isLeftClickDown();
	string title = string(BOLD) + "Configs";
	string sub_title = string(GRAY) + "Featured Configs";
	float width = DrawUtils::getTextWidth(&string("--------------------------------------------------------------------------------------------"));
	float height = DrawUtils::getTextWidth(&string("--------------------------------------------"));
	vec4_t rectPos = vec4_t(200, 100, 200 + width, 100 + height);

	DrawUtils::fillRoundRectangle(rectPos, MC_Color(0, 0, 0, 100), true);
	DrawUtils::drawCenteredString(vec2_t(rectPos.z / 1.56, rectPos.y + 10), &title, 1.f, MC_Color(255, 255, 255), true);
	DrawUtils::drawCenteredString(vec2_t(rectPos.z / 1.56, rectPos.y + 25), &sub_title, 1.f, MC_Color(255, 255, 255), true);
	DrawUtils::flush();
}

void ConfigManagerMenu::init() { hasInitializedCM = true; }

void ConfigManagerMenu::onKeyUpdate(int key, bool isDown) {
	if (!hasInitializedCM)
		return;
	static auto configManager = moduleMgr->getModule<ConfigManagerMod>();

	if (!isDown)
		return;

	if (!configManager->isEnabled()) {
		timesRenderedCM = 0;
		return;
	}

	if (timesRenderedCM < 10)
		return;
	timesRenderedCM = 0;

	switch (key) {
	default:
	case VK_ESCAPE:
		configManager->setEnabled(false);
		return;
	}
}