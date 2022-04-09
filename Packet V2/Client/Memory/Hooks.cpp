#include "Hooks.h"

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
TextHolder styledReturnText;
//#define TEST_DEBUG

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
				//g_Hooks.Actor_startSwimmingHook = std::make_unique<FuncHook>(localPlayerVtable[201], Hooks::Actor_startSwimming);

				//g_Hooks.Actor_ascendLadderHook = std::make_unique<FuncHook>(localPlayerVtable[339], Hooks::Actor_ascendLadder);
				
				g_Hooks.Actor_rotationHook = std::make_unique<FuncHook>(localPlayerVtable[27], Hooks::Actor_rotation);

				//g_Hooks.Actor_swingHook = std::make_unique<FuncHook>(localPlayerVtable[219], Hooks::Actor_swing);

				//g_Hooks.JumpPowerHook = std::make_unique<FuncHook>(localPlayerVtable[345], Hooks::JumpPower); //jump from ground with movement proxy

				//g_Hooks.setPosHook = std::make_unique<FuncHook>(localPlayerVtable[19], Hooks::setPos);

				g_Hooks.Actor__baseTick = std::make_unique<FuncHook>(localPlayerVtable[49], Hooks::Actor_baseTick);

				g_Hooks.Mob__isImmobileHook = std::make_unique<FuncHook>(localPlayerVtable[91], Hooks::Mob__isImmobile);

				//g_Hooks.Actor_isInWaterHook = std::make_unique<FuncHook>(localPlayerVtable[71], Hooks::Actor_isInWater);

				g_Hooks.Player_tickWorldHook = std::make_unique<FuncHook>(localPlayerVtable[364], Hooks::Player_tickWorld);

				//g_Hooks.Actor_lerpMotionHook = std::make_unique<FuncHook>(localPlayerVtable[46], Hooks::Actor_lerpMotion);

				//g_Hooks.Actor__isInvisibleHook = std::make_unique<FuncHook>(localPlayerVtable[59], Hooks::Actor__isInvisible);
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

		void* chestTick = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 56 57 41 56 48 83 EC ? 48 83 79"));
		g_Hooks.ChestBlockActor_tickHook = std::make_unique<FuncHook>(chestTick, Hooks::ChestBlockActor_tick);

		//void* lerpFunc = reinterpret_cast<void*>(FindSignature("8B 02 89 81 ? ? ? ? 8B 42 ? 89 81 ? ? ? ? 8B 42 ? 89 81 ? ? ? ? C3 CC CC CC CC CC 48 89 5C 24"));
		//g_Hooks.Actor_lerpMotionHook = std::make_unique<FuncHook>(lerpFunc, Hooks::Actor_lerpMotion);

		void* getRenderLayer = reinterpret_cast<void*>(FindSignature("8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC F3 0F 10 81"));
		g_Hooks.BlockLegacy_getRenderLayerHook = std::make_unique<FuncHook>(getRenderLayer, Hooks::BlockLegacy_getRenderLayer);

		void* getLightEmission = reinterpret_cast<void*>(FindSignature("0F B6 81 ? ? ? ? 88 02 48 8B C2"));
		g_Hooks.BlockLegacy_getLightEmissionHook = std::make_unique<FuncHook>(getLightEmission, Hooks::BlockLegacy_getLightEmission);

		void* autoComplete = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 41 8B D9"));
		g_Hooks.PleaseAutoCompleteHook = std::make_unique<FuncHook>(autoComplete, Hooks::PleaseAutoComplete);

		uintptr_t** packetSenderVtable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)g_Data.getClientInstance()->loopbackPacketSender);
		g_Hooks.LoopbackPacketSender_sendToServerHook = std::make_unique<FuncHook>(packetSenderVtable[2], Hooks::LoopbackPacketSender_sendToServer);

		void* getFov = reinterpret_cast<void*>(FindSignature("40 53 48 83 EC ?? 0F 29 7C 24 ?? 44"));
		g_Hooks.LevelRendererPlayer_getFovHook = std::make_unique<FuncHook>(getFov, Hooks::LevelRendererPlayer_getFov);

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

		void* fullbright = reinterpret_cast<void*>(FindSignature("48 83 EC ? 80 B9 ? ? ? ? ? 48 8D 54 24 ? 48 8B 01 74 ? 41 B8 ? ? ? ? FF 50 ? 48 8B 10 48 85 D2 74 ? 48 8B 42 ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? E8 ? ? ? ? 48 83 C4 ? C3 F3 0F 10 42 ? 48 83 C4 ? C3 41 B8 ? ? ? ? FF 50 ? 48 8B 10 48 85 D2 75 ? E8 ? ? ? ? CC E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC F3 0F 11 4C 24"));
		g_Hooks.GetGammaHook = std::make_unique<FuncHook>(fullbright, Hooks::GetGamma);
		
		//bad
		//void* onAppSuspended = reinterpret_cast<void*>(FindSignature("48 8B C4 55 48 8B EC 48 83 EC ? 48 C7 45 ? ? ? ? ? 48 89 58 ? 48 89 70 ? 48 89 78 ? 48 8B F1 E8 ? ? ? ? 48 8B D8 48 8B C8"));
		//g_Hooks.MinecraftGame_onAppSuspendedHook = std::make_unique<FuncHook>(onAppSuspended, Hooks::MinecraftGame_onAppSuspended);
		
		void* RakNetInstance__tick = reinterpret_cast<void*>(FindSignature("48 89 5C 24 10 48 89 74 24 18 55 57 41 54 41 56 41 57 48 8D AC 24 20 FD FF FF 48 81 EC E0 03 00 00"));
		g_Hooks.RakNetInstance_tickHook = std::make_unique<FuncHook>(RakNetInstance__tick, Hooks::RakNetInstance_tick);
		
		void* ConnectionRequest__create = reinterpret_cast<void*>(FindSignature("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B ?? ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 49 8B D9 48 89 55 E8"));
		g_Hooks.ConnectionRequest_createHook = std::make_unique<FuncHook>(ConnectionRequest__create, Hooks::ConnectionRequest_create);
		
		void* _getSkinPack = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B EA 48 8B F1"));
		g_Hooks.SkinRepository___loadSkinPackHook = std::make_unique<FuncHook>(_getSkinPack, Hooks::SkinRepository___loadSkinPack);

		void* lerpFunc = reinterpret_cast<void*>(FindSignature("8B 02 89 81 ? ? ? ? 8B 42 ? 89 81 ? ? ? ? 8B 42 ? 89 81 ? ? ? ? C3 CC CC CC CC CC 48 89 5C 24"));
		g_Hooks.Actor_lerpMotionHook = std::make_unique<FuncHook>(lerpFunc, Hooks::Actor_lerpMotion);

		void* ForceThirdPerson = reinterpret_cast<void*>(Utils::getBase() + 0xCA3D40);//48 83 ec ? 48 8b 01 48 8d 54 24 ? 41 b8 ? ? ? ? ff 50 ? 48 8b 10 48 85 d2 74 ? 48 8b 42 ? 48 8b 88 ? ? ? ? 48 85 c9 74 ? e8 ? ? ? ? 48 83 c4 ? c3 8b 42 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc cc 48 83 ec ? 48 8b 01 48 8d 54 24 ? 41 b8 ? ? ? ? ff 50 ? 48 8b 10 48 85 d2 74 ? 48 8b 42 ? 48 8b 88 ? ? ? ? 48 85 c9 74 ? e8 ? ? ? ? 48 83 c4 ? c3 8b 42 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc cc 48 83 ec ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 44 24 ? 48 8b 01 41 b8 ? ? ? ? 88 54 24 ? 48 8d 54 24 ? ff 50 ? 48 8b 08 48 85 c9 74 ? 48 8d 54 24 ? e8 ? ? ? ? 48 8b 4c 24 ? 48 33 cc e8 ? ? ? ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc cc cc cc cc 48 83 ec ? 48 8b 01 48 8d 54 24 ? 41 b8 ? ? ? ? ff 50 ? 48 8b 10 48 85 d2 74 ? 48 8b 42 ? 48 8b 88 ? ? ? ? 48 85 c9 74 ? e8 ? ? ? ? 48 83 c4 ? c3 0f b6 42 ? 48 83 c4 ? c3 e8 ? ? ? ? cc cc cc cc cc cc cc cc cc cc cc 48 83 ec ? 48 8b 01
		g_Hooks.forceThirdPerson = std::make_unique<FuncHook>(ForceThirdPerson, Hooks::ForceThirdPersonLol);
		
		//bad
		//void* _toStyledString = reinterpret_cast<void*>(FindSignature("40 55 56 57 48 81 EC ?? ?? ?? ?? 48 C7 44 24 ?? FE FF FF FF 48 89 9C 24 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 48 8B FA 48 8B D9 48 89 54 24 ?? 33 D2"));
		//g_Hooks.toStyledStringHook = std::make_unique<FuncHook>(_toStyledString, Hooks::toStyledString);
		 
#ifdef TEST_DEBUG
		void* addAction = reinterpret_cast<void*>(FindSignature("55 56 57 41 56 41 57 48 83 EC ?? 45 0F B6 F8 4C 8B F2 48 8B F1 48 8B 01 48 8B 88") - 5);
		g_Hooks.InventoryTransactionManager__addActionHook = std::make_unique<FuncHook>(addAction, Hooks::InventoryTransactionManager__addAction);
#endif

		void* localPlayerUpdateFromCam = reinterpret_cast<void*>(FindSignature("48 89 5C 24 10 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 80"));
		g_Hooks.LocalPlayer__updateFromCameraHook = std::make_unique<FuncHook>(localPlayerUpdateFromCam, Hooks::LocalPlayer__updateFromCamera);
		
		//bad
		//void* renderNameTags = reinterpret_cast<void*>(FindSignature("48 8B C4 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 C7 45 ? ? ? ? ? 48 89 58 ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05 ? ? ? ? 48 33 C4"));
		//g_Hooks.LevelRendererPlayer__renderNameTagsHook = std::make_unique<FuncHook>(renderNameTags, Hooks::LevelRendererPlayer__renderNameTags);
	
		static constexpr auto counterStart = __COUNTER__ + 1;
		#define lambda_counter (__COUNTER__ - counterStart)
		
		void* levelRendererBobView = reinterpret_cast<void*>(FindSignature("48 8B C4 48 89 58 20 57 48 ?? ?? ?? ?? 00 00 0F ?? ?? ?? 0F ?? ?? ?? ?? 0F ?? ?? ?? ?? 0F ?? ?? ??"));

		static auto bobViewHookF = [](__int64 _this, glm::mat4& matrix, float lerpT) {
			static auto origFunc = g_Hooks.lambdaHooks.at(lambda_counter)->GetFastcall<void, __int64, glm::mat4&, float>();
						static auto animations = moduleMgr->getModule<Animations>();
			static auto killaura = moduleMgr->getModule<Killaura>();
			//static auto test = moduleMgr->getModule<TestModule>();
            auto p = g_Data.getLocalPlayer();
            float degrees = fmodf(p->getPosOld()->lerp(p->getPos(), lerpT).x, 5) - 2.5f;
            degrees *= 180 / 2.5f;

            auto pos = g_Data.getClientInstance()->levelRenderer->getOrigin();

            glm::mat4 View = matrix;

            matrix = View;

            // Blocking Animation
            if (animations->isEnabled() && animations->shouldBlock && g_Data.canUseMoveKeys() && g_Data.isInGame()) {
                // 1.7
                if (animations->mode.getSelectedValue() == 1) {
                    matrix = glm::translate<float>(matrix, glm::vec3(5.54, 0.85, -2.00));
                    matrix = glm::scale<float>(matrix, glm::vec3(2, 2, 2));
                    float degrees = 13;
                    degrees *= 180 / 4;

                    auto pos = g_Data.getClientInstance()->levelRenderer->getOrigin();
            
                    glm::mat4 View = matrix;
            
                    matrix = View;
                    matrix = glm::rotate<float>(matrix, glm::radians<float>(degrees), glm::vec3(2.58, -4.40, -3.50));
                    matrix = glm::translate<float>(matrix, glm::vec3(1.08, -0.02, -0.02));
                    matrix = glm::scale<float>(matrix, glm::vec3(4, 4, 4));
                    matrix = glm::translate<float>(matrix, glm::vec3(0.5, 0.4, 0.4));
                }

                // Spin
                if (animations->mode.getSelectedValue() == 2) {
                auto player = g_Data.getLocalPlayer();
                float degrees = fmodf(player->getPosOld()->lerp(player->getPos(), lerpT).x, 5) - 2.5f;
                degrees *= 180 / 2.5f;

                auto pos = g_Data.getClientInstance()->levelRenderer->getOrigin();
            
                glm::mat4 View = matrix;
            
                matrix = View;
                matrix = glm::rotate<float>(matrix, glm::radians<float>(degrees), glm::vec3(0, 0, 1));
                }
            }

			// Custom settings
			if (animations->isEnabled() && !animations->shouldBlock && g_Data.isInGame()) {
				if (animations->translate)
					matrix = glm::translate<float>(matrix, glm::vec3(animations->xPos, animations->yPos, animations->zPos)); // X Y Z

				if (animations->scale)
					matrix = glm::scale<float>(matrix, glm::vec3(animations->xScale, animations->yScale, animations->zScale)); // SCALE

				if (animations->rotate)
					matrix = glm::rotate<float>(matrix, degrees, glm::vec3(animations->xRotate, animations->yRotate, animations->zRotate)); // idk unused
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

int Hooks::ForceThirdPersonLol(__int64 a1) {
	static auto func = g_Hooks.forceThirdPerson->GetFastcall<int, __int64>();
	if (moduleMgr->getModule<Freecam>()->isEnabled())
		return 1;
	else
		return func(a1);
}

bool Hooks::playerCallBack(C_Player* lp, __int64 a2, __int64 a3) {
	static auto oTick = g_Hooks.playerCallBack_Hook->GetFastcall<bool, C_Player*, __int64, __int64>();
	if (lp == g_Data.getLocalPlayer())
		moduleMgr->onPlayerTick(lp);
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

			if (entity != nullptr && (__int64)entity != 0xFFFFFFFFFFFFFCD7 && ent.ent != nullptr && entity->isAlive() && *(__int64*)ent.ent != 0xFFFFFFFFFFFFFCD7 && *(__int64*)ent.ent > 0x6FF000000000 && *(__int64*)ent.ent < 0x800000000000 && *((int64_t*)ent.ent + 1) < 0x6FF000000000 && *(__int64*)ent.ent <= Utils::getBase() + 0x10000000)
				validEntities.push_back(ent);
		}
		g_Hooks.entityList.clear();
		g_Hooks.entityList = validEntities;
	}
	return oTick(lp, a2, a3);
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
				g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%sYour prefix is: \"%s%c%s\"", GRAY, YELLOW, cmdMgr->prefix, RED);
				g_Data.getClientInstance()->getGuiData()->displayClientMessageF("%sEnter \"%s%cprefix .%s\" to reset your prefix", GRAY, YELLOW, cmdMgr->prefix, RED);
			}
		}
	}
	oSendMessage(_this, text);
}

void Hooks::Actor_baseTick(C_Entity* ent) {
	static auto oFunc = g_Hooks.Actor__baseTick->GetFastcall<void, C_Entity*>();
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

void Hooks::Actor_rotation(C_Entity* _this, vec2_t& angle) {
	static auto oFunc = g_Hooks.Actor_rotationHook->GetFastcall<void, C_Entity*, vec2_t&>();
	static auto killauraMod = moduleMgr->getModule<Killaura>();
	static auto freelookMod = moduleMgr->getModule<Freelook>();
	if (killauraMod->isEnabled() && g_Data.getLocalPlayer() == _this && !killauraMod->targetListEmpty && killauraMod->mode.getSelectedValue() == 1) {
		angle = { killauraMod->theRot };
	}
	if (freelookMod->isEnabled() && g_Data.getLocalPlayer() == _this) {
		angle = { freelookMod->oldPos.x, freelookMod->oldPos.y };
	}
	oFunc(_this, angle);
}

__int64 Hooks::UIScene_setupAndRender(C_UIScene* uiscene, __int64 screencontext) {
	static auto oSetup = g_Hooks.UIScene_setupAndRenderHook->GetFastcall<__int64, C_UIScene*, __int64>();

	g_Hooks.shouldRender = false;
	// g_Hooks.shouldRender = uiscene->isPlayScreen();

	return oSetup(uiscene, screencontext);
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

	DrawUtils::setCtx(renderCtx, dat);

	if (GameData::shouldHide() || !g_Hooks.shouldRender || !moduleMgr->isInitialized())
		return oText(a1, renderCtx);

	static auto hudMod = moduleMgr->getModule<HudModule>();
#ifdef _DEBUG
	static auto hudEditorMod = moduleMgr->getModule<HudEditorMod>();
#endif
	static auto notificationsMod = moduleMgr->getModule<Notifications>();
	static auto clickGuiModule = moduleMgr->getModule<ClickGuiMod>();
	static auto arraylistMod = moduleMgr->getModule<ArrayList>();
	static auto watermark = moduleMgr->getModule<Watermark>();
	static auto disabler = moduleMgr->getModule<Disabler>();
	static auto blinkMod = moduleMgr->getModule<Blink>();

	HImGui.startFrame();

	g_Data.frameCount++;

	auto wid = g_Data.getClientInstance()->getGuiData()->windowSize;

	// Call PreRender() functions
	moduleMgr->onPreRender(renderCtx);
	DrawUtils::flush();

	__int64 retval = oText(a1, renderCtx);

	bool shouldPostRender = true;
	bool shouldRenderArrayList = true;
	bool shouldRenderTabGui = true;

	static float rcolors[4];          // Rainbow color array RGBA
	static float disabledRcolors[4];  // Rainbow Colors, but for disabled modules
	static float currColor[4];        // ArrayList colors

	static constexpr float colorIncrease = 0.05f;
	static float dynamicColor = 0.f;
	static bool isIncreasingColor = true;
	static bool isIncreasingcurrColor = true;
	static float dynamic = 0.f;

	dynamic = dynamicColor;
	isIncreasingcurrColor = !isIncreasingColor;

	// Rainbow color updates
	{
		Utils::ApplyRainbow(rcolors, 0.0005f);  // Increase Hue of rainbow color array
		disabledRcolors[0] = std::min(10.f, rcolors[0] * 0.20f + -22.f);
		disabledRcolors[1] = std::min(10.f, rcolors[2] * 0.21f + -24.f);
		disabledRcolors[2] = std::min(10.f, rcolors[3] * 0.22f + -26.f);
		disabledRcolors[3] = 1;
	}
	// Dynamic color updates
	{
		dynamicColor += (isIncreasingColor ? 0.007f : -0.007f) * DrawUtils::getLerpTime();
		if (dynamicColor < 0.2f) {
			dynamicColor = 0.2;
			isIncreasingColor = true;
		}
		if (dynamicColor > 1.f) {
			dynamicColor = 1.f;
			isIncreasingColor = false;
		}
	}

	{
		// Main Menu
		std::string screenName(g_Hooks.currentScreenName);
		if (strcmp(screenName.c_str(), "start_screen") == 0) {
			// Draw Custom Geo Button
			if (g_Data.allowWIPFeatures()) {
				// if (HImGui.Button("CustomButton", vec2_t(wid.x * (0.765f - 0.5f), wid.y * 0.92f), true)) {
				// }
			}

		}
		else {
			shouldRenderTabGui = hudMod->tabGUI && hudMod->isEnabled();
			shouldRenderArrayList = arraylistMod->arraylist && arraylistMod->isEnabled();

			// CLICKGUI::RENDER clickgui render
			if (clickGuiModule->isEnabled()) {
				ClickGui::render();
				shouldPostRender = true;
				shouldRenderArrayList = false;
				shouldRenderTabGui = false;
			}

			if (shouldRenderTabGui) TabGui::render();

			{
				// Display ArrayList on the Right?
				static constexpr bool isOnSomeFuckingSide = true;

				float yOffset = 0;  // Offset of next Text
				vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
				vec2_t windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;

				vec2_t mousePos = *g_Data.getClientInstance()->getMousePos();
				mousePos.div(windowSizeReal);
				mousePos.mul(windowSize);

				// Draw ArrayList
				if (moduleMgr->isInitialized() && shouldRenderArrayList) {
					// Parameters
					float textSize = hudMod->scale;
					float textPadding = 0.6f * textSize;
					float textHeight = 10.0f * textSize;
					float smoothness = 2;

					struct IModuleContainer {
						// Struct used to Sort IModules in a std::set
						std::shared_ptr<IModule> backingModule;
						std::string moduleName;
						bool enabled;
						int keybind;
						float textWidth;
						vec2_t* pos;
						bool shouldRender = true;

						IModuleContainer(std::shared_ptr<IModule> mod) {
							auto arrayList = moduleMgr->getModule<ArrayList>();
							if (arrayList->modes) {
								const char* moduleNameChr = mod->getModuleName();
								moduleName = moduleNameChr;
							}
							else {
								const char* moduleNameChr = mod->getRawModuleName();
								moduleName = moduleNameChr;
							}

							this->enabled = mod->isEnabled();
							this->keybind = mod->getKeybind();
							this->backingModule = mod;
							this->pos = mod->getPos();

							if (!this->enabled && *this->pos == vec2_t(0.f, 0.f))
								this->shouldRender = false;
							this->textWidth = DrawUtils::getTextWidth(&moduleName, arraylistMod->scale);
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
						std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();
						for (auto it : *moduleList) {
							if (it.get() != arraylistMod)
								if (it.get() != hudMod)
#ifdef _DEBUG
									if (it.get() != hudEditorMod)
#endif
										if (it.get() != watermark)
											if (it.get() != clickGuiModule)
												modContainerList.emplace(IModuleContainer(it));
						}
					}

					int a = 0;
					int b = 0;
					int c = 0;

					// Loop through mods to display Labels
					float lastTextLenght = 0.f;
					vec4_t underline;
					for (std::set<IModuleContainer>::iterator it = modContainerList.begin(); it != modContainerList.end(); ++it) {
						if (!it->shouldRender)
							continue;

						std::string textStr = it->moduleName;
						float textWidth = it->textWidth;

						float xOffsetOri = windowSize.x - textWidth - (textPadding * 2);

						float xOffset = windowSize.x - it->pos->x;
						float barOffset = windowSize.x;
						float barSize = windowSize.x;

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
						vec2_t textPos = vec2_t(
							xOffset + textPadding,
							yOffset + textPadding);
						vec4_t rectPos = vec4_t(
							xOffset - 2,
							yOffset,
							isOnSomeFuckingSide ? windowSize.x : textWidth + (textPadding * 2),
							yOffset + textPadding * 2 + textHeight);
						vec4_t leftRect = vec4_t(
							xOffset - 2,
							yOffset,
							xOffset - 1,
							yOffset + textPadding * 2 + textHeight);
						vec2_t textShadow = vec2_t(
							xOffset + textPadding + 1,
							yOffset + textPadding + 1);
						vec4_t barBG = vec4_t(
							xOffset - 5.5f,
							yOffset,
							isOnSomeFuckingSide ? windowSize.x : textWidth + (textPadding * 2),
							yOffset + textPadding * 2 + textHeight);
						vec2_t barTextPos = vec2_t(
							xOffset + textPadding - 2.5,
							yOffset + textPadding);
						vec4_t bar = vec4_t(
							barSize - 1.5,
							yOffset,
							barOffset,
							yOffset + textPadding * 2 + textHeight);

						underline = vec4_t(windowSize.x - (lastTextLenght + 2.f + (textPadding * 2.f)), leftRect.y, leftRect.x, leftRect.y + 1.f);

						lastTextLenght = textWidth;
						c++;
						b++;
						if (b < 20)
							a = moduleMgr->getEnabledModuleCount() * 2;
						else
							b = 0;
						currColor[3] = rcolors[3];
						if (hudMod->color.getSelectedValue() == 0) {  // Rainbow
							Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[2], rcolors[1], currColor[0], currColor[2], currColor[2]);
							currColor[0] += 1 / rectPos.x * rectPos.y * 3;
							Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[1], currColor[2]);
						}
						if (hudMod->color.getSelectedValue() == 2) {  // Horion
							Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
							currColor[0] += 1.f / a * c;
							Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[1], currColor[2]);
						}
						if (hudMod->color.getSelectedValue() == 3) {  // Fadeaway
							Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
							currColor[0] += 1.f / a * c;
							Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[3], currColor[3]);
						}
						if (hudMod->color.getSelectedValue() == 4) {  // Weather
							Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[2], currColor[2]);
							currColor[0] += 1.1f / a * b;
							Utils::ColorConvertHSVtoRGB(currColor[0], currColor[2], currColor[3], currColor[0], currColor[0], currColor[1]);
						}

						if (hudMod->color.getSelectedValue() == 1) {  // Dynamic
							dynamic += (isIncreasingcurrColor ? colorIncrease : -colorIncrease);
							if (dynamic < 0.2f) {
								dynamic = 0.2f;
								isIncreasingcurrColor = true;
							}
							if (dynamic > 1.f) {
								dynamic = 1.f;
								isIncreasingcurrColor = false;
							}
						}

						auto arrayList = moduleMgr->getModule<ArrayList>();
						if (arraylistMod->mode.getSelectedValue() == 2) {                         // Bar
							DrawUtils::fillRectangle(barBG, MC_Color(0, 0, 0), arrayList->bgOp);  // ArrayList background
						}
						else {
							DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), arrayList->bgOp);  // ArrayList background
						}

						// ArrayList Modes
						// Outline
						if (arraylistMod->mode.getSelectedValue() == 0) {
							if (hudMod->color.getSelectedValue() != 1)  // Rainbow
								DrawUtils::fillRectangle(leftRect, MC_Color(currColor), 1.f);
							DrawUtils::fillRectangle(underline, MC_Color(currColor), 1.f);
							if (hudMod->color.getSelectedValue() == 1) {  // Dynamic
								DrawUtils::fillRectangle(leftRect, MC_Color(dynamic, dynamic, dynamic), 1.f);
								DrawUtils::fillRectangle(underline, MC_Color(dynamic, dynamic, dynamic), 1.f);
							}
						}

						// Split
						if (arraylistMod->mode.getSelectedValue() == 1) {
							if (hudMod->color.getSelectedValue() != 1)  // Rainbow
								DrawUtils::fillRectangle(leftRect, MC_Color(currColor), 1.f);
							if (hudMod->color.getSelectedValue() == 1) {  // Dynamic
								DrawUtils::fillRectangle(leftRect, MC_Color(dynamic, dynamic, dynamic), 1.f);
							}
						}

						// Bar
						if (arraylistMod->mode.getSelectedValue() == 2) {
							if (hudMod->color.getSelectedValue() != 1)  // Rainbow
								DrawUtils::fillRectangle(bar, MC_Color(currColor), 1.f);
							if (hudMod->color.getSelectedValue() == 1) {  // Dynamic
								DrawUtils::fillRectangle(bar, MC_Color(dynamic, dynamic, dynamic), 1.f);
							}
						}

						underline = vec4_t(windowSize.x - (textWidth + 2.f + (textPadding * 2.f)), leftRect.w, windowSize.x, leftRect.w + 1.f);

						if (!GameData::canUseMoveKeys() && rectPos.contains(&mousePos) && arraylistMod->clickToggle) {
							vec4_t selectedRect = rectPos;
							selectedRect.x = leftRect.z;
							if (leftMouseDown) {
								DrawUtils::fillRectangle(selectedRect, MC_Color(0.8f, 0.8f, 0.8f), 0.8f);
								if (executeClick)
									it->backingModule->toggle();
							}
							else
								DrawUtils::fillRectangle(selectedRect, MC_Color(0.8f, 0.8f, 0.8f, 0.8f), 0.3f);
						}

						if (arraylistMod->mode.getSelectedValue() == 2) {  // Bar
							if (hudMod->color.getSelectedValue() != 1)     // currColor
								DrawUtils::drawText(vec2_t(barTextPos), &textStr, MC_Color(currColor), textSize, 1);
							if (hudMod->color.getSelectedValue() == 1) {  // Dynamic
								DrawUtils::drawText(barTextPos, &textStr, MC_Color(dynamic, dynamic, dynamic), textSize, 1);
							}
						}
						else {
							if (hudMod->color.getSelectedValue() != 1)  // Rainbow
								DrawUtils::drawText(vec2_t(textPos), &textStr, MC_Color(currColor), textSize, 1);
							if (hudMod->color.getSelectedValue() == 1) {  // Dynamic
								DrawUtils::drawText(textPos, &textStr, MC_Color(dynamic, dynamic, dynamic), textSize, 1);
							}
						}

						yOffset += textHeight + (textPadding * 2);
					}

					// Bottom Line
					if (arraylistMod->mode.getSelectedValue() == 0)
						if (hudMod->color.getSelectedValue() != 1)  // Rainbow
							DrawUtils::fillRectangle(underline, MC_Color(currColor), 1.f);
					if (hudMod->color.getSelectedValue() == 1 && arraylistMod->mode.getSelectedValue() == 0) {  // Dynamic
						DrawUtils::fillRectangle(underline, MC_Color(dynamic, dynamic, dynamic), 1.f);
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

	// Draw HUD
	if (hudMod->isEnabled() && g_Data.canUseMoveKeys() && g_Data.isInGame()) { // suck a duck
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		// FPS
		float startY3 = windowSize.y - 50;  // fps - i need help
		float startY2 = windowSize.y - 36;  // speed
		float startY1 = windowSize.y - 22;  // position

		std::string fpsText = "FPS: " + std::to_string(g_Data.getFPS());
		float lFPS = DrawUtils::getTextWidth(&fpsText, 1) + 6.5;
		vec4_t fpsRectPos = vec4_t(2.5, startY3 + 6, lFPS, startY3 + 20);
		vec2_t fpsPos = vec2_t(fpsRectPos.x + 2, fpsRectPos.y + 3.5);

		DrawUtils::fillRectangle(fpsRectPos, MC_Color(0, 0, 0), hudMod->opacity);

		if (hudMod->color.getSelectedValue() != 1)  // Rainbow
			DrawUtils::drawText(fpsPos, &fpsText, MC_Color(currColor), 1, 1);
		if (hudMod->color.getSelectedValue() == 1)  // Dynamic
			DrawUtils::drawText(fpsPos, &fpsText, MC_Color(dynamic, dynamic, dynamic), 1, 1);

		// Speed (BPS)
		auto player = g_Data.getLocalPlayer();
		std::string speedText = "Speed: " + std::to_string((int)player->getBlocksPerSecond()) + std::string(".") + std::to_string((int)(player->getBlocksPerSecond() * 10) - ((int)player->getBlocksPerSecond() * 10));
		float lSpeed = DrawUtils::getTextWidth(&speedText, 1) + 6.5;
		vec4_t speedRectPos = vec4_t(2.5, startY2 + 6, lSpeed, startY2 + 20);
		vec2_t speedPos = vec2_t(speedRectPos.x + 2, speedRectPos.y + 3.5);

		DrawUtils::fillRectangle(speedRectPos, MC_Color(0, 0, 0), hudMod->opacity);

		if (hudMod->color.getSelectedValue() != 1)  // Rainbow
			DrawUtils::drawText(speedPos, &speedText, MC_Color(currColor), 1, 1);
		if (hudMod->color.getSelectedValue() == 1)  // Dynamic
			DrawUtils::drawText(speedPos, &speedText, MC_Color(dynamic, dynamic, dynamic), 1, 1);

		// Position
		vec3_t* currPos = g_Data.getLocalPlayer()->getPos();

		std::string position = "Position: " + std::to_string((int)floorf(currPos->x)) + " " + std::to_string((int)floorf(currPos->y)) + " " + std::to_string((int)floorf(currPos->z));
		float lPos = DrawUtils::getTextWidth(&position, 1) + 6.5;

		vec4_t rectPos = vec4_t(2.5, startY1 + 6, lPos, startY1 + 20);
		vec2_t textPos = vec2_t(rectPos.x + 2, rectPos.y + 3);

		DrawUtils::fillRectangle(rectPos, MC_Color(0, 0, 0), hudMod->opacity);

		if (hudMod->color.getSelectedValue() != 1)  // Rainbow
			DrawUtils::drawText(textPos, &position, MC_Color(currColor), 1, 1);
		if (hudMod->color.getSelectedValue() == 1)  // Dynamic
			DrawUtils::drawText(textPos, &position, MC_Color(dynamic, dynamic, dynamic), 1, 1);

		// Information
#ifdef _DEBUG
		std::string currRelease = "Developer Build";

#else
		std::string currRelease = "Public Release";
#endif
		std::string infoText = "V2.11 - " + std::string(BOLD) + currRelease;
		float infoTextLength = DrawUtils::getTextWidth(&infoText) + DrawUtils::getTextWidth(&std::string(""), 0.7) + 2;
		static const float height = (1 + 0.7 * 1) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();

		constexpr float borderPadding = 1;
		float margin = 2.f;
		vec4_t infoRect = vec4_t(
			windowSize.x - margin - infoTextLength - 2 - borderPadding * 2,
			windowSize.y - margin - height + 4,
			windowSize.x - margin + borderPadding - 2,
			windowSize.y - margin);
		vec2_t infoTextPos = vec2_t(infoRect.x + 1.5, infoRect.y + 3);

		DrawUtils::drawRoundRectangle(infoRect, MC_Color(0, 0, 0), hudMod->opacity);

		if (hudMod->color.getSelectedValue() != 1)  // Rainbow
			DrawUtils::drawText(vec2_t(infoTextPos.x + borderPadding, infoTextPos.y), &infoText, MC_Color(currColor), 1, 1);
		if (hudMod->color.getSelectedValue() == 1)  // Dynamic
			DrawUtils::drawText(vec2_t(infoTextPos.x + borderPadding, infoTextPos.y), &infoText, MC_Color(dynamic, dynamic, dynamic), 1, 1);
	}

	// Draw Watermark
	if (watermark->isEnabled() && g_Data.canUseMoveKeys() && g_Data.isInGame()) {
		auto player = g_Data.getLocalPlayer();
		std::string name = player->getNameTag()->getText();
		name = Utils::sanitize(name);
		name = name.substr(0, name.find('\n'));
		std::string name1 = "P";
		std::string name2 = "acket Client";
		std::string name3 = " : " + name;

		if (watermark->mode.getSelectedValue() == 0) { // Normal
			std::string nameBold = std::string(std::string(BOLD) + name1 + std::string(RESET) + std::string(WHITE) + name2);
			std::string nameStr = watermark->message;

			if (hudMod->color.getSelectedValue() != 1) { // Rainbow
				if (watermark->firstLetter) DrawUtils::drawText(vec2_t(6, 6), &nameBold, MC_Color(currColor), 1, 1);
				else DrawUtils::drawText(vec2_t(6, 6), &nameStr, MC_Color(currColor), 1, 1);
			}
			if (hudMod->color.getSelectedValue() == 1) { // Dynamic
				if (watermark->firstLetter) DrawUtils::drawText(vec2_t(6, 6), &nameBold, MC_Color(dynamic, dynamic, dynamic), 1, 1);
				else DrawUtils::drawText(vec2_t(6, 6), &nameStr, MC_Color(dynamic, dynamic, dynamic), 1, 1);
			}
		}

		if (watermark->mode.getSelectedValue() == 1) { // New
			float len = 9.f;
			std::string newModeBold = std::string(std::string(BOLD) + name1 + std::string(RESET) + std::string(WHITE) + name2 + name3);
			std::string newMode = std::string(watermark->message + name3);
			if (watermark->firstLetter) len = 11.f; // dont ask ok
			else len = 10.f;
			float topPos = DrawUtils::getTextWidth(&newMode, 1) + len;
			float lPos = DrawUtils::getTextWidth(&newMode, 1) + len;

			if (hudMod->color.getSelectedValue() != 1) {  // Rainbow
				DrawUtils::fillRectangle(vec4_t(6, 3, topPos, 4), MC_Color(currColor), 1);
				DrawUtils::drawRectangle(vec4_t(6, 3, topPos, 4), MC_Color(currColor), 1);
				DrawUtils::fillRectangle(vec4_t(7, 2, topPos - 1, 3), MC_Color(currColor), 1); // rounded
				if (watermark->firstLetter) DrawUtils::drawText(vec2_t(8.5, 6), &newModeBold, MC_Color(currColor), 1, 1);
				else DrawUtils::drawText(vec2_t(8.5, 6), &newMode, MC_Color(currColor), 1, 1);
			}
			if (hudMod->color.getSelectedValue() == 1) {  // Dynamic
				DrawUtils::fillRectangle(vec4_t(6, 3, topPos, 4), MC_Color(dynamic, dynamic, dynamic), 1);
				DrawUtils::fillRectangle(vec4_t(7, 2, topPos - 1, 3), MC_Color(dynamic, dynamic, dynamic), 1);
				if (watermark->firstLetter) DrawUtils::drawText(vec2_t(8.5, 6), &newModeBold, MC_Color(dynamic, dynamic, dynamic), 1, 1);
				else DrawUtils::drawText(vec2_t(8.5, 6), &newMode, MC_Color(dynamic, dynamic, dynamic), 1, 1);
			}
			DrawUtils::fillRectangle(vec4_t(6, 4, lPos, 16), MC_Color(0, 0, 0), watermark->opacity);
			DrawUtils::fillRectangle(vec4_t(7, 16, lPos - 1, 17), MC_Color(0, 0, 0), watermark->opacity); // rounded
		}
	}

	// Notifications
	if (notificationsMod->isEnabled()) {
		vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
		auto notifications = g_Data.getInfoBoxList();
		float yPos = windowSize.y - 15;
		for (auto& notification : notifications) {
			notification->fade();
			if (notification->fadeTarget == 1 && notification->duration <= 0 && notification->duration > -1)
				notification->fadeTarget = 0;
			else if (notification->duration > 0 && notification->fadeVal > 0.9f)
				notification->duration -= 1.f / 60;

			const float titleTextSize = notification->fadeVal * 1;
			const float messageTextSize = notification->fadeVal * 1;
			const float titleTextHeight = DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() * titleTextSize;
			vec2_t* pos;
			int lines = 1;

			std::string substring = notification->message;
			std::string title = std::string(BOLD) + notification->title;

			while (lines < 5) {
				auto brea = substring.find("\n");
				if (brea == std::string::npos || brea + 1 >= substring.size())
					break;
				substring = substring.substr(brea + 1);
				lines++;
			}
			if (notification->message.size() == 0)
				lines = 0;

			constexpr float notificationMessage = 1;
			constexpr float unused = 0.7f;
			static const float textHeight = (notificationMessage + unused * 1) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();
			constexpr float borderPadding = 10;
			constexpr float margin = 6;
			float nameLength = DrawUtils::getTextWidth(&substring, notificationMessage);
			float fullTextLength = nameLength + DrawUtils::getTextWidth(&std::string(""), unused) + 2;

			static float duration = 0;
			if (notification->duration > 1) {
				duration++ * notification->duration;
			}
			else {
				duration = 0;
			}

			/*static float duration = 0;
			if (duration >= 1000) duration = 0;
			else
				duration++;*/

			

			vec4_t rect = vec4_t(
				windowSize.x - margin - fullTextLength - 2 - borderPadding * 2,
				yPos - margin - textHeight - 4,
				windowSize.x - margin + borderPadding - 2,
				yPos - margin);

			if (notification->duration <= 1 && notification->duration > -1) {
				vec4_t rect2 = vec4_t(
					windowSize.x - notification->duration * 110,
					yPos - margin - textHeight - 5,
					windowSize.x - margin + borderPadding - 2,
					yPos - margin);

				vec2_t textPos = vec2_t(rect2.x + 11, rect2.y + 11);
				vec2_t titlePos = vec2_t(rect2.x + 15, rect2.y + 1);
				
				DrawUtils::drawText(vec2_t(textPos.x, textPos.y), &substring, MC_Color(255, 255, 255), 1, 1, true);
				DrawUtils::drawText(vec2_t(titlePos.x, titlePos.y), &title, MC_Color(255, 255, 255), 1, 1, true);
				DrawUtils::drawRoundRectangle(rect2, MC_Color(0, 0, 0), notificationsMod->opacity);
				
			}

			if (notification->duration > 1) {
				//deq pls add some math to this to make the line good and decrese with the timer without it being gay
				// - steal the code from drawline and improve on that
				// no i got enough aids from making a shitty rectangle 
				// colors:
				// success: 50, 255, 50
				// warning: 255, 200, 50
				// error: 255, 50, 50
				vec2_t textPos = vec2_t(rect.x + 11, rect.y + 11);
				vec2_t titlePos = vec2_t(rect.x + 15, rect.y + 1);

				
				DrawUtils::drawText(vec2_t(textPos.x, textPos.y), &substring, MC_Color(255, 255, 255), 1, 1, true);
				DrawUtils::drawText(vec2_t(titlePos.x, titlePos.y), &title, MC_Color(255, 255, 255), 1, 1, true);
				DrawUtils::drawRoundRectangle(rect, MC_Color(0, 0, 0), notificationsMod->opacity);
				DrawUtils::drawBottomLine(vec4_t{ rect.x + 1.5f, rect.y, rect.z - duration, rect.w + 0.5f }, MC_Color(255, 255, 255), 1);
			}
			yPos -= margin + 30;
		}
	}
	DrawUtils::flush();

	return retval;
}

float* Hooks::Dimension_getFogColor(__int64 _this, float* color, __int64 a3, float a4) {
	static auto oGetFogColor = g_Hooks.Dimension_getFogColorHook->GetFastcall<float*, __int64, float*, __int64, float>();
	static auto customSky = moduleMgr->getModule<CustomSky>();
	static float rcolors[4];

	if (customSky->isEnabled()) {
		if (customSky->rainbow) {
			if (rcolors[3] < 1) {
				rcolors[0] = 1;
				rcolors[1] = 0.2f;
				rcolors[2] = 0.2f;
				rcolors[3] = 1;
			}
			if (customSky->rainbow) {
				Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
				rcolors[0] += 0.001f;
				if (rcolors[0] >= 1)
					rcolors[0] = 0;
				Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);
				return rcolors;
			}
		} else {
			color[0] = customSky->red;
			color[1] = customSky->green;
			color[2] = customSky->blue;
			return color;
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

float Hooks::Dimension_getSunIntensity(__int64 a1, float a2, vec3_t* a3, float a4) {
	static auto oGetSunIntensity = g_Hooks.Dimension_getSunIntensityHook->GetFastcall<float, __int64, float, vec3_t*, float>();

	return oGetSunIntensity(a1, a2, a3, a4);
}

void Hooks::ChestBlockActor_tick(C_ChestBlockActor* _this, void* a) {
	static auto oTick = g_Hooks.ChestBlockActor_tickHook->GetFastcall<void, C_ChestBlockActor*, void*>();
	oTick(_this, a);
	static auto* chestEspMod = moduleMgr->getModule<ChestESP>();
	if (_this != nullptr && chestEspMod->isEnabled())
		GameData::addChestToList(_this);
}

void Hooks::Actor_lerpMotion(C_Entity* _this, vec3_t motVec) {
	static auto oLerp = g_Hooks.Actor_lerpMotionHook->GetFastcall<void, C_Entity*, vec3_t>();

	if (g_Data.getLocalPlayer() != nullptr && g_Data.getLocalPlayer() != _this)
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

void Hooks::LoopbackPacketSender_sendToServer(C_LoopbackPacketSender* a, C_Packet* packet) {
	static auto oFunc = g_Hooks.LoopbackPacketSender_sendToServerHook->GetFastcall<void, C_LoopbackPacketSender*, C_Packet*>();

	static auto autoSneakMod = moduleMgr->getModule<Sneak>();
	static auto freecamMod = moduleMgr->getModule<Freecam>();
	static auto blinkMod = moduleMgr->getModule<Blink>();
	static auto noPacketMod = moduleMgr->getModule<Packet>();

	if (noPacketMod->isEnabled() && g_Data.isInGame())
		return;

	if (freecamMod->isEnabled() || blinkMod->isEnabled()) {
		if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
			if (blinkMod->isEnabled()) {
				if (packet->isInstanceOf<C_MovePlayerPacket>()) {
					C_MovePlayerPacket* meme = reinterpret_cast<C_MovePlayerPacket*>(packet);
					meme->onGround = true;                                                            // Don't take Fall Damages when turned off
					blinkMod->getMovePlayerPacketHolder()->push_back(new C_MovePlayerPacket(*meme));  // Saving the packets
				} else {
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

	if (autoSneakMod->isEnabled() && g_Data.getLocalPlayer() != nullptr && autoSneakMod->doSilent && packet->isInstanceOf<C_PlayerActionPacket>()) {
		auto* pp = reinterpret_cast<C_PlayerActionPacket*>(packet);

		if (pp->action == 12 && pp->entityRuntimeId == g_Data.getLocalPlayer()->entityRuntimeId)
			return;  // dont send uncrouch
	}

	moduleMgr->onSendPacket(packet);

	oFunc(a, packet);
}

float Hooks::LevelRendererPlayer_getFov(__int64 _this, float a2, bool a3) {
	static auto oGetFov = g_Hooks.LevelRendererPlayer_getFovHook->GetFastcall<float, __int64, float, bool>();
	return oGetFov(_this, a2, a3);
}

void Hooks::MultiLevelPlayer_tick(C_EntityList* _this) {
	static auto oTick = g_Hooks.MultiLevelPlayer_tickHook->GetFastcall<void, C_EntityList*>();
	C_GameMode* gm = g_Data.getCGameMode();
	if (gm != nullptr) moduleMgr->onTick(gm);
	oTick(_this);
	GameData::EntityList_tick(_this);
}

void Hooks::GameMode_startDestroyBlock(C_GameMode* _this, vec3_ti* a2, uint8_t face, void* a4, void* a5) {
	static auto oFunc = g_Hooks.GameMode_startDestroyBlockHook->GetFastcall<void, C_GameMode*, vec3_ti*, uint8_t, void*, void*>();

	static auto nukerModule = moduleMgr->getModule<Nuker>();
	static auto instaBreakModule = moduleMgr->getModule<InstaBreak>();

	if (nukerModule->isEnabled()) {
		vec3_ti tempPos;

		int range = nukerModule->getNukerRadius();
		const bool isVeinMiner = nukerModule->isVeinMiner();
		const bool tree = nukerModule->treeMode();
		const bool isAutoMode = nukerModule->isAutoMode();

		C_BlockSource* region = g_Data.getLocalPlayer()->region;
		auto selectedBlockId = ((region->getBlock(*a2)->blockLegacy))->blockId;
		uint8_t selectedBlockData = region->getBlock(*a2)->data;

		if (!isAutoMode && !tree) {
			for (int x = -range; x < range; x++) {
				for (int y = -range; y < range; y++) {
					for (int z = -range; z < range; z++) {
						tempPos.x = a2->x + x;
						tempPos.y = a2->y + y;
						tempPos.z = a2->z + z;
						if (tempPos.y > 0) {
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
	if (instaBreakModule->isEnabled()) {
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
	if (xrayMod->isEnabled()) {
		char* text = a1->name.getText();
		if (strstr(text, "ore") == NULL)
			if (strcmp(text, "lava") != NULL)
				if (strcmp(text, "water") != NULL)
					if (strcmp(text, "portal") != NULL)
						if (strcmp(text, "amethyst_block") != NULL)
							if (strcmp(text, "ancient_debris") != NULL)
								if (strcmp(text, "command_block") != NULL)
									if (strcmp(text, "repeating_command_block") != NULL)
										if (strcmp(text, "chain_command_block") != NULL)
											if (strcmp(text, "structure_block") != NULL)
												if (strcmp(text, "deny") != NULL)
													if (strcmp(text, "allow") != NULL)
														if (strcmp(text, "bedrock") != NULL)
															if (strcmp(text, "gravel") != NULL)
																if (strcmp(text, "border_block") != NULL)
																	return 10;
	}
	return oFunc(a1);
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

__int8* Hooks::BlockLegacy_getLightEmission(C_BlockLegacy* a1, __int8* a2) {
	static auto oFunc = g_Hooks.BlockLegacy_getLightEmissionHook->GetFastcall<__int8*, C_BlockLegacy*, __int8*>();

	static auto xrayMod = moduleMgr->getModule<Xray>();
	if (xrayMod->isEnabled()) {
		*a2 = 15;
		return a2;
	}
	return oFunc(a1, a2);
}

float Hooks::GetGamma(uintptr_t* a1) {
	static auto cameraMod = moduleMgr->getModule<CameraMod>();
	static auto xrayMod = moduleMgr->getModule<Xray>();
	static auto nametagmod = moduleMgr->getModule<NameTags>();
	static auto zoomMod = moduleMgr->getModule<Zoom>();

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
		else if (!strcmp(settingname->getText(), "gfx_ingame_player_names")) {
			bool* ingamePlayerName = (bool*)((uintptr_t)list[i] + 16);
			nametagmod->ingameNametagSetting = ingamePlayerName;
			obtainedSettings++;
		}
		else if (!strcmp(settingname->getText(), "gfx_field_of_view")) {
			float* FieldOfView = (float*)((uintptr_t)list[i] + 24);
			if (zoomMod->isEnabled())
				zoomMod->OGFov = *FieldOfView;
			// Zoom calc
			{
				static auto zoomModule = moduleMgr->getModule<Zoom>();
				if (zoomModule->isEnabled()) zoomModule->target = zoomModule->strength;
				zoomModule->modifier = zoomModule->target - ((zoomModule->target - zoomModule->modifier) * 0.8f);
				if (abs(zoomModule->modifier - zoomModule->target) < 0.1f && !zoomModule->isEnabled())
					zoomModule->zooming = false;
			}
			obtainedSettings++;
		}
		if (obtainedSettings == 3) break;
	}

	if (xrayMod->isEnabled())
		return 25.f;

	if (cameraMod->isEnabled() && cameraMod->fullbright)
		return cameraMod->fbAmount;

	static auto ofunc = g_Hooks.GetGammaHook->GetFastcall<float, uintptr_t*>();
	return ofunc(a1);
}

__int64 Hooks::MinecraftGame_onAppSuspended(__int64 _this) {
	static auto oFunc = g_Hooks.MinecraftGame_onAppSuspendedHook->GetFastcall<__int64, __int64>();
	configMgr->saveConfig();
	return oFunc(_this);
}

// void Hooks::Actor_startSwimming(C_Entity* _this) {
// static auto oFunc = g_Hooks.Actor_startSwimmingHook->GetFastcall<void, C_Entity*>();

// static auto jesusModule = moduleMgr->getModule<Jesus>();
// if (jesusModule->isEnabled() && g_Data.getLocalPlayer() == _this)
// return;

// oFunc(_this);
// }

void Hooks::RakNetInstance_tick(C_RakNetInstance* _this, __int64 a2, __int64 a3) {
	static auto oTick = g_Hooks.RakNetInstance_tickHook->GetFastcall<void, C_RakNetInstance*, __int64, __int64>();
	GameData::setRakNetInstance(_this);
	oTick(_this, a2, a3);
}

float Hooks::GameMode_getPickRange(C_GameMode* _this, __int64 a2, char a3) {
	static auto oFunc = g_Hooks.GameMode_getPickRangeHook->GetFastcall<float, C_GameMode*, __int64, char>();

	if (g_Data.getLocalPlayer() != nullptr) {
		static auto blockreachMod = moduleMgr->getModule<BlockReach>();
		static auto clickTP = moduleMgr->getModule<ClickTP>();

		if (blockreachMod->isEnabled())
			return 250;

		if (clickTP->isEnabled())
			return 255;
	}

	return oFunc(_this, a2, a3);
}

__int64 Hooks::ConnectionRequest_create(__int64 _this, __int64 privateKeyManager, void* a3, TextHolder* selfSignedId, TextHolder* serverAddress, __int64 clientRandomId, TextHolder* skinId, SkinData* skinData, __int64 capeData, CoolSkinData* coolSkinStuff, TextHolder* deviceId, int inputMode, int uiProfile, int guiScale, TextHolder* languageCode, bool sendEduModeParams, TextHolder* tenantId, __int64 unused, TextHolder* platformUserId, TextHolder* thirdPartyName, bool thirdPartyNameOnly, TextHolder* platformOnlineId, TextHolder* platformOfflineId, TextHolder* capeId) {
	static auto oFunc = g_Hooks.ConnectionRequest_createHook->GetFastcall<__int64, __int64, __int64, void*, TextHolder*, TextHolder*, __int64, TextHolder*, SkinData*, __int64, CoolSkinData*, TextHolder*, int, int, int, TextHolder*, bool, TextHolder*, __int64, TextHolder*, TextHolder*, bool, TextHolder*, TextHolder*, TextHolder*>();

	auto geoOverride = g_Data.getCustomGeoOverride();

	if (g_Data.allowWIPFeatures()) {
		logF("Connection Request: InputMode: %i UiProfile: %i GuiScale: %i", inputMode, uiProfile, guiScale);
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
	*(int*)((*(__int64*)pack) + 888i64) = 2;  // Set pack origin to "2"

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
			t->serverName.setText("Packet Server");
			t->serverName2.setText("Packet Server");  // This is the one actually displayed
			t->domain.setText(".packetnbeta.club");
			t->serverAddress.setText("mc.packetbeta.wtf");
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

__int64 Hooks::GameMode_attack(C_GameMode* _this, C_Entity* ent) {
	if (!ent) return 0;
	auto func = g_Hooks.GameMode_attackHook->GetFastcall<__int64, C_GameMode*, C_Entity*>();
	moduleMgr->onAttack(ent);
	return func(_this, ent);
}

void Hooks::LocalPlayer__updateFromCamera(__int64 a1, C_Camera* camera) {
	auto func = g_Hooks.LocalPlayer__updateFromCameraHook->GetFastcall<void, __int64, C_Camera*>();
	func(a1, camera);
}

bool Hooks::Mob__isImmobile(C_Entity* ent) {
	auto func = g_Hooks.Mob__isImmobileHook->GetFastcall<bool, C_Entity*>();

	static auto antiImmobileMod = moduleMgr->getModule<AntiImmobile>();
	if (antiImmobileMod->isEnabled() && ent == g_Data.getLocalPlayer())
		return false;

	return func(ent);
}

/*void Hooks::Actor__setRot(C_Entity* _this, vec2_t& angle) {
	auto func = g_Hooks.Actor__setRotHook->GetFastcall<void, C_Entity*, vec2_t&>();
	auto killauraMod = moduleMgr->getModule<Killaura>();
	auto freelookMod = moduleMgr->getModule<Freelook>();
	if (killauraMod->isEnabled() && !killauraMod->targetListEmpty && killauraMod->rotations && _this == g_Data.getLocalPlayer()) {
		func(_this, angle = killauraMod->angle);
	}
	if (freelookMod->isEnabled() && g_Data.getLocalPlayer() == _this) {
		func(_this, angle = freelookMod->oldPos);
	}
	func(_this, angle);
}*/

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