#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class ServerInfo : public IModule {
public:
	float scale = 1.f;
	float serverInfoX = 0.f;
	float serverInfoY = 300.5f;

	ServerInfo() : IModule(0x0, Category::GUI, "shows the server ip and port of the current server") {
		registerFloatSetting("ServerX", &serverInfoX, serverInfoX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
		registerFloatSetting("ServerY", &serverInfoY, serverInfoY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
		registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	};
	~ServerInfo(){};

	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
			if (g_Data.getLocalPlayer() != nullptr || g_Data.getRakNetInstance()->isonaServer()) {
				auto Server = g_Data.getRakNetInstance();
				if (Server == nullptr) return;

				float yVal = serverInfoY;
				float xVal = serverInfoX;

				std::string serverIp = Server->serverIp.getText();
				std::string numericalIp = Server->numericalIp.getText();
				std::string Port = std::to_string(Server->serverPort).c_str();

				vec2 textPos = vec2(xVal, yVal);

				if (Server->serverIp.getTextLength() < 1) {
					serverIp = "Local World",Port = "Local World";
				}
				std::string ServerText = "IP: " + serverIp + " \nPort: " + Port;

					DrawUtils::drawText(vec2{textPos}, &ServerText, MC_Color(184, 0, 255), scale);
				}
			}
		}

	virtual const char* getModuleName() override {
		return "ServerInfo";
	}
};