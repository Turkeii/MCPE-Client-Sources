#include "Safewalk.h"

Safewalk::Safewalk() : IModule(0, Category::MOVEMENT, "SafeWalk") {

}

const char* Safewalk::getModuleName() {
	return "SafeWalk";
}