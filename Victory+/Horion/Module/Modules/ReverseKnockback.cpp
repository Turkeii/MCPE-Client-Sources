#include "ReverseKnockBack.h"

ReverseKnockBack::ReverseKnockBack() : IModule(0, Category::MOVEMENT, "Reverse knockback again") {
}

ReverseKnockBack::~ReverseKnockBack() {
}

const char* ReverseKnockBack::getModuleName() {
	return ("ReverseKnockBack");
}
