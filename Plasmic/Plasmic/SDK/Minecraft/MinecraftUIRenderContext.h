#pragma once
#include "MCUtilsClass.h"
#include "ClientInstance.h"
#include "../../Utils/PlasmicMath.h"


class MinecraftUIRenderContext {
public:
	virtual void Constructor(void);
	virtual float getLineLength(struct BitmapFont* font, class Text* text, float textSize, bool unknown);
	virtual float getTextAlpha();
	virtual void setTextAlpha(float alpha);
	virtual __int64 drawDebugText(const float* pos, class Text* text, float* color, float alpha, unsigned int textAlignment, const float* textMeasureData, const void* caretMeasureData);
	virtual __int64 drawText(struct BitmapFont* font, struct Rect* position, class Text* text, MC_Color colour, float alpha, unsigned int textAlignment, const float* textMeasureData, const uintptr_t* caretMeasureData);
	virtual void flushText(float timeSinceLastFlush);
	virtual __int64 drawImageNOTIMPLEMENTED();
	virtual __int64 drawNinesliceNOTIMPLEMENTED();
	virtual __int64 flushImagesNOTIMPLEMENTED();
	virtual __int64 beginSharedMeshBatchNOTIMPLEMENTED();
	virtual __int64 endSharedMeshBatchNOTIMPLEMENTED();
	virtual void drawRectangle(struct Rect position, MC_Color colour, float alpha, int lineWidth);
	virtual void fillRectangle(struct Rect position, MC_Color colour, float alpha);
};
