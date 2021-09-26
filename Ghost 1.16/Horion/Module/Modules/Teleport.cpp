#include "Teleport.h"

#include "../../DrawUtils.h"

Teleport::Teleport() : IModule(0, Category::MOVEMENT, "Click a block to teleport to it") {

}

Teleport::~Teleport() {
}

const char* Teleport::getModuleName() {
	return "Teleport";
}