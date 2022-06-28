#pragma once

#include "Module.h"

class AutoCrystal : public IModule {
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
	bool autoPlace = false;
	float maxDistance = 7.f;
	float hitRange = 7.f;
	float wallRange = 2.f;
	int maxSelfDmg = 6;  // Player damage
	int minDamage = 4;   // Target damage
	int minHealth = 8;
	bool suicide = false;    // TODO
	bool instakill = false;  // TODO
	bool stopOnInv = false;
	bool stopOnClick = false;
	int placeDelay = 2;
	int breakDelay = 0;
	bool flash = false;
	bool rightClick = false;
	bool autoSelect = true;
	bool renderPlaced = false;
	bool rainbow = false;
	bool botCheck = false;
	bool renderdmg = false;
	static float constexpr maxdot = 0.f;  // dot
	bool silentSwitch = false;
	bool noSwing = false;
	bool ReturnOnEat = false;
	bool NoTargetDisable = false;
	int previousSlot = -1;
	bool shouldPlace = false;
	bool shouldDestroy = false;
	bool disableAutoplace = false;
	bool rotate = false;
	vec2_t rotateTarget = {0.f, 0.f};
	bool packetSent = false;
	bool isPlayerAuthInput = false;
	int switchCooldown = 0;
	int renderTimer;
	bool ReturnOnGapple;
	struct CrystalRenderHolder {
		float enemyDmg;
		float playerDmg;
		vec3_ti pos;
	} latestCrystal;
	bool renderCrystal;
	float AutoCrystal::rFloat{0};
	float AutoCrystal::gFloat{255};
	float AutoCrystal::bFloat{0};
	int sdelay = 0;
	int Osdelay;
	bool newmode = false;
public:
	float minPlace = 0.f;
	float minBreak = 0.f;
	float placeRange = 7.f;

	AutoCrystal() : IModule(0x0, Category::COMBAT, "kills people (if ur good)") {
		dmgEnum = SettingEnum(this)
					  .addEntry(EnumEntry("1.13 Mode", dmg_nukkit))
					  .addEntry(EnumEntry("2b2e", dmg_2b2e))
					  .addEntry(EnumEntry("Vanilla", dmg_vanilla))
					  .addEntry(EnumEntry("Java", dmg_java));
		registerEnumSetting("Protocol", &dmgEnum, dmg_java);

		destroyEnum = SettingEnum(this)
						  .addEntry(EnumEntry("Check", destroy_check))
						  .addEntry(EnumEntry("All", destroy_all));
		registerEnumSetting("Destroy Mode", &destroyEnum, destroy_check);

		registerBoolSetting("Bot Check", &botCheck, true);
		registerBoolSetting("Auto Place", &autoPlace, false);
		registerFloatSetting("Min Place Range", &minPlace, 0.f, 0.f, 12.f);
		registerFloatSetting("Min Break Range", &minBreak, 0.f, 0.f, 12.f);
		//registerFloatSetting("Max Distance", &maxDistance, 7.f, 0.f, 15.f);
		registerFloatSetting("Break Range", &hitRange, 7.f, 0.f, 15.f);
		registerFloatSetting("Place Range", &placeRange, 7.f, 0.f, 15.f);
		registerFloatSetting("Wall Range", &wallRange, 2.f, 0.f, 15.f);

		registerIntSetting("Min Damage", &minDamage, 4, 0, 36);
		registerIntSetting("Max Self Dmg", &maxSelfDmg, 6, 0, 36);

		registerIntSetting("Min Health", &minHealth, 8, 0, 20);
		registerBoolSetting("Suicide", &suicide, false);

		registerIntSetting("Place Delay", &placeDelay, 2, 0, 20);
		registerIntSetting("Break Delay", &breakDelay, 0, 0, 20);

		rotations = SettingEnum(this)
						.addEntry(EnumEntry("Off", rotations_off))
						.addEntry(EnumEntry("Normal", rotations_normal))
						.addEntry(EnumEntry("AntiKick", rotations_antikick))
						.addEntry(EnumEntry("Arora", rotations_arora));
		registerEnumSetting("Rotations", &rotations, rotations_normal);

		registerBoolSetting("Flash Mode", &flash, false);
		registerBoolSetting("Right Click", &rightClick, false);
		registerBoolSetting("Auto Select", &autoSelect, true);
		registerBoolSetting("Spoof", &silentSwitch, false);
		registerBoolSetting("PauseOnInv", &stopOnInv, false);
		registerBoolSetting("PauseOnEat", &ReturnOnEat, false);
		//registerBoolSetting("NoSwing", &noSwing, noSwing);
		registerBoolSetting("NoTargetDisable", &NoTargetDisable, false);
		registerBoolSetting("DisableOnGap", &ReturnOnGapple, false);

		registerBoolSetting("Render", &renderPlaced, false);
		registerBoolSetting("Render Damage", &renderdmg, false);
		registerFloatSetting("Red", &rFloat, rFloat, 0.f, 255.f);
		registerFloatSetting("Green", &gFloat, gFloat, 0.f, 255.f);
		registerFloatSetting("Blue", &bFloat, bFloat, 0.f, 255.f);
	}

	vec2_t breakRot;
	vec2_t placeRot;
	std::vector<C_Entity*> toBreak;
	std::vector<vec3_ti> toPlace;
	SettingEnum rotations;
	static int constexpr rotations_off = 0;
	static int constexpr rotations_normal = 1;
	static int constexpr rotations_antikick = 2;  // 2b2e
	static int constexpr rotations_arora = 4;
	static int constexpr rotations_lockview = 3;  // For the funni if you know what I mean

	~AutoCrystal(){};

	virtual const char* getModuleName() override { return "AutoCrystal"; };
	virtual const char* getModName() override;
	virtual bool isFlashMode() override { return flash; };

	// Actually running the code in these
	virtual void onPreTick(C_GameMode* gm) override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onSendPacket(C_Packet* pkt) override;
	virtual void onEnable() override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onDisable() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* ctx) override;
	void doDestroy(std::vector<C_Entity*> crystals, C_GameMode* gm, bool placed);
	bool doPlace(std::vector<C_Entity*> targets, std::vector<C_Entity*> allEnts, C_GameMode* gm);
	bool findCrystal();
	static bool isTooFar(vec2_t from, vec2_t to);
	float computeExplosionDamage(vec3_t loc, C_Entity* target, C_BlockSource* reg, int mode);
	float computeExplosionDamage(C_Entity* crystal, C_Entity* target, C_BlockSource* reg, int mode) { return computeExplosionDamage(*crystal->getPos(), target, reg, mode); };
	float getBlastDamageEnchantReduction(C_ItemStack* item);
	float calculateBlockDensity(vec3_t pos, AABB aabb, C_BlockSource* region);
};