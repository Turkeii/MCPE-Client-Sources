#include "HudEditor.h"
#include <Windows.h>

//bool findBlocks(C_ItemStack* itemStack);
static bool isLeftClickDown1 = false;
static bool isRightClickDown1 = false;
static bool shouldToggleLeftClick1 = false;  // If true, toggle the focused module
static bool shouldToggleRightClick1 = false;


static bool notificationsIsDragging = false;
static bool sessionInfoIsDragging = false;
static bool playerListIsDragging = false;
static bool arrayListIsDragging = false;
static bool targetHUDIsDragging = false;
static bool watermarkIsDragging = false;
static bool scaffoldIsDragging = false;
static bool armHudIsDragging = false;
static bool buildIsDragging = false;
static bool fpsIsDragging = false;
static bool bpsIsDragging = false;
static bool posIsDragging = false;
static float defaultX = 0;
static float defaultY = 0;

//unsigned int focusedElement = -1;
//unsigned int draggedWindow = -1;
static vec2_t dragStartHudEditor = vec2_t();
//bool isFocused = false;

static bool hasInitializedHE = false;
static int timesRenderedHE = 0;

using namespace std;

void HudEditor::render() {
	auto player = g_Data.getLocalPlayer();
	bool rightClickDown = g_Data.isRightClickDown;
	bool leftClickDown = g_Data.isLeftClickDown();
	auto interfaceMod = moduleMgr->getModule<Interface>();
	static auto arrayList = moduleMgr->getModule<ArrayList>();
	static auto notifications = moduleMgr->getModule<Notifications>();
	static auto targetHUD = moduleMgr->getModule<TargetHUD>();
	static auto watermark = moduleMgr->getModule<Watermark>();
	static auto scaffold = moduleMgr->getModule<Scaffold>();
	static auto sessionInfo = moduleMgr->getModule<SessionInfo>();
	static auto playerList = moduleMgr->getModule<PlayerList>();
	static auto clickGUI = moduleMgr->getModule<ClickGUIMod>();

	vec3_t* currPos = g_Data.getLocalPlayer()->getPos();
	vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2_t mousePos = *g_Data.getClientInstance()->getMousePos();
	// Convert mousePos to visual Pos
	{
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;

		mousePos = mousePos.div(windowSizeReal);
		mousePos = mousePos.mul(windowSize);
	}
	static const float rectHeight2 = (5, 5) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();

	auto hudColor = ColorUtil::rainbowColor(8, 1.F, 1.F, 1);
	if (interfaceMod->color.getSelectedValue() == 0) hudColor = ColorUtil::rainbowColor(5, interfaceMod->saturation, 1, 1);
	if (interfaceMod->color.getSelectedValue() == 1) hudColor = ColorUtil::astolfoRainbow(5, 1000); //Astolfo

	string position = "Position: " + to_string((int)floorf(currPos->x)) + " " + to_string((int)floorf(currPos->y)) + " " + to_string((int)floorf(currPos->z));
	string speedText = "Speed: " + to_string((int)player->getBlocksPerSecond()) + string(".") + to_string((int)(player->getBlocksPerSecond() * 10) - ((int)player->getBlocksPerSecond() * 10));
	string fpsText = "FPS: " + to_string(g_Data.getFPS());
	string totalCountAids = "64";
	string example = "Example Notification";
	string strLength = "V2.11 - Developer Build   ";
	float lFPS = DrawUtils::getTextWidth(&fpsText, 1) + 6.5;
	float lPos = DrawUtils::getTextWidth(&position, 1) + 6.5;
	float lSpeed = DrawUtils::getTextWidth(&speedText, 1) + 6.5;
	float lNotif = DrawUtils::getTextWidth(&example, 1) + 6.5;
	float infoTextLength = DrawUtils::getTextWidth(&strLength) + DrawUtils::getTextWidth(&string(""), 0.7) + 2;
	static const float height = (1 + 0.7 * 1) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();
	constexpr float borderPadding = 1;
	float margin = 2.f;
	vec4_t fpsRectPos = vec4_t(interfaceMod->fpsX, interfaceMod->fpsY + 4, lFPS + interfaceMod->fpsX, interfaceMod->fpsY + 20);
	vec4_t notificationRect = vec4_t(notifications->positionX, notifications->positionY + 4, lNotif + notifications->positionX, notifications->positionY + 20);
	vec2_t notificationText = vec2_t(notificationRect.x + 2, notificationRect.y);
	vec4_t speedRectPos = vec4_t(interfaceMod->bpsX, interfaceMod->bpsY + 6, lSpeed + interfaceMod->bpsX, interfaceMod->bpsY + 20);
	vec4_t rectPos = vec4_t(interfaceMod->posX, interfaceMod->posY + 6, lPos + interfaceMod->posX, interfaceMod->posY + 20);
	vec4_t testRect = vec4_t(targetHUD->positionX, targetHUD->positionY, targetHUD->targetLen + targetHUD->positionX, targetHUD->positionY + rectHeight2);
	vec4_t watermarkRect = vec4_t(watermark->positionX - 1.f, watermark->positionY - 3.f, watermark->aidsLen + watermark->positionX + 1.f, watermark->positionY + watermark->height);
	vec4_t scaffoldRect = vec4_t(scaffold->scX, scaffold->scY, 20 + scaffold->scX, scaffold->scY + 15);
	vec2_t blockPos(scaffoldRect.x + 5, scaffoldRect.y + 7);
	vec4_t infoRect = vec4_t(interfaceMod->releaseX, interfaceMod->releaseY + 4, infoTextLength + interfaceMod->releaseX, interfaceMod->releaseY + 20);
	vec4_t rectPos2 = vec4_t(arrayList->positionX - 50, arrayList->positionY, arrayList->positionX, arrayList->positionY + 10);
	if (arrayList->invert) rectPos2 = vec4_t(arrayList->positionX - 50, arrayList->positionY - 10, arrayList->positionX, arrayList->positionY);
	vec4_t armorHudRect = vec4_t(interfaceMod->armorX, interfaceMod->armorY, 70 + interfaceMod->armorX, interfaceMod->armorY + 13);
	vec4_t sessionInfoRect = vec4_t(sessionInfo->siX, sessionInfo->siY, sessionInfo->siX + sessionInfo->aidsLen, sessionInfo->siY + 55);

	vec4_t clickGUIRect = vec4_t(windowSize.x / 2 - 35, windowSize.y / 2 - 8, windowSize.x / 2 + 35, windowSize.y / 2 + 8);
	if (clickGUIRect.contains(&mousePos)) {
		DrawUtils::fillRoundRectangle(clickGUIRect, MC_Color(255, 2555, 255, 100), true);
		if (clickGUIRect.contains(&mousePos) && leftClickDown) {
			clickGUI->hasOpenedGUI = true;
			shouldToggleLeftClick1 = false;
		}
	}
	DrawUtils::drawText(vec2_t(clickGUIRect.x + 17, clickGUIRect.y + 4), &string("Modules"), MC_Color(255, 255, 255), 1.F, 1.F, true);
	DrawUtils::drawCenteredString(vec2_t(windowSize.x / 2, windowSize.y / 2 - 20), &string("Packet Client"), 1.5f, MC_Color(255, 255, 255), true);
	DrawUtils::fillRoundRectangle(clickGUIRect, MC_Color(0, 0, 0, 100), false);
	DrawUtils::drawRoundRectangle2(clickGUIRect, MC_Color(255, 255, 255));
	
	const bool fpsIsFocused = fpsRectPos.contains(&mousePos);
	const bool playerListisFocused = playerList->rectPos2.contains(&mousePos);
	const bool sessionInfoIsFocused = sessionInfoRect.contains(&mousePos);
	const bool buildIsFocused = infoRect.contains(&mousePos);
	const bool bpsIsFocused = speedRectPos.contains(&mousePos);
	const bool posIsFocused = rectPos.contains(&mousePos);
	const bool targetHUDIsFocused = testRect.contains(&mousePos);
	const bool watermarkIsFocused = watermarkRect.contains(&mousePos);
	const bool scaffoldIsFocused = scaffoldRect.contains(&mousePos);
	const bool notificationsIsFocused = notificationRect.contains(&mousePos);
	const bool armorHudIsFocused = armorHudRect.contains(&mousePos);
	
	// ?? 
	/*C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
	for (int s = 0; s < 9; s++) {
		C_ItemStack* stack = inv->getItemStack(s);
		if (stack->item != nullptr && stack->getItem()->isBlock() && findBlocks(stack)) {
			if (stack->isValid()) DrawUtils::drawItem(stack, vec2_t(blockPos.x - 4, blockPos.y - 7), 1, 1, false);
		}
	}*/ 

	DrawUtils::drawText(blockPos, &totalCountAids, MC_Color(255, 255, 255), 1.F, 1.F, true);
	if (interfaceMod->info) DrawUtils::drawRectangle(fpsRectPos, MC_Color(0, 0, 0), 0.5F);
	if (interfaceMod->armorHUD) DrawUtils::drawRectangle(armorHudRect, MC_Color(0, 0, 0), 0.5F);
	if (interfaceMod->info) DrawUtils::fillRectangleA(fpsRectPos, MC_Color(255, 255, 255, 100));
	if (interfaceMod->armorHUD) DrawUtils::fillRectangleA(armorHudRect, MC_Color(255, 255, 255, 100));
	if (interfaceMod->release) DrawUtils::drawRectangle(infoRect, MC_Color(0, 0, 0), 0.5F);
	if (interfaceMod->release) DrawUtils::fillRectangleA(infoRect, MC_Color(255, 255, 255, 100));
	if (watermark->isEnabled()) DrawUtils::drawRectangle(watermarkRect, MC_Color(255, 255, 255), 1.F);
	if (interfaceMod->info) DrawUtils::drawRectangle(speedRectPos, MC_Color(0, 0, 0), 0.5F);
	if (interfaceMod->info) DrawUtils::fillRectangleA(speedRectPos, MC_Color(255, 255, 255, 100));
	if (interfaceMod->info) DrawUtils::drawRectangle(rectPos, MC_Color(0, 0, 0), 0.5F);
	if (interfaceMod->info) DrawUtils::fillRectangleA(rectPos, MC_Color(255, 255, 255, 100));
	if (targetHUD->isEnabled()) DrawUtils::drawRectangle(testRect, MC_Color(255, 255, 255), 1.f);
	if (targetHUD->isEnabled() && targetHUDIsFocused) DrawUtils::fillRoundRectangle(testRect, MC_Color(255, 255, 255, 255), false);
	if (sessionInfo->isEnabled() && sessionInfoIsFocused) DrawUtils::fillRoundRectangle(sessionInfoRect, MC_Color(255, 255, 255, 100), true);
	DrawUtils::drawRectangle(scaffoldRect, MC_Color(255, 255, 255), 1.F);

	//keybd_event(0x41, 0, KEYEVENTF_EXTENDEDKEY, 0);
	vec4_t t = vec4_t(20, 20, 200, 30);
	vec2_t stringPos = vec2_t(t.x, t.y);
	const bool tesdr = t.contains(&mousePos);
	string aids;
	//if (GetAsyncKeyState('F')) {
		//aids = aids += "a";
	//}

		//keybd_event(0x41, 0, KEYEVENTF_EXTENDEDKEY, 0);
	
	
	//DrawUtils::drawText(stringPos, &aids, MC_Color(255, 255, 255), 1.f, 1.f, true);
	//DrawUtils::fillRectangleA(t, MC_Color(0, 0, 0, 100));

	if (arrayListIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			arrayList->positionY = arrayList->positionY + diff.y;
			arrayList->positionX = arrayList->positionX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (arrayList->positionX > windowSize.x)
					arrayList->positionX = windowSize.x;

				if (arrayList->positionY > windowSize.y)
					arrayList->positionY = windowSize.y;

				arrayList->positionX = (float)fmax(0, arrayList->positionX);
				arrayList->positionY = (float)fmax(0, arrayList->positionY);
			}
		}
		else {
			arrayListIsDragging = false;
		}
	}
	else if (arrayList->focused && leftClickDown) {
		arrayListIsDragging = true;
		dragStartHudEditor = mousePos;
	}

	if (playerListIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			playerList->positionY = playerList->positionY + diff.y;
			playerList->positionX = playerList->positionX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (playerList->positionX > windowSize.x)
					playerList->positionX = windowSize.x;

				if (playerList->positionY > windowSize.y)
					playerList->positionY = windowSize.y;

				playerList->positionX = (float)fmax(0, playerList->positionX);
				playerList->positionY = (float)fmax(0, playerList->positionY);
			}
		}
		else {
			playerListIsDragging = false;
		}
	}
	else if (playerListisFocused && leftClickDown) {
		playerListIsDragging = true;
		dragStartHudEditor = mousePos;
	}

	if (sessionInfoIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			sessionInfo->siY = sessionInfo->siY + diff.y;
			sessionInfo->siX = sessionInfo->siX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (sessionInfo->siX > windowSize.x)
					sessionInfo->siX = windowSize.x;

				if (sessionInfo->siY > windowSize.y)
					sessionInfo->siY = windowSize.y;

				sessionInfo->siX = (float)fmax(0, sessionInfo->siX);
				sessionInfo->siY = (float)fmax(0, sessionInfo->siY);
			}
		}
		else {
			sessionInfoIsDragging = false;
		}
	}
	else if (sessionInfoIsFocused && leftClickDown) {
		sessionInfoIsDragging = true;
		dragStartHudEditor = mousePos;
	}

	if (armHudIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			interfaceMod->armorY = interfaceMod->armorY + diff.y;
			interfaceMod->armorX = interfaceMod->armorX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (interfaceMod->armorX > windowSize.x)
					interfaceMod->armorX = windowSize.x;

				if (interfaceMod->armorY > windowSize.y)
					interfaceMod->armorY = windowSize.y;

				interfaceMod->armorX = (float)fmax(0, interfaceMod->armorX);
				interfaceMod->armorY = (float)fmax(0, interfaceMod->armorY);
			}
		}
		else {
			armHudIsDragging = false;
		}
	}
	else if (armorHudIsFocused && leftClickDown) {
		armHudIsDragging = true;
		dragStartHudEditor = mousePos;
	}

	if (buildIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			interfaceMod->releaseY = interfaceMod->releaseY + diff.y;
			interfaceMod->releaseX = interfaceMod->releaseX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (interfaceMod->releaseX + 42 > windowSize.x)
					interfaceMod->releaseX = windowSize.x - 42;

				if (interfaceMod->releaseY + 15 > windowSize.y)
					interfaceMod->releaseY = windowSize.y - 15;

				interfaceMod->releaseX = (float)fmax(0, interfaceMod->releaseX);
				interfaceMod->releaseY = (float)fmax(0, interfaceMod->releaseY);
			}
		}
		else {
			buildIsDragging = false;
		}
	}
	else if (buildIsFocused && leftClickDown) {
		buildIsDragging = true;
		dragStartHudEditor = mousePos;
	}

	if (notificationsIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			notifications->positionY = notifications->positionY + diff.y;
			notifications->positionX = notifications->positionX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (notifications->positionX + 42 > windowSize.x)
					notifications->positionX = windowSize.x - 42;

				if (notifications->positionY + 15 > windowSize.y)
					notifications->positionY = windowSize.y - 15;

				notifications->positionX = (float)fmax(0, notifications->positionX);
				notifications->positionY = (float)fmax(0, notifications->positionY);
			}
		}
		else {
			notificationsIsDragging = false;
		}
	}
	else if (notificationsIsFocused && leftClickDown) {
		notificationsIsDragging = true;
		dragStartHudEditor = mousePos;
	}

	if (fpsIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			interfaceMod->fpsY = interfaceMod->fpsY + diff.y;
			interfaceMod->fpsX = interfaceMod->fpsX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (interfaceMod->fpsX + 42 > windowSize.x)
					interfaceMod->fpsX = windowSize.x - 42;

				if (interfaceMod->fpsY + 15 > windowSize.y)
					interfaceMod->fpsY = windowSize.y - 15;

				interfaceMod->fpsX = (float)fmax(0, interfaceMod->fpsX);
				interfaceMod->fpsY = (float)fmax(0, interfaceMod->fpsY);
			}
		}
		else {
			fpsIsDragging = false;
		}
	}
	else if (fpsIsFocused && leftClickDown) {
		fpsIsDragging = true;
		dragStartHudEditor = mousePos;
	}

	if (scaffoldIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			scaffold->scY = scaffold->scY + diff.y;
			scaffold->scX = scaffold->scX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (scaffold->scX + 20 > windowSize.x)
					scaffold->scX = windowSize.x - 20;

				if (scaffold->scY + 15 > windowSize.y)
					scaffold->scY = windowSize.y - 15;

				scaffold->scX = (float)fmax(0, scaffold->scX);
				scaffold->scY = (float)fmax(0, scaffold->scY);
			}
		}
		else {
			scaffoldIsDragging = false;
		}
	}
	else if (scaffoldIsFocused && leftClickDown) {
		dragStartHudEditor = mousePos;
		scaffoldIsDragging = true;
	}

	if (watermarkIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			watermark->positionY = watermark->positionY + diff.y;
			watermark->positionX = watermark->positionX + diff.x;
			dragStartHudEditor = mousePos;
		}
		else {
			watermarkIsDragging = false;
		}
	}
	else if (watermarkIsFocused && leftClickDown) {
		dragStartHudEditor = mousePos;
		watermarkIsDragging = true;
	}

	if (targetHUDIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			targetHUD->positionY = targetHUD->positionY + diff.y;
			targetHUD->positionX = targetHUD->positionX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (targetHUD->positionX + 120 > windowSize.x)
					targetHUD->positionX = windowSize.x - 120;

				if (targetHUD->positionY + 50 > windowSize.y)
					targetHUD->positionY = windowSize.y - 50;

				targetHUD->positionX = (float)fmax(0, targetHUD->positionX);
				targetHUD->positionY = (float)fmax(0, targetHUD->positionY);
			}
		}
		else {
			targetHUDIsDragging = false;
		}
	}
	else if (targetHUDIsFocused && leftClickDown) {
		dragStartHudEditor = mousePos;
		targetHUDIsDragging = true;
	}


	if (bpsIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			interfaceMod->bpsY = interfaceMod->bpsY + diff.y;
			interfaceMod->bpsX = interfaceMod->bpsX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (interfaceMod->bpsX + 55 > windowSize.x)
					interfaceMod->bpsX = windowSize.x - 55;

				if (interfaceMod->bpsY + 20 > windowSize.y)
					interfaceMod->bpsY = windowSize.y - 20;

				interfaceMod->bpsX = (float)fmax(0, interfaceMod->bpsX);
				interfaceMod->bpsY = (float)fmax(0, interfaceMod->bpsY);
			}
		}
		else {
			bpsIsDragging = false;
		}
	}
	else if (bpsIsFocused && leftClickDown) {
		dragStartHudEditor = mousePos;
		bpsIsDragging = true;
	}

	if (posIsDragging) {
		if (leftClickDown) {
			vec2_t diff = vec2_t(mousePos).sub(dragStartHudEditor);
			interfaceMod->posY = interfaceMod->posY + diff.y;
			interfaceMod->posX = interfaceMod->posX + diff.x;
			dragStartHudEditor = mousePos;
			// anti idiot
			{
				if (interfaceMod->posX + 100 > windowSize.x)
					interfaceMod->posX = windowSize.x - 100;

				if (interfaceMod->posY + 20 > windowSize.y)
					interfaceMod->posY = windowSize.y - 20;

				interfaceMod->posX = (float)fmax(0, interfaceMod->posX);
				interfaceMod->posY = (float)fmax(0, interfaceMod->posY);
			}
		}
		else {
			posIsDragging = false;
		}
	}
	else if (posIsFocused && leftClickDown) {
		dragStartHudEditor = mousePos;
		posIsDragging = true;
	}
	shouldToggleLeftClick1 = false;
	shouldToggleRightClick1 = false;

	DrawUtils::flush();
}

void HudEditor::init() { hasInitializedHE = true; }

void HudEditor::onKeyUpdate(int key, bool isDown) {
	if (!hasInitializedHE)
		return;
	static auto clickGUI = moduleMgr->getModule<ClickGUIMod>();

	if (!isDown)
		return;

	if (!clickGUI->isEnabled()) {
		timesRenderedHE = 0;
		return;
	}

	if (timesRenderedHE < 10)
		return;
	timesRenderedHE = 0;
}

void HudEditor::onMouseClickUpdate(int key, bool isDown) {
	static auto clickGUI = moduleMgr->getModule<ClickGUIMod>();
	if (clickGUI->isEnabled() && g_Data.isInGame()) {
		switch (key) {
		case 1:  // Left Click
			isLeftClickDown1 = isDown;
			if (isDown)
				shouldToggleLeftClick1 = true;
			break;
		case 2:  // Right Click
			isRightClickDown1 = isDown;
			if (isDown)
				shouldToggleRightClick1 = true;
			break;
		}
	}
}

using json = nlohmann::json;
void HudEditor::onLoadSettings(void* confVoid) {
	auto sessionInfo = moduleMgr->getModule<SessionInfo>();
	auto interfaceMod = moduleMgr->getModule<Interface>();
	auto playerList = moduleMgr->getModule<PlayerList>();
	auto arrayList = moduleMgr->getModule<ArrayList>();
	auto targetHUD = moduleMgr->getModule<TargetHUD>();
	auto watermark = moduleMgr->getModule<Watermark>();
	auto scaffold = moduleMgr->getModule<Scaffold>();

	json* conf = reinterpret_cast<json*>(confVoid);
	if (conf->contains("HudEditorMenu")) {
		auto obj = conf->at("HudEditorMenu");
		if (obj.is_null())
			return;
		auto Position = "pos";
		const char* categories[12] = { "Speed","FPS","Position","Watermark","TargetHud","BlockCount","Release","ArrayList","Config","ArmorHud","SessionInfo","PlayerList" };
		//Speed
		if (obj.contains(categories[0])) {
			auto SpeedVal = obj.at(categories[0]);
			if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
				auto posVal = SpeedVal.at(Position);
				if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
					interfaceMod->bpsX = { posVal["x"].get<float>() };
					interfaceMod->bpsY = { posVal["y"].get<float>() };
				}
			}
		}
		//FPS
		if (obj.contains(categories[1])) {
			auto SpeedVal = obj.at(categories[1]);
			if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
				auto posVal = SpeedVal.at(Position);
				if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
					interfaceMod->fpsX = { posVal["x"].get<float>() };
					interfaceMod->fpsY = { posVal["y"].get<float>() };
				}
			}
		}
		//Position
		if (obj.contains(categories[2])) {
			auto SpeedVal = obj.at(categories[2]);
			if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
				auto posVal = SpeedVal.at(Position);
				if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
					interfaceMod->posX = { posVal["x"].get<float>() };
					interfaceMod->posY = { posVal["y"].get<float>() };
				}
			}
		}
		//Watermark
		if (obj.contains(categories[3])) {
			auto SpeedVal = obj.at(categories[3]);
			if (!SpeedVal.is_null()) {
				if (SpeedVal.contains(Position)) {
					auto posVal = SpeedVal.at(Position);
					if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
						watermark->positionX = { posVal["x"].get<float>() };
						watermark->positionY = { posVal["y"].get<float>() };
					}
				}
				if (SpeedVal.contains("client")) {
					auto posVal = SpeedVal.at("client");
					if (!posVal.is_null() && posVal.contains("name") && posVal["name"].is_string())
						interfaceMod->getClientName() = {posVal["name"].get < string >()};
				}
			}
		}
		//TargetHud
		if (obj.contains(categories[4])) {
			auto SpeedVal = obj.at(categories[4]);
			if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
				auto posVal = SpeedVal.at(Position);
				if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
					targetHUD->positionX = { posVal["x"].get<float>() };
					targetHUD->positionY = { posVal["y"].get<float>() };
				}
			}
		}
		//BlockCount
		if (obj.contains(categories[5])) {
			auto SpeedVal = obj.at(categories[5]);
			if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
				auto posVal = SpeedVal.at(Position);
				if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
					scaffold->scX = { posVal["x"].get<float>() };
					scaffold->scY = { posVal["y"].get<float>() };
				}
			}
		}
		// Release
		if (obj.contains(categories[6])) {
			auto SpeedVal = obj.at(categories[6]);
			if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
				auto posVal = SpeedVal.at(Position);
				if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
					interfaceMod->releaseX = { posVal["x"].get<float>() };
					interfaceMod->releaseY = { posVal["y"].get<float>() };
				}
			}
		}
		if (obj.contains(categories[7])) {
			auto SpeedVal = obj.at(categories[7]);
			if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
				auto posVal = SpeedVal.at(Position);
				if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
					arrayList->positionX = { posVal["x"].get<float>() };
					arrayList->positionY = { posVal["y"].get<float>() };
				}
			}
			if (obj.contains(categories[9])) {
				auto SpeedVal = obj.at(categories[9]);
				if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
					auto posVal = SpeedVal.at(Position);
					if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
						interfaceMod->armorX = { posVal["x"].get<float>() };
						interfaceMod->armorY = { posVal["y"].get<float>() };
					}
				}
			}
			if (obj.contains(categories[10])) {
				auto SpeedVal = obj.at(categories[10]);
				if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
					auto posVal = SpeedVal.at(Position);
					if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
						sessionInfo->siX = { posVal["x"].get<float>() };
						sessionInfo->siY = { posVal["y"].get<float>() };
					}
				}
			}
			if (obj.contains(categories[11])) {
				auto SpeedVal = obj.at(categories[11]);
				if (!SpeedVal.is_null() && SpeedVal.contains(Position)) {
					auto posVal = SpeedVal.at(Position);
					if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
						playerList->positionX = { posVal["x"].get<float>() };
						playerList->positionY = { posVal["y"].get<float>() };
					}
				}
			}
		}
	}
}

void HudEditor::onSaveSettings(void* confVoid) {
	json* conf = reinterpret_cast<json*>(confVoid);
	auto interfaceMod = moduleMgr->getModule<Interface>();
	auto arrayList = moduleMgr->getModule<ArrayList>();
	auto targetHUD = moduleMgr->getModule<TargetHUD>();
	auto watermark = moduleMgr->getModule<Watermark>();
	auto scaffold = moduleMgr->getModule<Scaffold>();
	auto sessionInfo = moduleMgr->getModule<SessionInfo>();
	auto playerList = moduleMgr->getModule<PlayerList>();
	// Save to json
	if (conf->contains("HudEditorMenu"))
		conf->erase("HudEditorMenu");

	json obj = {};
	// armorHud
	json playerListObj = {};
	playerListObj["pos"]["x"] = playerList->positionX;
	playerListObj["pos"]["y"] = playerList->positionY;
	obj["PlayerList"] = playerListObj;
	// armorHud
	json armorHUDObj = {};
	armorHUDObj["pos"]["x"] = interfaceMod->armorX;
	armorHUDObj["pos"]["y"] = interfaceMod->armorY;
	obj["ArmorHud"] = armorHUDObj;
	// sessioninfo
	json sessionInfoObj = {};
	sessionInfoObj["pos"]["x"] = sessionInfo->siX;
	sessionInfoObj["pos"]["y"] = sessionInfo->siY;
	obj["SessionInfo"] = sessionInfoObj;
	// Release
	json buildObj = {};
	buildObj["pos"]["x"] = interfaceMod->releaseX;
	buildObj["pos"]["y"] = interfaceMod->releaseY;
	obj["Release"] = buildObj;
	// AidsList
	json arrayListObj = {};
	arrayListObj["pos"]["x"] = arrayList->positionX;
	arrayListObj["pos"]["y"] = arrayList->positionY;
	obj["ArrayList"] = arrayListObj;
	//Speed
	json speedObj = {};
	speedObj["pos"]["x"] = interfaceMod->bpsX;
	speedObj["pos"]["y"] = interfaceMod->bpsY;
	obj["Speed"] = speedObj;
	//FPS
	json fpsObj = {};
	fpsObj["pos"]["x"] = interfaceMod->fpsX;
	fpsObj["pos"]["y"] = interfaceMod->fpsY;
	obj["FPS"] = fpsObj;
	//Position
	json PositionObj = {};
	PositionObj["pos"]["x"] = interfaceMod->posX;
	PositionObj["pos"]["y"] = interfaceMod->posY;
	obj["Position"] = PositionObj;
	//Watermark
	json WatermarkObj = {};
	WatermarkObj["pos"]["x"] = watermark->positionX;
	WatermarkObj["pos"]["y"] = watermark->positionY;
	WatermarkObj["client"]["name"] = interfaceMod->getClientName();
	obj["Watermark"] = WatermarkObj;
	//TargetHud
	json TargetHudObj = {};
	TargetHudObj["pos"]["x"] = targetHUD->positionX;
	TargetHudObj["pos"]["y"] = targetHUD->positionY;
	obj["TargetHud"] = TargetHudObj;
	//BlockCount
	json BlockCountObj = {};
	BlockCountObj["pos"]["x"] = scaffold->scX;
	BlockCountObj["pos"]["y"] = scaffold->scY;
	obj["BlockCount"] = BlockCountObj;

	conf->emplace("HudEditorMenu", obj);
}