#include "NoHitbox.h"

NoHitbox::NoHitbox() 
	                   : IModule(0x0, Category::EXPLOITS, "0 by 0 hitbox.")
{
	this->registerFloatSetting("Width",  &width,  0.f, 0.f, 4.f);
	this->registerFloatSetting("Height", &height, 0.f, 0.f, 4.f);
}

const char* NoHitbox::getModuleName()
{
	return ("NoHitbox");
}

void NoHitbox::onEnable()
{
	if (auto p = g_Data.getLocalPlayer())
		p->setSize(width, height);
}

void NoHitbox::onDisable()
{
	if (auto p = g_Data.getLocalPlayer())
		p->setSize(1.f, 2.f);
}
