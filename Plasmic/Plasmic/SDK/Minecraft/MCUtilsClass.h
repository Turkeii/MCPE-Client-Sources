#pragma once

class Text {
public:

	union {
		char inlineText[16]; //0x0000 
		char* pText; //0x0000 
	};

	size_t textLength; //0x0010 
	size_t reservedLenght; //0x0018

	Text();
	Text(const char* text, bool malloc = false);
	char* getText();
	void setText(const char* text, bool malloc = false);
	void zeroMemory();
};

class NewChatMessage {
public:
	Text username; //0x0000
	Text message; //0x0020
private:
	char pad_0040[32]; //0x0040
public:
	Text xuid; //0x0060
	Text xuid2; //0x0080


	NewChatMessage(Text TheMessage, Text Username, Text XUID);

}; //Size: 0x0638



struct MC_Color {
	union {
		struct {
			float r, g, b, a;
		};
		float arr[4];
	};


	MC_Color();
	MC_Color(const MC_Color& other);
	MC_Color(const float* floatArray);
	MC_Color(float r, float g, float b, float a = 1.f);
	MC_Color(const int r, const int g, const int b, const int a = 255);

	bool operator == (MC_Color colour) { return this->r == colour.r && this->g == colour.g && this->b == colour.b; };
	bool operator != (MC_Color colour) { return this->r != colour.r || this->g != colour.g || this->b != colour.b; };
};