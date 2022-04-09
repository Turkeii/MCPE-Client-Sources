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
	vec2 pos = {-1, -1};
	bool isExtended = true;
	const char* name = "";
};

std::map<unsigned int, std::shared_ptr<ClickWindow>> windowMap;
std::map<unsigned int, SavedWindowSettings> savedWindowSettings;

bool isDragging = false;
unsigned int draggedWindow = -1;
vec2 dragStart = vec2();

unsigned int focusedElement = -1;
bool isFocused = false;

static constexpr float textPadding = 0.80f;
static constexpr float textSize = 0.80f;
static constexpr float textHeight = textSize * 8.0f;
static constexpr float categoryMargin = 0.5f;
static constexpr float paddingRight = 13.f;
static constexpr float crossSize = textHeight / 2.f;
static constexpr float crossWidth = 0.3f;
static const MC_Color selectedModuleColor = MC_Color(184, 0, 255);
static const MC_Color selectedSettingColor1 = MC_Color(184, 0, 255);
static const MC_Color selectedSettingColor2 = MC_Color(184, 0, 255);

static float rcolors[4];  // Rainbow color RGBA

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
	static auto partner = moduleMgr->getModule<Partner>();
	static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
	vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2 currentTooltipPos = vec2(5.f, windowSize.y - 15.f);
	float textWidth = DrawUtils::getTextWidth(text, textSize);
	vec2 textPos = vec2(
		currentTooltipPos.x + textPadding,
		currentTooltipPos.y);
	vec4 rectPos = vec4(
		currentTooltipPos.x - 2.f,
		currentTooltipPos.y - 2.f,
		currentTooltipPos.x + (textPadding * 2) + textWidth + 2.f,
		currentTooltipPos.y + textHeight + 2.f);
	if (partner->Partnered.selected == 1) {
		DrawUtils::drawText(textPos, text, MC_Color(150, 30, 255), textSize);
	} else {
		if (partner->Partnered.selected == 0) {
			DrawUtils::drawText(textPos, text, MC_Color(0, 0, 255), textSize);
		} else {
			if (partner->Partnered.selected == 2) {
				DrawUtils::drawText(textPos, text, MC_Color(184, 0, 255), textSize);
			} else {
				DrawUtils::drawText(textPos, text, MC_Color(184, 0, 255), textSize);
			}
			DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
			DrawUtils::drawRectangle(rectPos, MC_Color(0, 0, 0), 1.f, 0.5f);
		}
	}
}
	void ClickGui::renderCategory(Category category) {
	static float currColor[4];  // ArrayList colors

	// rainbow colors
	{
		if (currColor[3] < 1) {
			currColor[0] = 1;
			currColor[1] = 0.2f;
			currColor[2] = 0.2f;
			currColor[3] = 1;
		}
		Utils::ApplyRainbow(currColor, 0.00025f);
	}
	const char* categoryName = ClickGui::catToName(category);

	const std::shared_ptr<ClickWindow> ourWindow = getWindow(categoryName);

	// Reset Windows to pre-set positions to avoid confusion
	if (resetStartPos) {
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
		case Category::SERVER:
			ourWindow->pos.x = yot / 7.f * 4.f;
			break;
		case Category::WORLD:
			ourWindow->pos.x = yot / 7.f * 5.f;
			break;
		case Category::FLYS:
			ourWindow->pos.x = yot / 7.f * 6.f;
			break;
		case Category::GUI:
			ourWindow->pos.x = yot / 7.f * 4.f;
			ourWindow->pos.y = 145.f;
			break;
		case Category::CONFIG:
			ourWindow->pos.x = yot / 7.f * 5.8f;
			ourWindow->pos.y = 145.f;
			break;
		case Category::ENTITY:
			ourWindow->pos.x = yot / 7.f * 5.f;
			ourWindow->pos.y = 145.f;
			break;
		case Category::PARTNER:
			ourWindow->pos.x = yot / 7.f * 6.4f;
			ourWindow->pos.y = 145.f;
			break;
		}
	}

	const float xOffset = ourWindow->pos.x;
	const float yOffset = ourWindow->pos.y;
	vec2* windowSize = &ourWindow->size;
	currentXOffset = xOffset;
	currentYOffset = yOffset;

	// Get All Modules in our category
	std::vector<std::shared_ptr<IModule>> moduleList;
	getModuleListByCategory(category, &moduleList);

	// Get max width of all text
	{
		for (auto& it : moduleList) {
			std::string label = it->getModuleName();
			windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&label, textSize, Fonts::SMOOTH));
		}
	}

	const float xEnd = currentXOffset + windowSize->x + paddingRight;

	vec2 mousePos = *g_Data.getClientInstance()->getMousePos();

// Convert mousePos to visual Pos
	{
		vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		vec2 windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;

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

		} else {
			ourWindow->animation = 1 - ((1 - ourWindow->animation) * 0.85f);
			if (1 - ourWindow->animation < 0.001f)
				ourWindow->isInAnimation = false;
		}
	}

	currentYOffset += textHeight + (textPadding * 2);
	// Loop through Modules to display em
	// ANIMATIONS
	if (ourWindow->isExtended || ourWindow->isInAnimation) {
		if (ourWindow->isInAnimation) {
			currentYOffset -= ourWindow->animation * moduleList.size() * (textHeight + (textPadding * 2));
		}

		bool overflowing = false;
		const float cutoffHeight = roundf(g_Data.getGuiData()->heightGame * 0.75f) + 0.5f /*fix flickering related to rounding errors*/;
		int moduleIndex = 0;
		for (auto& mod : moduleList) {
			moduleIndex++;
			if (moduleIndex < ourWindow->yOffset)
				continue;
			float probableYOffset = (moduleIndex - ourWindow->yOffset) * (textHeight + (textPadding * 2));

			if (ourWindow->isInAnimation) {  // Estimate, we don't know about module settings yet
				if (probableYOffset > cutoffHeight) {
					overflowing = true;
					break;
				}
			} else if ((currentYOffset - ourWindow->pos.y) > cutoffHeight || currentYOffset > g_Data.getGuiData()->heightGame - 5) {
				overflowing = true;
				break;
			}

			std::string textStr = mod->getModuleName();

			vec2 textPos = vec2(
				currentXOffset + textPadding,
				currentYOffset + textPadding);
			vec4 rectPos = vec4(
				currentXOffset,
				currentYOffset,
				xEnd,
				currentYOffset + textHeight + (textPadding * 2));

			bool allowRender = currentYOffset >= categoryHeaderYOffset;
			static auto partner = moduleMgr->getModule<Partner>();
			// Background
			if (allowRender) {
				static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
				if (!ourWindow->isInAnimation && !isDragging && rectPos.contains(&mousePos)) {  // Is the Mouse hovering above us?
					if (ClickguiOpac->RGB) {
						DrawUtils::fillRectangle(rectPos, currColor, ClickguiOpac->opacity);
					} else {
						if (partner->Partnered.selected == 1)
							DrawUtils::fillRectangle(rectPos, MC_Color(150, 30, 255), ClickguiOpac->opacity);
						else
						if (partner->Partnered.selected == 0)
							DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 255), ClickguiOpac->opacity);
						else 
							if (partner->Partnered.selected == 2)
							DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
						else 
							DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
					}
					std::string tooltip = mod->getTooltip();
					static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
					if (clickGuiMod->showTooltips && !tooltip.empty())
						renderTooltip(&tooltip);
					if (shouldToggleLeftClick && !ourWindow->isInAnimation) {  // Are we being clicked?
						mod->toggle();
						shouldToggleLeftClick = false;
					}
				} else {
					DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
				}
			}

			// Text
			static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
			if (partner->Partnered.selected == 1) {
				if (clickGuiMod->RGB) {
					if (allowRender)
						DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(150, 30, 255) : MC_Color(currColor), textSize);
				} else {
					if (allowRender)
						DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(150, 30, 255) : MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), textSize);
				}
			} else {
				if (partner->Partnered.selected == 0) {
					if (clickGuiMod->RGB) {
						if (allowRender)
							DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(0, 0, 255) : MC_Color(currColor), textSize);
					} else {
						if (allowRender)
							DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(0, 0, 255) : MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), textSize);
					}
				} else {
					if (clickGuiMod->RGB) {
						if (allowRender)
							DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(ClickGuiMod::trcolor, ClickGuiMod::tgcolor, ClickGuiMod::tbcolor) : MC_Color(currColor), textSize);
					} else {
						if (partner->Partnered.selected == 2) {
							if (allowRender)
								DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(ClickGuiMod::trcolor, ClickGuiMod::tgcolor, ClickGuiMod::tbcolor) : MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), textSize);
						} else {
							if (allowRender)
							DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? MC_Color(ClickGuiMod::trcolor, ClickGuiMod::tgcolor, ClickGuiMod::tbcolor) : MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), textSize);
						}
					}
				}
			}

			// Settings
			{
				std::vector<SettingEntry*>* settings = mod->getSettings();
				if (settings->size() > 2 && allowRender) {
					std::shared_ptr<ClickModule> clickMod = getClickModule(ourWindow, mod->getRawModuleName());
					if (rectPos.contains(&mousePos) && shouldToggleRightClick && !ourWindow->isInAnimation) {
						shouldToggleRightClick = false;
						clickMod->isExtended = !clickMod->isExtended;
					}
					if (partner->Partnered.selected == 1) {
						GuiUtils::drawCrossLine(vec2(
													currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
													currentYOffset + textPadding + (textHeight / 2)),
												MC_Color(150, 30, 255), crossWidth, crossSize, !clickMod->isExtended);
					} else {
						if (partner->Partnered.selected == 0) {
							GuiUtils::drawCrossLine(vec2(
														currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
														currentYOffset + textPadding + (textHeight / 2)),
													MC_Color(0, 0, 255), crossWidth, crossSize, !clickMod->isExtended);
						} else {
							if (partner->Partnered.selected == 2) {
								GuiUtils::drawCrossLine(vec2(
															currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
															currentYOffset + textPadding + (textHeight / 2)),
														MC_Color(184, 0, 255), crossWidth, crossSize, !clickMod->isExtended);
							} else {
									GuiUtils::drawCrossLine(vec2(
															currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
															currentYOffset + textPadding + (textHeight / 2)),
															MC_Color(184, 0, 255), crossWidth, crossSize, !clickMod->isExtended);
							}
						}
					}

					currentYOffset += textHeight + (textPadding * 2);

					if (clickMod->isExtended) {
						float startYOffset = currentYOffset;
						for (auto setting : *settings) {
							if (strcmp(setting->name, "enabled") == 0 || strcmp(setting->name, "keybind") == 0)
								continue;

							vec2 textPos = vec2(
								currentXOffset + textPadding + 5,
								currentYOffset + textPadding);

							// Incomplete, because we dont know the endY yet
							vec4 rectPos = vec4(
								currentXOffset,
								currentYOffset,
								xEnd,
								0);

							if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
								overflowing = true;
								break;
							}

							switch (setting->valueType) {
							case ValueType::BOOL: {
								rectPos.w = currentYOffset + textHeight + (textPadding * 2);
								static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
								if (clickGuiMod->opacity) {
									DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), clickGuiMod->opacity);
								} else {
									DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), clickGuiMod->opacity);
								}
								vec4 selectableSurface = vec4(
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
								if (partner->Partnered.selected == 1) {
									vec4 boxPos = vec4(
										textPos.x + textPadding,
										textPos.y + textPadding,
										textPos.x + textHeight - textPadding,
										textPos.y + textHeight - textPadding);

									DrawUtils::drawRectangle(boxPos, MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), isFocused ? 1 : 0.8f, 0.5f);

									if (setting->value->_bool) {
										DrawUtils::setColor(255, 255, 255, 1);
										boxPos.x += textPadding;
										boxPos.y += textPadding;
										boxPos.z -= textPadding;
										boxPos.w -= textPadding;
										DrawUtils::drawLine(vec2(boxPos.x, boxPos.y), vec2(boxPos.z, boxPos.w), 0.5f);
										DrawUtils::drawLine(vec2(boxPos.z, boxPos.y), vec2(boxPos.x, boxPos.w), 0.5f);
									}
								} else {
									if (partner->Partnered.selected == 0) {
										vec4 boxPos = vec4(
											textPos.x + textPadding,
											textPos.y + textPadding,
											textPos.x + textHeight - textPadding,
											textPos.y + textHeight - textPadding);

										DrawUtils::drawRectangle(boxPos, MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), isFocused ? 1 : 0.8f, 0.5f);

										if (setting->value->_bool) {
											DrawUtils::setColor(255, 255, 255, 1);
											boxPos.x += textPadding;
											boxPos.y += textPadding;
											boxPos.z -= textPadding;
											boxPos.w -= textPadding;
											DrawUtils::drawLine(vec2(boxPos.x, boxPos.y), vec2(boxPos.z, boxPos.w), 0.5f);
											DrawUtils::drawLine(vec2(boxPos.z, boxPos.y), vec2(boxPos.x, boxPos.w), 0.5f);
										}
									} else {
										if (partner->Partnered.selected == 2) {
											vec4 boxPos = vec4(
												textPos.x + textPadding,
												textPos.y + textPadding,
												textPos.x + textHeight - textPadding,
												textPos.y + textHeight - textPadding);

											DrawUtils::drawRectangle(boxPos, MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), isFocused ? 1 : 0.8f, 0.5f);

											if (setting->value->_bool) {
												DrawUtils::setColor(255, 255, 255, 1);
												boxPos.x += textPadding;
												boxPos.y += textPadding;
												boxPos.z -= textPadding;
												boxPos.w -= textPadding;
												DrawUtils::drawLine(vec2(boxPos.x, boxPos.y), vec2(boxPos.z, boxPos.w), 0.5f);
												DrawUtils::drawLine(vec2(boxPos.z, boxPos.y), vec2(boxPos.x, boxPos.w), 0.5f);
											}
										} else {
											vec4 boxPos = vec4(
												textPos.x + textPadding,
												textPos.y + textPadding,
												textPos.x + textHeight - textPadding,
												textPos.y + textHeight - textPadding);

											DrawUtils::drawRectangle(boxPos, MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), isFocused ? 1 : 0.8f, 0.5f);

											if (setting->value->_bool) {
												DrawUtils::setColor(255, 255, 255, 1);
												boxPos.x += textPadding;
												boxPos.y += textPadding;
												boxPos.z -= textPadding;
												boxPos.w -= textPadding;
												DrawUtils::drawLine(vec2(boxPos.x, boxPos.y), vec2(boxPos.z, boxPos.w), 0.5f);
												DrawUtils::drawLine(vec2(boxPos.z, boxPos.y), vec2(boxPos.x, boxPos.w), 0.5f);
											}
										}
									}
								}
								textPos.x += textHeight + (textPadding * 2);
								// Text
								if (partner->Partnered.selected == 1) {
									// Convert first letter to uppercase for more friendlieness
									char name[0x21];
									sprintf_s(name, 0x21, "%s", setting->name);
									if (name[0] != 0)
										name[0] = toupper(name[0]);

									std::string elTexto = name;
									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 10 /* because we add 10 to text padding + checkbox*/);
									DrawUtils::drawText(textPos, &elTexto, isFocused ? MC_Color(1.0f, 1.0f, 1.0f) : MC_Color(0.8f, 0.8f, 0.8f), textSize);
									currentYOffset += textHeight + (textPadding * 2);

								} else {
									if (partner->Partnered.selected == 0) {
										// Convert first letter to uppercase for more friendlieness
										char name[0x21];
										sprintf_s(name, 0x21, "%s", setting->name);
										if (name[0] != 0)
											name[0] = toupper(name[0]);

										std::string elTexto = name;
										windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 10 /* because we add 10 to text padding + checkbox*/);
										DrawUtils::drawText(textPos, &elTexto, isFocused ? MC_Color(1.0f, 1.0f, 1.0f) : MC_Color(0.8f, 0.8f, 0.8f), textSize);
										currentYOffset += textHeight + (textPadding * 2);
									} else {
										if (partner->Partnered.selected == 2) {
											// Convert first letter to uppercase for more friendlieness
											char name[0x21];
											sprintf_s(name, 0x21, "%s", setting->name);
											if (name[0] != 0)
												name[0] = toupper(name[0]);

											std::string elTexto = name;
											windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 10 /* because we add 10 to text padding + checkbox*/);
											DrawUtils::drawText(textPos, &elTexto, isFocused ? MC_Color(1.0f, 1.0f, 1.0f) : MC_Color(0.8f, 0.8f, 0.8f), textSize);
											currentYOffset += textHeight + (textPadding * 2);
										} else {
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
									}
								}
								break;
							}
							case ValueType::ENUM: {  // Click setting
								// Text and background
								static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
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
									DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
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

								windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5.f);  // because we add 5 to text padding
								textPos.y = currentYOffset + textPadding - 1;
								vec4 selectableSurface = vec4(textPos.x, rectPos.y, xEnd, rectPos.w);
								MC_Color col;

								if (setting->value->_int == e || (selectableSurface.contains(&mousePos) && !ourWindow->isInAnimation)) {
									if (isEven)
										col = selectedSettingColor1;
									else
										col = selectedSettingColor2;
								} else {
									if (isEven)
										col = selectedSettingColor1;
									else
										col = selectedSettingColor2;
								}
								DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
								DrawUtils::drawText(textPos, &elTexto, MC_Color(1.f, 1.f, 1.f));
								// logic
								selectableSurface.y = settingStart;
								if (!ourWindow->isInAnimation && selectableSurface.contains(&mousePos)) {
									if (shouldToggleLeftClick) {
										shouldToggleLeftClick = false;
										((SettingEnum*)setting->extraData)->SelectNextValue(false);
									} else if (shouldToggleRightClick) {
										shouldToggleRightClick = false;
										((SettingEnum*)setting->extraData)->SelectNextValue(true);
									}
								}
								currentYOffset += textHeight + (textPadding * 2);

								break;
							}
							case ValueType::FLOAT: {
								static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
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
									DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
								}

								if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
									overflowing = true;
									break;
								}
								// Slider
								{
									vec4 rect = vec4(
										currentXOffset + textPadding + 5,
										currentYOffset + textPadding,
										xEnd - textPadding,
										currentYOffset - textPadding + textHeight);

									// Visuals & Logic
									{
										rectPos.y = currentYOffset;
										rectPos.w += textHeight + (textPadding * 2);
										// Background
										const bool areWeFocused = rect.contains(&mousePos);

										DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);  // Background
										DrawUtils::drawRectangle(rect, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);     // Slider background

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
											vec2 mid = vec2(
												rect.x + ((rect.z - rect.x) / 2),
												rect.y - 0.2f);
											char str[10];
											sprintf_s(str, 10, "%.2f", setting->value->_float);
											std::string text = str;
											mid.x -= DrawUtils::getTextWidth(&text, textSize) / 2;

											DrawUtils::drawText(mid, &text, MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), textSize);
										}

										// Draw Progress
										{
											rect.z = rect.x + value;
											DrawUtils::fillRectangle(rect, MC_Color(0, 0, 0), (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
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
									currentYOffset += textHeight + (textPadding * 2);
								}
							} break;
							case ValueType::INT: {
								static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
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
									DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
								}
								if ((currentYOffset - ourWindow->pos.y) > (g_Data.getGuiData()->heightGame * 0.75)) {
									overflowing = true;
									break;
								}
								// Slider
								{
									vec4 rect = vec4(
										currentXOffset + textPadding + 5,
										currentYOffset + textPadding,
										xEnd - textPadding,
										currentYOffset - textPadding + textHeight);

									// Visuals & Logic
									{
										rectPos.y = currentYOffset;
										rectPos.w += textHeight + (textPadding * 2);
										// Background
										const bool areWeFocused = rect.contains(&mousePos);

										DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);  // Background
										DrawUtils::drawRectangle(rect, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);     // Slider background
										DrawUtils::drawRectangle(rect, ClickGui::renderCategory ? MC_Color() : MC_Color(currColor), 1.f);

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
											vec2 mid = vec2(
												rect.x + ((rect.z - rect.x) / 2),
												rect.y - 0.2f  // Hardcoded ghetto
											);
											char str[10];
											sprintf_s(str, 10, "%i", setting->value->_int);
											std::string text = str;
											mid.x -= DrawUtils::getTextWidth(&text, textSize) / 1;

											DrawUtils::drawText(mid, &text, MC_Color(ClickGuiMod::tfrcolor, ClickGuiMod::tfgcolor, ClickGuiMod::tfbcolor), textSize);
										}

										// Draw Progress
										{
											rect.z = rect.x + value;
											DrawUtils::fillRectangle(rect, MC_Color(0, 0, 0), (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
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
									currentYOffset += textHeight + (textPadding * 2);
								}
							} break;
							case ValueType::SPACE: {
								static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
								// Text and background
								{
									// Convert first letter to uppercase for more friendlieness
									char name[0x22];
									sprintf_s(name, "%s", setting->name);
									if (name[0] != 0)
										name[0] = toupper(name[0]);

									std::string elTexto = name;
									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 /* because we add 5 to text padding*/);
									currentYOffset += textPadding + textHeight;
									rectPos.w = currentYOffset;
									DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);
									rectPos.z -= 1.f;
									rectPos.x = textPos.x;
									DrawUtils::drawTopAndBottomRectangle(rectPos, MC_Color(255, 255, 255), 1.f);
									textPos.y -= 0.95f;
									// to center the text, do textPos.x = the middle of textPos.x
									DrawUtils::drawText(textPos, &elTexto, MC_Color(1.0f, 1.0f, 1.0f), textSize);
								}

								break;
							}
							default: {
								char alc[100];
								sprintf_s(alc, 100, "Not implemented (%s)", setting->name);
								std::string elTexto = alc;
								// Adjust window size if our text is too  t h i c c
								windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 3 /* because we add 5 to text padding*/);

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
							DrawUtils::drawLine(vec2(currentXOffset + 2, startYOffset), vec2(currentXOffset + 2, endYOffset), 0.5f);
						}
					}
				} else
					currentYOffset += textHeight + (textPadding * 2);
			}
		}

		vec4 winRectPos = vec4(
			xOffset,
			yOffset,
			xEnd,
			currentYOffset);

		if (winRectPos.contains(&mousePos)) {
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
		vec2 textPos = vec2(
			currentXOffset + textPadding,
			categoryHeaderYOffset + textPadding);
		vec4 rectPos = vec4(
			currentXOffset - categoryMargin,
			categoryHeaderYOffset - categoryMargin,
			currentXOffset + windowSize->x + paddingRight + categoryMargin,
			categoryHeaderYOffset + textHeight + (textPadding * 2));

		// Extend Logic
		// ANIMATION
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
					vec2 diff = vec2(mousePos).sub(dragStart);
					ourWindow->pos = ourWindow->pos.add(diff);
					dragStart = mousePos;
				} else {  // Stopped dragging
					isDragging = false;
				}
			} else if (rectPos.contains(&mousePos) && shouldToggleLeftClick) {
				isDragging = true;
				draggedWindow = Utils::getCrcHash(categoryName);
				shouldToggleLeftClick = false;
				dragStart = mousePos;
			}
		}
		static auto partner = moduleMgr->getModule<Partner>();
		// Draw component
		if (partner->Partnered.selected == 1) {
			{
				// Draw Text
				std::string textStr = categoryName;
				static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
				if (ClickguiOpac->RGB) {
					DrawUtils::drawText(textPos, &textStr, MC_Color(currColor), textSize);
				} else {
					DrawUtils::drawText(textPos, &textStr, MC_Color(150, 30, 255), textSize);
				}
				DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);

				DrawUtils::fillRectangle(vec4(rectPos.x, rectPos.w - 1, rectPos.z, rectPos.w), MC_Color(150, 30, 255), 1 - ourWindow->animation);
				// Draw Dash
				GuiUtils::drawCrossLine(vec2(
											currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
											categoryHeaderYOffset + textPadding + (textHeight / 2)),
										MC_Color(150, 30, 255), crossWidth, crossSize, !ourWindow->isExtended);
			}
		} else {
			if (partner->Partnered.selected == 0) {
				{
					// Draw Text
					std::string textStr = categoryName;
					static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
					if (ClickguiOpac->RGB) {
						DrawUtils::drawText(textPos, &textStr, MC_Color(currColor), textSize);
					} else {
						DrawUtils::drawText(textPos, &textStr, MC_Color(0, 0, 255), textSize);
					}
					DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);

					DrawUtils::fillRectangle(vec4(rectPos.x, rectPos.w - 1, rectPos.z, rectPos.w), MC_Color(0, 0, 255), 1 - ourWindow->animation);
					// Draw Dash
					GuiUtils::drawCrossLine(vec2(
												currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
												categoryHeaderYOffset + textPadding + (textHeight / 2)),
											MC_Color(0, 0, 255), crossWidth, crossSize, !ourWindow->isExtended);
				}
			} else {
				if (partner->Partnered.selected == 2) {
					// Draw Text
					std::string textStr = categoryName;
					static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
					if (ClickguiOpac->RGB) {
						DrawUtils::drawText(textPos, &textStr, MC_Color(currColor), textSize);
					} else {
						DrawUtils::drawText(textPos, &textStr, MC_Color(184, 0, 255), textSize);
					}
					DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);

					DrawUtils::fillRectangle(vec4(rectPos.x, rectPos.w - 1, rectPos.z, rectPos.w), selectedModuleColor, 1 - ourWindow->animation);
					// Draw Dash
					GuiUtils::drawCrossLine(vec2(
												currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
												categoryHeaderYOffset + textPadding + (textHeight / 2)),
											MC_Color(184, 0, 255), crossWidth, crossSize, !ourWindow->isExtended);
				} else {
					// Draw Text
					std::string textStr = categoryName;
					static auto ClickguiOpac = moduleMgr->getModule<ClickGuiMod>();
					if (ClickguiOpac->RGB) {
						DrawUtils::drawText(textPos, &textStr, MC_Color(currColor), textSize);
					} else {
						DrawUtils::drawText(textPos, &textStr, MC_Color(184, 0, 255), textSize);
					}
					DrawUtils::fillRectangle(rectPos, MC_Color(ClickGuiMod::rcolor, ClickGuiMod::gcolor, ClickGuiMod::bcolor), ClickguiOpac->opacity);

					DrawUtils::fillRectangle(vec4(rectPos.x, rectPos.w - 1, rectPos.z, rectPos.w), selectedModuleColor, 1 - ourWindow->animation);
					// Draw Dash
					GuiUtils::drawCrossLine(vec2(
												currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f,
												categoryHeaderYOffset + textPadding + (textHeight / 2)),
											MC_Color(184, 0, 255), crossWidth, crossSize, !ourWindow->isExtended);
				}
			}
		}
	}

	// anti idiot
	{
		vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;

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

	if (timesRendered < 10)
		timesRendered++;

	// Fill Background
	{
		DrawUtils::fillRectangle(vec4(
									 0,
									 0,
									 g_Data.getClientInstance()->getGuiData()->widthGame,
									 g_Data.getClientInstance()->getGuiData()->heightGame),
								 MC_Color(0, 0, 0), 0.2f);
	}

	renderCategory(Category::COMBAT);
	renderCategory(Category::VISUAL);
	renderCategory(Category::MOVEMENT);
	renderCategory(Category::PLAYER);
	renderCategory(Category::WORLD);
	renderCategory(Category::GUI);
	renderCategory(Category::FLYS);
	renderCategory(Category::SERVER);
	renderCategory(Category::CONFIG);
	renderCategory(Category::ENTITY);
	renderCategory(Category::PARTNER);

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
		if (key == clickGuiMod->getKey())
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
		for (int i = 0; i <= (int)Category::SERVER /*last category*/; i++) {
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
