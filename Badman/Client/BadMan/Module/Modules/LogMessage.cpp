#include "LogMessage.h"

Logs::Logs() : IModule(0x0, Category::MISC, "Displays the logs for enabling modules") {
}

Logs::~Logs() {
}

const char* Logs::getModuleName() {
	return ("Logs");
}
