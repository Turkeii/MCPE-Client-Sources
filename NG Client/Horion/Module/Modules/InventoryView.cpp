#include "InventoryView.h"
#include "../../../Utils/Logger.h"
#include "../../DrawUtils.h"
#include "../../Module/ModuleManager.h"
#include "../ModuleManager.h"

float InventoryView::rtext{1.f};
float InventoryView::gtext{1.f};
float InventoryView::btext{1.f};

	InventoryView::InventoryView():IModule(0x0, Category::GUI, "renders inventory on screen") {
	registerFloatSetting("invPosX", &invX, invX, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.x);
	registerFloatSetting("invPosY", &invY, invY, 0.f, g_Data.getClientInstance()->getGuiData()->windowSize.y);
	registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f);
	registerFloatSetting("Red", &rtext, rtext, 0.f, 1.f);
	registerFloatSetting("Green", &gtext, gtext, 0.f, 1.f);
	registerFloatSetting("Blue", &btext, btext, 0.f, 1.f);
	registerBoolSetting("RGB", &RGB, RGB);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
	}

InventoryView::~InventoryView() {
}

const char* InventoryView::getModuleName() {
	return ("InvView");
}

static float currColor[4];

void InventoryView::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	static auto partner = moduleMgr->getModule<Partner>();
	if (!(g_Data.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		C_PlayerInventoryProxy* itemnun = g_Data.getLocalPlayer()->getSupplies();
		C_Inventory* item = itemnun->inventory;
		g_Data.getLocalPlayer()->getSupplies()->inventory;
		float sideBars = 1.5f;
		float yVal = invY + sideBars;
		xVal = invX + sideBars;
		{
			if (currColor[3] < 1) {
				currColor[0] = 1;
				currColor[1] = 0.2f;
				currColor[2] = 0.2f;
				currColor[3] = 1;
			}
			Utils::ApplyRainbow(currColor, 0.00025f);
		}

		if (RGB) {
			DrawUtils::setColor(currColor[1], currColor[2], currColor[3], opacity);
		} else {
		DrawUtils::setColor(255, 255, 255, opacity);
		}

		DrawUtils::drawRectangle(vec2(invX, invY), vec2(invX + 152.f + sideBars, invY + 80.f + sideBars), sideBars / 2);

		for (int j = 9; j < 18; j++) {
			if ((item->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(item->getItemStack(j), vec2(xVal, yVal + 0.f), 1.f, 1.f - .30f, false);
				char stackAmount = item->getItemStack(j)->count;
				std::string stackStr = std::to_string(item->getItemStack(j)->count);
				if (item->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2(xVal + 6.5f, (yVal + 0.f) + 9.5f), &stackStr, MC_Color(InventoryView::rtext, InventoryView::gtext, InventoryView::btext), scale);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
		for (int j = 18; j < 27; j++) {
			if ((item->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(item->getItemStack(j), vec2(xVal + 27.f, yVal + 20.f), 1.f, 1.f - .30f, false);
				std::string stackStr = std::to_string(item->getItemStack(j)->count);
				if (item->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2(xVal + 33.5f, (yVal + 20.f) + 9.5f), &stackStr, MC_Color(InventoryView::rtext, InventoryView::gtext, InventoryView::btext), scale);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
		for (int j = 27; j < 36; j++) {
			if ((item->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(item->getItemStack(j), vec2(xVal + 54.f, yVal + 40.f), 1.f, 1.f - .30f, false);
				std::string stackStr = std::to_string(item->getItemStack(j)->count);
				if (item->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2(xVal + 60.5f, (yVal + 40.f) + 9.5f), &stackStr, MC_Color(InventoryView::rtext, InventoryView::gtext, InventoryView::btext), scale);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
		for (int j = 0; j < 9; j++) {
			if ((item->getItemStack(j)->item != nullptr)) {
				DrawUtils::drawItem(item->getItemStack(j), vec2(xVal + 80.f, yVal + 60.f), 1.f, 1.f - .30f, false);
				std::string stackStr = std::to_string(item->getItemStack(j)->count);
				if (item->getItemStack(j)->count > 1)
					DrawUtils::drawText(vec2(xVal + 86.5f, (yVal + 60.f) + 9.5f), &stackStr, MC_Color(InventoryView::rtext, InventoryView::gtext, InventoryView::btext), scale);
			}
			xVal += 17.f;
		}
		xVal -= 180.f;
	}
}