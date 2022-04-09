#pragma once
#include "Module.h"

class Spammer : public IModule {
private:
	int Odelay = 0;
	bool bypass = true;
	int delay = 2;
	int length = 8;
	std::string message = "Packet Client - The best client for MCBE | discord.gg/J3vUwUWRVq";

public:
	Spammer();
	~Spammer();

	inline std::string& getMessage() { return message; };
	inline int& getDelay() { return delay; };
	inline bool& getBypass() { return bypass; };

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};