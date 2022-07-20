#include "ServerInfo.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"

ServerInfo::ServerInfo() : IModule(0x0, Category::GUI, "shows the server ip and port of the current server") {
	registerFloatSetting("ServerX", &this->serverInfX, this->serverInfX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("ServerY", &this->serverInfY, this->serverInfY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

ServerInfo::~ServerInfo() {
}

const char* ServerInfo::getModuleName() {
	return ("ServerInfo");
}

void ServerInfo::onPostRender(C_MinecraftUIRenderContext* renderCtx){
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		if (g_Data.getLocalPlayer() != nullptr || g_Data.getRakNetInstance()->isonaServer()) {
			auto Server = g_Data.getRakNetInstance();
			if (Server == nullptr) return;

			float yVal = serverInfY;
			float xVal = serverInfX;

			std::string IP = Server->serverIp.getText();
			std::string Port = std::to_string(Server->serverPort).c_str();

			vec2_t textPos = vec2_t(xVal, yVal);

			if (Server->serverIp.getTextLength() < 1) {
				IP = "Local World";
			}
			std::string ServerText = "IP: " + IP + " \nPort: " + Port;

			DrawUtils::drawText(textPos, &ServerText, MC_Color(0.7f, 0.7f, 1.f), scale - 0.001f * 1.3f, 0.7f, Fonts::SMOOTH);
		}
	}
}
