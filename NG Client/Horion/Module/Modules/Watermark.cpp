#include "Watermark.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

Watermark::Watermark() : IModule(0x0, Category::GUI, "Show Watermark") {
	registerEnumSetting("Watermark Types", &watermark, 0);
	watermark = (*new SettingEnum(this))
					.addEntry(EnumEntry("CSGO", 0))
					.addEntry(EnumEntry("CSGO Player", 1))
					.addEntry(EnumEntry("CSGO Version", 2))
					.addEntry(EnumEntry("Old Version", 3));
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

Watermark::~Watermark() {
}

const char* Watermark::getModuleName() {
	return ("Watermark");
}

	static float currColor[4];

void Watermark::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		static float rcolors[4];          // Rainbow color array RGBA
		static float disabledRcolors[4];  // Rainbow Colors, but for disabled modules
		static float currColor[4];        // ArrayList colors
		{
			Utils::ApplyRainbow(rcolors, 0.0008);  // Increase Hue of rainbow color array
			disabledRcolors[0] = std::min(1.f, rcolors[0] * 0.4f + 0.2f);
			disabledRcolors[1] = std::min(1.f, rcolors[1] * 0.4f + 0.2f);
			disabledRcolors[2] = std::min(1.f, rcolors[2] * 0.4f + 0.2f);
			disabledRcolors[3] = 1;
		}
		currColor[3] = rcolors[5];
		currColor[3] = rcolors[5];
		Utils::ColorConvertRGBtoHSV(rcolors[0 & 1], rcolors[2], rcolors[01], currColor[0], currColor[1], currColor[2]);
		currColor[0] += 0.5f;
		Utils::ColorConvertHSVtoRGB(currColor[0 & 1], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);

		vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		vec2 windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
		static auto partner = moduleMgr->getModule<Partner>();
		static auto hud = moduleMgr->getModule<HudModule>();
		//
		constexpr float nameTextSize = 0.8f;
		constexpr float versionTextSize = 0.6f;
		static const float textHeight = (nameTextSize + versionTextSize * 0.7f) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();
		//
		if (watermark.selected == 0) {
			if (partner->Partnered.selected == 1) {

				static std::string name = "Fadeaway | Public Build";
				static std::string version = "";

				float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
				float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);

				if (hud->rgb) {
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
				} else {
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
				}
			} else {
				if (partner->Partnered.selected == 0) {

					static std::string name = "Surge | Public Build";
					static std::string version = "";

					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);

					if (hud->rgb) {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					} else {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					}
				} else {

					static std::string name = "NG Client | Public Build";
					static std::string version = "";

					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);

					if (hud->rgb) {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					} else {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					}
				}
			}
		} else if (watermark.selected == 1) {
			if (partner->Partnered.selected == 1) {

				auto player = g_Data.getLocalPlayer();
				std::string playername = player->getNameTag()->getText();
				
				static std::string name = "Fadeaway | " + playername;
				static std::string version = "";

				float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
				float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);

				if (hud->rgb) {
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
				} else {
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
				}
			} else {
				if (partner->Partnered.selected == 0) {

					auto player = g_Data.getLocalPlayer();
					std::string playername = player->getNameTag()->getText();
					
					static std::string name = "Surge | " + playername;
					static std::string version = "";

					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);

					if (hud->rgb) {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					} else {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					}
				} else {

					auto player = g_Data.getLocalPlayer();
					std::string playername = player->getNameTag()->getText();
					

					static std::string name = "NG Client | " + playername;
					static std::string version = "";

					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);

					if (hud->rgb) {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					} else {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					}
				}
			}
		} else if (watermark.selected == 2) {
			if (partner->Partnered.selected == 1) {

				static std::string name = "Fadeaway | 1.18.12.2";
				static std::string version = "";

				float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
				float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);

				if (hud->rgb) {
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
				} else {
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
					DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
					DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
				}
			} else {
				if (partner->Partnered.selected == 0) {

					static std::string name = "Surge | 1.18.12.2";
					static std::string version = "";

					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);
					if (hud->rgb) {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					} else {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					}
				} else {

					static std::string name = "NG Client | 1.18.12.2";
					static std::string version = "";

					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);
					if (hud->rgb) {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(currColor), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					} else {
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 2.0f), &name, MC_Color(currColor), nameTextSize);
						DrawUtils::drawText(vec2(windowSize.x / windowSize.x, windowSize.y / windowSize.y + 1.5f), &name, MC_Color(255, 255, 255), nameTextSize);

						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 10), MC_Color(0, 0, 0), opacity);
						DrawUtils::fillRectangle(vec4(windowSize.x / windowSize.x, windowSize.y / windowSize.y, +nameLength + 2, 2), MC_Color(currColor), 1.f);
					}
				}
			}
		} else if (watermark.selected == 3) {
			constexpr float borderPadding = 1;
			constexpr float margin = 5;

			if (partner->Partnered.selected == 1) {
				static std::string name = "Fadeaway";
				static std::string version = "";

				float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
				float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);
				vec4 rect = vec4(
					windowSize.x - margin - fullTextLength - borderPadding * 2,
					windowSize.y - margin - textHeight,
					windowSize.x - margin + borderPadding,
					windowSize.y - margin);

				DrawUtils::drawRectangle(rect, MC_Color(rcolors), 1.f, 2.f);
				DrawUtils::fillRectangle(rect, MC_Color(12, 12, 12), 1.f);
				DrawUtils::drawText(vec2(rect.x + borderPadding, rect.y), &name, MC_Color(rcolors), nameTextSize);
				DrawUtils::drawText(vec2(rect.x + borderPadding + nameLength, rect.w - 7), &version, MC_Color(rcolors), versionTextSize);

			} else {
				if (partner->Partnered.selected == 0) {

					static std::string name = "Surge";
					static std::string version = "";

					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);
					vec4 rect = vec4(
						windowSize.x - margin - fullTextLength - borderPadding * 2,
						windowSize.y - margin - textHeight,
						windowSize.x - margin + borderPadding,
						windowSize.y - margin);

					DrawUtils::drawRectangle(rect, MC_Color(rcolors), 1.f, 2.f);
					DrawUtils::fillRectangle(rect, MC_Color(12, 12, 12), 1.f);
					DrawUtils::drawText(vec2(rect.x + borderPadding, rect.y), &name, MC_Color(rcolors), nameTextSize);
					DrawUtils::drawText(vec2(rect.x + borderPadding + nameLength, rect.w - 7), &version, MC_Color(rcolors), versionTextSize);
				} else {
					static std::string name = "NG";
					static std::string version = "";

					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);
					vec4 rect = vec4(
						windowSize.x - margin - fullTextLength - borderPadding * 2,
						windowSize.y - margin - textHeight,
						windowSize.x - margin + borderPadding,
						windowSize.y - margin);

					DrawUtils::drawRectangle(rect, MC_Color(rcolors), 1.f, 2.f);
					DrawUtils::fillRectangle(rect, MC_Color(12, 12, 12), 1.f);
					DrawUtils::drawText(vec2(rect.x + borderPadding, rect.y), &name, MC_Color(rcolors), nameTextSize);
					DrawUtils::drawText(vec2(rect.x + borderPadding + nameLength, rect.w - 7), &version, MC_Color(rcolors), versionTextSize);
				}
			}
		}
	}