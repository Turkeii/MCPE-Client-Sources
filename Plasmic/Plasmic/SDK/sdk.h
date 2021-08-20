#pragma once

#define WINDOWS_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <string.h>

#include "../Utils/PlasmicMath.h"
#include "../Utils/mem.h"

#include "Minecraft/MCUtilsClass.h"
#include "Minecraft/Enums.h"



//Block.h
class Material;
class BlockLegacy;
class BlockSource;
class Block;
class ChunkViewSource;
class ChunkSource;
#include "Minecraft/Block.h"


//ClientInstance.h
class GuiData;
class CMinecraft;
class ServerInstance;
struct LevelRenderer;
struct BitmapFont;
struct FontContainer;
struct FontList;
struct FontRepository;
class MinecraftGame;
struct ClientMoveInputHandler;
class ClientInstance;
#include "Minecraft/Item.h"


//Item.h
class Item;
class ItemStack;
class Inventory;
class PlayerInventory;
#include "Minecraft/Item.h"


//Level.h
class Dimension; 
class Level;
struct LevelHolder;
#include "Minecraft/Level.h"


//LocalPlayer.h   &&   Actor.h
class Gamemode;
class LocalPlayer;
#include "Minecraft/LocalPlayer.h"
#include "Minecraft/Actor.h"


//MinecraftUIRenderContext.h
class MinecraftUIRenderContext;
#include "Minecraft/MinecraftUIRenderContext.h"


//Packet.h
class Packet;
class PlayerAuthInputPacket;
class LevelSoundEventPacket;
class MovePlayerPacket;
class PlayerActionPacket;
class CommandRequestPacket;
#include "Minecraft/packet.h"

#include "game.h"