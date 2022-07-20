#include "InventoryView.h"
#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"
#include "../../../Utils/Logger.h"


InventoryView::InventoryView() : IModule(0x0, Category::GUI, "renders inventory on screen") {
registerFloatSetting("invPosX", &this->invX, this->invX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
registerFloatSetting("invPosY", &this->invY, this->invY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
}

InventoryView::~InventoryView() {
}

const char* InventoryView::getModuleName() {
	return ("InventoryView");
}

float xDiff2 = -1.f;
float yDiff2 = -1.f;

void InventoryView::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
	vec2_t mousePosition = *g_Data.getClientInstance()->getMousePos();
	mousePosition = mousePosition.div(windowSizeReal);
	mousePosition = mousePosition.mul(windowSize);
	static auto hudEditorMod = moduleMgr->getModule<HudEditor>();

	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		C_PlayerInventoryProxy* supplies2 = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* inv2 = supplies2->inventory;
		g_Data.getLocalPlayer()->getSupplies()->inventory;
		vec2_t invPos = vec2_t(100.f, 100.f);
		vec2_t invPos2 = vec2_t(100.f, 120.f);
		C_ItemStack* test = inv2->getItemStack(1);
		C_ItemStack* test2 = inv2->getItemStack(2);
		float testF = 100.f;
		float sideBars = 1.5f;
		float yVal = invY + sideBars;

		xVal = invX + sideBars;

		static float rcolors[4];
		static auto ThemeMod = moduleMgr->getModule<Theme>();
		if (ThemeMod->rainbow) {
			if (rcolors[3] < 1) {
				rcolors[0] = 1;
				rcolors[1] = 0.2f;
				rcolors[2] = 0.2f;
				rcolors[3] = 1;
			}

			Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);  // perfect code, dont question this

			rcolors[0] += 0.0015f;
			if (rcolors[0] >= 1) {
				rcolors[0] = 0;
			}

			Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
			DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], 1.f);
		} else {
			DrawUtils::setColor(Theme::rFloat, Theme::gFloat, Theme::bFloat, 1.f);
		}
		DrawUtils::drawRectangle(vec2_t(invX, invY), vec2_t(invX + 150.f + sideBars, invY + 60.f + sideBars), sideBars / 2);

		for (int j = 9; j < 18; j++) {
			if ((inv2->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(inv2->getItemStack(j), vec2_t(xVal, yVal + 0.f), 1.f, 1.f - .30f, false);
				char stackAmount = inv2->getItemStack(j)->count;
				std::string stackStr = std::to_string(inv2->getItemStack(j)->count);
				if (inv2->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2_t(xVal + 6.5f, (yVal + 0.f) + 9.5f), &stackStr, MC_Color(Background::rFloat, Background::gFloat, Background::bFloat), 1.f - .20f);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
		for (int j = 18; j < 27; j++) {
			if ((inv2->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(inv2->getItemStack(j), vec2_t(xVal + 27.f, yVal + 20.f), 1.f, 1.f - .30f, false);
				std::string stackStr = std::to_string(inv2->getItemStack(j)->count);
				if (inv2->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2_t(xVal + 33.5f, (yVal + 20.f) + 9.5f), &stackStr, MC_Color(Background::rFloat, Background::gFloat, Background::bFloat), 1.f - .20f);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
		for (int j = 27; j < 36; j++) {
			if ((inv2->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(inv2->getItemStack(j), vec2_t(xVal + 54.f, yVal + 40.f), 1.f, 1.f - .30f, false);
				std::string stackStr = std::to_string(inv2->getItemStack(j)->count);
				if (inv2->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2_t(xVal + 60.5f, (yVal + 40.f) + 9.5f), &stackStr, MC_Color(Background::rFloat, Background::gFloat, Background::bFloat), 1.f - .20f);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;

		if (hudEditorMod->isEnabled()) {
			if ((mousePosition.x >= invX && mousePosition.x <= invX + 180.f + sideBars) && (mousePosition.y >= invY && mousePosition.y <= invY + 60.f + sideBars)) {
				if (!g_Data.isLeftClickDown()) {
					xDiff2 = mousePosition.x - invX;
					yDiff2 = mousePosition.y - invY;
				}

				if (xDiff2 <= 0.f) {
					xDiff2 = 40.f;
				}

				if (yDiff2 <= 0.f) {
					yDiff2 = 40.f;
				}

				DrawUtils::setColor(0.7f, 0.7f, 0.7f, 0.8f);
				DrawUtils::fillRectangle(vec2_t(invX, invY), vec2_t(invX + 180.f + sideBars, invY + 60.f + sideBars));

				if (g_Data.isLeftClickDown()) {
					if (mousePosition.x - xDiff2 >= 1.f) {
						invX = mousePosition.x - xDiff2;
					} else {
						invX = mousePosition.x;
					}

					if (mousePosition.y - yDiff2 >= 1.f) {
						invY = mousePosition.y - yDiff2;
					} else {
						invY = mousePosition.y;
					}  //*/
					   //	pvpX = mousePosition.x;
					   //	pvpY = mousePosition.y;

					DrawUtils::setColor(0, 1, 1, 1);
					DrawUtils::drawLine(vec2_t(0, 0), mousePosition, 0.5f);
				}
			}
		}
	}
}