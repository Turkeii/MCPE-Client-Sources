#pragma once

#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "../../Memory/GameData.h"

#include "Modules/Aimbot.h"
#include "Modules/AirJump.h"
#include "Modules/AirSwim.h"
#include "Modules/AntiBot.h"
#include "Modules/AutoArmor.h"
#include "Modules/AutoClicker.h"
#include "Modules/AutoGapple.h"
#include "Modules/AutoSneak.h"
#include "Modules/AutoSprint.h"
#include "Modules/AutoTotem.h"
#include "Modules/Fucker.h"
#include "Modules/Bhop.h"
#include "Modules/Blink.h"
#include "Modules/BowAimbot.h"
#include "Modules/AntiVoid.h"
#include "Modules/ChestAura.h"
#include "Modules/DropperEsp.h"
#include "Modules/ChestStealer.h"
#include "Modules/ClickGuiMod.h"
#include "Modules/Teleport.h"
#include "Modules/Crasher.h"
#include "Modules/Criticals.h"
#include "Modules/CrystalAura.h"
#include "Modules/Derp.h"
#include "Modules/ESP.h"
#include "Modules/EditionFaker.h"
#include "Modules/FastEat.h"
#include "Modules/FastLadder.h"
#include "Modules/Fly.h"
#include "Modules/Freecam.h"
#include "Modules/FullBright.h"
#include "Modules/Glide.h"
#include "Modules/HighJump.h"
#include "Modules/Hitbox.h"
#include "Modules/HudModule.h"
#include "Modules/ExtendedBlockReach.h"
#include "Modules/InfiniteAura.h"
#include "Modules/InstaBreak.h"
#include "Modules/InventoryCleaner.h"
#include "Modules/InventoryMove.h"
#include "Modules/Jesus.h"
#include "Modules/Jetpack.h"
#include "Modules/Killaura.h"
#include "Modules/MidClick.h"
#include "Modules/Module.h"
#include "Modules/NameTags.h"
#include "Modules/NoFall.h"
#include "Modules/NoFriends.h"
#include "Modules/Velocity.h"
#include "Modules/NoPacket.h"
#include "Modules/NoSlowDown.h"
#include "Modules/NoWeb.h"
#include "Modules/Nuker.h"
#include "Modules/Phase.h"
#include "Modules/RainbowSky.h"
#include "Modules/Reach.h"
#include "Modules/Scaffold.h"
#include "Modules/Spammer.h"
#include "Modules/Speed.h"
#include "Modules/StackableItem.h"
#include "Modules/Step.h"
#include "Modules/TimeChanger.h"
#include "Modules/Timer.h"
#include "Modules/Tower.h"
#include "Modules/Tracer.h"
#include "Modules/TriggerBot.h"
#include "Modules/Xray.h"
#include "Modules/NightMode.h"
#include "Modules/NoSwing.h"
#include "Modules/ZeroTP.h"
#include "Modules/AirStuck.h"
#include "Modules/Zoom.h"
#include "Modules/Teams.h"
#include "Modules/Nbt.h"
#include "Modules/AutoCrystal.h"
#include "Modules/Freelook.h"
#include "Modules/NoHurtcam.h"
#include "Modules/AntiImmobile.h"
#include "Modules/FollowPathModule.h"
#include "Modules/NoPaintingCrash.h"
#include "Modules/Waypoints.h"
#include "Modules/Spider.h"
#include "Modules/Compass.h"
#include "Modules/Radar.h"
#include "Modules/VanillaPlus.h"
#include "Modules/ViewModel.h"
#include "Modules/Twerk.h"
#include "Modules/AutoTimer.h"
#include "Modules/CrystalAuraOW.h"
#include "Modules/Placer.h"
#include "Modules/PvpResources.h"
#include "Modules/PistonAura.h"
#include "Modules/SpeedBypass.h"
#include "Modules/HoleEsp.h"
#include "Modules/ReverseStep.h"
#include "Modules/TargetHud.h"
#include "Modules/selectionHighlight.h"
#include "Modules/CAtwo.h"
#include "Modules/AntiCrystal.h"
#include "Modules/Chat.h"
#include "Modules/AutoEz.h"
#include "Modules/AntiAnvil.h"
#include "Modules/ElytraFly.h"
#include "Modules/CrystalAura2.h"
#include "Modules/PacketMine.h"
#include "Modules/AutoWeapon.h"
//#include "Modules/ArrayList.h"
#include "Modules/HoleFiller.h"
#include "Modules/BoatFly.h"
#include "Modules/CrystalAuraWTA.h"
#include "Modules/Theme.h"
#include "Modules/PlayerList.h"
#include "Modules/JavaAura.h"
#include "Modules/CrystalMove.h"
#include "Modules/CrystalReplenishment.h"
#include "Modules/AnchorAura.h"
#include "Modules/InventoryView.h"
#include "Modules/Background.h"
#include "Modules/HudEditor.h"
#include "Modules/SpeedDisplay.h"
#include "Modules/surround.h"
#include "Modules/Breadcrums.h"
#include "Modules/BlockEsp.h"
#include "Modules/NoClip.h"
#include "Modules/BoatSpeed.h"
#include "Modules/FastPlace.h"
#include "Modules/AutoTrap.h"
#include "Modules/StrafeSpeed.h"
#include "Modules/AltTheme.h"
#include "Modules/ReverseKnockBack.h"
#include "Modules/FastStop.h"
#include "Modules/ShieldBreaker.h"
#include "Modules/AirWalk.h"
#include "Modules/BowSpam.h"
#include "Modules/XPFast.h"
#include "Modules/CrystalAuraBPG.h"
#include "Modules/BPGRewrite.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"
//#include "Modules/TestModule.h"

class ModuleManager {
private:
	GameData* gameData;
	std::vector<std::shared_ptr<IModule>> moduleList;
	bool initialized = false;
	std::shared_mutex moduleListMutex;

public:
	~ModuleManager();
	ModuleManager(GameData* gameData);
	void initModules();
	void disable();
	void onLoadConfig(void* conf);
	void onSaveConfig(void* conf);
	void onTick(C_GameMode* gameMode);
	void onAttack(C_Entity* attackedEnt);

	void onKeyUpdate(int key, bool isDown);
	void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	void onLevelRender();
	void onMove(C_MoveInputHandler* handler);
	void onSendPacket(C_Packet*);

	std::shared_lock<std::shared_mutex> lockModuleList() { return std::shared_lock(this->moduleListMutex); }
	std::unique_lock<std::shared_mutex> lockModuleListExclusive() { return std::unique_lock(this->moduleListMutex); }
	
	std::shared_mutex* getModuleListLock() { return &this->moduleListMutex; }

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<IModule>>* getModuleList();

	int getModuleCount();
	int getEnabledModuleCount();

	/*
	 *	Use as follows: 
	 *		IModule* mod = moduleMgr.getModule<NoKnockBack>(); 
	 *	Check for nullptr directly after that call, as Hooks::init is called before ModuleManager::initModules !	
	 */
	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		auto lock = this->lockModuleList();
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())){
				
				return pRet;
			}
		}
		return nullptr;
	};

	// Dont Use this functions unless you absolutely need to. The function above this one works in 99% of cases
	std::optional<std::shared_ptr<IModule>> getModuleByName(const std::string name) {
		if (!isInitialized())
			return nullptr;
		std::string nameCopy = name;
		std::transform(nameCopy.begin(), nameCopy.end(), nameCopy.begin(), ::tolower);
		
		auto lock = this->lockModuleList();
		for (std::vector<std::shared_ptr<IModule>>::iterator it = this->moduleList.begin(); it != this->moduleList.end(); ++it) {
			std::shared_ptr<IModule> mod = *it;
			std::string modNameCopy = mod->getRawModuleName();
			std::transform(modNameCopy.begin(), modNameCopy.end(), modNameCopy.begin(), ::tolower);
			if (modNameCopy == nameCopy)
				return std::optional<std::shared_ptr<IModule>>(mod);
		}
		return std::optional<std::shared_ptr<IModule>>();
	}
};

extern ModuleManager* moduleMgr;
