#include "TextCustomizer.h"
#include "AltTheme.h"

float TextCustomizer::rFloat{AltTheme::rFloat};
float TextCustomizer::gFloat{AltTheme::gFloat};
float TextCustomizer::bFloat{AltTheme::bFloat};
bool TextCustomizer::chroma{};
TextCustomizer::TextCustomizer() : IModule(0, Category::GUI, "Change the color of the UI's text.") {
	registerFloatSetting("Red", &rFloat, 0.7f, 0, 1);
	registerFloatSetting("Green", &gFloat, 0.7f, 0, 1);
	registerFloatSetting("Blue", &bFloat, 1.f, 0, 1);
	//registerBoolSetting("Chroma", &this->chroma, false);
}

TextCustomizer::~TextCustomizer() {
}

const char* TextCustomizer::getModuleName() {
	return ("TextCustomizer");
}
