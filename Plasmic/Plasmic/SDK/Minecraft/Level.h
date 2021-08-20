#pragma once
#include "MCUtilsClass.h"
#include "../../Utils/PlasmicMath.h"


class Dimension {
#ifndef _1_16_40
	char pad_0008[16]; //0x0008
public:
	class Text dimensionName; //0x0018
private:
	char pad_0038[16]; //0x0038
public:
	class Level* level; //0x0048
private:
	char pad_0050[8]; //0x0050
public:
	class BlockSource* blockSource; //0x0058
private:
	char pad_0060[152]; //0x0060
public:
	class chunkSource* chunkSource; //0x00F8
private:
	char pad_0100[8]; //0x0100
public:
	class Weather* Weather; //0x0108
private:
	char pad_0110[360]; //0x0110

#else
	char pad_0008[16]; //0x0008
public:
	class Text dimensionName; //0x0018
	class MultiPlayerLevel* multiplayerLevel; //0x0038
private:
	char pad_0040[8]; //0x0040
public:
	class BlockSource* blockSource; //0x0048
private:
	char pad_0050[168]; //0x0050
public:
	class Weather* Weather; //0x00F8
public:
	char pad_0100[288]; //0x0100
#endif

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void onBlockChanged(BlockSource* blocksource, BlockPos* pos, uint32_t idk1, const Block* oldBlock, const Block* newBlock, uint8_t idk2, struct ActorBlockSyncMessage* idk3);
	virtual void onBrightnessChanged(BlockSource* blocksource, BlockPos* pos);
	virtual void Function6();
	virtual void netEventCallback_Handle();
	virtual void Function8();
	virtual void onBlockEvent(BlockSource* blocksource, int idk1, int idk2, int idk3, int idk4, int idk5);
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void onChunkLoaded(class ChunkSource* chunksource, class LevelChunk* idk2);
	virtual void Function23();
	virtual void onLevelDestruction(const Text* idk);
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void init();
	virtual void tick();
	virtual void tickRedstone();
	virtual void createGenerator();
	virtual void upgradeLevelChunk(class ChunkSource* chunksource, class levelChunk* levelchunk);
	virtual void fixWallChunk(class ChunkSource* chunksource, class levelChunk* levelchunk);
	virtual void Function39();
	virtual void Function40();
	virtual void getBrightnessDependentFogColor(MC_Color color, float idk);
	virtual void getMaxFogEnd();
	virtual void Function43();
	virtual void Function44();
	virtual void getEnchantSlot();
	virtual void getDefaultBiome();
	virtual void Function47();
	virtual void Function48();
	virtual void getBlockPosition();
	virtual void Function50();
	virtual void Function51();
	virtual void getClearColorScale();
	virtual void Function53();
	virtual void isDay();
	virtual void getShadowRadius(float);
	virtual void getSunIntensity(float idk1, const Vec3* pos, float idk2);
	virtual void Function57();
	virtual void translatePosAcrossDimension(const Vec3* pos, int dimensionID);
	virtual void sendBroadcast(const class Packet*, const class Player*);
	virtual void is2DPositionRelevantForPlayer(const BlockPos* pos, class LocalPlayer* player);
	virtual void isEntityRelevantForPlayer(const BlockPos* pos, class LocalPlayer* player);
	virtual void getLightTextureImageBuilder();
	virtual void getBrightnessRamp();
	virtual void startLeaveGame();
	virtual void _createChunkBuildOrderPolicy();
	virtual void _upgradeOldLimboEntity(class CompoundTag*, int LimboEntitiesVersion);//enum LimboEntitiesVersion);
	//virtual void _wrapStorageForVersionCompatibility(class std::unique_ptr<class ChunkSource, struct std::default_delete<class ChunkSource>> youFindOut, enum StorageVersion);
	virtual void _wrapStorageForVersionCompatibility();
	virtual void Function68();
	virtual void Function69();
	virtual void Function70();
	virtual void Function71();
	virtual void deserialize(const class CompoundTag*);
	virtual void serialize(class CompoundTag*);
	virtual void Function74();
	virtual void Function75();

};




class MultiPlayerLevel {
public:
	char pad_0008[72]; //0x0008
	uint64_t listStart; //0x0050
	uint64_t listEnd; //0x0058
	char pad_0060[32]; //0x0060

	/* VTable Functions (Not currently defined) */

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
public:

	inline class Actor* get(size_t idx) {
		if (idx >= getListSize())
			return 0;
		return *reinterpret_cast<class Actor**>(listStart + (idx * sizeof(uintptr_t)));
	};
	inline size_t getListSize() {
		return (listEnd - listStart) / sizeof(uintptr_t);
	};
};


