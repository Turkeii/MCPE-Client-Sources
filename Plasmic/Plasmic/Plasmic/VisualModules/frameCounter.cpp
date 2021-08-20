#include "frameCounter.h"
#include "Keystroke.h"


static char fpsText[16] = "FPS: 0000000";



static float textPos = 0.f;
void frameCounter::onTick(Gamemode* gm) {
	sprintf(fpsText, "%d FPS", game::fps);

	size.x = (((KEY_WIDTH * 3.f) + (KEY_PADDING * 2.f)) - reducedWidth) * scale;
	size.y = 14.f * scale;

	textPos = pos.x + size.x / 3.9f;
}




void frameCounter::onRender() {

	

	RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.color, backgroundColor.opacity);

	RenderUtils::RenderText(fpsText, Vec2(pos.x + ((size.x / 2.f) - (RenderUtils::GetTextWidth(fpsText, 1.f * scale) / 2.f)), pos.y + (1.68f * scale)), textColor.color, 1.f * scale, textColor.opacity);
	RenderUtils::FlushText();
}