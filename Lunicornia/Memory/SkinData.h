#pragma once
struct SkinData {
public:
	char pad_0x0000[0x4]; //0x0000
	unsigned int SkinWidth; //0x0004 
	unsigned int SkinHeight; //0x0008 
	char pad_0x000C[0x4]; //0x000C
	void* skinData; //0x0010 
	size_t skinSize; //0x0018 
};