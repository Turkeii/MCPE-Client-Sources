#include "Keystrokes.h"

int Keystrokes::rFloat{255};
int Keystrokes::gFloat{255};
int Keystrokes::bFloat{255};
float Keystrokes::vertical{};
float Keystrokes::horizontal{};


Keystrokes::Keystrokes() : IModule(0x0, Category::HUD, "Edit Keystrokes") {
	registerBoolSetting("Rainbow", &this->rainbow, this->rainbow);
	registerIntSetting("Red", &rFloat, rFloat, 0, 255);
	registerIntSetting("Green", &gFloat, gFloat, 0, 255);
	registerIntSetting("Blue", &bFloat, bFloat, 0, 255);
	registerFloatSetting("Up/Down", &this->vertical, this->vertical, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Left/Right", &this->horizontal, this->horizontal, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
}

Keystrokes::~Keystrokes() {
}

const char* Keystrokes::getModuleName() {
	return ("Keystrokes");
}

void Keystrokes::onPostRender(C_MinecraftUIRenderContext* renderCtx) {

	if (this->isEnabled() && GameData::canUseMoveKeys()) {
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		Keystrokes::drawKeystroke(*input->forwardKey, vec2_t(Keystrokes::horizontal + 32.f, Keystrokes::vertical - 84));
		Keystrokes::drawKeystroke(*input->leftKey, vec2_t(Keystrokes::horizontal + 10.f, Keystrokes::vertical - 62));
		Keystrokes::drawKeystroke(*input->backKey, vec2_t(Keystrokes::horizontal + 32.f, Keystrokes::vertical - 62));
		Keystrokes::drawKeystroke(*input->rightKey, vec2_t(Keystrokes::horizontal + 54.f, Keystrokes::vertical - 62));
		Keystrokes::drawKeystroke(*input->spaceBarKey, vec2_t(Keystrokes::horizontal + 10.f, Keystrokes::vertical - 40));
		Keystrokes::drawLeftMouseKeystroke(vec2_t(Keystrokes::horizontal + 10.f, Keystrokes::vertical - 18));
		Keystrokes::drawRightMouseKeystroke(vec2_t(Keystrokes::horizontal + 43.f, Keystrokes::vertical - 18));
	}
}

void Keystrokes::drawKeystroke(char key, const vec2_t& pos) {
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

	std::string keyString = Utils::getKeybindName(key);
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (key == *input->forwardKey) {
		vec4_t rectPos(
			pos.x,
			pos.y,
			pos.x + 20.f,
			pos.y + 20.f);
		vec2_t textPos(
			(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f) + 0.2f,
			rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat) : MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat), 1.f);
			DrawUtils::drawText(textPos, &keyString, MC_Color(rcolors), 1.f, 1.f);
		}

		if (key == *input->spaceBarKey) {
			if (key == *input->spaceBarKey) keyString = "-";
			vec4_t rectPos(
				pos.x,
				pos.y,
				pos.x + 64.f,
				pos.y + 15.f);
			vec2_t textPos(
				(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
				rectPos.y + 7.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

			DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat) : MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat), 1.f);
			DrawUtils::drawText(textPos, &keyString, MC_Color(255, 255, 255), 1.f, 1.f);
		} else {
			vec4_t rectPos(
				pos.x,
				pos.y,
				pos.x + ((key == *input->spaceBarKey) ? 64.f : 20.f),
				pos.y + ((key == *input->spaceBarKey) ? 15.f : 20.f));
			vec2_t textPos(
				(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
				rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

			DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat) : MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat), 1.f);
	
				DrawUtils::drawText(textPos, &keyString, MC_Color(rcolors), 1.f, 1.f);
			}
		}

		void Keystrokes::drawLeftMouseKeystroke(vec2_t pos) {
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
	std::string keyString;
	keyString = "LMB";
	vec4_t rectPos(
		pos.x,
		pos.y + 2,
		pos.x + 31.f,
		pos.y + 22.f);
	DrawUtils::fillRectangle(rectPos, GameData::GameData::isLeftClickDown() ? MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat) : MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat), 1.f);
	vec2_t textPos(
		(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
		rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);
	
		DrawUtils::drawText(textPos, &keyString, MC_Color(rcolors), 1.f, 1.f);
	}


void Keystrokes::drawRightMouseKeystroke(vec2_t pos) {
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
		std::string keyString;
		keyString = "RMB";
		vec4_t rectPos(
			pos.x,
			pos.y + 2,
			pos.x + 31.f,
			pos.y + 22.f);

		DrawUtils::fillRectangle(rectPos, GameData::GameData::isRightClickDown() ? MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat) : MC_Color(Keystrokes::rFloat, Keystrokes::gFloat, Keystrokes::bFloat), 1.f);

	vec2_t textPos(
		(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f),
		rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		DrawUtils::drawText(textPos, &keyString, MC_Color(rcolors), 1.f, 1.f);
	}
