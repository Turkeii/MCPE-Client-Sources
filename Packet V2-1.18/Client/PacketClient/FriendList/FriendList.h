#pragma once

#include <algorithm>
#include <string>
#include <typeinfo>
#include <vector>

#include "../../Memory/GameData.h"

class FriendList {
private:
	//GameData* gameData;
public:
	FriendList();
	~FriendList();

	static std::vector<std::string> getList();
	static bool findPlayer(std::string Name);
	static void addPlayerToList(std::string name);
	static bool removePlayer(std::string& g);
	std::vector<std::string> List;
};

extern FriendList g_friend;
