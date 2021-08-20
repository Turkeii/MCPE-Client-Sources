#include "Image.h"
#include <cstdio>
#include <Windows.h>
#include <fstream>

#include "RenderUtils.h"
#include "Logger.h"

int8_t Image::imgState = 0;
std::vector<Image*> Image::images;

void Image::DeInitImages() {
	for (uint16_t i = 0; i < Image::images.size(); i++) 
		if (Image::images[i] != nullptr) {

			for (int x = 0; x < Image::images[i]->width; x++) {
				delete[] Image::images[i]->StoredImage[x];
			}
			delete[] Image::images[i]->StoredImage;
			if (Image::images[i]->shouldDelete)
				delete Image::images[i];
			Image::images[i] = nullptr;
		}
	
}


Image::Image(const char* FileName, bool ShouldDelete) {
	if (imgState == -1)
		return;

	//getting the path
	char filepath[500] = { 0 };
	sprintf(filepath, "%s\\..\\RoamingState\\Plasmic\\Images", getenv("LOCALAPPDATA"));

	DWORD attr = GetFileAttributesA(filepath);
	if (attr == INVALID_FILE_ATTRIBUTES) {
		imgState = -1;
		return;
	} else if (!(attr & FILE_ATTRIBUTE_DIRECTORY)) {
		imgState = -1;
		return;
	}

	sprintf(filepath + strlen(filepath), "\\%s", FileName);
	std::fstream img(filepath, std::ios::binary | std::ios::in);
	if (!img.is_open())
		return;

	//get image dimensions
	img.read((char*)&width, 4);
	img.read((char*)&height, 4);
	
	//init image array
	StoredImage = new MC_Color*[width];
	for (int i = 0; i < width; i++) 
		StoredImage[i] = new MC_Color[height];
	
	//loading image
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			img.read((char*)&StoredImage[x][y], sizeof(MC_Color));
		}
	}

	img.close();
	shouldDelete = ShouldDelete;
	Image::images.push_back(this);
	canUseImage = true;
}


void Image::DrawImage(Vec2 pos, Vec2 size, float opacity) {
	if (!canUse())
		return;


	float pixelSizeX, pixelSizeY;
	if (size.x == 0 || size.y == 0) {
		pixelSizeX = 1.f;
		pixelSizeY = 1.f;
	} else {
		pixelSizeX = size.x / width;
		pixelSizeY = size.y / height;
	}

	if (opacity == 1.f) {
		Rect pixelPos;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (StoredImage[x][y].a == 0.f)
					continue;
				pixelPos.x = pos.x + (x * pixelSizeX);
				pixelPos.y = pos.y + (y * pixelSizeY);
				pixelPos.z = pixelPos.x + pixelSizeX;
				pixelPos.w = pixelPos.y + pixelSizeY;

				RenderUtils::FillRectangle(pixelPos, StoredImage[x][y], StoredImage[x][y].a);
			}
		}

	} else {
		Rect pixelPos;
		for (int x = 0; x < width - 1; x++) {
			for (int y = 0; y < height - 1; y++) {
				if (StoredImage[x][y].a == 0.f)
					continue;
				pixelPos.x = pos.x + (x * pixelSizeX);
				pixelPos.y = pos.y + (y * pixelSizeY);
				pixelPos.z = pixelPos.x + pixelSizeX;
				pixelPos.w = pixelPos.y + pixelSizeY;

				RenderUtils::FillRectangle(pixelPos, StoredImage[x][y], StoredImage[x][y].a * opacity);
			}
		}
	}

	return;
}