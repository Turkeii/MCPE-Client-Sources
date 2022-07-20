#include "Xray.h"

Xray::Xray() : IModule(VK_NUMPAD6, Category::VISUAL, "X-Ray view!") {

registerBoolSetting("Netherite", &this->debris, this->debris);
registerBoolSetting("Diamonds", &this->diamonds, this->diamonds);
registerBoolSetting("Emeralds", &this->emeralds, this->emeralds);
registerBoolSetting("Iron", &this->iron, this->iron);
registerBoolSetting("Gold", &this->gold, this->gold);
registerBoolSetting("Coal", &this->coal, this->coal);
registerBoolSetting("Redstone", &this->redstone, this->redstone);
registerBoolSetting("Lapis", &this->lapis, this->lapis);
registerBoolSetting("Other", &this->other, this->other);
}

Xray::~Xray() {
}

const char* Xray::getModuleName() {
	return ("X-Ray");
}
