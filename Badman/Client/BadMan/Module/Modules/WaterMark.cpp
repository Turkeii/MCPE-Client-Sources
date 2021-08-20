#include "WaterMark.h"

WaterMark::WaterMark() : IModule(0x0, Category::GUI, "Displays BadMan water mark") {
}

WaterMark::~WaterMark() {
}

const char* WaterMark::getModuleName() {
	return ("WaterMark");
}
