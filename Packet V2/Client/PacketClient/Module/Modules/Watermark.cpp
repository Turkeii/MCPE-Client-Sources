#include "Watermark.h"

Watermark::Watermark() : IModule(0, Category::VISUAL, "as") {
	registerBoolSetting("FirstLetter", &firstLetter, &firstLetter);
	registerEnumSetting("Theme", &mode, 0);
	mode.addEntry("Simple", 0);
	mode.addEntry("New", 1);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

Watermark::~Watermark() {
}

const char* Watermark::getModuleName() {
	return ("Watermark");
}
