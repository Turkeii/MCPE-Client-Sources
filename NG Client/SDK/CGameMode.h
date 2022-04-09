#pragma once

#include <stdint.h>
#include "../Memory/GameData.h"
#include "../Utils/HMath.h"
#include "CClientInstance.h"
#include "CEntity.h"

class C_GameMode {
private:
	virtual __int64 destructorGameMode();
	// Duplicate destructor
public:
	virtual __int64 startDestroyBlock(vec3i const & pos, unsigned char blockSide, bool & isDestroyedOut);
	virtual __int64 destroyBlock(vec3i *, unsigned char);
	virtual __int64 continueDestroyBlock(vec3i const &, unsigned char blockSide, bool & isDestroyedOut);
	virtual __int64 stopDestroyBlock(vec3i const &);
	virtual __int64 startBuildBlock(vec3i const &, unsigned char);
	virtual __int64 buildBlock(vec3i *, unsigned char);
	virtual __int64 continueBuildBlock(vec3i const &, unsigned char);
	virtual __int64 stopBuildBlock(void);
	virtual __int64 tick(void);

private:
	virtual __int64 getPickRange(__int64 const &, bool);
	virtual __int64 useItem(C_ItemStack &);
	virtual __int64 useItemOn(C_ItemStack &, vec3i const &, unsigned char, vec3 const &, C_Block const *);
	virtual __int64 interact(C_Entity &, vec3 const &);

public:
	virtual __int64 attack(C_Entity *);

private:
	virtual __int64 releaseUsingItem(void);

public:
	virtual void setTrialMode(bool);
	virtual bool isInTrialMode(void);

private:
	virtual __int64 registerUpsellScreenCallback(__int64);

public:
	C_Player *player;

	__int64 getDestroyBlockFace() {
		return *reinterpret_cast<__int64 *>(this + 0x1C);
	}
};