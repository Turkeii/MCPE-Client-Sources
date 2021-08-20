#pragma once
class ClickGui;
class Module;

#include "../Utils/PlasmicMath.h"
#include "../Utils/mem.h"
#include <Windows.h>
#include <cstdarg>

//SDK
#include "../SDK/sdk.h"


class ClickGui {
	bool enabled = false;
public:
	bool uiHidden = false;

	uint16_t key = 'L';
	Module* clickguiModule;

	ClickGui();


	void Enable() { enabled = true; onEnable(); }
	void Disable() { enabled = false; onDisable(); }
	void Toggle() { enabled = !enabled; if (enabled) onEnable(); else onDisable(); }
	bool isEnabled() { return enabled; }
	bool shouldRenderVisualModules();

	void onEnable();
	void onDisable();
	void onEject();


	void onRender();
	void onKey(uint16_t key, bool isDown, bool& cancel);
	void onMouse(MouseButton button, bool isDown, bool& cancel);

	static void sendNotificationf(const char* format, ...);
	void notificationRenderer();
};

