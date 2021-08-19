#include "AntiBan.h"

AntiBan::AntiBan() : IMCCommand("antiban", "anti ban", "antiban") {
}

AntiBan::~AntiBan() {
}

bool AntiBan::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);

	clientMessageF("Resetting UUID, Please wait.."); 
	clientMessageF("Successfully changed!"); 
	return true;
}