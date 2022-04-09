#include "HudModule.h"

#include "../../DrawUtils.h"

HudModule::HudModule() : IModule(0, Category::VISUAL, "Displays ur mom") {
	registerEnumSetting("Color", &color, 0);
	color.addEntry("Rainbow", 0);
	color.addEntry("Dynamic", 1);
	color.addEntry("Horion", 2);
	color.addEntry("Fadeaway", 3);
	color.addEntry("Weather", 4);
	color.addEntry("Custom", 5);  // not sure how i will implement this
	registerBoolSetting("Keystrokes", &keystrokes, keystrokes);
	registerBoolSetting("ArmorHUD", &armorHUD, armorHUD);
	registerBoolSetting("Info", &info, info);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

	// Colors
static float rcolors[4];          // Rainbow color array RGBA
static float disabledRcolors[4];  // Rainbow Colors, but for disabled modules
static float currColor[4];        // ArrayList colors

HudModule::~HudModule() {
}

const char* HudModule::getModuleName() {
	return ("HUD");
}

void HudModule::onTick(C_GameMode* gm) {
}

void HudModule::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}

void HudModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	float f = 10.f * scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	// float startY = tabGUI ? 6 * f : 0.f;

	static constexpr float colorIncrease = 0.05f;
	static float dynamicColor = 0.f;
	static bool isIncreasingColor = true;
	static bool isIncreasingcurrColor = true;
	static float dynamic = 0.f;
	int a = 0;
	int b = 0;
	int c = 0;

	dynamic = dynamicColor;
	isIncreasingcurrColor = !isIncreasingColor;

	// Rainbow color updates
	{
		Utils::ApplyRainbow(rcolors, 0.0005f);  // Increase Hue of rainbow color array
		disabledRcolors[0] = std::min(10.f, rcolors[0] * 0.20f + -22.f);
		disabledRcolors[1] = std::min(10.f, rcolors[2] * 0.21f + -24.f);
		disabledRcolors[2] = std::min(10.f, rcolors[3] * 0.22f + -26.f);
		disabledRcolors[3] = 1;
	}
	// Dynamic color updates
	{
		dynamicColor += (isIncreasingColor ? 0.007f : -0.007f) * DrawUtils::getLerpTime();
		if (dynamicColor < 0.2f) {
			dynamicColor = 0.2;
			isIncreasingColor = true;
		}
		if (dynamicColor > 1.f) {
			dynamicColor = 1.f;
			isIncreasingColor = false;
		}
	}
	currColor[3] = rcolors[3];
	if (color.getSelectedValue() == 0) {  // Rainbow
		Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[2], rcolors[1], currColor[0], currColor[1], currColor[2]);
		currColor[0] += 1.f / a * c;
		Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[1], currColor[2]);
	}
	if (color.getSelectedValue() == 2) {  // Horion
		Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
		currColor[0] += 1.f / a * c;
		Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[1], currColor[2]);
	}
	if (color.getSelectedValue() == 3) {  // Fadeaway
		Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
		currColor[0] += 1.f / a * c;
		Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[3], currColor[3]);
	}
	if (color.getSelectedValue() == 4) {  // Weather
		Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[2], currColor[2]);
		currColor[0] += 1.1f / a * b;
		Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[0], currColor[1]);
	}
	dynamic += (isIncreasingcurrColor ? colorIncrease : -colorIncrease);
	if (dynamic < 0.2f) {
		dynamic = 0.2f;
		isIncreasingcurrColor = true;
	}
	if (dynamic > 1.f) {
		dynamic = 1.f;
		isIncreasingcurrColor = false;
	}

	// Armor HUD - remove atm
	/*if (armorHUD) {
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		static float constexpr opacity = 1;
		float scale = 3 * 0.26f;
		float spacing = scale + 15.f + 2;
		std::string lenlol = "                      ";  // add more spaces for longer rect lol
		std::string armor = "Armor:";
		float startY = windowSize.y - 37;
		float l = DrawUtils::getTextWidth(&lenlol, 1) + 6.5;
		vec4_t rectPos = vec4_t(2.5, startY + 6, l, startY + 20);
		vec2_t textPos = vec2_t(rectPos.x + 35, rectPos.y + 1);
		vec2_t textPos2 = vec2_t(rectPos.x + 2, rectPos.y + 3);
		DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), hudMod->opacity);
		C_LocalPlayer* player = g_Data.getLocalPlayer();

		if (hudMod->color.getSelectedValue() != 1)  // Rainbow
			DrawUtils::drawText(textPos2, &armor, MC_Color(currColor), 1, 1, true);
		if (hudMod->color.getSelectedValue() == 1) {  // Dynamic
			DrawUtils::drawText(textPos2, &armor, MC_Color(dynamic, dynamic, dynamic), 1, 1, true);
		}

		for (int t = 0; t < 4; t++) {
			C_ItemStack* stack = player->getArmor(t);
			if (stack->isValid()) {
				DrawUtils::drawItem(stack, vec2_t(textPos), 1, scale, false);
				textPos.x += scale * spacing;
			}
		}
	}*/

	// Keystrokes (duh)
	if (keystrokes && g_Data.getLocalPlayer() != nullptr && GameData::canUseMoveKeys()) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(32.f, windowSize.y - 74));
		DrawUtils::drawKeystroke(*input->leftKey, vec2_t(10.f, windowSize.y - 52));
		DrawUtils::drawKeystroke(*input->backKey, vec2_t(32.f, windowSize.y - 52));
		DrawUtils::drawKeystroke(*input->rightKey, vec2_t(54.f, windowSize.y - 52));
		DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(10.f, windowSize.y - 30));
	}
}

void HudModule::onDisable() {
}