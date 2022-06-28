#include <Windows.h>
#include <Psapi.h>
#include "HMath.h"
#include <sys\stat.h>
#include <iostream>
#include <direct.h>
#include <conio.h>
#include <sstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include<TlHelp32.h>
#include <tchar.h> 
#include <vector>
#include <thread>
#include <wtsapi32.h>
#include <psapi.h>
#include <math.h>
#include <algorithm> 
#include <playsoundapi.h>
#include "../../../Utils/Logger.h"
#pragma comment(lib, "winmm.lib")
#include "../Memory/Hooks.h"
#include<windows.h>
#include <tchar.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")
using namespace std;

void Utils::ApplySystemTime(std::stringstream* ss) {
	using namespace std::chrono;
#ifdef _DEBUG
	const std::chrono::system_clock::time_point systemNow = system_clock::now();
	auto ms = duration_cast<milliseconds>(systemNow.time_since_epoch()) % 10000;
	time_t now_c = system_clock::to_time_t(systemNow);
	tm timeInfo{};
	localtime_s(&timeInfo, &now_c);  // using localtime_s as std::localtime is not thread-safe.
	*ss << "[" << std::put_time(&timeInfo, "%T") << "." << std::setfill('0') << std::setw(4) << ms.count() << "] ";
#endif
}

uintptr_t cachedBase = 0;

uintptr_t Utils::getBase() {
	if (cachedBase == 0) cachedBase = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
	return cachedBase;
}

void Utils::GetCurrentSystemTime(tm& timeInfo) {
	const std::chrono::system_clock::time_point systemNow = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(systemNow);
	localtime_s(&timeInfo, &now_c);  // using localtime_s as std::localtime is not thread-safe.
}
void Utils::systemPlay(std::string name) {
	std::string path = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Kek.Club+\\CustomSounds\\") + std::string(name);
	PlaySoundA((LPCSTR)path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void Utils::makeRoamingFoldr(std::string file) {
	std::string path = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\") + std::string(file);
	// Creating File
	if (mkdir(path.c_str()) == -1)
		return;
	else
		return;
}

void Utils::makeFoldr(std::string file) {
	std::string path = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Kek.Club+\\") + std::string(file);
	// Creating File
	if (mkdir(path.c_str()) == -1)
		return;
	else
		return;
}
void Utils::patchBytes(unsigned char* dst, unsigned char* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void Utils::nopBytes(unsigned char* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

bool invalidChar(char c) {
	return !(c >= 0 && *reinterpret_cast<unsigned char*>(&c) < 128);
}

std::string Utils::sanitize(std::string text) {
	std::string out;
	bool wasValid = true;
	for (char c : text) {
		bool isValid = !invalidChar(c);
		if (wasValid) {
			if (!isValid) {
				wasValid = false;
			} else {
				out += c;
			}
		} else {
			wasValid = isValid;
		}
	}
	return out;
}

std::wstring Utils::stringToWstring(std::string txt) {
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, txt.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, txt.c_str(), -1, wstr, wchars_num);
	// do whatever with wstr
	std::wstring gamer(wstr);
	delete[] wstr;
	return gamer;
}

std::string Utils::getRttiBaseClassName(void* ptr) {
#define retIfBad(m, c) \
	if (IsBadReadPtr(reinterpret_cast<void*>(m), c)) DebugBreak();

	retIfBad(ptr, 8);

	__int64 vtable = *reinterpret_cast<__int64*>(ptr);
	retIfBad(vtable - sizeof(uintptr_t), 8);

	uintptr_t moduleBase;
	if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<char*>(vtable), reinterpret_cast<HMODULE*>(&moduleBase)))
		return std::string("invalid handle");

	auto objLocator = *reinterpret_cast<__int64*>(vtable - sizeof(uintptr_t));
	retIfBad(objLocator + 0x10, 8);
	auto classHierachyDescriptorOffset = *reinterpret_cast<int*>(objLocator + 0x10);
	auto classHierachy = moduleBase + classHierachyDescriptorOffset;
	retIfBad(classHierachy + 0x8, sizeof(unsigned int));
	int numBaseClasses = *reinterpret_cast<int*>(classHierachy + 0x8);
	if (numBaseClasses < 0 || numBaseClasses > 25)
		numBaseClasses = 0;
	retIfBad(classHierachy + 0xC, sizeof(uintptr_t));
	auto baseClassArrayOffset = *reinterpret_cast<int*>(classHierachy + 0xC);
	auto baseClassArray = moduleBase + baseClassArrayOffset;
	retIfBad(baseClassArray, sizeof(unsigned int));


	// We could iterate over all base classes here, but we just return the first
	auto classDescriptorOffset = *reinterpret_cast<unsigned int*>(baseClassArray);
	auto classDescriptor = moduleBase + classDescriptorOffset;
	retIfBad(classDescriptor, sizeof(int));
	auto typeDescripterOffset = *reinterpret_cast<int*>(classDescriptor);
	auto typeDescriptor = moduleBase + typeDescripterOffset;
	retIfBad(typeDescriptor, 0x10 + 512);

	size_t rttiLength = strnlen_s(reinterpret_cast<char*>(typeDescriptor + 0x11), 512);
	if (rttiLength > 5 && rttiLength < 512) {
		auto name = std::string(reinterpret_cast<char*>(typeDescriptor + 0x10 + 1));
		if (name.substr(0, 3) == "?AV")
			name = name.substr(3);
		if (name.substr(name.size() - 2, 2) == "@@")
			name = name.substr(0, name.size() - 2);
		return name;
	}

	return std::string("invalid");
}
size_t Utils::posToHash(const vec3_ti& pos) {
	return rotBy(pos.x, 0) | rotBy(pos.z, 24) | (static_cast<unsigned __int64>(pos.y) << 48u);
}
std::string Utils::getClipboardText() {
	if (!OpenClipboard(nullptr)) {
		return "";
	} else {
		HANDLE hData = GetClipboardData(CF_TEXT);
		char* pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr)
			return "";
		CloseClipboard();
		return std::string(pszText);
	}
}
using rmb = void(__fastcall*)(__int64);
static rmb rmbDownFunc = reinterpret_cast<rmb>(Utils::getBase() + 0x7CCBA0);  // Second one of 40 53 48 83 EC ?? 48 8B 01 48 8B D9 FF 90 ?? ?? 00 00 48 8B C8 48 8B 10 FF 52 ?? 84 C0 ?? ?? 48 8B 03 48 8B CB FF 90 ?? ?? 00 00 80 B8 ?? ?? 00 00 01
static rmb rmbUpFunc = reinterpret_cast<rmb>(Utils::getBase() + 0x7CD270);    // 48 89 5C 24 ?? 57 48 83 EC ?? 48 8B 01 48 8B D9 FF 90 ?? ?? 00 00 48 8B F8 48 85 C0 ?? ?? 48 8B ?? ?? ?? ?? ?? 80 B8 ?? ?? 00 00 00
void Utils::rightClick() {
	rmbDownFunc(g_Hooks.RMBManager);
	rmbUpFunc(g_Hooks.RMBManager);
}
void Utils::setClipboardText(std::string& text) {
	if (!OpenClipboard(nullptr))
		return;
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), text.c_str(), text.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}
uintptr_t Utils::FindSignatureModule(const char* szModule, const char* szSignature) {
	const char* pattern = szSignature;
	uintptr_t firstMatch = 0;
	static const auto rangeStart = (uintptr_t)GetModuleHandleA(szModule);
	static MODULEINFO miModInfo;
	static bool init = false;
	if (!init) {
		init = true;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	}
	static const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;

	BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;

	for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++) {
		if (!*pattern)
			return firstMatch;

		while (*(PBYTE)pattern == ' ')
			pattern++;

		if (!*pattern)
			return firstMatch;

		if (oldPat != pattern) {
			oldPat = pattern;
			if (*(PBYTE)pattern != '\?')
				patByte = GET_BYTE(pattern);
		}

		if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {
			if (!firstMatch)
				firstMatch = pCur;

			if (!pattern[2] || !pattern[1])
				return firstMatch;

			//if (*(PWORD)pattern == '\?\?' || *(PBYTE)pattern != '\?')
			//pattern += 3;

			//else
			pattern += 2;
		} else {
			pattern = szSignature;
			firstMatch = 0;
		}
	}
#ifdef _DEBUG
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
	const char* sig = szSignature;  // Put sig in here to access it in debugger
	// This will not get optimized away because we are in debug
	// Leave this in here to quickly find bad signatures in case of updates
	logF("Signature dead: %s", szSignature);
	if (false) {
		const char* msgToTheOverwhelmedDebugger = "SIGNATURE NOT FOUND";
		__debugbreak();
	}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif
	return 0u;
}
