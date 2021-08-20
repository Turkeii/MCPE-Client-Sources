#pragma once
#include <cstdint>

class Item;
class ItemStack {
public:
	Item** item; //0x0008
private:
	char pad_0010[8]; //0x0010
public:
	class Block* blockptr; //0x0018 will be nulptr if it isn't a block
	char pad_0020[2]; //0x0020
public:
	int8_t amount; //0x0022
	char pad_0023[109]; //0x0023

	virtual void destructor();
	virtual void reinit(BlockLegacy* legacy, int count);
	virtual void reinit(Item* item, int count, int itemData);
	virtual void Function3();
	virtual void setNull();
	virtual void toString();
	virtual void toDebugString();
}; //Size: 0x0090




class Item {
#ifndef _1_16_40
public:
	class Text atlasType; //0x0008
private:
	char pad_0028[104]; //0x0028
public:
	int16_t maxStackSize; //0x0090
	int16_t id; //0x0092
private:
	char pad_0094[4]; //0x0094
public:
	class Text translateName; //0x0098
private:
	char pad_00B8[8]; //0x00B8
public:
	class Text name; //0x00C0
private:
	char pad_00E0[8]; //0x00E0
public:
	class Text isFrom; //0x00E8
private:
	char pad_0108[40]; //0x0108
public:
	class Text fullName; //0x0130 dosen't work with every item, e.g. minecraft:diamond_sword or isFrom:name
private:
	char pad_0150[8]; //0x0150
public:
	int16_t maxDurability; //0x0158
private:
	char pad_015A[6]; //0x015A
public:
	bool isFireResistant; //0x0160
private:
	char pad_0161[135]; //0x0161
public:
	class Text itemGroup; //0x01E8
private:
	char pad_0208[32]; //0x0208
public:
	class FoodItemComponentLegacy* foodItemComponentLegacy; //0x0228
private:
	char pad_0230[8]; //0x0230
public:
	class CameraItemComponentLegacy* cameraItemComponentLegacy; //0x0238
private:
	char pad_0240[56]; //0x0240
public:

#else
public:
	class Text atlasType; //0x0008
private:
	char pad_0028[64]; //0x0028
public:
	int16_t maxStackSize; //0x0068
	int16_t id; //0x006A
private:
	char pad_006C[4]; //0x006C
public:
	class Text translateName; //0x0070
	class Text name; //0x0090
	class Text isFrom; //0x00B0
private:
	char pad_00D0[8]; //0x00D0
public:
	class Text fullname; //0x00D8 isn't always filled, assemble with isFrom:name
	int16_t maxDurability; //0x00F8
private:
	char pad_00FA[6]; //0x00FA
public:
	bool isFireResistant; //0x0100
private:
	char pad_0101[191]; //0x0101
public:

#endif

	virtual void Function0();
	virtual void initServer();
	virtual void Function2();
	virtual void getMaxUseDuration();
	virtual void getMaxUseDuration2();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void isCamera();
	virtual void isDamageable();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void isFood();
	virtual void Function18();
	virtual void Function19();
	virtual void getCamera();
	virtual void getFood();
	virtual void Function22();
	virtual void setMaxStackSize(unsigned char amount);
	virtual void setStackedByData(bool isStackedByData);
	virtual void setMaxDamage(int maxDamage);
	virtual void setHandEquipped();
	virtual void setUseAnimation();
	virtual void setMaxUseDuration(int maxUseDuration);
	virtual void setRequiresWorldBuilder();
	virtual void setExplodable(bool explodable);
	virtual void setFireResistant(bool fireResistant);
	virtual void setIsGlint(bool isGlint);
	virtual void setShouldRespawn(bool shouldRespawn);
	virtual void getColorAtPos(BlockPos* position);
	virtual void canBeDepleted();
	virtual void Function36();
	virtual void Function37();
	virtual void isStackedByData();
	virtual void getMaxDamage();
	virtual void Function40();
	virtual void isHandEquipped();
	virtual void isGlint();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void isDestructive();
	virtual void Function49();
	virtual void Function50();
	virtual void Function51();
	virtual void appendFormatedHoverText();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void Function57();
	virtual void isValidAuxValue();
	virtual void getDamageChance();
	virtual void Function60();
	virtual void Function61();
	virtual void Function62();
	virtual void getSecondaryColor();
	virtual void Function64();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual void Function68();
	virtual void getSecondaryColor2();
	virtual void getSecondaryColor3();
	virtual void getActorIdentifier();
	virtual void Function72();
	virtual void Function73();
	virtual void buildIdAux();
	virtual void buildDescriptor();
	virtual void use(ItemStack* itemstack, class LocalPlayer* localPlayer);
	virtual void dispense(BlockSource* blocksource, class Container* container, int idk, const Vec3* position);
	virtual void useTimeDepleted();
	virtual void releaseUsing(ItemStack* itemstack, class LocalPlayer* localPlayer);
	virtual void getBrightness();
	virtual void hurtActor(ItemStack itemstack, class Actor* actor, class Mob* mob);
	virtual void Function82();
	virtual void Function83();
	virtual void mineBlock(class ItemInstance* item, const Block* block, int x, int y, int z, class Actor* actor);
	virtual void mineBlock2(class ItemInstance* item, const Block* block, int x, int y, int z, class Actor* actor);
	virtual void buildDescriptionName();
	virtual void buildDescriptionID();
	virtual void buildEffectDescriptionName();
	virtual void buildCategoryDescriptionName();
	virtual void readUserData(ItemStack* itemstack, class IDataInput, class ReadOnlyBinaryStream*);
	virtual void writeUserData(ItemStack* itemstack, class IDataOutput*);
	virtual void getMaxStackSize();
	virtual void Function93();
	virtual void Function94();
	virtual void getCooldownType();
	virtual void getCooldownTime();
	virtual void Function97();
	virtual void Function98();
	virtual void getDamageValue(const class CompoundTag* ctag);
	virtual void setDamageValue(ItemStack* itemstack, short damageValue);
	virtual void getInHandUpdateType(const LocalPlayer*, const ItemStack* itemstack1, const ItemStack* itemstack2, bool idk1, bool idk2);
	virtual void Function102();
	virtual void Function103();
	virtual void isSameItem(const ItemStack* itemstack1, const ItemStack* itemstack2);
	virtual void initClient();
	virtual void getInteractText();
	virtual void Function107();
	virtual void isEmissive(int idk);
	virtual void getLightEmission(int idk);
	virtual void getIcon(const ItemStack* itemstack, int idk1, bool idk2);
	virtual void getIconYoffset();
	virtual void Function112();
	virtual void setIcon(class TextureUVCoordinateSet* that);
	virtual void setIconAtlas(class Text* idk1, int idk2);
	virtual void Function115();
	virtual void Function116();
	virtual void Function117();
	virtual void getFurnaceBurnIntervalMultipler();
	virtual void getFurnaceXPMultiplier();
	virtual void Function120();
	virtual void Function121();
	virtual void calculatePlacePos(const ItemStack* itemstack, class Actor*, bool idk, struct BlockPos* output1);
	virtual void _useOn(ItemStack* itemstack, class Actor* actor, struct BlockPos blockpos, unsigned char idk1, float idk2, float idk3, float idk4);
}; //Size: 0x0278







class Inventory {
	char pad_0000[224]; //0x0000
public:
	ItemStack* supplieStart; //0x00E0 this is an array of ItemStack
	uintptr_t supplieEnd; //0x00E8
}; //Size: 0x0110



class PlayerInventory {
	char pad_0000[16]; //0x0000
public:
	int64_t selectedSlot; //*goes from 0 to 8    0x0010
private:
	char pad_0018[152]; //0x0018
public:
	class Inventory* inventory; //0x00B0
}; //Size: 0x0108
