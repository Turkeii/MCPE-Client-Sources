#include "TestModule.h"
#include "../../../Memory/Hooks.h"

TestModule::TestModule() : IModule(0x0, Category::WORLD, "For testing purposes") {
	enum1 = SettingEnum(this)
				.addEntry(EnumEntry("1", 1))
				.addEntry(EnumEntry("2", 2))
				.addEntry(EnumEntry("3", 3));

	registerFloatSetting("float1", &float1, 0, -10, 10);
	registerIntSetting("Sound", &int1, int1, 0, 500);
	registerEnumSetting("Enum1", &enum1, 0);
	registerBoolSetting("Random", &bool1, true);
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return "TestModule";
}

static std::vector<C_Entity*> tagtr;
void findjeoe(C_Entity* currentEntity, bool isRegularEntitie) {
	static auto test = moduleMgr->getModule<TestModule>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() != 63)
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < 100) {
		tagtr.push_back(currentEntity);
	}
}

void TestModule::onEnable() {
	g_Data.getLocalPlayer()->unlockAchievements();
}

void TestModule::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	//plr->pitch = 0;
	//plr->bodyYaw = 90;
	//plr->yawUnused1 = 90;
}

void TestModule::onTick(C_GameMode* gm) {
	//g_Data.getLocalPlayer()->unlockAchievments();
	if (bool1) {
		C_TextPacket textPacket;
		textPacket.message.setText("test + ");
		textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
		textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
		//g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
	}
}

void TestModule::onWorldTick(C_GameMode* gm) {
}

void TestModule::onMove(C_MoveInputHandler* hand) {
}

void TestModule::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
}

void TestModule::onSendPacket(C_Packet* packet) {
}

void TestModule::onDisable() {
	//CommandRequestPacket mpp("/q sky");
	//g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);
}

void TestModule::onLevelRender() {
}

void TestModule::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	//std::string screenName(g_Hooks.currentScreenName);
	//if (screenName != "toast_screen" && screenName != "start_screen" && screenName != "debug_screen" && screenName != "pause_screen" && screenName != "À$0a-" && screenName != "ÀA&w-")
	//DrawUtils::drawText(vec2{100, 100}, &screenName, MC_Color(0, 0, 255));

	//C_TexturePtr texture;
	//texture.filePath = TextHolder("texture/ui/hotbar_2");
	//__int64 yot = 0;
	//DrawUtils::drawImage("texture/ui/hotbar_2", vec2(100, 100), vec2(100, 300), vec2(1, 1));
	//renderCtx->drawImage(&texture, vec2(100, 100), vec2(500, 100), yot, vec2(1, 1));
}