#include "Manager.h"

std::vector<Command*> CommandManager::commands;



#include "Commands/Help.h"
#include "Commands/SayCommand.h"
#include "Commands/SyncRainbow.h"
#include "Commands/setcolor.h"


#include "Commands/DebugCommand.h"



void CommandManager::init() {
	CommandManager::commands.push_back(new Help);
	CommandManager::commands.push_back(new SayCommand);
	CommandManager::commands.push_back(new SyncRainbow);
	CommandManager::commands.push_back(new SetColorCommand);


#ifndef NDEBUG
	CommandManager::commands.push_back(new DebugCommand);
#endif

}

void CommandManager::DeInit() {
	for (uint16_t i = 0; i < commands.size(); i++)
		if (commands[i] != nullptr)
			delete commands[i];
}


void CommandManager::onCommand(const char* text) {
	size_t tlenght = strlen(text);

	for (uint16_t i = 0; i < commands.size(); i++) 
		if (startWith(text, tlenght, commands[i]->command, commands[i]->commandLenght - 1)) {
			commands[i]->execute(text + commands[i]->commandLenght + 1);
			return;
		}
		
	game::sendClientChat(mltext("This command is not valid!", "Cette commande n'est pas valide!"));
}



bool cmpAfterFirstSpace(const char* text, const char* compareTo) {
	for (int i = 0;; i++) {
		if (text[i] == 0)
			return false;
		else if (text[i] == ' ')
			return !strcmp(text + i + 1, compareTo);
	}
}
bool cmpAfterFirstOrSecondSpace(const char* text, const char* compareTo) {
	bool isFirstSpace = true;
	for (int i = 0;; i++) {
		if (text[i] == 0)
			return false;
		else if (text[i] == ' ')
			if (!strcmp(text + i + 1, compareTo))
				return true;
			else if (!isFirstSpace)
				return false;
	}
}

bool endWith(const char* text, size_t textLenght, const char* compareTo, size_t compareToLenght) {
	if (compareToLenght > textLenght)
		return false;
	for (int i = 1;; i++) {
		if (text[textLenght - i] != compareTo[compareToLenght - i])
			return false;
		if (i == compareToLenght)
			return true;
	}
}
bool startWith(const char* text, size_t textLenght, const char* compareTo, size_t compareToLenght) {
	if (compareToLenght > textLenght)
		return false;
	for (int i = 0;; i++) {
		if (text[i] != compareTo[i])
			return false;
		if (i == compareToLenght)
			return true;
	}
}