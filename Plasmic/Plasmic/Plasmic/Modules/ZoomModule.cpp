#include "ZoomModule.h"





std::chrono::high_resolution_clock zoomclock;
std::chrono::steady_clock::time_point start;
bool isAnimating = false;

void ZoomModule::onRender() {

	if (!isAnimating)
		game::clientinstance->guiData->windowSizeReal.x = (originalSize / zoomValue);
	else {
		float multi = std::chrono::duration<float>(zoomclock.now() - start).count() / animationDuration;
		if (multi > 1.f) {
			multi = 1.f;
			isAnimating = false;
		}
		game::clientinstance->guiData->windowSizeReal.x = (originalSize / (zoomValue * multi));
	}

	//Epic debug info
	//char gamer[50] = { 0 };
	//sprintf(gamer, "Zoom: %f     OriginalSize: %f         Size: %f", zoomValue, originalSize, (originalSize / zoomValue));

//	RenderUtils::RenderText(gamer, Vec2(10, 100), MC_Color(0.f, 1.f, 0.f), 1.f, 1.f);
}



void ZoomModule::onEnable() {
	originalSize = game::clientinstance->guiData->windowSizeReal.x;

	if (doAnimation) {
		isAnimating = true;
		start = zoomclock.now();
	}
}
void ZoomModule::onDisable() {
	game::clientinstance->guiData->windowSizeReal.x = originalSize;
	if (!saveScroll)
		zoomValue = 5.f;
}



void ZoomModule::onMouse(MouseButton button, bool isDown, bool& cancel) {


	if (button == MouseButton::SCROLL) {
		if (isDown)
			zoomValue -= 0.75f;
		else
			zoomValue += 0.75f;


		if (zoomValue > MODULE_ZOOM_MAXZOOM)
			zoomValue = MODULE_ZOOM_MAXZOOM;
		if (zoomValue < MODULE_ZOOM_MINZOOM)
			zoomValue = MODULE_ZOOM_MINZOOM;
		cancel = true;
	}



}