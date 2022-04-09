#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AntiBot : public IModule {
public:
	std::string name = ("AntiBot");
	SettingEnum mode = this;

	bool hitboxCheck = true;
	bool nameCheck = false;
	bool invisibleCheck = true;
	bool entityIdCheck = true;
	bool otherCheck = true;
	bool extraCheck = false;


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
	AntiBot() : IModule(0x0, Category::PLAYER, "Enable this module to filter bots!") {
		registerEnumSetting("Mode", &mode, 0);
		mode.addEntry("Basic", 0);
		mode.addEntry("Advanced", 1);
		registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
		registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
		registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
		registerBoolSetting("Other Check", &otherCheck, otherCheck);
		registerBoolSetting("Extra Check", &extraCheck, extraCheck);
	};
	~AntiBot(){};

	virtual const char* getModuleName() override {
		if (mode.getSelectedValue() == 0) {
			name = std::string("AntiBot ") + std::string("[Basic]");
			return name.c_str();
		} else if (mode.getSelectedValue() == 1) {
			name = std::string("AntiBot ") + std::string("[Advanced]");
			return name.c_str();
		}
	}
};
