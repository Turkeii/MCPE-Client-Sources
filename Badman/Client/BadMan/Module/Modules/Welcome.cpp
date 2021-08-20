#include "Welcome.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

Welcome::Welcome() : IModule(0x0, Category::GUI, "Welcomes you at the top of the screen") {
	registerEnumSetting("Text Modes", &TextMode, 0);
	TextMode = SettingEnum(this)
					 .addEntry(EnumEntry("Welcome", 0))
					 .addEntry(EnumEntry("Hello", 1))
					 .addEntry(EnumEntry("Brooda", 2))
					 .addEntry(EnumEntry("BadMan", 3));
	
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
		std::string playerName = std::string(g_Data.getLocalPlayer()->getNameTag()->getText()) + "§r";

		switch (TextMode.selected) {
		default:
			name = "welcome " + playerName;
		break;

		case 1:
			name = "Hello " + playerName + " :^)";
		break;

		case 2:
			name = "salamu alaykum " + playerName;
		break;

		case 3:
			name = "welcome to BadMan " + playerName;
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

		static auto ThemeMod = moduleMgr->getModule<Theme>();
		if (ThemeMod->rainbow) {
			if (rcolors[3] < 1) {
				rcolors[0] = 1;
				rcolors[1] = 0.2f;
				rcolors[2] = 0.2f;
				rcolors[3] = 1;
			}

			Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);  // perfect code, dont question this

			rcolors[0] += 0.0015f;
			if (rcolors[0] >= 1) {
				rcolors[0] = 0;
			}

			Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
			DrawUtils::drawText(vec2_t(x, y), &name, MC_Color(rcolors), nameTextSize);
		} else {
			DrawUtils::drawText(vec2_t(x, y), &name, MC_Color(Theme::rFloat, Theme::gFloat, Theme::bFloat), nameTextSize);
		}
	}
}
