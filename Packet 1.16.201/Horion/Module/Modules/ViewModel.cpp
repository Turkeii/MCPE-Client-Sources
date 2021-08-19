#include "ViewModel.h"

ViewModel::ViewModel() : IModule(0, Category::VISUAL, "fucurn") {
}

const char* ViewModel::getModuleName() {
	return "ViewModel";
}