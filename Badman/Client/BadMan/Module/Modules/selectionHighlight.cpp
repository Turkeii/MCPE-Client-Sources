#include "selectionHighlight.h"

#include "../../../Utils/Target.h"
selectionHighlight::selectionHighlight() : IModule(0x0, Category::VISUAL, "Custom selection box!") {
	registerFloatSetting("Thickness", &this->thickness, this->thickness, 0.f, 1.f);
	registerFloatSetting("Opacity", &this->opacityVal, this->opacityVal, 0.f, 1.f);
	registerBoolSetting("Outline", &this->doOutline, this->doOutline);
	registerBoolSetting("Rainbow", &this->selectRainbow, this->selectRainbow);
	registerFloatSetting("Red", &this->rSelect, this->rSelect, 0.f, 1.f);
	registerFloatSetting("Green", &this->gSelect, this->gSelect, 0.f, 1.f);
	registerFloatSetting("Blue", &this->bSelect, this->bSelect, 0.f, 1.f);
	//registerBoolSetting("FaceHighlight", &this->faceH, this->faceH);
	//registerFloatSetting("FaceOpacity", &this->fOpacity, this->fOpacity, 0.f, 1.f);
}

selectionHighlight::~selectionHighlight() {
}

const char* selectionHighlight::getModuleName() {
	return ("Selection Highlight");
}

void selectionHighlight::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	float customHighlight[4];

	customHighlight[0] = rSelect;
	customHighlight[1] = rSelect;
	customHighlight[2] = rSelect;
	customHighlight[3] = 1.f;

	static float rainbowColors[4];
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		{
			if (rainbowColors[3] < 1) {
				rainbowColors[0] = 0.2f;
				rainbowColors[1] = 0.2f;
				rainbowColors[2] = 1.f;
				rainbowColors[3] = 1;
			}

			Utils::ApplyRainbow(rainbowColors, 0.0015f);
		}  //0.0015f

		if (g_Data.getLocalPlayer() != nullptr) {
			float mC = thickness / 2;
			auto pStruct = g_Data.getClientInstance()->getPointerStruct();

			vec3_t hLower = pStruct->block.toVec3t();
			hLower = hLower.floor();
			vec3_t hUpper = pStruct->block.toVec3t();
			hUpper = hUpper.floor();
			hUpper.x += 1.f;
			hUpper.y += 1.f;
			hUpper.z += 1.f;

			if (selectRainbow) {
				int face = pStruct->blockSide;
				int rayType = pStruct->rayHitType;
				if (rayType == 0) {
					DrawUtils::setColor(rainbowColors[0], rainbowColors[1], rainbowColors[2], opacityVal);
					DrawUtils::drawBox(hLower, hUpper, thickness, doOutline);
				}

				if (faceH) {
					if (face == 1) {
						DrawUtils::setColor(rainbowColors[0], rainbowColors[1], rainbowColors[2], fOpacity);

						//top
						vec2_t a1 = DrawUtils::worldToScreen(vec3_t(hUpper.x, hUpper.y, hUpper.z));
						vec2_t a2 = DrawUtils::worldToScreen(vec3_t(hUpper.x, hUpper.y, hUpper.z - 1.f));
						//bottom
						vec2_t a3 = DrawUtils::worldToScreen(vec3_t(hUpper.x, hUpper.y - 1.f, hUpper.z));
						vec2_t a4 = DrawUtils::worldToScreen(vec3_t(hUpper.x, hUpper.y - 1.f, hUpper.z - 1.f));

						//DrawUtils::drawQuad(a1, a2, a3, a4);
					}

					//DrawUtils::drawText(vec2_t(100.f, 100.f), &std::string(std::to_string(face) + " " + std::to_string(rayType)), MC_Color(255, 0, 0));
				}

			} else {
				int rayType = pStruct->rayHitType;
				if (rayType == 0) {
					DrawUtils::setColor(rSelect, gSelect, bSelect, opacityVal);
					DrawUtils::drawBox(hLower, hUpper, thickness, doOutline);
				}

				if (faceH) {
				}
			}
		}
	}
}