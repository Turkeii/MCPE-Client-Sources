#include "NoMiningTrace.h"

NoMiningTrace::NoMiningTrace() : IModule(0x0, Category::PLAYER, "Doesnt send destroyBlock packets") {
}

NoMiningTrace::~NoMiningTrace() {
}

const char* NoMiningTrace::getModuleName() {
	return ("NoMiningTrace");
}
