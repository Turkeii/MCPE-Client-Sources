#include "ClickGui.h"

#include <Windows.h>

#include "../../Utils/Json.hpp"
#include "../../Utils/Logger.h"

bool isLeftClickDown = false;
bool isRightClickDown = false;
bool shouldToggleLeftClick = false;  // If true, toggle the focused module
bool shouldToggleRightClick = false;
bool resetStartPos = true;
bool initialised = false;
int scrollingDirection = 0;

struct SavedWindowSettings {
	vec2_t pos = { -1, -1 };
	bool isExtended = true;
	const char* name = "";
};

std::map<unsigned int, std::shared_ptr<ClickWindow>> windowMap;
std::map<unsigned int, SavedWindowSettings> savedWindowSettings;

bool isDragging = false;
unsigned int draggedWindow = -1;
vec2_t dragStart = vec2_t();

unsigned int focusedElement = -1;
bool isFocused = false;

static constexpr float textPadding = 1.f;
static constexpr float textSize = 1;
static constexpr float textHeight = textSize * 9.5f;
static constexpr float categoryMargin = 0.5f;
static constexpr float paddingRight = 13.5f;
static constexpr float crossSize = textHeight / 2.f;
static constexpr float crossWidth = 0.3f;
static const MC_Color selectedModuleColor = MC_Color(32, 32, 32);
static const MC_Color selectedSettingColor1 = MC_Color(64, 64, 64);
static const MC_Color selectedSettingColor2 = MC_Color(64, 64, 64);
static const MC_Color moduleColor = MC_Color(0, 0, 0);
static const MC_Color SettingColor1 = MC_Color(64, 64, 64);
static const MC_Color SettingColor2 = MC_Color(64, 64, 64);

static float rcolors[4];  // Rainbow color array RGBA

float currentYOffset = 0;
float currentXOffset = 0;

int timesRendered = 0;
int opacityC = 1;

void ClickGui::getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();

	for (auto& it : *moduleList) {
		if (it->getCategory() == category)
			modList->push_back(it);
	}
}

std::shared_ptr<ClickWindow> ClickGui::getWindow(const char* name) {
	unsigned int id = Utils::getCrcHash(name);

	auto search = windowMap.find(id);
	if (search != windowMap.end()) {  // Window exists already
		return search->second;
	}
	else {  // Create window
	 // TODO: restore settings for position etc
		std::shared_ptr<ClickWindow> newWindow = std::make_shared<ClickWindow>();
		newWindow->name = name;

		auto savedSearch = savedWindowSettings.find(id);
		if (savedSearch != savedWindowSettings.end()) {  // Use values from config
			newWindow->isExtended = savedSearch->second.isExtended;
			if (savedSearch->second.pos.x > 0)
				newWindow->pos = savedSearch->second.pos;
		}

		windowMap.insert(std::make_pair(id, newWindow));
		return newWindow;
	}
}

std::shared_ptr<ClickModule> ClickGui::getClickModule(std::shared_ptr<ClickWindow> window, const char* name) {
	unsigned int id = Utils::getCrcHash(name);

	auto search = window->moduleMap.find(id);
	if (search != window->moduleMap.end()) {  // Window exists already
		return search->second;
	}
	else {  // Create window
	 // TODO: restore settings for position etc
		std::shared_ptr<ClickModule> newModule = std::make_shared<ClickModule>();

		window->moduleMap.insert(std::make_pair(id, newModule));
		return newModule;
	}
}

void ClickGui::renderLabel(const char* text) {
}

void ClickGui::renderTooltip(std::string* text) {
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2_t mousePos = *g_Data.getClientInstance()->getMousePos();
	vec2_t currentTooltipPos = vec2_t(5.f, mousePos.y - 15.f);
	float textWidth = DrawUtils::getTextWidth(text, textSize);

	vec2_t textPos = vec2_t(
		currentTooltipPos.x + textPadding,
		currentTooltipPos.y);
	vec4_t rectPos = vec4_t(
		currentTooltipPos.x - 2.f,
		currentTooltipPos.y - 2.f,
		currentTooltipPos.x + (textPadding * 2) + textWidth + 2.f,
		currentTooltipPos.y + textHeight + 2.f);

	DrawUtils::fillRectangle(rectPos, MC_Color(32, 32, 32), 1.0f);
	DrawUtils::drawRectangle(rectPos, MC_Color(32, 32, 32), 1.f, 0.5f);
	//DrawUtils::drawText(mousePos, text, MC_Color(255, 255, 255), textSize, 1);
	DrawUtils::drawText(vec2_t(textPos), text, MC_Color(255, 255, 255), 1);
}

void ClickGui::renderCategory(Category category, bool Rainbow, float backgroundAlpha) {
	const char* categoryName = ClickGui::catToName(category);
	auto clickGUI = moduleMgr->getModule<ClickGuiMod>();

	const std::shared_ptr<ClickWindow> ourWindow = getWindow(categoryName);

	// Reset Windows to pre-set positions to avoid confusion
	if (resetStartPos && ourWindow->pos.x <= 0) {
		float yot = g_Data.getGuiData()->windowSize.x;
		ourWindow->pos.y = 4;
		switch (category) {
		case Category::COMBAT:
			ourWindow->pos.x = 10.f;
			break;
		case Category::VISUAL:
			ourWindow->pos.x = yot / 7.f;
			break;
		case Category::MOVEMENT:
			ourWindow->pos.x = yot / 7.f * 2.f;
			break;
		case Category::PLAYER:
			ourWindow->pos.x = yot / 7.f * 3.f;
			break;
		case Category::EXPLOIT:
			ourWindow->pos.x = yot / 7.f * 4.1f;
			break;
		case Category::MISC:
			ourWindow->pos.x = yot / 7.f * 5.2f;
			break;
		case Category::CONFIG:
			ourWindow->pos.x = yot / 7.f * 6.2f;
			break;
		case Category::CUSTOM:
			ourWindow->pos.x = yot / 7.f * 6.f;
			break;
		}
	}

	float currColor[4];  // ArrayList colors
	currColor[3] = rcolors[3];

	const float xOffset = ourWindow->pos.x;
	const float yOffset = ourWindow->pos.y;
	vec2_t* windowSize = &ourWindow->size;
	currentXOffset = xOffset;
	currentYOffset = yOffset + 2.f;

	// Get All Modules in our category
	std::vector<std::shared_ptr<IModule>> ModuleList;
	getModuleListByCategory(category, &ModuleList);

	// Get max width of all text

	for (auto& it : ModuleList) {
		std::string label = it->getRawModuleName();
		windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&label, textSize, Fonts::SMOOTH));
	}

	std::vector<std::shared_ptr<IModule>> moduleList;
	//Sorting by length, that is terrible but it works
	{
		std::vector<int> toIgniore;
		int moduleCount = (int)ModuleList.size();

		for (int i = 0; i < moduleCount; i++) {
			float bestWidth = 0.f;
			int bestIndex = 0;

			for (int j = 0; j < ModuleList.size(); j++) {
				bool stopurphat = false;
				for (int bruhwth = 0; bruhwth < toIgniore.size(); bruhwth++)
					if (j == toIgniore[bruhwth]) {
						stopurphat = true;
						break;
					}
				if (stopurphat)
					continue;

				std::string t = ModuleList[j]->getRawModuleName();
				float textWidthRn = DrawUtils::getTextWidth(&t, textSize, Fonts::SMOOTH);
				if (textWidthRn > bestWidth) {
					bestWidth = textWidthRn;
					bestIndex = j;
				}
			}
			moduleList.push_back(ModuleList[bestIndex]);
			toIgniore.push_back(bestIndex);
		}
	}

	const float xEnd = currentXOffset + windowSize->x + paddingRight;

	vec2_t mousePos = *g_Data.getClientInstance()->getMousePos();

	// Convert mousePos to visual Pos
	{
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;

		mousePos = mousePos.div(windowSizeReal);
		mousePos = mousePos.mul(windowSize);
	}

	float categoryHeaderYOffset = currentYOffset;

	if (ourWindow->isInAnimation) {
		if (ourWindow->isExtended) {
			ourWindow->animation *= 0.85f;
			if (ourWindow->animation < 0.001f) {
				ourWindow->yOffset = 0;  // reset scroll
				ourWindow->isInAnimation = false;
			}

		}
		else {
			ourWindow->animation = 1 - ((1 - ourWindow->animation) * 0.85f);
			if (1 - ourWindow->animation < 0.001f)
				ourWindow->isInAnimation = false;
		}
	}

	currentYOffset += textHeight + (textPadding * 2);
	// Loop through Modules to display em
	if (ourWindow->isExtended || ourWindow->isInAnimation) {
		if (ourWindow->isInAnimation) {
			currentYOffset -= ourWindow->animation * moduleList.size() * (textHeight + (textPadding * 2));
		}

		bool overflowing = false;
		const float cutoffHeight = roundf(g_Data.getGuiData()->heightGame * 3.f) + 0.5f /*fix flickering related to rounding errors*/;
		int moduleIndex = 0;
		for (auto& mod : moduleList) {
			moduleIndex++;
			if (moduleIndex < ourWindow->yOffset)
				continue;
			float probableYOffset = (moduleIndex - ourWindow->yOffset) * (textHeight + (textPadding * 2));

			Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[2], rcolors[1], currColor[0], currColor[1], currColor[2]);
			currColor[0] += 1.f / moduleList.size() * moduleIndex;
			Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[1], currColor[2]);

			if (ourWindow->isInAnimation) {  // Estimate, we don't know about module settings yet
				if (probableYOffset > cutoffHeight) {
					overflowing = true;
					break;
				}
			}
			else if ((currentYOffset - ourWindow->pos.y) > cutoffHeight || currentYOffset > g_Data.getGuiData()->heightGame - 5) {
				overflowing = true;
				break;
			}

			std::string textStr = mod->getRawModuleName();

			vec2_t textPos = vec2_t(
				currentXOffset + textPadding + 1.18f,
				currentYOffset + textPadding + 1.20f);

			vec4_t rectPos = vec4_t(
				currentXOffset,
				currentYOffset,
				xEnd,
				currentYOffset + textHeight + (textPadding * 2));

			bool allowRender = currentYOffset >= categoryHeaderYOffset;

			// Background
			if (allowRender) {
				if (!ourWindow->isInAnimation && !isDragging && rectPos.contains(&mousePos)) {  // Is the Mouse hovering above us?
					DrawUtils::fillRectangle(rectPos, selectedModuleColor, backgroundAlpha);
					std::string tooltip = mod->getTooltip();
					static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
					if (clickGuiMod->showTooltips && !tooltip.empty())
						renderTooltip(&tooltip);
					if (shouldToggleLeftClick && !ourWindow->isInAnimation) {  // Are we being clicked?
						mod->toggle();
						shouldToggleLeftClick = false;
					}
				}
				else {
					DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);
				}
			}

			// Text
			if (allowRender)
				if (Rainbow)
					DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(currColor) : MC_Color(MC_Color(64, 64, 64)), textSize);  // MC_Color(currColor[0] / 4.f, currColor[1] / 4.f, currColor[2] / 4.f), textSize);
				else
					DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(ClickGuiMod::textR, ClickGuiMod::textG, ClickGuiMod::textB) : MC_Color(ClickGuiMod::dtextR, ClickGuiMod::dtextG, ClickGuiMod::dtextB), textSize);
			if (clickGUI->theme.getSelectedValue() == 1) {  // fadeaway
				DrawUtils::fillRectangle(rectPos, mod->isEnabled() ? MC_Color(215, 84, 229) : MC_Color(0, 0, 0), textSize);
			}
			//DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(255, 255, 255) : MC_Color(100, 100, 100), textSize);

			// Settings
			{
				std::vector<SettingEntry*>* settings = mod->getSettings();
				if (settings->size() > 2 && allowRender) {
					std::shared_ptr<ClickModule> clickMod = getClickModule(ourWindow, mod->getRawModuleName());
					if (rectPos.contains(&mousePos) && shouldToggleRightClick && !ourWindow->isInAnimation) {
						shouldToggleRightClick = false;
						clickMod->isExtended = !clickMod->isExtended;
					}
					if (Rainbow) {
						GuiUtils::drawCrossLine(vec2_t(
							currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
							currentYOffset + textPadding + (textHeight / 2)),
							MC_Color(currColor), crossWidth, crossSize, !clickMod->isExtended);
					}
					if (!Rainbow) {
						GuiUtils::drawCrossLine(vec2_t(
							currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
							currentYOffset + textPadding + (textHeight / 2)),
							MC_Color(255, 255, 255), crossWidth, crossSize, !clickMod->isExtended);
					}

					currentYOffset += textHeight + (textPadding * 2);

					if (clickMod->isExtended) {
						float startYOffset = currentYOffset;
						for (auto setting : *settings) {
							if (strcmp(setting->name, "enabled") == 0 || strcmp(setting->name, "keybind") == 0)
								continue;

							vec2_t textPos = vec2_t(
								currentXOffset + textPadding + 5,
								currentYOffset + textPadding);

							// Incomplete, because we dont know the endY yet
							vec4_t rectPos = vec4_t(
								currentXOffset,
								currentYOffset,
								xEnd,
								0);

							if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
								overflowing = true;
								break;
							}

							switch (setting->valueType) {
							case ValueType::BOOL_T: {
								rectPos.w = currentYOffset + textHeight + (textPadding * 2);
								DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);
								vec4_t selectableSurface = vec4_t(
									textPos.x + textPadding,
									textPos.y + textPadding,
									xEnd - textPadding,
									textPos.y + textHeight - textPadding);

								bool isFocused = selectableSurface.contains(&mousePos);
								// Logic
								{
									if (isFocused && shouldToggleLeftClick && !ourWindow->isInAnimation) {
										shouldToggleLeftClick = false;
										setting->value->_bool = !setting->value->_bool;
									}
								}
								// Checkbox
								{
									vec4_t boxPos = vec4_t(
										textPos.x + textPadding,
										textPos.y + textPadding,
										textPos.x + textHeight - textPadding,
										textPos.y + textHeight - textPadding);

									DrawUtils::drawRectangle(boxPos, MC_Color(255, 255, 255), isFocused ? 1 : 0.8f, 0.5f);

									if (setting->value->_bool) {
										DrawUtils::setColor(28, 107, 201, 1);
										boxPos.x += textPadding;
										boxPos.y += textPadding;
										boxPos.z -= textPadding;
										boxPos.w -= textPadding;
										DrawUtils::drawLine(vec2_t(boxPos.x, boxPos.y), vec2_t(boxPos.z, boxPos.w), 0.5f);
										DrawUtils::drawLine(vec2_t(boxPos.z, boxPos.y), vec2_t(boxPos.x, boxPos.w), 0.5f);
										//DrawUtils::fillRectangle(vec2_t(boxPos.x, boxPos.y), vec2_t(boxPos.z, boxPos.w));
									}
								}
								textPos.x += textHeight + (textPadding * 2);
								// Text
								{
									// Convert first letter to uppercase for more friendlieness
									char name[0x21];
									sprintf_s(name, 0x21, "%s", setting->name);
									if (name[0] != 0)
										name[0] = toupper(name[0]);

									std::string elTexto = name;
									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 10 /* because we add 10 to text padding + checkbox*/);
									DrawUtils::drawText(textPos, &elTexto, isFocused ? MC_Color(1.0f, 1.0f, 1.0f) : MC_Color(0.8f, 0.8f, 0.8f), textSize);
									currentYOffset += textHeight + (textPadding * 2);
								}
								break;
							}
							case ValueType::ENUM_T: {  // Click setting
								// Text and background
								float settingStart = currentYOffset;
								{
									char name[0x22];
									sprintf_s(name, "%s:", setting->name);
									// Convert first letter to uppercase for more friendlieness
									if (name[0] != 0)
										name[0] = toupper(name[0]);

									std::string elTexto = name;
									rectPos.w = currentYOffset + textHeight + (textPadding * 2);
									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 /* because we add 5 to text padding*/ + crossSize);
									DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);
									DrawUtils::drawText(textPos, &elTexto, MC_Color(0.8f, 0.8f, 0.8f), textSize);
									currentYOffset += textHeight + (textPadding * 2);
								}
								int e = 0;

								if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
									overflowing = true;
									break;
								}

								bool isEven = e % 2 == 0;
								rectPos.y = currentYOffset;
								rectPos.w = currentYOffset + textHeight + (textPadding * 2);
								EnumEntry& i = ((SettingEnum*)setting->extraData)->GetSelectedEntry();

								char name[0x21];
								sprintf_s(name, 0x21, "   %s", i.GetName().c_str());
								// Convert first letter to uppercase for more friendlieness
								if (name[0] != 0) name[0] = toupper(name[0]);
								std::string elTexto = name;

								windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5.f);  //because we add 5 to text padding
								textPos.y = currentYOffset + textPadding - 1;
								vec4_t selectableSurface = vec4_t(textPos.x, rectPos.y, xEnd, rectPos.w);
								MC_Color col;

								if (setting->value->_int == e || (selectableSurface.contains(&mousePos) && !ourWindow->isInAnimation)) {
									if (isEven)
										col = selectedSettingColor1;
									else
										col = selectedSettingColor2;
								}
								else {
									if (isEven)
										col = SettingColor1;
									else
										col = SettingColor2;
								}
								DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);
								//DrawUtils::fillRectangle(selectableSurface, col, backgroundAlpha);
								DrawUtils::drawText(textPos, &elTexto, MC_Color(1.f, 1.f, 1.f));
								// logic
								selectableSurface.y = settingStart;
								if (!ourWindow->isInAnimation && selectableSurface.contains(&mousePos)) {
									if (shouldToggleLeftClick) {
										shouldToggleLeftClick = false;
										((SettingEnum*)setting->extraData)->SelectNextValue(false);
									}
									else if (shouldToggleRightClick) {
										shouldToggleRightClick = false;
										((SettingEnum*)setting->extraData)->SelectNextValue(true);
									}
								}
								currentYOffset += textHeight + (textPadding * 2);

								break;
							}

							case ValueType::FLOAT_T: {
								// Text and background
								{
									// Convert first letter to uppercase for more friendlieness
									char name[0x22];
									sprintf_s(name, "%s:", setting->name);
									if (name[0] != 0)
										name[0] = toupper(name[0]);

									std::string elTexto = name;
									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 /* because we add 5 to text padding*/);
									DrawUtils::drawText(textPos, &elTexto, MC_Color(1.0f, 1.0f, 1.0f), textSize);
									currentYOffset += textPadding + textHeight;
									rectPos.w = currentYOffset;
									DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);
								}

								if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
									overflowing = true;
									break;
								}
								// Slider
								{
									vec4_t rect = vec4_t(
										currentXOffset + textPadding + 5,
										currentYOffset + textPadding,
										xEnd - textPadding,
										currentYOffset - textPadding + textHeight + 3.f);

									// Visuals & Logic
									{
										rectPos.y = currentYOffset;
										rectPos.w += textHeight + (textPadding * 2) + 3.f;
										// Background
										const bool areWeFocused = rect.contains(&mousePos);

										DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);                   // Background
										DrawUtils::drawRectangle(rect, MC_Color(1.0f, 1.0f, 1.0f), 0.f, backgroundAlpha);  // Slider background

										const float minValue = setting->minValue->_float;
										const float maxValue = setting->maxValue->_float - minValue;
										float value = (float)fmax(0, setting->value->_float - minValue);  // Value is now always > 0 && < maxValue
										if (value > maxValue)
											value = maxValue;
										value /= maxValue;  // Value is now in range 0 - 1
										const float endXlol = (xEnd - textPadding) - (currentXOffset + textPadding + 5);
										value *= endXlol;  // Value is now pixel diff between start of bar and end of progress

										// Draw Int
										{
											vec2_t mid = vec2_t(
												rect.x + ((rect.z - rect.x) / 2),
												rect.y - .2f);
											char str[10];
											sprintf_s(str, 10, "%.2f", setting->value->_float);
											std::string text = str;
											mid.x -= DrawUtils::getTextWidth(&text, textSize) / 2;
											mid.y += 2.f;
											DrawUtils::drawText(mid, &text, MC_Color(255, 255, 255), textSize);
										}

										// Draw Progress
										{
											rect.z = rect.x + value;
											DrawUtils::fillRectangle(rect, MC_Color(64, 64, 64), (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
										}

										// Drag Logic
										{
											if (setting->isDragging) {
												if (isLeftClickDown && !isRightClickDown)
													value = mousePos.x - rect.x;
												else
													setting->isDragging = false;
											}
											else if (areWeFocused && shouldToggleLeftClick && !ourWindow->isInAnimation) {
												shouldToggleLeftClick = false;
												setting->isDragging = true;
											}
										}

										// Save Value
										{
											value /= endXlol;  // Now in range 0 - 1
											value *= maxValue;
											value += minValue;

											setting->value->_float = value;
											setting->makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
										}
									}
									currentYOffset += textHeight + (textPadding * 2) + 3.f;
								}
							} break;
							case ValueType::INT_T: {
								// Text and background
								{
									// Convert first letter to uppercase for more friendlieness
									char name[0x22];
									sprintf_s(name, "%s:", setting->name);
									if (name[0] != 0)
										name[0] = toupper(name[0]);

									std::string elTexto = name;
									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 /* because we add 5 to text padding*/);
									DrawUtils::drawText(textPos, &elTexto, MC_Color(1.0f, 1.0f, 1.0f), textSize);
									currentYOffset += textPadding + textHeight;
									rectPos.w = currentYOffset;
									DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);
								}
								if ((currentYOffset - ourWindow->pos.y) > (g_Data.getGuiData()->heightGame * 0.75)) {
									overflowing = true;
									break;
								}
								// Slider
								{
									vec4_t rect = vec4_t(
										currentXOffset + textPadding + 5,
										currentYOffset + textPadding,
										xEnd - textPadding,
										currentYOffset - textPadding + textHeight + 3.f);

									// Visuals & Logic
									{
										rectPos.y = currentYOffset;
										rectPos.w += textHeight + (textPadding * 2) + 3.f;
										// Background
										const bool areWeFocused = rect.contains(&mousePos);

										DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);                   // Background
										DrawUtils::drawRectangle(rect, MC_Color(1.0f, 1.0f, 1.0f), 0.f, backgroundAlpha);  // Slider background

										const float minValue = (float)setting->minValue->_int;
										const float maxValue = (float)setting->maxValue->_int - minValue;
										float value = (float)fmax(0, setting->value->_int - minValue);  // Value is now always > 0 && < maxValue
										if (value > maxValue)
											value = maxValue;
										value /= maxValue;  // Value is now in range 0 - 1
										const float endXlol = (xEnd - textPadding) - (currentXOffset + textPadding + 5);
										value *= endXlol;  // Value is now pixel diff between start of bar and end of progress

										// Draw Int
										{
											vec2_t mid = vec2_t(
												rect.x + ((rect.z - rect.x) / 2),
												rect.y - 0.2f  // Hardcoded ghetto
											);
											char str[10];
											sprintf_s(str, 10, "%i", setting->value->_int);
											std::string text = str;
											mid.x -= DrawUtils::getTextWidth(&text, textSize) / 2;
											mid.y += 2.f;
											DrawUtils::drawText(mid, &text, MC_Color(255, 255, 255), textSize);
										}

										// Draw Progress
										{
											rect.z = rect.x + value;
											DrawUtils::fillRectangle(rect, MC_Color(64, 64, 64), (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
										}

										// Drag Logic
										{
											if (setting->isDragging) {
												if (isLeftClickDown && !isRightClickDown)
													value = mousePos.x - rect.x;
												else
													setting->isDragging = false;
											}
											else if (areWeFocused && shouldToggleLeftClick && !ourWindow->isInAnimation) {
												shouldToggleLeftClick = false;
												setting->isDragging = true;
											}
										}

										// Save Value
										{
											value /= endXlol;  // Now in range 0 - 1
											value *= maxValue;
											value += minValue;

											setting->value->_int = (int)roundf(value);
											setting->makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
										}
									}
									currentYOffset += textHeight + (textPadding * 2) + 3.f;
								}
							} break;
							default: {
								char alc[100];
								sprintf_s(alc, 100, "Not implemented (%s)", setting->name);
								std::string elTexto = alc;
								// Adjust window size if our text is too  t h i c c
								windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 /* because we add 5 to text padding*/);

								DrawUtils::drawText(textPos, &elTexto, MC_Color(1.0f, 1.0f, 1.0f), textSize);
								currentYOffset += textHeight + (textPadding * 2);
							} break;
							}
						}
						float endYOffset = currentYOffset;
						if (endYOffset - startYOffset > textHeight + 1 || overflowing) {
							startYOffset += textPadding;
							endYOffset -= textPadding;
							DrawUtils::setColor(1, 1, 1, 1);
							DrawUtils::drawLine(vec2_t(currentXOffset + 2, startYOffset), vec2_t(currentXOffset + 2, endYOffset), 0.5f);
						}
					}
				}
				else
					currentYOffset += textHeight + (textPadding * 2);
			}
		}

		vec4_t winRectPos = vec4_t(
			xOffset,
			yOffset,
			xEnd,
			currentYOffset);

		if (winRectPos.contains(&mousePos)) {
			if (scrollingDirection > 0 && overflowing) {
				ourWindow->yOffset += scrollingDirection;
			}
			else if (scrollingDirection < 0) {
				ourWindow->yOffset += scrollingDirection;
			}
			scrollingDirection = 0;
			if (ourWindow->yOffset < 0) {
				ourWindow->yOffset = 0;
			}
		}
	}
	DrawUtils::flush();
	// Draw Category Header
	{
		vec2_t textPos = vec2_t(
			currentXOffset + textPadding,
			categoryHeaderYOffset + textPadding);
		vec4_t rectPos = vec4_t(
			currentXOffset - categoryMargin,
			categoryHeaderYOffset - categoryMargin,
			currentXOffset + windowSize->x + paddingRight + categoryMargin,
			categoryHeaderYOffset + textHeight + (textPadding * 2));
		vec4_t rect = vec4_t(
			currentXOffset + textPadding + 5,
			currentYOffset + textPadding,
			xEnd - textPadding,
			currentYOffset - textPadding + textHeight + 3.f);

		vec2_t mid = vec2_t(
			rect.x + ((rect.z - rect.x) / 2),
			categoryHeaderYOffset + 1);

		// Extend Logic
		{
			if (rectPos.contains(&mousePos) && shouldToggleRightClick && !isDragging) {
				shouldToggleRightClick = false;
				ourWindow->isExtended = !ourWindow->isExtended;
				if (ourWindow->isExtended && ourWindow->animation == 0)
					ourWindow->animation = 0.2f;
				else if (!ourWindow->isExtended && ourWindow->animation == 1)
					ourWindow->animation = 0;
				ourWindow->isInAnimation = true;

				for (auto& mod : moduleList) {
					std::shared_ptr<ClickModule> clickMod = getClickModule(ourWindow, mod->getRawModuleName());
					clickMod->isExtended = false;
				}
			}
		}

		// Dragging Logic
		{
			if (isDragging && Utils::getCrcHash(categoryName) == draggedWindow) {  // WE are being dragged
				if (isLeftClickDown) {                                             // Still dragging
					vec2_t diff = vec2_t(mousePos).sub(dragStart);
					ourWindow->pos = ourWindow->pos.add(diff);
					dragStart = mousePos;
				}
				else {  // Stopped dragging
					isDragging = false;
				}
			}
			else if (rectPos.contains(&mousePos) && shouldToggleLeftClick) {
				isDragging = true;
				draggedWindow = Utils::getCrcHash(categoryName);
				shouldToggleLeftClick = false;
				dragStart = mousePos;
			}
		}

		// Draw component
		{
			// Draw hudeditor button
			vec2_t textPos2 = vec2_t(
				currentXOffset + textPadding,
				categoryHeaderYOffset + textPadding);
			vec2_t windowSize2 = g_Data.getClientInstance()->getGuiData()->windowSize;

#ifdef _DEBUG
			auto hudEditor = moduleMgr->getModule<HudEditorMod>();
			std::string length = "HUD Editor";

			float startY = windowSize2.y - 24;
			float l = DrawUtils::getTextWidth(&length, 1.4) + 3;

			vec4_t rectPos22 = vec4_t(2.5, startY + 4, l, startY + 20);
			vec2_t textPos22 = vec2_t(rectPos22.x + 9, rectPos22.y + 4);

			DrawUtils::drawLine(vec2_t(rectPos22.x, rectPos22.y + 17), vec2_t(rectPos22.x + l - 2.5, rectPos22.y + 17), 1);
			DrawUtils::drawText(vec2_t(textPos22), &length, MC_Color(255, 255, 255), 1, 1, true);

			if (rectPos22.contains(&mousePos)) {
				DrawUtils::fillRectangle(rectPos22, MC_Color(64, 64, 64), 0.1);
			}
			else {
				DrawUtils::fillRectangle(rectPos22, MC_Color(0, 0, 0), 0.1);
			}

			if (shouldToggleLeftClick && rectPos22.contains(&mousePos)) {
				DrawUtils::fillRectangle(rectPos22, MC_Color(64, 64, 64), 0.1);
				clickGUI->setEnabled(false);
				hudEditor->setEnabled(true);
			}
#endif

			std::string textStr = categoryName;
			DrawUtils::drawText(textPos2, &textStr, MC_Color(255, 255, 255), textSize);
			//DrawUtils::drawText(vec2_t(x, y), &text, MC_Color(255, 255, 255), 1.f);
			Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[2], rcolors[1], currColor[0], currColor[1], currColor[2]);
			currColor[0] += 1.f / moduleList.size();
			Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[1], currColor[2]);

			if (Rainbow)
				DrawUtils::drawText(textPos2, &textStr, MC_Color(currColor), textSize);
			DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);

			DrawUtils::fillRectangle(vec4_t(rectPos.x, rectPos.w - 1, rectPos.z, rectPos.w), MC_Color(255, 255, 255), 1 - ourWindow->animation);
			if (Rainbow)
				DrawUtils::fillRectangle(vec4_t(rectPos.x, rectPos.w - 1, rectPos.z, rectPos.w), MC_Color(currColor), 1 - ourWindow->animation);
			// Draw Dash
			GuiUtils::drawCrossLine(vec2_t(
				currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
				categoryHeaderYOffset + textPadding + (textHeight / 2)),
				MC_Color(255, 255, 255), crossWidth, crossSize, !ourWindow->isExtended);
			if (Rainbow) {
				GuiUtils::drawCrossLine(vec2_t(
					currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
					categoryHeaderYOffset + textPadding + (textHeight / 2)),
					MC_Color(currColor), crossWidth, crossSize, !ourWindow->isExtended);
			}
		}
	}

	// anti idiot
	{
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		if (ourWindow->pos.x + ourWindow->size.x > windowSize.x) {
			ourWindow->pos.x = windowSize.x - ourWindow->size.x;
		}

		if (ourWindow->pos.y + ourWindow->size.y > windowSize.y) {
			ourWindow->pos.y = windowSize.y - ourWindow->size.y;
		}

		ourWindow->pos.x = (float)fmax(0, ourWindow->pos.x);
		ourWindow->pos.y = (float)fmax(0, ourWindow->pos.y);
	}

	moduleList.clear();
	DrawUtils::flush();
}

void ClickGui::render() {
	static auto clickGUIMod = moduleMgr->getModule<ClickGuiMod>();
	if (!moduleMgr->isInitialized())
		return;

	if (timesRendered < 10)
		timesRendered++;

	// Fill Background
	{
		DrawUtils::fillRectangle(vec4_t(
			0,
			0,
			g_Data.getClientInstance()->getGuiData()->widthGame,
			g_Data.getClientInstance()->getGuiData()->heightGame),
			MC_Color(0, 0, 0), 0.3);
	}

	// Render all categorys
	Utils::ApplyRainbow(rcolors, 0.001f);  // Increase Hue of rainbow color array

	static ClickGuiMod* guimod = moduleMgr->getModule<ClickGuiMod>();

	renderCategory(Category::COMBAT, guimod->rainbowColor, guimod->enabled ? guimod->opacity : 1.f);
	renderCategory(Category::VISUAL, guimod->rainbowColor, guimod->enabled ? guimod->opacity : 1.f);
	renderCategory(Category::MOVEMENT, guimod->rainbowColor, guimod->enabled ? guimod->opacity : 1.f);
	renderCategory(Category::PLAYER, guimod->rainbowColor, guimod->enabled ? guimod->opacity : 1.f);
	renderCategory(Category::EXPLOIT, guimod->rainbowColor, guimod->enabled ? guimod->opacity : 1.f);
	renderCategory(Category::MISC, guimod->rainbowColor, guimod->enabled ? guimod->opacity : 1.f);
#ifdef _DEBUG
	renderCategory(Category::CONFIG, guimod->rainbowColor, guimod->enabled ? guimod->opacity : 1.f);
#endif
	bool UwantCustomCategory4SomeReason = false;
	if (UwantCustomCategory4SomeReason)
		renderCategory(Category::CUSTOM, guimod->rainbowColor, guimod->opacity ? guimod->opacity : 1.f);

	shouldToggleLeftClick = false;
	shouldToggleRightClick = false;
	resetStartPos = false;

	DrawUtils::flush();
}

void ClickGui::init() { initialised = true; }

void ClickGui::onMouseClickUpdate(int key, bool isDown) {
	static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
	if (clickGuiMod->isEnabled() && g_Data.isInGame()) {
		switch (key) {
		case 1:  // Left Click
			isLeftClickDown = isDown;
			if (isDown)
				shouldToggleLeftClick = true;
			break;
		case 2:  // Right Click
			isRightClickDown = isDown;
			if (isDown)
				shouldToggleRightClick = true;
			break;
		}
	}
}

void ClickGui::onWheelScroll(bool direction) {
	if (!direction)
		scrollingDirection++;
	else
		scrollingDirection--;
}

void ClickGui::onKeyUpdate(int key, bool isDown) {
	if (!initialised)
		return;
	static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();

	if (!isDown)
		return;

	if (!clickGuiMod->isEnabled()) {
		timesRendered = 0;
		return;
	}

	if (timesRendered < 10)
		return;
	timesRendered = 0;

	switch (key) {
	case VK_ESCAPE:
		clickGuiMod->setEnabled(false);
		return;
	default:
		if (key == clickGuiMod->getKeybind())
			clickGuiMod->setEnabled(false);
	}
}

using json = nlohmann::json;
void ClickGui::onLoadConfig(void* confVoid) {
	savedWindowSettings.clear();
	windowMap.clear();
	json* conf = reinterpret_cast<json*>(confVoid);
	if (conf->contains("ClickGuiMenu")) {
		auto obj = conf->at("ClickGuiMenu");
		if (obj.is_null())
			return;
		for (int i = 0; i <= (int)Category::CUSTOM /*last category*/; i++) {
			auto catName = ClickGui::catToName((Category)i);
			if (obj.contains(catName)) {
				auto value = obj.at(catName);
				if (value.is_null())
					continue;
				try {
					SavedWindowSettings windowSettings = {};
					windowSettings.name = catName;
					if (value.contains("pos")) {
						auto posVal = value.at("pos");
						if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
							try {
								windowSettings.pos = { posVal["x"].get<float>(), posVal["y"].get<float>() };
							}
							catch (std::exception e) {
							}
						}
					}
					if (value.contains("isExtended")) {
						auto isExtVal = value.at("isExtended");
						if (!isExtVal.is_null() && isExtVal.is_boolean()) {
							try {
								windowSettings.isExtended = isExtVal.get<bool>();
							}
							catch (std::exception e) {
							}
						}
					}
					savedWindowSettings[Utils::getCrcHash(catName)] = windowSettings;
				}
				catch (std::exception e) {
					logF("Config Load Error (ClickGuiMenu): %s", e.what());
				}
			}
		}
	}
}
void ClickGui::onSaveConfig(void* confVoid) {
	json* conf = reinterpret_cast<json*>(confVoid);
	// First update our map
	for (const auto& wind : windowMap) {
		savedWindowSettings[wind.first] = { wind.second->pos, wind.second->isExtended, wind.second->name };
	}

	// Save to json
	if (conf->contains("ClickGuiMenu"))
		conf->erase("ClickGuiMenu");

	json obj = {};

	for (const auto& wind : savedWindowSettings) {
		json subObj = {};
		subObj["pos"]["x"] = wind.second.pos.x;
		subObj["pos"]["y"] = wind.second.pos.y;
		subObj["isExtended"] = wind.second.isExtended;
		obj[wind.second.name] = subObj;
	}

	conf->emplace("ClickGuiMenu", obj);
}