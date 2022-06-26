#include "VClipCommand.h"
#include "pch.h"

VClipCommand::VClipCommand() : IMCCommand("vclip", "Teleport up/down", "<Y>") {
	registerAlias("v-clip");
}

bool VClipCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() >= 1);

	if (args->size() == 2) {
		vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;
		vec3_t pos;

		pos.x = 0.f + pPos.x;
		pos.y = assertFloat(args->at(1)) + pPos.y;
		pos.z = 0.f + pPos.z;
		g_Data.getLocalPlayer()->setPos(pos);

		std::string textStr = "VClipped " + args->at(1) + " blocks!";
		//auto notification = g_Data.addNotification("VClip Command:", textStr);
		//notification->duration = 5;
		return true;
	}
	return false;
}