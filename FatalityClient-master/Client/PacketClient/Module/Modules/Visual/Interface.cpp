#include "Interface.h"
#include "../pch.h"

Interface::Interface() : IModule(0, Category::VISUAL, "Displays the HUD") {
	registerEnumSetting("Color", &color, 0);
	color.addEntry("Rainbow", 0);
	color.addEntry("Astolfo", 1);
	color.addEntry("Wave", 2);
	color.addEntry("RGBWave", 3);
	registerBoolSetting("ArmorHUD", &armorHUD, armorHUD);
	registerBoolSetting("Release", &release, release);
	registerBoolSetting("Info", &info, info);
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
	registerFloatSetting("Saturation", &saturation, saturation, 0.f, 1.f);
	registerIntSetting("Seperation", &spacing, spacing, 5, 500);

	registerFloatSetting("Red", &r, r, 0.f, 255.f);
	registerFloatSetting("Green", &g, g, 0.f, 255.f);
	registerFloatSetting("Blue", &b, b, 0.f, 255.f);
	registerFloatSetting("Red2", &r2, r2, 0.f, 255.f);
	registerFloatSetting("Green2", &g2, g2, 0.f, 255.f);
	registerFloatSetting("Blue2", &b2, b2, 0.f, 255.f);
	shouldHide = true;
}

const char* Interface::getModuleName() {
	return ("Interface");
}

void Interface::onTick(C_GameMode* gm) {
	shouldHide = true;
}

void Interface::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}

void Interface::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto clickGUI = moduleMgr->getModule<ClickGUIMod>();

	static int index = 0;
	int curIndex = -index * spacing;
	auto hudColor = ColorUtil::interfaceColor(curIndex);

	if (!clickGUI->hasOpenedGUI) {
		if (armorHUD) {
			vec4_t testRect = vec4_t(armorX, armorY, 50 + armorX, armorY + 20);
			vec2_t armorPos = vec2_t(testRect.x, testRect.y);
			static float constexpr opacity = 10;
			float scale = 3 * 0.26f;
			float spacing = scale + 15.f + 2;
			for (int t = 0; t < 4; t++) {
				C_ItemStack* stack = player->getArmor(t);
				if (stack->isValid()) {
					DrawUtils::drawItem(stack, armorPos, 1, 1, false);
					armorPos.x += scale * spacing;
				}
			}
			C_PlayerInventoryProxy* supplies = player->getSupplies();
			C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			if (item->isValid()) DrawUtils::drawItem(item, armorPos, opacity, 1, item->isEnchanted());
		}

		if (release) {
#ifdef _DEBUG
			releaseStr = versionStr + "";
#else
			releaseStr = versionStr + "";
#endif

			float len = DrawUtils::getTextWidth(&releaseStr, 1) + 6.5;
			vec4_t fpsRectPos = vec4_t(releaseX, releaseY + 7, len + releaseX, releaseY + 20);
			DrawUtils::fillRoundRectangle(fpsRectPos, MC_Color(0, 0, 0, opacity), false);
			DrawUtils::drawGradientText(vec2_t(fpsRectPos.x + 3, fpsRectPos.y + 3.5), &releaseStr, 1, 1, true);
		}

		if (info) {
			auto hudColor = ColorUtil::interfaceColor(curIndex);

			// Speed (BPS)
			auto player = g_Data.getLocalPlayer();
			std::string speedText = "b/s: " + std::to_string((int)player->getBlocksPerSecond()) + std::string(".") + std::to_string((int)(player->getBlocksPerSecond() * 10) - ((int)player->getBlocksPerSecond() * 10));
			float lSpeed = DrawUtils::getTextWidth(&speedText, 1) + 6.5;
			vec4_t speedRectPos = vec4_t(bpsX, bpsY + 6, lSpeed + bpsX, bpsY + 20);
			vec2_t speedPos = vec2_t(speedRectPos.x + 3, speedRectPos.y + 3.5);
			DrawUtils::drawGradientText(speedPos, &speedText, 1, 1, true);
			DrawUtils::fillRoundRectangle(speedRectPos, MC_Color(0, 0, 0, opacity), false);

			// Position
			vec3_t* currPos = g_Data.getLocalPlayer()->getPos();
			std::string position = std::string(GRAY) + "XYZ: " + (RESET)+std::to_string((int)floorf(currPos->x)) + " " + std::to_string((int)floorf(currPos->y)) + " " + std::to_string((int)floorf(currPos->z));
			float lPos = DrawUtils::getTextWidth(&position, 1) + 6.5;
			vec4_t rectPos = vec4_t(posX, posY + 6, lPos + posX, posY + 20);
			vec2_t textPos = vec2_t(rectPos.x + 3, rectPos.y + 3);
			DrawUtils::drawGradientText(textPos, &position, 1, 1, true);
			DrawUtils::fillRoundRectangle(vec4_t(posX, posY + 6, lPos + posX, posY + 20), MC_Color(0, 0, 0, opacity), false);
		}
	}
}

void Interface::onDisable() {
	setEnabled(true);
}