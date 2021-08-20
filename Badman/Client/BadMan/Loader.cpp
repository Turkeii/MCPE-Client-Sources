#include "Loader.h"

SlimUtils::SlimMem mem;
const SlimUtils::SlimModule* gameModule;
bool isRunning = true;

#if defined _M_X64
#pragma comment(lib, "MinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "MinHook.x86.lib")
#endif

DWORD WINAPI keyThread(LPVOID lpParam) {
	logF("Key thread started");

	bool* keyMap = static_cast<bool*>(malloc(0xFF * 4 + 0x4));
	if (keyMap == nullptr)
		throw std::exception("Keymap not allocated");

	auto clickMap = reinterpret_cast<uintptr_t>(malloc(5));
	if (clickMap == 0)
		throw std::exception("Clickmap not allocated");

	bool* keyMapAddr = nullptr;
	uintptr_t sigOffset = FindSignature("48 8D 0D ?? ?? ?? ?? 89 1C B9");
	if (sigOffset != 0x0) {
		int offset = *reinterpret_cast<int*>((sigOffset + 3));                                   // Get Offset from code
		keyMapAddr = reinterpret_cast<bool*>(sigOffset + offset + /*length of instruction*/ 7);  // Offset is relative
	} else {
		logF("!!!KeyMap not located!!!");
		throw std::exception("Keymap not located");
	}

	C_HIDController** hidController = g_Data.getHIDController();

	while (isRunning) {
		if ((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::shouldTerminate()) {  // Press L to uninject
			isRunning = false;
			break;
		}

		for (uintptr_t i = 0; i < 0xFF; i++) {
			bool* newKey = keyMapAddr + (4 * i);
			bool newKeyPressed = (*newKey) && GameData::canUseMoveKeys();  // Disable Keybinds when in chat or inventory
			bool* oldKey = keyMap + (4 * i);
			if (newKeyPressed != *oldKey) {
				moduleMgr->onKeyUpdate((int)i, newKeyPressed);
			}
			if (*newKey != *oldKey) {  // Skip Chat or inventory checks
				TabGui::onKeyUpdate((int)i, *newKey);
				ClickGui::onKeyUpdate((int)i, *newKey);
			}
		}

	

		memcpy_s(keyMap, 0xFF * 4, keyMapAddr, 0xFF * 4);

		Sleep(2);
	}
	logF("Stopping Threads...");
	GameData::terminate();
	Sleep(200);  // Give the threads a bit of time to exit

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);  // Uninject
}

DWORD WINAPI injectorConnectionThread(LPVOID lpParam) {
	logF("Injector Connection Thread started");

	struct MemoryBoi {
		short protocolVersion;
		bool isPresent;
		bool isUnread;
		int clientVersion;
		DATAPACKET_CMD cmd;
		int params[5];
		int dataSize;
		unsigned char data[3000];
		unsigned char zeroByte = 0;
	};

	unsigned char magicValues[16] = {0x00, 0x4F, 0x52, 0x00, 0x49, 0x4F, 0x4E, 0x23, 0x9C, 0x47, 0xFB, 0xFF, 0x7D, 0x9C, 0x42, 0x57};
	char* magicArray = new char[sizeof(magicValues) + sizeof(uintptr_t) * 2];
	memcpy(magicArray, magicValues, sizeof(magicValues));

	logF("Magic array at %llX", magicArray);

	auto** badmanToInjectorPtr = reinterpret_cast<MemoryBoi**>(magicArray + sizeof(magicValues));
	auto** injectorToBadManPtr = reinterpret_cast<MemoryBoi**>(magicArray + sizeof(magicValues) + sizeof(uintptr_t));

	*badmanToInjectorPtr = new MemoryBoi();
	MemoryBoi* badmanToInjector = *badmanToInjectorPtr;
	badmanToInjector->isPresent = true;
	badmanToInjector->protocolVersion = 1;

	*injectorToBadManPtr = new MemoryBoi();
	MemoryBoi* injectorToBadMan = *injectorToBadManPtr;

	magicArray[0] = 0x48;  //Only find this allocated one, not the one in the thread stack

	logF("badmanToInjectorPtr at %llX", badmanToInjector);
	logF("injectorToBadManPtr at %llX", injectorToBadMan);

	LARGE_INTEGER frequency, timeSinceLastMessage, timeSinceLastPing;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&timeSinceLastMessage);
	QueryPerformanceCounter(&timeSinceLastPing);

	bool loggedIn = false;

	while (isRunning) {
		Sleep(2);
		LARGE_INTEGER endTime;
		QueryPerformanceCounter(&endTime);
		bool isConnected = badmanToInjector->isPresent && injectorToBadMan->isPresent && badmanToInjector->protocolVersion >= injectorToBadMan->protocolVersion;

		if (isConnected && !injectorToBadMan->isUnread) {
			__int64 elapsed = endTime.QuadPart - timeSinceLastMessage.QuadPart;
			float realElapsed = (float)elapsed / frequency.QuadPart;
			if (realElapsed > 4.f) {
				isConnected = false;
				logF("Disconnected from injector due to timeout");
				injectorToBadMan->isPresent = true;
				QueryPerformanceCounter(&timeSinceLastMessage);
			}
		}
		g_Data.setInjectorConnectionActive(isConnected);

		if (isConnected) {
			// Send Ping every 2 seconds to keep connection alive
			{
				__int64 elapsedPing = endTime.QuadPart - timeSinceLastPing.QuadPart;
				float realPing = (float)elapsedPing / frequency.QuadPart;
				if (realPing > 1) {
					BadManDataPacket pingPacket;
					pingPacket.cmd = CMD_PING;
					pingPacket.params[0] = 0x1333337;
					g_Data.sendPacketToInjector(pingPacket);
					QueryPerformanceCounter(&timeSinceLastPing);
				}
			}

			if (injectorToBadMan->isUnread) {  // They sent us a message
				QueryPerformanceCounter(&timeSinceLastMessage);
				switch (injectorToBadMan->cmd) {
				case CMD_INIT: {
					logF("Got CMD_INIT from injector");
					loggedIn = true;
					int flags = injectorToBadMan->params[0];
					if (flags & (1 << 0) && injectorToBadMan->dataSize > 0 && injectorToBadMan->dataSize < sizeof(injectorToBadMan->data)) {  // Has Json data
						injectorToBadMan->data[sizeof(injectorToBadMan->data) - 1] = '\0';
						json data = json::parse(reinterpret_cast<char*>(injectorToBadMan->data));
						if (data.at("discordAuth").is_string() && data.at("serial").is_number_integer()) {
							logF("Got api token from injector");
							auto serialNum = data.at("serial").get<unsigned int>();
							if (serialNum == 0) {
								logF("Serial is null!");
								GameData::terminate();
							}

							auto roamingFolder = Logger::GetRoamingFolderPath();
							if (roamingFolder.substr(0, 2) == L"C:") {  // Make sure we're getting a handle to the C volume

								HANDLE file = CreateFileW(roamingFolder.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS, 0);
								if (file != INVALID_HANDLE_VALUE) {
									unsigned long serial = 0;
									unsigned long maxNameLen = 0, flags2 = 0;
									bool succ = GetVolumeInformationByHandleW(file, 0, 0, &serial, &maxNameLen, &flags2, nullptr, 0);
									if (succ) {
										/*if (serial != serialNum) { // Dont print the raw values here, don't leak serials
											logF("Serial doesn't match! (Diff: %lli)", (long long) serial - (long long)serialNum);
											g_Data.terminate();
										}
										serialNum = serial;*/
									}
									CloseHandle(file);
								}
							}
						}
					}
					if (flags & (1 << 2))  // WIP Features
						g_Data.setAllowWIPFeatures(true);

					break;
				}
				case CMD_PING: {
					BadManDataPacket pongPacket;
					pongPacket.cmd = CMD_PONG;
					pongPacket.params[0] = injectorToBadMan->params[0];
					g_Data.sendPacketToInjector(pongPacket);
					break;
				}
				case CMD_PONG: {
					break;
				}
				case CMD_RESPONSE: {
					int id = injectorToBadMan->params[1];

					auto pk = std::make_shared<BadManDataPacket>();
					pk->cmd = (DATAPACKET_CMD)injectorToBadMan->params[0];
					memcpy(pk->params, &injectorToBadMan->params[2], sizeof(injectorToBadMan->params) - sizeof(int) * 2);

					if (injectorToBadMan->dataSize > 0 && injectorToBadMan->dataSize < 3000) {
						pk->dataArraySize = injectorToBadMan->dataSize;

						auto dataTemp = new unsigned char[injectorToBadMan->dataSize + 2];
						memset(dataTemp + injectorToBadMan->dataSize, 0, 2);  // If we don't zero the last 2 bytes, printing as unicode string won't work
						memcpy(dataTemp, injectorToBadMan->data, injectorToBadMan->dataSize);
						auto tmp = std::shared_ptr<unsigned char[]>(dataTemp);
						pk->data.swap(tmp);
					}

					g_Data.callInjectorResponseCallback(id, pk);
					break;
				}
				case CMD_LOG: {
					if(injectorToBadMan->dataSize > 4 && injectorToBadMan->dataSize < 2999){
						injectorToBadMan->data[injectorToBadMan->dataSize] = 0; // null terminator

						char* command = reinterpret_cast<char*>(&injectorToBadMan->data[3]);
						if(command[1] == cmdMgr->prefix)
							command++;

						cmdMgr->execute(command);
					}
					break;
				}
				default:
					break;
				}

				injectorToBadMan->isUnread = false;
			}

			// Send log messages
			{
				auto vecLock = Logger::GetTextToInjectorLock();;

				if (loggedIn && g_Data.isPacketToInjectorQueueEmpty()) {
					auto* stringPrintVector = Logger::GetTextToSend();
#if defined(_DEBUG) or defined(_BETA)
					if (stringPrintVector->size() > 0 && g_Data.isPacketToInjectorQueueEmpty()) {
						auto str = *stringPrintVector->begin();
						stringPrintVector->erase(stringPrintVector->begin());
						
						auto wstr = Utils::stringToWstring(str->text);
						
						const wchar_t* ident = L"log ";
						size_t identLength = wcslen(ident);
						size_t textLength = wcslen(wstr.c_str()) + identLength;

						if(textLength < 2990){
							BadManDataPacket packet;
							packet.cmd = CMD_LOG;
							auto tmp = std::shared_ptr<unsigned char[]>(new unsigned char[(textLength + 1) * sizeof(wchar_t)]);
							packet.data.swap(tmp);
							size_t leng = (textLength + 1) * sizeof(wchar_t);
							wcscpy_s((wchar_t*)packet.data.get(), textLength, ident);
							wcscpy_s((wchar_t*)(packet.data.get() + identLength * sizeof(wchar_t)), textLength - identLength + 1, wstr.c_str());
							packet.dataArraySize = (int)wcslen((wchar_t*)packet.data.get()) * sizeof(wchar_t);

							if(packet.dataArraySize < 2999)
								g_Data.sendPacketToInjector(packet);
						}
					}
#else
					stringPrintVector->clear();
#endif
				}
			}

			if (!badmanToInjector->isUnread && !g_Data.isPacketToInjectorQueueEmpty()) {
				QueryPerformanceCounter(&timeSinceLastMessage);
				// They read the message, lets send the next one
				BadManDataPacket nextDataPack = g_Data.getPacketToInjector();
				if (nextDataPack.dataArraySize >= 3000) {
					throw std::exception("BadMan Data packet too big to send");
				}

				badmanToInjector->cmd = nextDataPack.cmd;
				memcpy(badmanToInjector->params, nextDataPack.params, sizeof(int) * 5);
				if (nextDataPack.dataArraySize > 0) {
					memcpy(badmanToInjector->data, nextDataPack.data.get(), nextDataPack.dataArraySize);
				}

				badmanToInjector->dataSize = nextDataPack.dataArraySize;

				badmanToInjector->isUnread = true;
			}
		} else
			Sleep(30);
	}
	logF("Quitting connection thread");
	badmanToInjector->isPresent = false;
	memset(magicValues, 0, sizeof(magicValues));
	memset(magicArray, 0, sizeof(magicValues) + sizeof(uintptr_t) * 2);
	Sleep(150);
	delete *badmanToInjectorPtr;
	delete *injectorToBadManPtr;
	delete[] magicArray;

	ExitThread(0);
}

#ifndef _MSC_VER
#define _MSC_VER "unk"
#endif

DWORD WINAPI start(LPVOID lpParam) {
	logF("Starting up...");
	logF("MSC v%i at %s", _MSC_VER, __TIMESTAMP__);

	DWORD conThread;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)injectorConnectionThread, lpParam, NULL, &conThread);
	logF("InjCon: %i", conThread);
	init();

	DWORD procId = GetCurrentProcessId();
	if (!mem.Open(procId, SlimUtils::ProcessAccess::Full)) {
		logF("Failed to open process, error-code: %i", GetLastError());
		return 1;
	}
	gameModule = mem.GetModule(L"Minecraft.Windows.exe");  // Get Module for Base Address

	MH_Initialize();
	g_Data.checkGameVersion();
	GameData::initGameData(gameModule, &mem, (HMODULE)lpParam);
	Target::init(g_Data.getPtrLocalPlayer());

	Hooks::Init();

	DWORD keyThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)keyThread, lpParam, NULL, &keyThreadId);  // Checking Keypresses
	logF("KeyT: %i", keyThreadId);

	logF("Waiting for injector");
	while (!g_Data.isInjectorConnectionActive()) {
		Sleep(10);
		if (!isRunning)
			ExitThread(0);
	}
	logF("Injector found");

	cmdMgr->initCommands();
	logF("Initialized command manager (1/3)");
	moduleMgr->initModules();
	logF("Initialized module manager (2/3)");
	configMgr->init();
	logF("Initialized config manager (3/3)");

	Hooks::Enable();
	TabGui::init();
	ClickGui::init();

	logF("Hooks enabled");

	std::thread countThread([] {
		while (isRunning) {
			Sleep(1000);
			g_Data.fps = g_Data.frameCount;
			g_Data.frameCount = 0;
			g_Data.cpsLeft = g_Data.leftclickCount;
			g_Data.leftclickCount = 0;
			g_Data.cpsRight = g_Data.rightclickCount;
			g_Data.rightclickCount = 0;
		}
	});
	countThread.detach();

	logF("Count thread started");

	ExitThread(0);
}

BOOL __stdcall DllMain(HMODULE hModule,
					   DWORD ul_reason_for_call,
					   LPVOID) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: {
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, hModule, NULL, NULL);
		DisableThreadLibraryCalls(hModule);
	} break;
	case DLL_PROCESS_DETACH:
		isRunning = false;

		scriptMgr.unloadAllScripts();
		configMgr->saveConfig();
		moduleMgr->disable();
		cmdMgr->disable();
		Hooks::Restore();
		//GameWnd.OnDeactivated();

		logF("Removing logger");
		Logger::Disable();

		MH_Uninitialize();
		delete moduleMgr;
		delete cmdMgr;
		delete configMgr;
		}
		return true;
	}