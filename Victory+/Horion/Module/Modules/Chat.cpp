#include "Chat.h"

Chat::Chat() : IModule(0, Category::MISC, "For testing purposes") {
	//registerBoolSetting("GreenText", &this->bool1, true);
}

Chat::~Chat() {
}

const char* Chat::getModuleName() {
	return "Chat";
}