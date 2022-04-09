#include "ModuleManager.h"
#include "../../Utils/Logger.h"
#include "../../Utils/Json.hpp"

using json = nlohmann::json;

ModuleManager::ModuleManager(GameData* gameData) {
	gameData = gameData;
}

ModuleManager::~ModuleManager() {
	initialized = false;
	auto lock = lockModuleListExclusive();
	moduleList.clear();
}

void ModuleManager::initModules() {
	logF("Initializing modules");
	{
		auto lock = lockModuleListExclusive();

		moduleList.push_back(std::shared_ptr<IModule>(new Aimbot()));
		moduleList.push_back(std::shared_ptr<IModule>(new AirJump()));
		moduleList.push_back(std::shared_ptr<IModule>(new AirStuck()));
		moduleList.push_back(std::shared_ptr<IModule>(new AirSwim()));
		moduleList.push_back(std::shared_ptr<IModule>(new AnchorAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiAnvil()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiBot()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiImmobile()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiLagBack()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiVoid()));
		moduleList.push_back(std::shared_ptr<IModule>(new ArmourHud()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoArmor()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoBuild()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoClick()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoJump()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoPot()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoSneak()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoSprint()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoTotem()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoWalk()));
		moduleList.push_back(std::shared_ptr<IModule>(new Bhop()));
		moduleList.push_back(std::shared_ptr<IModule>(new Blink()));
		moduleList.push_back(std::shared_ptr<IModule>(new BlockEsp()));
		moduleList.push_back(std::shared_ptr<IModule>(new BowAimbot()));
		moduleList.push_back(std::shared_ptr<IModule>(new bps()));
		moduleList.push_back(std::shared_ptr<IModule>(new ChestAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new ChestStealer()));
		moduleList.push_back(std::shared_ptr<IModule>(new ClickGuiMod()));
		moduleList.push_back(std::shared_ptr<IModule>(new Compass()));
		moduleList.push_back(std::shared_ptr<IModule>(new Coordinates()));
		moduleList.push_back(std::shared_ptr<IModule>(new cps()));
		moduleList.push_back(std::shared_ptr<IModule>(new Crasher()));
		moduleList.push_back(std::shared_ptr<IModule>(new Derp()));
		moduleList.push_back(std::shared_ptr<IModule>(new Disabler()));
		moduleList.push_back(std::shared_ptr<IModule>(new EditionFaker()));
		moduleList.push_back(std::shared_ptr<IModule>(new EntityBhop()));
		moduleList.push_back(std::shared_ptr<IModule>(new EntityDerp()));
		moduleList.push_back(std::shared_ptr<IModule>(new EntityFly()));
		moduleList.push_back(std::shared_ptr<IModule>(new EntityJesus()));
		moduleList.push_back(std::shared_ptr<IModule>(new EntityJetpack()));
		moduleList.push_back(std::shared_ptr<IModule>(new EntityLongJump()));
		moduleList.push_back(std::shared_ptr<IModule>(new EntitySpeed()));
		moduleList.push_back(std::shared_ptr<IModule>(new EntitySpider()));
		moduleList.push_back(std::shared_ptr<IModule>(new ESP()));
		moduleList.push_back(std::shared_ptr<IModule>(new ExtendedBlockReach()));
		moduleList.push_back(std::shared_ptr<IModule>(new FastEat()));
		moduleList.push_back(std::shared_ptr<IModule>(new FastLadder()));
		moduleList.push_back(std::shared_ptr<IModule>(new FastStop()));
		moduleList.push_back(std::shared_ptr<IModule>(new FightBot()));
		moduleList.push_back(std::shared_ptr<IModule>(new Flight()));
		moduleList.push_back(std::shared_ptr<IModule>(new FollowPathModule()));
		moduleList.push_back(std::shared_ptr<IModule>(new fps()));
		moduleList.push_back(std::shared_ptr<IModule>(new Freecam()));
		moduleList.push_back(std::shared_ptr<IModule>(new Freelook()));
		moduleList.push_back(std::shared_ptr<IModule>(new Fucker()));
		moduleList.push_back(std::shared_ptr<IModule>(new Camera()));
		moduleList.push_back(std::shared_ptr<IModule>(new Glide()));
		moduleList.push_back(std::shared_ptr<IModule>(new GUI()));
		moduleList.push_back(std::shared_ptr<IModule>(new HackerDetect()));
		moduleList.push_back(std::shared_ptr<IModule>(new HighJump()));
		moduleList.push_back(std::shared_ptr<IModule>(new Hitbox()));
		moduleList.push_back(std::shared_ptr<IModule>(new HiveConfig()));
		moduleList.push_back(std::shared_ptr<IModule>(new HiveFly()));
		moduleList.push_back(std::shared_ptr<IModule>(new HudModule()));
		moduleList.push_back(std::shared_ptr<IModule>(new InsideAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new InstaBreak()));
		moduleList.push_back(std::shared_ptr<IModule>(new InventoryCleaner()));
		moduleList.push_back(std::shared_ptr<IModule>(new InventoryMove()));
		moduleList.push_back(std::shared_ptr<IModule>(new InventoryView()));
		moduleList.push_back(std::shared_ptr<IModule>(new Jesus()));
		moduleList.push_back(std::shared_ptr<IModule>(new KeyStrokes()));
		moduleList.push_back(std::shared_ptr<IModule>(new Killaura()));
		moduleList.push_back(std::shared_ptr<IModule>(new LongJump()));
		moduleList.push_back(std::shared_ptr<IModule>(new MegaDupe()));
		moduleList.push_back(std::shared_ptr<IModule>(new MidClick()));
		moduleList.push_back(std::shared_ptr<IModule>(new MinplexConfig()));
		moduleList.push_back(std::shared_ptr<IModule>(new NameTags()));
		moduleList.push_back(std::shared_ptr<IModule>(new NightMode()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoClip()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoFall()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoFriends()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoPacket()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoRender()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoSlowDown()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoSwing()));
		moduleList.push_back(std::shared_ptr<IModule>(new Notifications()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoWeb()));
		moduleList.push_back(std::shared_ptr<IModule>(new Nuker()));
		moduleList.push_back(std::shared_ptr<IModule>(new PacketLogger()));
		moduleList.push_back(std::shared_ptr<IModule>(new PacketMultiplier()));
		moduleList.push_back(std::shared_ptr<IModule>(new Partner()));
		moduleList.push_back(std::shared_ptr<IModule>(new PotionAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new Radar()));
		moduleList.push_back(std::shared_ptr<IModule>(new Rainbow()));
		moduleList.push_back(std::shared_ptr<IModule>(new RainbowSky()));
		moduleList.push_back(std::shared_ptr<IModule>(new Reach()));
		moduleList.push_back(std::shared_ptr<IModule>(new Scaffold()));
		moduleList.push_back(std::shared_ptr<IModule>(new selectionHighlight()));
		moduleList.push_back(std::shared_ptr<IModule>(new ServerInfo()));
		moduleList.push_back(std::shared_ptr<IModule>(new SnowballAimbot()));
		moduleList.push_back(std::shared_ptr<IModule>(new Spammer()));
		moduleList.push_back(std::shared_ptr<IModule>(new Speed()));
		moduleList.push_back(std::shared_ptr<IModule>(new Spider()));
		moduleList.push_back(std::shared_ptr<IModule>(new Step()));
		moduleList.push_back(std::shared_ptr<IModule>(new StorageESP()));
		moduleList.push_back(std::shared_ptr<IModule>(new Surround()));
		moduleList.push_back(std::shared_ptr<IModule>(new SwingAnimations()));
		moduleList.push_back(std::shared_ptr<IModule>(new TargetStrafe));
		moduleList.push_back(std::shared_ptr<IModule>(new Teams()));
		moduleList.push_back(std::shared_ptr<IModule>(new Teleport()));
		moduleList.push_back(std::shared_ptr<IModule>(new TestModule()));
		moduleList.push_back(std::shared_ptr<IModule>(new TimeChanger()));
		moduleList.push_back(std::shared_ptr<IModule>(new Timer()));
		moduleList.push_back(std::shared_ptr<IModule>(new ToggleSounds()));
		moduleList.push_back(std::shared_ptr<IModule>(new Totem()));
		moduleList.push_back(std::shared_ptr<IModule>(new TPAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new Tracer()));
		moduleList.push_back(std::shared_ptr<IModule>(new TriggerBot()));
		moduleList.push_back(std::shared_ptr<IModule>(new Velocity()));
		moduleList.push_back(std::shared_ptr<IModule>(new ViewModel()));
		moduleList.push_back(std::shared_ptr<IModule>(new Waypoints()));
		moduleList.push_back(std::shared_ptr<IModule>(new Watermark()));
		moduleList.push_back(std::shared_ptr<IModule>(new XP()));
		moduleList.push_back(std::shared_ptr<IModule>(new Xray()));
		moduleList.push_back(std::shared_ptr<IModule>(new Zoom()));

		moduleList.push_back(std::shared_ptr<IModule>(new TargetHUD()));

		//
		 moduleList.push_back(std::shared_ptr<IModule>(new CrystalAura()));
		 moduleList.push_back(std::shared_ptr<IModule>(new HoleESP()));
		 moduleList.push_back(std::shared_ptr<IModule>(new EZspam()));
		 moduleList.push_back(std::shared_ptr<IModule>(new AutoEZ()));
		 moduleList.push_back(std::shared_ptr<IModule>(new AutoEZv2()));
		 moduleList.push_back(std::shared_ptr<IModule>(new AutoEZv3()));
		 moduleList.push_back(std::shared_ptr<IModule>(new NoJumpDelay()));
		//

		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{*current->getModuleName()} < std::string{*other->getModuleName()};
		});

		initialized = true;
	}
	
	getModule<HudModule>()->setEnabled(true);
	getModule<ClickGuiMod>()->setEnabled(false);
	getModule<AntiBot>()->setEnabled(true);
	getModule<GUI>()->setEnabled(true);
}

void ModuleManager::disable() {
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->setEnabled(false);
	}
}

void ModuleManager::onLoadConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onLoadConfig(conf);
	}

	getModule<HudModule>()->setEnabled(true);
	getModule<ClickGuiMod>()->setEnabled(false);
	getModule<AntiBot>()->setEnabled(true);
	getModule<GUI>()->setEnabled(true);
}

void ModuleManager::onSaveConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onSaveConfig(conf);
	}
}

void ModuleManager::onTick(C_GameMode* gameMode) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onTick(gameMode);
	}
}

void ModuleManager::onPreTick(C_GameMode* gameMode) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPreTick(gameMode);
	}
}

void ModuleManager::onWorldTick(C_GameMode* gameMode) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onWorldTick(gameMode);
	}
}

void ModuleManager::onPlayerTick(C_Player* plr) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPlayerTick(plr);
	}
}

void ModuleManager::onAttack(C_Entity* attackEnt) {
	if (!isInitialized())
		return;

	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onAttack(attackEnt);
	}
}

void ModuleManager::onKeyUpdate(int key, bool isDown) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onKeyUpdate(key, isDown);
	}
}

void ModuleManager::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPreRender(renderCtx);
	}
}

void ModuleManager::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPostRender(renderCtx);
	}
}

void ModuleManager::onSendPacket(C_Packet* packet) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onSendPacket(packet);
	}
}

std::vector<std::shared_ptr<IModule>>* ModuleManager::getModuleList() {
	return &moduleList;
}

int ModuleManager::getModuleCount() {
	return (int)moduleList.size();
}

int ModuleManager::getEnabledModuleCount() {
	int i = 0;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled()) i++;
	}
	return i;
}
void ModuleManager::onMove(C_MoveInputHandler* hand) {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onMove(hand);
	}
}
void ModuleManager::onLevelRender() {
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onLevelRender();
	}
}

ModuleManager* moduleMgr = new ModuleManager(&g_Data);
