#include <Windows.h>
#include <MinHook.h>
#include "Utils/Logger.h"
#include "Utils/mem.h"
#include "Plasmic/Manager.h"
#include "Plasmic/Manager.h"
#include "Plasmic/ClickGui.h"

#include "rgb.h"
#include <thread>
#include "Plasmic/Module.h"
std::vector<ClickguiColor*> ClickguiColor::colors;
void updateRGB();
void BlockModules();
std::thread rgbThread;
std::thread blockThread;

BOOL APIENTRY ClientMain(HMODULE hmodule) {
    mem::mod = (uintptr_t)GetModuleHandleA(NULL);
    mem::g_hModule = hmodule;
    mem::isRunning = true;
    Logger::init();
    Logger::logf("gaming");


    MH_Initialize();
 
    HookManager::init();
    ModuleManager::InitModules();
    CommandManager::init();
    game::clickGui = new ClickGui;

    
    Sleep(100);

    Config::load("Default");
    rgbThread = std::thread(updateRGB);
    blockThread = std::thread(BlockModules);

    while (!game::clientinstance)
        Sleep(1);
    ClickGui::sendNotificationf(mltext("Plasmic Client is now injected!", "Plasmic Client est desormait injecte!"));
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
        HANDLE threadCreation = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ClientMain, hModule, 0, 0);
        if (threadCreation != NULL)
            CloseHandle(threadCreation);
    }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}








void Eject(HMODULE hm) {
    game::clearClientChat();
    mem::isRunning = false;
    if (blockThread.joinable()) 
        blockThread.join();
    if (rgbThread.joinable())
        rgbThread.join();

    

    HookManager::DisableAllHooks();
    Sleep(125);
    ModuleManager::DeInit();
    CommandManager::DeInit();

    Sleep(125);
    HookManager::DeInit();
    Logger::logf("the gaming is done.");

    Sleep(125);
    FreeLibraryAndExitThread(hm, 0);
}

