#include "Coordinates.h"


//+9
uintptr_t coordinateAddress = 0;
DWORD originalProtect;

Coordinates::Coordinates() : VisualModule("Coordinates", Vec2(10.f, 35.f), Vec2(50.f,40.f), mltext("Show your current coordinates.", "Affiche vos coordonees.")) {
	addBoolSetting(mltext("Show X: Y: Z:", "Montrer X: Y: Z:"), "showXYZ", showXYZ, &showXYZ);
	addBoolSetting(mltext("In the same line", "Dans la meme ligne"), "SameLine", sameLine, &sameLine);
	addBoolSetting(mltext("Display precise coordinates", "Extreme precision"), "Precise", precise, &precise);

	addFloatSetting(mltext("Scale", "Multiplicateur de taille"), "scale", scale, &scale, 0.5f, 1.5f);
	addColorSetting(mltext("Text Color", "Couleur du Texte"), "textColor", textColor, &textColor);
	addColorSetting(mltext("Background Color", "Couleur du Fond"), "backColor", backgroundColor, &backgroundColor);

	coordinateAddress = mem::FindSignature("74 0D 80 78 04 00 74 07 B0 01 48 83 C4 28 C3 32 C0 48 83 C4 28 C3");
	if (coordinateAddress == NULL) {
		Logf("Could not find the PositionDisableAddress for Coordinates module");
		return;
	}
	coordinateAddress += 9;

	VirtualProtect((void*)coordinateAddress, 1, PAGE_EXECUTE_READWRITE, &originalProtect);
	*(bool*)coordinateAddress = 0;
}
void Coordinates::onEject() {

	if (coordinateAddress != NULL)
		*(bool*)coordinateAddress = 1;

}


static char coordinateText[100] = { 0 };
void Coordinates::onRender() {
	if (game::localPlayer == 0)
		return;


	memset(coordinateText, 0, 100);
	if (!showXYZ) {
		Vec3 playerPosition = *game::localPlayer->getPos();
		playerPosition.y -= 1.62001f;



		if (sameLine) {
			size.x = RenderUtils::GetTextWidth(coordinateText, 1.04f * scale);
			size.y = RenderUtils::GetTextWidth("W.", 1.5f * scale);
			//	size.y += 6.f;
		}

		int x = (int)playerPosition.x;
		if (x < 0)
			x--;
		int y = (int)playerPosition.y;
		int z = (int)playerPosition.z;
		if (z < 0)
			z--;


		if (sameLine) {
			if (precise)
				sprintf(coordinateText, "%f    %f    %f", playerPosition.x, playerPosition.y, playerPosition.z);
			else
				sprintf(coordinateText, "%d    %d    %d", x, y, z);


			RenderUtils::RenderText(coordinateText, Vec2(pos.x + 3.f, pos.y), textColor.getColor(), 1.f * scale, textColor.opacity);
			size.x = RenderUtils::GetTextWidth(coordinateText, 1.f * scale) + 8.f;
			size.y = RenderUtils::GetTextWidth("W", 1.f * scale) + (4.f * scale);

			RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);
		}
		else {
			float fatness = 0.f;
			float gamer = 0.f;
			float cheight = RenderUtils::GetTextWidth("W", 1.f * scale) + (2.428f * scale);

			if (precise)
				sprintf(coordinateText, "%f\0", playerPosition.x);
			else
				sprintf(coordinateText, "%d\0", x);
			RenderUtils::RenderText(coordinateText, Vec2(pos.x + 3.f, pos.y), textColor.getColor(), 1.f * scale, textColor.opacity);
			gamer = RenderUtils::GetTextWidth(coordinateText, 1.f * scale);
			fatness = gamer;

			if (precise)
				sprintf(coordinateText, "%f\0", playerPosition.y);
			else
				sprintf(coordinateText, "%d\0", y);
			RenderUtils::RenderText(coordinateText, Vec2(pos.x + 3.f, pos.y + cheight), textColor.getColor(), 1.f * scale, textColor.opacity);
			gamer = RenderUtils::GetTextWidth(coordinateText, 1.f * scale);
			if (gamer > fatness) fatness = gamer;

			if (precise)
				sprintf(coordinateText, "%f\0", playerPosition.z);
			else
				sprintf(coordinateText, "%d\0", z);
			RenderUtils::RenderText(coordinateText, Vec2(pos.x + 3.f, pos.y + (cheight * 2)), textColor.getColor(), 1.f * scale, textColor.opacity);
			gamer = RenderUtils::GetTextWidth(coordinateText, 1.f * scale);
			if (gamer > fatness) fatness = gamer;



			size.x = fatness + 14.f;
			size.y = (cheight * 3) + (0.3f * scale);
			RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);
		}

	}
	else {
		Vec3 playerPosition = *game::localPlayer->getPos();
		playerPosition.y -= 1.62001f;



		if (sameLine) {
			size.x = RenderUtils::GetTextWidth(coordinateText, 1.04f * scale);
			size.y = RenderUtils::GetTextWidth("W.", 1.5f * scale);
			//	size.y += 6.f;
		}

		int x = (int)playerPosition.x;
		if (x < 0)
			x--;
		int y = (int)playerPosition.y;
		int z = (int)playerPosition.z;
		if (z < 0)
			z--;


		if (sameLine) {
			if (precise)
				sprintf(coordinateText, "X: %f    Y: %f    Z: %f", playerPosition.x, playerPosition.y, playerPosition.z);
			else
				sprintf(coordinateText, "X: %d    Y: %d    Z: %d", x, y, z);


			RenderUtils::RenderText(coordinateText, Vec2(pos.x + 3.f, pos.y), textColor.getColor(), 1.f * scale, textColor.opacity);
			size.x = RenderUtils::GetTextWidth(coordinateText, 1.f * scale) + 8.f;
			size.y = RenderUtils::GetTextWidth("W", 1.f * scale) + (4.f * scale);

			RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);
		}
		else {
			float fatness = 0.f;
			float gamer = 0.f;
			float cheight = RenderUtils::GetTextWidth("W", 1.f * scale) + (2.428f * scale);

			if (precise)
				sprintf(coordinateText, "X: %f\0", playerPosition.x);
			else
				sprintf(coordinateText, "X: %d\0", x);
			RenderUtils::RenderText(coordinateText, Vec2(pos.x + 3.f, pos.y), textColor.getColor(), 1.f * scale, textColor.opacity);
			gamer = RenderUtils::GetTextWidth(coordinateText, 1.f * scale);
			fatness = gamer;

			if (precise)
				sprintf(coordinateText, "Y: %f\0", playerPosition.y);
			else
				sprintf(coordinateText, "Y: %d\0", y);
			RenderUtils::RenderText(coordinateText, Vec2(pos.x + 3.f, pos.y + cheight), textColor.getColor(), 1.f * scale, textColor.opacity);
			gamer = RenderUtils::GetTextWidth(coordinateText, 1.f * scale);
			if (gamer > fatness) fatness = gamer;

			if (precise)
				sprintf(coordinateText, "Z: %f\0", playerPosition.z);
			else
				sprintf(coordinateText, "Z: %d\0", z);
			RenderUtils::RenderText(coordinateText, Vec2(pos.x + 3.f, pos.y + (cheight * 2)), textColor.getColor(), 1.f * scale, textColor.opacity);
			gamer = RenderUtils::GetTextWidth(coordinateText, 1.f * scale);
			if (gamer > fatness) fatness = gamer;



			size.x = fatness + 14.f;
			size.y = (cheight * 3) + (0.3f * scale);
			RenderUtils::FillRectangle(Rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y), backgroundColor.getColor(), backgroundColor.opacity);
		}

	}
	
	RenderUtils::FlushText();
}
