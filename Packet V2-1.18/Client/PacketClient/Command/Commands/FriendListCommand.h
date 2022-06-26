#pragma once
#include "ICommand.h"
class FriendListCommand : public IMCCommand {
public:
	static void addFriend(C_Entity* currentEntity, bool);
	static std::vector<std::string>* globalarg;

	virtual bool execute(std::vector<std::string>* args) override;
	FriendListCommand();
};
