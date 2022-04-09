#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Coordinates : public IModule {
public:
	float scale = 1.f;
	float coordsX = 412.f;
	float coordsY = 314.f;

	Coordinates() : IModule(0x0, Category::GUI, "Tells the player their coords") {
		registerFloatSetting("CoordinatesX", &coordsX, coordsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
		registerFloatSetting("CoordinatesY", &coordsY, coordsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
		registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	};
	~Coordinates(){};

	void onPostRender(C_MinecraftUIRenderContext* renderCtx) {
		if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
			std::string tempStr("Movement");
			float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
			float f = 10.f * this->scale;

			if (!(g_Data.getLocalPlayer() == nullptr)) {
				vec3* pos = g_Data.getLocalPlayer()->getPos();
				float yVal = coordsY;
				float xVal = coordsX;
				int curDim = 0;
				C_LocalPlayer* player = g_Data.getLocalPlayer();
				player->getDimensionId(&curDim);

				if (curDim == 0 || curDim == 2) {
					std::string coordsX = "X: " + std::to_string((int)floorf(pos->x));
					std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y - 1.f));
					std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z));

					vec4 rectPos = vec4(2.5f, yVal + 15.f * scale - 0.001f, len, yVal + 35.f * scale - 0.001f);
					vec2 textPos = vec2(xVal, yVal);
					vec2 outLinePos = vec2(textPos.x + 0.6f * scale - 0.001f, textPos.y - 0.6f * scale - 0.001f);
					if (curDim == 0) {
						std::string coordsText = "XYZ: " + coordsX + " " + coordsY + " " + coordsZ;

						DrawUtils::drawText(textPos, &coordsText, MC_Color(184, 0, 255), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
						yVal += f;
					} else if (curDim == 2) {
						std::string coordsText = "End: " + coordsX + " " + coordsY + " " + coordsZ;
						DrawUtils::drawText(textPos, &coordsText, MC_Color(255, 255, 555), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
						yVal += f;
					}
					std::string NcoordsX = "X: " + std::to_string((int)floorf(pos->x + 0.001f) / 8);
					std::string NcoordsZ = "Z: " + std::to_string((int)floorf(pos->z + 0.001f) / 8);
					vec4 NrectPos = vec4(2.5f, yVal + 15.f * scale - 0.001f, len, yVal + 45.f * scale - 0.001f);
					vec2 NtextPos = vec2(xVal, yVal);
					vec2 NoutLinePos = vec2(NtextPos.x + 0.6f * scale - 0.001f, NtextPos.y - 0.6f * scale - 0.001f);
					std::string NcoordsText = "Nether: " + NcoordsX + " " + coordsY + " " + NcoordsZ;

					DrawUtils::drawText(NtextPos, &NcoordsText, MC_Color(184, 0, 255), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
				}

				else if (curDim == 1) {
					std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y - 1.f));
					std::string NcoordsX = "X: " + std::to_string((int)floorf(pos->x));
					std::string NcoordsZ = "Z: " + std::to_string((int)floorf(pos->z));
					vec4 NrectPos = vec4(2.5f, yVal + 15.f * 1, len, yVal + 35.f * scale - 0.001f);
					vec2 NtextPos = vec2(xVal, yVal);
					vec2 NoutLinePos = vec2(NtextPos.x + 0.6f * 1, NtextPos.y - 0.6f * scale - 0.001f);
					std::string NcoordsText = "Nether: " + NcoordsX + " " + coordsY + " " + NcoordsZ;

					DrawUtils::drawText(NtextPos, &NcoordsText, MC_Color(184, 0, 255), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
					yVal += f;

					std::string coordsX = "X: " + std::to_string((int)floorf(pos->x + 0.001f) * 8);
					std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z + 0.001f) * 8);

					vec4 rectPos = vec4(2.5f, yVal + 15.f * scale - 0.001f, len, yVal + 45.f * scale - 0.001f);
					vec2 textPos = vec2(xVal, yVal);
					vec2 outLinePos = vec2(textPos.x + 0.6f * scale - 0.001f, textPos.y - 0.6f * scale - 0.001f);
					std::string coordsText = "XYZ: " + coordsX + " " + coordsY + " " + coordsZ;

					DrawUtils::drawText(textPos, &coordsText, MC_Color(184, 0, 255), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
				}
			}
		}
	}

	virtual const char* getModuleName() override {
		return "Coordinates";
	}
};