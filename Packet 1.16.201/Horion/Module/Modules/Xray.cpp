#include "Xray.h"

Xray::Xray() : IModule(0, Category::VISUAL, "X-Ray view!") {
}

Xray::~Xray() {
}

const char* Xray::getModuleName() {
	return ("Xray");
}
