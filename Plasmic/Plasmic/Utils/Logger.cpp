#include "Logger.h"
#include <string>
#include <Windows.h>
#include <filesystem>
#include <fstream>

bool hasExtension(std::string fileName) {
	std::string::size_type idx;
	idx = fileName.rfind('.');

	return idx != std::string::npos;
}

bool doesPathExist(std::string path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

void CreateDir(std::string path) {
	if (!hasExtension(path)) {
		std::string envPath = getenv("APPDATA");
		if (envPath.length() <= 0)
			return;

		std::string roamingDir = envPath + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\");
		if (!doesPathExist(roamingDir))
			return;

		std::string precisePath = std::string(roamingDir + path);
		std::filesystem::create_directories(precisePath);
	}
}

void DeletePath(std::string path) {
	std::string precisePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\" + path);
	if (doesPathExist(precisePath)) {
		if (std::filesystem::is_directory(precisePath)) {
			std::filesystem::remove_all(precisePath);
		}
		else {
			std::filesystem::remove(precisePath);
		}
	}
}

void WriteToFile(std::string str, std::string path) {
if (hasExtension(path)) {
		std::string precisePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\" + path);
		if (!doesPathExist(precisePath)) {
			std::filesystem::path p(precisePath);
			std::filesystem::create_directories(p.parent_path().string());
		}

		CloseHandle(CreateFileA(precisePath.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));
		if (doesPathExist(precisePath) && str.length() > 0) {
			std::ofstream fileOutput;
			fileOutput.open(precisePath.c_str(), std::ios_base::app);
			fileOutput << str << std::endl;
			fileOutput.close();
		}
	}
}

void Logger::init() {
	DeletePath("Plasmic/Logs.txt");
}


extern void sendChatMessage(const char* format, va_list list);
void Logger::logf(const char* format, ...) {
	char buffer[350] = {0};

	va_list argsptr;
	va_start(argsptr, format);
	vsprintf((buffer + 8), format, argsptr);

	buffer[0] = 'L';
	buffer[1] = 'O';
	buffer[2] = 'G';
	buffer[3] = ':';
	buffer[4] = ' ';
	buffer[5] = ' ';
	buffer[6] = ' ';
	buffer[7] = ' ';


	WriteToFile(buffer, "Plasmic/Logs.txt");
	//sendChatMessage(buffer, NULL);
}

void Logger::log(const char* Text) {
#ifndef _NDEBUG
	WriteToFile(Text, "Plasmic/Logs.txt");
	//sendChatMessage(Text, NULL);
#endif
}