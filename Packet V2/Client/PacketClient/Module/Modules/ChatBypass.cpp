#include "ChatBypass.h"

ChatBypass::ChatBypass() : IModule(0, Category::MISC, "Description") {
}

const char* ChatBypass::getModuleName() {
	return "ChatBypass";
}