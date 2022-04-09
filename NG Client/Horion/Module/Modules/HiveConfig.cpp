#include "HiveConfig.h"

#include "../../Module/ModuleManager.h"

HiveConfig::HiveConfig() : IModule(0x0, Category::CONFIG, "Auto Loads Best Config For Hive") {
}

HiveConfig::~HiveConfig() {
}

const char* HiveConfig::getModuleName() {
	return ("Hive");
}

void HiveConfig::onEnable() {
	//Disable All and Unbind All
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* modules = moduleMgr->getModuleList();
	for (auto it = modules->begin(); it != modules->end(); ++it) {
		auto mod = *it;
		mod->setEnabled(false);
		mod->setKey(0x0);
	}

	//Modules
	static auto HudMod = moduleMgr->getModule<HudModule>();
	static auto KillMod = moduleMgr->getModule<Killaura>();
	static auto ESPMod = moduleMgr->getModule<ESP>();
	static auto Stop = moduleMgr->getModule<FastStop>();
	static auto AutoArm = moduleMgr->getModule<AutoArmor>();
	static auto StepBro = moduleMgr->getModule<Step>();
	static auto Sprint = moduleMgr->getModule<AutoSprint>();
	static auto BowBot = moduleMgr->getModule<BowAimbot>();
	static auto Scaff = moduleMgr->getModule<Scaffold>();
	static auto Break = moduleMgr->getModule<InstaBreak>();
	static auto HackerDetector = moduleMgr->getModule<HackerDetect>();
	static auto Fuck = moduleMgr->getModule<Fucker>();
	static auto NoSlow = moduleMgr->getModule<NoSlowDown>();
	static auto ClickGUI = moduleMgr->getModule<ClickGuiMod>();
	static auto ReachMod = moduleMgr->getModule<Reach>();
	static auto Bright = moduleMgr->getModule<Camera>();
	static auto Web = moduleMgr->getModule<NoWeb>();
	static auto HiveFli = moduleMgr->getModule<HiveFly>();
	static auto JesusSUS = moduleMgr->getModule<Jesus>();
	static auto FastLAd = moduleMgr->getModule<FastLadder>();
	static auto Tags = moduleMgr->getModule<NameTags>();
	static auto Hop = moduleMgr->getModule<Bhop>();
	static auto Mid = moduleMgr->getModule<MidClick>();
	static auto Select = moduleMgr->getModule<selectionHighlight>();
	static auto AntiBotMod = moduleMgr->getModule<AntiBot>();
	static auto Cleaner = moduleMgr->getModule<InventoryCleaner>();
	static auto Team = moduleMgr->getModule<Teams>();
	static auto AntiImmo = moduleMgr->getModule<AntiImmobile>();
	static auto ViewMod = moduleMgr->getModule<ViewModel>();
	static auto ChestSteal = moduleMgr->getModule<ChestStealer>();
	static auto Disable = moduleMgr->getModule<Disabler>();
	static auto AntiKBMod = moduleMgr->getModule < Velocity> ();
	static auto SwingAnimation = moduleMgr->getModule<SwingAnimations>();
	static auto ArrayList = moduleMgr->getModule<GUI>();
	static auto Long = moduleMgr->getModule<LongJump>();
	static auto partner = moduleMgr->getModule<Partner>();

	//Toggle All Needed Mods
	HudMod->setEnabled(true);
	ClickGUI->setEnabled(false);
	AntiBotMod->setEnabled(true);
	Select->setEnabled(true);
	AntiKBMod->setEnabled(true);
	AntiImmo->setEnabled(true);
	HackerDetector->setEnabled(true);
	NoSlow->setEnabled(true);
	ChestSteal->setEnabled(true);
	BowBot->setEnabled(true);
	AutoArm->setEnabled(true);
	FastLAd->setEnabled(true);
	ViewMod->setEnabled(true);
	Sprint->setEnabled(true);
	Break->setEnabled(true);
	Cleaner->setEnabled(true);
	Tags->setEnabled(true);
	Bright->setEnabled(true);
	Stop->setEnabled(true);
	Mid->setEnabled(true);
	Disable->setEnabled(true);
	Fuck->setEnabled(true);
	Web->setEnabled(true);
	ReachMod->setEnabled(true);
	JesusSUS->setEnabled(true);
	StepBro->setEnabled(true);
	ESPMod->setEnabled(true);
	Team->setEnabled(true);
	//SwingAnimation->setEnabled(true);

	//Set All Settings

	//Killaura
	KillMod->setKey('F');
	KillMod->range = 4.50f;
	KillMod->delay = 2.f;
	KillMod->rots.selected = 1;
#ifdef _DEBUG
	KillMod->targ.selected = 1;
#else
	KillMod->targ.selected = 0;
#endif
	// Breaker
	partner->Partnered.selected = 0;
	// Killaura
	KillMod->info = true;
	KillMod->hurttime = false;
	KillMod->isMobAura = false;
	KillMod->noSwing = false;
	//Scaffold
	Scaff->setKey('G');
	Scaff->staircaseMode = true;
	Scaff->fagNigas = true;
	Scaff->UpwardsFlyinNigas = 0.50f;
	Scaff->autoselect = true;
	Scaff->Fullselect = true;
	Scaff->spoof = false;
	Scaff->spam = false;
	Scaff->rot = true;
	Scaff->SukinMyBigJuicyAss = true;
	Scaff->noSwing = true;
	Scaff->yLock = false;
	Scaff->predict = true;
	Scaff->GayNigaFags = true;
	Scaff->THICCC = false;
	//Bhop
	Hop->setKey('C');
	Hop->speed = 0.90;
	Hop->hive = true;
	//Breaker
	Fuck->setKey('V');
	Fuck->noSwing = true;
	Fuck->redstone = true;
	Fuck->bypass = true;
	Fuck->rots = false;
	Fuck->treasures = true;
	Fuck->chests = false;
	Fuck->range = 3;
	//Teams
	Team->colorCheck = true;
	//Disabler
	Disable->hive = true;
	//Selection Highlight
	Select->thickness = 0.40f;
	Select->opacityVal = 1.f;
	Select->selectRainbow = false;
	Select->doOutline = true;
	Select->rSelect = 1.f;
	Select->bSelect = 1.f;
	Select->gSelect = 1.f;
	//HiveFly
	//HiveFli->setKey('R');
	//HiveFli->clip = false;
	//HiveFli->clipHeight = 5.f;
	//LongJump
	Long->setKey('X');
	Long->slow = true;
	Long->hit = true;
	Long->speed = 1.63f;
	Long->height = 0.52f;
	//BowAimbot
	BowBot->predict = true;
	BowBot->visualize = true;
	//Step
	StepBro->height = 2.f;
	//ESP
	ESPMod->betterESP = false;
	ESPMod->circle = false;
	ESPMod->doRainbow = false;
	ESPMod->is2d = false;
	ESPMod->iszephyr = true;
	ESPMod->isMobEsp = false;
	//FullBright
	Bright->intensity = 25.f;
	//NameTags
	Tags->displayArmor = true;
	Tags->underline = true;
	Tags->opacity = .12f;
	//Viewmodel
	ViewMod->xTrans = 0.35f;
	ViewMod->yTrans = 0.06f;
	ViewMod->zTrans = -0.74f;
	ViewMod->doTranslate = true;
	ViewMod->doScale = false;
	ViewMod->doRotation = false;
	ViewMod->spin = false;
	//AutoSprint
	Sprint->alldirections = true;
	//FastLadder
	FastLAd->speed = 0.60f;
	//AntiBot
	AntiBotMod->hitboxCheck = true;
	AntiBotMod->extraCheck = false;
	AntiBotMod->entityIdCheck = true;
	AntiBotMod->nameCheck = true;
	AntiBotMod->otherCheck = false;
	AntiBotMod->invisibleCheck = false;
	//ChestStealer
	ChestSteal->delay = 0;
	ChestSteal->enhanced = true;
	ChestSteal->dump = false;
	//InvCleaner
	Cleaner->setKey('N');
	Cleaner->autoSort = true;
	Cleaner->keepArmor = true;
	Cleaner->keepBlocks = true;
	Cleaner->keepBow = false;
	Cleaner->keepFood = true;
	Cleaner->keepPick = false;
	Cleaner->keepShovel = false;
	Cleaner->keepTools = true;
	Cleaner->openInv = false;
	//ClickGUI
	ClickGUI->setKey(VK_TAB);
	ClickGUI->showTooltips = true;
	//Arraylist
	ArrayList->Fluxbar = true;
	ArrayList->bar = false;
	ArrayList->underbar = false;
	ArrayList->rgb = true;
	ArrayList->ice = false;
	ArrayList->bottom = false;
	ArrayList->opacity = 0.26f;
	ArrayList->rcolor = 0.f;
	ArrayList->gcolor = 0.f;
	ArrayList->bcolor = 0.f;
	//HUDModule
	HudMod->Hud = true;
	HudMod->rgb = false;
	HudMod->Msg = false;
	HudMod->watermark = true;
	HudMod->notifications = false;
	HudMod->bools = false;
	HudMod->keybinds = true;
	HudMod->keystrokes = false;
	HudMod->displaySecondHalf = false;
	HudMod->alwaysShow = false;
	HudMod->opacity = 0.28f;
	HudMod->scale = 0.75f;
	//InstaBreak
	Break->mode.selected = 1;
	//Reach
	ReachMod->reachValue = 7.f;
	//Swing Animations
	SwingAnimation->swing.selected = 2;

	//Tell User Binds
	g_Data.getGuiData()->displayClientMessageF("=======================================");
	for (auto it = modules->begin(); it != modules->end(); ++it) {
		auto mod = *it;
		auto modOpt = mod;
		if (Utils::getKeyName(mod->getKey()) != "Unknown") {
			if (partner->Partnered.selected == 0)
				g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] %s is currently bound to %s", WHITE, BLUE, WHITE, mod->getModuleName(), Utils::getKeyName(mod->getKey()));
			else
				g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s] %s is currently bound to %s", WHITE, LIGHT_PURPLE, WHITE, mod->getModuleName(), Utils::getKeyName(mod->getKey()));
		}
	}

	//Success
	if (partner->Partnered.selected == 0) {
		g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s]%s Successfully Made Config!", WHITE, BLUE, WHITE, BLUE);
	} else {
		g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s]%s Successfully Made Config!", WHITE, LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
	}

	//Tell Dumbass To Save Config
	g_Data.getGuiData()->displayClientMessageF("%s[%sAutoConfig%s]%s Type %s.config save%s to save your config!", WHITE, GREEN, WHITE, GREEN, WHITE, GREEN);
}
