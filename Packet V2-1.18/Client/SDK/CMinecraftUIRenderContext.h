#pragma once

#include "TextHolder.h"
#include "../Utils/HMath.h"

struct MC_Color;

class C_FilePath {
private:
	char pad_0x0[0x8];    //0x0000
	TextHolder filePath;  //0x0008
public:
	C_FilePath(std::string filePath) {
		memset(this, 0, sizeof(C_FilePath));
		this->filePath.setText(filePath);
	};
};

class C_TexturePtr {
private:
	char pad_0x0[0x18];  //0x0000
public:
	TextHolder filePath;  //0x0018
private:
	char pad_0x0038[0x20];  //0x0038
};

class C_Font {
private:
	virtual void destructorFont();
	virtual void unk1();
	virtual void unk2();
	virtual void unk3();
	virtual void unk4();
	virtual void unk5();

public:
	virtual float getLineLength(TextHolder* str, float textSize, bool unknown);
	virtual float getLineHeight();
};

struct TextMeasureData {
public:
	TextMeasureData(float* size, bool showShadow) {
		this->textSize = *size;  // Okay not useless ;-;
		this->showShadow = showShadow;
		this->idfkwhatthisiscalled = 0;
		this->idfkWhatThisIs = false;
	};

public:
	float textSize;
	int idfkwhatthisiscalled;
	bool showShadow;
	bool idfkWhatThisIs;
};

class C_MinecraftUIRenderContext {
private:
	float _[140];

public:
	virtual ~C_MinecraftUIRenderContext();
	virtual float getLineLength(C_Font* font, TextHolder* str, float textSize, bool unknown);
	virtual float getTextAlpha();
	virtual void setTextAlpha(float alpha);
	virtual __int64 drawDebugText(const float* pos, TextHolder* text, float* color, float alpha, unsigned int textAlignment, const float* textMeasureData, const void* caretMeasureData);
	virtual __int64 drawText(C_Font* font, const float* pos, TextHolder* text, float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const uintptr_t* caretMeasureData);
	virtual void flushText(float timeSinceLastFlush);                       // time used for ticking the obfuscated text
	virtual __int64 drawImage(const C_TexturePtr* texturePtr, vec2_t const& ImagePos, vec2_t const& ImageDimension, vec2_t const& idk, vec2_t const& idk2);  // didnt bother putting in the parameters
	virtual __int64 drawNinesliceNOTIMPLEMENTED();
	virtual __int64 flushImages(MC_Color& color, __int64 flushImageAddr, class HashedString& hashedString);
	virtual __int64 beginSharedMeshBatchNOTIMPLEMENTED();
	virtual __int64 endSharedMeshBatchNOTIMPLEMENTED();
	virtual void drawRectangle(const float* pos, const float* color, float alpha, int lineWidth);  // line width is guessed
	virtual void fillRectangle(const float* pos, const float* color, float alpha);
	virtual void increaseStencilRef();
	virtual void decreaseStencilRef();
	virtual void resetStencilRef();
	virtual void fillvec4_tangleStencil(vec4_t position);
	virtual void enableScissorTest(vec4_t position);
	virtual void disableScissorTest();
	virtual void setClippingvec4_tangle(vec4_t position);
	virtual void setFullClippingvec4_tangle();
	virtual void saveCurrentClippingvec4_tangle();
	virtual void restoreSavedClippingvec4_tangle();
	virtual int getFullClippingvec4_tangle();
	virtual void updateCustom(uintptr_t a1);
	virtual void renderCustom(uintptr_t a1, int a2, vec4_t position);
	virtual void cleanup();
	virtual void removePersistentMeshes();
	virtual C_TexturePtr* getTexture(C_TexturePtr* ptr, C_FilePath& path);
	// There are a few more functions but didnt bother
};
