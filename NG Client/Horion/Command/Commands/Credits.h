#pragma once
#include "ICommand.h"
class Credits : public IMCCommand {
public:
	Credits() : IMCCommand("Credits", "puts credits in chat", "") {
		registerAlias("Credit");
	}
	~Credits() {}

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		assertTrue(g_Data.getLocalPlayer() != nullptr);

		clientMessageF("[%sNG%s] %s Credits For NG Client!", GOLD, WHITE, BLUE);
		
		clientMessageF("[%sNG%s] %s Deadtros: Original/first developer.", GOLD, WHITE, BLUE);
		
		clientMessageF("[%sNG%s] %s NRG: Really smart does bypasses and etc.", GOLD, WHITE, BLUE);
		
		clientMessageF("[%sNG%s] %s Intop: Really smart does reverse engineering.", GOLD, WHITE, BLUE);
		
		clientMessageF("[%sNG%s] %s HackerHansen: Really smart at making bypasses.", GOLD, WHITE, BLUE);
		
		clientMessageF("[%sNG%s] %s 2474: Really good at helping with NG such as fixing errors.", GOLD, WHITE, BLUE);
		
		clientMessageF("[%sNG%s] %s Sentinel: Really good at giving ideas.", GOLD, WHITE, BLUE);
		
		clientMessageF("[%sNG%s] %s Founder:Really good at making bypasses and etc.", GOLD, WHITE, BLUE);

		clientMessageF("[%sNG%s] %s NicktrosGaming: Founder of NG Client.", GOLD, WHITE, BLUE);
		return true;
	}
};