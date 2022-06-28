#include "Welcome.h"

#include "../../DrawUtils.h"
#include "../ModuleManager.h"
using namespace std;
int Welcome::rFloat{255};
int Welcome::gFloat{255};
int Welcome::bFloat{255};
bool reberse = false;
Welcome::Welcome() : IModule(0x0, Category::HUD, "Welcomes you with various messages") {
	registerEnumSetting("Rainbow", &rainBow, 0);
	rainBow = SettingEnum(this)
				  .addEntry(EnumEntry("Custom Color", 0))
				  .addEntry(EnumEntry("Kek", 1));
	registerEnumSetting("Mode", &TextMode, 0);
	TextMode = SettingEnum(this)
				   .addEntry(EnumEntry("God Bless", 0))
				   .addEntry(EnumEntry("Welcome Back", 1))
				   .addEntry(EnumEntry("Welcome", 2))
				   .addEntry(EnumEntry("Kek.Club+", 3));
	registerBoolSetting("Reverse", &reberse, reberse);

	registerFloatSetting("PrimaryRed", &r1, r1, 0.f, 255.f);
	registerFloatSetting("PrimaryGreen", &g1, g1, 0.f, 255.f);
	registerFloatSetting("PrimaryBlue", &b1, b1, 0.f, 255.f);
	registerFloatSetting("SecondaryRed", &r2, r2, 0.f, 255.f);
	registerFloatSetting("SecondaryGreen", &g2, g2, 0.f, 255.f);
	registerFloatSetting("SecondaryBlue", &b2, b2, 0.f, 255.f);
	registerFloatSetting("Wave Speed", &sped, sped, 0.f, 100.f);

	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

Welcome::~Welcome() {
}

const char* Welcome::getModuleName() {
	return ("Welcome");
}

void Welcome::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	static float rcolors[4];

	if (g_Data.isInGame() && GameData::canUseMoveKeys()) {
		float nameTextSize = scale + 0.5f;
		static const float textHeight = (nameTextSize * 0.7f) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();
		constexpr float borderPadding = 1;
		constexpr float margin = 5;
		std::string playerName = std::string(g_Data.getLocalPlayer()->getNameTag()->getText());

		switch (TextMode.selected) {
		default:
			name = "God Bless Kek.Club+ ";
			break;

		case 1:
			name = "Welcome Back " + playerName;
			break;

		case 2:
			name = "Welcome, " + playerName;
			break;

		case 3:
			name = "Welcome To Kek.Club+ " + playerName + " :^)";
			break;
		}
			switch (rainBow.selected) {
			default:
				pastel = true;
				rainbow = false;
				break;
			case 1:
				pastel = false;
				rainbow = true;
				break;
			}
		float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
		float fullTextLength = nameLength;
		float x = windowSize.x - windowSize.x / 2 - nameLength / 2;
		float y = windowSize.y - windowSize.y;
		vec4_t rect = vec4_t(
			windowSize.x - margin - fullTextLength - borderPadding * 415,
			windowSize.y - margin - textHeight,
			windowSize.x - margin + borderPadding,
			windowSize.y - margin);
		static float rcolors[4];          // Rainbow color array RGBA
		static float disabledRcolors[4];  // Rainbow Colors, but for disabled modules
		static float currColor[4];        // ArrayList colors
		{
			Utils::ApplyRainbow(rcolors, 0.0008f);  // Increase Hue of rainbow color array
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
		if (rainbow) {
			int ind = 1;
			for (char c : name) {
				ind++;
				int charWidth = DrawUtils::getTextWidth(&string(&c), nameTextSize);
				if (reberse) {
					MC_Color arrayColor = DrawUtils::getRainbowWave(5, 1.f, 1, (-ind * (sped * -1)) * 2);
					DrawUtils::drawText(vec2_t(x, y), &string(&c), arrayColor, nameTextSize, 1);
				} else {
					MC_Color arrayColor = DrawUtils::getRainbowWave(5, 1.f, 1, (-ind * sped) * 2);
					DrawUtils::drawText(vec2_t(x, y), &string(&c), arrayColor, nameTextSize, 1);
				}
				x += charWidth;
			}
		} else {
			int ind = 1;
			for (char c : name) {
				ind++;
				int charWidth = DrawUtils::getTextWidth(&string(&c), nameTextSize);
				if (reberse) {
					MC_Color arrayColor = DrawUtils::getWaveRGB(r1, g1, b1, r2, g2, b2, -ind * sped);
					DrawUtils::drawText(vec2_t(x, y), &string(&c), arrayColor, nameTextSize, 1);
				} else {
					MC_Color arrayColor = DrawUtils::getWaveRGB(r1, g1, b1, r2, g2, b2, -ind * (sped * -1));
					DrawUtils::drawText(vec2_t(x, y), &string(&c), arrayColor, nameTextSize, 1);
				}
				x += charWidth;
			}
		}
	}
}