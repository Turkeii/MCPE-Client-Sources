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
#include "Animation.h"
static std::vector<C_Entity> targList;
Animations::Animations() : IModule(0, Category::VISUAL, "animtion custom Developed - KaeruClient") {
	// registerFloatSetting("float1", &this->float1, 0, -10, 10);
	this->registerBoolSetting("Translate", &this->doTranslate, this->doTranslate);
	this->registerBoolSetting("Scale", &this->doScale, this->doScale);
	this->registerBoolSetting("Spin", &this->aroundWorld, this->aroundWorld);
	this->registerFloatSetting("X", &this->xTrans, 0.f, -2.f, 2.f);
	this->registerFloatSetting("Y", &this->yTrans, 0.f, -2.f, 2.f);
	this->registerFloatSetting("Z", &this->zTrans, 0.f, -2.f, 2.f);
	this->registerFloatSetting("ScaleX", &this->xMod, 1.f, 0.f, 2.f);
	this->registerFloatSetting("ScaleY", &this->yMod, 1.f, 0.f, 2.f);
	this->registerFloatSetting("ScaleZ", &this->zMod, 1.f, 0.f, 2.f);
	registerBoolSetting("Reset", &this->redo, this->redo);
	this->registerFloatSetting("RotateX", &this->xRotate, 1.f, 0.f, 2.f);
    this->registerFloatSetting("RotateY", &this->yRotate, 1.f, 0.f, 2.f);
	this->registerFloatSetting("RotateZ", &this->zRotate, 1.f, 0.f, 2.f);
}

Animations::~Animations() {
}

void Animations::onTick(C_GameMode* gm) {
	if (redo) {
		auto aniMod = moduleMgr->getModule<Animations>();
		aniMod->redo = false;
		float1 = 0;
		xMod = 1.f;
		yMod = 1.f;
		zMod = 1.f;

		xTrans = 0.f;
		yTrans = 0.f;
		zTrans = 0.f;

		xRotate = 0.f;
		yRotate = 0.f;
		zRotate = 0.f;
	}
}

const char* Animations::getModuleName() {
	return ("Animation");
}