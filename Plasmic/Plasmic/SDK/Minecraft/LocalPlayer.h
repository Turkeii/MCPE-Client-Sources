#pragma once
#include "MCUtilsClass.h"
#include "../../Utils/PlasmicMath.h"
#include "Level.h"
#include "Actor.h"
#include <vector>

//redo that
class Gamemode {
public:
	LocalPlayer* Player; //0x0008

	virtual void Destructor();
	virtual void startDestroyBlock(BlockPos*pos, uint8_t idk, bool something);
	virtual void destroyBlock(BlockPos* pos, uint8_t idk);
	virtual void continueDestroyBlock(BlockPos*, uint8_t, bool);
	virtual void stopDestroyBlock(BlockPos*);
	virtual void startBuildBlock(BlockPos*, uint8_t);
	virtual void buildBlock(BlockPos*, uint8_t);
	virtual void continueBuildBlock(BlockPos*, uint8_t);
	virtual void stopBuildBlock(void);
	virtual void tick(void);
	virtual float getPickRange();
	virtual void useItem();
	virtual bool useItemOn(ItemStack* item, BlockPos* pos, uint8_t idk, Vec3* precisePos, Block* interactedBlock); //12
	virtual void interact(Actor*, Vec3*);
	virtual bool attack(Actor*);
	virtual void releaseUsingItem();
};


//TODO: improve that there is nothing bruh


class LocalPlayer {
#ifndef _1_16_40
private:
	char pad_0008[8]; //0x0008
	int64_t ActorID; //0x0010
	char pad_0018[212]; //0x0018
public:
	int32_t dimensionID; //0x00EC
private:
	char pad_00F0[48]; //0x00F0
public: // ~~those can be usefull for the freelook~~
	float lookingatPitch1; //0x0120
	float lookingatYaw1; //0x0124
	float lookingatPitch2; //0x0128
	float lookingatYaw2; //0x012C
private:
	char pad_0130[16]; //0x0130
public:
	Vec3 actorPosition; //0x0140
private:
	char pad_014C[112]; //0x014C
public:
	float fallingDistance; //0x01BC
	bool canJump; //0x01C0
	bool isOnGround; //0x01C1
private:
	char pad_01C2[206]; //0x01C2
public:
	int64_t tickCount; //0x0290
private:
	char pad_0298[176]; //0x0298
public:
	class BlockSource* blocksource; //0x0348
	class Dimension* dimension; //0x0350
	class MultiPlayerLevel* multiplayerlevel; //0x0358
private:
	char pad_0360[8]; //0x0360
public:
	Text skinID; //0x0368
private:
	char pad_0388[64]; //0x0388
public:
	Text isFrom; //0x03C8
	Text entityName; //0x03E8
private:
	char pad_0408[72]; //0x0408
public:
	class Text fullEntityName; //isn't filled for everything so assemble it using isFrom:entityName   0x0450
private:
	char pad_0470[40]; //0x0470
public:
	Vec3 actorpos; //0x0498
	Vec3 headpos; //0x04A4
private:
	char pad_04B0[36]; //0x04B0
public:
	Vec3 velocity; //0x04D4
	Vec3 velocity2; //0x04E0
private:
	char pad_04EC[252]; //0x04EC
public:
	class SimplePlayerContainer* simpleplayerContainer; //0x05E8
private:
	char pad_05F0[156]; //0x05F0
public:
	float cameraRotation180; //0x068C
	float cameraRotation; //0x0690
private:
	char pad_0694[4]; //0x0694
public:
	int32_t hurtAnimationStatus; //0x0698
	int32_t hurtAnimationStatusTotalTime; //0x069C
private:
	char pad_06A0[480]; //0x06A0
public:
	class Text username; //0x0880
private:
	char pad_08A0[720]; //0x08A0
public:
	class ChunkViewSource* chunkViewSource1; //0x0B70
private:
	char pad_0B78[8]; //0x0B78
public:
	class ChunkViewSource* chunkViewSource2; //0x0B80
private:
	char pad_0B88[8]; //0x0B88
public:
	class BlockSource* blockSource2; //0x0B90
private:
	char pad_0B98[40]; //0x0B98
public:
	Vec2 dirrection; //0x0BC0
private:
	char pad_0BC8[32]; //0x0BC8
public:
	class PlayerInventory* playerInventory; //0x0BE8
private:
	char pad_0BF0[1026]; //0x0BF0
public:
	int16_t selectedItemID; //0x0FF2
private:
	char pad_0FF4[68]; //0x0FF4
public:
	class EnderchestContainer* enderchestContainer; //0x1038
private:
	char pad_1040[408]; //0x1040
public:
	class ItemStack* inventoryItemHolding; //0x11D8
private:
	char pad_11E0[56]; //0x11E0
public:
	class GameMode* cgameMode; //0x1218
private:
	char pad_1220[2780]; //0x1220
public:
	int32_t gamemode; //0x1CFC

#else

	char pad_0000[224]; //0x0000
public:
	int32_t dimensionID; //0x00E8
private:
	char pad_00EC[20]; //0x00EC
public:
	float lookingatPith1; //0x0100
	float lookingatYaw1; //0x0104
	float lookingatPith2; //0x0108
	float lookingatYaw2; //0x010C
private:
	char pad_0110[16]; //0x0110
public:
	Vec3 actorPosition; //0x0120
private:
	char pad_012C[112]; //0x012C
public:
	float fallingDistance; //0x019C
	bool canJump; //0x01A0
	bool isOnGround; //0x01A1
private:
	char pad_01A2[198]; //0x01A2
public:
	uint64_t tickCount; //0x0268
private:
	char pad_0270[176]; //0x0270
public:
	class BlockSource* blocksource; //0x0320
	class Dimension* dimension; //0x0328
	class MultiplayerLevel* multiplayerlevel; //0x0330
private:
	char pad_0338[8]; //0x0338
public:
	class Text skinID; //0x0340
private:
	char pad_0360[48]; //0x0360
public:
	class Text isFrom; //0x0390
	class Text entityName; //0x03B0
private:
	char pad_03D0[72]; //0x03D0
public:
	class Text fullEntityName; //0x0418 isn't fill for everything assemble isFrom:entityName
private:
	char pad_0438[32]; //0x0438
public:
	Vec3 actorpos; //0x0458
	Vec3 headPos; //0x0464
private:
	char pad_0470[12]; //0x0470
	Vec3 N00002085; //0x047C
	Vec3 N00000ECF; //0x0488
public:
	Vec3 velocity; //0x0494
private:
	char pad_04A0[216]; //0x04A0
public:
	class SimplePlayerContainer* simplePlayerContainer; //0x0578
private:
	char pad_0580[164]; //0x0580
public:
	float cameraRotation180; //0x0624
	float cameraRotation; //0x0628
private:
	char pad_062C[4]; //0x062C
public:
	int32_t hurtAnimationStatus; //0x0630
	int32_t hurtAnimationStatusTotalTime; //0x0634
private:
	char pad_0638[480]; //0x0638
public:
	class Text username; //0x0818
private:
	char pad_0838[720]; //0x0838
public:
	class ChunkViewSource* chunkViewSource1; //0x0B08
	class ChunkViewSource* chunkViewSource2; //0x0B10
	class BlockSource* blockSource2; //0x0B18
private:
	char pad_0B20[80]; //0x0B20
public:
	class PlayerInventory* playerInventory; //0x0B70
private:
	char pad_0B78[1026]; //0x0B78
public:
	int32_t selectedItemID; //0x0F7A
private:
	char pad_0F7E[66]; //0x0F7E
public:
	class EnderChestContainer* enderchestContainer; //0x0FC0
private:
	char pad_0FC8[408]; //0x0FC8
public:
	class ItemStack* inventoryItemHolding; //0x1160
private:
	char pad_1168[56]; //0x1168
public:
	class Gamemode* cgameMode; //0x11A0
private:
	char pad_11A8[2780]; //0x11A8
public:
	int32_t gamemode; //0x1C84

#endif





	virtual void Function0() {}
	virtual void Function1() {}
	virtual void Function2() {}
	virtual void Function3() {}
	virtual void Function4() {}
	virtual void Function5() {}
	virtual void Function6() {}
	virtual void Function7() {}
	virtual void Function8() {}
	virtual void getOnDeathExperiance() {}
	virtual void getOwnerEntityType() {}
	virtual void playerRemove() {}
	virtual void setPos(Vec3* position) {}
	virtual void Function13() {}
	virtual Vec3* getPos() { return NULL; }
	virtual Vec3* getPosOld() { return NULL; }
	virtual void getPosExtrapolated() {}
	virtual void getAttachPos() {}
	virtual Vec3 getFiringPos() {}
	virtual void setRot(Vec2 look) {}
	virtual void Function20() {}
	virtual void move() {}
	virtual void Function22() {}
	virtual void Function23() {}
	virtual void Function24() {}
	virtual void Function25() {}
	virtual void Function26() {}
	virtual void Function27() {}
	virtual void Function28() {}
	virtual void checkBlockCollisions() {}
	virtual void Function30() {}
	virtual bool isFireImmune() { return false; }
	virtual void Function32() {}
	virtual void blockedByShield() {}
	virtual void teleportTo(Vec3* position, char idk = 2) {  }
	virtual void tryTeleportTo() {}
	virtual void chorusFuitTeleport(Vec3* position) {}
	virtual void lerpTo() {}
	virtual void lerpMotion() {}
	virtual void getAddPacket() {}
	virtual void normalTick() {}
	virtual void baseTick() {}
	virtual void rideTick() {}
	virtual void Function43() {}
	virtual void getRidingHeight() {}
	virtual void startRiding() {}
	virtual void addRider() {}
	virtual void Function47() {}
	virtual void Function48() {}
	virtual void Function49() {}
	virtual void Function50() {}
	virtual void isFree() {}
	virtual bool isInWall() { return false; }
	virtual bool isInvisible() { return false; }
	virtual bool canShowNametag() { return false; }
	virtual void Function55() {}
	virtual void setNametagVisible(bool visibility) {}
	virtual void getNametag() {}
	virtual void getNametagAsHash() {}
	virtual void Function59() {}
	virtual void Function60() {}
	virtual void setNametag() {}
	virtual void Function62() {}
	virtual void setScoretag() {}
	virtual void getScoretag() {}
	virtual bool isinWater() { return true; }
	virtual bool hasEnteredWater() { return false; }
	virtual bool isImmersedInWater() { return false; }
	virtual bool isWet() { return false; }
	virtual bool isinLava() { return true; }
	virtual bool isUnderLiquid() { return false; }
	virtual bool isOverWater() { return true; }
	virtual void makeStuckInBlock(Vec3 position) {}
	virtual void Function73() {}
	virtual void Function74() {}
	virtual void Function75() {}
	virtual void Function76() {}
	virtual void Function77() {}
	virtual void Function78() {}
	virtual void canSee() {}
	virtual void Function80() {}
	virtual void getBrightness() {}
	virtual void Function82() {}
	virtual void Function83() {}
	virtual void onAboveBubbleColumn() {}
	virtual void onInsideBubbleColum() {}
	virtual bool isImmobile() { return true; }
	virtual bool isSilent() { return false; }
	virtual bool isPickable() { return false; }
	virtual void Function89() {}
	virtual bool isSleeping() { return false; }
	virtual void Function91() {}
	virtual void setSneaking(bool sneakstatus) {}
	virtual bool isBlocking() { return false; }
	virtual bool isDamageBlocked() { return false; }
	virtual bool isAlive() { return false; }
	virtual bool isonFire() { return false; }
	virtual bool isonHotBlock() { return false; }
	virtual void Function98() {}
	virtual void Function99() {}
	virtual void Function100() {}
	virtual void Function101() {}
	virtual void Function102() {}
	virtual bool canAttack(LocalPlayer* player, bool idk) { return false; }
	virtual void setTarget() {}
	virtual void Function105() {}
	virtual void isValidTarget() {}
	virtual void attack() {}
	virtual void performRangedAttack() {}
	virtual void adjustDamageAmount() {}
	virtual __int64 getEquipementCount() { return 0; }
	virtual void Function111() {}
	virtual void Function112() {}
	virtual void Function113() {}
	virtual void Function114() {}
	virtual __int64 getInventorySize() { return 0; }
	virtual __int64 getEquipSlots() { return 0; }
	virtual void Function117() {}
	virtual void Function118() {}
	virtual void Function119() {}
	virtual void Function120() {}
	virtual bool isJumping() { return true; }
	virtual bool isEnchanted() { return false; }
	virtual void Function123() {}
	virtual void Function124() {}
	virtual bool shouldRender() { return true; }
	virtual void Function126() {}
	virtual void Function127() {}
	virtual void actuallyHurt(int damage, const struct ActorDamageSource*, bool idk) {}
	virtual void animateHurt() {}
	virtual bool doFireHurt(int damage) { return false; }
	virtual void Function131() {}
	virtual void Function132() {}
	virtual void feed(int hunger) {}
	virtual void Function134() {}
	virtual void Function135() {}
	virtual void Function136() {}
	virtual void Function137() {}
	virtual void spawnAtLocation() {}
	virtual void Function139() {}
	virtual void Function140() {}
	virtual void Function141() {}
	virtual void despawn() {}
	virtual void Function143() {}
	virtual void Function144() {}
	virtual void setArmor(int armorSlot, const ItemStack& item);
	virtual const ItemStack& getArmor(int armorSlot);
	virtual void Function147() {}
	virtual void Function148() {}
	virtual void Function149() {}
	virtual const ItemStack& getEquippedSlot(int EquipementSlot);
	virtual void setEquipedSlot(int EquipementSlot, const ItemStack& item) {}
	virtual void Function152() {}
	virtual void Function153() {}
	virtual void setOffhandSlot(const ItemStack*) {}
	virtual const ItemStack* getEquippedTotem();
	virtual bool consumeTotem() { return false; }
	virtual void save() {}
	virtual void saveWithoutID() {}
	virtual void load() {}
	virtual void Function160() {}
	virtual void getEntittyTypeID() {}
	virtual void Function162() {}
	virtual void Function163() {}
	virtual void setOnFire(int firetime) {}
	virtual void Function165() {}
	virtual void Function166() {}
	virtual void Function167() {}
	virtual __int64 getPortalWaitTime() { return 0; }
	virtual enum Dimensions getDimentionID() { return Dimensions::Overworld; }
	virtual bool canChangeDimensions() { return false; }
	virtual void Function171() {}
	virtual void changeDimension(Dimensions dim) {}
	virtual void Function173() {}
	virtual void Function174() {}
	virtual void causeFallDamage(float fallDistance) {}
	virtual void Function176() {}
	virtual void Function177() {}
	virtual void Function178() {}
	virtual void Function179() {}
	virtual void Function180() {}
	virtual void Function181() {}
	virtual void Function182() {}
	virtual void Function183() {}
	virtual void Function184() {}
	virtual void Function185() {}
	virtual void Function186() {}
	virtual void Function187() {}
	virtual void Function188() {}
	virtual void startSwimming() {}
	virtual void stopSwimming() {}
	virtual void Function191() {}
	virtual int getCommandPermissionLevel() { return 0; }
	virtual void setPermissions(int permissionlevel) {}
	virtual void Function194() {}
	virtual __int64 getDeathTime() { return 0; }
	virtual void heal(int lifeToAdd) {}
	virtual void Function197() {}
	virtual void Function198() {}
	virtual void Function199() {}
	virtual void Function200() {}
	virtual void Function201() {}
	virtual void Function202() {}
	virtual void Function203() {}
	virtual void Function204() {}
	virtual void Function205() {}
	virtual void swing() {}
	virtual void useItem(class ItemStackBase*, int ItemUSeMethod, bool) {}
	virtual void Function208() {}
	virtual void Function209() {}
	virtual void Function210() {}
	virtual void Function211() {}
	virtual void Function212() {}
	virtual void Function213() {}
	virtual bool isWorldBuilder() { return false; }
	virtual bool isCreative() { return false; }
	virtual bool isAdventure() { return false; }
	virtual void Function217() {}
	virtual void Function218() {}
	virtual void Function219() {}
	virtual void Function220() {}
	virtual void Function221() {}
	virtual void Function222() {}
	virtual void getlifespan() {}
	virtual void Function224() {}
	virtual void Function225() {}
	virtual bool wasHurt() { return true; }
	virtual void Function227() {}
	virtual void Function228() {}
	virtual void Function229() {}
	virtual void Function230() {}
	virtual void Function231() {}
	virtual void Function232() {}
	virtual void Function233() {}
	virtual void kill() {}
	virtual void die(const ActorDamageSource& damageSource) {}
	virtual void Function236() {}
	virtual void Function237() {}
	virtual void Function238() {}
	virtual void Function239() {}
	virtual void Function240() {}
	virtual void Function241() {}
	virtual void outOfWorld() {}
	virtual void _hurt() {}
	virtual void Function244() {}
	virtual void Function245() {}
	virtual void Function246() {}
	virtual void playStepSound() {}
	virtual void Function248() {}
	virtual void Function249() {}
	virtual void Function250() {}
	virtual void Function251() {}
	virtual void Function252() {}
	virtual void Function253() {}
	virtual void Function254() {}
	virtual void Function255() {}
	virtual void Function256() {}
	virtual void Function257() {}
	virtual void Function258() {}
	virtual void Function259() {}
	virtual void Function260() {}
	virtual void Function261() {}
	virtual void Function262() {}
	virtual void Function263() {}
	virtual void setSleeping(bool sleepStatus) {}
	virtual void setSprinting(bool sprintStatus) {}
	virtual void Function266() {}
	virtual void Function267() {}
	virtual void Function268() {}
	virtual void Function269() {}
	virtual void Function270() {}
	virtual float getSpeed() { return 0.0f; }
	virtual void setSpeed(float newSpeed) {}
	virtual void Function273() {}
	virtual void Function274() {}
	virtual void Function275() {}
	virtual void Function276() {}
	virtual void Function277() {}
	virtual void Function278() {}
	virtual void Function279() {}
	virtual void Function280() {}
	virtual void Function281() {}
	virtual void Function282() {}
	virtual void Function283() {}
	virtual void lookAt(LocalPlayer* actor, float headrot, float headrot2) {}
	virtual bool islookingAtAnEntity() { return false; }
	virtual void Function286() {}
	virtual void Function287() {}
	virtual void Function288() {}
	virtual void Function289() {}
	virtual void Function290() {}
	virtual void Function291() {}
	virtual void Function292() {}
	virtual void Function293() {}
	virtual void Function294() {}
	virtual void Function295() {}
	virtual void getLastHurtByMob() {}
	virtual void setLastHurtByMob() {}
	virtual LocalPlayer* getLastHurtByPlayer() { return nullptr; }
	virtual void setLastHurtByPlayer(LocalPlayer* player) {}
	virtual void Function300() {}
	virtual void Function301() {}
	virtual void Function302() {}
	virtual void doHurtTarget(LocalPlayer* actor) {}
	virtual void Function304() {}
	virtual void Function305() {}
	virtual void Function306() {}
	virtual void Function307() {}
	virtual void Function308() {}
	virtual __int64 getArmorValue() { return 0; }
	virtual float getArmorCoverPercentage() { return 0.0f; }
	virtual void hurtArmor() {}
	virtual void hurtArmorPlayer() {}
	virtual void hurtArmorSlot() {}
	virtual void setDamagedArmor() {}
	virtual void sendArmorDamage() {}
	virtual void sendArmor() {}
	virtual void Function317() {}
	virtual void Function318() {}
	virtual __int64 clearEquipment() { return 0; }
	virtual std::vector<const ItemStack*> getAllArmor() const { std::vector<const ItemStack*> gamer; return gamer; }
	virtual void Function321() {}
	virtual void Function322() {}
	virtual void Function323() {}
	virtual void Function324() {}
	virtual void dropEquipmentOnDeath() {}
	virtual void Function326() {}
	virtual void clearVanishEnchantedItemsOnDeath() {}
	virtual void sendInventory(bool idk) {}
	virtual void Function329() {}
	virtual void Function330() {}
	virtual void Function331() {}
	virtual void setItemSlot(int EquipementSlot, const ItemStack* item) {}
	virtual void Function333() {}
	virtual void Function334() {}
	virtual void Function335() {}
	virtual void Function336() {}
	virtual void Function337() {}
	virtual void Function338() {}
	virtual void ascendLadder() {}
	virtual void asscendScaffolding() {}
	virtual void descendScaffolding() {}
	virtual void dropContainer() {}
	virtual void Function343() {}
	virtual void jumpFromGround() {}
	virtual void Function345() {}
	virtual void Function346() {}
	virtual void Function347() {}
	virtual void Function348() {}
	virtual void getDamageAfterEnchantReduction() {}
	virtual void getDamageAfterArmorAbsorb() {}
	virtual void Function351() {}
	virtual void tickDeath() {}
	virtual void Function353() {}
	virtual void Function354() {}
	virtual void Function355() {}
	virtual void Function356() {}
	virtual void Function357() {}
	virtual void resendAllChunks() {}
	virtual void Function359() {}
	virtual void Function360() {}
	//It will tp you to the overworld Whatever you pass in
	virtual void changeDimensionWithCredits(Dimensions = Dimensions::Overworld) {}
	virtual void Function362() {}
	virtual void Function363() {}
	virtual void Function364() {}
	virtual void moveView() {}
	virtual void setName() {}
	virtual void Function367() {}
	virtual void Function368() {}
	virtual void Function369() {}
	virtual void respawn() {}
	virtual void Function371() {}
	virtual void resetPos() {}
	virtual void Function373() {}
	virtual void Function374() {}
	virtual void Function375() {}
	virtual void Function376() {}
	virtual void startDestroying() {}
	virtual void stopDestroying() {}
	virtual void Function379() {}
	virtual void Function380() {}
	virtual void openTrading() {}
	virtual bool canOpenContainerScreen() { return false; }
	virtual void Function383() {}
	virtual void Function384() {}
	virtual void openInventory() {}
	virtual void Function386() {}
	virtual void Function387() {}
	virtual void displayTextObjectMessage() {}
	virtual void displayTextObjectWisperMessage() {}
	virtual void displayWisperMessage() {}
	virtual void startSleepInBed(const BlockPos& bedPosition) {}
	virtual void stopSleepInBed(bool idk1, bool idk2) {}
	virtual void canStartSleepInBed() {}
	virtual void Function394() {}
	virtual void Function395() {}
	virtual void Function396() {}
	virtual void Function397() {}
	virtual bool isHostingPlayer() { return false; }
	virtual bool isLoading() { return false; }
	virtual bool isPlayerInitalized() { return false; }
	virtual void Function401() {}
	virtual void Function402() {}
	virtual void Function403() {}
	virtual void setGamemode(Gamemodes newGamemode) {}
	virtual void Function405() {}
	virtual void Function406() {}
	virtual void Function407() {}
	virtual void Function408() {}
	virtual void addExperiance(int AmountOfExperiance) {}
	virtual void addLevels(int amountOfLevels) {}
	virtual void Function411() {}
	virtual void Function412() {}
	virtual void Function413() {}
	virtual void Function414() {}
	virtual void Function415() {}
	virtual void setFOVmodifier(float fov) {}
	virtual void Function417() {}
	virtual void Function418() {}
	virtual void Function419() {}
	virtual void Function420() {}
	virtual void Function421() {}
	virtual void Function422() {}
	virtual void Function423() {}
	virtual void Function424() {}
	virtual void sendInventoryTransaction() {}
	virtual void sendComplexInventoryTransaction() {}
	virtual void sendNetworkPacket(class Packet*) {  }
	virtual void Function428() {}
	virtual void Function429() {}
	virtual void Function430() {}
	virtual void Function431() {}
	virtual void Function432() {}
	virtual void Function433() {}
	virtual void Function434() {}
	virtual void Function435() {}

};

