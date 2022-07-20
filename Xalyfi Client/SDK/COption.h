#pragma once
#include "../Utils/Logger.h"
#include "TextHolder.h"
#include <stdint.h>

class C_Option {
	char pad_0000[256];  //0x0000
public:
	TextHolder optionName;       //0x0100
	TextHolder internalName;     //0x0120
	int32_t listPosition;  //0x0140
private:
	char pad_0144[12];  //0x0144
public:
	TextHolder translateName;  //0x0150
private:
	char pad_0170[112];  //0x0170
public:
	union {
		int32_t mini;  //0x01E0 for enums they are inverted
		float minf;    //0x01E0 for enums they are inverted
	};
	union {
		int32_t maxi;  //0x01E4 for enums they are inverted
		float maxf;    //0x01E4 for enums they are inverted
	};
	union {
		int32_t valuei;  //0x01E8
		float valuef;    //0x01E8
	};
	union {
		int32_t defaultValuei;  //0x01EC
		float defaultValuef;    //0x01EC
	};

private:
	char pad_01F0[88];  //0x01F0
public:
	static inline C_Option** optionList;

	static inline C_Option* getOptionByInternalName(C_Option** list, const char* InternalName) {
		for (uint16_t i = 1; i < 500; i++) {
			if (list[i] == nullptr)
				continue;
			if (!strcmp(list[i]->internalName.getText(), InternalName))
				return list[i];
		}
		return nullptr;
	}
	static inline C_Option* getOptionByName(C_Option** list, const char* Name) {
		for (uint16_t i = 1; i < 500; i++) {
			if (list[i] == nullptr)
				continue;
			if (!strcmp(list[i]->optionName.getText(), Name))
				return list[i];
		}
		return nullptr;
	}
	static inline C_Option* getOptionByTranslate(C_Option** list, const char* TranslateText) {
		for (uint16_t i = 1; i < 500; i++) {
			if (list[i] == nullptr)
				continue;
			if (!strcmp(list[i]->translateName.getText(), TranslateText))
				return list[i];
		}
		return nullptr;
	}

	static inline void printOptions(C_Option** list) {
		//for (uint16_t i = 1; i < 400; i++) {
		//for (uint16_t i = 1; i < 250; i++) {
		for (uint16_t i = 1; i < 500; i++) {
			if (list[i] == nullptr)
				continue;

			/*if (list[i + 1] != nullptr)  {
					game::sendClientChat("%d %d   %s  %d  %s\n%d %d   %s  %d  %s\n%d %d   %s  %d  %s", i, list[i]->listPosition, list[i]->optionName.getText(), list[i]->internalName.getText(), list[i]->translateName.getText(), i+1, list[i + 1]->listPosition, list[i + 1]->optionName.getText(), list[i + 1]->internalName.getText(), list[i + 1]->translateName.getText());
					i++;
				}
			 else*/
			logF("%d %d   %s  %d  %s", i, list[i]->listPosition, list[i]->optionName.getText(), list[i]->internalName.getText(), list[i]->translateName.getText());
		}
	}
};  //Size: 0x0248