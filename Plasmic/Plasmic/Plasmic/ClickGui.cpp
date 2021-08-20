#include "ClickGui.h"
#include "../Utils/Logger.h"

#include "Manager.h"
#include <cmath>
#include "../Utils/Image.h"


#define gdebug 0

typedef void(*_mrelease)(MinecraftGame* minecraftgaming);
typedef void(*_mcapture)(MinecraftGame* minecraftgaming);

_mrelease releaseMouse;
_mcapture captureMouse;


bool isFading = true;
std::chrono::high_resolution_clock fadeClock;
auto openedAt = fadeClock.now();


void correctValue(int& current, int min, int max) {
	if (current < min)
		current = min;
	else if (current > max)
		current = max;
}
void correctValue(float& current, float min, float max) {
	if (current < min)
		current = min;
	else if (current > max)
		current = max;
}








#pragma region Notification

static MC_Color notificationBackgroundColor(0.176470f, 0.176470f, 0.176470f);
#define notificationBackgroundOpacity 0.85f
static MC_Color notificationTextColor(1.f, 1.f, 1.f);
#define notificationTextOpacity 1.f

#define NotificationDuration 2.f 
#define NotificationOpenTime 0.5f

std::chrono::high_resolution_clock notificationClock;
auto notificationStart = notificationClock.now();


int8_t notificationStage;
float notificationAnimation = 0.f;
char notificationText[256];
float notificationtw = 0.f;
float twdp2 = 0.f;
float notificationHalfwindow = 0.f;

void ClickGui::sendNotificationf(const char* format, ...) {
	if (!game::clientinstance) 
		return;
	
	va_list argsptr;
	va_start(argsptr, format);
	vsprintf_s(notificationText, 256, format, argsptr);

	notificationHalfwindow = game::clientinstance->guiData->windowSizeScaled.x / 2.f;
	notificationStart = notificationClock.now();
	notificationStage = 1;
}

//Image logo("logo.plasmicimg");
void ClickGui::notificationRenderer() {
	//logo.DrawImage(Vec2(50.f, 50.f), Vec2(32.f, 32.f), 1.f);

	//RenderUtils::RenderText(game::currentScreen, Vec2(0.f, 60.f), MC_Color(0.f, 1.f, 0.f), 1.f, 1.f);
	if (notificationStage == 0 || uiHidden)
		return;

	if (notificationStage == 1) {
		notificationtw = RenderUtils::GetTextWidth(notificationText, 1.f);
		twdp2 = notificationtw / 2.f;
		notificationStage = 2;
	}

	if (notificationStage == 2) {
		notificationAnimation = std::chrono::duration<float>(notificationClock.now() - notificationStart).count() / NotificationOpenTime;
		if (notificationAnimation > 1.f) {
			notificationAnimation = 1.f;
			notificationStart = notificationClock.now();
			notificationStage = 3;
		}

	}
	if (notificationStage == 3) {
		if (std::chrono::duration<float>(notificationClock.now() - notificationStart).count() > NotificationDuration) {
			notificationStart = notificationClock.now();
			notificationStage = 4;
		}
	}
	if (notificationStage == 4) {
		notificationAnimation = 1.f - (std::chrono::duration<float>(notificationClock.now() - notificationStart).count() / NotificationOpenTime);
		if (notificationAnimation < 0) {
			notificationStage = 0;
			return;
		}
	}


	Rect notifRect((notificationHalfwindow - twdp2) - 4.f, 10.f * notificationAnimation, notificationHalfwindow + twdp2 + 4.f, (10.f * notificationAnimation) + 15.f);
	RenderUtils::FillRectangle(notifRect, notificationBackgroundColor, notificationBackgroundOpacity * notificationAnimation);
	RenderUtils::RenderText(notificationText, Vec2(notifRect.x + 4.f, notifRect.y + 3.f), notificationTextColor, 1.f, notificationTextOpacity * notificationAnimation);

	//to align text
	//yes
	//wasting cpu cycles doing that
	//makes it align the text
	//idk either.....
	char gdsgfda[14];
	sprintf(gdsgfda, "%f", notifRect.y);
//	RenderUtils::RenderText(gdsgfda, Vec2(notifRect.x + 4.f, notifRect.y + 10.f), notificationTextColor, 1.f, notificationTextOpacity * notificationAnimation);

	RenderUtils::FlushText();
	RenderUtils::DrawRectangle(notifRect, notificationTextColor, notificationTextOpacity * notificationAnimation, 1.f);
}
#pragma endregion

#pragma region Init
bool MinecraftiaSetting = false;
void OnMinecraftia(Setting* s) {
	RenderUtils::SetFont(*s->vbool);
}

bool skipNextLazyness = false;
bool skipTwoLazyness = false;
bool LazyGuiRedraw = false;
void OnLazyGuiRedraw(Setting* s) {
	if (*s->vbool == true) {
		game::sendClientChat(mltext("Enable the \"skipNextLazyness\" setting until the minecraft GUI is above plasmic.\nThen enable the \"skipNextLazyness\" setting twice.\nYou now have the optimal lazyRedraw settings!", "Activer l'option \"skipNextLazyness\" jusqu'a ce que l'interface minecraft soit par dessu celle de plasmic\nActiver l'option \"skipNextLazyness\" deux fois apres.\nVous avez desormais les meilleur parametres LazyGuiRedraw!"));
		ClickGui::sendNotificationf(mltext("Warning, it may cause flickers/flashing images if you have screen animations.", "Attention, ce reglage peut causer des flickers / images qui flash si vous avez les animations a l'ecran."));
	}
	//skipTwoLazyness = true;
	//skipNextLazyness = true;
}

bool DisableClickguiSnapping = false;

ClickGui::ClickGui() {
#ifndef _1_16_40
	releaseMouse = (_mrelease)mem::FindSignature("40 53 48 83 EC 40 48 8B D9 80 B9 ?? ?? ?? ?? 00 0F 85 ?? ?? ?? ?? 48 8B 91 ?? ?? ?? ?? 48 8B 42 08 48 8B CA 80 78 19 00 75 12");
	if (releaseMouse == nullptr)
		Logger::log("sig ClickGui captureMouse is broken");


	captureMouse = (_mcapture)mem::FindSignature("40 53 48 83 EC 40 48 8B D9 80 B9 ?? ?? ?? ?? 00 0F 84 ?? ?? ?? ?? 48 8B 91 ?? ?? ?? ?? 48 8B 42 08 48 8B CA 80 78 19 00 75 12");
	if (captureMouse == nullptr)
		Logger::log("sig ClickGui captureMouse is broken");


#else
	releaseMouse = (_mrelease)mem::FindSignature("40 53 48 83 EC 40 48 C7 44 24 20 ?? ?? ?? ?? 48 8B D9 80 B9 ?? ?? ?? ?? 00 75 66 48 8B 91 ?? ?? ?? ?? 48 8B 42 08 80 78 19 00");
	if (releaseMouse == nullptr)
		Logger::log("sig ClickGui captureMouse is broken");

	captureMouse = (_mcapture)mem::FindSignature("40 53 48 83 EC 40 48 C7 44 24 20 ?? ?? ?? ?? 48 8B D9 80 B9 ?? ?? ?? ?? 00 0F 84 ?? ?? ?? ?? 48 8B 91");
	if (captureMouse == nullptr)
		Logger::log("sig ClickGui captureMouse is broken");
#endif


	//Create a module to make it have the options,
	//its easier like that because all the code is already
	//made we can just add the settings there :)


	clickguiModule = &ModuleManager::GetClickGuiModule;
	ModuleManager::GetClickGuiModule.addKeybindSetting(mltext("Clickgui key", "Touche pour ouvrir l'interface"), "ClickGuiKey", key, &key, true);
	ModuleManager::GetClickGuiModule.addBoolSetting(mltext("Minecraftia font", "Police d'ecriture Minecraftia"), "IsMinecraftia", MinecraftiaSetting, &MinecraftiaSetting, true, (uintptr_t)OnMinecraftia);
	ModuleManager::GetClickGuiModule.addBoolSetting(mltext("Disable Module Snapping", "Desactiver la liaisons des mods"), "DisableClickguiSnapping", DisableClickguiSnapping, &DisableClickguiSnapping, true);
	ModuleManager::GetClickGuiModule.addBoolSetting(mltext("LazyGuiRedraw (fps+ for plasmic ui)", "LazyGuiRedraw (fps+ pour plasmic UI)"), "LazyGuiRedraw", LazyGuiRedraw, &LazyGuiRedraw, true, (uintptr_t)OnLazyGuiRedraw);
	ModuleManager::GetClickGuiModule.addBoolSetting("skipNextLazyness", "skipNextLazyness", skipNextLazyness, &skipNextLazyness, true);

	
	//Image::DeInitImages();
}
#pragma endregion


#pragma region EnableDisable

bool waitingKey = false;
uint16_t selectedKey = 0;

bool isInModuleSettings = false;
Module* selectedModule = nullptr;
VisualModule* selectedVisualModule = nullptr;
ClickguiColor* selectedColor = nullptr;

void ClickGui::onEnable() {
	isFading = true;
	openedAt = fadeClock.now();

	//if (!strcmp(game::currentScreen, "hud_screen"))
		captureMouse(game::minecraftGame);
}

bool IsEject = false;
void ClickGui::onDisable() {
		if (!strcmp(game::currentScreen, "hud_screen"))
			releaseMouse(game::minecraftGame);

	//remove selected ability
	if (selectedModule != nullptr) {
		for (uint8_t i = 0; i < selectedModule->settings.size(); i++)
			selectedModule->settings[i].closeClickgui();
	}
	else if (selectedVisualModule != nullptr) {
		for (uint8_t i = 0; i < selectedVisualModule->settings.size(); i++)
			selectedVisualModule->settings[i].closeClickgui();
	}

	isInModuleSettings = false;
	waitingKey = false;

	selectedModule = nullptr;
	selectedVisualModule = nullptr;
	selectedColor = nullptr;

	isFading = false;

	if (!IsEject)
		Config::save(mltext("Default", "Defaut"));
}
#pragma endregion



void ClickGui::onEject() {
	IsEject = true;
	if (enabled)
		onDisable();
}
bool ClickGui::shouldRenderVisualModules() {
	if (enabled && !isInModuleSettings)
		return true;
	if (!enabled && uiHidden)
		return false;

	return game::minecraftGame->canMoveCamera;
}




//its not a real blur but yeah idk how to call this
static MC_Color blurColor(0.176470f, 0.176470f, 0.176470f);
#define blurOpacity 0.4f
static MC_Color backgroundColor(0.1f, 0.1f, 0.1f);
#define CLICKGUI_SETTINGS_OPACITY 0.4f

static MC_Color enabledModuleColor(0.f, 0.69f, 0.1f);
static MC_Color disabledModuleColor(0.69f, 0.1f, 0.1f);

static MC_Color moduleSettingsButtonColor(1.0f, 0.0f, 0.f);
static MC_Color sliderColor(0.f, 0.6f, 1.f);

static MC_Color visualModuleBackColor(0.2f, 0.2f, 0.2f);
#define visualModuleBackOpacity 0.25f
static MC_Color hoverColor(0.8f, 0.8f, 0.8f);
#define hoverOpacity 0.45f

static MC_Color textColor(1.f, 1.f, 1.f);



#pragma region InputHandling

void ClickGui::onKey(uint16_t key, bool isDown, bool& cancel) {
	if (!waitingKey)
	if ((key == VK_ESCAPE || key == this->key || key == VK_INSERT) && isDown) {
		cancel = true;
		this->Disable();
	}
	if (waitingKey) {
		waitingKey = false;
		selectedKey = key;
	}


	cancel = true;
}


bool didClick = false;
bool ismousedownrn = false;
MouseButton clickedButton = MouseButton::MOUSE_MOVE;
int8_t scrollCount = 0;
void ClickGui::onMouse(MouseButton button, bool isDown, bool& cancel) {
	if (waitingKey) {
		cancel = true;
		return;
	}

	if (button == MouseButton::LEFT) {
		ismousedownrn = isDown;
		if (!isDown) 
			if (selectedModule != nullptr) {
				for (uint8_t i = 0; i < selectedModule->settings.size(); i++)
					selectedModule->settings[i].selected = false;
			} else if (selectedVisualModule != nullptr) {
				for (uint8_t i = 0; i < selectedVisualModule->settings.size(); i++)
					selectedVisualModule->settings[i].selected = false;
			}
	}


	if (isDown)
		didClick = true;

	clickedButton = button;
	if (clickedButton == MouseButton::SCROLL) {
		didClick = true;
		if (isDown)
			scrollCount--;
		else
			scrollCount++;
	}


	cancel = true;
}
#pragma endregion

static float mx = 0.f;
static float my = 0.f;
static float wx = 0.f;
static float wy = 0.f;


Rect ModuleRect;
Rect ModuleSettingsRect;
float TextHeight_2 = 0.f;
float TextHeight_1 = 0.f;


void ClickGui::onRender() {


	//preparation
	GuiData* g = game::clientinstance->guiData;
	mx = (g->windowSizeScaled.x * g->mouseX) / g->windowSizeReal.x;
	my = (g->windowSizeScaled.y * g->mouseY) / g->windowSizeReal.y;
	wx = g->windowSizeScaled.x;
	wy = g->windowSizeScaled.y;


	//background
	RenderUtils::FillRectangle(Rect(0, 0, wx, wy), blurColor, blurOpacity);
	TextHeight_1 = RenderUtils::GetTextWidth("W", 1.2f);
	TextHeight_2 = RenderUtils::GetTextWidth("W", 2.2f);

	float TextWidth = 0.f;





#pragma region ColorPicker
	if (selectedColor != nullptr) {

	Rect WindowRect(wx / 10.f, wy / 10.f, wx - wx / 10.f, wy - wy / 10.f);
	RenderUtils::FillRectangle(WindowRect, backgroundColor, 1.f);
	float panel2start = ((WindowRect.x + WindowRect.z) / 3.f) * 2.f;

#define GetCenterTextPos(rectangle, text, textSize) ((((rectangle.z - rectangle.x) / 2.f) - (RenderUtils::GetTextWidth(text, textSize) / 2.f)) + rectangle.x)






		//Color presets
		float ColorPresetSquaresSizeX = (panel2start - WindowRect.x) / 8.f;
		float ColorPresetSquaresSizeY = (35.f * (WindowRect.w - WindowRect.y)) / 210.2f;//35.f;
		Rect presetSquare(WindowRect.x, WindowRect.y, WindowRect.x + ColorPresetSquaresSizeX, WindowRect.y + ColorPresetSquaresSizeY);

		{
		bool UselessBoolBecauseIMakeDumbFunctionsWithWeirdParameters = false;
		Rect HighlightRect(-1.f, -1.f, -1.f, -1.f);
		MC_Color HighlightRectColor;
		for (int8_t i = 0; i < 8; i++) {
			RenderUtils::FillRectangle(presetSquare, ClickguiColor::getPreset(i, UselessBoolBecauseIMakeDumbFunctionsWithWeirdParameters), 1.f);

			if (presetSquare.isInside(mx, my)) {
				HighlightRect = presetSquare;
				HighlightRectColor = ClickguiColor::getPreset(i, UselessBoolBecauseIMakeDumbFunctionsWithWeirdParameters);
				if (didClick && clickedButton == MouseButton::LEFT)
					selectedColor->selectPreset(i);
			}
			presetSquare.x = presetSquare.z;
			presetSquare.z += ColorPresetSquaresSizeX;
		}
		presetSquare.x = WindowRect.x;
		presetSquare.z = presetSquare.x + ColorPresetSquaresSizeX;
		presetSquare.y = presetSquare.w;
		presetSquare.w += ColorPresetSquaresSizeY;
		for (int8_t i = 8; i < 16; i++) {
			RenderUtils::FillRectangle(presetSquare, ClickguiColor::getPreset(i, UselessBoolBecauseIMakeDumbFunctionsWithWeirdParameters), 1.f);

			if (presetSquare.isInside(mx, my)) {
				HighlightRect = presetSquare;
				HighlightRectColor = ClickguiColor::getPreset(i, UselessBoolBecauseIMakeDumbFunctionsWithWeirdParameters);
				if (didClick && clickedButton == MouseButton::LEFT)
					selectedColor->selectPreset(i);
			}
			presetSquare.x = presetSquare.z;
			presetSquare.z += ColorPresetSquaresSizeX;
		}
		RenderUtils::FillRectangle(Rect(WindowRect.x, presetSquare.w, WindowRect.z, presetSquare.w + 0.5f), textColor, 1.f);
		if (HighlightRect.x > -1.f)
			RenderUtils::DrawRectangle(HighlightRect, HighlightRectColor, 1.f, 3.f);
	}




		
		float height = presetSquare.w + 20.f;
		Rect intRect(WindowRect.x + 5.f, height, (panel2start - WindowRect.x) + WindowRect.x - 20.f, height + 2.f);
		static uint8_t selectedSlider = 0;
		if (!ismousedownrn) //reset slider selection
			selectedSlider = 0; 

		//red
		//red
		{
			RenderUtils::RenderText(mltext("Red", "Rouge"), Vec2(intRect.x, height - 14.f), textColor, 1.f, 1.f);
			RenderUtils::FillRectangle(intRect, sliderColor, 1.f);
			intRect.y -= 3.0f; intRect.w += 2.5f; //make the clickable area fatter

			float sliderPos = ((intRect.z - intRect.x) * selectedColor->color.r) + intRect.x;
			Rect SliderRect(sliderPos - 2.5f, intRect.y, sliderPos + 3.0f, intRect.w);

			
			//color scrolling support;
			if (intRect.isInside(mx, my) && didClick)
				if (clickedButton == MouseButton::SCROLL) 
					selectedColor->color.r += scrollCount / 255.f;
			correctValue(selectedColor->color.r, 0.f, 1.f);

			if (ismousedownrn && (intRect.isInside(mx, my) && selectedSlider == 0) || selectedSlider == 1) {
				selectedSlider = 1;//if the user leave but don't release the mouse, we don't want him to lose his slider...
				float vx = mx, vy = my;	//out of bounds support
				if (mx < intRect.x) vx = intRect.x; if (my < intRect.y) vy = intRect.y; if (mx > intRect.z) vx = intRect.z; if (my > intRect.w) vy = intRect.w;

				selectedColor->color.r = (vx - intRect.x) / (intRect.z - intRect.x);

				SliderRect = Rect(vx - 2.5f, intRect.y, vx + 2.5f, intRect.w);
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
				RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
			}
			else
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

			//Display value
			char value[11] = { 0 };
			sprintf(value, "%i", (int)(selectedColor->color.r * 255.f));
			RenderUtils::RenderText(value, Vec2(intRect.z + 5.f, intRect.y - 1.35f), textColor, 1.f, 1.f);

		}

		//blue
		//blue
		height += ColorPresetSquaresSizeY;
		intRect.y = height;
		intRect.w = height + 2.f;
		{
			RenderUtils::RenderText(mltext("Blue", "Bleu"), Vec2(intRect.x, height - 14.f), textColor, 1.f, 1.f);
			RenderUtils::FillRectangle(intRect, sliderColor, 1.f);
			intRect.y -= 3.0f; intRect.w += 2.5f; //make the clickable area fatter

			float sliderPos = ((intRect.z - intRect.x) * selectedColor->color.b) + intRect.x;
			Rect SliderRect(sliderPos - 2.5f, intRect.y, sliderPos + 3.0f, intRect.w);

			
			//color scrolling support;
			if (intRect.isInside(mx, my) && didClick)
				if (clickedButton == MouseButton::SCROLL) 
					selectedColor->color.b += scrollCount / 255.f;
			correctValue(selectedColor->color.b, 0.f, 1.f);

			if (ismousedownrn && (intRect.isInside(mx, my) && selectedSlider == 0) || selectedSlider == 2) {
				selectedSlider = 2;//if the user leave but don't release the mouse, we don't want him to lose his slider...
				float vx = mx, vy = my;	//out of bounds support
				if (mx < intRect.x) vx = intRect.x; if (my < intRect.y) vy = intRect.y; if (mx > intRect.z) vx = intRect.z; if (my > intRect.w) vy = intRect.w;

				selectedColor->color.b = (vx - intRect.x) / (intRect.z - intRect.x);

				SliderRect = Rect(vx - 2.5f, intRect.y, vx + 2.5f, intRect.w);
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
				RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
			}
			else
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

			//Display value
			char value[11] = { 0 };
			sprintf(value, "%i", (int)(selectedColor->color.b * 255.f));
			RenderUtils::RenderText(value, Vec2(intRect.z + 5.f, intRect.y - 1.35f), textColor, 1.f, 1.f);

		}

		//green
		//green
		height += ColorPresetSquaresSizeY;
		intRect.y = height;
		intRect.w = height + 2.f;
		{
			RenderUtils::RenderText(mltext("Green", "Vert"), Vec2(intRect.x, height - 14.f), textColor, 1.f, 1.f);
			RenderUtils::FillRectangle(intRect, sliderColor, 1.f);
			intRect.y -= 3.0f; intRect.w += 2.5f; //make the clickable area fatter

			float sliderPos = ((intRect.z - intRect.x) * selectedColor->color.g) + intRect.x;
			Rect SliderRect(sliderPos - 2.5f, intRect.y, sliderPos + 3.0f, intRect.w);

			
			//color scrolling support;
			if (intRect.isInside(mx, my) && didClick)
				if (clickedButton == MouseButton::SCROLL) 
					selectedColor->color.g += scrollCount / 255.f;
			correctValue(selectedColor->color.g, 0.f, 1.f);

			if (ismousedownrn && (intRect.isInside(mx, my) && selectedSlider == 0) || selectedSlider == 3) {
				selectedSlider = 3;//if the user leave but don't release the mouse, we don't want him to lose his slider...
				float vx = mx, vy = my;	//out of bounds support
				if (mx < intRect.x) vx = intRect.x; if (my < intRect.y) vy = intRect.y; if (mx > intRect.z) vx = intRect.z; if (my > intRect.w) vy = intRect.w;

				selectedColor->color.g = (vx - intRect.x) / (intRect.z - intRect.x);

				SliderRect = Rect(vx - 2.5f, intRect.y, vx + 2.5f, intRect.w);
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
				RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
			}
			else
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

			//Display value
			char value[11] = { 0 };
			sprintf(value, "%i", (int)(selectedColor->color.g * 255.f));
			RenderUtils::RenderText(value, Vec2(intRect.z + 5.f, intRect.y - 1.35f), textColor, 1.f, 1.f);

		}

		//alpha
		//alpha
		if (selectedColor->showAlpha) {
			height += ColorPresetSquaresSizeY;
			intRect.y = height;
			intRect.w = height + 2.f;
			{
				RenderUtils::RenderText(mltext("Opacity", "Opacite"), Vec2(intRect.x, height - 14.f), textColor, 1.f, 1.f);
				RenderUtils::FillRectangle(intRect, sliderColor, 1.f);
				intRect.y -= 3.0f; intRect.w += 2.5f; //make the clickable area fatter

				float sliderPos = ((intRect.z - intRect.x) * selectedColor->opacity) + intRect.x;
				Rect SliderRect(sliderPos - 2.5f, intRect.y, sliderPos + 3.0f, intRect.w);


				//color scrolling support;
				if (intRect.isInside(mx, my) && didClick)
					if (clickedButton == MouseButton::SCROLL)
						selectedColor->opacity += scrollCount / 255.f;
				correctValue(selectedColor->opacity, 0.f, 1.f);

				if (ismousedownrn && (intRect.isInside(mx, my) && selectedSlider == 0) || selectedSlider == 4) {
					selectedSlider = 4;//if the user leave but don't release the mouse, we don't want him to lose his slider...
					float vx = mx, vy = my;	//out of bounds support
					if (mx < intRect.x) vx = intRect.x; if (my < intRect.y) vy = intRect.y; if (mx > intRect.z) vx = intRect.z; if (my > intRect.w) vy = intRect.w;

					selectedColor->opacity = (vx - intRect.x) / (intRect.z - intRect.x);

					SliderRect = Rect(vx - 2.5f, intRect.y, vx + 2.5f, intRect.w);
					RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
					RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
				}
				else
					RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

				//Display value
				char value[11] = { 0 };
				sprintf(value, "%i", (int)(selectedColor->opacity * 255.f));
				RenderUtils::RenderText(value, Vec2(intRect.z + 5.f, intRect.y - 1.35f), textColor, 1.f, 1.f);

			}
		}








		//Color ID for Color code
		//Color ID for Color code
		for (uint16_t i = 0; i < ClickguiColor::colors.size(); i++)
			if (ClickguiColor::colors[i] == selectedColor) {
				char txt[14];
				sprintf(txt, "Color ID: %i", i);
				RenderUtils::RenderText(txt, Vec2(panel2start + 8.f, presetSquare.w + 5.f), textColor, 0.8f, 1.f);
				break;
			}


		//isRGB
		//isRGB
		height = presetSquare.w + ColorPresetSquaresSizeY/2.f;
		RenderUtils::RenderText("Rainbow", Vec2(panel2start + 8.f, height), textColor, 1.f, 1.f);
		Rect boolRect(WindowRect.z - 15.f, height, WindowRect.z - 5.f, height + 10.f);
		RenderUtils::FillRectangle(boolRect, selectedColor->isRGB ? enabledModuleColor : disabledModuleColor, 1.f);
		if (boolRect.isInside(mx, my)) {
			RenderUtils::FillRectangle(boolRect, hoverColor, hoverOpacity);
			if (didClick && clickedButton == MouseButton::LEFT) {
				selectedColor->isRGB = !selectedColor->isRGB;
				if (selectedColor->isRGB) {
					selectedColor->color.r = 1.f;
					selectedColor->color.b = 0.f;
					selectedColor->color.g = 0.f;
				}
			}
		}


		
		//brightness
		//brightness
		height += ColorPresetSquaresSizeY;
		intRect.y = height;
		intRect.w = height + 2.f;
		intRect.x = panel2start + 8.f;
		intRect.z = WindowRect.z - 20.f;
		{ //more like float rect now but ima use the same rect
			RenderUtils::RenderText(mltext("Brightness", "Luminosite"), Vec2(intRect.x, height - 14.f), textColor, 1.f, 1.f);
			RenderUtils::FillRectangle(intRect, sliderColor, 1.f);
			intRect.y -= 3.0f; intRect.w += 2.5f; //make the clickable area fatter

			
			float sliderPos = (((selectedColor->rgbBrightness - 1.f) * (intRect.z - intRect.x)) / 4.f) + intRect.x;
			Rect SliderRect(sliderPos - 2.5f, intRect.y, sliderPos + 3.0f, intRect.w);

			//color scrolling support;
			if (intRect.isInside(mx, my) && didClick)
				if (clickedButton == MouseButton::SCROLL)
					selectedColor->color.g += 0.25f;
			correctValue(selectedColor->rgbBrightness, 1.f, 5.f); 
			

			if (ismousedownrn && (intRect.isInside(mx, my) && selectedSlider == 0) || selectedSlider == 5) {
				selectedSlider = 5;//if the user leave but don't release the mouse, we don't want him to lose his slider...
				float vx = mx, vy = my;	//out of bounds support
				if (mx < intRect.x) vx = intRect.x; if (my < intRect.y) vy = intRect.y; if (mx > intRect.z) vx = intRect.z; if (my > intRect.w) vy = intRect.w;

				selectedColor->rgbBrightness = ((vx - intRect.x) * (4.f / (intRect.z - intRect.x))) + 1.f;

				SliderRect = Rect(vx - 2.5f, intRect.y, vx + 2.5f, intRect.w);
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
				RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
			}
			else
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

			//Display value
			char value[11] = { 0 };
			sprintf(value, "%.2f", selectedColor->rgbBrightness);
			RenderUtils::RenderText(value, Vec2(intRect.z + 4.f, intRect.y - 1.35f), textColor, 1.f, 1.f);
		}

		//rgbspeed
		//rgb speed
		height += ColorPresetSquaresSizeY/1.5f;
		intRect.y = height;
		intRect.w = height + 2.f;
		{ //more like float rect now but ima use the same rect
			RenderUtils::RenderText(mltext("Rainbow Speed", "Vitesse du Rainbow"), Vec2(intRect.x, height - 14.f), textColor, 1.f, 1.f);
			RenderUtils::FillRectangle(intRect, sliderColor, 1.f);
			intRect.y -= 3.0f; intRect.w += 2.5f; //make the clickable area fatter


			float sliderPos = (((selectedColor->rgbSpeed - 0.0008f) * (intRect.z - intRect.x)) / 0.0092f) + intRect.x;
			Rect SliderRect(sliderPos - 2.5f, intRect.y, sliderPos + 3.0f, intRect.w);

			//color scrolling support;
			if (intRect.isInside(mx, my) && didClick)
				if (clickedButton == MouseButton::SCROLL)
					selectedColor->color.g += 0.002f;
			correctValue(selectedColor->rgbSpeed, 0.0008f, 0.01f);


			if (ismousedownrn && (intRect.isInside(mx, my) && selectedSlider == 0) || selectedSlider == 6) {
				selectedSlider = 6;//if the user leave but don't release the mouse, we don't want him to lose his slider...
				float vx = mx, vy = my;	//out of bounds support
				if (mx < intRect.x) vx = intRect.x; if (my < intRect.y) vy = intRect.y; if (mx > intRect.z) vx = intRect.z; if (my > intRect.w) vy = intRect.w;

				selectedColor->rgbSpeed = ((vx - intRect.x) * (0.0092f / (intRect.z - intRect.x))) + 0.0008f;

				SliderRect = Rect(vx - 2.5f, intRect.y, vx + 2.5f, intRect.w);
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
				RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
			}
			else
				RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

			//Display value
			char value[11] = { 0 };
			sprintf(value, "%.2f", selectedColor->rgbSpeed * 100.0);
			RenderUtils::RenderText(value, Vec2(intRect.z + 4.f, intRect.y - 1.35f), textColor, 1.f, 1.f);
		}


		
		//PREVIEW
		RenderUtils::FillRectangle(Rect(panel2start, WindowRect.y, WindowRect.z, WindowRect.y + (ColorPresetSquaresSizeY * 2.0f)), selectedColor->getColor(), selectedColor->opacity);


		
		

		//Confirm button
		Rect confirmButtonRect(panel2start, WindowRect.w - ColorPresetSquaresSizeY, WindowRect.z, WindowRect.w);
		RenderUtils::FillRectangle(confirmButtonRect, sliderColor, 1.f);

		if (confirmButtonRect.isInside(mx, my)) {
			RenderUtils::FillRectangle(confirmButtonRect, hoverColor, hoverOpacity);
			if (didClick && clickedButton == MouseButton::LEFT) 
				selectedColor = nullptr;
		}
		RenderUtils::RenderText("Confirm", Vec2(GetCenterTextPos(confirmButtonRect, "Confirm", 3.5f) + 0.5f, confirmButtonRect.y + (RenderUtils::isMinecraftia ? 6.f: 2.f)), textColor, 3.5f, 1.f);
		

		//RESET brightness&rgbspeed button
		confirmButtonRect.w = confirmButtonRect.y - 2.f;
		confirmButtonRect.y -= 14.f;
		RenderUtils::FillRectangle(confirmButtonRect, sliderColor, 1.f);

		if (confirmButtonRect.isInside(mx, my)) {
			RenderUtils::FillRectangle(confirmButtonRect, hoverColor, hoverOpacity);
			if (didClick && clickedButton == MouseButton::LEFT) {
				selectedColor->rgbBrightness = 1.f;
				selectedColor->rgbSpeed = 0.003f;
			}
		}
		RenderUtils::RenderText("Reset Brightness & Rainbow Speed", Vec2(GetCenterTextPos(confirmButtonRect, "Reset Brightness & Rainbow Speed", 0.83f) + 2.5f, confirmButtonRect.y + 2.f), textColor, 0.8f, 1.f);

		
		RenderUtils::FillRectangle(Rect(panel2start, WindowRect.y, panel2start + 1.f, WindowRect.w), textColor, 1.f);
		RenderUtils::FlushText();
		didClick = false;
		scrollCount = 0;
		return;
	}







#pragma endregion


	


	if (!isInModuleSettings) {
		RenderUtils::RenderText("Click and Drag modules to move them.", Vec2((wx / 2.f) - 75.f, wy - 22.f), textColor, 1.f, 1.f);

		//fade opacity calc
		float FadeOpacity = 1.f;
		if (isFading)
			FadeOpacity = (std::chrono::duration<float>(fadeClock.now() - openedAt)).count();
		if (FadeOpacity > 1.f) {
			isFading = false;
			FadeOpacity = 1.f;
		}




		for (uint16_t i = 0; i < ModuleManager::visualModuleList.size(); i++) {
			if (ModuleManager::visualModuleList[i]->isEnabled() == false)
				continue;
			VisualModule* vmp = ModuleManager::visualModuleList[i];

			Rect modr(vmp->pos.x, vmp->pos.y, vmp->pos.x + vmp->size.x, vmp->pos.y + vmp->size.y);
			RenderUtils::FillRectangle(modr, visualModuleBackColor, visualModuleBackOpacity);
		
			//remove drag & snap
			static int draggingModule = -1;
			

#pragma region Snapping
				if (!ismousedownrn && draggingModule == i) {
					if (!DisableClickguiSnapping) {

					for (uint16_t j = 0; j < ModuleManager::visualModuleList.size(); j++) {
						if (j == i) //not wana do it on urself smh
							continue;
						if (ModuleManager::visualModuleList[j]->isEnabled() == false)
							continue;

						VisualModule* tvmp = ModuleManager::visualModuleList[j];

						//top left, bottom left
						float distance = vmp->pos.Distance(Vec2(tvmp->pos.x, tvmp->pos.y + tvmp->size.y));
						if (distance < 3.5f) {
							vmp->pos.x = tvmp->pos.x;
							vmp->pos.y = tvmp->pos.y + tvmp->size.y;
							break;
						}

						//bottom left, top left
						distance = tvmp->pos.Distance(Vec2(vmp->pos.x, vmp->pos.y + vmp->size.y));
						if (distance < 3.5f) {
							vmp->pos.x = tvmp->pos.x;
							vmp->pos.y = tvmp->pos.y - vmp->size.y;
							break;
						}

						//top left, top right
						distance = vmp->pos.Distance(Vec2(tvmp->pos.x + tvmp->size.x, tvmp->pos.y));
						if (distance < 3.5f) {
							vmp->pos.x = tvmp->pos.x + tvmp->size.x;
							vmp->pos.y = tvmp->pos.y;
							break;
						}

						//top right, top left
						distance = tvmp->pos.Distance(Vec2(vmp->pos.x + vmp->size.x, vmp->pos.y));
						if (distance < 3.5f) {
							vmp->pos.x = tvmp->pos.x - vmp->size.x;
							vmp->pos.y = tvmp->pos.y;
							break;
						}
					}

				}


					draggingModule = -1;
			}
#pragma endregion

			//Drag logic
			static Vec2 clickedDragPos;
			bool wasInside = false;
			if (modr.isInside(mx, my)) {
				//right click option
				if (didClick)
					if (clickedButton == MouseButton::RIGHT) {
						selectedModule = NULL;
						selectedVisualModule = vmp;
						isInModuleSettings = true;
					} else if (clickedButton == MouseButton::SCROLL) 
						for (uint16_t j = 0; j < vmp->settings.size(); j++)
							if (!strcmp("scale", vmp->settings[j].internalName)) {
								*vmp->settings[j].vfloat += ((float)scrollCount/10.f) / vmp->settings[j].maxfloat;
								correctValue(*vmp->settings[j].vfloat, vmp->settings[j].minfloat, vmp->settings[j].maxfloat);
								vmp->settings[j].callOnChange();
							}

				
				
				//start dragging
				if (didClick && clickedButton == MouseButton::LEFT && draggingModule != i) {
					draggingModule = i;
					clickedDragPos = Vec2(mx - vmp->pos.x, my - vmp->pos.y);
				}
				RenderUtils::FillRectangle(modr, hoverColor, hoverOpacity);
				wasInside = true;
			}

			if (draggingModule == i) {
				if (!wasInside) RenderUtils::FillRectangle(modr, hoverColor, hoverOpacity);

				vmp->pos.x = mx - clickedDragPos.x;
				vmp->pos.y = my - clickedDragPos.y;
			}
			

		}












		//ModuleSettings button
#ifndef _IN_FRENCH
		Rect GoModuleSettingsButton((wx / 2.f) / 1.45f, (wy / 2.f) / 1.15f, (wx / 2.f) * 1.3f, (wy / 2.f) * 1.1f);
#else
		Rect GoModuleSettingsButton((wx / 2.2f) / 1.45f, (wy / 2.f) / 1.15f, (wx / 1.9f) * 1.3f, (wy / 2.f) * 1.1f);
#endif
		RenderUtils::FillRectangle(GoModuleSettingsButton, backgroundColor, 0.50f * FadeOpacity);
		RenderUtils::DrawRectangle(GoModuleSettingsButton, textColor, 1.f * FadeOpacity, 1.0f);
		RenderUtils::RenderText(mltext("Module Settings", "Reglages des modules"), Vec2(
			(wx / 2.f) - (RenderUtils::GetTextWidth(mltext("Module Settings", "Reglages des modules"), 2.f)/2.f) - 1.f,
			(wy / 2.f) - RenderUtils::GetTextWidth("W", 1.70f)), textColor, 2.f, 1.f * FadeOpacity);
		if (GoModuleSettingsButton.isInside(mx, my)) {
			RenderUtils::FillRectangle(GoModuleSettingsButton, hoverColor, hoverOpacity * FadeOpacity);
			if (didClick && clickedButton == MouseButton::LEFT)
				isInModuleSettings = true;
		}

#if gdebug == 1
		char debugText[100] = { 0 };
		Rect r = GoModuleSettingsButton;
		sprintf(debugText, "x: %d    y: %d    z: %d    w: %d", (int)r.x, (int)r.y, (int)r.z, (int)r.w);
		RenderUtils::RenderText(debugText, Vec2(2.f, wy - 20.f), MC_Color(0.3f, 1.f, 0.3f), 1.5f, 1.f);
#endif


	}
	//NOW IN MODULE SETTINGS
	//NOW IN MODULE SETTINGS
	//NOW IN MODULE SETTINGS
	//NOW IN MODULE SETTINGS
	else {

		ModuleRect = Rect(wx / 12.f, wy / 12.f, (wx / 2.f) - 5.f, wy - (wy / 12.f) + 5.f);
		RenderUtils::FillRectangle(ModuleRect, backgroundColor, CLICKGUI_SETTINGS_OPACITY);
				

		//VisualModuleRect = Rect(ModuleRect.x, ModuleRect.w + 10.f, ModuleRect.z, wy - (wy / 12.f) + 5.f);
		//RenderUtils::FillRectangle(VisualModuleRect, backgroundColor, CLICKGUI_SETTINGS_OPACITY);
	
		if (selectedModule == nullptr && selectedVisualModule == nullptr)
			selectedModule = clickguiModule;

		ModuleSettingsRect = Rect(ModuleRect.z + 10.f, ModuleRect.y, wx - ModuleRect.x, ModuleRect.w);
		RenderUtils::FillRectangle(ModuleSettingsRect, backgroundColor, CLICKGUI_SETTINGS_OPACITY);
		TextWidth = RenderUtils::GetTextWidth(mltext("Module Settings", "Parametres du Module"), 1.f);
		RenderUtils::RenderText(mltext("Module Settings", "Parametres du Module"), Vec2(wx - (wx / 3.5f) - TextWidth, ModuleSettingsRect.y), textColor, 2.f, 1.f);
		

		
		float previousScrollValue = ModuleRect.y + 1.f;
		float scrollValue = previousScrollValue;
		float PositionOfTheModuleNameText = ModuleRect.x + 8.f;

		for (uint16_t i = 0; i < ModuleManager::moduleList.size(); i++) {
			if (ModuleManager::moduleList[i]->isBlocked)
				continue;
			RenderUtils::RenderText(ModuleManager::moduleList[i]->name, Vec2(PositionOfTheModuleNameText, scrollValue - 2.f), ModuleManager::moduleList[i]->isEnabled() ? enabledModuleColor : textColor, 1.f, 1.f);
			scrollValue += 10.f;
			RenderUtils::FillRectangle(Rect(ModuleRect.x, scrollValue - 2.f, ModuleRect.z, scrollValue - 1.f), sliderColor, 0.2f);

			

			Rect moduleSelect(ModuleRect.x, previousScrollValue - 1.f, ModuleRect.z, scrollValue - 4.f);
			Rect resetRect(ModuleRect.z - 27.f, previousScrollValue, ModuleRect.z - 3.f, previousScrollValue + 7.f);
			RenderUtils::FillRectangle(resetRect, sliderColor, 1.f);
			RenderUtils::RenderText("Reset", Vec2(((resetRect.z - resetRect.x) / 2.f) + resetRect.x - (RenderUtils::GetTextWidth("Reset", 0.8f) / 2.f), resetRect.y - 1.0f), textColor, 0.8f, 1.f);

				if (moduleSelect.isInside(mx,my)) 
					if (resetRect.isInside(mx, my)) {
						RenderUtils::FillRectangle(resetRect, hoverColor, hoverOpacity);
						if (didClick && clickedButton == MouseButton::LEFT)
							for (uint8_t j = 0; j < ModuleManager::moduleList[i]->settings.size(); j++)
								ModuleManager::moduleList[i]->settings[j].reset();
						
					}
					else {
						RenderUtils::FillRectangle(Rect(moduleSelect.x + 2.f, previousScrollValue + 1.f, moduleSelect.x + 5.f, scrollValue - 4.f), textColor, 0.85f);
						if (didClick && clickedButton == MouseButton::LEFT) {
							selectedModule = ModuleManager::moduleList[i];
							selectedVisualModule = nullptr;
						} else if (didClick && clickedButton == MouseButton::RIGHT)
							if (ModuleManager::moduleList[i]->isToggle)
								ModuleManager::moduleList[i]->Toggle();
					}
				

			previousScrollValue = scrollValue;
		}


		for (uint16_t i = 0; i < ModuleManager::visualModuleList.size(); i++) {
			RenderUtils::RenderText(ModuleManager::visualModuleList[i]->name, Vec2(PositionOfTheModuleNameText, scrollValue - 2.f), ModuleManager::visualModuleList[i]->isEnabled() ? enabledModuleColor : textColor, 1.f, 1.f);
			scrollValue += 10.f;
			RenderUtils::FillRectangle(Rect(ModuleRect.x, scrollValue - 2.f, ModuleRect.z, scrollValue - 1.f), sliderColor, 0.2f);

			Rect moduleSelect(ModuleRect.x, previousScrollValue - 1.f, ModuleRect.z, scrollValue - 2.f);
			Rect resetRect(ModuleRect.z - 27.f, previousScrollValue, ModuleRect.z - 3.f, previousScrollValue + 7.f);
			RenderUtils::FillRectangle(resetRect, sliderColor, 1.f);
			RenderUtils::RenderText("Reset", Vec2(((resetRect.z - resetRect.x) / 2.f) + resetRect.x - (RenderUtils::GetTextWidth("Reset", 0.8f) / 2.f), resetRect.y - 1.0f), textColor, 0.8f, 1.f);

			if (moduleSelect.isInside(mx, my)) {
				if (resetRect.isInside(mx, my)) {
					RenderUtils::FillRectangle(resetRect, hoverColor, hoverOpacity);
					if (didClick && clickedButton == MouseButton::LEFT)
						for (uint8_t j = 0; j < ModuleManager::visualModuleList[i]->settings.size(); j++)
							ModuleManager::visualModuleList[i]->settings[j].reset();

				}
				else {
					RenderUtils::FillRectangle(Rect(moduleSelect.x + 2.f, previousScrollValue + 1.f, moduleSelect.x + 5.f, scrollValue - 4.f), textColor, 0.85f);
					if (didClick && clickedButton == MouseButton::LEFT) {
						selectedVisualModule = ModuleManager::visualModuleList[i];
						selectedModule = nullptr;
					}
					else if (didClick && clickedButton == MouseButton::RIGHT)
						ModuleManager::visualModuleList[i]->Toggle();
				}
			}

			previousScrollValue = scrollValue;
		}


		bool ismoduleSelected = false;
		bool isSelectedModuleToggle = true;
		bool ismoduleEnabled = false;
		const char* moduleName = nullptr;
		const char* moduleDescription = nullptr;
		std::vector<Setting>* options = nullptr;

		if (selectedModule != nullptr) {
			moduleName = selectedModule->name;
			ismoduleEnabled = selectedModule->enabled;
			moduleDescription = selectedModule->shortDescription;
			options = &selectedModule->settings;
			ismoduleSelected = true;
			isSelectedModuleToggle = selectedModule->isToggle;
		}
		if (selectedVisualModule != nullptr) {
			moduleName = selectedVisualModule->name;
			ismoduleEnabled = selectedVisualModule->enabled;
			moduleDescription = selectedVisualModule->shortDescription;
			options = &selectedVisualModule->settings;
			ismoduleSelected = true;
			isSelectedModuleToggle = true;
		}

		if (ismoduleSelected) {
			scrollValue = ModuleSettingsRect.y + TextHeight_2 + 5.f;
			previousScrollValue = scrollValue;
			float textSettingX = ModuleSettingsRect.x + 5.f;

		

			//Enable / disabled
			if (isSelectedModuleToggle) {
				//module name drawing
				RenderUtils::RenderText(moduleName, Vec2(textSettingX, scrollValue), textColor, 1.f, 1.f);
				TextWidth = RenderUtils::GetTextWidth(mltext("Disabled", "Desactiver"), 1.2f);
				Rect EnableDisableButton(ModuleSettingsRect.z - TextWidth, previousScrollValue, ModuleSettingsRect.z, scrollValue + TextHeight_1 + 2.f);

				if (ismoduleEnabled) {
					RenderUtils::FillRectangle(EnableDisableButton, enabledModuleColor, 1.f);
					RenderUtils::RenderText(mltext("Enabled", "Activer"), Vec2(ModuleSettingsRect.z - TextWidth + 4.5f, EnableDisableButton.y), textColor, 1.f, 1.f);
				} else {
					RenderUtils::FillRectangle(EnableDisableButton, disabledModuleColor, 1.f);
					RenderUtils::RenderText(mltext("Disabled", "Desactiver"), Vec2(ModuleSettingsRect.z - TextWidth + 3.f, EnableDisableButton.y), textColor, 1.f, 1.f);
				}

				if (EnableDisableButton.isInside(mx, my)) {
					RenderUtils::FillRectangle(EnableDisableButton, hoverColor, hoverOpacity);
					if (didClick && clickedButton == MouseButton::LEFT)
						if (selectedModule != nullptr)
							selectedModule->Toggle();
						else if (selectedVisualModule != nullptr)
							selectedVisualModule->Toggle();
				}
			} else {
				TextWidth = RenderUtils::GetTextWidth(mltext("Enable with the keybind.", "Activer avec la touche."), 1.0f);
				RenderUtils::RenderText(moduleName, Vec2(textSettingX, scrollValue), textColor, 1.f, 1.f);
				RenderUtils::RenderText(mltext("Enable with the keybind.", "Activer avec la touche."), Vec2(ModuleSettingsRect.z - TextWidth, scrollValue), textColor, 1.f, 1.f);
			}
			scrollValue += TextHeight_1 += 5.f;
			previousScrollValue = scrollValue;

			//Description
			RenderUtils::RenderText(moduleDescription, Vec2(textSettingX, scrollValue), textColor, 0.75f, 1.f);
			scrollValue += TextHeight_1 + 5.f;
			previousScrollValue = scrollValue;


			


			for (uint8_t i = 0; i < options->size(); i++) {
				

				if (!(*options)[i].showInClickgui)
					continue; //not show value that should not be shown?

				switch ((*options)[i].type) {
				case SettingType::BOOL: {

					RenderUtils::RenderText((*options)[i].name, Vec2(textSettingX, scrollValue), textColor, 1.f, 1.f);
					Rect boolRect(ModuleSettingsRect.z - 15.f, scrollValue, ModuleSettingsRect.z - 5.f, scrollValue + 10.f);
					RenderUtils::FillRectangle(boolRect, *(*options)[i].vbool ? enabledModuleColor : disabledModuleColor, 1.f);
					if (boolRect.isInside(mx, my)) {
						RenderUtils::FillRectangle(boolRect, hoverColor, hoverOpacity);
						if (didClick && clickedButton == MouseButton::LEFT) {
							*(*options)[i].vbool = !(*(*options)[i].vbool);
							(*options)[i].callOnChange();
						}
					}

					previousScrollValue = scrollValue;
					scrollValue += (*options)[i].getHeight();
					break; }
				case SettingType::INT: {
					scrollValue -= 2.f;
					RenderUtils::RenderText((*options)[i].name, Vec2(textSettingX, scrollValue), textColor, 0.85f, 1.0f);

					previousScrollValue = scrollValue + 12.f;
					Rect intRect(ModuleSettingsRect.x + 5.f, previousScrollValue, ModuleSettingsRect.z - 40.f, previousScrollValue + 2.f);
					RenderUtils::FillRectangle(intRect, sliderColor, 1.f);
					intRect.y -= 3.0f;
					intRect.w += 2.5f;

					float sliderPos = ((float)(*(*options)[i].vint - (*options)[i].minint) * (intRect.z - intRect.x)) / (float)((*options)[i].maxint - (*options)[i].minint);
					sliderPos += intRect.x;
					Rect SliderRect(sliderPos - 2.5f, intRect.y, sliderPos + 3.0f, intRect.w);
					
					bool isValidSelection = true;
					for (uint8_t j = 0; j < (*options).size(); j++)
						if ((*options)[j].selected && j != i)
							isValidSelection = false;

					if (isValidSelection && ismousedownrn && (intRect.isInside(mx,my) || (*options)[i].selected)) {
						//if the user leave but don't release the mouse, we don't wanthim to lose his slider...
						(*options)[i].selected = true;
						float vx = mx, vy = my;
						if (mx < intRect.x) vx = intRect.x;
						if (my < intRect.y) vy = intRect.y;
						if (mx > intRect.z) vx = intRect.z;
						if (my > intRect.w) vy = intRect.w;
						
						//Epic math right there
						(*(*options)[i].vint) = (int)round((((vx - intRect.x) * ((*options)[i].maxint - (*options)[i].minint)) / (intRect.z - intRect.x)) + (*options)[i].minint);
						(*options)[i].callOnChange();

						SliderRect = Rect(vx - 2.5f, intRect.y, vx + 2.5f, intRect.w);
						RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
						RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
					} else 
						RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

					char value[11] = { 0 };
					sprintf(value, "%i", (*(*options)[i].vint));
					RenderUtils::RenderText(value, Vec2(intRect.z + 5.f, intRect.y - 1.35f), textColor, 1.f, 1.f);
					scrollValue += (*options)[i].getHeight();
					previousScrollValue = scrollValue;
					break;}


				case SettingType::FLOAT: {
					scrollValue -= 2.f;
					RenderUtils::RenderText((*options)[i].name, Vec2(textSettingX, scrollValue), textColor, 0.85f, 1.0f);

					previousScrollValue = scrollValue + 12.f;
					Rect floatRect(ModuleSettingsRect.x + 5.f, previousScrollValue, ModuleSettingsRect.z - 40.f, previousScrollValue + 2.f);
					RenderUtils::FillRectangle(floatRect, sliderColor, 1.f);
					floatRect.y -= 3.0f;
					floatRect.w += 2.5f;

					float sliderPos = ((((*(*options)[i].vfloat) - (*options)[i].minfloat) * (floatRect.z - floatRect.x)) / ((*options)[i].maxfloat - (*options)[i].minfloat));
					sliderPos += floatRect.x;
					Rect SliderRect(sliderPos - 2.5f, floatRect.y, sliderPos + 3.0f, floatRect.w);

					bool isValidSelection = true;
					for (uint8_t j = 0; j < (*options).size(); j++)
						if ((*options)[j].selected && j != i)
							isValidSelection = false;
					

					if (isValidSelection && ismousedownrn && (floatRect.isInside(mx, my) || (*options)[i].selected)) {
						//if the user leave but don't release the mouse, we don't wanthim to lose his slider...
						(*options)[i].selected = true;
						float vx = mx, vy = my;
						if (mx < floatRect.x) vx = floatRect.x;
						if (my < floatRect.y) vy = floatRect.y;
						if (mx > floatRect.z) vx = floatRect.z;
						if (my > floatRect.w) vy = floatRect.w;

						//Epic math right there
						(*(*options)[i].vfloat) = (((vx - floatRect.x) * ((*options)[i].maxfloat - (*options)[i].minfloat)) / (floatRect.z - floatRect.x)) + (*options)[i].minfloat;
						(*options)[i].callOnChange();

						SliderRect = Rect(vx - 2.5f, floatRect.y, vx + 2.5f, floatRect.w);
						RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
						RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
					}
					else
						RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

					char value[11] = { 0 };
					sprintf(value, "%.2f", (*(*options)[i].vfloat));
					RenderUtils::RenderText(value, Vec2(floatRect.z + 5.f, floatRect.y - 1.35f), textColor, 1.f, 1.f);
					scrollValue += (*options)[i].getHeight();
					previousScrollValue = scrollValue;
					break; }

				case SettingType::KEYBIND: {

					RenderUtils::RenderText((*options)[i].name, Vec2(textSettingX, scrollValue), textColor, 1.f, 1.f);
					float spaceLenght = RenderUtils::GetTextWidth("spacel", 1.f);
					Rect keyRect(ModuleSettingsRect.z - 5.f - spaceLenght, scrollValue, ModuleSettingsRect.z - 5.f, scrollValue + 10.f);

					RenderUtils::DrawRectangle(keyRect, sliderColor, 1.f, 0.5f);

					//text
					char keyName[10] = { 0 };
					(*options)[i].getKeybindName(keyName);
					RenderUtils::RenderText(keyName, Vec2(((keyRect.z - keyRect.x) / 2.f) + keyRect.x - (RenderUtils::GetTextWidth(keyName, 0.8f) / 2.f), keyRect.y + 0.5f), textColor, 0.8f, 1.f);
					RenderUtils::FlushText();

					static int16_t optionWaitkey = -1;
					if (keyRect.isInside(mx, my)) {
						RenderUtils::FillRectangle(keyRect, hoverColor, hoverOpacity);
						if (didClick && clickedButton == MouseButton::LEFT) {
							waitingKey = true;
							optionWaitkey = i;
						}
					}
					if (optionWaitkey == i && !waitingKey) {
						waitingKey = false;
						optionWaitkey = -1;
						*(*options)[i].vKeybind = selectedKey == VK_ESCAPE ? 0 : selectedKey;
						(*options)[i].callOnChange();
					}


					//Default button
					keyRect = Rect(keyRect.x - 40.f, keyRect.y, keyRect.x - 6.f, keyRect.w);
					RenderUtils::FillRectangle(keyRect, sliderColor, 1.f);
					RenderUtils::RenderText(mltext("Default", "Defaut"), Vec2(((keyRect.z - keyRect.x) / 2.f) + keyRect.x - (RenderUtils::GetTextWidth(mltext("Default", "Defaut"), 0.8f) / 2.f), keyRect.y + +0.5f), textColor, 0.8f, 1.f);
					if (keyRect.isInside(mx, my)) {
						RenderUtils::FillRectangle(keyRect, hoverColor, hoverOpacity);
						if (didClick && clickedButton == MouseButton::LEFT) {
							*(*options)[i].vKeybind = (*options)[i].dKeybind;
							(*options)[i].callOnChange();
						}
					}


					RenderUtils::FlushText();
					scrollValue += (*options)[i].getHeight();
					previousScrollValue = scrollValue;
					break; }


				case SettingType::VEC2: {
#pragma region Vec2Setting

					scrollValue -= 2.f;
					RenderUtils::RenderText((*options)[i].name, Vec2(textSettingX, scrollValue), textColor, 0.85f, 1.0f);
					previousScrollValue = scrollValue + 12.f;


					{
						Rect floatRect(ModuleSettingsRect.x + 5.f, previousScrollValue, ((ModuleSettingsRect.z - ModuleSettingsRect.x) / 2) + ModuleSettingsRect.x - 30.f, previousScrollValue + 2.f);
						RenderUtils::FillRectangle(floatRect, sliderColor, 1.f);
						floatRect.y -= 3.0f;
						floatRect.w += 2.5f;

						float sliderPos = (((*options)[i].vvec2->x - (*options)[i].minvec2.x) * (floatRect.z - floatRect.x)) / ((*options)[i].maxvec2.x - (*options)[i].minvec2.x);
						sliderPos += floatRect.x;
						Rect SliderRect(sliderPos - 2.5f, floatRect.y, sliderPos + 3.0f, floatRect.w);

						bool isValidSelection = true;
						for (uint8_t j = 0; j < (*options).size(); j++)
							if ((*options)[j].selected && j != i)
								isValidSelection = false;
						isValidSelection = isValidSelection && (*options)[i].selectID == 1 || !(*options)[i].selected;


						if (isValidSelection && ismousedownrn && (floatRect.isInside(mx, my))) {
							//if the user leave but don't release the mouse, we don't wanthim to lose his slider...
							(*options)[i].selectID = 1;
							float vx = mx, vy = my;
							if (mx < floatRect.x) vx = floatRect.x;
							if (my < floatRect.y) vy = floatRect.y;
							if (mx > floatRect.z) vx = floatRect.z;
							if (my > floatRect.w) vy = floatRect.w;

							//Epic math right there
							(*options)[i].vvec2->x = (((vx - floatRect.x) * ((*options)[i].maxvec2.x - (*options)[i].minvec2.x) / (floatRect.z - floatRect.x)) + (*options)[i].minvec2.x);
							(*options)[i].callOnChange();

							SliderRect = Rect(vx - 2.5f, floatRect.y, vx + 2.5f, floatRect.w);
							RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
							RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
						}
						else
							RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

						char value[11] = { 0 };
						sprintf(value, "%.2f", (*options)[i].vvec2->x);
						RenderUtils::RenderText(value, Vec2(floatRect.z + 5.f, floatRect.y - 1.35f), textColor, 1.f, 1.f);
					}


					Rect floatRect(ModuleSettingsRect.z - ((ModuleSettingsRect.z - ModuleSettingsRect.x) / 2), previousScrollValue, ModuleSettingsRect.z - 30.f, previousScrollValue + 2.f);
					RenderUtils::FillRectangle(floatRect, sliderColor, 1.f);
					floatRect.y -= 3.0f;
					floatRect.w += 2.5f;

					float sliderPos = (((*options)[i].vvec2->y - (*options)[i].minvec2.y) * (floatRect.z - floatRect.x)) / ((*options)[i].maxvec2.y - (*options)[i].minvec2.y);
					sliderPos += floatRect.x;
					Rect SliderRect(sliderPos - 2.5f, floatRect.y, sliderPos + 3.0f, floatRect.w);


					bool isValidSelection = true;
					for (uint8_t j = 0; j < (*options).size(); j++)
						if ((*options)[j].selected && j != i)
							isValidSelection = false;
					isValidSelection = isValidSelection && (*options)[i].selectID == 2 || !(*options)[i].selected;


					if (isValidSelection && (ismousedownrn && (floatRect.isInside(mx, my)))) {
						//if the user leave but don't release the mouse, we don't wanthim to lose his slider...
						(*options)[i].selectID = 2;
						float vx = mx, vy = my;
						if (mx < floatRect.x) vx = floatRect.x;
						if (my < floatRect.y) vy = floatRect.y;
						if (mx > floatRect.z) vx = floatRect.z;
						if (my > floatRect.w) vy = floatRect.w;

						float game = options->at(i).maxvec2.y;
						//Epic math right there
						(*options)[i].vvec2->y = (((vx - floatRect.x) * ((*options)[i].maxvec2.y - (*options)[i].minvec2.y) / (floatRect.z - floatRect.x)) + (*options)[i].minvec2.y);
						(*options)[i].callOnChange();

						SliderRect = Rect(vx - 2.5f, floatRect.y, vx + 2.5f, floatRect.w);
						RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);
						RenderUtils::FillRectangle(SliderRect, hoverColor, hoverOpacity);
					}
					else
						RenderUtils::FillRectangle(SliderRect, sliderColor, 1.f);

					char value[11] = { 0 };
					sprintf(value, "%.2f", (*options)[i].vvec2->y);
					RenderUtils::RenderText(value, Vec2(floatRect.z + 5.f, floatRect.y - 1.35f), textColor, 1.f, 1.f);
					scrollValue += (*options)[i].getHeight();
					previousScrollValue = scrollValue;

					break; }
#pragma endregion

				case SettingType::COLOR:
				
					RenderUtils::RenderText((*options)[i].name, Vec2(textSettingX, scrollValue + 1.5f), textColor, 0.60f, 1.f);
					Rect colorRect(ModuleSettingsRect.z - 20.f, scrollValue, ModuleSettingsRect.z - 2.f, scrollValue + 10.f);
					RenderUtils::FillRectangle(colorRect, (*options)[i].vColor->getColor(), (*options)[i].vColor->opacity);
			

					//Change color button

					colorRect = Rect(colorRect.x - 50.f, colorRect.y, colorRect.x - 3.f, colorRect.w);
					RenderUtils::FillRectangle(colorRect, sliderColor, 1.f);
					RenderUtils::RenderText(mltext("Change color", "Changer couleur"), Vec2(((colorRect.z - colorRect.x) / 2.f) + colorRect.x - (RenderUtils::GetTextWidth("Change color", 0.8f) / 2.f), colorRect.y + +0.5f), textColor, 0.8f, 1.f);
					if (colorRect.isInside(mx, my)) {
						RenderUtils::FillRectangle(colorRect, hoverColor, hoverOpacity);
						if (didClick && clickedButton == MouseButton::LEFT)
							selectedColor = (*options)[i].vColor;
					}


					//Default button
					colorRect = Rect(colorRect.x - 27.f, colorRect.y, colorRect.x - 3.f, colorRect.w);
					RenderUtils::FillRectangle(colorRect, sliderColor, 1.f);
					RenderUtils::RenderText(mltext("Default", "Defaut"), Vec2(((colorRect.z - colorRect.x) / 2.f) + colorRect.x - (RenderUtils::GetTextWidth(mltext("Default", "Defaut"), 0.8f) / 2.f), colorRect.y + +0.5f), textColor, 0.8f, 1.f);
					if (colorRect.isInside(mx, my)) {
						RenderUtils::FillRectangle(colorRect, hoverColor, hoverOpacity);
						if (didClick && clickedButton == MouseButton::LEFT) 
							*(*options)[i].vColor = (*options)[i].dColor;
					}
					RenderUtils::FlushText();

					scrollValue += (*options)[i].getHeight();
					previousScrollValue = scrollValue;

				};


				//after settings drawing



			}


		}

		if (waitingKey) {
			float tw = (RenderUtils::GetTextWidth("You can cancel the change by pressing Escape", 1.35f) / 2.f) - 1.f;
			RenderUtils::FillRectangle(Rect(((wx / 2.f) - tw) - 16.f, (wy/2.f) - TextHeight_2 - 12.f, ((wx / 2.f) + tw) + 16.f, (wy/2.f) + TextHeight_1 - 1.f), MC_Color(0.f, 0.f, 0.f), 0.5f);
			RenderUtils::RenderUtils::RenderText("  Press the key you want to use as a keybind.\nYou can cancel the change by pressing Escape", Vec2((wx / 2.f) - tw, (wy / 2.f) - RenderUtils::GetTextWidth("WW", 1.70f)), textColor, 1.35f, 1.f);
		}


	}








#if gdebug == 1
	char debugText[100] = { 0 };
	sprintf(debugText, "WindowSizeX: %d    WindowSizeY: %d\nMousePosX: %d    MousePosY: %d", (int)wx, (int)wy, (int)mx, (int)my);
	RenderUtils::RenderText(debugText, Vec2(2.f, 2.f), MC_Color(0.3f, 1.f, 0.3f), 1.5f, 1.f);
#endif


	RenderUtils::FlushText();

	didClick = false;
	scrollCount = 0;
}





