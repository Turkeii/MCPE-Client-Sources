#pragma once
#include "MCUtilsClass.h"
#include <cstdint>

class Material {
public:
	int32_t type; //0x0000
	char pad_0004[32]; //0x0004
}; //Size: 0x0040

class BlockLegacy {
public:
	Text tileName; //0x0008
private:
	char pad_0028[8]; //0x0028
public:
	Text name; //0x0030
private:
	char pad_0050[8]; //0x0050
public:
	Text isFrom; //0x0058
private:
	char pad_0078[8]; //0x0078
public:
	Text fullname; //0x0080
private:
	char pad_00A0[56]; //0x00A0
public:
	Material* material; //0x00D8
private:
	char pad_00E0[16]; //0x00E0
public:
	Text itemGroup; //0x00F0
private:
	char pad_0110[2]; //0x0110
public:
	bool obstructChest; //0x0112
private:
	char pad_0113[29]; //0x0113
public:
	float handBreakTime; //0x0130
private:
	char pad_0134[20]; //0x0134
public:
	int64_t id; //0x0148


	virtual void Function0() {}
	virtual void getStateFromLegacyData() {}
	virtual void newBlockEntity() {}
	virtual void getNextBlockPermutation() {}
	virtual void Function4() {}
	virtual void getCollisionShape() {}
	virtual bool isObstructingChest() { return false; }
	virtual void randomlyModifyPosition2() {}
	virtual void randomlyModifyPosition() {}
	virtual void addAABB() {}
	virtual void getAABB() {}
	virtual void addCollisionShapes() {}
	virtual void getOutline() {}
	virtual void getLiquidClipVolume() {}
	virtual void Function14() {}
	virtual void Function15() {}
	virtual void Function16() {}
	virtual void Function17() {}
	virtual void Function18() {}
	virtual void canProvideSupport() {}
	virtual void canConnect() {}
	virtual void getConnectedDirections() {}
	virtual void Function22() {}
	virtual void Function23() {}
	virtual void Function24() {}
	virtual bool isBlockingWater() { return false; }

}; //Size: 0x0640

class BlockSource {
public:
	char pad_0000[64]; //0x0000
}; //Size: 0x0040

class Block {
public:
	int64_t blockVariation; //0x0008
	class BlockLegacy* blockLegacy; //0x0010
private:
	char pad_0018[88]; //0x0018
	virtual void Function0();
public:
	//it should be an enum but I have no info on what are the layers.
	virtual int getRenderLayer();
}; //Size: 0x0070

class ChunkViewSource {};
class ChunkSource {};