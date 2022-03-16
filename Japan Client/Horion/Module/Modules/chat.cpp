#include "chat.h"

Chat::Chat() : IModule(0, Category::CUSTOM, "For Chat purposes Japan") {
	registerBoolSetting("GreenText", &this->greentext, true);
}

Chat::~Chat() {
}

const char* Chat::getModuleName() {
	return "Chat+";
}