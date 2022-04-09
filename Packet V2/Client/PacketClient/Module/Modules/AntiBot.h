#pragma once
#include "Module.h"
class AntiBot : public IModule {
public:
	bool hitboxCheck = true;
	bool nameCheck = false;
	bool invisibleCheck = true;
	bool entityIdCheck = true;
	bool otherCheck = true;
	bool extraCheck = false;

	AntiBot();
	~AntiBot();

	std::string name = ("AntiBot");
	SettingEnum mode = this;

	bool isHitboxCheckEnabled() {
		return hitboxCheck && this->isEnabled();
	}
	bool isNameCheckEnabled() {
		return nameCheck && this->isEnabled();
	}
	bool isInvisibleCheckEnabled() {
		return invisibleCheck && this->isEnabled();
	}
	bool isEntityIdCheckEnabled() {
		return entityIdCheck && this->isEnabled();
	}
	bool isOtherCheckEnabled() {
		return otherCheck && this->isEnabled();
	}
	bool isExtraCheckEnabled() {
		return this->extraCheck && this->isEnabled();
	}

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
};
