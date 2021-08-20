#include "CPSmodule.h"
#include "Keystroke.h"

static char cpsText[32] = "CPS 0|0";



void CPSmodule::onTick(Gamemode* gm) {
	size.x = (((KEY_WIDTH * 3.f) + (KEY_PADDING * 2.f)) - reducedWidth) * scale;
	size.y = 14.f * scale;

	if (cpsAfter)
		if (showRightclick)
			sprintf(cpsText, "%d | %d CPS", game::lcps, game::rcps);
		else
			sprintf(cpsText, "%d CPS", game::lcps);
	else
		if (showRightclick)
			sprintf(cpsText, "CPS %d | %d", game::lcps, game::rcps);
		else
			sprintf(cpsText, "CPS %d", game::lcps);
}

void CPSmodule::onRender() {

	RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.color, backgroundColor.opacity);

	RenderUtils::RenderText(cpsText, Vec2(pos.x + ((size.x/2.f) - (RenderUtils::GetTextWidth(cpsText, 1.f * scale)/2.f)), pos.y + (1.68f * scale)), textColor.color, 1.f * scale, textColor.opacity);
	RenderUtils::FlushText();
}


