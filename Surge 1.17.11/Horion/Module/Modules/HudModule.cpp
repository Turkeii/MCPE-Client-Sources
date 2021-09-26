#include "HudModule.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

HudModule::HudModule() : IModule(0, Category::VISUAL, "Displays More") {
	registerBoolSetting("ClickToggle", &this->clickToggle, this->clickToggle);
	registerBoolSetting("Watermark", &this->watermark, this->watermark);
	registerBoolSetting("Coordinates", &this->coordinates, this->coordinates);
	registerBoolSetting("Sup Bitch", &this->supbitch, this->supbitch);
	registerBoolSetting("Show Keybinds", &this->keybinds, this->keybinds);
	registerBoolSetting("Show ArmorHUD", &this->displayArmor, this->displayArmor);
	registerBoolSetting("RGB Borders", &this->rgbborders, this->rgbborders);
	registerBoolSetting("RGB Text", &this->rgbtext, this->rgbtext);
	registerBoolSetting("Keystrokes", &this->keystrokes, this->keystrokes);
	registerBoolSetting("Show FPS", &this->fps, this->fps);
	registerBoolSetting("Show CPS", &this->cps, this->cps);
	registerBoolSetting("Always show", &this->alwaysShow, this->alwaysShow);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
	registerFloatSetting("Opacity", &this->opacity, this->opacity, 0.0f, 1.f);
}

HudModule::~HudModule() {
}

const char* HudModule::getModuleName() {
	return ("HUD");
}

void HudModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	static float rcolors[4];          // Rainbow color array RGBA
	static float disabledRcolors[4];  // Rainbow Colors, but for disabled modules
	static float currColor[4];        // ArrayList colors

	// Rainbow color updates
	{
		Utils::ApplyRainbow(rcolors);  // Increase Hue of rainbow color array
		disabledRcolors[0] = std::min(1.f, rcolors[0] * 0.4f + 0.2f);
		disabledRcolors[1] = std::min(1.f, rcolors[1] * 0.4f + 0.2f);
		disabledRcolors[2] = std::min(1.f, rcolors[2] * 0.4f + 0.2f);
		disabledRcolors[3] = 1;
	}
	int a = 0;
	int b = 0;
	int c = 0;
	currColor[3] = rcolors[3];
	Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
	currColor[0] += 1.f / a * c;
	Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[1], currColor[2]);

	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = tabgui ? -0.28 * f : 0.f;
	if (tabgui && scriptMgr.getNumEnabledScripts() > 0)
		startY += f;
	{  // FPS
		if (!(g_Data.getLocalPlayer() == nullptr || !this->fps)) {
			std::string fpsText = "FPS: " + std::to_string(g_Data.getFPS());
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), opacity);
			static auto rgbHud = moduleMgr->getModule<HudModule>();
			if (rgbHud->rgbtext) {
				DrawUtils::drawText(textPos, &fpsText, MC_Color(rcolors), scale);
			} else {
				DrawUtils::drawText(textPos, &fpsText, MC_Color(0, 0, 255), scale);
			}

			startY += f;
		}
	}
	{  // Sup Bitch
		if (!(g_Data.getLocalPlayer() == nullptr || !this->supbitch)) {
			std::string fpsText = "Sup Bitch";
			vec4_t rectPos = vec4_t(300.f, startY + 3.f * scale, len, startY + 150.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), 0);
			static auto rgbHud = moduleMgr->getModule<HudModule>();
			if (rgbHud->rgbtext) {
				DrawUtils::drawText(textPos, &fpsText, MC_Color(rcolors), scale);
			} else {
				DrawUtils::drawText(textPos, &fpsText, MC_Color(0, 0, 255), scale);
			}
		}
	}
	{  // CPS
		if (!(g_Data.getLocalPlayer() == nullptr || !this->cps)) {
			std::string cpsText = "CPS: " + std::to_string(g_Data.getLeftCPS()) + " - " + std::to_string(g_Data.getRightCPS());
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), opacity);
			static auto rgbHud = moduleMgr->getModule<HudModule>();
			if (rgbHud->rgbtext) {
				DrawUtils::drawText(textPos, &cpsText, MC_Color(rcolors), scale);
			} else {
				DrawUtils::drawText(textPos, &cpsText, MC_Color(0, 0, 225), scale);
			}

			startY += f;
		}
	}
	{  // Coordinates
		if (!(g_Data.getLocalPlayer() == nullptr || !this->coordinates)) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();

			std::string coordsX = "X: " + std::to_string((int)floorf(pos->x));
			std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y));
			std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z));
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 35.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), opacity);
			static auto rgbHud = moduleMgr->getModule<HudModule>();
			if (rgbHud->rgbtext) {
				DrawUtils::drawText(textPos, &coordsX, MC_Color(rcolors), scale);
				textPos.y += f;
				DrawUtils::drawText(textPos, &coordsY, MC_Color(rcolors), scale);
				textPos.y += f;
				DrawUtils::drawText(textPos, &coordsZ, MC_Color(rcolors), scale);
			} else {
				DrawUtils::drawText(textPos, &coordsX, MC_Color(0, 0, 255), scale);
				textPos.y += f;
				DrawUtils::drawText(textPos, &coordsY, MC_Color(0, 0, 255), scale);
				textPos.y += f;
				DrawUtils::drawText(textPos, &coordsZ, MC_Color(0, 0, 255), scale);
			}
		}
	}
	{
		// ArmorHUD
		if (!(g_Data.getLocalPlayer() == nullptr || !this->displayArmor || !GameData::canUseMoveKeys())) {
			static float constexpr scale = 1.f;
			static float constexpr opacity = 0.25f;
			static float constexpr spacing = scale + 15.f;
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			float x = windowSize.x / 2.f + 5.f;
			float y = windowSize.y - 57.5f;
			for (int i = 0; i < 4; i++) {
				C_ItemStack* stack = player->getArmor(i);
				if (stack->isValid()) {
					DrawUtils::drawItem(stack, vec2_t(x, y), opacity, scale, stack->isEnchanted());
					x += scale * spacing;
				}
			}
			C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
			C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			//x += scale * spacing;
			if (item->isValid())
				DrawUtils::drawItem(item, vec2_t(x, y), opacity, scale, item->isEnchanted());
		}
	}
	{  // Keystrokes
			if (!(g_Data.getLocalPlayer() == nullptr || !this->keystrokes || !GameData::canUseMoveKeys())) {
				C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
				DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(32.f, windowSize.y - 84));
				DrawUtils::drawKeystroke(*input->leftKey, vec2_t(10.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->backKey, vec2_t(32.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->rightKey, vec2_t(54.f, windowSize.y - 62));
				DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(10.f, windowSize.y - 40));
				DrawUtils::drawLeftMouseKeystroke(vec2_t(10.f, windowSize.y - 25));
				DrawUtils::drawRightMouseKeystroke(vec2_t(43.f, windowSize.y - 25));
			}
		}
	}