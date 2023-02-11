#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class AntiBot : public IModule {
public:
	bool invisibleCheck = true;
	bool entityIdCheck = true;
	bool hitboxCheck = true;
	bool extraCheck = false;
	bool nameCheck = false;
	bool otherCheck = true;

	std::string name = ("AntiBot");
	SettingEnum mode = this;

	bool isInvisibleCheckEnabled() { return invisibleCheck && this->isEnabled(); }
	bool isEntityIdCheckEnabled() { return entityIdCheck && this->isEnabled(); }
	bool isExtraCheckEnabled() { return this->extraCheck && this->isEnabled(); }
	bool isHitboxCheckEnabled() { return hitboxCheck && this->isEnabled(); }
	bool isOtherCheckEnabled() { return otherCheck && this->isEnabled(); }
	bool isNameCheckEnabled() { return nameCheck && this->isEnabled(); }

	virtual const char* getRawModuleName();
	virtual const char* getModuleName();
	AntiBot();
};