#include "Watermark.h"

#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
bool letter = false;
bool sense = false;
SettingEnum mode;
int Watermark::rFloat{255};
int Watermark::gFloat{255};
int Watermark::bFloat{255};
float Watermark::vertical{};
float Watermark::horizontal{};
Watermark::Watermark() : IModule(0x0, Category::HUD, "Show Watermark") {
	mode = SettingEnum(this)
			   .addEntry(EnumEntry("Java", 0))
			   .addEntry(EnumEntry("CSGO", 1))
			   .addEntry(EnumEntry("Gamesense", 2))
			   .addEntry(EnumEntry("None", 3));
	registerEnumSetting("Mode", &mode, 0);
	registerBoolSetting("Text Shadow", &textShadow, textShadow);
	registerBoolSetting("First Letter", &letter, letter);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

Watermark::~Watermark() {
}

const char* Watermark::getModuleName() {
	return ("Watermark");
}
void Watermark::onTick(C_GameMode* gm) {
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
}
void Watermark::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
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
	auto player = g_Data.getLocalPlayer();

	if (mode.selected == 1,2) {
		if (player != nullptr) {
			std::string name = player->getNameTag()->getText();
			std::string fpsText = std::to_string(g_Data.getFPS()/2);
			name = Utils::sanitize(name);
			std::string name1 = "Kek";
			std::string name2 = ".Club+";
			std::string name4 = " | " + name;
			std::string name3 = " | " + fpsText + " FPS";
			std::string textStr = std::string(std::string(WHITE) + name1 + std::string(RESET) + std::string() + name2 + std::string(WHITE) + name3 + name4);
			float lPos = DrawUtils::getTextWidth(&textStr, 1) + 10.f;
			DrawUtils::fillRectangle(vec4_t(8, 6, lPos, 4), MC_Color(255, 0, 0), 10);
			DrawUtils::drawText(vec2_t(8, 6), &textStr, MC_Color(rcolors), 1, 1);
			DrawUtils::fillRectangle(vec4_t(6, 4, lPos, 16), MC_Color(27, 30, 35), opacity);
		}
		if (mode.selected == 0) {
			vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
			constexpr float nameTextSize = 1.0f;
			constexpr float versionTextSize = 0.7f;
			static const float textHeight = (nameTextSize + versionTextSize * 0.7f /* We don't quite want the version string in its own line, just a bit below the name */) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();
			constexpr float borderPadding = 1;
			constexpr float margin = 5;

			static std::string name = "Kek.Club+ ";
#ifdef _DEBUG
			static std::string version = "0.1.0";
#elif defined _BETA
			static std::string version = "beta";
#else
			static std::string version = "public";
#endif
		}
	}
}