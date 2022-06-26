#include "ArrayList.h"
#include "../pch.h"

using namespace std;
ArrayList::ArrayList() : IModule(0, Category::VISUAL, "Displays enabled modules") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Outline", 0);
	mode.addEntry("Full", 1);
	mode.addEntry("Split", 2);
	mode.addEntry("Bar", 3);
	mode.addEntry("Right", 4);
	mode.addEntry("None", 5);
	registerEnumSetting("Animation", &animation, 1);
	animation.addEntry("Normal", 0);
	animation.addEntry("Smooth", 1);
	animation.addEntry("None", 2);
	registerBoolSetting("Modes", &modes, modes);
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
	registerFloatSetting("Spacing", &spacing, spacing, 0.f, 1.f);
	shouldHide = true;
}

const char* ArrayList::getModuleName() {
	return ("ArrayList");
}

#pragma region IModuleContainer
struct IModuleContainer {
	shared_ptr<IModule> backingModule;
	bool shouldRender = true;
	string moduleName;
	float textWidth;
	bool enabled;
	vec2_t* pos;

	IModuleContainer(shared_ptr<IModule> mod) {
		const char* name = "Module";
		switch (moduleMgr->getModule<ArrayList>()->modes) {
		case 0: name = mod->getRawModuleName(); moduleName = name; break;
		case 1: name = mod->getModuleName(); moduleName = name; break;
		}

		enabled = mod->isEnabled();
		backingModule = mod;
		pos = mod->getPos();

		if (!enabled && *pos == vec2_t(0.f, 0.f)) shouldRender = false;
		textWidth = DrawUtils::getTextWidth(&moduleName, 1.f) + 5.f;
	}

	bool operator<(const IModuleContainer& other) const {
		if (textWidth == other.textWidth) return moduleName < other.moduleName;
		return textWidth > other.textWidth;
	}
};
#pragma endregion

void ArrayList::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	auto interfaceMod = moduleMgr->getModule<Interface>();
	auto clickGUI = moduleMgr->getModule<ClickGUIMod>();

	vec2_t mousePos = *g_Data.getClientInstance()->getMousePos(); {
		vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		mousePos = mousePos.div(windowSizeReal);
		mousePos = mousePos.mul(windowSize);
	}

	if (g_Data.canUseMoveKeys() && !clickGUI->hasOpenedGUI) {
		vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
		vec2_t racoonaids = g_Data.getClientInstance()->getGuiData()->windowSize;
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		static constexpr bool rightSide = true;
		set<IModuleContainer> moduleList;

		windowSize.x = positionX;
		windowSize.y = positionY;
		float textSize = 1.f;
		float yOffset = positionY;
		float textPadding = spacing * textSize;
		float textHeight = 10.0f * textSize;

		if (yOffset > racoonaids.y / 2) invert = true;
		else invert = false;

		auto lock = moduleMgr->lockModuleList();
		vector<shared_ptr<IModule>>* getModuleList = moduleMgr->getModuleList();
		for (auto moduleInd : *getModuleList) {
			if (moduleInd->shouldHide) continue;
			moduleList.emplace(IModuleContainer(moduleInd));
		}

		float lastModuleLength = 0.f;
		vec4_t underline;
		int index = 0;

		vec4_t selectableSurface;

		for (std::set<IModuleContainer>::iterator mod = moduleList.begin(); mod != moduleList.end(); ++mod) {
			if (!mod->shouldRender) continue;
			index++; int curIndex = -index * interfaceMod->spacing;

			if (invert) selectableSurface.y -= 10.2f;
			else selectableSurface.w += 10.2f;

			float textWidth;
			std::string textStr = mod->moduleName;
			textWidth = DrawUtils::getTextWidth(&textStr, textSize) + 2.f;
			if (mode.getSelectedValue() == 1 || mode.getSelectedValue() == 3 || mode.getSelectedValue() == 4) textWidth = DrawUtils::getTextWidth(&textStr, textSize) + 4.f;
			if (index == 1) selectableSurface = vec4_t(windowSize.x - textWidth, windowSize.y, windowSize.x, windowSize.y + 10);

			#pragma region Animations
			// Animations
			float xOffsetOri = windowSize.x - textWidth - (textPadding * 2);
			float xOffset = windowSize.x - mod->pos->x;

			switch (animation.getSelectedValue()) {
			case 0: case 1: mod->pos->x += ((textPadding * 2) + textWidth - mod->pos->x) * 0.05f; break;
			case 2: mod->pos->x += INFINITY; break;
			}

			if (xOffset < xOffsetOri) xOffset = xOffsetOri;
			if (!mod->enabled) {
				switch (animation.getSelectedValue()) {
				case 0: xOffset += mod->pos->y; mod->pos->y += 4.f; break;
				case 1: xOffset += mod->pos->y; mod->pos->y += ((textPadding * 2) + textWidth + 2.f - mod->pos->y) * 0.05f; break;
				case 2:xOffset += mod->pos->y; mod->pos->y += INFINITY; break;
				}

				if (!invert) yOffset -= mod->pos->y / (textHeight + (textPadding * 2) * 0.1f);
				else yOffset += mod->pos->y / (textHeight + (textPadding * 2) * 0.1f);
			}
			if (!mod->enabled && xOffset > windowSize.x) { mod->pos->x = 0.f; mod->pos->y = 0.f; }
			#pragma endregion

            #pragma region Math
			vec4_t rectPos = vec4_t(xOffset - 3, yOffset, windowSize.x + (textPadding * 2), yOffset + textPadding * 2 + textHeight);
			vec4_t bar = vec4_t(rectPos.z - 1.f, rectPos.y, rectPos.z, rectPos.w);
			if (mode.getSelectedValue() == 4) bar = vec4_t(rectPos.z - 1.f, rectPos.y - 2.f, rectPos.z, rectPos.w);
			if (mode.getSelectedValue() == 4 && invert) bar = vec4_t(rectPos.z - 1.f, rectPos.y, rectPos.z, rectPos.w + 2.f);
			vec4_t topLine = vec4_t(rectPos.x - 1.f, rectPos.y - 1.f, rectPos.z, rectPos.y);
			vec4_t topLine2 = vec4_t(rectPos.x, rectPos.y - 2, rectPos.z, rectPos.y);
			if (invert) topLine2 = vec4_t(rectPos.x, rectPos.y + (textPadding * 2) + textHeight, rectPos.z, rectPos.y+ (textPadding * 2) + textHeight + 2);
			vec4_t topLine3 = vec4_t(rectPos.x, rectPos.y - 3.f, rectPos.z, rectPos.y - 2);
			if (invert) topLine3 = vec4_t(rectPos.x, rectPos.y + (textPadding * 2) + textHeight + 2, rectPos.z, rectPos.y + (textPadding * 2) + textHeight + 3);
			if (invert) topLine = vec4_t(rectPos.x, rectPos.y + (textPadding * 2) + textHeight - 1, rectPos.z + 1.f, rectPos.y + (textPadding * 2) + textHeight);
			vec4_t leftRect = vec4_t(xOffset - 4, yOffset, xOffset - 3, yOffset + textPadding * 2 + textHeight);
			vec2_t textPos = vec2_t(rectPos.x + 4.f, rectPos.y);
			if (mode.getSelectedValue() == 1) textPos = vec2_t(rectPos.x + 4.f, rectPos.y + 1.f);
			if (invert) textPos = vec2_t(rectPos.x + 3.5f, rectPos.y + 2.f);
			underline = vec4_t(windowSize.x - (lastModuleLength + 4.f + (textPadding * 2.f)), leftRect.y, leftRect.x, leftRect.y + 1.f);
			if (invert) underline = vec4_t(windowSize.x - (lastModuleLength + 4.f + (textPadding * 2.f)), leftRect.y + (textPadding * 2) + textHeight - 1, leftRect.x, leftRect.y + (textPadding * 2) + textHeight);

			if (selectableSurface.contains(&mousePos)) focused = true;
			else focused = false;
			#pragma endregion

			// Drawing
			auto interfaceColor = ColorUtil::interfaceColor(curIndex);
			if (opacity > 0) DrawUtils::fillRectangleA(rectPos, MC_Color(0, 0, 0, opacity));
			switch (mode.getSelectedValue()) {
			case 0:
				DrawUtils::fillRectangleA(leftRect, MC_Color(interfaceColor));
				if (mod->enabled)DrawUtils::fillRectangleA(underline, MC_Color(interfaceColor));
				DrawUtils::drawText(textPos, &textStr, MC_Color(interfaceColor), textSize, 1.f, true);
				break;
			case 1:
				DrawUtils::fillRectangleA(leftRect, MC_Color(interfaceColor));
				if (mod->enabled) DrawUtils::fillRectangleA(underline, MC_Color(interfaceColor));
				if (index == 1) DrawUtils::fillRectangleA(topLine, MC_Color(interfaceColor));
				DrawUtils::fillRectangleA(bar, MC_Color(interfaceColor));
				DrawUtils::drawText(textPos, &textStr, MC_Color(interfaceColor), textSize, 1.f, true);
				break;
			case 2:
				DrawUtils::fillRectangleA(leftRect, MC_Color(interfaceColor));
				DrawUtils::drawText(textPos, &textStr, MC_Color(interfaceColor), textSize, 1.f, true);
				break;
			case 3:
				DrawUtils::fillRectangleA(bar, MC_Color(interfaceColor));
				DrawUtils::drawText(textPos, &textStr, MC_Color(interfaceColor), textSize, 1.f, true);
				break;
			case 4:
				if (index == 1) DrawUtils::fillRectangleA(topLine2, MC_Color(0, 0, 0, opacity));
				if (index == 1) DrawUtils::fillRectangleA(topLine3, MC_Color(interfaceColor));
				DrawUtils::fillRectangleA(bar, MC_Color(interfaceColor));
				DrawUtils::drawText(textPos, &textStr, MC_Color(interfaceColor), textSize, 1.f, true);
				break;
			case 5: DrawUtils::drawText(textPos, &textStr, MC_Color(interfaceColor), textSize, 1.f, true); break;
			}

			if (invert) yOffset -= textHeight + (textPadding * 2);
			else yOffset += textHeight + (textPadding * 2);

			lastModuleLength = textWidth;
			underline = vec4_t(leftRect.x, leftRect.w, windowSize.x, leftRect.w + 1.f);
			if (invert) underline = vec4_t(leftRect.z, leftRect.y, windowSize.x, leftRect.y + 1.f);
		}

		index++; int curIndex = -index * interfaceMod->spacing;
		auto interfaceColor = ColorUtil::interfaceColor(curIndex);
		if (mode.getSelectedValue() == 0 || mode.getSelectedValue() == 1) DrawUtils::fillRectangleA(underline, MC_Color(interfaceColor));
		moduleList.clear();
	}
}