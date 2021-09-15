#include "ArrayList.h"

#include "../ModuleManager.h"

ArrayList::ArrayList() : IModule(0, Category::VISUAL, "ArrayList") {
	this->registerBoolSetting("Icy Arraylist", &this->ice, this->ice);
	this->registerBoolSetting("RGB Borders", &this->rgb, this->rgb);
	this->registerBoolSetting("RGB text", &this->rgbtext, this->rgbtext);
	this->registerBoolSetting("Better Colors", &this->different, this->different);
	this->registerBoolSetting("Side Bar", &this->bar, this->bar);
	this->registerBoolSetting("Bottom Bar", &this->underbar, this->underbar);
	this->registerBoolSetting("Bottom Right", &this->bottom, this->bottom);
	registerFloatSetting("Opacity", &this->opacity, this->opacity, 0.f, 1.f);
}

ArrayList::~ArrayList() {
}

const char* ArrayList::getModuleName() {
	return "ArrayList";
}