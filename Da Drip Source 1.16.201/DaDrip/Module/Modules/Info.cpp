#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "Info.h"

Info::Info() : IModule(0x0, Category::HUD, "Displays info about your game") {
	registerBoolSetting("Show FPS", &this->fps, this->fps);
	registerBoolSetting("Show CPS", &this->cps, this->cps);
	registerBoolSetting("Coordinates", &this->coordinates, this->coordinates);
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

Info::~Info() {
}

const char* Info::getModuleName() {
	return ("Info");
}

void Info::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = tabgui ? 6 * f : 0.f;

	if (!(g_Data.getLocalPlayer() == nullptr || !this->fps)) {
		std::string fpsText = "FPS: " + std::to_string(g_Data.getFPS());
		vec4_t rectPos = vec4_t(2.5f, 5.f * scale, len, 15.f * scale);
		vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
		DrawUtils::fillRectangle(rectPos, MC_Color(20, 20, 20), 1.f);
		DrawUtils::drawText(textPos, &fpsText, MC_Color(200, 200, 200), scale);
	}

	if (!(g_Data.getLocalPlayer() == nullptr || !this->cps)) {
		std::string cpsText = "CPS: " + std::to_string(g_Data.getLeftCPS()) + " - " + std::to_string(g_Data.getRightCPS());
		vec4_t rectPos = vec4_t(2.5f, 5.f * scale, len, 15.f * scale);
		vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
		DrawUtils::fillRectangle(rectPos, MC_Color(20, 20, 20), 1.f);
		DrawUtils::drawText(textPos, &cpsText, MC_Color(200, 200, 200), scale);
	}

	if (!(g_Data.getLocalPlayer() == nullptr || !this->coordinates)) {
		vec3_t* pos = g_Data.getLocalPlayer()->getPos();
		int curDim = 0;
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		player->getDimensionId(&curDim);

		if (curDim == 0 || curDim == 2) {
			std::string coordsX = "X: " + std::to_string((int)floorf(pos->x));
			std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y - 1.f));
			std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z));

			vec4_t rectPos = vec4_t(2.5f, startY + 15.f * scale, len, startY + 35.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			vec2_t outLinePos = vec2_t(textPos.x + 0.6f * scale, textPos.y - 0.6f * scale);
			//DrawUtils::fillRectangle(rectPos, MC_Color(20, 20, 20), 1.f);
			if (curDim == 0) {
				std::string coordsText = "Overworld: " + coordsX + " " + coordsY + " " + coordsZ;
				DrawUtils::drawText(outLinePos, &coordsText, MC_Color(0, 0, 0), scale * 1.3f, 1.f, Fonts::SMOOTH);
				DrawUtils::drawText(textPos, &coordsText, MC_Color(255, 255, 255), scale * 1.3f, 1.f, Fonts::SMOOTH);
				startY += f;
			} else if (curDim == 2) {
				std::string coordsText = "End: " + coordsX + " " + coordsY + " " + coordsZ;
				DrawUtils::drawText(outLinePos, &coordsText, MC_Color(0, 0, 0), scale * 1.3f, 1.f, Fonts::SMOOTH);
				DrawUtils::drawText(textPos, &coordsText, MC_Color(255, 255, 255), scale * 1.3f, 1.f, Fonts::SMOOTH);
				startY += f;
			}
			std::string NcoordsX = "X: " + std::to_string((int)floorf(pos->x + 0.001) / 8);
			std::string NcoordsZ = "Z: " + std::to_string((int)floorf(pos->z + 0.001) / 8);
			vec4_t NrectPos = vec4_t(2.5f, startY + 15.f * scale, len, startY + 45.f * scale);
			vec2_t NtextPos = vec2_t(NrectPos.x + 1.5f, NrectPos.y + 1.f);
			vec2_t NoutLinePos = vec2_t(NtextPos.x + 0.6f * scale, NtextPos.y - 0.6f * scale);
			std::string NcoordsText = "Nether: " + NcoordsX + " " + coordsY + " " + NcoordsZ;
			DrawUtils::drawText(NoutLinePos, &NcoordsText, MC_Color(0, 0, 0), scale * 1.3f, 1.f, Fonts::SMOOTH);
			DrawUtils::drawText(NtextPos, &NcoordsText, MC_Color(255, 255, 255), scale * 1.3f, 1.f, Fonts::SMOOTH);
		}

		else if (curDim == 1) {
			std::string coordsX = "X: " + std::to_string((int)floorf(pos->x + 0.001) * 8);
			std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y - 1.f));
			std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z + 0.001) * 8);

			vec4_t rectPos = vec4_t(2.5f, startY + 15.f * scale, len, startY + 35.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			vec2_t outLinePos = vec2_t(textPos.x + 0.6f * scale, textPos.y - 0.6f * scale);
			//DrawUtils::fillRectangle(rectPos, MC_Color(20, 20, 20), 1.f);
			std::string coordsText = "OverWorld: " + coordsX + " " + coordsY + " " + coordsZ;
			DrawUtils::drawText(outLinePos, &coordsText, MC_Color(0, 0, 0), scale * 1.3f, 1.f, Fonts::SMOOTH);
			DrawUtils::drawText(textPos, &coordsText, MC_Color(255, 255, 255), scale * 1.3f, 1.f, Fonts::SMOOTH);
			startY += f;

			std::string NcoordsX = "X: " + std::to_string((int)floorf(pos->x));
			std::string NcoordsZ = "Z: " + std::to_string((int)floorf(pos->z));
			vec4_t NrectPos = vec4_t(2.5f, startY + 15.f * 1, len, startY + 45.f * scale);
			vec2_t NtextPos = vec2_t(NrectPos.x + 1.5f, NrectPos.y + 1.f);
			vec2_t NoutLinePos = vec2_t(NtextPos.x + 0.6f * 1, NtextPos.y - 0.6f * scale);
			std::string NcoordsText = "Nether: " + NcoordsX + " " + coordsY + " " + NcoordsZ;
			DrawUtils::drawText(NoutLinePos, &NcoordsText, MC_Color(0, 0, 0), scale * 1.3f, 1.f, Fonts::SMOOTH);
			DrawUtils::drawText(NtextPos, &NcoordsText, MC_Color(255, 255, 255), scale * 1.3f, 1.f, Fonts::SMOOTH);
		}
	}
}