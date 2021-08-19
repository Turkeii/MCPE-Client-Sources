#include "Keystrokes.h"


float Keystrokes::rFloat{255};
float Keystrokes::gFloat{255};
float Keystrokes::bFloat{255};
float Keystrokes::vertical{};
float Keystrokes::horizontal{};
bool Keystrokes::cps{true};
bool Keystrokes::chroma{false};
bool Keystrokes::outline{false};

Keystrokes::Keystrokes() : IModule(0x0, Category::HUD, "Edit Keystrokes") {
	registerBoolSetting("Outline", &this->outline, false);
	registerFloatSetting("Outline Red", &rFloat, rFloat, 0, 255);
	registerFloatSetting("Outline Green", &gFloat, gFloat, 0, 255);
	registerFloatSetting("Outline Blue", &bFloat, bFloat, 0, 255);
	registerBoolSetting("CPS", &this->cps, false);
	registerBoolSetting("Chroma", &this->chroma, false);
	registerFloatSetting("Up/Down", &this->vertical, this->vertical, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Left/Right", &this->horizontal, this->horizontal, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
}

Keystrokes::~Keystrokes() {
}

const char* Keystrokes::getModuleName() {
	return ("Keystrokes");
}

void Keystrokes::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	{
		if (this->isEnabled() && GameData::canUseMoveKeys()) {
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(Keystrokes::horizontal + 32.f, Keystrokes::vertical - 84));
			DrawUtils::drawKeystroke(*input->leftKey, vec2_t(Keystrokes::horizontal + 10.f, Keystrokes::vertical - 62));
			DrawUtils::drawKeystroke(*input->backKey, vec2_t(Keystrokes::horizontal + 32.f, Keystrokes::vertical - 62));
			DrawUtils::drawKeystroke(*input->rightKey, vec2_t(Keystrokes::horizontal + 54.f, Keystrokes::vertical - 62));
			DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(Keystrokes::horizontal + 10.f, Keystrokes::vertical - 40));
			DrawUtils::drawLeftMouseKeystroke(vec2_t(Keystrokes::horizontal + 10.f, Keystrokes::vertical - 18));
			DrawUtils::drawRightMouseKeystroke(vec2_t(Keystrokes::horizontal + 43.f, Keystrokes::vertical - 18));
		}
	}
}