#include "Coordinates.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"

Coordinates::Coordinates() : IModule(0x0, Category::GUI, "Tells the player their coords") {
	registerFloatSetting("CoordsX", &this->coordsX, this->coordsX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("CoordsY", &this->coordsY, this->coordsY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

Coordinates::~Coordinates() {
}

const char* Coordinates::getModuleName() {
	return ("Coordinates");
}

void Coordinates::onPostRender(C_MinecraftUIRenderContext* renderCtx){
	
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		std::string tempStr("Movement");
		float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
		float f = 10.f * this->scale;

		if (!(g_Data.getLocalPlayer() == nullptr)) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();
			float yVal = coordsY;
			float xVal = coordsX;
			int curDim = 0;
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			player->getDimensionId(&curDim);

			if (curDim == 0 || curDim == 2) {
				std::string coordsX = "X: " + std::to_string((int)floorf(pos->x));
				std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y - 1.f));
				std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z));

				vec4_t rectPos = vec4_t(2.5f, yVal + 15.f * scale - 0.001f, len, yVal + 35.f * scale - 0.001f);
				vec2_t textPos = vec2_t(xVal, yVal);
				vec2_t outLinePos = vec2_t(textPos.x + 0.6f * scale - 0.001f, textPos.y - 0.6f * scale - 0.001f);
				//DrawUtils::fillRectangle(rectPos, MC_Color(20, 20, 20), 1.f);
				if (curDim == 0) {
					std::string coordsText = "XYZ: " + coordsX + " " + coordsY + " " + coordsZ;
					DrawUtils::drawText(textPos, &coordsText, MC_Color(AltTheme::rFloat, AltTheme::gFloat, AltTheme::bFloat), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
					yVal += f;
				} else if (curDim == 2) {
					std::string coordsText = "End: " + coordsX + " " + coordsY + " " + coordsZ;
					DrawUtils::drawText(textPos, &coordsText, MC_Color(AltTheme::rFloat, AltTheme::gFloat, AltTheme::bFloat), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
					yVal += f;
				}
				std::string NcoordsX = "X: " + std::to_string((int)floorf(pos->x + 0.001) / 8);
				std::string NcoordsZ = "Z: " + std::to_string((int)floorf(pos->z + 0.001) / 8);
				vec4_t NrectPos = vec4_t(2.5f, yVal + 15.f * scale - 0.001f, len, yVal + 45.f * scale - 0.001f);
				vec2_t NtextPos = vec2_t(xVal, yVal);
				vec2_t NoutLinePos = vec2_t(NtextPos.x + 0.6f * scale - 0.001f, NtextPos.y - 0.6f * scale - 0.001f);
				std::string NcoordsText = "Nether: " + NcoordsX + " " + coordsY + " " + NcoordsZ;
				DrawUtils::drawText(NtextPos, &NcoordsText, MC_Color(AltTheme::rFloat, AltTheme::gFloat, AltTheme::bFloat), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
			}

			else if (curDim == 1) {
				std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y - 1.f));
				std::string NcoordsX = "X: " + std::to_string((int)floorf(pos->x));
				std::string NcoordsZ = "Z: " + std::to_string((int)floorf(pos->z));
				vec4_t NrectPos = vec4_t(2.5f, yVal + 15.f * 1, len, yVal + 35.f * scale - 0.001f);
				vec2_t NtextPos = vec2_t(xVal, yVal);
				vec2_t NoutLinePos = vec2_t(NtextPos.x + 0.6f * 1, NtextPos.y - 0.6f * scale - 0.001f);
				std::string NcoordsText = "Nether: " + NcoordsX + " " + coordsY + " " + NcoordsZ;
				DrawUtils::drawText(NtextPos, &NcoordsText, MC_Color(AltTheme::rFloat, AltTheme::gFloat, AltTheme::bFloat), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
				yVal += f;

				std::string coordsX = "X: " + std::to_string((int)floorf(pos->x + 0.001) * 8);
				std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z + 0.001) * 8);

				vec4_t rectPos = vec4_t(2.5f, yVal + 15.f * scale - 0.001f, len, yVal + 45.f * scale - 0.001f);
				vec2_t textPos = vec2_t(xVal, yVal);
				vec2_t outLinePos = vec2_t(textPos.x + 0.6f * scale - 0.001f, textPos.y - 0.6f * scale - 0.001f);
				//DrawUtils::fillRectangle(rectPos, MC_Color(20, 20, 20), 1.f);
				std::string coordsText = "XYZ: " + coordsX + " " + coordsY + " " + coordsZ;
				DrawUtils::drawText(textPos, &coordsText, MC_Color(AltTheme::rFloat, AltTheme::gFloat, AltTheme::bFloat), scale - 0.001f * 1.3f, 1.f, Fonts::SMOOTH);
			}
		}
	}
}
