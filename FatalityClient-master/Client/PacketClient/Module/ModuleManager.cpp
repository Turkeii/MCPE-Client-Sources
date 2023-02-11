#include "ModuleManager.h"
#include "../../Utils/Logger.h"
#include "../../Utils/Json.hpp"

using json = nlohmann::json;

ModuleManager::ModuleManager(GameData* gameData) {
	this->gameData = gameData;
}

ModuleManager::~ModuleManager() {
	initialized = false;
	auto lock = this->lockModuleListExclusive();
	this->moduleList.clear();
}

void ModuleManager::initModules() {
	{
		auto lock = this->lockModuleListExclusive();

		// Menu
		moduleList.push_back(std::shared_ptr<IModule>(new ConfigManagerMod()));
		moduleList.push_back(std::shared_ptr<IModule>(new ClickGUIMod()));
		moduleList.push_back(std::shared_ptr<IModule>(new DebugMenu()));

		// Combat
		moduleList.push_back(std::shared_ptr<IModule>(new AutoClicker()));
		moduleList.push_back(std::shared_ptr<IModule>(new CrystalAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new TriggerBot()));
		moduleList.push_back(std::shared_ptr<IModule>(new Criticals()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoPlay()));
		moduleList.push_back(std::shared_ptr<IModule>(new Killaura()));
		moduleList.push_back(std::shared_ptr<IModule>(new Switcher()));
		moduleList.push_back(std::shared_ptr<IModule>(new HitBoxes()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiBot()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoPot()));
		moduleList.push_back(std::shared_ptr<IModule>(new Aimbot()));
		moduleList.push_back(std::shared_ptr<IModule>(new TPAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new Reach()));
		moduleList.push_back(std::shared_ptr<IModule>(new Regen()));
		moduleList.push_back(std::shared_ptr<IModule>(new Teams()));

		// Visual
		moduleList.push_back(std::shared_ptr<IModule>(new Notifications()));
		moduleList.push_back(std::shared_ptr<IModule>(new BlockOutline()));
		moduleList.push_back(std::shared_ptr<IModule>(new BreadCrumbs()));
		moduleList.push_back(std::shared_ptr<IModule>(new SessionInfo()));
		moduleList.push_back(std::shared_ptr<IModule>(new Animations()));
		moduleList.push_back(std::shared_ptr<IModule>(new PlayerList()));
		moduleList.push_back(std::shared_ptr<IModule>(new ArrayList()));
		moduleList.push_back(std::shared_ptr<IModule>(new CustomSky()));
		moduleList.push_back(std::shared_ptr<IModule>(new Interface()));
		moduleList.push_back(std::shared_ptr<IModule>(new TargetHUD()));
		moduleList.push_back(std::shared_ptr<IModule>(new Watermark()));
		moduleList.push_back(std::shared_ptr<IModule>(new Ambience()));
		moduleList.push_back(std::shared_ptr<IModule>(new BlockESP()));
		moduleList.push_back(std::shared_ptr<IModule>(new ChestESP()));
		moduleList.push_back(std::shared_ptr<IModule>(new Freelook()));
		moduleList.push_back(std::shared_ptr<IModule>(new NameTags()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoRender()));
		moduleList.push_back(std::shared_ptr<IModule>(new Camera()));
		moduleList.push_back(std::shared_ptr<IModule>(new Radar()));
		moduleList.push_back(std::shared_ptr<IModule>(new Zoom()));
		moduleList.push_back(std::shared_ptr<IModule>(new Xray()));
		moduleList.push_back(std::shared_ptr<IModule>(new ESP()));
#ifdef _DEBUG
		//moduleList.push_back(std::shared_ptr<IModule>(new Waypoints()));
#endif

		// Movement
		moduleList.push_back(std::shared_ptr<IModule>(new TargetStrafe()));
		moduleList.push_back(std::shared_ptr<IModule>(new SafeWalk()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiVoid()));
		moduleList.push_back(std::shared_ptr<IModule>(new FastStop()));
		moduleList.push_back(std::shared_ptr<IModule>(new LongJump()));
		moduleList.push_back(std::shared_ptr<IModule>(new Velocity()));
		moduleList.push_back(std::shared_ptr<IModule>(new InvMove()));
		moduleList.push_back(std::shared_ptr<IModule>(new Flight()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoSlow()));
		moduleList.push_back(std::shared_ptr<IModule>(new Spider()));
		moduleList.push_back(std::shared_ptr<IModule>(new Sprint()));
		moduleList.push_back(std::shared_ptr<IModule>(new Jesus()));
		moduleList.push_back(std::shared_ptr<IModule>(new Speed()));
		moduleList.push_back(std::shared_ptr<IModule>(new Step()));
#ifdef _DEBUG
		moduleList.push_back(std::shared_ptr<IModule>(new HiveFly()));
		moduleList.push_back(std::shared_ptr<IModule>(new KBFly()));
#endif

		// Player
		moduleList.push_back(std::shared_ptr<IModule>(new ChestStealer()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoJumpDelay()));
		moduleList.push_back(std::shared_ptr<IModule>(new BlockReach()));
		moduleList.push_back(std::shared_ptr<IModule>(new InvManager()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoTotem()));
		moduleList.push_back(std::shared_ptr<IModule>(new FastPlace()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoRotate()));
		moduleList.push_back(std::shared_ptr<IModule>(new Scaffold()));
		moduleList.push_back(std::shared_ptr<IModule>(new Freecam()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoSwing()));
		moduleList.push_back(std::shared_ptr<IModule>(new Blink()));
		moduleList.push_back(std::shared_ptr<IModule>(new Timer()));
		moduleList.push_back(std::shared_ptr<IModule>(new XP()));

		// Exploit
		moduleList.push_back(std::shared_ptr<IModule>(new PacketMultiplier()));
		moduleList.push_back(std::shared_ptr<IModule>(new HackerDetector()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiImmobile()));
		moduleList.push_back(std::shared_ptr<IModule>(new ChatBypass()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoLagBack()));
		moduleList.push_back(std::shared_ptr<IModule>(new SpeedMine()));
		moduleList.push_back(std::shared_ptr<IModule>(new Disabler()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoPacket()));
		moduleList.push_back(std::shared_ptr<IModule>(new FastUse()));
		moduleList.push_back(std::shared_ptr<IModule>(new Crasher()));
		moduleList.push_back(std::shared_ptr<IModule>(new FreeTP()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoFall()));
		moduleList.push_back(std::shared_ptr<IModule>(new Phase()));

		// Other
		moduleList.push_back(std::shared_ptr<IModule>(new ToggleSounds()));
		moduleList.push_back(std::shared_ptr<IModule>(new DeathEffects()));
		moduleList.push_back(std::shared_ptr<IModule>(new FollowPath()));
		moduleList.push_back(std::shared_ptr<IModule>(new HitEffects()));
		moduleList.push_back(std::shared_ptr<IModule>(new ChatSuffix()));
		moduleList.push_back(std::shared_ptr<IModule>(new Killsults()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoHive()));
		moduleList.push_back(std::shared_ptr<IModule>(new Breaker()));
		moduleList.push_back(std::shared_ptr<IModule>(new Spammer()));
		moduleList.push_back(std::shared_ptr<IModule>(new ClickTP()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoGG()));
		moduleList.push_back(std::shared_ptr<IModule>(new ItemTP()));
		moduleList.push_back(std::shared_ptr<IModule>(new Nuker()));
		moduleList.push_back(std::shared_ptr<IModule>(new Derp()));
		moduleList.push_back(std::shared_ptr<IModule>(new MCF()));

#ifdef _DEBUG
		moduleList.push_back(std::shared_ptr<IModule>(new PacketLogger()));
		moduleList.push_back(std::shared_ptr<IModule>(new TestModule()));
		//moduleList.push_back(std::shared_ptr<IModule>(new FallSave()));
#endif

		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{*current->getModuleName()} < std::string{*other->getModuleName()};
		});
		initialized = true;
	}
	
	getModule<Notifications>()->setEnabled(true);
	getModule<ClickGUIMod>()->setEnabled(false);
	getModule<Killaura>()->setEnabled(false);
	getModule<Interface>()->setEnabled(true);
	getModule<ArrayList>()->setEnabled(true);
	getModule<Watermark>()->setEnabled(true);
	getModule<AntiBot>()->setEnabled(true);
	getModule<AntiBot>()->setEnabled(true);
	getModule<Sprint>()->setEnabled(true);
}

void ModuleManager::disable() {
	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		if (mod->isEnabled())
			mod->setEnabled(false);
	}
}

void ModuleManager::onLoadConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized()) return;

	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		mod->onLoadConfig(conf);
	}

	if (!getModule<Step>()->isEnabled() && g_Data.getLocalPlayer() != nullptr) g_Data.getLocalPlayer()->stepHeight = 0.5625f;
	getModule<ClickGUIMod>()->setEnabled(false);
}

void ModuleManager::onSaveConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized()) return;

	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		mod->onSaveConfig(conf);
	}
}

void ModuleManager::onLoadSettings(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized()) return;

	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		mod->onLoadSettings(conf);
	}
	getModule<ClickGUIMod>()->setEnabled(false);
}

void ModuleManager::onSaveSettings(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized()) return;

	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		mod->onSaveSettings(conf);
	}
}

void ModuleManager::onPlayerTick(C_Player* plr) {
	if (!isInitialized()) return;

	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPlayerTick(plr);
	}
}

void ModuleManager::onWorldTick(C_GameMode* gameMode) {
	if (!isInitialized()) return;

	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onWorldTick(gameMode);
	}
}

void ModuleManager::onTick(C_GameMode* gameMode) {
	if (!isInitialized()) return;

	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onTick(gameMode);
	}
}

void ModuleManager::onAttack(C_Entity* attackEnt) {
	if (!isInitialized()) return;

	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onAttack(attackEnt);
	}
}

void ModuleManager::onKeyUpdate(int key, bool isDown) {
	if (!isInitialized()) return;

	auto lock = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		mod->onKeyUpdate(key, isDown);
	}
}

void ModuleManager::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized()) return;

	auto mutex = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPreRender(renderCtx);
	}
}

void ModuleManager::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized()) return;

	auto mutex = this->lockModuleList();
	for (auto& mod : this->moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPostRender(renderCtx);
	}
}

void ModuleManager::onSendPacket(C_Packet* packet) {
	if (!isInitialized()) return;

	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onSendPacket(packet);
	}
}

std::vector<std::shared_ptr<IModule>>* ModuleManager::getModuleList() {
	return &this->moduleList;
}

int ModuleManager::getModuleCount() {
	return (int)moduleList.size();
}

int ModuleManager::getEnabledModuleCount() {
	int i = 0;
	auto lock = this->lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled()) i++;
	}
	return i;
}

void ModuleManager::onMove(C_MoveInputHandler* hand) {
	if (!isInitialized()) return;

	auto lock = this->lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onMove(hand);
	}
}

void ModuleManager::onLevelRender() {
	if (!isInitialized()) return;
	auto lock = this->lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled()) it->onLevelRender();
	}
}

ModuleManager* moduleMgr = new ModuleManager(&g_Data);