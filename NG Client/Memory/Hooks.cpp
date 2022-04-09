#include "Hooks.h"

#include "windows.h"
#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_relational.hpp>
#include <glm/ext/matrix_transform.hpp>  // perspective, translate, rotate
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>         // mat4
#include <glm/trigonometric.hpp>  //radians

#include "../SDK/Tag.h"

Hooks g_Hooks;
bool isTicked = false;
bool overrideStyledReturn = false;
bool justEnabled = true;
bool isOpen = true;
int enabledTicks = 0;
TextHolder styledReturnText;
//#define TEST_DEBUG

void blockRotate(glm::mat4& matrix, float upper) {
	matrix = glm::translate<float>(matrix, glm::vec3(-0.5F, upper, 0.0F));
	matrix = glm::rotate<float>(matrix, 30.0F, glm::vec3(0.0F, 1.0F, 0.0F));
	matrix = glm::rotate<float>(matrix, -80.0F, glm::vec3(1.0F, 0.0F, 0.0F));
	matrix = glm::rotate<float>(matrix, 60.0F, glm::vec3(0.0F, 1.0F, 0.0F));
}

void Hooks::Init() {
	logF("Setting up Hooks...");
	// clang-format off
	// Vtables
	{
		// GameMode::vtable
		{
			uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 8B FA 48 8B 89 ? ? ? ? 48 85 C9 74 ? 48 8B 01 BA ? ? ? ? FF 10 48 8B 8B");
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
			uintptr_t** gameModeVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
			if (gameModeVtable == 0x0 || sigOffset == 0x0)
				logF("C_GameMode signature not working!!!");
			else {
				g_Hooks.GameMode_startDestroyBlockHook = std::make_unique<FuncHook>(gameModeVtable[1], Hooks::GameMode_startDestroyBlock);

				g_Hooks.GameMode_getPickRangeHook = std::make_unique<FuncHook>(gameModeVtable[10], Hooks::GameMode_getPickRange);

				g_Hooks.GameMode_attackHook = std::make_unique<FuncHook>(gameModeVtable[14], Hooks::GameMode_attack);
			}
		}
		
		// BlockLegacy::vtable
		{
			intptr_t sigOffset = FindSignature("48 8D 05 ?? ?? ?? ?? 48 89 06 EB 03 49 8B F4 4D 89 26");  // BlockLegacy constructor
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
            uintptr_t** blockLegacyVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
			if (blockLegacyVtable == 0x0 || sigOffset == 0x0)
				logF("C_BlockLegacy signature not working!!!");
			else {
				//g_Hooks.BlockLegacy_getRenderLayerHook = std::make_unique<FuncHook>(blockLegacyVtable[182], Hooks::BlockLegacy_getRenderLayer);
				//g_Hooks.BlockLegacy_getLightEmissionHook = std::make_unique<FuncHook>(blockLegacyVtable[185], Hooks::BlockLegacy_getLightEmission);
			}
		}

		// LocalPlayer::vtable
		{
			uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 8B 89 ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 48 8B 10");
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
			uintptr_t** localPlayerVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
			if (localPlayerVtable == 0x0 || sigOffset == 0x0)
				logF("C_LocalPlayer signature not working!!!");
			else {
				
				g_Hooks.Actor_startSwimmingHook = std::make_unique<FuncHook>(localPlayerVtable[201], Hooks::Actor_startSwimming);

				g_Hooks.Actor_ascendLadderHook = std::make_unique<FuncHook>(localPlayerVtable[339], Hooks::Actor_ascendLadder);
				
				g_Hooks.Actor_rotationHook = std::make_unique<FuncHook>(localPlayerVtable[27], Hooks::Actor_rotation);

				g_Hooks.Actor_swingHook = std::make_unique<FuncHook>(localPlayerVtable[219], Hooks::Actor_swing);

				g_Hooks.JumpPowerHook = std::make_unique<FuncHook>(localPlayerVtable[345], Hooks::JumpPower); //jump from ground with movement proxy

				g_Hooks.setPosHook = std::make_unique<FuncHook>(localPlayerVtable[19], Hooks::setPos);

				g_Hooks.Actor_baseTickHook = std::make_unique<FuncHook>(localPlayerVtable[49], Hooks::Actor_baseTick);

				g_Hooks.Mob__isImmobileHook = std::make_unique<FuncHook>(localPlayerVtable[91], Hooks::Mob__isImmobile);

				g_Hooks.Actor_isInWaterHook = std::make_unique<FuncHook>(localPlayerVtable[71], Hooks::Actor_isInWater);

				g_Hooks.Player_tickWorldHook = std::make_unique<FuncHook>(localPlayerVtable[364], Hooks::Player_tickWorld);
				#ifdef _DEBUG
				//g_Hooks.testyHook = std::make_unique<FuncHook>(localPlayerVtable[1], Hooks::testy);
				#endif
			}
		}

		// MoveInputHandler::vtable
		{
			uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? 49 89 48 ? 49 89 80 ? ? ? ? 49 89 80 ? ? ? ? 48 39 87 ? ? ? ? 74 20 48 8B 8F");
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
			uintptr_t** moveInputVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
			if (moveInputVtable == 0x0 || sigOffset == 0x0)
				logF("C_MoveInputHandler signature not working!!!");
			else {
				g_Hooks.MoveInputHandler_tickHook = std::make_unique<FuncHook>(moveInputVtable[1], Hooks::MoveInputHandler_tick);
			}
		}

		// PackAccessStrategy vtables for isTrusted
		{
			uintptr_t sigOffset = FindSignature("48 8D 05 ?? ?? ?? ?? 49 89 06 49 8D 76 50");
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
			uintptr_t** directoryPackVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset +  7);

			{
				g_Hooks.DirectoryPackAccessStrategy__isTrustedHook = std::make_unique<FuncHook>(directoryPackVtable[6], Hooks::DirectoryPackAccessStrategy__isTrusted);
			}

			uintptr_t sigOffset2 = FindSignature("48 8D 05 ?? ?? ?? ?? 48 89 01 4C 8D B1 ?? ?? ?? ?? 49 8B 46 08"); // Was 48 8D 05 ?? ?? ?? ?? 48 89 03 49 8D 57 in 1.18.2
			int offset2 = *reinterpret_cast<int*>(sigOffset2 + 3);
			uintptr_t** directoryPackVtable2 = reinterpret_cast<uintptr_t**>(sigOffset2 + offset2 +  7);

			{
				g_Hooks.ZipPackAccessStrategy__isTrustedHook = std::make_unique<FuncHook>(directoryPackVtable2[6], Hooks::ReturnTrue);
			}
			g_Hooks.SkinRepository___checkSignatureFileInPack = std::make_unique<FuncHook>(FindSignature("48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B 79"), Hooks::ReturnTrue);
		}
	}
	
	// Signatures
	{
		//void* Actor_breath = reinterpret_cast<void*>(FindSignature("48 89 5C 24 18 56 48 83 EC 50 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 40 8B 81"));
		//g_Hooks.Actor_breatheHook = std::make_unique<FuncHook>(Actor_breath, Hooks::Actor_breathe);
				
		//void* _toStyledString = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B D8 48 8B F9"));
		//g_Hooks.toStyledStringHook = std::make_unique<FuncHook>(_toStyledString, Hooks::toStyledString);

		//void* InGamePlayScreen___renderLevel = reinterpret_cast<void*>(FindSignature("48 89 5C 24 20 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 B4 24 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 49 8B D8 4C"));
		//g_Hooks.InGamePlayScreen___renderLevelHook = std::make_unique<FuncHook>(InGamePlayScreen___renderLevel, Hooks::InGamePlayScreen___renderLevel);

		//void* testy = reinterpret_cast<void*>(FindSignature("48 8B 05 61 DF CD 02 48 85 C0 75 07"));
		//g_Hooks.testyHook = std::make_unique<FuncHook>(testy, Hooks::testy);
		
		//void* ascendLadder = reinterpret_cast<void*>(FindSignature("C7 81 ? ? ? ? ? ? ? ? C3 CC CC CC CC CC C7 81 ? ? ? ? ? ? ? ? C3 CC CC CC CC CC C7 81"));
		//g_Hooks.Actor_ascendLadderHook = std::make_unique<FuncHook>(ascendLadder, Hooks::Actor_ascendLadder);

		void* _sendChatMessage = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4C 8B EA 4C 8B F9 48 8B 49"));
		g_Hooks.ClientInstanceScreenModel_sendChatMessageHook = std::make_unique<FuncHook>(_sendChatMessage, Hooks::ClientInstanceScreenModel_sendChatMessage);

		void* _renderCtx = reinterpret_cast<void*>(FindSignature("48 8B ? 48 89 ? ? 55 56 57 41 ? 41 ? 41 ? 41 ? 48 8D ? ? ? ? ? 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? ? ? 4C 8B ? 48 89 ? ? ? 4C 8B"));
		g_Hooks.RenderTextHook = std::make_unique<FuncHook>(_renderCtx, Hooks::RenderText);
		g_Hooks.RenderTextHook->enableHook();

		void* setupRender = reinterpret_cast<void*>(FindSignature("48 89 5C 24 10 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 48 8B DA 48 8B F9 33 D2 41 B8"));
		g_Hooks.UIScene_setupAndRenderHook = std::make_unique<FuncHook>(setupRender, Hooks::UIScene_setupAndRender);

		void* render = reinterpret_cast<void*>(FindSignature("48 89 5C 24 18 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 48 8B DA 48 8B F9 B9 10 ? ? ?"));
		g_Hooks.UIScene_renderHook = std::make_unique<FuncHook>(render, Hooks::UIScene_render);

		void* fogColorFunc = reinterpret_cast<void*>(FindSignature("41 0F 10 08 48 8B C2 0F"));
		g_Hooks.Dimension_getFogColorHook = std::make_unique<FuncHook>(fogColorFunc, Hooks::Dimension_getFogColor);

		void* timeOfDay = reinterpret_cast<void*>(FindSignature("44 8B C2 B8 ? ? ? ? F7 EA"));
		g_Hooks.Dimension_getTimeOfDayHook = std::make_unique<FuncHook>(timeOfDay, Hooks::Dimension_getTimeOfDay);

		void* sunItensity = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 57 48 83 EC 30 48 8B B9 ? ? ? ? 49 8B D8"));
		g_Hooks.Dimension_getSunIntensityHook = std::make_unique<FuncHook>(sunItensity, Hooks::Dimension_getSunIntensity);

		void* chestTick = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 56 57 41 56 48 83 EC ? 48 83 79"));
		g_Hooks.ChestBlockActor_tickHook = std::make_unique<FuncHook>(chestTick, Hooks::ChestBlockActor_tick);

		void* lerpFunc = reinterpret_cast<void*>(FindSignature("8B 02 89 81 ? ? ? ? 8B 42 ? 89 81 ? ? ? ? 8B 42 ? 89 81 ? ? ? ? C3 CC CC CC CC CC 48 89 5C 24"));
		g_Hooks.Actor_lerpMotionHook = std::make_unique<FuncHook>(lerpFunc, Hooks::Actor_lerpMotion);

		void* getRenderLayer = reinterpret_cast<void*>(FindSignature("8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC F3 0F 10 81"));
		g_Hooks.BlockLegacy_getRenderLayerHook = std::make_unique<FuncHook>(getRenderLayer, Hooks::BlockLegacy_getRenderLayer);

		void* getLightEmission = reinterpret_cast<void*>(FindSignature("0F B6 81 ? ? ? ? 88 02 48 8B C2"));
		g_Hooks.BlockLegacy_getLightEmissionHook = std::make_unique<FuncHook>(getLightEmission, Hooks::BlockLegacy_getLightEmission);

		void* getGameEdition = reinterpret_cast<void*>(FindSignature("8B 91 ?? ?? ?? ?? 85 D2 74 1C 83 EA 01"));
		g_Hooks.AppPlatform_getGameEditionHook = std::make_unique<FuncHook>(getGameEdition, Hooks::AppPlatform_getGameEdition);

		uintptr_t** packetSenderVtable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)g_Data.getClientInstance()->loopbackPacketSender);
		g_Hooks.LoopbackPacketSender_sendToServerHook = std::make_unique<FuncHook>(packetSenderVtable[2], Hooks::LoopbackPacketSender_sendToServer);

		void* getFov = reinterpret_cast<void*>(FindSignature("40 53 48 83 EC ?? 0F 29 7C 24 ?? 44"));
		g_Hooks.LevelRendererPlayer_getFovHook = std::make_unique<FuncHook>(getFov, Hooks::LevelRendererPlayer_getFov);

		void* getRMBHook = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ?? 56 57 41 56 48 83 EC ?? 48 8B ?? ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 48 8B F2 4C 8B F1 0F 57 C0"));
		g_Hooks.RMBManagerThingyHook = std::make_unique<FuncHook>(getRMBHook, Hooks::RMBManagerThingy);

		void* tick_entityList = reinterpret_cast<void*>(FindSignature("48 89 ?? ?? ?? 57 48 83 EC ?? 48 8B ?? E8 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 48 8B D8 ?? ?? ?? ?? ?? ?? 48 99"));
		g_Hooks.MultiLevelPlayer_tickHook = std::make_unique<FuncHook>(tick_entityList, Hooks::MultiLevelPlayer_tick);

		void* keyMouseFunc = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 0F 29 74 24 ? 0F 29 7C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F0"));
		g_Hooks.HIDController_keyMouseHook = std::make_unique<FuncHook>(keyMouseFunc, Hooks::HIDController_keyMouse);

		void* renderLevel = reinterpret_cast<void*>(FindSignature("48 89 5C 24 10 48 89 74 24 20 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 49 8B F8 48 8B DA"));
		g_Hooks.LevelRenderer_renderLevelHook = std::make_unique<FuncHook>(renderLevel, Hooks::LevelRenderer_renderLevel);

		void* playerCallBackHook = reinterpret_cast<void*>(FindSignature("F3 0F ?? ?? ?? ?? 00 00 ?? 0F ?? 00 F3 0F ?? ?? F3 0F ?? ?? 04"));
		g_Hooks.playerCallBack_Hook = std::make_unique<FuncHook>(playerCallBackHook, Hooks::playerCallBack);

		void* clickHook = reinterpret_cast<void*>(FindSignature("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24 ? ? ? ? 48 8B D9"));
		g_Hooks.ClickFuncHook = std::make_unique<FuncHook>(clickHook, Hooks::ClickFunc);

		void* chestScreenControllerTick = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 E8 ? ? ? ? 48 8B 17"));
		g_Hooks.ChestScreenController_tickHook = std::make_unique<FuncHook>(chestScreenControllerTick, Hooks::ChestScreenController_tick);

		void* autoComplete = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 41 8B D9"));
		g_Hooks.PleaseAutoCompleteHook = std::make_unique<FuncHook>(autoComplete, Hooks::PleaseAutoComplete);

		void* fullbright = reinterpret_cast<void*>(FindSignature("48 83 EC ? 80 B9 ? ? ? ? ? 48 8D 54 24 ? 48 8B 01 74 ? 41 B8 ? ? ? ? FF 50 ? 48 8B 10 48 85 D2 74 ? 48 8B 42 ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? E8 ? ? ? ? 48 83 C4 ? C3 F3 0F 10 42 ? 48 83 C4 ? C3 41 B8 ? ? ? ? FF 50 ? 48 8B 10 48 85 D2 75 ? E8 ? ? ? ? CC E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC F3 0F 11 4C 24"));
		g_Hooks.GetGammaHook = std::make_unique<FuncHook>(fullbright, Hooks::GetGamma);

		void* RakNetInstance__tick = reinterpret_cast<void*>(FindSignature("48 89 5C 24 10 48 89 74 24 18 55 57 41 54 41 56 41 57 48 8D AC 24 20 FD FF FF 48 81 EC E0 03 00 00"));
		g_Hooks.RakNetInstance_tickHook = std::make_unique<FuncHook>(RakNetInstance__tick, Hooks::RakNetInstance_tick);

		void* ConnectionRequest__create = reinterpret_cast<void*>(FindSignature("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B ?? ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 49 8B D9 48 89 55 E8"));
		g_Hooks.ConnectionRequest_createHook = std::make_unique<FuncHook>(ConnectionRequest__create, Hooks::ConnectionRequest_create);

		void* _getSkinPack = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B EA 48 8B F1"));
		g_Hooks.SkinRepository___loadSkinPackHook = std::make_unique<FuncHook>(_getSkinPack, Hooks::SkinRepository___loadSkinPack);

		void* destroySpeed = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B FA 0F 29 74 24 ? 48 8B 91"));
		g_Hooks.getDestroySpeedHook = std::make_unique<FuncHook>(destroySpeed, Hooks::getDestroySpeed);

		void* actorDie = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 57 48 83 EC ? C6 81 ? ? ? ? ? 48 8B F9"));
		g_Hooks.actorDieHook = std::make_unique<FuncHook>(actorDie, Hooks::onActorDie);

		void* inventoryScreen = reinterpret_cast<void*>(FindSignature("48 89 5c 24 ? 48 89 74 24 ? 48 89 7c 24 ? 55 41 54 41 55 41 56 41 57 48 8d 6c 24 ? 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 45 ? 48 8b f9 33 f6 89 74 24"));
		g_Hooks.inventoryScreen__tickHook = std::make_unique<FuncHook>(inventoryScreen, Hooks::inventoryScreen__tick);

#ifdef TEST_DEBUG
		void* addAction = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC 30 45 0F B6 F8 4C 8B F2 48 8B F1 48 8B 01 48 8B 88 ? ? ? ? 48 85 C9"));
		g_Hooks.InventoryTransactionManager__addActionHook = std::make_unique<FuncHook>(addAction, Hooks::InventoryTransactionManager__addAction);
#endif

		void* localPlayerUpdateFromCam = reinterpret_cast<void*>(FindSignature("48 89 5C 24 10 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 80"));//Broken
		g_Hooks.LocalPlayer__updateFromCameraHook = std::make_unique<FuncHook>(localPlayerUpdateFromCam, Hooks::LocalPlayer__updateFromCamera);

		//void* renderNameTags = reinterpret_cast<void*>(FindSignature("4C 8B DC 49 89 5B ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 41 0F 29 73 ? 41 0F 29 7B ? 45 0F 29 43 ? 48 8B 05"));//Broken
		//g_Hooks.LevelRendererPlayer__renderNameTagsHook = std::make_unique<FuncHook>(renderNameTags, Hooks::LevelRendererPlayer__renderNameTags);

		static constexpr auto counterStart = __COUNTER__ + 1;
		#define lambda_counter (__COUNTER__ - counterStart)

		void* levelRendererBobView = reinterpret_cast<void*>(FindSignature("48 8B C4 48 89 58 20 57 48 ?? ?? ?? ?? 00 00 0F ?? ?? ?? 0F ?? ?? ?? ?? 0F ?? ?? ?? ?? 0F ?? ?? ??"));

		static auto bobViewHookF = [](__int64 _this, glm::mat4& matrix, float lerpT){
			static auto origFunc = g_Hooks.lambdaHooks.at(lambda_counter)->GetFastcall<void, __int64, glm::mat4&, float>();
			
			static auto ViewMod = moduleMgr->getModule<ViewModel>();
			static auto KillMod = moduleMgr->getModule<Killaura>();			
			auto player = g_Data.getLocalPlayer();
			float degrees = fmodf(player->getPosOld()->lerp(player->getPos(), lerpT).x, 5) - 2.5f;
			degrees *= 180 / 2.5f;

			auto pos = g_Data.getClientInstance()->levelRenderer->getOrigin();
			
			glm::mat4 View = matrix;
			
			matrix = View;
			auto slot = g_Data.getLocalPlayer()->getSupplies()->inventory->getItemStack(g_Data.getLocalPlayer()->getSupplies()->selectedHotbarSlot);
		if (KillMod->isEnabled() && !KillMod->targetListA && slot != nullptr && slot->item != nullptr && slot->getItem()->isWeapon() && moduleMgr->getModule<SwingAnimations>()->isEnabled()) {
			 lerpT = 0.f;
				// translate for bedrock
				matrix = glm::translate<float>(matrix, glm::vec3(0.42222223281, 0.0, -0.16666666269302368));
				// java translated
				matrix = glm::translate<float>(matrix, glm::vec3(-0.15f, 0.15f, -0.2f));
				blockRotate(matrix, 0.2f);
				return;
		 } else if (ViewMod->isEnabled()) {
				auto p = g_Data.getLocalPlayer();
				if (ViewMod->mode.selected == 0 && ViewMod->spin){
				float degrees = fmaf(p->getPosOld()->lerp(p->getPos(), lerpT).z, 95 ,0);
				matrix = glm::rotate<float>(matrix, glm::radians<float>(degrees), glm::vec3(0, 255, 0));
				}
				if (ViewMod->mode.selected == 1 && ViewMod->spin){
				float degrees = fmaf(p->getPosOld()->lerp(p->getPos(), lerpT).z, 95 ,0);
				matrix = glm::rotate<float>(matrix, glm::radians<float>(degrees), glm::vec3(0, 0, 255));
				}
				if (ViewMod->mode.selected == 2 && ViewMod->spin){
				float degrees = fmaf(p->getPosOld()->lerp(p->getPos(), lerpT).z, 95 ,0);
				matrix = glm::rotate<float>(matrix, glm::radians<float>(degrees), glm::vec3(255, 0, 0));
				}
				if (ViewMod->doRotation)
					matrix = glm::rotate<float>(matrix, ViewMod->RotatePosition, glm::vec3(ViewMod->xRotate, ViewMod->yRotate, ViewMod->zRotate));
				if (ViewMod->doTranslate)
					matrix = glm::translate<float>(matrix, glm::vec3(ViewMod->xTrans, ViewMod->yTrans, ViewMod->zTrans));
				if (ViewMod->doScale)
					matrix = glm::scale<float>(matrix, glm::vec3(ViewMod->xMod, ViewMod->yMod, ViewMod->zMod));
			}
			return origFunc(_this, matrix, lerpT);
		};
		
		std::shared_ptr<FuncHook> bobViewHook = std::make_shared<FuncHook>(levelRendererBobView, (decltype(&bobViewHookF.operator()))bobViewHookF);

		g_Hooks.lambdaHooks.push_back(bobViewHook);

		#undef lambda_counter
		
		

		logF("Hooks initialized");
	}

// clang-format on
}

void Hooks::Restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(10);
}

void Hooks::Enable() {
	logF("Hooks enabled");
	MH_EnableHook(MH_ALL_HOOKS);
}

void* Hooks::Player_tickWorld(C_Player* _this, __int64 unk) {
	static auto oTick = g_Hooks.Player_tickWorldHook->GetFastcall<void*, C_Player*, __int64>();
	auto o = oTick(_this, unk);

	if (_this == g_Data.getLocalPlayer()) {
		// TODO: refactor all modules to not use GameMode
		C_GameMode* gm = *reinterpret_cast<C_GameMode**>(reinterpret_cast<__int64>(_this) + 0x1238);
		GameData::updateGameData(gm);
		moduleMgr->onWorldTick(gm);
	}
	return o;
}

bool Hooks::playerCallBack(C_Player* lp, __int64 cock, __int64 penis) {
	static auto oTick = g_Hooks.playerCallBack_Hook->GetFastcall<bool, C_Player*, __int64, __int64>();
	// om, we need this check or else is makes all entitys look the directions we are setting rotations to look lol
	if (lp == g_Data.getLocalPlayer())
		moduleMgr->onPlayerTick(lp);

	// Fix I Hope
	{
		if (g_Data.getLocalPlayer() != nullptr && lp == g_Data.getLocalPlayer()) {
			if (!g_Data.getLocalPlayer() || !g_Data.getLocalPlayer()->pointingStruct || !*(&g_Data.getLocalPlayer()->region + 1))
				g_Hooks.entityList.clear();

			std::vector<EntityListPointerHolder> validEntities;
			for (const auto& ent : g_Hooks.entityList) {
				auto entity = ent.ent;
				MEMORY_BASIC_INFORMATION info;
				VirtualQuery(ent.ent, &info, sizeof(MEMORY_BASIC_INFORMATION));
				if (info.State & MEM_FREE) continue;
				if (info.State & MEM_RESERVE) continue;
				if (entity != nullptr && (__int64)entity != 0xFFFFFFFFFFFFFCD7 && (__int64)entity != 0xFFFFFF00FFFFFF00 && ent.ent != nullptr && *(__int64*)ent.ent != 0xFFFFFFFFFFFFFCD7 && *(__int64*)ent.ent > 0x6FF000000000 && *(__int64*)ent.ent < 0x800000000000 && *((int64_t*)ent.ent + 1) < 0x6FF000000000 && *(__int64*)ent.ent <= Utils::getBase() + 0x10000000 && entity->isAlive())
					validEntities.push_back(ent);
			}
			g_Hooks.entityList.clear();
			g_Hooks.entityList = validEntities;
		}
	}

	return oTick(lp, cock, penis);
}

void Hooks::ClientInstanceScreenModel_sendChatMessage(void* _this, TextHolder* text) {
	static auto oSendMessage = g_Hooks.ClientInstanceScreenModel_sendChatMessageHook->GetFastcall<void, void*, TextHolder*>();

	if (text->getTextLength() > 0) {
		char* message = text->getText();

		if (*message == cmdMgr->prefix) {
			cmdMgr->execute(message);

			return;
		} else if (*message == '.') {
			// maybe the user forgot his prefix, give him some helpful advice
			static bool helpedUser = false;
			if (!helpedUser) {
				helpedUser = true;
				g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%sYour Horion prefix is: \"%s%c%s\"", RED, YELLOW, cmdMgr->prefix, RED);
				g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%sEnter \"%s%cprefix .%s\" to reset your prefix", RED, YELLOW, cmdMgr->prefix, RED);
			}
		}
	}
	oSendMessage(_this, text);
}

void Hooks::Actor_baseTick(C_Entity* ent) {
	static auto oFunc = g_Hooks.Actor_baseTickHook->GetFastcall<void, C_Entity*>();
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (!player || !player->getPointingStruct()) return oFunc(ent);

	static int tickCountThen = 0;
	int tickCountNow = *(int*)((__int64)player->getPointingStruct() + 0x690);

	if (tickCountNow != tickCountThen) {
		g_Hooks.entityList.clear();
		tickCountThen = tickCountNow;
	}
	if (ent->isClientSide()) {
		EntityListPointerHolder e;
		e.addedTick = tickCountNow;
		e.ent = ent;

		bool found = false;
		for (const auto& entity : g_Hooks.entityList)
			if (entity.ent == ent && entity.addedTick == tickCountNow) {
				found = true;
				break;
			}

		if (!found)
			g_Hooks.entityList.push_back(e);
	}
	return oFunc(ent);
}

__int64 Hooks::UIScene_setupAndRender(C_UIScene* uiscene, __int64 screencontext) {
	static auto oSetup = g_Hooks.UIScene_setupAndRenderHook->GetFastcall<__int64, C_UIScene*, __int64>();
	g_Hooks.shouldRender = false;

	return oSetup(uiscene, screencontext);
}

void Hooks::RMBManagerThingy(__int64 a1, __int64 a2) {
	static auto oClick = g_Hooks.RMBManagerThingyHook->GetFastcall<void, __int64, __int64>();
	g_Hooks.RMBManager = a1;
	oClick(a1, a2);
}

__int64 Hooks::UIScene_render(C_UIScene* uiscene, __int64 screencontext) {
	static auto oRender = g_Hooks.UIScene_renderHook->GetFastcall<__int64, C_UIScene*, __int64>();

	g_Hooks.shouldRender = false;

	TextHolder alloc{};
	uiscene->getScreenName(&alloc);

	if (alloc.getTextLength() < 100) {
		strcpy_s(g_Hooks.currentScreenName, alloc.getText());
	}

	if (!g_Hooks.shouldRender) {
		g_Hooks.shouldRender = (strcmp(alloc.getText(), "start_screen") == 0 || strcmp(alloc.getText(), "hud_screen") == 0);
	}
	alloc.alignedTextLength = 0;

	return oRender(uiscene, screencontext);
}

__int64 Hooks::RenderText(__int64 a1, C_MinecraftUIRenderContext* renderCtx) {
	static auto oText = g_Hooks.RenderTextHook->GetFastcall<__int64, __int64, C_MinecraftUIRenderContext*>();

	C_GuiData* dat = g_Data.getClientInstance()->getGuiData();

	if (reinterpret_cast<__int64>(dat) < 0x500000000 || reinterpret_cast<__int64>(dat) > 0xFFFFFFFFFFF00000) return oText(a1, renderCtx);

	DrawUtils::setCtx(renderCtx, dat);

	{
		static bool wasConnectedBefore = false;
		static LARGE_INTEGER start;
		static LARGE_INTEGER frequency;
		if (frequency.QuadPart == 0) {
			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&start);
		}
		static bool hasSentWarning = false;
		if (!g_Data.isInjectorConnectionActive() && !hasSentWarning) {
			__int64 retval = oText(a1, renderCtx);

			LARGE_INTEGER end, elapsed;
			QueryPerformanceCounter(&end);
			elapsed.QuadPart = end.QuadPart - start.QuadPart;
			float elapsedFlot = (float)elapsed.QuadPart / frequency.QuadPart;
			if (elapsedFlot > 0.5f && !hasSentWarning) {
				hasSentWarning = true;
				auto box = g_Data.addInfoBox("Thanks For Choosing The NG Client!", "We Are 22");
				box->closeTimer = 5;
				vec2 windowSize = dat->windowSize;

				DrawUtils::flush();
			}

			if (!hasSentWarning)  // Wait for injector, it might connect in time
				return retval;
		} else
			wasConnectedBefore = true;
	}

	if (GameData::shouldHide() || !moduleMgr->isInitialized())
		return oText(a1, renderCtx);

	static auto hudModule = moduleMgr->getModule<HudModule>();
	static auto gui = moduleMgr->getModule<GUI>();
	static auto clickGuiModule = moduleMgr->getModule<ClickGuiMod>();

	HImGui.startFrame();

	g_Data.frameCount++;

	auto wid = g_Data.getClientInstance()->getGuiData()->windowSize;

	// Call PreRender() functions
	moduleMgr->onPreRender(renderCtx);
	DrawUtils::flush();

	__int64 retval = oText(a1, renderCtx);

	bool shouldPostRender = true;
	bool shouldRenderArrayList = true;

	static float rcolors[4];          // Rainbow color array RGBA
	static float disabledRcolors[4];  // Rainbow Colors, but for disabled modules
	static float currColor[4];        // ArrayList colors
	static float SurgeColor[4];       // ArrayList colors

	// Rainbow color updates
	{
		Utils::ApplyRainbow(rcolors);  // Increase Hue of rainbow color array
		disabledRcolors[0] = std::min(1.f, rcolors[0] * 0.4f + 0.2f);
		disabledRcolors[1] = std::min(1.f, rcolors[1] * 0.4f + 0.2f);
		disabledRcolors[2] = std::min(1.f, rcolors[2] * 0.4f + 0.2f);
		disabledRcolors[3] = 1;
	}

	{
		// Main Menu
		static auto partner = moduleMgr->getModule<Partner>();
		std::string screenName(g_Hooks.currentScreenName);
		vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;

		if (strcmp(screenName.c_str(), "start_screen") == 0) {
			vec2 text = vec2(windowSize.x / windowSize.x, 5);
			vec2 outline = vec2(windowSize.x / windowSize.x, 5.5);

			MC_Color wight = MC_Color(255, 255, 255);
			std::string string;
			if (partner->Partnered.selected == 1)
			string = "Fadeaway Client";
			else if (partner->Partnered.selected == 0)
			string = "Surge Client";
			else
			string = "NG Client";
			DrawUtils::drawText(text, &string, wight, 2.f, 1.f);

			text.y += 18.f;
			string = "Version: 1.18.12.2";
			DrawUtils::drawText(text, &string, wight, 1.f, 1.f);
			text.y += 15.f;
			string =
				//Changelogs
				"Changelogs: \n"
				"[+] Jesus \n"
				"[-] ExtendedBlockReach \n"
				"[-] InsideTP \n"
				"[-] Trail \n"
				"[-] Phase \n"
				"[-] Snow \n"
				"[-] SoundPlayer \n"
				"[*] Code Clean Up \n"
				"[*] getKeybind - getKey \n"
				"[*] Many Fixes \n\n"
				//partner
				"partner: \n"
				"Fadeaway \n"
				"Surge \n"
				"ghost \n\n"
				//Credits
				"Credits: \n"
				"NRG \n"
				"Intop \n"
				"DeadtrosGaming \n"
				"2474 \n"
				"Sentinel \n"
				"Founder \n";
			DrawUtils::drawText(text, &string, wight, 1.f, 1.f);
		}

		// Draw Buttons
		if (!strcmp(screenName.c_str(), "start_screen") == 0) {
			if (hudModule->Buttons) {
				if (!g_Data.canUseMoveKeys() && !clickGuiModule->isEnabled()) {
					if (HImGui.Button("Disable Spammer", vec2(wid.x / 13.f, wid.y / 15.f), true)) {
						static auto spammer = moduleMgr->getModule<Spammer>();
						if (spammer->isEnabled()) spammer->setEnabled(false);
					}
					if (HImGui.Button("Disable Crasher", vec2(wid.x / 13.f, wid.y / 9.f), true)) {
						static auto crasher = moduleMgr->getModule<Crasher>();
						if (crasher->isEnabled()) crasher->setEnabled(false);
					}
					if (HImGui.Button("Disable Nuker", vec2(wid.x / 13.f, wid.y / 6.37f), true)) {
						static auto nuker = moduleMgr->getModule<Nuker>();
						if (nuker->isEnabled()) nuker->setEnabled(false);
					}
					if (HImGui.Button("Disable Aura", vec2(wid.x / 13.f, wid.y / 5.0f), true)) {
						static auto aura = moduleMgr->getModule<Killaura>();
						if (aura->isEnabled()) aura->setEnabled(false);
					}
				}
			}
		}
		if (strcmp(screenName.c_str(), "start_screen") == 0) {
			// Draw BIG epic Surge watermark
			if (partner->Partnered.selected == 0) {
				std::string text = "Surge Client";
				auto gay = wid.x / 2;
				vec2 textPos = vec2(gay - DrawUtils::getTextWidth(&text, text.size() / 3.3f), wid.y / 70.f);
				vec4 rectPos = vec4(textPos.x - 20.f, textPos.y - 20.f, textPos.x + DrawUtils::getTextWidth(&text, 3.f) + 20.f, textPos.y + 40.f);
				if (hudModule->rgb) {
					DrawUtils::fillRectangle(rectPos, MC_Color(currColor), 0.f);
				} else {
					DrawUtils::fillRectangle(rectPos, MC_Color(255, 255, 255), 0.f);
				}
				if (hudModule->rgb) {
					DrawUtils::drawText(textPos, &text, MC_Color(currColor), 8.f);
				} else {
					DrawUtils::drawText(textPos, &text, MC_Color(0, 0, 255), 8.f);
				}
			}
		} else {
			shouldRenderArrayList = gui && gui->isEnabled();

			if (clickGuiModule->isEnabled()) {
				ClickGui::render();
				shouldPostRender = false;
				shouldRenderArrayList = false;
			}
			{
				// Display ArrayList on the Right?
				static constexpr bool isOnRightSide = true;

				float yOffset = 0;  // Offset of next Text
				vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
				vec2 windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
				vec2 mousePos = *g_Data.getClientInstance()->getMousePos();

				// Convert mousePos to visual Pos
				{
					mousePos = mousePos.div(windowSizeReal);
					mousePos = mousePos.mul(windowSize);
				}

				// Draw ArrayList
				if (moduleMgr->isInitialized() && shouldRenderArrayList) {
					vec2 textPos;
					vec4 FluxBar;
					vec4 rectPos;
					vec4 leftRect;
					vec4 underline;
					vec4 topIce;
					vec4 rightRect;
					vec4 lastPos;
					// Parameters
					float textSize = hudModule->scale;
					float textPadding = 1.0f * textSize;
					float textHeight = 10.0f * textSize;
					float smoothness = 2;

					struct IModuleContainer {
						// Struct used to Sort IModules in a std::set
						std::shared_ptr<IModule> backingModule;
						std::string moduleName;
						bool enabled;
						int keybind;
						float textWidth;
						vec2* pos;
						bool shouldRender = true;

						IModuleContainer(std::shared_ptr<IModule> mod) {
							auto arrayList = moduleMgr->getModule<GUI>();
							auto hud = moduleMgr->getModule<HudModule>();
							if (arrayList->modes) {
								const char* moduleNameChr = mod->getModuleName();
								moduleName = moduleNameChr;
							} else {
								const char* moduleNameChr = mod->getRawModuleName();
								moduleName = moduleNameChr;
							}

							this->enabled = mod->isEnabled();
							this->keybind = mod->getKey();
							this->backingModule = mod;
							this->pos = mod->getPos();

							if (!this->enabled && *this->pos == vec2(0.f, 0.f))
								this->shouldRender = false;
							this->textWidth = DrawUtils::getTextWidth(&moduleName, hudModule->scale);
						}

						bool operator<(const IModuleContainer& other) const {
							/*if (enabled) {
						if (!other.enabled)  // We are enabled
							return true;
					} else if (other.enabled)  // They are enabled
						return false;*/

							if (this->textWidth == other.textWidth)
								return moduleName < other.moduleName;
							return this->textWidth > other.textWidth;
						}
					};

					// Mouse click detector
					static bool wasLeftMouseDown = GameData::isLeftClickDown();  // Last isDown value
					bool leftMouseDown = GameData::isLeftClickDown();            // current isDown value

					bool executeClick = leftMouseDown && leftMouseDown != wasLeftMouseDown;  // isDown == true AND (current state IS NOT last state)
					wasLeftMouseDown = leftMouseDown;                                        // Set last isDown value

					std::set<IModuleContainer> modContainerList;
					// Fill modContainerList with Modules
					{
						auto lock = moduleMgr->lockModuleList();
						auto hud = moduleMgr->getModule<HudModule>();
						auto watermark = moduleMgr->getModule<Watermark>();
						std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();
						for (auto it : *moduleList) {
							if (it.get() != hudModule)
								if (it.get() != hudModule)
										if (it.get() != hudModule)
											if (it.get() != clickGuiModule)
												modContainerList.emplace(IModuleContainer(it));
						}
					}
					if (hudModule->bottom) {
						yOffset = windowSize.y - textHeight;
					}
					int a = 0;
					int b = 0;
					int c = 0;
					// Fill modContainerList with Modules
					{
						auto lock = moduleMgr->lockModuleList();
						std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();
						for (auto it : *moduleList) {
							if (it.get() != hudModule)
								modContainerList.emplace(IModuleContainer(it));
						}
					}
					if (gui->bottom) {
						yOffset = windowSize.y - textHeight;
					}
					// int a = 0;
					// int b = 0;
					// int c = 0;

					// Loop through mods to display Labels
					float Length = 0.f;
					for (std::set<IModuleContainer>::iterator it = modContainerList.begin(); it != modContainerList.end(); ++it) {
						if (!it->shouldRender)
							continue;

						std::string textStr = it->moduleName;
						float textWidth = it->textWidth;

						float xOffsetOri = windowSize.x - textWidth - (textPadding * 2);

						float xOffset = windowSize.x - it->pos->x;

						it->pos->x += smoothness;

						if (xOffset < xOffsetOri) {
							xOffset = xOffsetOri;
						}
						if (!it->enabled) {
							xOffset += it->pos->y;
							it->pos->y += smoothness;
						}
						if (xOffset >= windowSize.x && !it->enabled) {
							it->pos->x = 0.f;
							it->pos->y = 0.f;
						}
						if (gui->Fluxbar) {
							textPos = vec2(
								xOffset + textPadding - 4,
								yOffset + textPadding);
							FluxBar = vec4(
								windowSize.x - 2,
								yOffset,
								isOnRightSide ? windowSize.x : textWidth + (textPadding * 2),
								yOffset + textPadding * 2 + textHeight);
							rectPos = vec4(
								xOffset - 6,
								yOffset,
								isOnRightSide ? windowSize.x : textWidth + (textPadding * 2),
								yOffset + textPadding * 2 + textHeight);
							leftRect = vec4(
								xOffset - 6,
								yOffset,
								xOffset - 5,
								yOffset + textPadding * 2 + textHeight);
							topIce = vec4(
								xOffset - 7,
								yOffset,
								xOffset - 14,
								yOffset + textPadding * 2 + textHeight);
							rightRect = vec4(
								xOffset - 6,
								yOffset,
								xOffset - 5,
								yOffset + textPadding * 7 + textHeight);
							underline = vec4(
								windowSize.x - (Length + 6.f + (textPadding * 2.f)),
								leftRect.y,
								leftRect.x,
								leftRect.y + 1.f);
						} else {
							textPos = vec2(
								xOffset + textPadding,
								yOffset + textPadding);
							FluxBar = vec4(
								windowSize.x - 3,
								yOffset,
								isOnRightSide ? windowSize.x : textWidth + (textPadding * 2),
								yOffset + textPadding * 2 + textHeight);
							rectPos = vec4(
								xOffset - 2,
								yOffset,
								isOnRightSide ? windowSize.x : textWidth + (textPadding * 2),
								yOffset + textPadding * 2 + textHeight);
							leftRect = vec4(
								xOffset - 2,
								yOffset,
								xOffset - 1,
								yOffset + textPadding * 2 + textHeight);
							topIce = vec4(
								xOffset - 3,
								yOffset,
								xOffset - 10,
								yOffset + textPadding * 2 + textHeight);
							rightRect = vec4(
								xOffset - 6,
								yOffset,
								xOffset - 5,
								yOffset + textPadding * 7 + textHeight);
							underline = vec4(
								windowSize.x - (Length + 2.f + (textPadding * 2.f)),
								leftRect.y,
								leftRect.x,
								leftRect.y + 1.f);
						}
						Length = textWidth;
						c++;
						b++;
						if (b < 20)
							a = moduleMgr->getEnabledModuleCount() * 2;
						else
							b = 0;
						if (gui->mode.selected == 8) {
						currColor[3] = rcolors[3];
						Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[3]);
						currColor[0] += 2.f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[2], currColor[1], currColor[2], currColor[2]);
						// BADMAN
						//currColor[3] = rcolors[3];
						//Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[3]);
						//currColor[0] += 2.f / a * c;
						//Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[2], currColor[1], currColor[2], currColor[2]);
						} else if (gui->mode.selected == 7) {
						currColor[3] = rcolors[3];
						Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[3]);
						currColor[0] += 2.f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[1], currColor[2]);
						//cool rgb
						//currColor[3] = rcolors[3];
						//Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[3]);
						//currColor[0] += 2.f / a * c;
						//Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[1], currColor[2]);
						} else if (gui->mode.selected == 6) {
						currColor[3] = rcolors[3];
						Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[2]);
						currColor[0] += 2.f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[2], currColor[0], currColor[1], currColor[3]);
						// weather+
						//currColor[3] = rcolors[3];
						//Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[2]);
						//currColor[0] += 2.f / a * c;
						//Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[2], currColor[0], currColor[1], currColor[3]);
					    } else if (gui->mode.selected == 4) {
						Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
						currColor[0] += 1.f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[3], currColor[3]);
						// fadeaway
						// Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
						// currColor[0] += 1.f / a * c;
						// Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[3], currColor[3]);
						} else if (gui->mode.selected == 3) {
						currColor[3] = rcolors[3];
						Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[2]);
						currColor[0] += 2.f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[1], currColor[3]);
						// V2
						//currColor[3] = rcolors[3];
						//Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[2]);
						//currColor[0] += 2.f / a * c;
						//Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[1], currColor[3]);
						} else if (gui->mode.selected == 2) {
						currColor[3] = rcolors[3];
						Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
						currColor[0] += 1.f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[1], currColor[2]);
						// Horion
						// currColor[3] = rcolors[3];
						// Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
						// currColor[0] += 1.f / a * c;
						// Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[1], currColor[2]);
					    } else if (gui->mode.selected == 1) {
						currColor[3] = rcolors[5];
						Utils::ColorConvertRGBtoHSV(rcolors[0 & 1], rcolors[2], rcolors[01], currColor[0], currColor[1], currColor[2]);
						currColor[0] += 3.5f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0 & 1], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
						// Surge
						// currColor[3] = rcolors[5];
						// Utils::ColorConvertRGBtoHSV(rcolors[0 & 1], rcolors[2], rcolors[01], currColor[0], currColor[1], currColor[2]);
						// currColor[0] += 3.5f / a * c;
						// Utils::ColorConvertHSVtoRGB(currColor[0 & 1], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
						} else if (gui->mode.selected == 0) {
						currColor[3] = rcolors[3];
						Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[2]);
						currColor[0] += 2.f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
						// BADMAN RGB
						// currColor[3] = rcolors[3];
						// Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[3], currColor[2]);
						// currColor[0] += 2.f / a * c;
						// Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
						} else if (gui->mode.selected == 5) {
						currColor[3] = rcolors[5];
						currColor[3] = rcolors[5];
						Utils::ColorConvertRGBtoHSV(rcolors[0 & 1], rcolors[2], rcolors[01], currColor[0], currColor[1], currColor[2]);
						currColor[0] += .5f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0 & 1], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
						// NG RGBs
						// currColor[3] = rcolors[5];
						// currColor[3] = rcolors[5];
						// Utils::ColorConvertRGBtoHSV(rcolors[0 & 1], rcolors[2], rcolors[01], currColor[0], currColor[1], currColor[2]);
						// currColor[0] += 0.5f / a * c;
						// Utils::ColorConvertHSVtoRGB(currColor[0 & 1], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
						} else {
						currColor[3] = rcolors[5];
						currColor[3] = rcolors[5];
						Utils::ColorConvertRGBtoHSV(rcolors[0 & 1], rcolors[2], rcolors[01], currColor[0], currColor[1], currColor[2]);
						currColor[0] += .5f / a * c;
						Utils::ColorConvertHSVtoRGB(currColor[0 & 1], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
						// NG RGBs
						// currColor[3] = rcolors[5];
						// currColor[3] = rcolors[5];
						// Utils::ColorConvertRGBtoHSV(rcolors[0 & 1], rcolors[2], rcolors[01], currColor[0], currColor[1], currColor[2]);
						// currColor[0] += 0.5f / a * c;
						// Utils::ColorConvertHSVtoRGB(currColor[0 & 1], currColor[2], currColor[2], currColor[0], currColor[1], currColor[2]);
						}

						DrawUtils::fillRectangle(rectPos, MC_Color(GUI::rcolor, GUI::bcolor, GUI::gcolor), gui->opacity);  // Background
						if (gui->Fluxbar)
							if (gui->rgb) {
								DrawUtils::fillRectangle(FluxBar, MC_Color(currColor), 1.f);
							} else {
								if (partner->Partnered.selected == 0)
									DrawUtils::fillRectangle(FluxBar, MC_Color(10, 10, 255), 1.f);
								else
									DrawUtils::fillRectangle(FluxBar, MC_Color(184, 0, 255), 1.f);
							}
						if (gui->rgb) {
							if (gui->underbar) {
								DrawUtils::fillRectangle(underline, MC_Color(currColor), 1.f);
							}
							if (gui->bar) {
								DrawUtils::fillRectangle(leftRect, MC_Color(currColor), 1.f);
							}
						} else {
							if (gui->underbar) {
								if (partner->Partnered.selected == 0)
									DrawUtils::fillRectangle(underline, MC_Color(0, 0, 0), 1.f);
								else
									DrawUtils::fillRectangle(underline, MC_Color(184, 0, 255), 1.f);
							}
							if (gui->bar) {
								if (partner->Partnered.selected == 0)
									DrawUtils::fillRectangle(leftRect, MC_Color(0, 0, 0), 1.f);
								else
									DrawUtils::fillRectangle(leftRect, MC_Color(184, 0, 255), 1.f);
							}
						}
						if (gui->ice) {
							if (gui->rgb) {
								DrawUtils::fillRectangle(topIce, MC_Color(currColor), 1.f);
								DrawUtils::fillRectangle(rightRect, MC_Color(currColor), 1.f);
							} else {
								DrawUtils::fillRectangle(topIce, MC_Color(240, 240, 230), 1.f);
								DrawUtils::fillRectangle(rightRect, MC_Color(184, 0, 255), 1.f);
							}
						}
						if (!GameData::canUseMoveKeys() && rectPos.contains(&mousePos) && gui->clickToggle) {
							vec4 selectedRect = rectPos;
							// selectedRect.x = leftRect.z;
							// selectedRect.x = rightRect.z;
							if (leftMouseDown) {
								DrawUtils::fillRectangle(selectedRect, MC_Color(0.8f, 0.8f, 0.8f), 0.8f);
								if (executeClick)
									it->backingModule->toggle();
							} else
								DrawUtils::fillRectangle(selectedRect, MC_Color(0.8f, 0.8f, 0.8f, 0.8f), 0.3f);
						}
						if (gui->rgb) {
							DrawUtils::drawText(textPos, &textStr, MC_Color(currColor), textSize);
						} else {
							if (partner->Partnered.selected == 0)
								DrawUtils::drawText(textPos, &textStr, MC_Color(0, 0, 255), textSize);
							else if (partner->Partnered.selected == 1)
								DrawUtils::drawText(textPos, &textStr, MC_Color(150, 30, 255), textSize);
							else
								DrawUtils::drawText(textPos, &textStr, MC_Color(0, 246, 255), textSize);
						}
						if (gui->bottom) {
							yOffset -= textHeight + (textPadding * 2);
						} else {
							yOffset += textHeight + (textPadding * 2);
						}
					}
					if (gui->underbar) {
						if (gui->rgb) {
							DrawUtils::fillRectangle(vec4{rectPos.x, rectPos.w, rectPos.z, rectPos.w + 1.f}, MC_Color(currColor), 1.f);
						} else {
							if (partner->Partnered.selected == 0)
								DrawUtils::fillRectangle(vec4{rectPos.x, rectPos.w, rectPos.z, rectPos.w + 1.f}, MC_Color(0, 0, 0), 1.f);
							else
								DrawUtils::fillRectangle(vec4{rectPos.x, rectPos.w, rectPos.z, rectPos.w + 1.f}, MC_Color(184, 0, 255), 1.f);
						}
					}
					c = 0;
					modContainerList.clear();
				}
			}
		}
	}

	if (shouldPostRender) moduleMgr->onPostRender(renderCtx);
	HImGui.endFrame();
	DrawUtils::flush();

	// Draw Info / Alert Boxes
	{
		auto box = g_Data.getFreshInfoBox();
		if (box) {
			box->fade();
			if (box->fadeTarget == 1 && box->closeTimer <= 0 && box->closeTimer > -1)
				box->fadeTarget = 0;
			else if (box->closeTimer > 0 && box->fadeVal > 0.9f)
				box->closeTimer -= 1.f / 60;
			const float paddingHoriz = 20 * box->fadeVal;
			const float paddingVert = 5 * box->fadeVal;
			const float titleTextSize = box->fadeVal * 2;
			const float messageTextSize = box->fadeVal * 1;
			const float titleTextHeight = DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() * titleTextSize;

			int lines = 1;
			std::string substring = box->message;
			while (lines < 5) {
				auto brea = substring.find("\n");
				if (brea == std::string::npos || brea + 1 >= substring.size())
					break;
				substring = substring.substr(brea + 1);
				lines++;
			}
			if (box->message.size() == 0)
				lines = 0;

			const float messageHeight = DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() * messageTextSize * lines;
			static auto partner = moduleMgr->getModule<Partner>();
			float titleWidth = DrawUtils::getTextWidth(&box->title, titleTextSize);
			float msgWidth = DrawUtils::getTextWidth(&box->message, messageTextSize);
			vec2 centerPos(wid.x / 2.f, wid.y / 50.f);
			vec2 textPos = vec2(wid.x / 2.f - titleWidth / 2.f, wid.y / 50.f);
			vec2 msgPos = vec2(wid.x / 2.f - msgWidth / 2.f, textPos.y + titleTextHeight + paddingVert);
			vec4 rectPos = vec4(
				centerPos.x - paddingHoriz - std::max(titleWidth, msgWidth) / 2,
				centerPos.y - paddingVert,
				centerPos.x + paddingHoriz + std::max(titleWidth, msgWidth) / 2,
				centerPos.y + paddingVert * 2 + titleTextHeight + messageHeight * lines);
			DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), box->fadeVal);
			if (hudModule->rgb)
				DrawUtils::drawRectangle(rectPos, currColor, box->fadeVal, 2.f);
			else if (partner->Partnered.selected == 0)
				DrawUtils::drawRectangle(rectPos, MC_Color(0, 0, 255), box->fadeVal, 2.f);
			else
				DrawUtils::drawRectangle(rectPos, MC_Color(184, 0, 255), box->fadeVal, 2.f);

			DrawUtils::drawText(textPos, &box->title, MC_Color(), titleTextSize, box->fadeVal);
			DrawUtils::drawText(msgPos, &box->message, MC_Color(), messageTextSize, box->fadeVal);
		}
	}
	DrawUtils::flush();

	return retval;
}

float* Hooks::Dimension_getFogColor(__int64 _this, float* color, __int64 a3, float a4) {
	static auto oGetFogColor = g_Hooks.Dimension_getFogColorHook->GetFastcall<float*, __int64, float*, __int64, float>();

	static float rcolors[4];

	static auto nightMod = moduleMgr->getModule<NightMode>();
	if (nightMod->isEnabled()) {
		color[0] = 0.f;
		color[1] = 0.f;
		color[2] = 0.2f;
		color[3] = 1;
		return color;
	}

	static float currColor[4];

	static auto rainbowSkyMod = moduleMgr->getModule<RainbowSky>();
	if (rainbowSkyMod->isEnabled()) {
		if (RainbowSky::custom) {
			if (rcolors[3] < 1) {
				rcolors[0] = 1;
				rcolors[1] = 0.2f;
				rcolors[2] = 0.2f;
				rcolors[3] = 1;
			}

			Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);  // perfect code, dont question this

			rcolors[0] += rainbowSkyMod->intensity;
			if (rcolors[0] >= 1) {
				rcolors[0] = 0;
			}

			Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);

			return rcolors;
		} else {
			if (currColor[3] < 1) {
				currColor[0] = 1;
				currColor[1] = 0.2f;
				currColor[2] = 0.2f;
				currColor[3] = 1;
			}

			Utils::ColorConvertRGBtoHSV(currColor[0], currColor[1], currColor[2], currColor[0], currColor[1], currColor[2]);  // perfect code, dont question this

			currColor[0] += rainbowSkyMod->intensity;
			if (currColor[0] >= 1) {
				currColor[0] = 0;
			}

			Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[1], currColor[2]);

			currColor[0] = RainbowSky::red;
			currColor[1] = RainbowSky::green;
			currColor[2] = RainbowSky::blue;

			return currColor;
		}
	}
	return oGetFogColor(_this, color, a3, a4);
}

float Hooks::Dimension_getTimeOfDay(__int64 _this, int a2, float a3) {
	static auto oGetTimeOfDay = g_Hooks.Dimension_getTimeOfDayHook->GetFastcall<float, __int64, int, float>();

	static auto timeChange = moduleMgr->getModule<TimeChanger>();
	if (timeChange->isEnabled()) {
		return timeChange->modifier;
	}

	return oGetTimeOfDay(_this, a2, a3);
}

float Hooks::Dimension_getSunIntensity(__int64 a1, float a2, vec3* a3, float a4) {
	static auto oGetSunIntensity = g_Hooks.Dimension_getSunIntensityHook->GetFastcall<float, __int64, float, vec3*, float>();

	static auto nightMod = moduleMgr->getModule<NightMode>();
	if (nightMod->isEnabled()) {
		return -0.5f;
	}

	return oGetSunIntensity(a1, a2, a3, a4);
}

void Hooks::ChestBlockActor_tick(C_ChestBlockActor* _this, void* a) {
	static auto oTick = g_Hooks.ChestBlockActor_tickHook->GetFastcall<void, C_ChestBlockActor*, void*>();
	oTick(_this, a);
	static auto* chestEspMod = moduleMgr->getModule<StorageESP>();
	if (_this != nullptr && chestEspMod->isEnabled())
		GameData::addChestToList(_this);
}

void Hooks::Actor_lerpMotion(C_Entity* _this, vec3 motVec) {
	static auto oLerp = g_Hooks.Actor_lerpMotionHook->GetFastcall<void, C_Entity*, vec3>();

	if (g_Data.getLocalPlayer() != _this)
		return oLerp(_this, motVec);

	static auto noKnockbackmod = moduleMgr->getModule<Velocity>();
	if (noKnockbackmod->isEnabled()) {
		static void* networkSender = nullptr;

		if (!networkSender)
			networkSender = reinterpret_cast<void*>(9 + FindSignature("48 8B CB FF ?? ?? ?? ?? 00 C6 47 ?? 01 48 8B 5C 24"));

		if (networkSender == _ReturnAddress()) {
			motVec = _this->velocity.lerp(motVec, noKnockbackmod->xModifier, noKnockbackmod->yModifier, noKnockbackmod->xModifier);
		}
	}

	oLerp(_this, motVec);
}

int Hooks::AppPlatform_getGameEdition(__int64 _this) {
	static auto oGetEditon = g_Hooks.AppPlatform_getGameEditionHook->GetFastcall<signed int, __int64>();

	static auto mod = moduleMgr->getModule<EditionFaker>();
	if (mod->isEnabled()) {
		return mod->getFakedEditon();
	}

	return oGetEditon(_this);
}

void Hooks::PleaseAutoComplete(__int64 a1, __int64 a2, TextHolder* text, int a4) {
	static auto oAutoComplete = g_Hooks.PleaseAutoCompleteHook->GetFastcall<void, __int64, __int64, TextHolder*, int>();
	char* tx = text->getText();
	if (tx != nullptr && text->getTextLength() >= 1 && tx[0] == '.') {
		std::string search = tx + 1;                                              // Dont include the '.'
		std::transform(search.begin(), search.end(), search.begin(), ::tolower);  // make the search text lowercase

		struct LilPlump {
			std::string cmdAlias;
			IMCCommand* command = 0;
			bool shouldReplace = true;  // Should replace the current text in the box (autocomplete)

			bool operator<(const LilPlump& o) const {
				return cmdAlias < o.cmdAlias;
			}
		};  // This is needed so the std::set sorts it alphabetically

		std::set<LilPlump> searchResults;

		std::vector<IMCCommand*>* commandList = cmdMgr->getCommandList();
		for (auto it = commandList->begin(); it != commandList->end(); ++it) {  // Loop through commands
			IMCCommand* c = *it;
			auto* aliasList = c->getAliasList();
			for (auto it = aliasList->begin(); it != aliasList->end(); ++it) {  // Loop through aliases
				std::string cmd = *it;
				LilPlump plump;

				for (size_t i = 0; i < search.size(); i++) {  // Loop through search string
					char car = search.at(i);
					if (car == ' ' && i == cmd.size()) {
						plump.shouldReplace = false;
						break;
					} else if (i >= cmd.size())
						goto outerContinue;

					if (car != cmd.at(i))  // and compare
						goto outerContinue;
				}
				// Not at outerContinue? Then we got a good result!
				{
					cmd.insert(0, 1, '.');  // Prepend the '.'

					plump.cmdAlias = cmd;
					plump.command = c;
					searchResults.emplace(plump);
				}

			outerContinue:
				continue;
			}
		}

		if (!searchResults.empty()) {
			LilPlump firstResult = *searchResults.begin();

			size_t maxReplaceLength = firstResult.cmdAlias.size();
			if (searchResults.size() > 1) {
				for (auto it = searchResults.begin()++; it != searchResults.end(); it++) {
					auto alias = it->cmdAlias;
					maxReplaceLength = std::min(maxReplaceLength, alias.size());

					for (int i = 0; i < maxReplaceLength; i++) {
						if (alias[i] != firstResult.cmdAlias[i]) {
							maxReplaceLength = i;
							break;
						}
					}
				}
			} else
				maxReplaceLength = firstResult.cmdAlias.size();

			g_Data.getGuiData()->displayClientMessageF("==========");
			if (searchResults.size() > 1) {
				for (auto it = searchResults.begin(); it != searchResults.end(); ++it) {
					LilPlump plump = *it;
					g_Data.getGuiData()->displayClientMessageF("%s%s - %s%s", plump.cmdAlias.c_str(), GRAY, ITALIC, plump.command->getDescription());
				}
			}
			if (firstResult.command->getUsage(firstResult.cmdAlias.c_str() + 1)[0] == 0)
				g_Data.getGuiData()->displayClientMessageF("%s%s %s- %s", WHITE, firstResult.cmdAlias.c_str(), GRAY, firstResult.command->getDescription());
			else
				g_Data.getGuiData()->displayClientMessageF("%s%s %s %s- %s", WHITE, firstResult.cmdAlias.c_str(), firstResult.command->getUsage(firstResult.cmdAlias.c_str() + 1 /*exclude prefix*/), GRAY, firstResult.command->getDescription());

			if (firstResult.shouldReplace) {
				if (search.size() == firstResult.cmdAlias.size() - 1 && searchResults.size() == 1) {
					maxReplaceLength++;
					firstResult.cmdAlias.append(" ");
				}
				text->setText(firstResult.cmdAlias.substr(0, maxReplaceLength));  // Set text
				using syncShit = void(__fastcall*)(TextHolder*, TextHolder*);
				static syncShit sync = reinterpret_cast<syncShit>(Utils::FindSignature("40 53 48 83 EC ? 48 8B DA 48 8D 4C 24 ? E8 ? ? ? ? 90 48 8B 40 ? 48 8B 08 48 8B 01 48 8B D3 FF 90 ? ? ? ? 90 F0 48 FF 0D ? ? ? ? 48 8B 44 24 ? 48 85 C0 74 ? 48 83 38 ? 74 ? 80 7C 24 ? ? 74 ? F0 48 FF 0D ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 80 7C 24 ? ? 74 ? E8 ? ? ? ? C6 44 24 ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 80 7C 24 ? ? 74 ? 48 8B 4C 24 ? E8 ? ? ? ? 90 48 83 C4 ? 5B C3 B9 ? ? ? ? E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53"));
				sync(text, text);
			}
		}
		return;
	}
	oAutoComplete(a1, a2, text, a4);
}

void Hooks::Actor_rotation(C_Entity* _this, vec2& sexyAngle) {
	static auto oFunc = g_Hooks.Actor_rotationHook->GetFastcall<void, C_Entity*, vec2&>();
	static auto killauraMod = moduleMgr->getModule<Killaura>();
	static auto potionAuramod = moduleMgr->getModule<PotionAura>();
	static auto freelookMod = moduleMgr->getModule<Freelook>();
	static auto botMod = moduleMgr->getModule<FightBot>();
	static auto targetMod = moduleMgr->getModule<TargetStrafe>();
#ifdef _DEBUG
	static auto test = moduleMgr->getModule<TestModule>();
#endif
	if (botMod->isEnabled() && g_Data.getLocalPlayer() == _this && !botMod->targetListA && botMod->sexy) {
		sexyAngle = {botMod->joe};
	}
	if (killauraMod->isEnabled() && g_Data.getLocalPlayer() == _this && !killauraMod->targetListA && killauraMod->rots.selected == 0) {
		sexyAngle = {killauraMod->joe};
	}
	if (potionAuramod->isEnabled() && g_Data.getLocalPlayer() == _this && !potionAuramod->targetListA && potionAuramod->sexy) {
		sexyAngle = {potionAuramod->joe};
	}
	if (freelookMod->isEnabled() && g_Data.getLocalPlayer() == _this) {
		sexyAngle = {freelookMod->oldPos.x, freelookMod->oldPos.y};
	}
	if (targetMod->isEnabled() && g_Data.getLocalPlayer() == _this) {
		sexyAngle = {targetMod->hoe.x, targetMod->hoe.y};
	}
	oFunc(_this, sexyAngle);
}

void Hooks::LoopbackPacketSender_sendToServer(C_LoopbackPacketSender* a, C_Packet* packet) {
	static auto oFunc = g_Hooks.LoopbackPacketSender_sendToServerHook->GetFastcall<void, C_LoopbackPacketSender*, C_Packet*>();

	// static auto autoSneakMod = moduleMgr->getModule<AutoSneak>();
	static auto blinkMod = moduleMgr->getModule<Blink>();
	static auto nofall = moduleMgr->getModule<NoFall>();
	static auto noPacketMod = moduleMgr->getModule<NoPacket>();
	static auto tp = moduleMgr->getModule<Teleport>();
	static auto autoSneakMod = moduleMgr->getModule<AutoSneak>();
	static auto hiveFly = moduleMgr->getModule<HiveFly>();
	static auto disabler = moduleMgr->getModule<Disabler>();
	static auto test = moduleMgr->getModule<TestModule>();
	static auto pm = moduleMgr->getModule<PacketMultiplier>();
	// if (test->isEnabled() && packet->isInstanceOf<C_NPCRequestPacket>()) {  //Good for testing packet sigs
	// return;
	//	g_Data.getLocalPlayer()->jumpFromGround();
	// }

	if (noPacketMod->isEnabled() && g_Data.isInGame())
		return;

	if (nofall->isEnabled() && g_Data.isInGame() && nofall->nopackety && !g_Data.getLocalPlayer()->onGround && !hiveFly->isEnabled()) {
		if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			auto* mpp = reinterpret_cast<C_MovePlayerPacket*>(packet);
			mpp->onGround = true;
		}
		g_Data.getLocalPlayer()->fallDistance = 0.f;
		return;
	}

	if (nofall->isEnabled() && g_Data.isInGame()) {
		if (nofall->server && !hiveFly->isEnabled()) {
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			if (packet->isInstanceOf<C_MovePlayerPacket>()) {
				auto* ree = reinterpret_cast<C_MovePlayerPacket*>(packet);
				if (g_Data.getLocalPlayer() != nullptr && g_Data.getLocalPlayer()->fallDistance > 4.f) {
					ree->onGround = true;
					return;  // dont send Off groung packet
				}
			}
		}
	}

	if (blinkMod->isEnabled()) {
		if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
			if (blinkMod->isEnabled()) {
				if (packet->isInstanceOf<C_MovePlayerPacket>()) {
					C_MovePlayerPacket* meme = reinterpret_cast<C_MovePlayerPacket*>(packet);
					meme->onGround = true;                                                            // Don't take Fall Damages when turned off
					blinkMod->getMovePlayerPacketHolder()->push_back(new C_MovePlayerPacket(*meme));  // Saving the packets
				} else {
					if (g_Data.getRakNetInstance()->isonaServer())  // if ur on a server, do this but if ur on a world dont bec it crashes
						blinkMod->getPlayerAuthInputPacketHolder()->push_back(new PlayerAuthInputPacket(*reinterpret_cast<PlayerAuthInputPacket*>(packet)));
				}
			}
			return;  // Dont call LoopbackPacketSender_sendToServer
		}
	} else if (!blinkMod->isEnabled()) {
		if (blinkMod->getMovePlayerPacketHolder()->size() > 0) {
			for (auto it : *blinkMod->getMovePlayerPacketHolder()) {
				oFunc(a, (it));
				delete it;
				it = nullptr;
			}
			blinkMod->getMovePlayerPacketHolder()->clear();
			return;
		}
		if (blinkMod->getPlayerAuthInputPacketHolder()->size() > 0) {
			for (auto it : *blinkMod->getPlayerAuthInputPacketHolder()) {
				oFunc(a, (it));
				delete it;
				it = nullptr;
			}
			blinkMod->getPlayerAuthInputPacketHolder()->clear();
			return;
		}
	}

	moduleMgr->onSendPacket(packet);

	if (disabler->isEnabled() && disabler->hive && packet->isInstanceOf<NetworkLatencyPacket>()) {
		NetworkLatencyPacket* pkt = (NetworkLatencyPacket*)packet;
		if (pkt->timeStamp == 69420) {
			// g_Data.getGuiData()->displayClientMessageF("DaddyUwU");//tests
			return;
		}
	}

	/*if (strcmp(packet->getName()->getText(), "EmotePacket") == 0) {
		auto varInt = reinterpret_cast<__int64*>(reinterpret_cast<__int64>(packet) + 0x28);
		auto text = reinterpret_cast<TextHolder*>(reinterpret_cast<__int64>(packet) + 0x30);
		auto bet = reinterpret_cast<unsigned char*>(reinterpret_cast<__int64>(packet) + 0x50);
		logF("emote %llX %s %i", *varInt, text->getText(), *bet);
	} fix emote crashing*/

	if (!pm->isEnabled()) {
		oFunc(a, packet);
	} else {
		for (int PacketMult = 0; PacketMult < pm->multiplier; PacketMult++)
		oFunc(a, packet);
	}
}

float Hooks::LevelRendererPlayer_getFov(__int64 _this, float a2, bool a3) {
	static auto oGetFov = g_Hooks.LevelRendererPlayer_getFovHook->GetFastcall<float, __int64, float, bool>();
	return oGetFov(_this, a2, a3);
}

void Hooks::MultiLevelPlayer_tick(C_EntityList* _this) {
	static auto oTick = g_Hooks.MultiLevelPlayer_tickHook->GetFastcall<void, C_EntityList*>();
	C_GameMode* gm = g_Data.getCGameMode();
	if (gm != nullptr) {
		moduleMgr->onTick(gm);
		oTick(_this);
	}
	GameData::EntityList_tick(_this);
	if (gm != nullptr) {
		moduleMgr->onPreTick(gm);
	}
}

void Hooks::GameMode_startDestroyBlock(C_GameMode* _this, vec3i* a2, uint8_t face, void* a4, void* a5) {
	static auto oFunc = g_Hooks.GameMode_startDestroyBlockHook->GetFastcall<void, C_GameMode*, vec3i*, uint8_t, void*, void*>();

	static auto nukerModule = moduleMgr->getModule<Nuker>();
	static auto instaBreakModule = moduleMgr->getModule<InstaBreak>();
	static auto fucker = moduleMgr->getModule<Fucker>();

	if (nukerModule->isEnabled()) {
		vec3i tempPos;

		int range = nukerModule->getNukerRadius();
		const bool isVeinMiner = nukerModule->isVeinMiner();
		const bool isAutoMode = nukerModule->isAutoMode();

		C_BlockSource* region = g_Data.getLocalPlayer()->region;
		auto selectedBlockId = ((region->getBlock(*a2)->blockLegacy))->blockId;
		uint8_t selectedBlockData = region->getBlock(*a2)->data;

		if (!isAutoMode) {
			for (int x = -range; x < range; x++) {
				for (int y = -range; y < range; y++) {
					for (int z = -range; z < range; z++) {
						tempPos.x = a2->x + x;
						tempPos.y = a2->y + y;
						tempPos.z = a2->z + z;
						if (tempPos.y > -64) {
							C_Block* blok = region->getBlock(tempPos);
							uint8_t data = blok->data;
							auto id = blok->blockLegacy->blockId;
							if (blok->blockLegacy->material->isSolid == true && (!isVeinMiner || (id == selectedBlockId && data == selectedBlockData)))
								_this->destroyBlock(&tempPos, face);
						}
					}
				}
			}
		}
		return;
	}
	if (instaBreakModule->isEnabled() && instaBreakModule->mode.selected == 0) {
		_this->destroyBlock(a2, face);
		return;
	}

	oFunc(_this, a2, face, a4, a5);
}

void Hooks::HIDController_keyMouse(C_HIDController* _this, void* a2, void* a3) {
	static auto oFunc = g_Hooks.HIDController_keyMouseHook->GetFastcall<void, C_HIDController*, void*, void*>();
	GameData::setHIDController(_this);
	isTicked = true;
	oFunc(_this, a2, a3);
	return;
}

int Hooks::BlockLegacy_getRenderLayer(C_BlockLegacy* a1) {
	static auto oFunc = g_Hooks.BlockLegacy_getRenderLayerHook->GetFastcall<int, C_BlockLegacy*>();

	static auto xrayMod = moduleMgr->getModule<Xray>();

	bool shouldRender = false;

	if (xrayMod->isEnabled()) {
		if (xrayMod->emeralds) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strstr(text, "emerald_ore") == 0)
				if (strstr(text, "emerald_block") == 0)
					if (strcmp(text, "lava") != NULL)
						if (strcmp(text, "water") != NULL)
							if (strcmp(text, "barrel") != NULL)
								if (strcmp(text, "portal") != NULL)
									if (strcmp(text, "deny") != NULL)
										if (strcmp(text, "end_portal") != NULL)
											if (strcmp(text, "end_portal_frame") != NULL)
												if (strcmp(text, "command_block") != NULL)
													if (strcmp(text, "chain_command_block") != NULL)
														if (strcmp(text, "repeating_command_block") != NULL)
															return 10;
		}

		if (xrayMod->diamonds) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strstr(text, "diamond_ore") == NULL)
				if (strstr(text, "diamond_block") == NULL)
					if (strcmp(text, "lava") != NULL)
						if (strcmp(text, "water") != NULL)
							if (strcmp(text, "barrel") != NULL)
								if (strcmp(text, "portal") != NULL)
									if (strcmp(text, "deny") != NULL)
										if (strcmp(text, "end_portal") != NULL)
											if (strcmp(text, "end_portal_frame") != NULL)
												if (strcmp(text, "command_block") != NULL)
													if (strcmp(text, "chain_command_block") != NULL)
														if (strcmp(text, "repeating_command_block") != NULL)
															return 10;
		}

		if (xrayMod->iron) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strstr(text, "iron_ore") == NULL)
				if (strstr(text, "iron_block") == NULL)
					if (strcmp(text, "lava") != NULL)
						if (strcmp(text, "water") != NULL)
							if (strcmp(text, "barrel") != NULL)
								if (strcmp(text, "portal") != NULL)
									if (strcmp(text, "deny") != NULL)
										if (strcmp(text, "end_portal") != NULL)
											if (strcmp(text, "end_portal_frame") != NULL)
												if (strcmp(text, "command_block") != NULL)
													if (strcmp(text, "chain_command_block") != NULL)
														if (strcmp(text, "repeating_command_block") != NULL)
															return 10;
		}

		if (xrayMod->gold) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strstr(text, "gold_ore") == NULL)
				if (strstr(text, "gold_block") == NULL)
					if (strcmp(text, "gilded_blackstone") != NULL)
						if (strcmp(text, "lava") != NULL)
							if (strcmp(text, "water") != NULL)
								if (strcmp(text, "barrel") != NULL)
									if (strcmp(text, "portal") != NULL)
										if (strcmp(text, "deny") != NULL)
											if (strcmp(text, "end_portal") != NULL)
												if (strcmp(text, "end_portal_frame") != NULL)
													if (strcmp(text, "command_block") != NULL)
														if (strcmp(text, "chain_command_block") != NULL)
															if (strcmp(text, "repeating_command_block") != NULL)
																return 10;
		}

		if (xrayMod->debris) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strstr(text, "ancient_debris") == NULL)
				if (strstr(text, "netherite_block") == NULL)
					if (strcmp(text, "lava") != NULL)
						if (strcmp(text, "water") != NULL)
							if (strcmp(text, "barrel") != NULL)
								if (strcmp(text, "portal") != NULL)
									if (strcmp(text, "deny") != NULL)
										if (strcmp(text, "end_portal") != NULL)
											if (strcmp(text, "end_portal_frame") != NULL)
												if (strcmp(text, "command_block") != NULL)
													if (strcmp(text, "chain_command_block") != NULL)
														if (strcmp(text, "repeating_command_block") != NULL)
															return 10;
		}

		if (xrayMod->coal) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strstr(text, "coal_ore") == NULL)
				if (strstr(text, "coal_block") == NULL)
					if (strcmp(text, "lava") != NULL)
						if (strcmp(text, "water") != NULL)
							if (strcmp(text, "barrel") != NULL)
								if (strcmp(text, "portal") != NULL)
									if (strcmp(text, "deny") != NULL)
										if (strcmp(text, "end_portal") != NULL)
											if (strcmp(text, "end_portal_frame") != NULL)
												if (strcmp(text, "command_block") != NULL)
													if (strcmp(text, "chain_command_block") != NULL)
														if (strcmp(text, "repeating_command_block") != NULL)
															return 10;
		}

		if (xrayMod->redstone) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strstr(text, "redstone_ore") == NULL)
				if (strstr(text, "redstone_block") == NULL)
					if (strcmp(text, "lava") != NULL)
						if (strcmp(text, "water") != NULL)
							if (strcmp(text, "barrel") != NULL)
								if (strcmp(text, "portal") != NULL)
									if (strcmp(text, "deny") != NULL)
										if (strcmp(text, "end_portal") != NULL)
											if (strcmp(text, "end_portal_frame") != NULL)
												if (strcmp(text, "command_block") != NULL)
													if (strcmp(text, "chain_command_block") != NULL)
														if (strcmp(text, "repeating_command_block") != NULL)
															return 10;
		}

		if (xrayMod->lapis) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strstr(text, "lapis_ore") == NULL)
				if (strstr(text, "lapis_block") == NULL)
					if (strcmp(text, "lava") != NULL)
						if (strcmp(text, "water") != NULL)
							if (strcmp(text, "barrel") != NULL)
								if (strcmp(text, "portal") != NULL)
									if (strcmp(text, "deny") != NULL)
										if (strcmp(text, "end_portal") != NULL)
											if (strcmp(text, "end_portal_frame") != NULL)
												if (strcmp(text, "command_block") != NULL)
													if (strcmp(text, "chain_command_block") != NULL)
														if (strcmp(text, "repeating_command_block") != NULL)
															return 10;
		}

		if (xrayMod->other) {
			shouldRender = true;
			char* text = a1->name.getText();
			if (strcmp(text, "lava") != NULL)
				if (strcmp(text, "water") != NULL)
					if (strcmp(text, "barrel") != NULL)
						if (strcmp(text, "portal") != NULL)
							if (strcmp(text, "deny") != NULL)
								if (strcmp(text, "end_portal") != NULL)
									if (strcmp(text, "end_portal_frame") != NULL)
										if (strcmp(text, "command_block") != NULL)
											if (strcmp(text, "chain_command_block") != NULL)
												if (strcmp(text, "repeating_command_block") != NULL)
													return 10;
		}

		char* text = a1->name.getText();
		if (strstr(text, "ore") == NULL)
			if (strstr(text, "ancient_debris") == NULL)
				if (strstr(text, "netherite_block") == NULL)
					if (strstr(text, "diamond_block") == NULL)
						if (strstr(text, "emerald_block") == NULL)
							if (strstr(text, "gold_block") == NULL)
								if (strstr(text, "iron_block") == NULL)
									if (strstr(text, "coal_block") == NULL)
										if (strstr(text, "redstone_block") == NULL)
											if (strstr(text, "lapis_block") == NULL)
												if (strcmp(text, "gilded_blackstone") != NULL)
													if (strcmp(text, "lava") != NULL)
														if (strcmp(text, "water") != NULL)
															if (strcmp(text, "barrel") != NULL)
																if (strcmp(text, "portal") != NULL)
																	if (strcmp(text, "deny") != NULL)
																		if (strcmp(text, "end_portal") != NULL)
																			if (strcmp(text, "end_portal_frame") != NULL)
																				if (strcmp(text, "command_block") != NULL)
																					if (strcmp(text, "chain_command_block") != NULL)
																						if (strcmp(text, "repeating_command_block") != NULL)
																							return 10;

	}
	return oFunc(a1);
}

__int8* Hooks::BlockLegacy_getLightEmission(C_BlockLegacy* a1, __int8* a2) {
	static auto oFunc = g_Hooks.BlockLegacy_getLightEmissionHook->GetFastcall<__int8*, C_BlockLegacy*, __int8*>();

	static auto xrayMod = moduleMgr->getModule<Xray>();
	if (xrayMod->isEnabled()) {
		*a2 = 15;
		return a2;
	}
	return oFunc(a1, a2);
}

__int64 Hooks::LevelRenderer_renderLevel(__int64 _this, __int64 a2, __int64 a3) {
	static auto oFunc = g_Hooks.LevelRenderer_renderLevelHook->GetFastcall<__int64, __int64, __int64, __int64>();

	using reloadShit_t = void(__fastcall*)(__int64);
	static reloadShit_t reloadChunk = nullptr;

	if (!reloadChunk) {
		// RenderChunkCoordinator::rebuildAllRenderChunkGeometry
		reloadChunk = reinterpret_cast<reloadShit_t>(FindSignature("48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 48 8B F9 48 8D A9"));
	}

	static auto xrayMod = moduleMgr->getModule<Xray>();

	static bool lastState = false;
	if (lastState != xrayMod->isEnabled()) {
		// LevelRenderer::rebuildAllRenderChunkGeometry
		lastState = xrayMod->isEnabled();
		unsigned long long* v5;  // rdi
		unsigned long long* i;   // rbx

		v5 = *(unsigned long long**)(_this + 32);
		for (i = (unsigned long long*)*v5; i != v5; i = (unsigned long long*)*i)
			reloadChunk(i[3]);
	}

	auto ret = oFunc(_this, a2, a3);

	DrawUtils::setGameRenderContext(a2);
	moduleMgr->onLevelRender();
	DrawUtils::setGameRenderContext(0);

	return ret;
}

void Hooks::ClickFunc(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
	static auto oFunc = g_Hooks.ClickFuncHook->GetFastcall<void, __int64, char, char, __int16, __int16, __int16, __int16, char>();
	static auto clickGuiModule = moduleMgr->getModule<ClickGuiMod>();

	// MouseButtons
	// 0 = mouse move
	// 1 = left click
	// 2 = right click
	// 3 = middle click
	// 4 = scroll   (isDown: 120 (SCROLL UP) and -120 (SCROLL DOWN))

	ClickGui::onMouseClickUpdate((int)mouseButton, isDown);
	HImGui.onMouseClickUpdate((int)mouseButton, isDown);

	if (isDown)
		if (mouseButton == 1)
			g_Data.leftclickCount++;
		else if (mouseButton == 2)
			g_Data.rightclickCount++;

	if (clickGuiModule->isEnabled()) {
		if (mouseButton == 4) {
			ClickGui::onWheelScroll(isDown > 0);
		}
		if (mouseButton != 0)  // Mouse click event
			return;
	}
	return oFunc(a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8);
}

__int64 Hooks::MoveInputHandler_tick(C_MoveInputHandler* a1, C_Entity* a2) {
	static auto oTick = g_Hooks.MoveInputHandler_tickHook->GetFastcall<__int64, C_MoveInputHandler*, C_Entity*>();

	auto ret = oTick(a1, a2);
	moduleMgr->onMove(a1);

	return 0;
}

__int64 Hooks::ChestScreenController_tick(C_ChestScreenController* a1) {
	static auto oFunc = g_Hooks.ChestScreenController_tickHook->GetFastcall<__int64, C_ChestScreenController*>();

	static auto chestStealerMod = moduleMgr->getModule<ChestStealer>();
	if (chestStealerMod->isEnabled()) chestStealerMod->chestScreenController_tick(a1);

	return oFunc(a1);
}

__int64 Hooks::inventoryScreen__tick(C_CraftingScreenController* a1) {
	static auto oFunc = g_Hooks.inventoryScreen__tickHook->GetFastcall<__int64, C_CraftingScreenController*>();
	std::string screenName(g_Hooks.currentScreenName);

	static auto AutoArmorMod = moduleMgr->getModule<AutoArmor>();
	if (AutoArmorMod->isEnabled() && AutoArmorMod->openInv) AutoArmorMod->inventoryScreen = a1;

	return oFunc(a1);
}

float Hooks::GetGamma(uintptr_t* a1) {
	static auto fullbright = moduleMgr->getModule<Camera>();
	static auto xrayMod = moduleMgr->getModule<Xray>();
	static auto nametagmod = moduleMgr->getModule<NameTags>();
	static auto zoomMod = moduleMgr->getModule<Zoom>();
	static auto noRenderMod = moduleMgr->getModule<NoRender>();

	uintptr_t** list = (uintptr_t**)a1;

	char obtainedSettings = 0;
	bool hadIt = false;
	for (uint16_t i = 3; i < 450; i++) {
		if (list[i] == nullptr) continue;
		uintptr_t* info = *(uintptr_t**)((uintptr_t)list[i] + 8);
		if (info == nullptr) continue;

		TextHolder* translateName = (TextHolder*)((uintptr_t)info + 0x1D8);
		TextHolder* settingname = (TextHolder*)((uintptr_t)info + 0x188);

		if (!strcmp(translateName->getText(), "options.smoothlighting")) {
			if (hadIt) continue;
			bool* smoothlightning = (bool*)((uintptr_t)list[i] + 16);
			xrayMod->smoothLightningSetting = smoothlightning;
			obtainedSettings++;
			hadIt = true;
		}
		if (noRenderMod->isEnabled()) {
		 if (!strcmp(translateName->getText(), "options.dev_disableRenderEntities")) {
				bool* disableRenderEnts = (bool*)((uintptr_t)list[i] + 16);
			*disableRenderEnts = noRenderMod->entities;
				obtainedSettings++;
				}
		else if (!strcmp(translateName->getText(), "options.dev_disableRenderBlockEntities")) {
			bool* disableRenderBlockEnts = (bool*)((uintptr_t)list[i] + 16);
			*disableRenderBlockEnts = noRenderMod->blockEntities;
			obtainedSettings++;
			}
			else if (!strcmp(translateName->getText(), "options.dev_disableRenderParticles")) {
				bool* disableRenderParticles = (bool*)((uintptr_t)list[i] + 16);
				*disableRenderParticles = noRenderMod->particles;
				obtainedSettings++;
				}
			else if (!strcmp(translateName->getText(), "options.dev_disableRenderWeather")) {
				bool* disableRenderParticles = (bool*)((uintptr_t)list[i] + 16);
				*disableRenderParticles = noRenderMod->weather;
				obtainedSettings++;
			}
		} else if (!strcmp(settingname->getText(), "gfx_ingame_player_names")) {
			bool* ingamePlayerName = (bool*)((uintptr_t)list[i] + 16);
			nametagmod->ingameNametagSetting = ingamePlayerName;
			obtainedSettings++;
		} else if (!strcmp(settingname->getText(), "gfx_field_of_view")) {
			float* FieldOfView = (float*)((uintptr_t)list[i] + 24);
			if (zoomMod->isEnabled())
				zoomMod->OGFov = *FieldOfView;
			obtainedSettings++;
		}
		if (obtainedSettings == 7) break;
	}

	if (xrayMod->isEnabled())
		return 25.f;

	if (fullbright->isEnabled())
		return fullbright->intensity;

	static auto ofunc = g_Hooks.GetGammaHook->GetFastcall<float, uintptr_t*>();
	return ofunc(a1);
}

bool Hooks::Actor_isInWater(C_Entity* _this) {
	static auto oFunc = g_Hooks.Actor_isInWaterHook->GetFastcall<bool, C_Entity*>();

	if (g_Data.getLocalPlayer() != _this)
		return oFunc(_this);

	static auto airSwimModule = moduleMgr->getModule<AirSwim>();
	if (airSwimModule->isEnabled())
		return true;

	return oFunc(_this);
}

void Hooks::JumpPower(C_Entity* a1, float a2) {
	static auto oFunc = g_Hooks.JumpPowerHook->GetFastcall<void, C_Entity*, float>();
	static auto highJumpMod = moduleMgr->getModule<HighJump>();
	static auto freeMod = moduleMgr->getModule<Freecam>();
	if (highJumpMod->isEnabled() && g_Data.getLocalPlayer() == a1) {
		a1->velocity.y = highJumpMod->jumpPower;
		return;
	}
	if (freeMod->isEnabled() && g_Data.getLocalPlayer() == a1) {
		// a1->velocity.y = 0;
		// return;
	}
	oFunc(a1, a2);
}

void Hooks::Actor_ascendLadder(C_Entity* _this) {
	static auto oFunc = g_Hooks.Actor_ascendLadderHook->GetFastcall<void, C_Entity*>();

	static auto fastLadderModule = moduleMgr->getModule<FastLadder>();
	if (fastLadderModule->isEnabled() && g_Data.getLocalPlayer() == _this) {
		_this->velocity.y = fastLadderModule->speed;
		return;
	}
	return oFunc(_this);
}

void Hooks::Actor_swing(C_Entity* _this) {
	static auto oFunc = g_Hooks.Actor_swingHook->GetFastcall<void, C_Entity*>();
	static auto noSwingMod = moduleMgr->getModule<NoSwing>();
	static auto killMod = moduleMgr->getModule<Killaura>();
	static auto scaffMod = moduleMgr->getModule<Scaffold>();
	static auto breakmod = moduleMgr->getModule<Fucker>();
	if (!(noSwingMod->isEnabled() || scaffMod->isEnabled() && scaffMod->noSwing || breakmod->isEnabled() && breakmod->noSwing && breakmod->destroy)) return oFunc(_this);
}

void Hooks::Actor_startSwimming(C_Entity* _this) {
	static auto oFunc = g_Hooks.Actor_startSwimmingHook->GetFastcall<void, C_Entity*>();

	static auto jesusModule = moduleMgr->getModule<Jesus>();
	if (jesusModule->isEnabled() && g_Data.getLocalPlayer() == _this)
		return;

	oFunc(_this);
}

void Hooks::RakNetInstance_tick(C_RakNetInstance* _this, __int64 a2, __int64 a3) {
	static auto oTick = g_Hooks.RakNetInstance_tickHook->GetFastcall<void, C_RakNetInstance*, __int64, __int64>();
	if (a3 == 0) GameData::setRakNetInstance(_this);
	oTick(_this, a2, a3);
}

float Hooks::GameMode_getPickRange(C_GameMode* _this, __int64 a2, char a3) {
	static auto oFunc = g_Hooks.GameMode_getPickRangeHook->GetFastcall<float, C_GameMode*, __int64, char>();

	if (g_Data.getLocalPlayer() != nullptr) {
		static auto extendedBlockReachModule = moduleMgr->getModule<ExtendedBlockReach>();
		if (extendedBlockReachModule->isEnabled())
			return extendedBlockReachModule->getBlockReach();

		static auto teleportModule = moduleMgr->getModule<Teleport>();
		if (teleportModule->isEnabled())
			return 255;
	}

	return oFunc(_this, a2, a3);
}

__int64 Hooks::ConnectionRequest_create(__int64 _this, __int64 privateKeyManager, void* a3, TextHolder* selfSignedId, TextHolder* serverAddress, __int64 clientRandomId, TextHolder* skinId, SkinData* skinData, __int64 capeData, CoolSkinData* coolSkinStuff, TextHolder* deviceId, int inputMode, int uiProfile, int guiScale, TextHolder* languageCode, bool sendEduModeParams, TextHolder* tenantId, __int64 unused, TextHolder* platformUserId, TextHolder* thirdPartyName, bool thirdPartyNameOnly, TextHolder* platformOnlineId, TextHolder* platformOfflineId, TextHolder* capeId) {
	static auto oFunc = g_Hooks.ConnectionRequest_createHook->GetFastcall<__int64, __int64, __int64, void*, TextHolder*, TextHolder*, __int64, TextHolder*, SkinData*, __int64, CoolSkinData*, TextHolder*, int, int, int, TextHolder*, bool, TextHolder*, __int64, TextHolder*, TextHolder*, bool, TextHolder*, TextHolder*, TextHolder*>();

	auto geoOverride = g_Data.getCustomGeoOverride();

	if (g_Data.allowWIPFeatures()) {
		logF("Connection Request: InputMode: %i UiProfile: %i GuiScale: %i", inputMode, uiProfile, guiScale);

		// Logger::WriteBigLogFileF(skinGeometryData->getTextLength() + 20, "Geometry: %s", skinGeometryData->getText());
		auto hResourceGeometry = FindResourceA((HMODULE)g_Data.getDllModule(), MAKEINTRESOURCEA(IDR_TEXT1), "TEXT");
		auto hMemoryGeometry = LoadResource((HMODULE)g_Data.getDllModule(), hResourceGeometry);

		auto sizeGeometry = SizeofResource((HMODULE)g_Data.getDllModule(), hResourceGeometry);
		auto ptrGeometry = LockResource(hMemoryGeometry);

		auto hResourceSteve = FindResourceA((HMODULE)g_Data.getDllModule(), MAKEINTRESOURCEA(IDR_STEVE), (char*)RT_RCDATA);
		auto hMemorySteve = LoadResource((HMODULE)g_Data.getDllModule(), hResourceSteve);

		auto sizeSteve = SizeofResource((HMODULE)g_Data.getDllModule(), hResourceSteve);
		auto ptrSteve = LockResource(hMemorySteve);

		// std::unique_ptr<TextHolder> newGeometryData(new TextHolder(ptrGeometry, sizeGeometry));
		TextHolder* newGeometryData = nullptr;

		if (std::get<0>(geoOverride)) {  // Is overriding geometry
			auto overrideGeo = std::get<1>(geoOverride);
			newGeometryData = new TextHolder(*overrideGeo.get());
		} else {  // Default

			/*char* str;  // Obj text
			{
				auto hResourceObj = FindResourceA(g_Data.getDllModule(), MAKEINTRESOURCEA(IDR_OBJ), "TEXT");
				auto hMemoryObj = LoadResource(g_Data.getDllModule(), hResourceObj);
				auto sizeObj = SizeofResource(g_Data.getDllModule(), hResourceObj);
				auto ptrObj = LockResource(hMemoryObj);
				str = new char[sizeObj + 1];
				memset(str, 0, sizeObj + 1);
				memcpy(str, ptrObj, sizeObj);
			}
			newGeometryData = new TextHolder(SkinUtil::modGeometry(reinterpret_cast<char*>(ptrGeometry), SkinUtil::objToMesh(str)));*/
		}

		SkinData* newSkinData = new SkinData();
		newSkinData->SkinWidth = 128;
		newSkinData->SkinHeight = 128;
		newSkinData->skinData = ptrSteve;
		newSkinData->skinSize = sizeSteve;

		auto texOverride = g_Data.getCustomTextureOverride();
		auto texture = std::get<1>(texOverride);  // Put it here so it won't go out of scope until after it has been used
		if (std::get<0>(texOverride)) {           // Enabled
			newSkinData->skinData = std::get<0>(*texture.get()).get();
			newSkinData->skinSize = std::get<1>(*texture.get());
		}

		// Logger::WriteBigLogFileF(newGeometryData->getTextLength() + 20, "Geometry: %s", newGeometryData->getText());
		TextHolder* newSkinResourcePatch = new TextHolder(Utils::base64_decode("ewogICAiZ2VvbWV0cnkiIDogewogICAgICAiYW5pbWF0ZWRfZmFjZSIgOiAiZ2VvbWV0cnkuYW5pbWF0ZWRfZmFjZV9wZXJzb25hXzRjZGJiZmFjYTI0YTk2OGVfMF8wIiwKICAgICAgImRlZmF1bHQiIDogImdlb21ldHJ5LnBlcnNvbmFfNGNkYmJmYWNhMjRhOTY4ZV8wXzAiCiAgIH0KfQo="));

		TextHolder* fakeName = g_Data.getFakeName();
		TextHolder resourcePatchBackup;

		if (newGeometryData != nullptr) {
			memcpy(&resourcePatchBackup, &coolSkinStuff->skinResourcePatch, sizeof(TextHolder));
			memcpy(&coolSkinStuff->skinResourcePatch, newSkinResourcePatch, sizeof(TextHolder));
			styledReturnText = *newGeometryData;
			overrideStyledReturn = true;
		}

		//  newGeometryData == nullptr ? skinResourcePatch : newSkinResourcePatch, newGeometryData == nullptr ? skinGeometryData : newGeometryData, skinAnimationData, isPremiumSkin, isPersonaSkin,
		__int64 res = oFunc(_this, privateKeyManager, a3, selfSignedId, serverAddress, clientRandomId, skinId, (newGeometryData == nullptr && !std::get<0>(texOverride)) ? skinData : newSkinData, capeData, coolSkinStuff, deviceId, inputMode, uiProfile, guiScale, languageCode, sendEduModeParams, tenantId, unused, platformUserId, fakeName != nullptr ? fakeName : thirdPartyName, fakeName != nullptr ? true : thirdPartyNameOnly, platformOnlineId, platformOfflineId, capeId);

		if (newGeometryData != nullptr) {
			memcpy(&coolSkinStuff->skinResourcePatch, &resourcePatchBackup, sizeof(TextHolder));
			resourcePatchBackup.resetWithoutDelete();
		}
		overrideStyledReturn = false;

		styledReturnText = TextHolder();

		if (hMemoryGeometry)
			FreeResource(hMemoryGeometry);
		if (hMemorySteve)
			FreeResource(hMemorySteve);

		if (newGeometryData)
			delete newGeometryData;
		delete newSkinData;
		delete newSkinResourcePatch;
		return res;
	} else {
		TextHolder* fakeName = g_Data.getFakeName();
		__int64 res = oFunc(_this, privateKeyManager, a3, selfSignedId, serverAddress, clientRandomId, skinId, skinData, capeData, coolSkinStuff, deviceId, inputMode, uiProfile, guiScale, languageCode, sendEduModeParams, tenantId, unused, platformUserId, fakeName != nullptr ? fakeName : thirdPartyName, fakeName != nullptr ? true : thirdPartyNameOnly, platformOnlineId, platformOfflineId, capeId);
		return res;
	}
}

void Hooks::InventoryTransactionManager_addAction(C_InventoryTransactionManager* a1, C_InventoryAction* a2) {
	static auto Func = g_Hooks.InventoryTransactionManager_addActionHook->GetFastcall<void, C_InventoryTransactionManager*, C_InventoryAction*>();
	Func(a1, a2);
}

bool Hooks::DirectoryPackAccessStrategy__isTrusted(__int64 _this) {
	static auto func = g_Hooks.DirectoryPackAccessStrategy__isTrustedHook->GetFastcall<bool, __int64>();

	static uintptr_t** directoryPackAccessStrategyVtable = 0;

	if (!directoryPackAccessStrategyVtable) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ?? ?? ?? ?? 49 89 06 49 8D 76 50");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		directoryPackAccessStrategyVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
	}

	if (*reinterpret_cast<uintptr_t*>(_this) == (uintptr_t)directoryPackAccessStrategyVtable)
		return true;

	return func(_this);
}

bool Hooks::ReturnTrue(__int64 _this) {
	return true;
}

__int64 Hooks::SkinRepository___loadSkinPack(__int64 _this, __int64 pack, __int64 a3) {
	static auto func = g_Hooks.SkinRepository___loadSkinPackHook->GetFastcall<__int64, __int64, __int64, __int64>();

	// auto res = (*(unsigned __int8 (**)(void))(**(__int64**)(pack + 8) + 48i64))();
	// logF("SkinRepository___loadSkinPack: origin %i, is Trusted: %i", *(int*)((*(__int64*)pack) + 888i64), res);
	*(int*)((*(__int64*)pack) + 910i64) = 2;  // Set pack origin to "2"

	return func(_this, pack, a3);
}

GamerTextHolder* Hooks::toStyledString(__int64 strIn, GamerTextHolder* strOut) {
	static auto func = g_Hooks.toStyledStringHook->GetFastcall<GamerTextHolder*, __int64, GamerTextHolder*>();

	static auto conRequest = reinterpret_cast<__int64>(g_Hooks.ConnectionRequest_createHook->funcPtr);
	if (reinterpret_cast<__int64>(_ReturnAddress()) > conRequest && reinterpret_cast<__int64>(_ReturnAddress()) < conRequest + 10000 && overrideStyledReturn) {
		// Return address is within boundaries of connection request function

		strOut->copyFrom(&styledReturnText);

		return strOut;
	}

	return func(strIn, strOut);
}

void prepCoolBean() {
	if (g_Data.getClientInstance() && g_Data.getClientInstance()->minecraftGame->getServerEntries() && *reinterpret_cast<__int64*>(g_Data.getClientInstance()->minecraftGame->getServerEntries() + 0x50)) {
		auto serverEntries = g_Data.getClientInstance()->minecraftGame->getServerEntries() + 0x48;

		struct ThirdPartyServer {
			TextHolder serverName;
			TextHolder uuid;
			TextHolder masterPlayerAccount;
			TextHolder serverName2;
			TextHolder lobbyDescription;
			TextHolder domain;            // contains the last two parts of the domain .hivebedrock.network .mineplex.com
			TextHolder pathToServerIcon;  // C:\Users\user\AppData\Local\Packages\Microsoft.MinecraftUWP_8wekyb3d8bbwe\LocalCache\minecraftpe\ContentCache\ThirdPartyServer\\<file hash>.jpg
			TextHolder serverAddress;
			int coolBoye;

			ThirdPartyServer() {
				memset(this, 0, sizeof(ThirdPartyServer));
			}
		};

		struct BeansEntry {
			BeansEntry* nextEntry;
			BeansEntry* prevEntry;
			TextHolder masterPlayer;
			float unk;
			char filler[0x3c];
			TextHolder masterPlayer2;
			TextHolder serverName;
			char filler2[8];
			std::shared_ptr<ThirdPartyServer>* start;  // array
			std::shared_ptr<ThirdPartyServer>* end;    // end of array
		};

		auto listEnd = *reinterpret_cast<BeansEntry**>(serverEntries);

		auto current = listEnd;
		int count = 0;
		while (listEnd != current->nextEntry) {
			current = current->nextEntry;
			count++;
		}
		if (count > 5)  // we already added a server
			goto end;

		// make new one
		BeansEntry* epic = new BeansEntry();
		epic->nextEntry = listEnd;
		epic->prevEntry = current;
		epic->masterPlayer.setText("");
		epic->unk = current->unk;
		memcpy(epic->filler, current->filler, sizeof(BeansEntry::filler));
		epic->masterPlayer2.setText("");
		epic->serverName.setText("Epic");
		memcpy(epic->filler2, current->filler2, sizeof(BeansEntry::filler2));

		auto cT = current->start[0].get();

		std::shared_ptr<ThirdPartyServer>* start = new std::shared_ptr<ThirdPartyServer>[1];

		{
			ThirdPartyServer* t = new ThirdPartyServer();

			t->coolBoye = cT->coolBoye;
			t->uuid.setText("");
			t->masterPlayerAccount = cT->masterPlayerAccount;
			t->lobbyDescription = cT->lobbyDescription;
			t->pathToServerIcon.setText("");
			t->serverName.setText("Horion Server");
			t->serverName2.setText("Horion Server");  // This is the one actually displayed
			t->domain.setText(".horionbeta.club");
			t->serverAddress.setText("mc.horionbeta.club");
			start[0] = std::shared_ptr<ThirdPartyServer>(t);
		}

		epic->start = start;
		epic->end = &start[1];

		current->nextEntry = epic;

		// increase count
		*reinterpret_cast<__int64*>(g_Data.getClientInstance()->minecraftGame->getServerEntries() + 0x50) += 1;
	end:;
	}
}

__int64 Hooks::prepFeaturedServers(__int64 a1) {
	static auto func = g_Hooks.prepFeaturedServersHook->GetFastcall<__int64, __int64>();
	auto ret = func(a1);

	if (g_Data.getClientInstance() == nullptr)
		return ret;

	if (g_Data.allowWIPFeatures())
		prepCoolBean();

	return ret;
}

__int64 Hooks::prepFeaturedServersFirstTime(__int64 a1, __int64 a2) {
	static auto func = g_Hooks.prepFeaturedServersFirstTimeHook->GetFastcall<__int64, __int64, __int64>();

	if (g_Data.allowWIPFeatures())
		prepCoolBean();

	auto ret = func(a1, a2);

	return ret;
}

HRESULT Hooks::swapChain__ResizeBuffers(IDXGISwapChain* chain, UINT bufferCount, UINT Width, UINT Height, DXGI_FORMAT Newformat, UINT SwapChainFlags) {
	auto func = g_Hooks.swapchain__resizeBuffersHook->GetFastcall<HRESULT, IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT>();

#ifdef TEST_DIRECTX
	GameWnd.OnWindowSizeChanged(static_cast<int>(Width), static_cast<int>(Height));
#endif
	HRESULT ret = func(chain, bufferCount, Width, Height, Newformat, SwapChainFlags);

	return ret;
}

__int64 Hooks::Cube__compile(__int64 a1, __int64 a2) {
	auto func = g_Hooks.cube__compileHook->GetFastcall<__int64, __int64, __int64>();

	auto ret = func(a1, a2);

	auto end = *reinterpret_cast<__int64*>(a1 + 0x38);
	auto it = *reinterpret_cast<__int64*>(a1 + 0x30);
	auto boi = it + 0x1C;
	while (it != end) {  // loop through PolygonQuad
		if (it != boi + 0x34) {
			auto iter2 = boi - 0xC;
			do {
				// PolygonQuad::compile
				float* floatyBoi = reinterpret_cast<float*>(iter2 - 16);
				logF("%.1f %.1f %.1f", floatyBoi[0], floatyBoi[1], floatyBoi[2]);
				iter2 += 0x14;
			} while (iter2 - 0x10 != boi + 0x34);
		}
		boi += 0x50;
		it += 0x50;
	}

	return ret;
}

__int64 Hooks::InGamePlayScreen___renderLevel(__int64 playScreen, __int64 a2, __int64 a3) {
	auto func = g_Hooks.InGamePlayScreen___renderLevelHook->GetFastcall<__int64, __int64, __int64, __int64>();
	return func(playScreen, a2, a3);
}

__int64 Hooks::GameMode_attack(C_GameMode* _this, C_Entity* ent) {
	if (ent == nullptr) return 0;
	auto func = g_Hooks.GameMode_attackHook->GetFastcall<__int64, C_GameMode*, C_Entity*>();
	moduleMgr->onAttack(ent);
	return func(_this, ent);
}

void Hooks::setPos(C_Entity* ent, vec3& poo) {
	auto func = g_Hooks.setPosHook->GetFastcall<void, C_Entity*, vec3&>();
	static auto lag = moduleMgr->getModule<AntiLagBack>();
	if (lag->isEnabled() && ent == g_Data.getLocalPlayer())  // Cancel setPos
		return;
	func(ent, poo);
}

void Hooks::LocalPlayer__updateFromCamera(__int64 a1, C_Camera* camera) {
	auto func = g_Hooks.LocalPlayer__updateFromCameraHook->GetFastcall<__int64, __int64, C_Camera*>();
	auto freecamMod = moduleMgr->getModule<Freecam>();

	/* if (freecamMod->isEnabled() && g_Data.getLocalPlayer()->isAlive()) {
		memcpy((void*)((uintptr_t)camera + 0xB8), &freecamMod->targetPos, sizeof(vec3));
		camera->renderPlayerModel = true;
		camera->renderFirstPersonObjects = false;
		camera->getPlayerRotation(&freecamMod->cameraRot);
	}

	if (noHurtcamMod->isEnabled() && g_Data.isInGame() && g_Data.getLocalPlayer()->isAlive()) {
		vec2 rot;
		camera->getPlayerRotation(&rot);
		if (camera->facesPlayerFront) {
			rot.x *= -1;  // rotate back
			rot.y += 180;
			rot = rot.normAngles();
		}

		camera->setOrientationDeg(rot.x, rot.y, 0);
	}*/

	func(a1, camera);
}

bool Hooks::Mob__isImmobile(C_Entity* ent) {
	auto func = g_Hooks.Mob__isImmobileHook->GetFastcall<bool, C_Entity*>();

	static auto antiImmobileMod = moduleMgr->getModule<AntiImmobile>();
	if (ent == g_Data.getLocalPlayer()) {
		g_Hooks.shouldLocalPlayerBeImmobile = func(ent);
		if (antiImmobileMod->isEnabled())
			return false;
	}

	return func(ent);
}
/*#ifdef _DEBUG bool Hooks::testy(C_Entity* ent) {
	static auto oFunc = g_Hooks.testyHook->GetFastcall<bool, C_Entity*>();
	static auto test = moduleMgr->getModule<TestModule>();
	if (test->isEnabled())
		return true;
	return oFunc(ent);
}
#endif*/
float Hooks::getDestroySpeed(C_Player* _this, C_Block& block) {
	static auto oFunc = g_Hooks.getDestroySpeedHook->GetFastcall<float, C_Player*, C_Block&>();
	static auto instabreakMod = moduleMgr->getModule<InstaBreak>();
	if (instabreakMod->isEnabled() && instabreakMod->mode.selected == 2)
		return NAN;
	return oFunc(_this, block);
}

void Hooks::onActorDie(C_Entity* _this, __int64 damageSource) {
	static auto oFunc = g_Hooks.actorDieHook->GetFastcall<void, C_Entity*, __int64>();
	C_LocalPlayer* Player = g_Data.getLocalPlayer();
	if (_this == Player) {
		std::string msg = "You died at (" + std::to_string((int)Player->getPos()->x) + ", " + std::to_string((int)Player->aabb.lower.y) + ", " + std::to_string((int)Player->getPos()->z) + ")";
		g_Data.getGuiData()->displayClientMessage(&msg);
	}
	oFunc(_this, damageSource);
}

void Hooks::InventoryTransactionManager__addAction(C_InventoryTransactionManager* _this, C_InventoryAction& action) {
	auto func = g_Hooks.InventoryTransactionManager__addActionHook->GetFastcall<void, C_InventoryTransactionManager*, C_InventoryAction&>();

#ifdef TEST_DEBUG
	char* srcName = "none";
	if (action.sourceItem.item && *action.sourceItem.item)
		srcName = (*action.sourceItem.item)->name.getText();
	char* targetName = "none";
	if (action.targetItem.item && *action.targetItem.item)
		targetName = (*action.targetItem.item)->name.getText();
	logF("%i %i %i %s %s", action.type, action.slot, action.sourceType, srcName, targetName, action.sourceType);

	/*if(/*action.slot == 14 && action.sourceType == 124 && strcmp(targetName, "none") == 0 && *strcmp(srcName, "stone_shovel") == 0){
		std::string tag = "{ench:[{id:9s,lvl:1s}]}";
		action.sourceItem.setUserData(std::move(Mojangson::parseTag(tag)));
	}
	if(/*action.slot == 2 && action.sourceType == 256 && strcmp(srcName, "none") == 0 &&* strcmp(targetName, "stone_shovel") == 0){
		std::string tag = "{ench:[{id:9s,lvl:1s}]}";
		action.targetItem.setUserData(std::move(Mojangson::parseTag(tag)));
	}*/
#endif

	func(_this, action);
}

void Hooks::LevelRendererPlayer__renderNameTags(__int64 a1, __int64 a2, TextHolder* a3, __int64 a4) {
	static auto func = g_Hooks.LevelRendererPlayer__renderNameTagsHook->GetFastcall<void, __int64, __int64, TextHolder*, __int64>();
	static auto nameTagsMod = moduleMgr->getModule<NameTags>();

	if (nameTagsMod->isEnabled() && nameTagsMod->nameTags.size() > 0) {
		std::string text = Utils::sanitize(a3->getText());
		std::size_t found = text.find('\n');

		if (found != std::string::npos)
			text = text.substr(0, found);

		if (nameTagsMod->nameTags.find(text) != nameTagsMod->nameTags.end())
			return;
	}

	return func(a1, a2, a3, a4);
}
