#include "Watermark.h"
#include "../pch.h"
#include <chrono>

using namespace std;
Watermark::Watermark() : IModule(0, Category::VISUAL, "Displays the watermark") {
	registerEnumSetting("Theme", &mode, 0);
	mode.addEntry("Simple", 0);
	mode.addEntry("New", 1);
	mode.addEntry("Weird", 2);
	mode.addEntry("Skeet", 3);
	mode.addEntry("Virtue 6", 4);
	registerBoolSetting("Gradient", &gradient, &gradient);
	registerFloatSetting("Opacity", &opacity, opacity, 0, 1);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 2);
	shouldHide = true;
}

const char* Watermark::getModuleName() {
	return ("Watermark");
}

void Watermark::onEnable() {
}

void Watermark::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr || moduleMgr->getModule<DebugMenu>()->isEnabled()) return;

	auto interfaceMod = moduleMgr->getModule<Interface>();
	auto clickGUI = moduleMgr->getModule<ClickGUIMod>();

	//DrawUtils::drawImage("textures/ui/heart_new.png", vec2_t(positionX + 5, positionY + 50), vec2_t(30, 30), vec2_t(0, 0), vec2_t(1, 1));

	if (g_Data.canUseMoveKeys() && !clickGUI->hasOpenedGUI) {
		string name = player->getNameTag()->getText(); name = Utils::sanitize(name); name = name.substr(0, name.find('\n')); string clientName = interfaceMod->getClientName(); string fpsText = string(GRAY) + "[" + string(RESET) + to_string(g_Data.getFPS()) + " FPS" + string(GRAY) + "]"; string skeetLen = "Fatalitysense | " + name + " | " + fpsText; string t = "Fatality         | " + name + " | " + fpsText; string sense = "sense"; string newText = clientName + GRAY + "| " + RESET + WHITE + name; string idk = "Fatality "; string idk2 = string(GRAY) + clientName; string len = idk + idk2; // why u lookin over here
		float textHeight = 16.f * scale;
		float textPadding = 1.f * scale;

		switch (mode.getSelectedValue()) {
		case 0: aidsLen = DrawUtils::getTextWidth(&clientName, scale) + 2.f; height = textHeight + (textPadding * 2); break;
		case 1: aidsLen = DrawUtils::getTextWidth(&newText, scale) + 6.f; height = textHeight + (textPadding * 2); break;
		case 2: aidsLen = DrawUtils::getTextWidth(&len, scale) + 12.f; height = textHeight + (textPadding * 2); break;
		case 3: aidsLen = DrawUtils::getTextWidth(&skeetLen, scale) + (textPadding * 13); height = textHeight + (textPadding * 2); break;
		}

		float flaot = DrawUtils::getTextWidth(&idk, scale) + 8.F;
		float te = DrawUtils::getTextWidth(&sense, scale) + 8.f;
		vec4_t skeetRect = vec4_t(positionX, positionY, positionX + aidsLen, positionY + textHeight + (textPadding * 4));
		vec4_t simpleRect = vec4_t(positionX, positionY, positionX + aidsLen, positionY + textHeight + (textPadding * 2));
		vec4_t newRect = vec4_t(positionX, positionY, positionX + aidsLen, positionY + textHeight + (textPadding * 2));
		vec4_t idkRect = vec4_t(positionX, positionY, positionX + aidsLen, positionY + textHeight + (textPadding * 2));
		vec4_t newRectTop = vec4_t(newRect.x, newRect.y - 2, newRect.z, newRect.y);

		//DrawUtils::drawRounderRectangle(vec4_t(positionX, positionY, positionX + 15, positionY + 2.F), interfaceColor);
		//DrawUtils::drawCircle(vec4_t(positionX + 10, positionY, positionX + 14, positionY + 2.F), MC_Color(10, 10, 10, 255));m 

		auto interfaceColor = ColorUtil::interfaceColor(1);
		switch (mode.getSelectedValue()) {
		case 0:
			if (gradient) DrawUtils::drawGradientText(vec2_t(simpleRect.x, simpleRect.y), &clientName, scale, 1, true);
			else DrawUtils::drawText(vec2_t(simpleRect.x, simpleRect.y), &clientName, interfaceColor, scale, 1, true);
			break;
		case 1: // New
			DrawUtils::fillRoundRectangle(newRect, MC_Color(0, 0, 0, opacity), false);
			DrawUtils::fillRectangleA(newRectTop, interfaceColor);
			DrawUtils::drawText(vec2_t(newRect.x + (textPadding * 3), newRect.y + (textPadding * 3)), &newText, interfaceColor, scale, 1, true);
			break;
		case 2: // Weird
			DrawUtils::drawGradientText(vec2_t(simpleRect.x, simpleRect.y), &idk, scale, 1, true);
			DrawUtils::drawText(vec2_t(simpleRect.x + flaot + (textPadding * 2), simpleRect.y - 5), &idk2, MC_Color(), 1, 1, true);
			break;
		case 3: // Skeet
			DrawUtils::fillRectangle(skeetRect, MC_Color(27, 27, 27), 1);
			DrawUtils::drawRectangle(skeetRect, MC_Color(57, 57, 57), 1, 2);
			DrawUtils::drawText(vec2_t(skeetRect.x + (textPadding * 2) + 4.f, skeetRect.y + (textPadding * 2)), &t, MC_Color(255, 255, 255), scale, 1, true);
			DrawUtils::drawGradientText(vec2_t(skeetRect.x + te + (textPadding * 2) + 4.f, skeetRect.y + (textPadding * 2)), &sense, scale, 1, true);
			break;
		case 4: // Virtue
			// Text
			string virtue = "Virtue 6";
			string FPS = string(GRAY) + "Fps: " + to_string(g_Data.getFPS());
			string version = string(GRAY) + "Ver: 1.18.12";

			// Text Math
			float virtueLen = DrawUtils::getTextWidth(&virtue, 1.f);
			float FPSLen = DrawUtils::getTextWidth(&FPS, 1.f);
			float versionLen = DrawUtils::getTextWidth(&version, 1.f);
			float padding = 5.f;
			float fontHeight = DrawUtils::getFontHeight(1.f);

			// Rect Math
			vec4_t virtueRect = vec4_t(simpleRect.x - 1.f, simpleRect.y, simpleRect.x + versionLen + padding + 1.f, simpleRect.y + fontHeight * 3 + padding - 3.f);

			// Draw
			DrawUtils::fillRectangle(virtueRect, MC_Color(112, 112, 112), opacity);
			DrawUtils::drawRectangle(vec4_t(virtueRect.x, virtueRect.y, virtueRect.z + 0.5f, virtueRect.w + 0.5f), MC_Color(0, 0, 0), opacity, 1.f);

			DrawUtils::drawText(vec2_t(virtueRect.z / 2 - virtueLen / 2 + padding / 2, virtueRect.y + 3.f), &virtue, MC_Color(255, 255, 255), 1.f, 1.f, true);
			DrawUtils::drawText(vec2_t(virtueRect.z / 2 - FPSLen / 2 + padding / 2, virtueRect.y + 3.f + fontHeight), &FPS, MC_Color(255, 255, 255), 1.f, 1.f, true);
			DrawUtils::drawText(vec2_t(virtueRect.z / 2 - versionLen / 2 + padding / 2, virtueRect.y + 3.f + fontHeight * 2), &version, MC_Color(255, 255, 255), 1.f, 1.f, true);

		}
	}
}