#pragma once
#include <cstdint>
#include <vector>

#include "../SDK/Minecraft/MCUtilsClass.h"
#include "PlasmicMath.h"

class Image {
	static int8_t imgState;
	bool canUseImage = false;
	bool shouldDelete = false;

	MC_Color** StoredImage = nullptr;

	static std::vector<Image*> images;
public:
	bool canUse() { return (imgState != -1) && canUseImage && StoredImage != nullptr; }

	int width = 0;
	int height = 0;

	//the name of the file relative to the Images folder
	//please if you do new/malloc pass true k bye
	Image(const char* FileName, bool ShouldDelete = false);
	MC_Color* getPixel(int x, int y) { return &StoredImage[x][y]; }


	/*will draw the image at the location
	* if the size is 0 it will take the image's size
	*/
	void DrawImage(Vec2 Position, Vec2 Size, float opacity = 1.f);

	static void DeInitImages();
};

