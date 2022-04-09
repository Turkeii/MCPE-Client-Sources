#pragma once
#include "ICommand.h"
class FriendListCommand : public IMCCommand {
public:
	FriendListCommand();
	~FriendListCommand();

	static void addFriend(C_Entity* currentEntity, bool);
	static std::vector<std::string>* globalarg;

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
