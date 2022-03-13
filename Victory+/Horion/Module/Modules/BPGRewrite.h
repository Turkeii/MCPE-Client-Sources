#pragma once
#include "Module.h"

class BPGRewrite : public IModule {
private:
	SettingEnum dmgEnum;
	static int constexpr dmg_nukkit = 0;
	static int constexpr dmg_2b2e = 1;
	static int constexpr dmg_vanilla = 2;  // TODO: Implement ray tracing
	static int constexpr dmg_java = 3;

	SettingEnum destroyEnum;
	static int constexpr destroy_check = 0;
	static int constexpr destroy_all = 1;
	static int constexpr destroy_onlyplaced = 2;  // TODO

	bool autoPlace = true;
	float minDistance = 0.f;
	float maxDistance = 7.f;
	float wallRange = 2.f;

	int maxSelfDmg = 6;  // Player damage
	int minDamage = 4;   // Target damage
	int minHealth = 8;
	bool suicide = false;    // TODO
	bool instakill = false;  // TODO

	int placeDelay = 2;
	int breakDelay = 0;

	SettingEnum rotations;
	static int constexpr rotations_off = 0;
	static int constexpr rotations_normal = 1;
	static int constexpr rotations_antikick = 2;  // 2b2e
	static int constexpr rotations_lockview = 3;  // For the funni if you know what I mean

	bool flash = false;
	bool rightClick = false;
	bool autoSelect = false;

	bool renderPlaced = false;

	bool botCheck = false;

	static float constexpr maxdot = 0.f;  // dot

	std::vector<C_Entity*> toBreak;
	std::vector<vec3_ti> toPlace;

	int previousSlot = -1;

	struct CrystalRenderHolder {
		float enemyDmg;
		float playerDmg;
		vec3_ti pos;
	} latestCrystal;
	bool renderCrystal;

public:
	BPGRewrite() : IModule(0x0, Category::COMBAT, "CrystalAuraBPG but better") {
		dmgEnum = SettingEnum(this)
					  .addEntry(EnumEntry("Nukkit", dmg_nukkit))
					  .addEntry(EnumEntry("2b2e", dmg_2b2e))
					  .addEntry(EnumEntry("Vanilla", dmg_vanilla))
					  .addEntry(EnumEntry("Java", dmg_java));
		registerEnumSetting("Mode", &dmgEnum, dmg_2b2e);

		destroyEnum = SettingEnum(this)
						  .addEntry(EnumEntry("Check", destroy_check))
						  .addEntry(EnumEntry("All", destroy_all));
		registerEnumSetting("Destroy Mode", &destroyEnum, destroy_check);
	//	registerBoolSetting("Bot Check", &botCheck, true);

	//	registerBoolSetting("Auto Place", &autoPlace, false);
	//	registerFloatSetting("Min Distance", &minDistance, 0.f, 0.f, 12.f);
		registerFloatSetting("Distance", &maxDistance, 7.f, 0.f, 15.f);
		registerFloatSetting("Wall Range", &wallRange, 2.f, 0.f, 15.f);
		registerIntSetting("Min Damage", &minDamage, 4, 0, 36);
		registerIntSetting("Max Self Dmg", &maxSelfDmg, 6, 0, 36);
		registerIntSetting("Min Health", &minHealth, 8, 0, 20);
		registerBoolSetting("Suicide", &suicide, false);
		//registerBoolSetting("Instakill", &instakill, false);

		registerIntSetting("Delay", &placeDelay, 0, 0, 20);
		//registerIntSetting("Break Delay", &breakDelay, 0, 0, 20);

		rotations = SettingEnum(this)
						.addEntry(EnumEntry("Off", rotations_off))
						.addEntry(EnumEntry("Normal", rotations_normal))
						.addEntry(EnumEntry("AntiKick", rotations_antikick));
		registerEnumSetting("Rotations", &rotations, rotations_normal);

		//registerBoolSetting("Flash Mode", &flash, false);
		//registerBoolSetting("Right Click", &rightClick, false);
		//registerBoolSetting("Auto Select", &autoSelect, true);
	//	registerBoolSetting("Render", &renderPlaced, false);
	}
	~BPGRewrite(){};

	virtual const char* getModuleName() override { return "RewhiteCrystal"; };
	virtual bool isFlashMode() override { return flash; };

	virtual void onPreTick(C_GameMode* gm) override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onSendPacket(C_Packet* pkt) override;

	virtual void onEnable() override;
	virtual void onDisable() override;

	virtual void onPreRender(C_MinecraftUIRenderContext* ctx) override;

	void doDestroy(std::vector<C_Entity*> crystals, C_GameMode* gm, bool placed);
	bool doPlace(std::vector<C_Entity*> targets, std::vector<C_Entity*> allEnts, C_GameMode* gm);
	bool findCrystal(C_GameMode* gm);

	static bool isTooFar(vec2_t from, vec2_t to);

	float computeExplosionDamage(vec3_t loc, C_Entity* target, C_BlockSource* reg, int mode);
	float computeExplosionDamage(C_Entity* crystal, C_Entity* target, C_BlockSource* reg, int mode) { return computeExplosionDamage(*crystal->getPos(), target, reg, mode); };
	float getBlastDamageEnchantReduction(C_ItemStack* item);

	float calculateBlockDensity(vec3_t pos, AABB aabb, C_BlockSource* region);
	bool tryRaytrace(vec3_t pos, vec3_t end, C_BlockSource* region);
};