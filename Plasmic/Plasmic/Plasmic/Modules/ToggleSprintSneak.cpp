#include "ToggleSprintSneak.h"

#include "../Manager.h"
#include "../Hooks/InputHook.h"


bool cancelNextOne = false;
void ToggleSprintSneak::onKey(uint16_t key, bool isDown, bool& cancel) {
	if (!game::minecraftGame->canMoveCamera)
		return;

//	if (cancelNextOne == true) {
	//	cancelNextOne = false;
	//	return;
	//

	if (isSprint) {
		if (key == sprintKey) {
			lastOne = false;
			toggled++;
			if (toggled == 2 && isDown == false) {
				cancel = true;
				return;
			}

		}

		if (toggled > 3)
			toggled = 0;
	}

	if (isSneak) {
		if (key == sneakKey) {
			lastOne = true;
			sneaktoggled++;
			if (sneaktoggled == 2 && isDown == false) {
				cancel = true;
				return;
			}
		}

		if (sneaktoggled > 3)
			sneaktoggled = 0;
	}
}



void ToggleSprintSneak::onRender() {
	if (!game::minecraftGame->canMoveCamera)
		return;

	
	RenderUtils::FillRectangle(Rect(0, 0, 0, 0), MC_Color(1, 1, 1), 1);//idk, without it text dosen't render its fat


	float th = 11.0f;
	if (RenderUtils::isMinecraftia)
		th = 8.5f;

	if (!game::clickGui->uiHidden)
		if (isSprint && lastOne == false && !alwaysSprint) 
			if (toggled == 0)
				RenderUtils::RenderText("[Sprinting: (Not Toggled)]", Vec2(0.f, isTop ? 0.f : (game::clientinstance->guiData->windowSizeScaled.y - th)), MC_Color(1.f, 1.f, 1.f), 1.f, 1.f);
			else if (toggled == 1 || toggled == 3)
				RenderUtils::RenderText("[Sprinting: (Held)]", Vec2(0.f, isTop ? 0.f : (game::clientinstance->guiData->windowSizeScaled.y - th)), MC_Color(1.f, 1.f, 1.f), 1.f, 1.f);
			else
				RenderUtils::RenderText("[Sprinting: (Toggled)]", Vec2(0.f, isTop ? 0.f : (game::clientinstance->guiData->windowSizeScaled.y - th)), MC_Color(1.f, 1.f, 1.f), 1.f, 1.f);
		else if (isSneak && lastOne == true)
			if (sneaktoggled == 0)
				RenderUtils::RenderText("[Sneaking: (Not Toggled)]", Vec2(0.f, isTop ? 0.f : (game::clientinstance->guiData->windowSizeScaled.y - th)), MC_Color(1.f, 1.f, 1.f), 1.f, 1.f);
			else if (sneaktoggled == 1 || sneaktoggled == 3)
				RenderUtils::RenderText("[Sneaking: (Held)]", Vec2(0.f, isTop ? 0.f : (game::clientinstance->guiData->windowSizeScaled.y - th)), MC_Color(1.f, 1.f, 1.f), 1.f, 1.f);
			else
				RenderUtils::RenderText("[Sneaking: (Toggled)]", Vec2(0.f, isTop ? 0.f : (game::clientinstance->guiData->windowSizeScaled.y - th)), MC_Color(1.f, 1.f, 1.f), 1.f, 1.f);
	

	if (sneaktoggled == 2) {
		game::clientinstance->moveinputHandler->pressingSneakkey = true;
		game::clientinstance->moveinputHandler->pressingSneakkey2 = true;
		game::clientinstance->moveinputHandler->pressingSneakkey3 = true;
		game::clientinstance->moveinputHandler->pressingRunkey = false;
		game::clientinstance->moveinputHandler->pressingRunkey2 = false;
	}
	else if (toggled == 2 || alwaysSprint) {
		game::clientinstance->moveinputHandler->pressingRunkey = true;
		game::clientinstance->moveinputHandler->pressingRunkey2 = true;
	}
	


	RenderUtils::FlushText();
}


void ToggleSprintSneak::onDisable() {

		game::clientinstance->moveinputHandler->pressingSneakkey = false;
		game::clientinstance->moveinputHandler->pressingSneakkey2 = false;
		game::clientinstance->moveinputHandler->pressingSneakkey3 = false;
		game::clientinstance->moveinputHandler->pressingRunkey = false;
		game::clientinstance->moveinputHandler->pressingRunkey2 = false;
}