#include "HudModuleTwo.h"

#include "../../DrawUtils.h"
#include "../../Scripting/ScriptManager.h"

HudModuleTwo::HudModuleTwo() : IModule(0, Category::VISUAL, "Displays ArrayList") {
	//registerBoolSetting("Background", &this->arraylistBackground, this->arraylistBackground);
	registerBoolSetting("TextShadow", &this->textShadow, this->textShadow);
	registerBoolSetting("Keystrokes", &this->keystrokes, this->keystrokes);
	registerBoolSetting("Watermark", &this->watermark, this->watermark);
	registerBoolSetting("Rainbow", &this->rainbow, this->rainbow);
	//registerBoolSetting("TabGui", &this->tabgui, this->tabgui);
	//registerBoolSetting("Version", &this->versionMode, this->versionMode);
	registerBoolSetting("FPS", &this->fps, this->fps);
	//registerBoolSetting("Keybinds", &this->keybinds, this->keybinds);
	//registerBoolSetting("Rainbow", &this->rainbow, this->rainbow);
	//registerBoolSetting("Outline", &this->arraylistOutline, this->arraylistOutline);
	//registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
	//registerBoolSetting("Shown", &this->arraylist, this->arraylist);
	//registerBoolSetting("ClickToggle", &this->clickToggle, this->clickToggle);
	//registerBoolSetting("Coordinates", &this->coordinates, this->coordinates);
	//registerBoolSetting("Show ArmorHUD", &this->displayArmor, this->displayArmor);
	registerBoolSetting("CPS", &this->cps, this->cps);
	registerFloatSetting("FpsPosX", &this->fpspos2, this->fpspos2, 1.f, 450.f);
	registerFloatSetting("FpsPosY", &this->fpspos, this->fpspos, 1.f, 150.f);

	registerFloatSetting("CpsPosX", &this->cpspos2, this->cpspos2, 1.f, 450.f);
	registerFloatSetting("CpsPosY", &this->cpspos, this->cpspos, 1.f, 150.f);
	//registerBoolSetting("Always show", &this->alwaysShow, this->alwaysShow);
}

HudModuleTwo::~HudModuleTwo() {
}

const char* HudModuleTwo::getModuleName() {
	return ("Hud");
}

void HudModuleTwo::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	float f = 10.f * this->scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = tabgui ? 6 * f : 0.f;
	if (tabgui && scriptMgr.getNumEnabledScripts() > 0)
		startY += f;
	{  // FPS
		if (!(g_Data.getLocalPlayer() == nullptr || !this->fps)) {
			std::string fpsText = "FPS: " + std::to_string(g_Data.getFPS());
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			vec2_t textPos = vec2_t(rectPos.x * fpspos2, rectPos.y * fpspos);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), 0.0f);
			DrawUtils::drawText(textPos, &fpsText, MC_Color(255, 255, 255), scale);

			startY *= f;
		}
	}

	{  // CPS
		if (!(g_Data.getLocalPlayer() == nullptr || !this->cps)) {
			std::string cpsText = "CPS: " + std::to_string(g_Data.getLeftCPS());
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.3f, rectPos.y + 313.f);  //CPS Location
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), 0.f);
			DrawUtils::drawText(textPos, &cpsText, MC_Color(255, 255, 255), scale);

			startY += f;
		}
	}

	{  // Coordinates
		if (!(g_Data.getLocalPlayer() == nullptr || !this->coordinates)) {
			vec3_t* pos = g_Data.getLocalPlayer()->getPos();

			std::string coordsX = "X: " + std::to_string((int)floorf(pos->x));
			std::string coordsY = "Y: " + std::to_string((int)floorf(pos->y));
			std::string coordsZ = "Z: " + std::to_string((int)floorf(pos->z));
			vec4_t rectPos = vec4_t(2.5f, startY + 5.f * scale, len, startY + 35.f * scale);
			vec2_t textPos = vec2_t(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), 0.3f);
			DrawUtils::drawText(textPos, &coordsX, MC_Color(255, 255, 255), scale);
			textPos.y += f;
			DrawUtils::drawText(textPos, &coordsY, MC_Color(255, 255, 255), scale);
			textPos.y += f;
			DrawUtils::drawText(textPos, &coordsZ, MC_Color(255, 255, 255), scale);
		}
	}
	{  // ArmorHUD
		if (!(g_Data.getLocalPlayer() == nullptr || !this->displayArmor || !GameData::canUseMoveKeys())) {
			static float constexpr scale = 1.f;
			static float constexpr opacity = 0.25f;
			static float constexpr spacing = scale + 15.f;
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			float x = windowSize.x / 2.f + 5.f;
			float y = windowSize.y - 57.5f;
			for (int i = 0; i < 4; i++) {
				C_ItemStack* stack = player->getArmor(i);
				if (stack->isValid()) {
					DrawUtils::drawItem(stack, vec2_t(x, y), opacity, scale, stack->isEnchanted());
					x += scale * spacing;
				}
			}
			C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
			C_ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			//x += scale * spacing;
			if (item->isValid())
				DrawUtils::drawItem(item, vec2_t(x, y), opacity, scale, item->isEnchanted());
		}
	}
	{  // Keystrokes
		if (!(g_Data.getLocalPlayer() == nullptr || !this->keystrokes || !GameData::canUseMoveKeys())) {
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			DrawUtils::drawKeystroke(*input->forwardKey, vec2_t(32.f, windowSize.y - 74));
			DrawUtils::drawKeystroke(*input->leftKey, vec2_t(10.f, windowSize.y - 52));
			DrawUtils::drawKeystroke(*input->backKey, vec2_t(32.f, windowSize.y - 52));
			DrawUtils::drawKeystroke(*input->rightKey, vec2_t(54.f, windowSize.y - 52));
			DrawUtils::drawKeystroke(*input->spaceBarKey, vec2_t(10.f, windowSize.y - 30));
		}
	}
	{  // alert
		if (!(g_Data.getLocalPlayer() == nullptr || !this->alert || !GameData::canUseMoveKeys())) {
			C_GuiData* dat = g_Data.getClientInstance()->getGuiData();
			static auto Bhopmod = moduleMgr->getModule<Bhop>();
			static auto Glidemod = moduleMgr->getModule<Glide>();
			static auto Flymod = moduleMgr->getModule<HiveFly>();
			static auto Longjumpmod = moduleMgr->getModule<LongJump>();
			static auto Scaffoldmod = moduleMgr->getModule<Scaffold>();
			static auto Freecammod = moduleMgr->getModule<Freecam>();
			vec2_t windowSize = dat->windowSize;
			if (Flymod->isEnabled() && Bhopmod->isEnabled())
				flyflag = true;
			if (Longjumpmod->isEnabled() && Bhopmod->isEnabled())
				bhopflag = true;
			if (Flymod->isEnabled() && Longjumpmod->isEnabled())
				longjumpflag = true;
			vec4_t duotagteam = (vec4_t(windowSize.x / 1.5f - (windowSize.x / 7),
										windowSize.y / 1.6f - (windowSize.y / 13),
										windowSize.x / 1.8f + (windowSize.x / 9),
										windowSize.y / 2 - windowSize.y / 8 + windowSize.y / 4));
			DrawUtils::fillRectangle(vec4_t(duotagteam),
									 MC_Color(0.05f, 0.05f, 0.05f), 0.35f);
		}
	}
}