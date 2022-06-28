#include "CBlockLegacy.h"

#include "../Memory/GameData.h"
#include "../Utils/Logger.h"
#include "../Utils/Utils.h"
C_Block* C_BlockSource::getBlock(const vec3_ti& block) {
	using getBlock_t = C_Block*(__fastcall*)(C_BlockSource*, const vec3_ti&);
	static getBlock_t getBlock = reinterpret_cast<getBlock_t>(FindSignature("48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 48 8B DA 8B 4A"));
	return getBlock(this, block);
}
C_BlockActor* C_BlockSource::getBlockEntity(const vec3_ti& block) {
	using getBlockEntity_t = C_BlockActor*(__fastcall*)(C_BlockSource*, const vec3_ti&);
	static getBlockEntity_t getBlockEntity = reinterpret_cast<getBlockEntity_t>(FindSignature("40 55 56 57 48 83 EC ?? 8B 02"));
	return getBlockEntity(this, block);
}

bool C_BlockSource::rayTraceBlocks(vec3_t& start, vec3_t& end, void* ent) {
	using rayTrace_t = RayTraceResult*(__fastcall*)(C_BlockSource* _this, RayTraceResult* hitres, vec3_t& start, vec3_t& end, bool idk1, bool idk2, int idkInt, bool idk3, bool idk4, void* ent);
	static rayTrace_t rayTrace = reinterpret_cast<rayTrace_t>(FindSignature("48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 70 ?? 0F 29 78 ?? 44 0F 29 40 ?? 44 0F 29 88 ?? ?? ?? ?? 44 0F 29 90 ?? ?? ?? ?? 44 0F 29 98 ?? ?? ?? ?? 44 0F 29 A0 ?? ?? ?? ?? 44 0F 29 A8 ?? ?? ?? ?? 44 0F 29 B0 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4D 8B D9"));
	if (rayTrace != 0) {
		RayTraceResult* res = new RayTraceResult();
		RayTraceResult yes = *rayTrace(this, res, start, end, false, false, 200, true, false, ent);
		delete res;
		return true;
	}
	return false;
}
C_Block* C_BlockSource::getLiquidBlock(const vec3_ti& block) {
	using getLiquidBlock_t = C_Block*(__fastcall*)(C_BlockSource*, const vec3_ti&);  // E8 41 7D 6A 01 48 8B C8 48 8B 46 10
	static getLiquidBlock_t getLiquidBlock = Utils::FuncFromSigOffset<getLiquidBlock_t>(FindSignature("E8 ?? ?? ?? ?? 65 48 8B 0C 25 ?? ?? ?? ??"), 1);
	return getLiquidBlock(this, block);  // E8 41 7D 6A ?? ?? ?? ?? ?? ?? ?? ??
}
bool C_BlockLegacy::getCollisionShape(AABB* collShapeOut, C_Block* block, C_BlockSource* blockSource, const vec3_ti* pos, C_Entity* actor) {
	return Utils::CallVFunc<5, bool, AABB*, C_Block*, C_BlockSource*, const vec3_ti*, C_Entity*>(this, collShapeOut, block, blockSource, pos, 0);
}
void C_BlockLegacy::liquidGetFlow(vec3_t* flowOut, C_BlockSource* reg, const vec3_ti* pos) {
	using liquid_getFlow_t = int(__fastcall*)(C_BlockLegacy*, vec3_t*, C_BlockSource*, const vec3_ti*);
	static liquid_getFlow_t liquid_getDepth = Utils::FuncFromSigOffset<liquid_getFlow_t>(FindSignature("E8 ? ? ? ? 48 8B 4C 24 ? F3 0F 10 01"), 1);

	liquid_getDepth(this, flowOut, reg, pos);
}

bool C_BlockLegacy::hasWater(C_BlockSource* reg, const vec3_ti& pos) {
	if (this->material->isLiquid) {
		return !this->material->isSuperHot;
	}

	auto liquidBlock = reg->getLiquidBlock(pos)->toLegacy();
	return this != liquidBlock && liquidBlock->material->isLiquid && !liquidBlock->material->isSuperHot;
}