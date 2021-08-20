#include "MCUtilsClass.h"
#include <string.h>




Text::Text() {}
Text::Text(const char* text, bool malloc) {
	textLength = strlen(text);
	reservedLenght = textLength | 0xF;

	if (textLength < 16)
		memcpy(inlineText, text, textLength);
	else if (!malloc)
		//top 10 anime betreyal
		pText = (char*)text;
	else {
		pText = new char[reservedLenght];
		memset(pText, 0, reservedLenght);
		memcpy(pText, text, textLength);
	}
}
char* Text::getText() {
	if (reservedLenght < 16)
		return this->inlineText;
	else
		return this->pText;
}
void Text::setText(const char* text, bool malloc) {
	textLength = strlen(text);
	reservedLenght = textLength | 0xF;

	if (textLength < 16)
		memcpy(inlineText, text, 16);
	else if (!malloc) 
		//top 10 anime betreyal
		pText = (char*)text;
	else {
		pText = new char[reservedLenght];
		memset(pText, 0, reservedLenght);
		memcpy(pText, text, textLength);
	}

		
}


void Text::zeroMemory() {
	memset(this, 0, sizeof(Text));
}






NewChatMessage::NewChatMessage(Text TheMessage, Text Username, Text XUID) {
	memcpy(&username, &Username, sizeof(Text));
	memcpy(&xuid, &XUID, sizeof(Text));
	memcpy(&xuid2, &xuid, sizeof(Text));
	memcpy(&message, &TheMessage, sizeof(Text));
}




MC_Color::MC_Color() {
	this->r = 1.f;
	this->g = 1.f;
	this->b = 1.f;
	this->a = 1.f;
}
MC_Color::MC_Color(const MC_Color& other) {
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	this->a = other.a;
}
MC_Color::MC_Color(const float* floatArray) {
	this->arr[0] = floatArray[0];
	this->arr[1] = floatArray[1];
	this->arr[2] = floatArray[2];
	this->arr[3] = floatArray[3];
}
MC_Color::MC_Color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
MC_Color::MC_Color(const int r, const int g, const int b, const int a) {
	this->r = r / 255.0f;
	this->g = g / 255.0f;
	this->b = b / 255.0f;
	this->a = a / 255.0f;
}