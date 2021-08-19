#include "TextCustomizer.h"

int TextCustomizer::rFloat{ 200 };
int TextCustomizer::gFloat{ 200 };
int TextCustomizer::bFloat{ 200 };
bool TextCustomizer::chroma{};
TextCustomizer::TextCustomizer() : IModule(0, Category::HUD, "Change the color of the UI's text.") {
	registerIntSetting("Red", &rFloat, rFloat, 0, 255);
	registerIntSetting("Green", &gFloat, gFloat, 0, 255);
	registerIntSetting("Blue", &bFloat, bFloat, 0, 255);
	registerBoolSetting("Chroma", &this->chroma, false);
}

TextCustomizer::~TextCustomizer() {

}




const char* TextCustomizer::getModuleName() {
	return ("TextCustomizer");
}
