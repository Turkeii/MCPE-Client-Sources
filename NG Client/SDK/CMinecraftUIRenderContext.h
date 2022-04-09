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
	virtual float getLineLength(TextHolder* str, float textSize);//bool unknown
	virtual float getLineHeight();
};

struct TextMeasureData {
	float textSize;
	int idk;
	bool bool1;
	bool bool2;
};

class NinesliceInfo {  // how the fuck did onix find what goes in this
private:
	char pad_0x0000[0xFF];  //0x0000
};

class C_MinecraftUIRenderContext {
private:
	float _[140];

public:
	virtual ~C_MinecraftUIRenderContext();
	virtual float getLineLength(C_Font* font, TextHolder* str, float textSize);//bool unknown
	virtual float getTextAlpha();
	virtual void setTextAlpha(float alpha);
	virtual __int64 drawDebugText(const float* pos, TextHolder* text, float* color, float alpha, unsigned int textAlignment, const float* textMeasureData, const void* caretMeasureData);
	virtual __int64 drawText(C_Font* font, const float* pos, TextHolder* text, float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const uintptr_t* caretMeasureData);
	virtual void flushText(float timeSinceLastFlush);                       // time used for ticking the obfuscated text
	virtual __int64 drawImage(C_TexturePtr* texturePtr, vec2& ImagePos, vec2& ImageDimension,__int64& a4,vec2& idk);  // didnt bother putting in the parameters
	virtual void drawNineslice(C_TexturePtr* const& texturePtr, NinesliceInfo NinesliceInfo);
	virtual __int64 flushImages(MC_Color& color, __int64 flushImageAddr, __int64 hashedString);
	virtual void beginSharedMeshBatch(uintptr_t ComponentRenderBatch);
	virtual void endSharedMeshBatch(float timeSinceLastFlush);
	virtual void drawRectangle(const float* pos, const float* color, float alpha, int lineWidth);  // line width is guessed
	virtual auto drawRect(vec4 position, MC_Color& colour, float alpha, int lineWidth) -> void{};
	virtual void fillRectangle(const float* pos, const float* color, float alpha);
	virtual void increaseStencilRef();
	virtual void decreaseStencilRef();
	virtual void resetStencilRef();
	virtual void fillRectangleStencil(const float* pos);
	virtual void enableScissorTest(const float* pos);
	virtual void disableScissorTest();
	virtual void setClippingRectangle(const float* pos);
	virtual void setFullClippingRectangle();
	virtual void saveCurrentClippingRectangle();
	virtual void restoreSavedClippingRectangle();
	virtual int getFullClippingRectangle();
	virtual void updateCustom(uintptr_t a1);
	virtual void renderCustom(uintptr_t a1, int a2, const float* pos);
	virtual void cleanup();
	virtual void removePersistentMeshes();
	virtual C_TexturePtr* getTexture(C_TexturePtr* ptr, C_FilePath& path);
	virtual int getZippedTexture(C_TexturePtr* Path, C_TexturePtr* ResourceLocation, bool a3);
	virtual void unloadTexture(C_TexturePtr* ResourceLocation);
	virtual int getUITextureInfo(C_TexturePtr* ResourceLocation, bool a2);
	virtual void touchTexture(C_TexturePtr* ResourceLocation);
	virtual int getMeasureStrategy(vec2 const&);
	virtual void snapImageSizeToGrid(vec2 const&);
	virtual void snapImagePositionToGrid(vec2 const&);
	virtual void notifyImageEstimate(unsigned long);
};