#include "ViewModel.h"

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
static std::vector<C_Entity*> targList;
ViewModel::ViewModel() : IModule(0, Category::VISUAL, "Custom item view model") {
	//registerFloatSetting("float1", &this->float1, 0, -10, 10);
	this->registerBoolSetting("Translate", &this->doTranslate, this->doTranslate);
	this->registerBoolSetting("Scale", &this->doScale, this->doScale);
	//this->registerBoolSetting("Rotate", &this->doRotate, this->doRotate);

	this->registerFloatSetting("TranslateX", &this->xTrans, 0.f, -2.f, 2.f);
	this->registerFloatSetting("TranslateY", &this->yTrans, 0.f, -2.f, 2.f);
	this->registerFloatSetting("TranslateZ", &this->zTrans, 0.f, -2.f, 2.f);

	this->registerFloatSetting("ScaleX", &this->xMod, 1.f, 0.f, 2.f);
	this->registerFloatSetting("ScaleY", &this->yMod, 1.f, 0.f, 2.f);
	this->registerFloatSetting("ScaleZ", &this->zMod, 1.f, 0.f, 2.f);

	//this->registerFloatSetting("RotateX", &this->xRotate, 1.f, 0.f, 2.f);
	//this->registerFloatSetting("RotateY", &this->yRotate, 1.f, 0.f, 2.f);
	//this->registerFloatSetting("RotateZ", &this->zRotate, 1.f, 0.f, 2.f);
}

ViewModel::~ViewModel() {
}

const char* ViewModel::getModuleName() {
	return "ViewModel";
}
