#pragma once

#include <stdint.h>

#include <string>

#include "../Memory/GameData.h"
#include "../Utils/HMath.h"
#include "CClientInstance.h"
#include "CEntity.h"

class C_GameMode {
private:
	virtual __int64 destructorGameMode();
	// Duplicate destructor
public:
	virtual __int64 startDestroyBlock(vec3_ti const &pos, unsigned char blockSide, bool &isDestroyedOut);
	virtual __int64 destroyBlock(vec3_ti *, unsigned char);
	virtual __int64 continueDestroyBlock(vec3_ti const &, unsigned char blockSide, bool &isDestroyedOut);
	virtual __int64 stopDestroyBlock(vec3_ti const &);
	virtual __int64 startBuildBlock(vec3_ti const &, unsigned char);
	virtual __int64 buildBlock(vec3_ti *, unsigned char);
	virtual __int64 continueBuildBlock(vec3_ti const &, unsigned char);
	virtual __int64 stopBuildBlock(void);
	virtual __int64 tick(void);

private:
	virtual __int64 getPickRange(__int64 const &, bool);
	virtual __int64 useItem(__int64 &);
	virtual __int64 useItemOn(__int64 &, vec3_ti const &, unsigned char, vec3_t const &, __int64 const *);
	virtual __int64 interact(C_Entity &, vec3_t const &);

public:
	virtual __int64 attack(C_Entity *);

private:
	virtual void releaseUsingItem(void);

public:
	virtual void setTrialMode(bool);
	virtual bool isInTrialMode(void);

private:
	virtual __int64 registerUpsellScreenCallback(__int64);

public:
	C_Player *player;

	int getMobType(C_Entity *entToCheck);
	/*   
returns what mob type an entity is.

0 = other
1 = player
2 = Monster
3 = Animal
4 = Item
//5 = Projectile



*/

private:
	std::vector<int> playerIds = {

		63,  //player

	};

	std::vector<int> passiveIds = {

		10,   //chicken
		11,   //cow
		12,   //pig
		13,   //sheep
		14,   //wolf
		15,   //villager
		16,   //mooshroom
		17,   //squid
		18,   //rabbit
		19,   //bat
		20,   //iron_golem
		21,   //snow_golem
		22,   //ocelot
		23,   //horse
		24,   //donkey
		25,   //mule
		26,   //skeleton_horse
		27,   //zombie_horse
		28,   //polar_bear
		29,   //llama
		30,   //parrot
		31,   //dolphin
		74,   //turtle
		75,   //cat
		108,  //pufferfish
		109,  //salmon
		111,  //tropicalfish
		112,  //cod
		113,  //panda
		115,  //villager_v2
		118,  //wandering_trader
		121,  //fox
		122,  //bee
		125,  //strider
		128,  //goat

	};

	std::vector<int> hostileIds = {

		32,   //zombie
		33,   //creeper
		34,   //skeleton
		35,   //spider
		36,   //zombie_pigman
		37,   //slime
		38,   //enderman
		39,   //silverfish
		40,   //cave_spider
		41,   //ghast
		42,   //magma_cube
		43,   //blaze
		44,   //zombie_villager
		45,   //witch
		46,   //stray
		47,   //husk
		48,   //wither_skeleton
		49,   //guardian
		50,   //elder_guardian
		52,   //wither
		53,   //ender_dragon
		54,   //shulker
		55,   //endermite
		57,   //vindicator
		58,   //phantom
		59,   //ravager
		104,  //evocation_illager
		105,  //vex
		110,  //drowned
		114,  //pillager
		116,  //zombie_villager_v2
		123,  //piglin
		124,  //hoglin
		126,  //zoglin
		127,  //piglin_brute

	};

	std::vector<int> otherIds = {

		61,   //armor_stand
		68,   //xp_bottle
		70,   //eye_of_ender_signal
		71,   //ender_crystal
		72,   //fireworks_rocket
		73,   //thrown_trident
		76,   //shulker_bullet
		77,   //fishing_hook
		79,   //dragon_fireball
		80,   //arrow
		81,   //snowball
		82,   //egg
		83,   //painting
		84,   //minecart
		85,   //fireball
		86,   //splash_potion
		87,   //ender_pearl
		88,   //leash_knot
		89,   //wither_skull
		90,   //boat
		91,   //wither_skull_dangerous
		93,   //lightning_bolt
		94,   //small_fireball
		95,   //area_effect_cloud
		96,   //hopper_minecart
		97,   //tnt_minecart
		98,   //chest_minecart
		100,  //command_block_minecart
		101,  //lingering_potion
		102,  //llama_spit
		103,  //evocation_fang
		106,  //ice_bomb
		107,  //balloon

	};

public:
	void survivalDestroyBlockHack(vec3_ti const &block, int face, bool &isDestroyedOut, bool isFirst);
};
