#include <array>
#include <deque>
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_relational.hpp>
#include <glm/ext/matrix_transform.hpp>  // perspective, translate, rotate
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>  //radians

#include "../../../SDK/MatrixStack.h"
#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "Animations.h"

Animations::Animations() : IModule(0, Category::VISUAL, "Changes the swing/hitting animation") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("None", 0);
	mode.addEntry("1.7", 1);
	mode.addEntry("Spin", 2);
	registerBoolSetting("SmoothSwing", &smoothSwing, smoothSwing);
	registerFloatSetting("X", &xPos, 0.f, -3.f, 3.f);
	registerFloatSetting("Y", &yPos, 0.f, -3.f, 3.f);
	registerFloatSetting("Z", &zPos, 0.f, -3.f, 3.f);
	//registerFloatSetting("ScaleX", &xScale, 1.f, 0.f, 2.f);
	//registerFloatSetting("ScaleY", &yScale, 1.f, 0.f, 2.f);
	//registerFloatSetting("ScaleZ", &zScale, 1.f, 0.f, 2.f);
	registerBoolSetting("Reset", &reset, reset);
}

Animations::~Animations() {
}

const char* Animations::getRawModuleName() {
	return "Animations";
}

const char* Animations::getModuleName() {
	if (mode.getSelectedValue() == 0) name = std::string("Animations");
	if (mode.getSelectedValue() == 1) name = std::string("Animations ") + std::string(GRAY) + std::string("1.7");
	if (mode.getSelectedValue() == 2) name = std::string("Animations ") + std::string(GRAY) + std::string("Spin");
	return name.c_str();
}

void Animations::onEnable() {
	if (smoothSwing) {

	}
}

void Animations::onTick(C_GameMode* gm) {
	auto slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot);
	auto killaura = moduleMgr->getModule<Killaura>();
	shouldBlock = slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon() && g_Data.isRightClickDown() || slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon() && !killaura->targetListEmpty && killaura->isEnabled();
	if (reset) {
		xScale = 1.f;
		yScale = 1.f;
		zScale = 1.f;
		xPos = 0.f;
		yPos = 0.f;
		zPos = 0.f;
		reset = false;
	}
}

void Animations::onDisable() {
	if (smoothSwing) {

	}
}