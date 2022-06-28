#pragma once

#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "TextHolder.h"
//#include "Tag.h"

class C_Material {
public:
	int type;  // 5 for water, 6 for lava
	bool isFlammable;
	bool isNeverBuildable;
	bool isAlwaysDestroyable;
	bool isReplaceable;
	bool isLiquid;  // 0x0008
private:
	char pad2[0x3];  // 0x009
public:
	float translucency;  // 0x00C
	bool isBlockingMotion;
	bool isBlockingPrecipitation;
	bool isSolid;
	bool isSuperHot;
	float color[4];
};

class C_Entity;
class C_Block;
class C_BlockSource;

class RayTraceResult {  // Some of these aren't set by some functions
public:
	vec3_t startPos;
	vec3_t relativeEndPos;
	uint32_t hitType;  // 0 is block, 1 is actor, 3 is air
	uint32_t blockFace;
	vec3_ti blockPos;
	vec3_t blockHitPos;  // If no block is found it just extends to the max ray position
	uintptr_t someActorHitPointer;
	uintptr_t someOtherActorHitPointer;
	uint32_t actorThingy;  // Could contain ids or something, 0xFFFFFFFF when not facing an actor
private:
	char idk[0x4];

public:
	bool isHittingLiquid;
	uint8_t liquidBlockFace;  // If the liquid were a solid block, what block face would it be
private:
	char nothing[0x2];

public:
	vec3_ti liquidBlockPos;
	vec3_t liquidBlockHitPos;   // Full of zeroes if there is no liquid block
	bool isExtendedBlockHit;  // Is the bedrock bridge mechanic thingy focusing a block
private:
	char pad[0x3];

public:
	RayTraceResult() {
		memset(this, 0x0, sizeof(RayTraceResult));
	}
};

class C_BlockLegacy {
public:
	uintptr_t** Vtable;         // 0x0000
	class TextHolder tileName;  // 0x0008
private:
	char pad_0028[8];  // 0x0028
public:
	class TextHolder name;  // 0x0030
private:
	char pad_0050[136];  // 0x0050
public:
	class C_Material* material;  // 0x00D8
private:
	char pad_00E0[108];  // 0x00E0
public:
	short blockId;  // 0x014C

	int liquidGetDepth(C_BlockSource*, const vec3_ti* pos);
	void liquidGetFlow(vec3_t* flowOut, C_BlockSource*, const vec3_ti* pos);
	bool getCollisionShape(AABB* collShapeOut, C_Block* block, C_BlockSource* blockSource, const vec3_ti* pos, C_Entity* actor);
	bool hasWater(C_BlockSource*, const vec3_ti& pos);
};

class C_Block {
public:
	uint8_t data;  // 0x8

private:
	char pad[0x7];

public:
	C_BlockLegacy* blockLegacy;  // 0x10

	inline C_BlockLegacy* toLegacy() { return blockLegacy; }

	virtual ~C_Block();
	virtual int getRenderLayer();
};

class CompoundTag;

class C_BlockActor {
private:
	virtual void destructor();
	virtual __int64 load(__int64&, CompoundTag*, __int64&);

public:
	virtual bool save(CompoundTag*);
};

class C_BlockSource {
public:
	C_Block* getBlock(const vec3_ti& block);
	C_BlockActor* getBlockEntity(const vec3_ti& block);
	C_Block* getLiquidBlock(const vec3_ti& block);
	bool rayTraceBlocks(vec3_t& start, vec3_t& end, void* ent = nullptr);
};