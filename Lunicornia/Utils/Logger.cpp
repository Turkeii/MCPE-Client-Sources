#include "Logger.h"

char logPath[200]; 
bool initializedLogger = false;
bool loggerActive = true;
CRITICAL_SECTION loggerLock;
CRITICAL_SECTION vecLock;
std::vector<TextForPrint> stringPrintVector = std::vector<TextForPrint>();

std::wstring Logger::GetRoamingFolderPath()
{
	ComPtr<IApplicationDataStatics> appDataStatics;
	auto hr = RoGetActivationFactory(HStringReference(L"Windows.Storage.ApplicationData").Get(), __uuidof(appDataStatics), &appDataStatics);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve application data statics");

	ComPtr<IApplicationData> appData;
	hr = appDataStatics->get_Current(&appData);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve current application data");

	ComPtr<IStorageFolder> roamingFolder;
	hr = appData->get_RoamingFolder(&roamingFolder);
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve roaming folder");

	ComPtr<IStorageItem> folderItem;
	hr = roamingFolder.As(&folderItem);
	if (FAILED(hr)) throw std::runtime_error("Failed to cast roaming folder to IStorageItem");

	HString roamingPathHString;
	hr = folderItem->get_Path(roamingPathHString.GetAddressOf());
	if (FAILED(hr)) throw std::runtime_error("Failed to retrieve roaming folder path");

	uint32_t pathLength;
	auto roamingPathCStr = roamingPathHString.GetRawBuffer(&pathLength);
	return std::wstring(roamingPathCStr, pathLength);

}
#include "../Horion/Module/ModuleManager.h"
void Logger::WriteLogFileF(const char * fmt, ...)
{
}

void Logger::WriteBigLogFileF(size_t maxSize, const char* fmt, ...)
{
}

std::vector<TextForPrint>* Logger::GetTextToPrint()
{
	return &stringPrintVector;
}

CRITICAL_SECTION* Logger::GetTextToPrintSection()
{
	return &vecLock;
}

void Logger::Disable()
{
	
	loggerActive = false;
#ifdef _DEBUG
	EnterCriticalSection(&loggerLock);
	EnterCriticalSection(&vecLock);
	LeaveCriticalSection(&vecLock);
	LeaveCriticalSection(&loggerLock);
	Sleep(50);

	DeleteCriticalSection(&loggerLock);
	DeleteCriticalSection(&vecLock);
#endif

}
