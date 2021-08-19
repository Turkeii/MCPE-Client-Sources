#include "ClickGui.h"

#include <Windows.h>

#include "../../Utils/Json.hpp"
#include "../../Utils/Logger.h"
#include "../Module/Modules/ColorCustomizer.h"
#include "../Module/Modules/HudModule.h"
#define min(a, b) (((a) < (b)) ? (a) : (b))

#define TEXTCOLOR (TextCustomizer::chroma ? DrawUtils::rcolors : MC_Color(TextCustomizer::rFloat, TextCustomizer::gFloat, TextCustomizer::bFloat))
#define BLACKORWHITE(bright) (((ColorCustomizer::rFloat + ColorCustomizer::gFloat * 1.5f + ColorCustomizer::bFloat) / 3 > 128) ? MC_Color(0, 0, 0) : MC_Color(bright, bright, bright))

#define FILLCOLOR (MC_Color(ColorCustomizer::rFloat, ColorCustomizer::gFloat, ColorCustomizer::bFloat))
#define FILLCOLORDARK (MC_Color(ColorCustomizer::rFloat - 50, ColorCustomizer::gFloat - 50, ColorCustomizer::bFloat - 50))
#define FILLCOLORLIGHT (MC_Color(ColorCustomizer::rFloat + 50, ColorCustomizer::gFloat + 50, ColorCustomizer::bFloat + 50))

#define FILLCOLORDARK1(a) (MC_Color(ColorCustomizer::rFloat - a, ColorCustomizer::gFloat - a, ColorCustomizer::bFloat - a))
#define FILLCOLORLIGHT1(a) (MC_Color(ColorCustomizer::rFloat + a, ColorCustomizer::gFloat + a, ColorCustomizer::bFloat + a))

#define FILLCOLORSMORT ((ColorCustomizer::rFloat + ColorCustomizer::gFloat * 1.5f + ColorCustomizer::bFloat) / 3 > 128 ? (FILLCOLORDARK) : (FILLCOLORLIGHT))
#define FILLCOLORSMART(a) ((ColorCustomizer::rFloat + ColorCustomizer::gFloat * 1.5f + ColorCustomizer::bFloat) / 3 > 128 ? (FILLCOLORDARK1(a)) : (FILLCOLORLIGHT1(a)))

#define OPACITY (ColorCustomizer::opacity)

bool isLeftClickDown = false;
bool isRightClickDown = false;
bool shouldToggleLeftClick = false;  // If true, toggle the focused module
bool shouldToggleRightClick = false;
bool resetStartPos = true;
bool initialised = false;
int scrollingDirection = 0;

SettingEntry* keybindMenuCurrent = nullptr;  // What setting is currently capturing the user's input?
int newKeybind = 0;
bool isCapturingKey = false;
bool shouldStopCapturing = false;

bool isConfirmingKey = false;  // Show a cancel and save button

struct SavedWindowSettings {
	vec2_t pos = {-1, -1};
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

#define clickScale (0.8f * (g_Data.getClientInstance()->getGuiData()->widthGame / 640.f))

#define textPadding (1.0f * clickScale)
#define textSize (1.0f * clickScale)
#define textHeight (textSize * 10.0f)
#define categoryMargin (0.5f * clickScale)
#define paddingRight (13.5f * clickScale)
#define crossSize (textHeight / 2.f)
#define crossWidth (0.3f * clickScale)
constexpr auto backgroundAlpha = 1;
#define selectedModuleColor MC_Color(30, 110, 200)
#define selectedSettingColor1 MC_Color(20, 100, 195)
#define selectedSettingColor2 MC_Color(40, 120, 205)
#define moduleColor MC_Color(15, 30, 50)
#define SettingColor1 MC_Color(10, 25, 45)
#define SettingColor2 MC_Color(20, 35, 55)

float currentYOffset = 0;
float currentXOffset = 0;

int timesRendered = 0;

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
	} else {  // Create window
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
	} else {  // Create window
		// TODO: restore settings for position etc
		std::shared_ptr<ClickModule> newModule = std::make_shared<ClickModule>();

		window->moduleMap.insert(std::make_pair(id, newModule));
		return newModule;
	}
}

void ClickGui::renderLabel(const char* text) {
}

void ClickGui::renderTooltip(std::string* text) {
	DrawUtils::doChroma();

	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2_t currentTooltipPos = vec2_t(5.f, windowSize.y - 15.f);
	float textWidth = DrawUtils::getTextWidth(text, textSize);
	vec2_t textPos = vec2_t(
		currentTooltipPos.x + textPadding,
		currentTooltipPos.y);
	vec4_t rectPos = vec4_t(
		currentTooltipPos.x - 2.f,
		currentTooltipPos.y - 2.f,
		currentTooltipPos.x + (textPadding * 2) + textWidth + 2.f,
		currentTooltipPos.y + textHeight + 2.f);
	DrawUtils::fillRectangle(rectPos, MC_Color(ColorCustomizer::rFloat, ColorCustomizer::gFloat, ColorCustomizer::bFloat), ColorCustomizer::opacity);
	DrawUtils::drawRectangle(rectPos, BLACKORWHITE(255), 1.f, 0.5f);
	if (TextCustomizer::chroma == true) {
		DrawUtils::drawText(textPos, text, MC_Color(DrawUtils::rcolors), textSize);
	} else {
		DrawUtils::drawText(textPos, text, MC_Color(TextCustomizer::rFloat, TextCustomizer::gFloat, TextCustomizer::bFloat), textSize);
	}
}

//*
std::vector<Category> categoryOrder;
std::vector<Category> nextOrder;

void ClickGui::setScale(float newscale) {
	//clickScale = newscale;
}

void ClickGui::renderCategory(Category category) {
	const char* categoryName = ClickGui::catToName(category);

	const std::shared_ptr<ClickWindow> ourWindow = getWindow(categoryName);

	// Reset Windows to pre-set positions to avoid confusion
	if (resetStartPos && ourWindow->pos.x <= 0) {
		float yot = g_Data.getGuiData()->windowSize.x;
		ourWindow->pos.y = 8;
		switch (category) {
		case Category::VISUAL:
			ourWindow->pos.x = 10.f;
			break;
		case Category::MOVEMENT:
			ourWindow->pos.x = yot / 7.f;
			break;
		case Category::HUD:
			ourWindow->pos.x = yot / 7.f * 2;
			break;
		}
	}

	const float xOffset = ourWindow->pos.x;
	const float yOffset = ourWindow->pos.y;
	vec2_t windowSize = ourWindow->size;
	currentXOffset = xOffset;
	currentYOffset = yOffset;

	struct ClickGuiItem {
		std::shared_ptr<IModule> mod;
		SettingEntry* setting;
		bool isSetting;

		ClickGuiItem(std::shared_ptr<IModule> mod) {
			this->mod = mod;
			isSetting = false;
		}
		ClickGuiItem(SettingEntry* setting) {
			this->setting = setting;
			isSetting = true;
		}
	};

	// Get All Modules in our category
	std::vector<std::shared_ptr<IModule>> moduleList;
	getModuleListByCategory(category, &moduleList);

	// Get max width of all text
	{
		for (auto& it : moduleList) {
			std::string label = it->getModuleName();
			windowSize.x = fmax(windowSize.x, DrawUtils::getTextWidth(&label, textSize, Fonts::SMOOTH));
		}
	}

	vec2_t mousePos = *g_Data.getClientInstance()->getMousePos();

	// Convert mousePos to visual Pos
	{
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;

		mousePos = mousePos.div(windowSizeReal);
		mousePos = mousePos.mul(windowSize);
	}

	bool canClick = true;

	{
		bool funny = false;
		for (auto i : windowMap) {
			if (i.second.get() == ourWindow.get()) {
				funny = true;
				continue;
			}
			if (funny && i.second->selectableSurface.contains(&mousePos))
				canClick = false;
		}
	}

	float categoryHeaderYOffset = currentYOffset;

	if (ourWindow->isInAnimation) {
		if (ourWindow->isExtended) {
			ourWindow->animation *= 0.85f;
			if (ourWindow->animation < 0.001f) {
				ourWindow->yOffset = 0;  // reset scroll
				ourWindow->isInAnimation = false;
			}

		} else {
			ourWindow->animation = 1 - ((1 - ourWindow->animation) * 0.85f);
			if (1 - ourWindow->animation < 0.001f)
				ourWindow->isInAnimation = false;
		}
	}

	std::vector<ClickGuiItem> items;

	currentYOffset += textHeight + (textPadding * 2);
	// Loop through Modules to display em
	if (ourWindow->isExtended || ourWindow->isInAnimation) {
		if (ourWindow->isInAnimation) {
			currentYOffset -= ourWindow->animation * moduleList.size() * (textHeight + (textPadding * 2));
		}

		bool overflowing = false;
		const float cutoffHeight = roundf(g_Data.getGuiData()->heightGame * 0.75f) + 0.5f /*fix flickering related to rounding errors*/;
		int moduleIndex = 0;

		int itemIndex = 0;

		static auto getSettingSize = [&](SettingEntry* entry) {
			float offset = 2.f * (float)entry->nestValue;

			switch (entry->valueType) {
			case ValueType::BOOL_T: {
				char name[0x21];
				sprintf_s(name, 0x21, "%s", entry->name);
				if (name[0] != 0)
					name[0] = toupper(name[0]);

				std::string elTexto = name;
				return vec2_t(DrawUtils::getTextWidth(&elTexto, textSize) + 10 + offset, 0.f);  // /* because we add 10 to text padding + checkbox
			} break;
			case ValueType::ENUM_SETTING_GROUP_T:
			case ValueType::ENUM_T: {
				float maxLength = 0.f;
				SettingEnum* _enum = (SettingEnum*)entry->extraData;

				// Compute largest enum so that the size doesn't change when you click
				int i = 0;
				for (auto it = _enum->Entrys.begin(); it != _enum->Entrys.end(); it++, i++) {
					maxLength = std::fmaxf(maxLength, DrawUtils::getTextWidth(&it->GetName(), textSize));
				}

				maxLength += 10.f;  // Padding between right side and value + value and name

				char name[0x22];
				sprintf_s(name, "%s:", entry->name);

				if (name[0] != 0x0)
					name[0] = toupper(name[0]);

				std::string text = name;

				maxLength += DrawUtils::getTextWidth(&text, textSize);

				maxLength += offset;

				if (entry->valueType == ValueType::ENUM_SETTING_GROUP_T) {
					for (auto it = _enum->Entrys.begin(); it != _enum->Entrys.end(); it++, i++) {
						std::string text = it->GetName();
						maxLength = fmax(DrawUtils::getTextWidth(&text, textSize) + 7 + offset, maxLength);
					}
				}

				return vec2_t(maxLength, 0.f);
			} break;
			case ValueType::INT_T:
			case ValueType::FLOAT_T: {
				// Convert first letter to uppercase for more friendlieness
				char name[0x22];
				sprintf_s(name, "%s:", entry->name);
				if (name[0] != 0)
					name[0] = toupper(name[0]);

				std::string elTexto = name;
				return vec2_t(DrawUtils::getTextWidth(&elTexto, textSize) + 5 + offset, 0.f);  // /* because we add 5 to text padding
			} break;
			case ValueType::KEYBIND_T: {
				if (!isCapturingKey || (keybindMenuCurrent != entry && isCapturingKey)) {
					char name[0x21];
					sprintf_s(name, 0x21, "%s:", entry->name);
					if (name[0] != 0)
						name[0] = toupper(name[0]);

					std::string text = name;

					const char* key;

					if (entry->value->_int > 0 && entry->value->_int < 190)
						key = KeyNames[entry->value->_int];
					else if (entry->value->_int == 0x0)
						key = "NONE";
					else
						key = "???";

					if (keybindMenuCurrent == entry && isCapturingKey) {
						key = "...";
					} else if (keybindMenuCurrent == entry && isConfirmingKey) {
						if (newKeybind > 0 && newKeybind < 190)
							key = KeyNames[newKeybind];
						else if (newKeybind == 0x0)
							key = "N/A";
						else
							key = "???";
					}

					std::string keyb = key;
					float keybSz = textHeight * 0.8f;

					float length = 10.f;  // because we add 5 to text padding + keybind name
					length += DrawUtils::getTextWidth(&text, textSize);
					length += DrawUtils::getTextWidth(&keyb, textSize);

					return vec2_t(length + offset, 0.f);
				} else {
					std::string text = "Press new bind...";
					return vec2_t(DrawUtils::getTextWidth(&text, textSize) + offset, 0.f);
				}
			} break;
			default:
				break;
			}

			return vec2_t(0.f, 0.f);
		};

		for (auto it = moduleList.begin(); it != moduleList.end(); ++it) {
			auto mod = *it;
			std::shared_ptr<ClickModule> clickMod = getClickModule(ourWindow, mod->getRawModuleName());
			std::vector<SettingEntry*>* settings = mod->getSettings();

			ClickGuiItem module(mod);

			items.push_back(module);

			if (clickMod->isExtended && settings->size() > 2) {
				for (auto it2 = settings->begin(); it2 != settings->end(); ++it2) {
					SettingEntry* setting = *it2;

					if (strcmp(setting->name, "enabled") == 0 || strcmp(setting->name, "Keybind") == 0 || strcmp(setting->name, "Visible") == 0)
						continue;

					items.push_back(setting);

					auto newList = setting->getAllExtendedSettings();

					for (auto sett : newList) {
						windowSize.x = fmaxf(getSettingSize(sett).x, windowSize.x);

						items.push_back(sett);
					}

					windowSize.x = fmaxf(getSettingSize(setting).x, windowSize.x);
				}
				SettingEntry* setting = (*settings)[2];
				items.push_back(setting);  // Add the "Visible" setting to the end of the settings.
				windowSize.x = fmaxf(getSettingSize(setting).x, windowSize.x);

				setting = (*settings)[0];
				items.push_back(setting);  // Add our special Keybind setting
				windowSize.x = fmaxf(getSettingSize(setting).x, windowSize.x);
			}
		}

		const float xEnd = currentXOffset + windowSize.x + paddingRight;

		//*
		for (auto& item : items) {
			itemIndex++;

			if (itemIndex < ourWindow->yOffset)
				continue;

			float probableYOffset = (itemIndex - ourWindow->yOffset) * (textHeight + (textPadding * 2));

			if (ourWindow->isInAnimation) {
				if (probableYOffset > cutoffHeight) {
					overflowing = true;
					break;
				}
			} else if ((currentYOffset - ourWindow->pos.y) > cutoffHeight || currentYOffset > g_Data.getGuiData()->heightGame - 5) {
				overflowing = true;
				break;
			}

			bool allowRender = currentYOffset >= categoryHeaderYOffset;

			if (!item.isSetting) {
				auto mod = item.mod;

				std::shared_ptr<ClickModule> clickMod = getClickModule(ourWindow, mod->getRawModuleName());
				std::vector<SettingEntry*>* settings = mod->getSettings();

				std::string textStr = mod->getModuleName();

				vec2_t textPos = vec2_t(
					currentXOffset + textPadding,
					currentYOffset + textPadding);
				vec4_t rectPos = vec4_t(
					currentXOffset,
					currentYOffset,
					xEnd,
					currentYOffset + textHeight + (textPadding * 2));

				bool allowRender = currentYOffset >= categoryHeaderYOffset;

				// Background
				if (allowRender) {
					if (!ourWindow->isInAnimation && !isDragging && rectPos.contains(&mousePos) && canClick) {  // Is the Mouse hovering above us?
						DrawUtils::fillRectangle(rectPos, FILLCOLORSMART(50), OPACITY);
						std::string tooltip = mod->getTooltip();
						static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
						if (clickGuiMod->showTooltips && !tooltip.empty())
							renderTooltip(&tooltip);
						if (shouldToggleLeftClick && !ourWindow->isInAnimation) {  // Are we being clicked?
							mod->toggle();
							shouldToggleLeftClick = false;
						}
					} else {
						DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);
					}

					// Text
					DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? TEXTCOLOR : BLACKORWHITE(100), textSize);

					if (rectPos.contains(&mousePos) && shouldToggleRightClick && !ourWindow->isInAnimation && canClick) {
						shouldToggleRightClick = false;
						clickMod->isExtended = !clickMod->isExtended;
					}
				}
			} else {
				auto setting = item.setting;

				float offset = 2.f * (float)setting->nestValue;

				setting->makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();

				if (strcmp(setting->name, "enabled") == 0 || strcmp(setting->name, "keybind") == 0)
					continue;

				vec2_t textPos = vec2_t(
					currentXOffset + textPadding + 5 + offset,
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
					DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);
					vec4_t selectableSurface = vec4_t(
						textPos.x + textPadding,
						textPos.y + textPadding,
						xEnd - textPadding,
						textPos.y + textHeight - textPadding);

					bool isFocused = selectableSurface.contains(&mousePos) && canClick;
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

						DrawUtils::drawRectangle(boxPos, BLACKORWHITE(255), isFocused ? 1 : 0.8f, 0.5f);

						if (setting->value->_bool) {
							auto colCross = BLACKORWHITE(255);
							DrawUtils::setColor(colCross.r, colCross.g, colCross.b, 1);
							boxPos.x += textPadding;
							boxPos.y += textPadding;
							boxPos.z -= textPadding;
							boxPos.w -= textPadding;
							DrawUtils::drawLine(vec2_t(boxPos.x, boxPos.y), vec2_t(boxPos.z, boxPos.w), 0.5f);
							DrawUtils::drawLine(vec2_t(boxPos.z, boxPos.y), vec2_t(boxPos.x, boxPos.w), 0.5f);
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
						////windowSize.x = fmax(windowSize.x, DrawUtils::getTextWidth(&elTexto, textSize) + 10 + offset);  // /* because we add 10 to text padding + checkbox
						DrawUtils::drawText(textPos, &elTexto, isFocused ? TEXTCOLOR : BLACKORWHITE(100), textSize);
					}
					break;
				}
				case ValueType::ENUM_SETTING_GROUP_T:
				case ValueType::ENUM_T: {
					// minValue is whether the enum is expanded
					// value is the actual mode (int)

					SettingEnum* _enum = (SettingEnum*)setting->extraData;
					std::string selected = "";  // We are looping through all the values so we might as well set the text beforehand

					// Text and background
					{
						float maxLength = 0.f;

						// Compute largest enum so that the size doesn't change when you click
						int i = 0;
						for (auto it = _enum->Entrys.begin(); it != _enum->Entrys.end(); it++, i++) {
							if (setting->value->_int == i)
								selected = it->GetName();

							maxLength = std::fmaxf(maxLength, DrawUtils::getTextWidth(&it->GetName(), textSize));
						}

						maxLength += 10.f;  // Padding between right side and value + value and name

						char name[0x22];
						sprintf_s(name, "%s:", setting->name);

						if (name[0] != 0x0)
							name[0] = toupper(name[0]);

						std::string text = name;

						maxLength += DrawUtils::getTextWidth(&text, textSize);

						//windowSize.x = fmax(windowSize.x, maxLength + offset);

						DrawUtils::drawText(textPos, &text, BLACKORWHITE(255), textSize);
						rectPos.w = currentYOffset + textHeight + (textPadding * 2);
						if (setting->minValue->_bool)
							currentYOffset += textHeight + textPadding;
						DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);

						vec2_t textPos2 = textPos;

						float textX = rectPos.z - 5.f;
						textX -= DrawUtils::getTextWidth(&selected, textSize);

						textPos2.x = textX;

						DrawUtils::drawText(textPos2, &selected, BLACKORWHITE(100), textSize);
					}

					// Logic
					{
						bool isFocused = rectPos.contains(&mousePos) && canClick;

						if (setting->groups.empty()) {
							if (isFocused && shouldToggleLeftClick) {
								setting->value->_int = (setting->value->_int + 1) % ((SettingEnum*)setting->extraData)->Entrys.size();
								shouldToggleLeftClick = false;
							}
						} else {
							SettingGroup* group = setting->groups[setting->value->_int];

							bool isModsExpanded = false;

							if (group != nullptr)
								isModsExpanded = group->isExpanded;

							if (isFocused && shouldToggleLeftClick) {
								if (!isModsExpanded) {
									setting->minValue->_bool = !setting->minValue->_bool;
								} else {
									for (auto g : setting->groups) {
										if (g != nullptr)
											g->isExpanded = false;
									}

									setting->minValue->_bool = true;
								}
								shouldToggleLeftClick = false;
							}

							if (isFocused && shouldToggleRightClick && group != nullptr) {
								setting->minValue->_bool = false;
								bool expand = !group->isExpanded;

								for (auto g : setting->groups) {
									if (g != nullptr)
										g->isExpanded = expand;
								}

								shouldToggleRightClick = false;
							}
						}
					}

					// Drop down menu
					if (setting->minValue->_bool) {
						int i = 0;
						for (auto it = _enum->Entrys.begin(); it != _enum->Entrys.end(); it++, i++) {
							bool highlight = i == setting->value->_int;

							textPos.y += textPadding + textHeight;
							if (it + 1 != _enum->Entrys.end())
								currentYOffset += textHeight + textPadding;

							textPos.x += 2;

							std::string text = it->GetName();
							//windowSize.x = fmax(windowSize.x, DrawUtils::getTextWidth(&text, textSize) + 7 + offset);
							DrawUtils::drawText(textPos, &text, highlight ? TEXTCOLOR : BLACKORWHITE(100), textSize);

							rectPos.y += textPadding + textHeight;
							rectPos.w += textPadding + textHeight;

							textPos.x -= 2;

							DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);

							// Logic
							if (rectPos.contains(&mousePos) && canClick && shouldToggleLeftClick) {
								setting->value->_int = i;
								shouldToggleLeftClick = false;
							}
						}
					}
				} break;
				case ValueType::FLOAT_T: {
					// Text and background
					{
						// Convert first letter to uppercase for more friendlieness
						char name[0x22];
						sprintf_s(name, "%s:", setting->name);
						if (name[0] != 0)
							name[0] = toupper(name[0]);

						std::string elTexto = name;
						//windowSize.x = fmax(windowSize.x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 + offset);  // /* because we add 5 to text padding
						DrawUtils::drawText(textPos, &elTexto, BLACKORWHITE(255), textSize);
						currentYOffset += textPadding + textHeight;
						rectPos.w = currentYOffset;
						DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);
					}

					if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
						overflowing = true;
						break;
					}
					// Slider
					{
						vec4_t rect = vec4_t(
							currentXOffset + textPadding + 5 + offset,
							currentYOffset + textPadding,
							xEnd - textPadding,
							currentYOffset - textPadding + textHeight);

						// Visuals & Logic
						{
							rectPos.y = currentYOffset;
							rectPos.w += textHeight + (textPadding * 2);
							// Background
							const bool areWeFocused = rect.contains(&mousePos) && canClick;

							DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);                    // Background
							DrawUtils::drawRectangle(rect, BLACKORWHITE(255), 1.f, backgroundAlpha);  // Slider background

							const float minValue = setting->minValue->_float;
							const float maxValue = setting->maxValue->_float - minValue;
							float value = (float)std::fmax(0, setting->value->_float - minValue);  // Value is now always > 0 && < maxValue
							if (value > maxValue)
								value = maxValue;
							value /= maxValue;  // Value is now in range 0 - 1
							const float endXlol = (xEnd - textPadding) - (currentXOffset + textPadding + 5);
							value *= endXlol;  // Value is now pixel diff between start of bar and end of progress

							// Draw Int
							{
								vec2_t mid = vec2_t(
									rect.x + ((rect.z - rect.x) / 2),
									rect.y - 0.2f);
								char str[10];
								sprintf_s(str, 10, "%.2f", setting->value->_float);
								std::string text = str;
								mid.x -= DrawUtils::getTextWidth(&text, textSize) / 2;

								DrawUtils::drawText(mid, &text, BLACKORWHITE(255), textSize);
							}

							// Draw Progress
							{
								rect.z = rect.x + value;
								DrawUtils::fillRectangle(rect, FILLCOLORSMORT, (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
							}

							// Drag Logic
							{
								if (setting->isDragging) {
									if (isLeftClickDown && !isRightClickDown)
										value = mousePos.x - rect.x;
									else
										setting->isDragging = false;
								} else if (areWeFocused && shouldToggleLeftClick && !ourWindow->isInAnimation) {
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
						//windowSize.x = fmax(windowSize.x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 + offset);  // /* because we add 5 to text padding
						DrawUtils::drawText(textPos, &elTexto, TEXTCOLOR, textSize);
						currentYOffset += textPadding + textHeight;
						rectPos.w = currentYOffset;
						DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);
					}
					if ((currentYOffset - ourWindow->pos.y) > (g_Data.getGuiData()->heightGame * 0.75)) {
						overflowing = true;
						break;
					}
					// Slider
					{
						vec4_t rect = vec4_t(
							currentXOffset + textPadding + 5 + offset,
							currentYOffset + textPadding,
							xEnd - textPadding,
							currentYOffset - textPadding + textHeight);

						// Visuals & Logic
						{
							rectPos.y = currentYOffset;
							rectPos.w += textHeight + (textPadding * 2);
							// Background
							const bool areWeFocused = rect.contains(&mousePos) && canClick;

							DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);                    // Background
							DrawUtils::drawRectangle(rect, BLACKORWHITE(255), 1.f, backgroundAlpha);  // Slider background

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

								DrawUtils::drawText(mid, &text, BLACKORWHITE(255), textSize);
							}

							// Draw Progress
							{
								rect.z = rect.x + value;
								DrawUtils::fillRectangle(rect, FILLCOLORSMORT, (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
							}

							// Drag Logic
							{
								if (setting->isDragging) {
									if (isLeftClickDown && !isRightClickDown)
										value = mousePos.x - rect.x;
									else
										setting->isDragging = false;
								} else if (areWeFocused && shouldToggleLeftClick && !ourWindow->isInAnimation) {
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
					}
				} break;
				case ValueType::KEYBIND_T: {
					rectPos.w = currentYOffset + textHeight + (textPadding * 2);
					if (!isCapturingKey || (keybindMenuCurrent != setting && isCapturingKey)) {
						char name[0x21];
						sprintf_s(name, 0x21, "%s:", setting->name);
						if (name[0] != 0)
							name[0] = toupper(name[0]);

						std::string text = name;

						DrawUtils::drawText(textPos, &text, TEXTCOLOR, textSize);

						const char* key;

						if (setting->value->_int > 0 && setting->value->_int < 190)
							key = KeyNames[setting->value->_int];
						else if (setting->value->_int == 0x0)
							key = "NONE";
						else
							key = "???";

						if (keybindMenuCurrent == setting && isCapturingKey) {
							key = "...";
						} else if (keybindMenuCurrent == setting && isConfirmingKey) {
							if (newKeybind > 0 && newKeybind < 190)
								key = KeyNames[newKeybind];
							else if (newKeybind == 0x0)
								key = "N/A";
							else
								key = "???";
						}

						std::string keyb = key;
						float keybSz = textHeight * 0.8f;

						float length = 10.f;  // because we add 5 to text padding + keybind name
						length += DrawUtils::getTextWidth(&text, textSize);
						length += DrawUtils::getTextWidth(&keyb, textSize);

						//windowSize.x = fmax(windowSize.x, length + offset);

						DrawUtils::drawText(textPos, &text, BLACKORWHITE(255), textSize);

						vec2_t textPos2(rectPos.z - 5.f, textPos.y);
						textPos2.x -= DrawUtils::getTextWidth(&keyb, textSize);

						DrawUtils::drawText(textPos2, &keyb, BLACKORWHITE(100), textSize);
					} else {
						std::string text = "Press new bind...";
						//windowSize.x = fmax(windowSize.x, DrawUtils::getTextWidth(&text, textSize));

						DrawUtils::drawText(textPos, &text, BLACKORWHITE(255), textSize);
					}

					DrawUtils::fillRectangle(rectPos, FILLCOLOR, OPACITY);

					if ((currentYOffset - ourWindow->pos.y) > (g_Data.getGuiData()->heightGame * 0.75)) {
						overflowing = true;
						break;
					}

					// Logic
					{
						bool isFocused = rectPos.contains(&mousePos) && canClick;

						if (isFocused && shouldToggleLeftClick && !(isCapturingKey && keybindMenuCurrent != setting /*don't let the user click other stuff while changing a keybind*/)) {
							keybindMenuCurrent = setting;
							isCapturingKey = true;
						}

						if (isFocused && shouldToggleRightClick && !(isCapturingKey && keybindMenuCurrent != setting)) {
							setting->value->_int = 0x0;  // Clear

							isCapturingKey = false;
						}

						if (shouldStopCapturing && keybindMenuCurrent == setting) {  // The user has selected a key
							shouldStopCapturing = false;
							isCapturingKey = false;
							setting->value->_int = newKeybind;
						}
					}
				} break;

				// WIP but I'll keep it here for now
				/*case ValueType::COLOR_PICKER_T: {
					break;  // not implemented yet, gonna work on other stuff
					// TODO: finish this
					{
						// Convert first letter to uppercase for more friendlieness
						char name[0x21];
						sprintf_s(name, 0x21, "%s:", setting->name);
						if (name[0] != 0)
							name[0] = toupper(name[0]);

						std::string elTexto = name;
						//windowSize.x = fmax(windowSize.x, DrawUtils::getTextWidth(&elTexto, textSize) + 5);  // /* because we add 5 to text padding
						DrawUtils::drawText(textPos, &elTexto, MC_Color(1.0f, 1.0f, 1.0f), textSize);
						currentYOffset += textPadding + textHeight;
						rectPos.w = currentYOffset;
						DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);
					}
					if ((currentYOffset - ourWindow->pos.y) > (g_Data.getGuiData()->heightGame * 0.75)) {
						overflowing = true;
						break;
					}

					ColorSettingValue* col = reinterpret_cast<ColorSettingValue*>(setting->value->color);
					MC_Color theColor = col->displayColor;

					// Red slider
					{
						vec4_t rect = vec4_t(
							currentXOffset + textPadding + 5,
							currentYOffset + textPadding,
							xEnd - textPadding,
							currentYOffset - textPadding + textHeight);

						int red = (int)std::floorf(col->displayColor.r * 255);

						// Visuals & Logic
						{
							rectPos.y = currentYOffset;
							rectPos.w += textHeight + (textPadding * 2);
							// Background
							const bool areWeFocused = rect.contains(&mousePos);

							DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);                   // Background
							DrawUtils::drawRectangle(rect, MC_Color(1.0f, 1.0f, 1.0f), 1.f, backgroundAlpha);  // Slider background

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

								DrawUtils::drawText(mid, &text, BLACKORWHITE, textSize);
							}

							// Draw Progress
							{
								rect.z = rect.x + value;
								DrawUtils::fillRectangle(rect, MC_Color(255, 0, 0), (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
							}

							// Drag Logic
							{
								if (setting->isDragging) {
									if (isLeftClickDown && !isRightClickDown)
										value = mousePos.x - rect.x;
									else
										setting->isDragging = false;
								} else if (areWeFocused && shouldToggleLeftClick && !ourWindow->isInAnimation) {
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
					}
				} break;*/
				default: {
					char alc[100];
					sprintf_s(alc, 100, "Not implemented (%s)", setting->name);
					std::string elTexto = alc;
					// Adjust window size if our text is too  t h i c c
					//windowSize.x = fmax(windowSize.x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 + offset);  // /* because we add 5 to text padding

					DrawUtils::drawText(textPos, &elTexto, MC_Color(255, 0, 0), textSize);
				} break;
				}
			}
			currentYOffset += textHeight + (textPadding * 2);
		}
		//*/

		vec4_t winRectPos = vec4_t(
			xOffset,
			yOffset,
			xEnd,
			currentYOffset);

		ourWindow->selectableSurface = winRectPos;

		if (winRectPos.contains(&mousePos) && canClick) {
			if (scrollingDirection > 0 && overflowing) {
				ourWindow->yOffset += scrollingDirection;
			} else if (scrollingDirection < 0) {
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
			currentXOffset + windowSize.x + paddingRight + categoryMargin,
			categoryHeaderYOffset + textHeight + (textPadding * 2));

		// Extend Logic
		{
			if (rectPos.contains(&mousePos) && shouldToggleRightClick && !isDragging && canClick) {
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
					for (auto itr = nextOrder.begin(); itr != nextOrder.end(); ++itr) {
						if (*itr._Ptr == category) {
							nextOrder.erase(itr);
							break;
						}
					}
					nextOrder.push_back(category);  // render on top
				} else {                            // Stopped dragging
					isDragging = false;
				}
			} else if (rectPos.contains(&mousePos) && shouldToggleLeftClick && canClick) {
				isDragging = true;
				draggedWindow = Utils::getCrcHash(categoryName);
				shouldToggleLeftClick = false;
				dragStart = mousePos;
			}
		}

		// Draw component
		{
			// Draw Text
			std::string textStr = categoryName;
			DrawUtils::drawText(textPos, &textStr, TEXTCOLOR, textSize);
			DrawUtils::fillRectangle(rectPos, FILLCOLOR, 1.f);

			DrawUtils::fillRectangle(vec4_t(rectPos.x, rectPos.w - 1, rectPos.z, rectPos.w), FILLCOLORSMORT, 1 - ourWindow->animation);
			// Draw Dash
			GuiUtils::drawCrossLine(vec2_t(
										currentXOffset + windowSize.x + paddingRight - (crossSize / 2) - 1.f,
										categoryHeaderYOffset + textPadding + (textHeight / 2)),
									BLACKORWHITE(255), crossWidth, crossSize, !ourWindow->isExtended);
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
	if (!moduleMgr->isInitialized())
		return;

	if (categoryOrder.empty()) {
		categoryOrder.push_back(Category::COMBAT);
		categoryOrder.push_back(Category::VISUAL);
		categoryOrder.push_back(Category::MOVEMENT);
		categoryOrder.push_back(Category::PLAYER);
		categoryOrder.push_back(Category::WORLD);
		categoryOrder.push_back(Category::MISC);
		categoryOrder.push_back(Category::HUD);
	}

	if (!nextOrder.empty())
		categoryOrder = nextOrder;

	nextOrder = categoryOrder;

	if (timesRendered < 10)
		timesRendered++;

	// Fill Background
	{
		DrawUtils::fillRectangle(vec4_t(
									 0,
									 0,
									 g_Data.getClientInstance()->getGuiData()->widthGame,
									 g_Data.getClientInstance()->getGuiData()->heightGame),
								 MC_Color(0, 0, 0), 0.2f);
	}

	// Render all categorys
	for (auto window : categoryOrder) {
		renderCategory(window);
	}

	shouldToggleLeftClick = false;
	shouldToggleRightClick = false;
	resetStartPos = false;

	DrawUtils::flush();
}

void ClickGui::init() { initialised = true; }

void ClickGui::onMouseClickUpdate(int key, bool isDown) {
	if (!moduleMgr->getModule<ClickGuiMod>()->isEnabled())
		return;

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

	if (isCapturingKey && !shouldStopCapturing) {
		newKeybind = key;
		shouldStopCapturing = true;
	}

	if (timesRendered < 10)
		return;
	timesRendered = 0;

	switch (key) {
	case VK_ESCAPE:
		clickGuiMod->setEnabled(false);
		isCapturingKey = false;
		isConfirmingKey = false;
		keybindMenuCurrent = nullptr;

		return;
	default:
		if (key == clickGuiMod->getKeybind()) {
			clickGuiMod->setEnabled(false);
			isCapturingKey = false;
			isConfirmingKey = false;
			keybindMenuCurrent = nullptr;
		}
	}
}

using json = nlohmann::json;
void ClickGui::onLoadConfig(void* confVoid) {
	savedWindowSettings.clear();
	windowMap.clear();
	json* conf = reinterpret_cast<json*>(confVoid);
	if (conf->contains("ClickGui")) {
		auto obj = conf->at("ClickGui");
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
								windowSettings.pos = {posVal["x"].get<float>(), posVal["y"].get<float>()};
							} catch (std::exception e) {
							}
						}
					}
					if (value.contains("isExtended")) {
						auto isExtVal = value.at("isExtended");
						if (!isExtVal.is_null() && isExtVal.is_boolean()) {
							try {
								windowSettings.isExtended = isExtVal.get<bool>();
							} catch (std::exception e) {
							}
						}
					}
					savedWindowSettings[Utils::getCrcHash(catName)] = windowSettings;
				} catch (std::exception e) {
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
		savedWindowSettings[wind.first] = {wind.second->pos, wind.second->isExtended, wind.second->name};
	}

	// Save to json
	if (conf->contains("ClickGui"))
		conf->erase("ClickGui");

	json obj = {};

	for (const auto& wind : savedWindowSettings) {
		json subObj = {};
		subObj["pos"]["x"] = wind.second.pos.x;
		subObj["pos"]["y"] = wind.second.pos.y;
		subObj["isExtended"] = wind.second.isExtended;
		obj[wind.second.name] = subObj;
	}

	conf->emplace("ClickGui", obj);
}
//e