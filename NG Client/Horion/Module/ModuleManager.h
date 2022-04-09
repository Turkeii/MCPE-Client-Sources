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
#include "Modules/AirStuck.h"
#include "Modules/AirSwim.h"
#include "Modules/AnchorAura.h"
#include "Modules/AntiAnvil.h"
#include "Modules/AntiBot.h"
#include "Modules/AntiImmobile.h"
#include "Modules/AntilagBack.h"
#include "Modules/AntiVoid.h"
#include "Modules/ArmourHud.h "
#include "Modules/AutoArmor.h"
#include "Modules/AutoBuild.h"
#include "Modules/AutoClick.h"
#include "Modules/AutoEZ.h"
#include "Modules/AutoEZv2.h"
#include "Modules/AutoEZv3.h"
#include "Modules/AutoJump.h"
#include "Modules/AutoPot.h"
#include "Modules/AutoSneak.h"
#include "Modules/AutoSprint.h"
#include "Modules/AutoTotem.h"
#include "Modules/AutoWalk.h"
#include "Modules/Bhop.h"
#include "Modules/Blink.h"
#include "Modules/BlockEsp.h"
#include "Modules/BowAimbot.h"
#include "Modules/bps.h"
#include "Modules/chestaura.h"
#include "Modules/ChestStealer.h"
#include "Modules/ClickGuiMod.h"
#include "Modules/Compass.h"
#include "Modules/Coordinates.h"
#include "Modules/cps.h"
#include "Modules/Crasher.h"
#include "Modules/CrystalAura.h"
#include "Modules/Derp.h"
#include "Modules/Disabler.h"
#include "Modules/EditionFaker.h"
#include "Modules/EntityBhop.h"
#include "Modules/EntityDerp.h"
#include "Modules/EntityFly.h"
#include "Modules/EntityJesus.h"
#include "Modules/EntityJetpack.h"
#include "Modules/EntityLongjump.h"
#include "Modules/EntitySpeed.h"
#include "Modules/EntitySpider.h"
#include "Modules/ESP.h"
#include "Modules/EzSPAM.h"
#include "Modules/ExtendedBlockReach.h"
#include "Modules/FastEat.h"
#include "Modules/FastLadder.h"
#include "Modules/FastStop.h"
#include "Modules/FightBot.h"
#include "Modules/Fly.h"
#include "Modules/FollowPathModule.h"
#include "Modules/fps.h"
#include "Modules/Freecam.h"
#include "Modules/Freelook.h"
#include "Modules/Fucker.h"
#include "Modules/Camera.h"
#include "Modules/Glide.h"
#include "Modules/GUI.h"
#include "Modules/HackerDetect.h"
#include "Modules/HighJump.h"
#include "Modules/Hitbox.h"
#include "Modules/HiveConfig.h"
#include "Modules/HiveFly.h"
#include "Modules/HudModule.h"
#include "Modules/HoleEsp.h"
#include "Modules/InsideAura.h"
#include "Modules/InstaBreak.h"
#include "Modules/InventoryCleaner.h"
#include "Modules/InventoryMove.h"
#include "Modules/InventoryView.h"
#include "Modules/Jesus.h"
#include "Modules/KeyStrokes.h"
#include "Modules/Killaura.h"
#include "Modules/LongJump.h"
#include "Modules/MegaDupe.h"
#include "Modules/MidClick.h"
#include "Modules/MinplexConfig.h"
#include "Modules/Module.h"
#include "Modules/NameTags.h"
#include "Modules/NightMode.h"
#include "Modules/NoClip.h"
#include "Modules/NoFall.h"
#include "Modules/NoFriends.h"
#include "Modules/NoPacket.h"
#include "Modules/NoRender.h"
#include "Modules/NoSlowDown.h"
#include "Modules/NoSwing.h"
#include "Modules/Notifications.h"
#include "Modules/NoWeb.h"
#include "Modules/Nuker.h"
#include "Modules/PacketLogger.h"
#include "Modules/PacketMultiplier.h"
#include "Modules/Partner.h"
#include "Modules/PotionAura.h"
#include "Modules/Radar.h"
#include "Modules/Rainbow.h"
#include "Modules/RainbowSky.h"
#include "Modules/Reach.h"
#include "Modules/Scaffold.h"
#include "Modules/selectionHighlight.h"
#include "Modules/ServerInfo.h"
#include "Modules/Snowball_Aimbot.h"
#include "Modules/Spammer.h"
#include "Modules/Speed.h"
#include "Modules/Spider.h"
#include "Modules/Step.h"
#include "Modules/StorageESP.h"
#include "Modules/Surround.h"
#include "Modules/SwingAnimations.h"
#include "Modules/TargetStrafe.h"
#include "Modules/Teams.h"
#include "Modules/Teleport.h"
#include "Modules/TestModule.h"
#include "Modules/TimeChanger.h"
#include "Modules/Timer.h"
#include "Modules/ToggleSounds.h"
#include "Modules/Totem.h"
#include "Modules/TPAura.h"
#include "Modules/Tracer.h"
#include "Modules/TriggerBot.h"
#include "Modules/Velocity.h"
#include "Modules/ViewModel.h"
#include "Modules/Waypoints.h"
#include "Modules/Watermark.h"
#include "Modules/XP.h"
#include "Modules/Xray.h"
#include "Modules/Zoom.h"

#include "Modules/TargetHUD.h"
#include "Modules/NoJumpDelay.h"

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
	void onPreTick(C_GameMode* gameMode);
	void onPlayerTick(C_Player* plr);
	void onWorldTick(C_GameMode* gameMode);
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
